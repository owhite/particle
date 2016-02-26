// input / output

int SwitchPin1 = D1;
int SwitchPin2 = D6;
int OptoIntPin = A0;
int LEDPin = D3;
int MotorEnablePin = D7;
int MotorPin1 = D0;
int MotorPin2 = D2;

// variables you can set

int PWMVal = 4;
int brightness = 0;
int fadeAmount = 5;
int pb1;
int pb2;
int optoIN;

void updateLED() {
  analogWrite(LEDPin, brightness);
  brightness = brightness + fadeAmount;
  if (brightness == 00 || brightness == 210) {
    fadeAmount = -fadeAmount ;
  }
  delay(20);
}

void setup() {
  pinMode(LEDPin, OUTPUT);
  pinMode(SwitchPin1, INPUT);
  pinMode(SwitchPin2, INPUT);
  pinMode(OptoIntPin, INPUT);
  pinMode(MotorPin1, OUTPUT);
  pinMode(MotorPin2, OUTPUT);
  pinMode(MotorEnablePin, OUTPUT);
}

void loop() {
  // updateLED();

  pb1 = digitalRead(SwitchPin1);
  pb2 = digitalRead(SwitchPin2);
  optoIN = digitalRead(OptoIntPin);
  if(optoIN == HIGH) { 
    analogWrite(LEDPin, 250);
  }
  if(pb1 == HIGH) { 
    analogWrite(LEDPin, 250);
    digitalWrite(MotorEnablePin, HIGH); 
    digitalWrite(MotorPin1, LOW); 
    analogWrite(MotorPin2, PWMVal); 
  }
  else if(pb2 == HIGH) { 
    analogWrite(LEDPin, 250);
    digitalWrite(MotorEnablePin, HIGH); 
    analogWrite(MotorPin1, PWMVal); 
    digitalWrite(MotorPin2, LOW); 
  }
  else {
    digitalWrite(MotorEnablePin, LOW); 
    digitalWrite(MotorPin1, LOW); 
    digitalWrite(MotorPin2, LOW);
    analogWrite(LEDPin, 20);
  }
}
