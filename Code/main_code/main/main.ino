//maximum frequency of oscialltion is the timer 1/timer loop
//TODO: replace with a non-blocking timer:
//TODO: time processes @BenShort
//this has no protection
//deadtimes in mns
const int MDT = 1; //change to actual value once measured with an oscilloscope
//Pins
const int D1 = 2;
const int D2 = 3;
const int D3 = 4;
const int D4 = 5;
const int D5 = 6;

//other variables:
float on_time = 500;
long int begin_timer, end_timer, delta_time;
int myTimeout = 10, length;
float frequency;
String value, function, frequency_string;

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
  Serial.setTimeout(myTimeout);
  Serial.println("setup successful");
}

//safety function to limit sensor
//returns allows the function to finish early
bool LR(double on_time, double off_time){
  //assumes that all gates are open by the time this function is reached
  //process of closing gates:
  digitalWrite(D1, true);
  digitalWrite(D4, true);

  
  //TODO: do we need delay, or how long does it take for the function to write anyway
  //TODO, add delay that it takes for the MOSFETS to actually switch the load on, needed to get the correct frequency as expected
  delay(MDT);
  //takes 4us to execute
  begin_timer = millis();

  //Safety Function
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
    end_timer = millis(); //takes 4us to execute
    delta_time = begin_timer - end_timer; //4us
    //total extra delay is 12us, therefore shouldn't really matter, with a strobe of 1kHz, that is only 0.12% error in the freq
    delay(on_time-MDT);
    digitalWrite(D1, false);
    digitalWrite(D4, false);
  }
  
  //Deadtime if the next instruction is to turn on the other side
  delay(MDT);
  delay(off_time - MDT);
  return false;
}
bool RL(double on_time, double off_time){
  //assumes that all gates are open by the time this function is reached
  //process of closing gates:
  digitalWrite(D2, true);
  digitalWrite(D3, true);

  
  //TODO: do we need delay, or how long does it take for the function to write anyway
  //TODO, add delay that it takes for the MOSFETS to actually switch the load on, needed to get the correct frequency as expected
  delay(MDT);
  //takes 4us to execute
  begin_timer = millis();

  //Safety Function
  //this limits the function to around 100kHz strobe, which is more than enough for the intended function
  if(!digitalRead(D5)){
    //emergency off
    digitalWrite(D2, false);
    digitalWrite(D1, false);
    digitalWrite(D3, false);
    digitalWrite(D4, false);

    delay(5000);
    Serial.println("Tripped");
    //will this run extra time when we don't need to?
    while (!digitalRead(D5)){
      Serial.println("Tripped");
      delay(5000);
    }
    //this allows us to skip the timers later on, which can be long!
    return true;
  }
  else{
    //off like normal
    end_timer = millis(); //takes 4us to execute
    delta_time = begin_timer - end_timer; //4us
    //total extra delay is 12us, therefore shouldn't really matter, with a strobe of 1kHz, that is only 0.12% error in the freq
    delay(on_time-MDT);
    digitalWrite(D2, false);
    digitalWrite(D3, false);
  }
  
  //Deadtime if the next instruction is to turn on the other side
  delay(MDT);
  delay(off_time - MDT);
  return false;
}

void main(){
    if(Serial.available()){
        //process input
        value = Serial.readString();
        int index = value.indexOf(' ');
        length = value.length();
        function = value.substring(0, index);
        frequency_string = value.substring(index + 1, length);
        frequency = frequency_string.toFloat();
        
        //decide what to do

        if(function == "LR"){
            on_time = 1/frequency;
            on_time = on_time/2;
        }
        else if(function == "RL"){
            on_time = 1/frequency;
            on_time = on_time/2;
        }
    }
    if(function == "LR"){
        LR(on_time, on_time);
    }
    else if (function == "RL"){
        RL(on_time, on_time);
    }
}

void loop() {
    main();
}
