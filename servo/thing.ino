Servo myservo;  // create servo object to control a servo

int LEDPin1 = D6;
int ServoPin = D1;
int pos = 0;    // variable to store the servo position

int brightness = 0;
int fadeAmount = 5;

void setup() {
  pinMode(LEDPin1, OUTPUT);
  myservo.attach(ServoPin); 
  analogWrite(LEDPin1, 120);
}

void loop() {

  for(pos = 0; pos < 180; pos += 1) {                                  
    myservo.write(pos);              
    delay(10);
  }

  for(pos = 180; pos>=1; pos-=1) {
    myservo.write(pos);
    delay(10);
  }
}
