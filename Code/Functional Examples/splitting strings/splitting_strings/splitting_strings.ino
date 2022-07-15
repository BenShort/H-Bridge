int myTimeout = 10, length;
float on_time, off_time;
String value, function, on_time_string, off_time_string;

void setup() {
  // put your setup code here, to run once:
  //serial
  Serial.begin(9600);
  Serial.setTimeout(myTimeout);
  Serial.println("setup successful");
}

void loop() {
  if(Serial.available()){
        //process input
        value = Serial.readString();
        int index = value.indexOf(' ');
        int index2 = value.indexOf(',');
        length = value.length();
        function = value.substring(0, index);
        on_time_string = value.substring(index + 1, index2);
        off_time_string = value.substring(index2 + 1, length);
        on_time = on_time_string.toFloat();
        off_time = off_time_string.toFloat();
    }
    if(function == "LR"){
        Serial.println(function + " " + String(on_time) + "," + String(off_time)); 
    }
    else if (function == "RL"){
        Serial.println(function + " " + String(on_time) + "," + String(off_time));
    }
}
