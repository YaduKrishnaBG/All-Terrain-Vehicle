#include <SoftwareSerial.h>
#include <DHT.h>
#include <DHT_U.h>

#define echopin  40 // echo pin
#define trigpin 44 // Trigger pin
#define DHTPIN 2     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
#define dht_pin 2 // Pin sensor is connected to

DHT_Unified dht(DHTPIN, DHTTYPE);
SoftwareSerial BT(22,24);


 int MotorAinput1 = 36;
 int MotorAinput2 = 34;
 int MotorBinput1 = 4;
 int MotorBinput2 = 5;
 int MotorCinput1 = 6;
 int MotorCinput2 = 7;
 int MotorDinput1 = 8;
 int MotorDinput2 = 9;
 int MotorEinput1 = 10;
 int MotorEinput2 = 11;
 int MotorFinput1 = 12;
 int MotorFinput2 = 14;

 int state;
 int Speed = 130; 

 uint32_t delayMS; // humidity sensor.

 int temp;
 int hum;

 int timer = 0;

 int distanceFwd;
 long duration;

 int chk = 0;
 int set = 10;

// Functions
void backward(){
    digitalWrite(36,HIGH);digitalWrite(34,LOW);digitalWrite(4,LOW);digitalWrite(5,HIGH);digitalWrite(6,HIGH);digitalWrite(7,LOW);digitalWrite(8,LOW);digitalWrite(9,HIGH);digitalWrite(10,LOW);digitalWrite(11,HIGH);digitalWrite(12,LOW);digitalWrite(14,HIGH); }

void forward(){
    digitalWrite(36,LOW);digitalWrite(34,HIGH); digitalWrite(4,HIGH);digitalWrite(5,LOW); digitalWrite(6,LOW);digitalWrite(7,HIGH);digitalWrite(8,HIGH);digitalWrite(9,LOW);digitalWrite(10,HIGH);digitalWrite(11,LOW);digitalWrite(12,HIGH);digitalWrite(14,LOW);}

void turnRight(){
    digitalWrite(36,LOW);digitalWrite(34,HIGH);digitalWrite(6,LOW);digitalWrite(7,HIGH);digitalWrite(10,HIGH); digitalWrite(11,LOW);digitalWrite(4,LOW);digitalWrite(5,HIGH);digitalWrite(8,LOW);digitalWrite(9,HIGH);digitalWrite(12,LOW);digitalWrite(14,HIGH);}
    
void turnLeft(){
    digitalWrite(36,HIGH);digitalWrite(34,LOW); digitalWrite(6,HIGH);digitalWrite(7,LOW); digitalWrite(10,LOW);digitalWrite(11,HIGH); digitalWrite(4,HIGH);digitalWrite(5,LOW);digitalWrite(8,HIGH);digitalWrite(9,LOW);digitalWrite(12,HIGH);digitalWrite(14,LOW);}

void Stop(){
    digitalWrite(36,LOW); digitalWrite(34,LOW); digitalWrite(4,LOW); digitalWrite(5,LOW); digitalWrite(6,LOW); digitalWrite(7,LOW);digitalWrite(8,LOW);digitalWrite(9,LOW);digitalWrite(10,LOW);digitalWrite(11,LOW); digitalWrite(12,LOW); digitalWrite(14,LOW);}
    
long data()
{  digitalWrite(trigpin,LOW); delayMicroseconds(2);  digitalWrite(trigpin,HIGH);  delayMicroseconds(10);  duration=pulseIn (echopin,HIGH);
  return duration / 29 / 2; }

void setup() {
// ultrasonic
  
    pinMode (trigpin, OUTPUT);
    pinMode (echopin, INPUT );

// Temp and humidity

dht.begin();
  // Print temperature sensor details. // CAN PUT IT IN LOOP() ??
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
 
  // Set delay between sensor readings based on sensor details.
  //delayMS = sensor.min_delay / 1000;


// Motor
  pinMode(MotorAinput1, OUTPUT);
  pinMode(MotorAinput2, OUTPUT);
  pinMode(MotorBinput1, OUTPUT);
  pinMode(MotorBinput2, OUTPUT);
  pinMode(MotorCinput1, OUTPUT);
  pinMode(MotorCinput2, OUTPUT);
  pinMode(MotorDinput1, OUTPUT);
  pinMode(MotorDinput2, OUTPUT);
  pinMode(MotorEinput1, OUTPUT);
  pinMode(MotorEinput2, OUTPUT);
  pinMode(MotorFinput1, OUTPUT);
  pinMode(MotorFinput2, OUTPUT);
   
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  BT.begin(9600); // Setting the baud rate of Software Serial Library  
  //delay(500); 
}

byte rx_byte = 0;
char cmmd;

void loop() {
    //if some date is sent, reads it and saves in state
    if (Serial.available()) {
    cmmd = Serial.read();
    //Serial.print("You sent Arduino: ");
    Serial.println(cmmd);
               
   
    distanceFwd = data();  
    Serial.println(distanceFwd);     
    
   if((distanceFwd<set) && (chk==1)){chk = 2; Stop();}
   if(distanceFwd>set){chk = 0;}
    
   // if the state is '1' the DC motor will go forward initial
   if ((cmmd == '1') && (chk==0)){chk = 1; forward();Serial.println("Go Forward!");}

   // if the state is '2' the motor will Reverse initial
   else if (cmmd == '4'){backward();Serial.println("Reverse!");}
    
   // if the state is '3' the motor will turn left initial
   else if (cmmd == '2'){turnLeft();Serial.println("Turn LEFT");}
    
   // if the state is '4' the motor will turn right initial
   else if (cmmd == '3'){turnRight();Serial.println("Turn RIGHT");}
    
   // if the state is '5' the motor will Stop initial
   else if (cmmd == '0') {Stop();Serial.println("STOP!");}  
}


    
if(BT.available() >= 0){  /// WHY S THIS REQUIRED ??
      //Serial.println("Connected"); 
      state = BT.read(); 
      //Serial.println(state);
      if(state > 10) { Speed = state;}    
         
       timer = timer+1;
//BT.print("timer: ");
//BT.println(timer);

if(timer==200){ 
if(distanceFwd>200){distanceFwd=200;} 
 BT.print("A");
 BT.print(";");
 BT.print(distanceFwd); //send distance to MIT App
 BT.println(";");

}
 //delay(5);
if(timer>300){
 sensors_event_t event;
  
 dht.temperature().getEvent(&event);
 temp = event.temperature;
   
 //Serial.println(temp);
  
 dht.humidity().getEvent(&event);
 hum = event.relative_humidity;
 
   
 //Serial.println(hum);

 BT.print("B");
 BT.print(";");
 BT.print(temp); //send distance to MIT App
 BT.print(";");
 BT.print(hum); //send distance to MIT App
 BT.println(";"); 
 timer = 0;
}
 
//delay(1); 

}
}
