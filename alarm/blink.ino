unsigned long resetInterval = 100;
unsigned long previousMillis = 0;  
unsigned long currentMillis = 0;   

int PWMVal_rewind = 5;
int PWMVal_ping = 13;
int MotorPin1 = D0;
int MotorPin2 = D1;
int MotorEnablePin = D7;
int SwitchPin1 = D3;
int SwitchPin2 = D4;
int OptoIntPin = A0;
int LEDPin = D2;

int STOP = 0;
int START = 1;
int FORWARD = 2;
int REVERSE = 3;

int optoIN;
int pb1;
int pb2;

int brightness = 0;
int fadeAmount = 5;

int pingState = STOP;

void updateLED() {
  if(optoIN == HIGH ||
     pb1 == HIGH ||
     pb2 == HIGH) {
    brightness = 250;
  }
  analogWrite(LEDPin, brightness);
  brightness = brightness + fadeAmount;
  if (brightness <= 00 || brightness >= 256) {
    fadeAmount = -fadeAmount;
  }
  delay(20);
}

void motorPause() {
  digitalWrite(MotorEnablePin, LOW); 
  digitalWrite(MotorPin1, LOW); 
  digitalWrite(MotorPin2, LOW);
  pingState = STOP;
}

void updatePing() {
  if (pingState == START) {
    pingState = REVERSE;
    digitalWrite(MotorEnablePin, HIGH); 
    analogWrite(MotorPin1, PWMVal_rewind); 
    digitalWrite(MotorPin2, LOW); 
  }
  if (pingState == REVERSE) {
    if (optoIN == HIGH) {
      delay(100);
      motorPause();
      delay(1000);
      pingState = FORWARD;
      previousMillis = millis();
      digitalWrite(MotorEnablePin, LOW); 
    }
  }
  if (pingState == FORWARD) {
    digitalWrite(MotorEnablePin, HIGH); 
    digitalWrite(MotorPin1, LOW); 
    analogWrite(MotorPin2, PWMVal_ping); 
    currentMillis = millis();
    if ((currentMillis - previousMillis) >= resetInterval) {
      digitalWrite(MotorEnablePin, HIGH); 
      motorPause();
      pingState = STOP;
    }
  }
}

void setup() {
  pinMode(LEDPin, OUTPUT);
  pinMode(OptoIntPin, INPUT);
  pinMode(SwitchPin1, INPUT);
  pinMode(SwitchPin2, INPUT);
  pinMode(MotorPin1, OUTPUT);
  pinMode(MotorPin2, OUTPUT);
  pinMode(MotorEnablePin, OUTPUT);

  digitalWrite(MotorPin1, LOW); 
  digitalWrite(MotorPin2, LOW);

  motorPause();
  delay(500);
  pingState = START;
}

void loop() {
  optoIN = digitalRead(OptoIntPin);
  pb1 = digitalRead(SwitchPin1);
  pb2 = digitalRead(SwitchPin2);

  if (pb1 == HIGH) {
    delay(200); // debounce
    pingState = START;
  }

  updateLED();
  updatePing();
}
