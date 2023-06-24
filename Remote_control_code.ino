#include <QTRSensors.h>
#include <SoftwareSerial.h>

#define SAFETY_DISTANCE 15

//pins from ultrasonic sensor (front)
int echoPin = A3; // transmitter 
int trigPin = A4; // receiver 
long duration;
long cm;

//pins from infra-red sensor (back)
int IRpin = A5;
int cmIR;
float volts;

/*LEFT MOTOR PARAMETERS*/
int left_motor_1 = 9;
int left_motor_2 = 10;
int motor_power_left = 5;

/*RIGHT MOTOR PARAMETERS*/
int right_motor_1 = 11;
int right_motor_2 = 12;
int motor_power_right = 6;

char aux ;
char command;

void setup()
{
  
    // put your setup code here, to run once:
    Serial.begin(9600);
    //set the pins for ultrasonic sensor 
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    //set the pins of the left motor as outputs in order
    //to set below the speed and the direction of the motor
    pinMode(motor_power_left, OUTPUT);
    pinMode(left_motor_1, OUTPUT);
    pinMode(left_motor_2, OUTPUT);
      
      
    //set the pins of the right motor as outputs in order
    //to set below the speed and the direction of the motor
    pinMode(motor_power_right, OUTPUT);
    pinMode(right_motor_1, OUTPUT);
    pinMode(right_motor_2, OUTPUT);

    //default value
    aux = '-'; 
}



void loop()
{
    //get the distance from sensors
    getDistanceFromSensors();
    
    if(Serial.available() > 0)
    {
     
    //we use "command" variable to read incoming serial data
    //which are sent when we push a button in the android app.
    
    command = Serial.read();
    
    if(!isDigit(command))
    {
      
      aux = command ;
    
    }
    
    if(aux == '-')   //case when there is no speed selected
      {
        
        // no speed is selected from the app so the car won't move 
        analogWrite(motor_power_right,0);
        analogWrite(motor_power_left, 0);
        
      }
      else if(aux == 's' )   //case when speed "slow" is selected
      {
        
        //the car will move with half of speed 
        analogWrite(motor_power_right,160);
        analogWrite(motor_power_left, 130);
      
      }
      else     //case when speed "fast" is selected 
      {
      
        //the car will move with full speed
        analogWrite(motor_power_right,245);
        analogWrite(motor_power_left, 190);
        
       }
        // these cases will take place depending on which
        //button the user will push in the android app 
    }
    
    switch(command) 
    {
      
      case '1': //forward
      
      if(cm < SAFETY_DISTANCE)
      {
        
       Stop();
      
      }
      else 
      {
        
       Forward();
      
      }
         
      break;
      
//-----------------------------------------------------------------
      case '2': //backwards
      if(cmIR < SAFETY_DISTANCE)
      {
       
       Stop();
      
      }
      else
      {
        
       Backwards();
      
      }
      break;
//-----------------------------------------------------------------
      case '3': //left
      
       Left();
       
      break;
//-----------------------------------------------------------------
      case '4'://right
      
      Right();
      
      break;
//-----------------------------------------------------------------
      default:
      
      Stop();
       
//right_motor_1 = high -> motorul se roteste in fata
//right_motor_2 = high -> motorul se roteste in spate 
//left_motor_1 = high -> motorul se roteste in fata
//left_motor_2 = high -> motorul se roteste in spate  
    } 
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

    //Infra-Red sensor (back)
    // sharp sensor
  
    volts = analogRead(IRpin)*0.0048828125;   
    cmIR = 26*pow(volts, -1.10);
}

void Forward()
{
      //right motor
     digitalWrite(right_motor_1, HIGH);
     digitalWrite(right_motor_2, LOW);
       
     //left motor       
     digitalWrite(left_motor_1, HIGH);
     digitalWrite(left_motor_2, LOW);

     
}

void Backwards()
{
     //right motor
     digitalWrite(right_motor_1, LOW);
     digitalWrite(right_motor_2, HIGH);
       
     //left motor
     digitalWrite(left_motor_1, LOW);
     digitalWrite(left_motor_2, HIGH);

     
}

void Right()
{
     //right motor
     digitalWrite(right_motor_1, LOW);
     digitalWrite(right_motor_2, HIGH);

     //left motor
     digitalWrite(left_motor_1, HIGH);
     digitalWrite(left_motor_2, LOW);
}

void Left()
{
     //right motor
     digitalWrite(right_motor_1, HIGH);
     digitalWrite(right_motor_2, LOW);
       

     //left motor
     digitalWrite(left_motor_1, LOW);
     digitalWrite(left_motor_2, HIGH);
}

void Stop()
{
     //right motor
     digitalWrite(right_motor_1, LOW);
     digitalWrite(right_motor_2, LOW);
        
     //left motor
     digitalWrite(left_motor_1, LOW);
     digitalWrite(left_motor_2, LOW);
}

 
