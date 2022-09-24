#include <Servo.h> 

Servo horizontal; // Yatay Servo Motor
int servoh = 90;   
int servohLimitHigh = 180;
int servohLimitLow = 65;
Servo vertical;   // Dikey Servo 
int servov = 90;    
int servovLimitHigh = 120;
int servovLimitLow = 15;

int ldrlt = 2; // Sol Üst LDR Sensör Pini   
int ldrrt = 3; //Sağ Üst LDR Sensör Pini
int ldrld = 0; //Sol Alt Sensör Pini
int ldrrd = 1; //Sağ Alt Sensör Pini

void setup()
{
  Serial.begin(9600);
  horizontal.attach(9); // Yatay Ekseni Servo Motor Pini
  vertical.attach(10); // Dikey Ekseni Servo Motor Pini
  horizontal.write(180);
  vertical.write(45);
}

void loop() 
{
  int lt = analogRead(ldrlt); // Sol Üst LDR Sensör 
  int rt = analogRead(ldrrt); // Sağ Üst LDR Sensör
  int ld = analogRead(ldrld); // Sol Alt Sensör
  int rd = analogRead(ldrrd); // Sağ Alt Sensör
  
  int dtime = 10;
  int tol = 50;
  
  int avt = (lt + rt) / 2; // Üst Sensör Verilerinin Ortalaması
  int avd = (ld + rd) / 2; // Alt Sensör Verilerinin Oratalaması
  int avl = (lt + ld) / 2; // Sol Sensör Verilerinin Ortalaması
  int avr = (rt + rd) / 2; // Sağ Sensör Verilerinin Ortalaması

  int dvert = avt - avd; // Alt ve Üst Sensörlerin Farkı
  int dhoriz = avl - avr;// Sağ ve Sol Sensörlerin Farkı
  
  Serial.print(avt);
  Serial.print(" ");
  Serial.print(avd);
  Serial.print(" ");
  Serial.print(avl);
  Serial.print(" ");
  Serial.print(avr);
  Serial.print("   ");
  Serial.print(dtime);
  Serial.print("   ");
  Serial.print(tol);
  Serial.println(" ");
  
    
  if (-1*tol > dvert || dvert > tol)
  {
  if (avt > avd)
  {
    servov = ++servov;
     if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
  }
  else if (avt < avd)
  {
    servov= --servov;
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
  }
  vertical.write(servov);
  }
  
  if (-1*tol > dhoriz || dhoriz > tol)
  {
  if (avl > avr)
  {
    servoh = --servoh;
    if (servoh < servohLimitLow)
    {
    servoh = servohLimitLow;
    }
  }
  else if (avl < avr)
  {
    servoh = ++servoh;
     if (servoh > servohLimitHigh)
     {
     servoh = servohLimitHigh;
     }
  }
  else if (avl = avr)
  {
    
  }
  horizontal.write(servoh);
  }
   delay(dtime);
}
