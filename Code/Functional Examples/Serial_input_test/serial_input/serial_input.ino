//variables
String value;
float t;

void setup(){
    Serial.begin(9600);
    Serial.println("Setup successful");
}

void loop(){
    if(Serial.available()){
        value = Serial.readString();
        t = value.toFloat();
        Serial.println(value);
        Serial.println(String(t));
    }
    else{
        Serial.println("nothing new");
        delay(1000);
    }
    
}
