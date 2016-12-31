/*

   Based on adamwelch.co.uk/2016/01/lithium-ion-18650-battery-capacity-checker/

*/

// Change these to match your configuration

#define highPin1 A7    // High side of the shunt resitor
#define lowPin1  A6   // Low side of the shunt resistor
#define gatePin1 2     // Signal to the gate pin of the MOSFET

#define highPin2 A5
#define lowPin2  A4
#define gatePin2 4

#define highPin3 A3
#define lowPin3  A2
#define gatePin3 6

#define highPin4 A1
#define lowPin4  A0
#define gatePin4 8

float shuntRes1 = 0.3; // In Ohms - Shunt resistor value
float shuntRes2 = 0.3;
float shuntRes3 = 0.3;
float shuntRes4 = 0.3;

float voltRef = 4.66;  // Reference voltage (probe your 5V pin)
int interval = 3000;   //Interval (ms) between measurements

float cellLow = 3.0;   // Discharge cutoff voltage 3.0 is safe for LiIon cells

// END of config options

boolean finished1 = false;
boolean finished2 = false;
boolean finished3 = false;
boolean finished4 = false;
boolean finishedAll = false;

float mAh1 = 0.0;
float mAh2 = 0.0;
float mAh3 = 0.0;
float mAh4 = 0.0;

float cellVolt1 = 0.0;
float cellVolt2 = 0.0;
float cellVolt3 = 0.0;
float cellVolt4 = 0.0;

float shuntVolt1 = 0.0;
float shuntVolt2 = 0.0;
float shuntVolt3 = 0.0;
float shuntVolt4 = 0.0;

float current = 0.0;

unsigned long previousMillis = 0;
unsigned long millisPassed = 0;
unsigned long previousMs = 0;

void setup() {
  Serial.begin(115200);
  pinMode(gatePin1, OUTPUT);
  pinMode(gatePin2, OUTPUT);
  pinMode(gatePin3, OUTPUT);
  pinMode(gatePin4, OUTPUT);
  digitalWrite(gatePin1, LOW);
  digitalWrite(gatePin2, LOW);
  digitalWrite(gatePin3, LOW);
  digitalWrite(gatePin4, LOW);
  delay(2000);
}

void loop() {

  cellVolt1 = analogRead(highPin1) * voltRef / 1024.0;
  cellVolt2 = analogRead(highPin2) * voltRef / 1024.0;
  cellVolt3 = analogRead(highPin3) * voltRef / 1024.0;
  cellVolt4 = analogRead(highPin4) * voltRef / 1024.0;

  shuntVolt1 = analogRead(lowPin1) * voltRef / 1024.0;
  shuntVolt2 = analogRead(lowPin2) * voltRef / 1024.0;
  shuntVolt3 = analogRead(lowPin3) * voltRef / 1024.0;
  shuntVolt4 = analogRead(lowPin4) * voltRef / 1024.0;

  unsigned long currentMillis = millis();

  // Main cell checking and reporting routine

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    //Cell 1
    if (cellVolt1 >= cellLow && finished1 == false)
    {
      digitalWrite(gatePin1, HIGH);
      millisPassed = millis() - previousMs;
      current = (cellVolt1 - shuntVolt1) / shuntRes1;
      mAh1 = mAh1 + (current * 1000.0) * (millisPassed / 3600000.0);

      Serial.print("C1");
      Serial.print("\t");
      Serial.print(cellVolt1);
      Serial.print("\t");
      Serial.print(current);
      Serial.print("\t");
      Serial.println(mAh1);
    }

    if (cellVolt1 < cellLow)
    {
      digitalWrite(gatePin1, LOW);
      finished1 = true;
    }

    if (finished1 == true && finishedAll == false)
    {
      Serial.print("C1*");
      Serial.print("\t");
      Serial.println(mAh1, 0);
    }

    // Cell 2
    if (cellVolt2 >= cellLow && finished2 == false)
    {
      digitalWrite(gatePin2, HIGH);
      millisPassed = millis() - previousMs;
      current = (cellVolt2 - shuntVolt2) / shuntRes2;
      mAh2 = mAh2 + (current * 1000.0) * (millisPassed / 3600000.0);

      Serial.print("C2");
      Serial.print("\t");
      Serial.print(cellVolt2);
      Serial.print("\t");
      Serial.print(current);
      Serial.print("\t");
      Serial.println(mAh2);
    }

    if (cellVolt2 < cellLow)
    {
      digitalWrite(gatePin2, LOW);
      finished2 = true;
    }

    if (finished2 == true && finishedAll == false)
    {
      Serial.print("C2*");
      Serial.print("\t");
      Serial.println(mAh2, 0);
    }

    // Cell 3
    if (cellVolt3 >= cellLow && finished3 == false)
    {
      digitalWrite(gatePin3, HIGH);
      millisPassed = millis() - previousMs;
      current = (cellVolt3 - shuntVolt3) / shuntRes3;
      mAh3 = mAh3 + (current * 1000.0) * (millisPassed / 3600000.0);

      Serial.print("C3");
      Serial.print("\t");
      Serial.print(cellVolt3);
      Serial.print("\t");
      Serial.print(current);
      Serial.print("\t");
      Serial.println(mAh3);
    }

    if (cellVolt3 < cellLow)
    {
      digitalWrite(gatePin3, LOW);
      finished3 = true;
    }

    if (finished3 == true && finishedAll == false)
    {
      Serial.print("C3*");
      Serial.print("\t");
      Serial.println(mAh3, 0);
    }

    // Cell 4
    if (cellVolt4 >= cellLow && finished4 == false)
    {
      digitalWrite(gatePin4, HIGH);
      millisPassed = millis() - previousMs;
      current = (cellVolt4 - shuntVolt4) / shuntRes4;
      mAh4 = mAh4 + (current * 1000.0) * (millisPassed / 3600000.0);

      Serial.print("C4");
      Serial.print("\t");
      Serial.print(cellVolt4);
      Serial.print("\t");
      Serial.print(current);
      Serial.print("\t");
      Serial.println(mAh4);
    }

    if (cellVolt4 < cellLow)
    {
      digitalWrite(gatePin4, LOW);
      finished4 = true;
    }

    if (finished4 == true && finishedAll == false)
    {
      Serial.print("C4*");
      Serial.print("\t");
      Serial.println(mAh4, 0);
    }

    // Add a blank line
    if (finishedAll == false)
    {
      Serial.println();
    }

    // All cells have finished discharging.

    if (finished1 == true && finished2 == true && finished3 == true && finished4 == true)
    {
      Serial.println("All cells are discharged");
      Serial.print("C1");
      Serial.print("\t");
      Serial.println(mAh1, 0);
      Serial.print("C2");
      Serial.print("\t");
      Serial.println(mAh2, 0);
      Serial.print("C3");
      Serial.print("\t");
      Serial.println(mAh3, 0);
      Serial.print("C4");
      Serial.print("\t");
      Serial.println(mAh4, 0);
      Serial.println();
      finishedAll = true;
    }
    previousMs = millis();
  }
}
