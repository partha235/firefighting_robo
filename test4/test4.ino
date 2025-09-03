#define Left 3      // left fire sensor
#define Right 4     // right fire sensor
#define Forward 5   // front fire sensor

#define LM1 6       // left motor input 1
#define LM2 7       // left motor input 2
#define RM1 8       // right motor input 1
#define RM2 9       // right motor input 2

#define Trig 10     // ultrasonic trigger
#define Echo 11     // ultrasonic echo

#define water 12    // for water pump motor

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

// --- Fire extinguish function ---
void spray_fire() {
  stop_robot();
  Serial.println("Spraying Water!");
  digitalWrite(water, HIGH);
  delay(2000);                // spray for 2 seconds
  digitalWrite(water, LOW);
}

// --- Measure ultrasonic distance ---
long getDistance() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  long duration = pulseIn(Echo, HIGH, 30000);  // timeout 30ms
  if (duration == 0) return -1;                // no reading

  long distance = duration * 0.034 / 2;        // cm
  return distance;
}

void setup() {
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(water, OUTPUT);

  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

  Serial.begin(9600);
}

void loop() {
  int lf = digitalRead(Left);
  int rf = digitalRead(Right);
  int ff = digitalRead(Forward);
  long dist = getDistance();

  Serial.print("Left = "); Serial.println(lf);
  Serial.print("Right = "); Serial.println(rf);
  Serial.print("Forward = "); Serial.println(ff);
  Serial.print("Ultrasonic = "); Serial.print(dist); Serial.println(" cm");

  // --- Fire detection logic ---
  if (!lf) {
    Serial.println("Left fire detected");
    left_turn();
    delay(300);
  }
  else if (!rf) {
    Serial.println("Right fire detected");
    right_turn();
    delay(300);
  }
  else if (!ff) {
    Serial.println("Front fire detected");
    backward();
    delay(500);
    spray_fire();   // activate water pump
  }
  // --- Ultrasonic obstacle detection ---
  else if (dist > 0 && dist < 20) {  // object closer than 20 cm
    Serial.println("Obstacle ahead! Avoiding...");
    stop_robot();
    delay(200);
    backward();
    delay(400);
    left_turn();
    delay(400);
  }
  else {
    forward();   // no fire, no obstacle
  }

  delay(100); // short delay for stability
}
