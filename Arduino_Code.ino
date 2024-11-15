#include <Servo.h>
#include <SoftwareSerial.h>





SoftwareSerial bluetoothSerial(0, 1);


Servo first;
Servo second;




Servo third;
Servo forth;





const int trigPin2 = 12;   // Ultrasonic sensor 2 trigger pin   first
const int echoPin2 = 13;   // Ultrasonic sensor 2 echo pin


const int trigPin3 = 10;   // Ultrasonic sensor 3 trigger pin   second
const int echoPin3 = 11;   // Ultrasonic sensor 3 echo pin




const int trig4 = 8;   //third ultrasonic
const int echo4 = 9;




const int trig5 = 6;  //forht
const int echo5 =7;




const int trig6 = A1;
const int echo6 =A0;   //fifth


const int trig7 = A3;//sixth
const int echo7 =A2;


const int trig8 = A5;


const int echo8 = A4;




const int trig9 = A7;


const int echo9 = A6;
















const int first_wheel = 22;


const int second_wheel = 24;


const int third_wheel = 26;






const int forth_wheel = 28;






const int backward_firstwheel = 23;
const int backward_secondwheel = 25;
const int backward_thirdwheel = 27;
const int backward_forthwheel = 29;












void setup() {
  bluetoothSerial.begin(115200);
  Serial.begin(115200);
 
  //for the servo motors
  first.attach(3);
  second.attach(2);
  third.attach(4);
  forth.attach(5);
  first.write(0);//keep this fix at 0 for original pos , 180 to grab


  second.write(180);//keep this fix at 0 for original pos , 90 turns left
 
 
  third.write(30);  //30 //keep this fix at 0 for original pos, and 60 for closed distance, further move the forth servo
 


 
  forth.write(180);  //keep this fix at 45 for orginal pos, and 90 when ultrasonic is detected for further bottle






  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);




  pinMode(trig4, OUTPUT);
  pinMode(echo4, INPUT);






  pinMode(trig5, OUTPUT);
  pinMode(echo5, INPUT);






  pinMode(trig6, OUTPUT);
  pinMode(echo6, INPUT);






  pinMode(trig7, OUTPUT);
  pinMode(echo7, INPUT);




  pinMode(trig8, OUTPUT);
  pinMode(echo8, INPUT);




  pinMode(trig9,OUTPUT);
  pinMode(echo9,INPUT);
















  pinMode(first_wheel, OUTPUT);
  pinMode(second_wheel, OUTPUT);
  pinMode(third_wheel, OUTPUT);
  pinMode(forth_wheel, OUTPUT);
  pinMode(backward_firstwheel, OUTPUT);
  pinMode(backward_secondwheel, OUTPUT);
  pinMode(backward_thirdwheel, OUTPUT);
  pinMode(backward_forthwheel, OUTPUT);
  //headServo1.write(0);
  delay(1000);
}


void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    processCommand(command);
  }
}


void processCommand(char command) {
  switch (command) {
    case 'A':
      //headServo1.write(90);
      delay(1000);
      break;
    case 'B':
      moveWheelsForward();
      break;
    case 'K':
      moveWheelsBackward();
      break;
    case 'C':
      stopWheels();
      break;
    case 'D':
      rotateRight();
      break;
    case 'E':
      rotateLeft();
      break;
    case 'F':
      stopRotation();
      break;
    case 'T':
      measureAndSendDistance(trigPin2, echoPin2);
      break;
    case 'G':
      measureAndSendDistance(trigPin3, echoPin3);
      break;




    case 'Y':
      measureAndSendDistance(trig4, echo4);
      break;
    case 'a':
      measureAndSendDistance(trig5, echo5);
      break;


   
    case 'b':
      measureAndSendDistance(trig6, echo6);
      break;
    case 'c':
      measureAndSendDistance(trig7, echo7);
      break;


    case 'd':
      measureAndSendDistance(trig8, echo8);
      break;




     case 'e':
      measureAndSendDistance(trig9, echo9);
      break;

    case 'f':
      backwardLeft();
      break;










    //for the first servos
    case 'M':
      first.write(0);
      delay(1000);
      break;
    case 'N':
      first.write(180);
      delay(1000);


      break;


    case 'O':
      first.write(90);
      delay(1000);
      break;
    //for the second servos
    case 'P':
      second.write(110);
      delay(1000);
      break;
    case 'R':
      second.write(102);
      delay(1000);
      break;
    case 'I':
      second.write(50); //50, 110
      delay(1000);
      break;


    case 'W':
      second.write(180);
      delay(1000);
      break;




    case 'L':
      third.write(90);
      delay(1000);
      break;
   
    case 'S':
      third.write(45);
      delay(1000);
      break;




    case 'H':
      third.write(0);
      delay(1000);
      break;


    case 'J':
      forth.write(45);
      delay(1000);
      break;


    case 'V':
      forth.write(90);
      delay(1000);
      break;


   


   






    //for the last servo joints motors:




  }  








 
}


