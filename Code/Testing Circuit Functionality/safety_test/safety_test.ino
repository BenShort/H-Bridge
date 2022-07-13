//TODO: replace with a non-blocking timer:

//this has no protection
//deadtimes in mns
const int MDT = 0.010;
//Pins
const int D1 = 1;
const int D2 = 2;
const int D3 = 3;
const int D4 = 4;
const int D5 = 5;

//on time for LED test
const int on_time_LR = 500;
const int on_time_RL = 500;


void setup() {
  //Set up h-bridge pins:
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, INPUT);

  //ensuring that all MOSFETS are open
  digitalWrite(D1, false);
  digitalWrite(D2, false);
  digitalWrite(D3, false);
  digitalWrite(D4, false);  

  //serial
  Serial.begin(9600);
  Serial.println("setup successful");
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
  while (!digitalRead(D5)){
      delay(5000);
  }
  //this allows us to skip the timers later on, which can be long!
  return true;


  return false;
}

bool LR(double on_time){
  //assumes that all gates are open by the time this function is reached
  //process of closing gates:
  digitalWrite(D1, true);
  digitalWrite(D4, true);

  //TODO: do we need delay, or how long does it take for the function to write anyway
  //TODO, add delay that it takes for the MOSFETS to actually switch the load on, needed to get the correct frequency as expected
  delay(MDT);
  

  //Safety Function---------------------------------------------------------------------------------------------------------------
  //this limits the function to around 100kHz strobe, which is more than enough for the intended function
  if(!digitalRead(D5)){
    //emergency off
    digitalWrite(D1, false);
    digitalWrite(D2, false);
    digitalWrite(D3, false);
    digitalWrite(D4, false);

    delay(5000);

    //will this run extra time when we don't need to?
    while (!digitalRead(D5)){
      delay(5000);
    }
    //this allows us to skip the timers later on, which can be long!
    return true;
  }
  else{
    //off like normal
    digitalWrite(D1, false);
    digitalWrite(D4, false);
  }
  //-----------------------------------------------------------------------------------------------------------------------------
  delay(on_time-MDT);
  //Deadtime if the next instruction is to turn on the other side
  delay(MDT);
  return false;
}

void loop() {
  // put your main code here, to run repeatedly:
  LR(on_time_LR);
  delay(5000);

}
