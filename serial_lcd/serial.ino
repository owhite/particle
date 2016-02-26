// variables you can set
int userMinutes = 45;
int userTimeZone = -5;
String user1 = "Lyra";
String user2 = "Owen";

bool publishSuccess;
int LEDPin = D2;
int SwitchPin1 = D0;
int SwitchPin2 = D1;

int brightness = 0;
int fadeAmount = 5;

String line1("               ");
String old_line1("               ");

String line2("               ");
String old_line2("               ");

String contactPerson;
String contactInfo;

String countDownTime; 
String currentTime;

void updateDisplay() {
  Serial1.write(12); // Clear             
  Serial1.print(line1);
  Serial1.write(13); // Form feed
  Serial1.print(line2);
}

void constructLine1(String timeStr) { // only one function needed for this
  line1 = String("     " + timeStr);
}

// there's a couple constructions for line2
void constructLine2_timed(String name, String timedStr) {
  line2 = String("Msg " + name + " @ " + timedStr);
}


void setup() {
  Time.zone(userTimeZone);

  Serial1.begin(9600);
  delay(100);
  Serial1.write(12); // Clear             
  delay(100);
  Serial1.write(17); // Turn backlight on
  delay(100);        // Required delay

  updateDisplay();

  Serial1.write(215); // a octave
  Serial1.write(212); // Quarter note
  Serial1.write(220); // A tweet
  delay(300);         // Wait

  pinMode(LEDPin, OUTPUT);
  pinMode(SwitchPin1, INPUT);
  pinMode(SwitchPin2, INPUT);

}

void loop() {
  int pb1; 
  int pb2; 

  currentTime = Time.format(Time.now(), "%I:%M");

  constructLine1(currentTime);
  if (! line1.equals(old_line1) ||
      ! line2.equals(old_line2)) {
    updateDisplay();
    old_line1 = line1;
    old_line2 = line2;
  }

  analogWrite(LEDPin, brightness);
  brightness = brightness + fadeAmount;
  pb1 = digitalRead(SwitchPin1);
  pb2 = digitalRead(SwitchPin2);

  if(pb1 == HIGH) { 
    analogWrite(LEDPin, 120);
    countDownTime = Time.format(Time.now() + (userMinutes * 60), "%I:%M");
    constructLine2_timed(user1, countDownTime);
    contactPerson = user1;
  }
  if(pb2 == HIGH) { 
    analogWrite(LEDPin, 120);
    countDownTime = Time.format(Time.now() + (userMinutes * 60), "%I:%M");
    constructLine2_timed(user2, countDownTime);
    contactPerson = user2;
  }

  if(countDownTime.equals(currentTime)) {
    Serial1.write(216); // a low octave
    Serial1.write(212); // Quarter note
    Serial1.write(220); // A tweet
    Serial1.write(215); // a high octave
    delay(1000);
    line2 = String("Notify: " + contactPerson);
    updateDisplay();
    delay(2000);

    if (contactPerson.equals(user1)) {
      publishSuccess = Spark.publish("pingUser1", "Go", 60, PRIVATE);
    }
    if (contactPerson.equals(user2)) {
      publishSuccess = Spark.publish("pingUser2", "Go", 60, PRIVATE);
    }
    if (publishSuccess) {
      line2 = String("...success");
    }
    else {
      line2 = String("Pub. failed");
    }
    updateDisplay();
    delay(2000);
    line2 = String("               ");
    updateDisplay();
    contactPerson = "";
    countDownTime = "";
  }

  if (brightness == 00 || brightness == 210) {
    fadeAmount = -fadeAmount ;
  }
  delay(20);
}
