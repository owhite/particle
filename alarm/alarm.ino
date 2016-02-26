// variables you can set

int UpTime = 800;

int PWMVal = 200;
int brightness = 0;
int fadeAmount = 5;

// input / output

int MotorPin1 = D0;
int MotorPin2 = D1;
int LEDPin = D2;
int SwitchPin1 = D3;
int SwitchPin2 = D4;
int MotorEnablePin = D7;
int OptoIntPin = A0;

int pb1;
int pb2;
int optoIN;

void updateLED() {
  if(optoIN == HIGH) {
    brightness = 220;
  }
  analogWrite(LEDPin, brightness);
  brightness = brightness + fadeAmount;
  if (brightness <= 00 || brightness >= 250) {
    fadeAmount = -fadeAmount;
  }
  delay(20);
}

void resetArm() {
  digitalWrite(MotorEnablePin, HIGH); 
  analogWrite(MotorPin1, PWMVal); 
  digitalWrite(MotorPin2, LOW); 
  optoIN = digitalRead(OptoIntPin);
  while (optoIN != HIGH) {}
  delay(200);
  digitalWrite(MotorEnablePin, LOW); 
  digitalWrite(MotorPin1, LOW); 
  digitalWrite(MotorPin2, LOW);
}

void setup() {
  pinMode(SwitchPin1, INPUT);
  pinMode(SwitchPin2, INPUT);
  pinMode(MotorPin1, OUTPUT);
  pinMode(MotorPin2, OUTPUT);
  pinMode(MotorEnablePin, OUTPUT);
  pinMode(OptoIntPin, INPUT);
  pinMode(LEDPin, OUTPUT);
  resetArm();
}

void loop() {

  optoIN = digitalRead(OptoIntPin);
  pb1 = digitalRead(SwitchPin1);
  pb2 = digitalRead(SwitchPin2);

  updateLED();
  if(pb1 == HIGH) { 
    resetArm();
    delay(800);
  }
  else {
    digitalWrite(MotorEnablePin, LOW); 
    digitalWrite(MotorPin1, LOW); 
    digitalWrite(MotorPin2, LOW);
    analogWrite(LEDPin, 20);
  }

}
