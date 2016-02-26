int LEDPin = D2;
int SwitchPin1 = D0;
int SwitchPin2 = D1;



int brightness = 0;
int fadeAmount = 5;
int pb1 = 0; 
int pb2 = 0; 

String line1("               ");
String old_line1("               ");

String line2("               ");
String old_line2("               ");

void updateDisplay() {
  Serial1.write(12); // Clear             
  Serial1.print(line1);
  Serial1.write(13); // Form feed
  Serial1.print(line2);

}

void constructLine1() {
  line1 = Time.format(Time.now(), "     %I:%M");
}

void setup() {

  Serial1.begin(9600);
  delay(100);
  Serial1.write(12); // Clear
  delay(100);
  Serial1.write(17); // Turn backlight on
  delay(100); // Required delay

  Time.zone(-5);
  line1 = Time.format(Time.now(), "     %I:%M");
  old_line1 = line1;

  // updateDisplay();

  Serial1.write(212);                // Quarter note
  Serial1.write(220);                // A tone
  delay(300);                       // Wait 3 seconds

  pinMode(LEDPin, OUTPUT);
  pinMode(SwitchPin1, INPUT);
  pinMode(SwitchPin2, INPUT);

}

void loop() {
  line1 = constructLine1();
  if (! (line1.equals(old_line1)) ) {
    updateDisplay();
    old_line1 = line1;
  }

  pb1 = digitalRead(SwitchPin1);
  pb2 = digitalRead(SwitchPin2);
  if(pb1 == HIGH || pb2 == HIGH) { 
    analogWrite(LEDPin, 220);
    reportTime();
    if(pb1 == HIGH) { 
      Serial1.print("Msg ");
      Serial1.print(user1);
      Serial1.print(" @ ");
    }
    if(pb2 == HIGH) { 
      Serial1.print("Msg ");
      Serial1.print(user2);
      Serial1.print(" @ ");
    }
    Serial1.print(Time.format(Time.now() + (userMinutes * 60), "%I:%M"));
  }

  analogWrite(LEDPin, brightness);
  brightness = brightness + fadeAmount;
  if (brightness == 00 || brightness == 210) {
    fadeAmount = -fadeAmount ;
  }
  delay(20);

}
