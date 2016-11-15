/* 
* Battery Capacity Checker
* 
* Based on adamwelch.co.uk/2016/01/lithium-ion-18650-battery-capacity-checker/ 
* YouTube Video: https://www.youtube.com/embed/qtws6VSIoYk
* 
* The LCD functions have been removed as I'm logging it all to serial
* 
* Modified to monitor 4 cells instead of 1
*
* Using an Arduino Micro
*
*/


// Change these to match your configuration

#define highPin1 A0    // High side of the shunt resitor
#define lowPin1  A11   // Low side of the shunt resistor
#define gatePin1 7     // Signal to the gate pin of the MOSFET

#define highPin2 A1
#define lowPin2  A10
#define gatePin2 5

#define highPin3 A2
#define lowPin3  A9
#define gatePin3 3

#define highPin4 A3
#define lowPin4  A8
#define gatePin4 2
 
float shuntRes1 = 0.3; // In Ohms - Shunt resistor value
float shuntRes2 = 0.3;
float shuntRes3 = 0.3;
float shuntRes4 = 0.3;

float voltRef = 5.00;  // Reference voltage (probe your 5V pin) 
int interval = 3000;   //Interval (ms) between measurements

// END of config options

boolean finished1 = false;
boolean finished2 = false;
boolean finished3 = false;
boolean finished4 = false;
 
boolean wait1 = false;
boolean wait2 = false;
boolean wait3 = false;
boolean wait4 = false;
boolean waitAll = false;
 
float mAh1 = 0.0;
float mAh2 = 0.0;
float mAh3 = 0.0;
float mAh4 = 0.0;

float battVolt1 = 0.0;
float battVolt2 = 0.0;
float battVolt3 = 0.0;
float battVolt4 = 0.0;

float shuntVolt1 = 0.0;
float shuntVolt2 = 0.0;
float shuntVolt3 = 0.0;
float shuntVolt4 = 0.0;

float current = 0.0;
float battLow = 3.0;
 
unsigned long previousMillis = 0;
unsigned long millisPassed = 0;

unsigned long previousMs1 = 0;
unsigned long previousMs2 = 0;
unsigned long previousMs3 = 0;
unsigned long previousMs4 = 0;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousMillis4 = 0;
unsigned long previousMillisAll = 0;
 
void setup() {
  Serial1.begin(115200);
  Serial1.println("Booting up...");
 
  pinMode(gatePin1, OUTPUT);
  pinMode(gatePin2, OUTPUT);
  pinMode(gatePin3, OUTPUT);
  pinMode(gatePin4, OUTPUT);
  digitalWrite(gatePin1, LOW);
  digitalWrite(gatePin2, LOW);
  digitalWrite(gatePin3, LOW);
  digitalWrite(gatePin4, LOW);
 }
 
