
//4 sensors
#include <Servo.h>
Servo servoLeft;
Servo servoRight;

int Left = 1530;
int Right = 1470;

char one,two,three,four;
char route[8]={2,1,0,1,0,1,2,9};//0:Left;1:Right;2:Straight;9:Stop
char count = 0;
void setup() {
Serial.begin(9600);
servoLeft.attach(13);
servoRight.attach(12);
goStraight();
}

void loop() {
  one = Get_1();two = Get_2();three = Get_3();four = Get_4();
  if(one||four){
    goStraight();
    delay(50);
    one = Get_1();four = Get_4();
    if(one||four){
      if(route[count] == 9){
        Stop();
        while(true){delay(500);}
        }
        goStraight();delay(450);  //550
        if(route[count] == 1){
          turnRight();delay(500);
          while(Get_3()==0){;}
          Stop();delay(500);turnRight();
          while(Get_3()==1){;}
        }else if(route[count] == 0){
        turnLeft();delay(500);
        while(Get_2()==0){;}
        Stop();delay(500);turnLeft();
        while(Get_2()==1){;}
        }}else if(route[count] == 2){
        goStraight();delay(300);
        }
        ++count;
        Stop();
        delay(100);
    }else if(two){
      goLeft();
    }else if(three){
      goRight();
    }else{
      goStraight();
      }
}


void Stop(){
  servoLeft.writeMicroseconds(1500); 
  servoRight.writeMicroseconds(1500);
  }
void turnLeft(){
  servoLeft.writeMicroseconds(1470); 
  servoRight.writeMicroseconds(1470);
  }

void turnRight(){
  servoLeft.writeMicroseconds(1550); //1530
  servoRight.writeMicroseconds(1550);//1530
  }

void goStraight(){
  servoLeft.writeMicroseconds(1600); //1530
  servoRight.writeMicroseconds(1490);//1470
}

void goLeft(){
  servoLeft.writeMicroseconds(1490);//1490
  servoRight.writeMicroseconds(1400);//1450
}

void goRight(){
  servoLeft.writeMicroseconds(1600); //1550
  servoRight.writeMicroseconds(1510);//1520
}


char Get_1(){
  float temp = float(analogRead(A0)) * 5.0 / 1024.0;
  if(temp<3.0)
  return 1;
  else
  return 0;
}
char Get_2(){
  float temp = float(analogRead(A1)) * 5.0 / 1024.0;
  if(temp<3.6)
  return 1;
  else
  return 0;
}
char Get_3(){
  float temp = float(analogRead(A2)) * 5.0 / 1024.0;
  if(temp<3.6)
  return 1;
  else
  return 0;
}
char Get_4(){
  float temp = float(analogRead(A5)) * 5.0 / 1024.0;
  if(temp<3.6)
  return 1;
  else
  return 0;
}
