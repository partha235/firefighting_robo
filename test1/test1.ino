// to check car movement.
#define LM1 2       // left motor
#define LM2 7       // left motor
#define RM1 4       // right motor
#define RM2 12       // right motor

void setup(){
    pinMode(LM1,OUTPUT);
    pinMode(LM2,OUTPUT);
    pinMode(RM1,OUTPUT);
    pinMode(RM2,OUTPUT);
    Serial.begin(9600);
}

void forward(){
    digitalWrite(LM1,1);
    digitalWrite(LM2,0);
    digitalWrite(RM1,1);
    digitalWrite(RM2,0);
}

void backward(){
    digitalWrite(LM1,0);
    digitalWrite(LM2,1);
    digitalWrite(RM1,0);
    digitalWrite(RM2,1);
}

void loop(){
    forward();
    delay(500);
    backward();
    delay(500);


}