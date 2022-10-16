#include <Otto.h>
Otto Otto;

#define LeftLeg 15
#define RightLeg 2
#define LeftFoot 13 
#define RightFoot 0 
#define Buzzer  5 
#define Trigger 12 // ultrasonic sensor trigger pin
#define Echo 14 // ultrasonic sensor echo pin

long distance;

long ultrasound() 
{
   long duration, distance;
   digitalWrite(Trigger,LOW);
   delayMicroseconds(2);
   digitalWrite(Trigger, HIGH);
   delayMicroseconds(10);
   digitalWrite(Trigger, LOW);
   duration = pulseIn(Echo, HIGH);
   distance = duration/58;
   return distance;
}

void setup() 
{
  Serial.begin(9600);
  Otto.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer); //Set the servo pins and Buzzer pin
  pinMode(Trigger, OUTPUT); 
  pinMode(Echo, INPUT);
  Otto.home();
}

void loop() 
{
  Serial.println(ultrasound());
  distance = ultrasound();

  if(distance >=15)
  {
   Otto.walk(2,700,1); 
  }
  else
  {
    Otto.walk(2,700,-1); 
  }
}
