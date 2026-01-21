#include <AFMotor.h>   //Download and Install AFMotor.h Library
#include <Servo.h>
AF_DCMotor motor2(2,MOTOR12_64KHZ); // left side wheels       
AF_DCMotor motor1(1,MOTOR12_64KHZ); // right side wheels       
AF_DCMotor motor4(4,MOTOR12_64KHZ); // flooor cleaning motor
Servo servo;
int angle = 0;      // Set minimum angle 5 degree 
int servoPin = 10;   // attach servo motor to digital pin 10
int state1;
int Speed = 130; 
void setup() 
{
  Serial.begin(9600);     // set baud rate 

  motor2.setSpeed(130);   //Set Motor Speed
  motor1.setSpeed(130);   //Set Motor Speed
  motor4.setSpeed(130);   //Set Motor Speed
  servo.attach(servoPin);  // set servo motor pin 
  servo.write(angle);     // input angle for servo
  delay(500);
}

void loop() 
{
    if(Serial.available() > 0)  
    {  //if some date is sent, reads it and saves in state     
    state1 = Serial.read();    
    Serial.println(state1);  
    if(state1 > 10){Speed = state1;} 
    }


        if(state1 == 11){ forword(); delay(1000); }  // if the state is '11' the DC motor will go forward
        else if(state1 == 22){backword();delay(1000);}  // if the state is '22' the motor will Reverse
        else if(state1 == 33){turnLeft();delay(1000);}  // if the state is '33' the motor will turn left
        else if(state1 == 44){turnRight();delay(1000);} // if the state is '44' the motor will turn right
        else if(state1 == 55){Stop();  }     // if the state is '55' the motor will Stop
        else if(state1 == 66){turnLeft();delay(1000); }   //if the state is '66' the motor turn right when command given from voice 
        else if(state1 == 77){turnRight();delay(1000);}  //if the state is '77' the motor turn right when command given from voice 
        else if (state1 == 45){servo.write(45); delay(1000);} //Servo motor down
        else if (state1 == 46){servo.write(0); delay(1000); }//servo motor up
        else if (state1 == 47){motor4.run(FORWARD); delay(1000);}// floor cleaner motor on
        else if (state1 == 48){motor4.run(RELEASE);delay(1000); }//floor cleaner motor off
      
}

void forword() 
{
    motor2.run(FORWARD); // move in forward direction
    motor1.run(FORWARD); 
    motor4.run(FORWARD);
}

void backword()
{
    motor2.run(BACKWARD); // move in backward direction 
    motor1.run(BACKWARD); 
    motor4.run(FORWARD); 
}

void turnRight()
{
    motor2.run(FORWARD); // move in right direction
   // motor1.run(BACKWARD); 
    motor4.run(FORWARD);
}

void turnLeft()
{
    //motor2.run(BACKWARD); // move in left direction 
    motor1.run(FORWARD); 
    motor4.run(FORWARD); 
}

void Stop()
{
    motor2.run(RELEASE); // stop 
    motor1.run(RELEASE);
    motor4.run(RELEASE);
}#define enA 9
#define in1 4
#define in2 5
#define enB 10
#define in3 6
#define in4 7

int xAxis, yAxis;
int  x = 0;
int  y = 0;

int motorSpeedA = 0;
int motorSpeedB = 0;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(38400); // Default communication rate of the Bluetooth module
}

void loop() {
  // Default value - no movement when the Joystick stays in the center
  xAxis = 510;
  yAxis = 510;

  // Read the incoming data from the Smartphone Android App
  while (Serial.available() >= 2) {
    x = Serial.read();
    delay(10);
    y = Serial.read();
  }
  delay(10);
  
  // Makes sure we receive corrent values
  if (x > 60 & x < 220) {
    xAxis = map(x, 220, 60, 1023, 0); // Convert the smartphone X and Y values to 0 - 1023 range, suitable motor for the motor control code below
  }
  if (y > 60 & y < 220) {
    yAxis = map(y, 220, 60, 0, 1023);
  }

  // Y-axis used for forward and backward control
  if (yAxis < 470) {
    // Set Motor A backward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // Set Motor B backward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 470, 0, 0, 255);
    motorSpeedB = map(yAxis, 470, 0, 0, 255);
  }
  else if (yAxis > 550) {
    // Set Motor A forward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // Set Motor B forward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 550, 1023, 0, 255);
    motorSpeedB = map(yAxis, 550, 1023, 0, 255);
  }
  // If joystick stays in middle the motors are not moving
  else {
    motorSpeedA = 0;
    motorSpeedB = 0;
  }

  // X-axis used for left and right control
  if (xAxis < 470) {
    // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
    int xMapped = map(xAxis, 470, 0, 0, 255);
    // Move to left - decrease left motor speed, increase right motor speed
    motorSpeedA = motorSpeedA - xMapped;
    motorSpeedB = motorSpeedB + xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA < 0) {
      motorSpeedA = 0;
    }
    if (motorSpeedB > 255) {
      motorSpeedB = 255;
    }
  }
  if (xAxis > 550) {
    // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
    int xMapped = map(xAxis, 550, 1023, 0, 255);
    // Move right - decrease right motor speed, increase left motor speed
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB - xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA > 255) {
      motorSpeedA = 255;
    }
    if (motorSpeedB < 0) {
      motorSpeedB = 0;
    }
  }
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  if (motorSpeedA < 70) {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 70) {
    motorSpeedB = 0;
  }
  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
}