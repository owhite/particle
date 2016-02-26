int userTimeZone = -5;
int D1Pin = D0;
int D2Pin = D1;
int PWMPin = D2;
int LEDPin1 = D3;

int brightness = 0;
int fadeAmount = 5;


String line1;
String old_line1;

String countDownTime; 
String currentTime;

void constructLine1(String timeStr) { // only one function needed for this
  line1 = String("       " + timeStr);
}

void updateDisplay() {
  Serial1.write(254);   
  Serial1.write(1);   //clear command.
  delay(10);
  Serial1.print(line1);
}

void setup() {
  Time.zone(userTimeZone);

  Serial1.begin(9600);

  delay(100);
  Serial1.write(254);   
  Serial1.write(1);   //clear command.
  delay(100);

  pinMode(D1Pin, OUTPUT);
  pinMode(D2Pin, OUTPUT);
  pinMode(PWMPin, OUTPUT);
  pinMode(LEDPin1, OUTPUT);

  digitalWrite(D1Pin, LOW);
  digitalWrite(D2Pin, LOW);

}

void loop() {

  analogWrite(PWMPin, 10);
  digitalWrite(D1Pin, HIGH);
  currentTime = Time.format(Time.now(), "%I:%M");

  constructLine1(currentTime);
  if (! line1.equals(old_line1)) {
    updateDisplay();
    old_line1 = line1;
  }

  analogWrite(LEDPin1, brightness);
  brightness = brightness + fadeAmount;
  if (brightness == 00 || brightness == 210) {
    fadeAmount = -fadeAmount ;
  }
  delay(20);

}