void moveWheelsForward() {
   int motorSpeed = map(128, 0, 255, 0, 50);
  digitalWrite(first_wheel, HIGH);
  digitalWrite(second_wheel, HIGH);
  digitalWrite(third_wheel, HIGH);
  digitalWrite(forth_wheel, HIGH);
  digitalWrite(backward_firstwheel, LOW);
  digitalWrite(backward_secondwheel, LOW);
  digitalWrite(backward_thirdwheel, LOW);
  digitalWrite(backward_forthwheel, LOW);
}


void moveWheelsBackward() {
  digitalWrite(backward_firstwheel, HIGH);
  digitalWrite(backward_secondwheel, HIGH);
  digitalWrite(backward_thirdwheel, HIGH);
  digitalWrite(backward_forthwheel, HIGH);
  digitalWrite(first_wheel, LOW);
  digitalWrite(second_wheel, LOW);
  digitalWrite(third_wheel, LOW);
  digitalWrite(forth_wheel, LOW);
  
}


void stopWheels() {
  digitalWrite(first_wheel, LOW);
  digitalWrite(second_wheel, LOW);
  digitalWrite(third_wheel, LOW);
  digitalWrite(forth_wheel, LOW);
  digitalWrite(backward_firstwheel, LOW);
  digitalWrite(backward_secondwheel, LOW);
  digitalWrite(backward_thirdwheel, LOW);
  digitalWrite(backward_forthwheel, LOW);

}


void rotateLeft() {
  digitalWrite(first_wheel, HIGH);
  digitalWrite(second_wheel, LOW);
  digitalWrite(third_wheel, HIGH);
  digitalWrite(forth_wheel, LOW);
  digitalWrite(backward_firstwheel, LOW);
  digitalWrite(backward_secondwheel, LOW);
  digitalWrite(backward_thirdwheel, LOW);
  digitalWrite(backward_forthwheel, LOW);


   






}


void rotateRight() {
  digitalWrite(first_wheel, LOW);
  digitalWrite(second_wheel, HIGH);
  digitalWrite(third_wheel, LOW);
  digitalWrite(forth_wheel, HIGH);
  digitalWrite(backward_firstwheel, LOW);
  digitalWrite(backward_secondwheel, LOW);
  digitalWrite(backward_thirdwheel, LOW);
  digitalWrite(backward_forthwheel, LOW);




 






}


void stopRotation() {
  digitalWrite(first_wheel, LOW);
  digitalWrite(second_wheel, LOW);
  digitalWrite(third_wheel, LOW);
  digitalWrite(forth_wheel, LOW);
  digitalWrite(backward_firstwheel, LOW);
  digitalWrite(backward_secondwheel, LOW);
  digitalWrite(backward_thirdwheel, LOW);
  digitalWrite(backward_forthwheel, LOW);
}

void backwardLeft(){
  digitalWrite(first_wheel, LOW);
  digitalWrite(second_wheel, LOW);
  digitalWrite(third_wheel, LOW);
  digitalWrite(forth_wheel, LOW);
  digitalWrite(backward_firstwheel, HIGH);
  digitalWrite(backward_secondwheel, LOW);
  digitalWrite(backward_thirdwheel, HIGH);
  digitalWrite(backward_forthwheel, LOW);
  

}


void measureAndSendDistance(int trigPin, int echoPin) {
  long duration;
  int distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("D");
  delay(100);  // Send 'D' to indicate distance measurement
  Serial.println(distance);
}



