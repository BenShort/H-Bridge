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

//functions:



//first h-bridge pin configuration
//state -> true = on, false = off
bool LR(double on_time){
  //assumes that all gates are open by the time this function is reached
  //process of closing gates:
  digitalWrite(D1, true);
  digitalWrite(D4, true);

  //TODO, add delay that it takes for the MOSFETS to actually switch the load on, needed to get the correct frequency as expected
  delay(on_time);

  digitalWrite(D1, false);
  digitalWrite(D4, false);

  //Deadtime if the next instruction is to turn on the other side
  delay(MDT);
}

void RL(double on_time){
  //assumes that all gates are open by the time this function is reached
  //process of closing gates:
  digitalWrite(D2, true);
  digitalWrite(D3, true);
  
  
  //wait appropriate delay before turning back off again
  //TODO, add delay that it takes for the MOSFETS to actually switch the load on, needed to get the correct frequency as expected
  delay(on_time);

  digitalWrite(D2, false);
  digitalWrite(D3, false);

  //Deadtime if the next instruction is to turn on the other side
  delay(MDT);
}


void loop() {
  // put your main code here, to run repeatedly:
  LR(on_time_LR);
  delay(100); //can remove later once we know the minimum deadtime and can ensure that it is being taken care of
  RL(on_time_RL);
  delay(100); //same as above
}
