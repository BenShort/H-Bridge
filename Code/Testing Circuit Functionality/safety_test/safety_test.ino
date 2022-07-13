//TODO: replace with a non-blocking timer:
//Pins
const int D5 = 5;
void setup() {
  //Set up h-bridge pins:
  pinMode(D5, INPUT);

  //serial
  Serial.begin(9600);
  Serial.println("setup successful");
}

//safety function to limit sensor
bool test_safety_hardware(){
  Serial.println(digitalRead(D5));
  //do this first to react faster if danger is present
  if(!digitalRead(D5)){
    Serial.println("Safety Tripped!");
  }
  else{
    Serial.println("Safety not Tripped");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  test_safety_hardware();
  delay(1000);
}
