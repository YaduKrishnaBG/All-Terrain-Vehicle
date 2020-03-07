int x=0;
void setup()
{
  
  const int MotorAinput1 = 36;
  const int MotorAinput2 = 34;
  const int MotorBinput1 = 4;
  const int MotorBinput2 = 5;
  const int MotorCinput1 = 6;
  const int MotorCinput2 = 7;
  const int MotorDinput1 = 8;
  const int MotorDinput2 = 9;
  const int MotorEinput1 = 10;
  const int MotorEinput2 = 11;
  const int MotorFinput1 = 12;
  const int MotorFinput2 = 14;
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
  Serial.begin(9600);

}

void loop(){

  if(Serial.available() > 0) // Checks whether data is comming from the serial port
  x = Serial.read(); // Reads the data from the serial port
  Serial.println(x);
  switch(x){             
  //while(true) 
    delay(150);
    case 50:                   //REVERSE
      Serial.println("Moving BACKWARD");
      Serial.println(x);
      digitalWrite(36,HIGH);
      digitalWrite(34,LOW);       //A
      digitalWrite(4,LOW);
      digitalWrite(5,HIGH);       //B
      digitalWrite(6,HIGH);
      digitalWrite(7,LOW);    //C
     digitalWrite(8,LOW);
     digitalWrite(9,HIGH);   //D
     digitalWrite(10,LOW);
      digitalWrite(11,HIGH);   //E
      digitalWrite(12,LOW);
      digitalWrite(14,HIGH);   //F
      delay(50);
      x = -1;
      break;
    case 49:                     //FORWARD
      Serial.println("Moving FORWARD");
      Serial.println(x);
      digitalWrite(36,LOW);      
      digitalWrite(34,HIGH);      //A
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);     //B
      digitalWrite(6,LOW);
      digitalWrite(7,HIGH);     //C
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);     //D 
      digitalWrite(10,HIGH);
      digitalWrite(11,LOW);     //E
      digitalWrite(12,HIGH);
      digitalWrite(14,LOW);     //F
      delay(50);
      x = -1;
      break;    
    case 51:                     //Turn RIGHT
      Serial.println("Twist Right");
      Serial.println(x);
      digitalWrite(36,LOW);
      digitalWrite(34,HIGH);       //A
      digitalWrite(6,LOW);
      digitalWrite(7,HIGH);    //C
      digitalWrite(10,HIGH);
      digitalWrite(11,LOW);   //E
      digitalWrite(4,LOW);
      digitalWrite(5,HIGH);     //B
      digitalWrite(8,LOW);
      digitalWrite(9,HIGH);     //D
      digitalWrite(12,LOW);
      digitalWrite(14,HIGH);     //F 
      delay(50);
      x = -1;
      break;
    case 52:                      //Rotate LEFT
     Serial.println("Twist Left");
      Serial.println(x);
      digitalWrite(36,HIGH);      
      digitalWrite(34,LOW);      //A
      digitalWrite(6,HIGH);
      digitalWrite(7,LOW);     //C
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);     //E
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);       //B
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);   //D
      digitalWrite(12,HIGH);
      digitalWrite(14,LOW);   //F
      delay(50);
      x = -1;
      break;
    default:                     //STOP
      Serial.println("Stop");
      Serial.println(x);
      digitalWrite(36,LOW);
      digitalWrite(34,LOW);
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
      digitalWrite(12,LOW);
      digitalWrite(14,LOW);
      delay(50);
      x = -1;
      break;
      //x++;
  }   
}
