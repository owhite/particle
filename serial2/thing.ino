int LEDPin = D2;
int SwitchPin1 = D0;
int SwitchPin2 = D1;

int brightness = 0;
int fadeAmount = 5;

String old_string;
String time_string;

void setup() {
  Serial1.begin(9600);
  delay(100);
  Serial1.write(12);                 // Clear             
  delay(100);
  Serial1.write(17);                 // Turn backlight on
  delay(100);                        // Required delay

  old_string.reserve(8);
  time_string.reserve(8);
  Time.zone(-5);
  old_string = Time.format(Time.now(), "%I:%M");
  Serial1.print("     ");
  Serial1.print(old_string);
  Serial1.write(212);                // Quarter note
  Serial1.write(220);                // A tone
  delay(300);                       // Wait 3 seconds

  pinMode(LEDPin, OUTPUT);
  pinMode(SwitchPin1, INPUT);
  pinMode(SwitchPin2, INPUT);

}

void loop() {
  int pb1; 
  int pb2; 

  Serial1.write(12);                 // Clear             
  Serial1.print(" xxx ");

  delay(200);

}
