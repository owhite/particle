int userTimeZone = -5;

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

  Serial1.write(254); // first line
  Serial1.write(128);
  Serial1.write("li1");

  Serial1.write(254); // second line
  Serial1.write(192);
  Serial1.write("l2");

  Serial1.write(254); // third line
  Serial1.write(148);
  Serial1.write("line3");

  Serial1.write(254); // fourth
  Serial1.write(212);
  Serial1.write("BURP4");

}

void loop() {
  currentTime = Time.format(Time.now(), "%I:%M");

  constructLine1(currentTime);
  if (! line1.equals(old_line1)) {
    updateDisplay();
    old_line1 = line1;
  }

}
