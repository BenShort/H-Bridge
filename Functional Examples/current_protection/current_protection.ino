void setup() {
  // put your setup code here, to run once:

}

//safety function to limit sensor
//returns allows the function to finish early
bool safety(){
  //the less logic here, the faster it will be
  if(!digitalRead(D5)){
    //either L or R use D1 or D2 to turn the circuit on or off, turning either off turns off the circuit, the rest are just for resetting to the 0 state
    digitalWrite(D1, false);
    digitalWrite(D2, false);
    digitalWrite(D3, false);
    digitalWrite(D4, false);
  }


  return false;
}

void loop() {
  // put your main code here, to run repeatedly:

}
