// to check sensor reading

#define Left 3      // left sensor
#define Right 4    // right sensor
#define Forward 5   //front sensor

void setup(){
    pinMode(Left,INPUT);
    pinMode(Right,INPUT);
    pinMode(Forward,INPUT);
    Serial.begin(9600);
}

void loop(){

    Serial.print("left = ");
    Serial.println(digitalRead(Left));

    Serial.print("Right = ");
    Serial.println(digitalRead(Right));
    
    Serial.print("Forward = ");
    Serial.println(digitalRead(Forward));

    delay(100);
}