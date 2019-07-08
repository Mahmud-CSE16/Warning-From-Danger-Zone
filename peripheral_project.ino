//The circuit:
// * LCD RS pin to digital pin 10
// * LCD Enable pin to digital pin 9
// * LCD D4 pin to digital pin 5
// * LCD D5 pin to digital pin 4
// * LCD D6 pin to digital pin 3
// * LCD D7 pin to digital pin 2
// * LCD R/W pin to ground
// * LCD VSS pin to ground
// * LCD VCC pin to 5V
// * LCD A pin to digital pin 8
// * LCD K pin to ground
// * LCD V0 pin to digital pin 6 (contrast)


// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(10, 9, 5, 4, 3, 2);
//front_sonar
#define trigPinF A0
#define echoPinF A1
//left_sonar
#define trigPinL A2
#define echoPinL A3
//right_sonar
#define trigPinR A4
#define echoPinR A5
//back_sonar
#define trigPinB A6
#define echoPinB A7

long cmF;
long cmL;
long cmR;
long cmB;
long duration;

int buzzer = 11;

void setup(){
  
  pinMode(trigPinF, OUTPUT);
  pinMode(echoPinF, INPUT);
  
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT);
  
  //analog pin
  pinMode(8,OUTPUT);
  analogWrite(8,150);
  
  //6 pin as contrast and value=20
  analogWrite(6,20);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
//  // Print a message to the LCD.
//  lcd.print("Hello World ...");
//  delay(1000);
  Serial.begin(9600);
}


void loop() {
  sonar();
  if(cmF<=10 || cmL<=10 || cmR<=10 || cmB<=10){
    if(cmF<=10){
      Serial.println("forward");
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Some one");
      lcd.setCursor(3, 1);
      lcd.print("in Front side");
    }
    if(cmL<=10){
      Serial.println("left");
       lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Some one");
      lcd.setCursor(3, 1);
      lcd.print("in Left side");
    }
    if(cmR<=10){
      Serial.println("right");
       lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Some one");
      lcd.setCursor(3, 1);
      lcd.print("in Right side");
    }
    if(cmB<=10){
      Serial.println("back");
       lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Some one");
      lcd.setCursor(3, 1);
      lcd.print("in back side");
    }
    tone(buzzer,700);
    delay(1000);
    noTone(buzzer);
    delay(500);
  }else{
    lcd.clear();
    lcd.print("Danger Zone..");
  }
}


long TimetoDistance(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return (microseconds * 0.03448) / 2;
}

  void sonar(){
    digitalWrite(trigPinF, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinF, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinF, LOW);

    duration = pulseIn(echoPinF, HIGH);
    cmF = TimetoDistance(duration);
    Serial.print("cmF : ");
    Serial.println(cmF);
    
    digitalWrite(trigPinL, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinL, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinL, LOW);

    duration = pulseIn(echoPinL, HIGH);
    cmR = TimetoDistance(duration);
    Serial.print("cmL : ");
    Serial.println(cmR);
    
    digitalWrite(trigPinR, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinR, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinR, LOW);

    duration = pulseIn(echoPinR, HIGH);
    cmL = TimetoDistance(duration);
    Serial.print("cmR : ");
    Serial.println(cmL);
    
    digitalWrite(trigPinB, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinB, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinB, LOW);

    duration = pulseIn(echoPinB, HIGH);
    cmB = TimetoDistance(duration);
    Serial.print("cmB : ");
    Serial.println(cmB);
    //Serial.print(" ");
    //delay(10);
  }
