
#include <SoftwareSerial.h>

#include <QTRSensors.h>

#define NUM_SENSORS 3


#define MAX_SPEED 160
//constants in PID alg
#define K_P 0.2
#define K_D 0.7
#define K_I 0.0

//distance at which we want to stop
#define SAFETY_DISTANCE 17 


//set the pins for each sensor
QTRSensorsRC qtrrc((unsigned char[]) {A0, A1, A2}, NUM_SENSORS);
//array in which we put data from sensors
unsigned int sensorValues[NUM_SENSORS];
int lastError = 0;
int integral = 0;

/*LEFT MOTOR PARAMETERS*/
int left_motor_1 = 9;
int left_motor_2 = 10;
int LEFT_MOTOR_PIN = 5;

/*RIGHT MOTOR PARAMETERS*/

int right_motor_1 = 11;
int right_motor_2 = 12;
int RIGHT_MOTOR_PIN = 6;


//pins from ultrasonic sensor (front)
int echoPin = A3; // transmitter 
int trigPin = A4; // receiver 
long duration;
long cm;
long counter;

void setup()
{
  Serial.begin(9600);
  
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  int i;
  for (i = 0; i < 250; i++)  // make the calibration take about 5 seconds
  {
    qtrrc.calibrate();
    delay(20);
  }

}

void loop()
{
  getDistanceFromSensors();
  
  int position = qtrrc.readLine(sensorValues);
  
  int error = position - 1000;
  int derivative = error - lastError;
  int pid = (K_P * error) + (K_D * derivative) + (K_I * integral);
  integral += error;
  lastError = error;

  Serial.println(cm);

  int leftSpeed = MAX_SPEED - pid;
  int rightSpeed = MAX_SPEED + pid;

  if(leftSpeed > 255 )
  {
    leftSpeed = 150;
  }

  if(rightSpeed > 255 )
  {
    rightSpeed = 150;
  }

  if(leftSpeed == 0 )
  {
    leftSpeed = 140;
  }

  if(rightSpeed == 0 )
  {
    rightSpeed = 140;
  }
  // adjust the motor speeds based on the pid output
  if (leftSpeed < 0)
  {
    digitalWrite(left_motor_1, LOW);
    digitalWrite(left_motor_2, HIGH);
    leftSpeed = 0;
  } 
  else 
  {
    digitalWrite(left_motor_1, HIGH);
    digitalWrite(left_motor_2, LOW);
  }

  if (rightSpeed < 0) {
    
    digitalWrite(right_motor_1, LOW);
    digitalWrite(right_motor_2, HIGH);
    rightSpeed = 0;
  }
  else
  {
    digitalWrite(right_motor_1, HIGH);
    digitalWrite(right_motor_2, LOW);
  }

  //if we have an obstacle the car wiil stop
   if(cm <= SAFETY_DISTANCE)
  {
    digitalWrite(right_motor_1, LOW);
    digitalWrite(right_motor_2, LOW);
    digitalWrite(left_motor_1, LOW);
    digitalWrite(left_motor_2, LOW);
    analogWrite(LEFT_MOTOR_PIN, 0);
   analogWrite(RIGHT_MOTOR_PIN, 0);
  }
  //the car is outside of the range of the line 
  if((sensorValues[0] >= 500 && sensorValues[0] <=1000) && (sensorValues[1] >=500 && sensorValues[1] <= 1000) && (sensorValues[2] >= 500 && sensorValues[0] <=1000))
  {
    digitalWrite(right_motor_1, LOW);
    digitalWrite(right_motor_2, LOW);
    digitalWrite(left_motor_1, LOW);
    digitalWrite(left_motor_2, LOW);
    analogWrite(LEFT_MOTOR_PIN, 0);
    analogWrite(RIGHT_MOTOR_PIN, 0);
  }
   analogWrite(LEFT_MOTOR_PIN, leftSpeed);
   analogWrite(RIGHT_MOTOR_PIN, rightSpeed);
}

  void getDistanceFromSensors()
{
    //ultrasonic sensor (front)
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    cm = (duration/2) / 29.1;
 
}