void loop() {
 
  battVolt1 = analogRead(highPin1) * voltRef / 1024.0;
  battVolt2 = analogRead(highPin2) * voltRef / 1024.0;
  battVolt3 = analogRead(highPin3) * voltRef / 1024.0;
  battVolt4 = analogRead(highPin4) * voltRef / 1024.0;

  shuntVolt1 = analogRead(lowPin1) * voltRef / 1024.0;
  shuntVolt2 = analogRead(lowPin2) * voltRef / 1024.0;
  shuntVolt3 = analogRead(lowPin3) * voltRef / 1024.0;
  shuntVolt4 = analogRead(lowPin4) * voltRef / 1024.0;

  unsigned long currentMillis = millis();

//BATTERY 1
  if(battVolt1 >= battLow && finished1 == false && wait1 == false) 
  {
      digitalWrite(gatePin1, HIGH);
      millisPassed = millis() - previousMs1;
      current = (battVolt1 - shuntVolt1) / shuntRes1;
      mAh1 = mAh1 + (current * 1000.0) * (millisPassed / 3600000.0);
      previousMs1 = millis();
      wait1 = true;
       
      Serial1.print("B1");
      Serial1.print("\t");
      Serial1.print(battVolt1);
      Serial1.print("\t");
      Serial1.print(current);
      Serial1.print("\t");
      Serial1.println(mAh1);
       
  }

  if(battVolt1 < battLow && wait1 == false)
  {
      digitalWrite(gatePin1, LOW);
      finished1 = true;
  }

  if(finished1 == true && wait1 == false)
  {
      Serial1.print("B1*");
      Serial1.print("\t");
      Serial1.println(mAh1);
      wait1 = true;
  }

  if((wait1 == true) && (currentMillis - previousMillis1 >= interval))
  {
       wait1 = false;
       previousMillis1 = currentMillis;  // Remember the time
  }

// BATTERY 2
  if(battVolt2 >= battLow && finished2 == false && wait2 == false)
  {
      digitalWrite(gatePin2, HIGH);
      millisPassed = millis() - previousMs2;
      current = (battVolt2 - shuntVolt2) / shuntRes2;
      mAh2 = mAh2 + (current * 1000.0) * (millisPassed / 3600000.0);
      previousMs2 = millis();
      wait2 = true;
        
      Serial1.print("B2");
      Serial1.print("\t");
      Serial1.print(battVolt2);
      Serial1.print("\t");
      Serial1.print(current);
      Serial1.print("\t");
      Serial1.println(mAh2);
  }

  if(battVolt2 < battLow && wait2 == false)
  {
      digitalWrite(gatePin2, LOW);
      finished2 = true;
  }

  if(finished2 == true && wait2 == false)
  {
      Serial1.print("B2*");
      Serial1.print("\t");
      Serial1.println(mAh2);
      wait2 = true;
  }

  if((wait2 == true) && (currentMillis - previousMillis2 >= interval))
  {
       wait2 = false;
       previousMillis2 = currentMillis;  // Remember the time
  }

// BATTERY 3
  if(battVolt3 >= battLow && finished3 == false && wait3 == false)
  {
      digitalWrite(gatePin3, HIGH);
      millisPassed = millis() - previousMs3;
      current = (battVolt3 - shuntVolt3) / shuntRes3;
      mAh3 = mAh3 + (current * 1000.0) * (millisPassed / 3600000.0);
      previousMs3 = millis();
      wait3 = true;
        
      Serial1.print("B3");
      Serial1.print("\t");
      Serial1.print(battVolt3);
      Serial1.print("\t");
      Serial1.print(current);
      Serial1.print("\t");
      Serial1.println(mAh3);
  }
  if(battVolt3 < battLow && wait3 == false)
  {
      digitalWrite(gatePin3, LOW);
      finished3 = true;
  }

  if(finished3 == true && wait3 == false)
  {
      Serial1.print("B3*");
      Serial1.print("\t");
      Serial1.println(mAh3);
      wait3 = true;
  }

  if((wait3 == true) && (currentMillis - previousMillis3 >= interval))
  {
       wait3 = false;
       previousMillis3 = currentMillis;  // Remember the time
  }

// BATTERY 4
  if(battVolt4 >= battLow && finished4 == false && wait4 == false)
  {
      digitalWrite(gatePin4, HIGH);
      millisPassed = millis() - previousMs4;
      current = (battVolt4 - shuntVolt4) / shuntRes4;
      mAh4 = mAh4 + (current * 1000.0) * (millisPassed / 3600000.0);
      previousMs4 = millis();
      wait4 = true;
        
      Serial1.print("B4");
      Serial1.print("\t");
      Serial1.print(battVolt4);
      Serial1.print("\t");
      Serial1.print(current);
      Serial1.print("\t");
      Serial1.println(mAh4);
  }

  if(battVolt4 < battLow && wait4 == false)
  {
      digitalWrite(gatePin4, LOW);
      finished4 = true;
  }

  if(finished4 == true && wait4 == false)
  {
      Serial1.print("B4*");
      Serial1.print("\t");
      Serial1.println(mAh4);
      wait4 = true;
  }

  if((wait4 == true) && (currentMillis - previousMillis4 >= interval))
  {
       wait4 = false;
       previousMillis4 = currentMillis;  // Remember the time
  }

// All batteries have finished discharging.

  if(finished1 == true && finished2 == true && finished3 == true && finished4 == true && waitAll == false)
  {
     Serial1.println("All batteries are discharged");
     Serial1.print("B1");
     Serial1.print("\t");
     Serial1.println(mAh1);
     Serial1.print("B2");
     Serial1.print("\t");
     Serial1.println(mAh2);
     Serial1.print("B3");
     Serial1.print("\t");
     Serial1.println(mAh3);
     Serial1.print("B4");
     Serial1.print("\t");
     Serial1.println(mAh4);
     waitAll = true;
  }
  if((waitAll == true) && (currentMillis - previousMillisAll >= interval))
  {
       waitAll = false;
       previousMillisAll = currentMillis;  // Remember the time
  }
}
