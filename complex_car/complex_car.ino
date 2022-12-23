#include <NewPing.h>
#include <Servo.h> 
#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200
boolean goesForward=false; 
int distance = 100;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
Servo myservo;   
 // create servo object to control a servo
// twelve servo objects can be created on most boards
int automate = 0;
String inputs;
void setup() {
   myservo.attach(9);  
  myservo.write(90); 
  delay(2000);
  distance = sonar.ping_cm();
  delay(100);
  
  
  Serial.begin(9600);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
 
}

void loop() {
  while(Serial.available()) 
{
delay(10); //Delay to make it stable
char c = Serial.read();
if (c == '#'){
break; 
}
inputs += c; 
}

  

  if (inputs.length() >0)
{
Serial.println(inputs);
if(inputs == "2")
{ digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);}
  
 if(inputs == "1")
{ digitalWrite(11,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(13,HIGH);
  digitalWrite(12,LOW);}
  if(inputs == "3")
{ digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);}
 if(inputs == "4" )
{digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);}
  if(inputs == "5")
{digitalWrite(11,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(13,LOW);
  digitalWrite(12,HIGH);}

  if(inputs =="6")
  {automate =0;
  while(automate == 0)
  {   int distanceR = 0;
 int distanceL =  0;
 delay(40);
 distance = sonar.ping_cm();
 if(distance<=20)
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  distanceR = lookRight();
  Serial.print("DistanceR:");
  Serial.println(distanceR);
  delay(200);
  distanceL = lookLeft();
  if(distanceL == 0)
  {distanceL = 41;}
  if(distanceR == 0)
  {distanceR = 40;}
  Serial.print("DistanceL:");
  Serial.println(distanceL);
  delay(200);

  if(distanceR>=distanceL)
  {Serial.print("R");
    digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);
  delay(200);
    moveStop();
  }
  else if(distanceR<distanceL)
  {Serial.print("L");
    digitalWrite(11,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(13,LOW);
  digitalWrite(12,HIGH);
  delay(200);
    moveStop();
  }
 }else
 {
  moveForward();
 }
 
 inputs="";

  while(Serial.available()) 
{
delay(10);
  char c = Serial.read(); 
if (c == '#'){
break; 
}
inputs += c;
}

if (inputs.length() >0)
{
Serial.println(inputs);
if (inputs=="6")
{automate=1;}
inputs="";}
  
  delay(500);}
}

    
    
    
    
    inputs="";
  }
 
  

  
  }
  
  
int lookRight()
{
    myservo.write(0); 
    delay(500);
    int distance = sonar.ping_cm();
    delay(100);
    myservo.write(90); 
    return distance;
}

int lookLeft()
{
    myservo.write(180); 
    delay(500);
    int distance = sonar.ping_cm();
    delay(100);
    myservo.write(90); 
    return distance;
}

void moveStop() {
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  } 
  void moveBackward() {

 if(!goesForward)
  {
   digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW); }}

  void moveForward() {
    goesForward=false;
    

  digitalWrite(11,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(13,HIGH);
  digitalWrite(12,LOW);
  }

  void turnRight() {
 digitalWrite(11,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(13,LOW);
  digitalWrite(12,HIGH);
} 
void turnLeft() {
  digitalWrite(11,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(13,LOW);
  digitalWrite(12,HIGH);
}
