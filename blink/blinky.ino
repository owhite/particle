int LEDPin1 = D3;

int brightness = 0;
int fadeAmount = 5;

void setup() {
  pinMode(LEDPin1, OUTPUT);
}

void loop() {
  analogWrite(LEDPin1, brightness);
  brightness = brightness + fadeAmount;
  if (brightness == 00 || brightness == 210) {
    fadeAmount = -fadeAmount ;
  }
  delay(20);
}
