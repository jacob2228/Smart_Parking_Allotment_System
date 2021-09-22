void setup() {
 pinMode(D8,INPUT);
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(D8));

}
