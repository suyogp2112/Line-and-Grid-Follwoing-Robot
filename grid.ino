/*
LINE FOLLOWER using 3 CNY70 sensors
Includes following things
Parallex Robot kit, Arduino.
3 Sensors, 3 - 10K & 220 omhs resistors

Coded By SUYOG PATIL & Praveen TC
SRH HEIDELBERG GERMANY
*/


#include <Servo.h>
String string;
bool boolState;
Servo servoLeft; // Declare left and right servos
Servo servoRight; 
int LeftLed=11;  // using Digital pin 11 for indication of left sensor
int MiddleLed=8; // using Digital pin 8 for indication of Middle sensor
int RightLed=3; // using Digital pin 3 for indication of Right sensor
int k = 0;
int flag = 0;
void confusion(int i);

void setup() // Built-in initialization block
{
Serial.begin(9600); //Enable serial communication
servoLeft.attach(13); // Attach left signal to pin 13
servoRight.attach(12); // Attach right signal to pin 12
//servoLeft.writeMicroseconds(1500); // limit speed (Full speed forward use 1700)
//servoRight.writeMicroseconds(1450); //Full speed forward use 1300
pinMode(LeftLed,OUTPUT);  //Use pin as Outputs
pinMode(RightLed,OUTPUT);
pinMode(MiddleLed,OUTPUT);
}

void loop() // Main loop auto-repeats
{
int a[6] = {1,0,2,0,1,0};

Serial.print("A3 = "); // Display "A3 = "
Serial.print(Left(A3)); // Display measured A3 volts
Serial.println("Left"); // Display " Voltage of Left sensor" & add newline

Serial.print("A4 = "); // Display "A4 = "
Serial.print(Middle(A4)); // Display measured A4 volts
Serial.println("Middle"); // Display " Voltage of Middle sensor" & add newline

Serial.print("A5 = "); // Display "A5 = "
Serial.print(Right(A5)); // Display measured A5 volts
Serial.println("Right"); // Display " Voltage of Right sensor" & add newline
//delay(1000);  // only add if u want to check voltage

//For Left Sensor A3
if (Left(A3) < 3.5) //Left Led On/Off
{
digitalWrite(LeftLed,LOW); //Off if black
}
else
  {
    digitalWrite(LeftLed,HIGH); //On if White
  }

//For middle Sensor A4
if(Middle(A4) > 3.5) // Middle Led On/Off
{
digitalWrite(MiddleLed,LOW); // off if white
    }
else
  {
    digitalWrite(MiddleLed,HIGH); // On if black
  }

  //For Right Sensor A5
if(Right(A5) < 3.5) // If Right sensor detected then turn Right
{
digitalWrite(RightLed,LOW); // Off if Black
}
else
  {
    digitalWrite(RightLed,HIGH); // On if white
  }

//GRID

if(Left(A3) < 3.5 && Right(A5) < 3.5 && Middle(A4) < 3.5){  //If all 3 sensors detected black
  if(flag == 0){
confusion(a[k]);
Serial.print("Command = "); 
Serial.print(a[k] );
k++;
flag =1;}
}

if(Middle(A4) < 3.5 && Right(A5) < 3.5 && Left(A3) > 3.5) //Turn Right
{
right();
}

if(Middle(A4) < 3.5 && Left(A3) < 3.5 && Right(A5) > 3.5) //Turn Left
{
left();
    
}
 if(Left(A3) > 3.5 && Right(A5) > 3.5 && Middle(A4) < 3.5) //Move Forward
{
forward();
    if (flag == 1)
      flag = 0;
}
}

void confusion(int i){  //Program for Grid
if((Left(A3) < 3.5 || Right(A5) < 3.5) && Middle(A4) < 3.5 && (i == 0))
{
right90();
}
if((Left(A3) < 3.5 || Right(A5) < 3.5) && Middle(A4) < 3.5 && (i == 1))
{
left90();
}
if((Left(A3) < 3.5 || Right(A5) < 3.5) && Middle(A4) < 3.5 && (i == 2))
{
forward();
}
if((Left(A3) < 3.5 || Right(A5) < 3.5) && Middle(A4) < 3.5 && (i == 3))
{
stop1();
}
}

void left()
{
  servoLeft.writeMicroseconds(1450); 
    servoRight.writeMicroseconds(1400);
}

void right()
{
  servoLeft.writeMicroseconds(1600); 
    servoRight.writeMicroseconds(1550);
}

void forward()
{
  servoLeft.writeMicroseconds(1550); // Full speed forward 1700
  servoRight.writeMicroseconds(1450); //1300
}

void left90()
{
  servoLeft.writeMicroseconds(1300); 
    servoRight.writeMicroseconds(1300);
}

void right90()
{
  
  servoLeft.writeMicroseconds(1700); 
    servoRight.writeMicroseconds(1700);
}

void stop1()
{
servoLeft.detach(); // Stop servo signals
servoRight.detach();
}

float Left(int A3) // Measures volts at adPin
{ // Returns floating point voltage
return float(analogRead(A3)) * 5.0 / 1024.0;
}

float Middle(int A4) // Measures volts at adPin
{ // Returns floating point voltage
return float(analogRead(A4)) * 5.0 / 1024.0;
}

float Right(int A5) // Measures volts at adPin
{ // Returns floating point voltage
return float(analogRead(A5)) * 5.0 / 1024.0;
}