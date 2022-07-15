//variables
String value;
float t;
int myTimeout = 10;
int long t1, t2, t3;

void setup(){
    Serial.begin(9600);
    Serial.setTimeout(myTimeout);
    Serial.println("Setup successful");
}

void loop(){
    if(Serial.available()){
        t1 = millis();
        value = Serial.readString();
        t2 = millis();
        t3 = t2 - t1;
        Serial.println(String(t3));
        t = value.toFloat();
        //Serial.println(value);
        Serial.println(String(t));
    }
    //else{
    //    Serial.println("nothing new");
    //    delay(1000);
    //}
    
}
