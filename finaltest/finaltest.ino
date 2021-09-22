
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "fir-data-e146a.firebaseio.com"
#define FIREBASE_AUTH "1OLiCnF4HTr0yqkCxUPtQrXxk1DVKYVXvVN11cty"
#define WIFI_SSID "Hehe"
#define WIFI_PASSWORD "bijuonstrikes123"
#define trig1 D0
#define echo1 D1
#define trig2 D2
#define echo2 D3
#define trig3 D5
#define echo3 D6


int dist,dur;
int sensor1;
int sensor2;
int sensor3;
void setup() {
  pinMode(trig1,OUTPUT);
  pinMode(echo1,INPUT);
  pinMode(trig2,OUTPUT);
  pinMode(echo2,INPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void loop()
{   
   digitalWrite(LED_BUILTIN,HIGH);
    sensor1 = sensorflag(trig1,echo1);
    if(sensor1==1)
    Firebase.setString("/ /FirebaseDB_Demo/car1","occupied");
    else
    Firebase.setString("/ /FirebaseDB_Demo/car1","unoccupied");
    
    
    sensor2 = sensorflag(trig2,echo2);

    if(sensor2==1)
    Firebase.setString("/ /FirebaseDB_Demo1/car2","occupied");
    else
    Firebase.setString("/ /FirebaseDB_Demo1/car2","unoccupied");
    

  /*   sensor3 = sensorflag(trig2,echo2);

    if(sensor3==1)
    Firebase.setString("/ /FirebaseDB_Demo/car3","occupied");
    else
    Firebase.setString("/ /FirebaseDB_Demo/car3","unoccupied");
    
    
    */
    
   /*
    Firebase.setInt("Sensor 1", sensor1);
    Firebase.setInt("Sensor 2", sensor2);
  // handle error*/
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
      
    
  }
}

int sensorflag(int trigger,int echopin)
{
  int sensorstate=0;
   digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  dur =pulseIn(echopin,HIGH);
  dist =(dur/2)/29.1;
  //Serial.println(trigger);
  Serial.println(dist);  
   if(dist<50)
    {
      delay(500);
      if(dist<50)
      sensorstate =1;
    }
    else
    {
      delay(500);
      if(dist>  50)
      sensorstate =0;
    }
   return sensorstate;
 
}

  

