#include <Servo.h>
#include <SoftwareSerial.h>




//set up the bluetooth module
SoftwareSerial bluetoothSerial(0, 1);

//set up 4 servo motors for the robot's arm
Servo first; 
Servo second;
Servo third;
Servo forth;




//set up 7 ultrasonic sensors
const int trigPin2 = 12;   // Ultrasonic sensor 2 trigger pin   first
const int echoPin2 = 13;   // Ultrasonic sensor 2 echo pin
const int trigPin3 = 10;   // Ultrasonic sensor 3 trigger pin   second
const int echoPin3 = 11;   // Ultrasonic sensor 3 echo pin
const int trig4 = 8;   //third ultrasonic
const int echo4 = 9;
const int trig5 = 6;  //forth
const int echo5 =7;
const int trig6 = A1;
const int echo6 =A0;   //fifth
const int trig7 = A3;//sixth
const int echo7 =A2;
const int trig8 = A5;
const int echo8 = A4;
const int trig9 = A7;
const int echo9 = A6;

//set up 6 wheels for both forward and backward 
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
  first.attach(3);//set up pin for first servo
  second.attach(2);//set up pin for second servo
  third.attach(4);//set up pin for third servo
  forth.attach(5);//set up pin for forth servo
  first.write(0);//keep this fix at 0 for original pos , 180 to grab
  second.write(180);//keep this fix at 180 for original pos , 90 turns left
  third.write(30);  //30 //keep this fix at 0 for original pos, and 60 for closed distance, further move the forth servo
  forth.write(180);  //keep this fix at 45 for orginal pos, and 90 when ultrasonic is detected for further bottle
  //OUTPUT FOR TRIGGER AND INPUT FOR ECHO
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
  //OUTPUT FOR ALL 6 DC MOTORS both forward and backward
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
  if (Serial.available() > 0) { //send the commands to Python
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
    case 'T': //send the data of the distance from the first ultrasonic sensors tp Python
      measureAndSendDistance(trigPin2, echoPin2);
      break;
    case 'G'://send the data of the distance from the second ultrasonic sensors tp Python
      measureAndSendDistance(trigPin3, echoPin3);
      break;
    case 'Y'://send the data of the distance from the third ultrasonic sensors tp Python
      measureAndSendDistance(trig4, echo4);
      break;
    case 'a'://send the data of the distance from the forth ultrasonic sensors tp Python
      measureAndSendDistance(trig5, echo5);
      break;


   
    case 'b'://send the data of the distance from the fifth ultrasonic sensors tp Python
      measureAndSendDistance(trig6, echo6);
      break;
    case 'c'://send the data of the distance from the sixth ultrasonic sensors tp Python
      measureAndSendDistance(trig7, echo7);
      break;


    case 'd'://send the data of the distance from the seventh ultrasonic sensors tp Python
      measureAndSendDistance(trig8, echo8);
      break;




     case 'e': //send the data of the distance from the eighth ultrasonic sensors tp Python
      measureAndSendDistance(trig9, echo9);
      break;

    case 'f'://send the data to Python for going backward of 6 DC motors
      backwardLeft();
      break;


    //-----FOR THE SERVO-----







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



    //for the third servo motors
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

    //for the 4th servo motors
    case 'J':
      forth.write(45);
      delay(1000);
      break;


    case 'V':
      forth.write(90);
      delay(1000);
      break;


  }  








 
}


void moveWheelsForward() { //function for 6 DC motors going straightforward
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


void moveWheelsBackward() {//function for 6 DC motors going backward
  digitalWrite(backward_firstwheel, HIGH);
  digitalWrite(backward_secondwheel, HIGH);
  digitalWrite(backward_thirdwheel, HIGH);
  digitalWrite(backward_forthwheel, HIGH);
  digitalWrite(first_wheel, LOW);
  digitalWrite(second_wheel, LOW);
  digitalWrite(third_wheel, LOW);
  digitalWrite(forth_wheel, LOW);
  
}


void stopWheels() {//function to stop DC motors, set all the DC motors to LOW
  digitalWrite(first_wheel, LOW);
  digitalWrite(second_wheel, LOW);
  digitalWrite(third_wheel, LOW);
  digitalWrite(forth_wheel, LOW);
  digitalWrite(backward_firstwheel, LOW);
  digitalWrite(backward_secondwheel, LOW);
  digitalWrite(backward_thirdwheel, LOW);
  digitalWrite(backward_forthwheel, LOW);

}


void rotateLeft() {//fuction for 3 LEFT DC MOTORS to turn, set the first and the third DC motors to HIGH, the rest is set to LOW
  digitalWrite(first_wheel, HIGH);
  digitalWrite(second_wheel, LOW);
  digitalWrite(third_wheel, HIGH);
  digitalWrite(forth_wheel, LOW);
  digitalWrite(backward_firstwheel, LOW);
  digitalWrite(backward_secondwheel, LOW);
  digitalWrite(backward_thirdwheel, LOW);
  digitalWrite(backward_forthwheel, LOW);


   






}


void rotateRight() { ////fuction for 3 LEFT DC MOTORS to turn, set the second and the forth DC motors to HIGH, the rest is set to LOW
  digitalWrite(first_wheel, LOW);
  digitalWrite(second_wheel, HIGH);
  digitalWrite(third_wheel, LOW);
  digitalWrite(forth_wheel, HIGH);
  digitalWrite(backward_firstwheel, LOW);
  digitalWrite(backward_secondwheel, LOW);
  digitalWrite(backward_thirdwheel, LOW);
  digitalWrite(backward_forthwheel, LOW);




 






}


void stopRotation() {//set every single DC motors to LOW
  digitalWrite(first_wheel, LOW);
  digitalWrite(second_wheel, LOW);
  digitalWrite(third_wheel, LOW);
  digitalWrite(forth_wheel, LOW);
  digitalWrite(backward_firstwheel, LOW);
  digitalWrite(backward_secondwheel, LOW);
  digitalWrite(backward_thirdwheel, LOW);
  digitalWrite(backward_forthwheel, LOW);
}

void backwardLeft(){//set the backward first and third DC motors to HIGH so the robot can pitch to the left when it's going backward
  digitalWrite(first_wheel, LOW);
  digitalWrite(second_wheel, LOW);
  digitalWrite(third_wheel, LOW);
  digitalWrite(forth_wheel, LOW);
  digitalWrite(backward_firstwheel, HIGH);
  digitalWrite(backward_secondwheel, LOW);
  digitalWrite(backward_thirdwheel, HIGH);
  digitalWrite(backward_forthwheel, LOW);
  

}


void measureAndSendDistance(int trigPin, int echoPin) {//set up 7 ultrasonisc sensors and call each of them inside the each case function
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



