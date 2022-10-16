#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Otto.h>
Otto Otto;

char auth[] = "IhdRVwqfke9IC2F8AW3UcYrR8bY8wENn";

char ssid[] = "robotto";
char pass[] = "robotto@123";

#define LeftLeg 15
#define RightLeg 2
#define LeftFoot 13 
#define RightFoot 0 
#define Buzzer  5 
#define Trigger 12 // ultrasonic sensor trigger pin
#define Echo 14 // ultrasonic sensor echo pin

long distance;
int forward,backward;

BLYNK_WRITE(V0)
{
  forward = param.asInt();
}

BLYNK_WRITE(V1)
{
 backward = param.asInt();
}



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

  Blynk.begin(auth, ssid, pass,"blynk.cloud", 80);
  
  Otto.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer); //Set the servo pins and Buzzer pin
  
  pinMode(Trigger, OUTPUT); 
  pinMode(Echo, INPUT);
  Otto.home();
}

void loop() 
{
  Blynk.run();
  
  Serial.println(ultrasound());
  distance = ultrasound();

  Blynk.virtualWrite(V2,distance);

  if(forward == 1)
  {
    Otto.walk(2,700,1);
  }
  
  if(backward == 1)
  {
    Otto.walk(2,700,-1);
  }
}
