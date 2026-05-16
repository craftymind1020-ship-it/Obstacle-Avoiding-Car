#include <Servo.h>

Servo myServo;

// ======================
// ULTRASONIC PINS
// ======================

#define trigPin 10
#define echoPin 11

// ======================
// MOTOR PINS
// ======================

#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9

// ======================
// VARIABLES
// ======================

long duration;
int distance;

// Memory system
String lastTurn = "NONE";

unsigned long turnMemoryTime = 0;

// ======================
// SETUP
// ======================

void setup() {

  Serial.begin(9600);

  // Ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Motors
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Servo
  myServo.attach(3);

  // Center servo
  myServo.write(90);

  delay(1000);
}

// ======================
// MAIN LOOP
// ======================

void loop() {

  // Forget old turn after 10 seconds
  if (millis() - turnMemoryTime > 10000) {

    lastTurn = "NONE";
  }

  // Move forward normally
  moveForward();

  // Check front distance
  distance = getDistance();

  Serial.print("Front: ");
  Serial.println(distance);

  // ======================
  // OBSTACLE DETECTED
  // ======================

  if (distance < 35) {

    stopCar();
    delay(150);

    // Move back slightly
    moveBackward();
    delay(400);

    stopCar();
    delay(150);

    // ======================
    // LOOK RIGHT
    // ======================

    myServo.write(30);
    delay(500);

    int rightDistance = getDistance();

    // ======================
    // LOOK LEFT
    // ======================

    myServo.write(150);
    delay(500);

    int leftDistance = getDistance();

    // Center servo
    myServo.write(90);
    delay(250);

    // ======================
    // DEAD END
    // ======================

    if (rightDistance < 25 && leftDistance < 25) {

      moveBackward();
      delay(800);

      // Continue previous direction
      if (lastTurn == "LEFT") {

        turnLeft();
        delay(1000);
      }

      else {

        turnRight();
        delay(1000);
      }
    }

    // ======================
    // TURN RIGHT
    // ======================

    else if (
      rightDistance > leftDistance &&
      lastTurn != "LEFT"
    ) {

      turnRight();
      delay(700);

      // Save memory
      lastTurn = "RIGHT";
      turnMemoryTime = millis();
    }

    // ======================
    // TURN LEFT
    // ======================

    else {

      turnLeft();
      delay(700);

      // Save memory
      lastTurn = "LEFT";
      turnMemoryTime = millis();
    }

    stopCar();
    delay(100);
  }
}

// ======================
// DISTANCE FUNCTION
// ======================

int getDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  distance = duration * 0.034 / 2;

  // Ignore bad readings
  if (distance == 0) {

    distance = 250;
  }

  return distance;
}

// ======================
// MOVE FORWARD
// ======================

void moveForward() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// ======================
// MOVE BACKWARD
// ======================

void moveBackward() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// ======================
// STOP
// ======================

void stopCar() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// ======================
// TURN RIGHT
// ======================

void turnRight() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// ======================
// TURN LEFT
// ======================

void turnLeft() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
