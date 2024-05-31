#include <Servo.h>

//ultrasonic sensor pins
const int trigpin = 7;
const int echopin = 8;

// establish variables for duration of the ping, and the distance result
// in inches and centimeters:
long duration, inches, cm;

//Motor
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int servoPin = 9;
int potPin = A0;

void setup() {

  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object

  //UsS
  //a more faster response between the sensor and the arduino
  Serial.begin(9600);

  //connecting the trig and echo pins of the sensor to give input and output
  //used to measure the ditance to an object
  //trigPin is used to send out short utrasonic waves
  //while the echo is used to recieve the reflected ultrasonic waves
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
}

void loop() {
  
  //ServoMotor pot control code

  //reads the analog value from the potentiometer pin and maps 
  //the corresponding readings into degrees rad 0-180

  int reading = analogRead(potPin);
  int angle = map(reading, 0, 1023, 0, 180);
  myservo.write(angle);

  //UsS

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
 
  duration = pulseIn(echopin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 343 m/s.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
