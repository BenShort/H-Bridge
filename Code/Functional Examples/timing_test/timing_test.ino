//this function is used to calculate the time taken for specific operations like arithemtic to take place

long int t1 = 200;
long int t2 = 137;
long int t3;
long int tim1, tim2, tim3;

void setup(){
    Serial.begin(9600);
}

void loop(){
    tim1 = micros();
    t3 = millis();
    tim2 = t1-t2-0.008;
    tim3 = tim2 - tim1;

    Serial.println(tim3);
    delay(100000);
}
