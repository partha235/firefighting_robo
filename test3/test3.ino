#define Left 3      // left sensor
#define Right 4     // right sensor
#define Forward 5   // front sensor

#define LM1 6       // left motor input 1
#define LM2 7       // left motor input 2
#define RM1 8       // right motor input 1
#define RM2 9       // right motor input 2

void setup() {
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  Serial.begin(9600);
}

// --- Motor movement functions ---
void forward() {
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  Serial.println("Forward");
}

void backward() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  Serial.println("Backward");
}

void left_turn() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  Serial.println("Left Turn");
}

void right_turn() {
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  Serial.println("Right Turn");
}

void stop_robot() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  Serial.println("Stop");
}

void loop() {
  int lf = digitalRead(Left);
  int rf = digitalRead(Right);
  int ff = digitalRead(Forward);

  Serial.print("Left = ");
  Serial.println(lf);
  Serial.print("Right = ");
  Serial.println(rf);
  Serial.print("Forward = ");
  Serial.println(ff);
  delay(100);

  // --- Logic ---
  if (!lf) {          // left sensor detects obstacle/fire
    Serial.println("Left fire");
    left_turn();
  }
  else if (!rf) {     // right sensor detects obstacle/fire
    Serial.println("Right fire");
    right_turn();
  }
  else if (!ff) {     // forward sensor detects obstacle/fire
    Serial.println("Forward fire");
    backward();
  }
  else {
    forward();        // nothing detected, keep moving forward
  }
}
