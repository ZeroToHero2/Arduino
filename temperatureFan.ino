#include <Adafruit_TCS34725.h>
#include <Servo.h>
#include "Wire.h"
#include "Adafruit_TCS34725.h"

float Temperature; 
float value; 
int lm35pin=A0;
int motor=8;
 
Servo ust_servo;
Servo alt_servo;
int renk = 0;
int data, durum = false;
 
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);
void setup() {
Serial.begin(9600);
pinMode(A0,INPUT);
pinMode(motor,OUTPUT);

 
if (tcs.begin()) {
} else {
 
while (1); // Dur!
}
 
ust_servo.attach(9);
alt_servo.attach(8);
ust_servo.write(120);
delay(10);
}
void loop() {
value = analogRead(lm35pin); 
value = (value/1023)*5000; 
Temperature = value/10;  
 
data = Serial.read();
delay(10);

if ( durum == true)
{
makine_baslat();
}
else 
{
makine_durdur();
}
 
}
 
void makine_baslat()
{
delay(500);
for(int i = 120; i > 55; i--) {
ust_servo.write(i);
delay(5);
}
delay(500);

renk = renk_oku();
delay(50);
switch (renk) {
 Serial.print("Sicaklik : ");
 Serial.print (Temperature);
 Serial.println (" ^C");

 if (Temperature>=15 && Temperature<=17)
 {
alt_servo.write(45);
Serial.println(1);
break;
 }

else if ( Temperature<=20)
 {
alt_servo.write(60);
Serial.println(2);
break; 
 }

else if ( Temperature<=25)
 {
alt_servo.write(72);
Serial.println(3);
break;
 }

else if (Temperature>25 )
 {   
alt_servo.write(88);
Serial.println(4);
break;
 }

else if (Temperature>25 )
 {   
alt_servo.write(102);
Serial.println(5);
break;
 }

else if (Temperature>25 )
 {   
alt_servo.write(120);
Serial.println(6);
break;
 }

else 
 {
Serial.println(0);
break;
 }
delay(300);


for(int i = 55; i > 20; i--) {
ust_servo.write(i);
delay(5);
}
delay(200);
 
for(int i = 20; i < 120; i++) {
ust_servo.write(i);
delay(5);
}
renk=0;
}
 
void makine_durdur()
{
ust_servo.write(ust_servo.read());
alt_servo.write(alt_servo.read());
}
 
// renk okuma fonksiyonu
int renk_oku() {
uint16_t clearcol, red, green, blue;
float average, r, g, b;
tcs.getRawData(&red, &green, &blue, &clearcol);
 
average = (red+green+blue)/3;
r = red/average;
g = green/average;
b = blue/average;
 
delay(50);
 
if((r < 1.74)&& (r > 1.58) && (g > 0.76) && (g < 0.9)&& (b < 0.56) && (b > 0.45)){
renk = 1;
 
}
if((r < 1.05)&& (r > 0.75) && (g > 1.38) && (g < 1.5)&& (b < 1)&& (b > 0.54)){
renk = 2;
 
}
if((r < 1.32)&& (r > 1.19) && (g > 1.24) && (g < 1.34)&& (b < 0.52)&& (b > 0.42)){
renk = 3;
 
}
 
if((r < 1.5)&& (r > 1.35) && (g > 0.74) && (g < 0.85)&& (b < 0.9)&& (b > 0.7)){
renk = 4;
 
}
if((r < 2.2)&& (r > 1.8) && (g > 0.5) && (g < 0.65)&& (b < 0.55)&& (b > 0.4)){
renk = 5;
 
}
if((r < 1)&& (r > 0.48) && (g > 1.24) && (g < 1.34)&& (b < 1.24)&& (b > 1.14)){
renk = 6;
 
}
return renk;
}
