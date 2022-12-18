#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>
int pin =8;
int duree = 250; //Durée du son
int freqmin = 2000; //La fréquence plus basse à émettre
int freqmax = 3000;
DS3231 myRTC;
LiquidCrystal_I2C lcd(0x27, 16, 2);
DateTime now;
bool century = false;
bool h12Flag;
bool pmFlag;
void setup () {
    Serial.begin(57600);
    Wire.begin();
    lcd.begin();
//  myRTC.setYear(22);
//  myRTC.setMonth(06);
//  myRTC.setDate(01);
//  myRTC.setDoW(3);
//  myRTC.setHour(18);
//  myRTC.setMinute(02);
//  myRTC.setSecond(0);
}

//----------------------fonction d'alarme---------------------------------------
void son(int d, int h , int m , int s){
  if(myRTC.getDoW()==d && myRTC.getHour(h12Flag, pmFlag)==h && myRTC.getMinute() ==m){
while(myRTC.getSecond()<5){
  sonner();
}
}
}
//************************************ fonction d'alarme pour les jours lundi ----- jeudi et le samedi**********************************
void jour_son(int j){
son(j,8,25,0);
son(j,9,14,00);
son(j,9,15,0);
son(j,13,25,0);
son(j,13,35,0);
son(j,15,50,0);
son(j,16,10,0);
son(j,18,30,0);
  }
//************************************ fonction d'alarme   vendredi**********************************
void vendredi_son(void){
son(5,8,25,0);
son(5,10,25,0);
son(5,10,35,0);
son(5,12,30,0);
son(5,14,25,0);
son(5,16,25,0);
son(5,16,35,0);
son(5,18,30,0);
}
void sonner(){
  int i;
  //le son devient plus aigu 
  for (i = freqmin; i<=freqmax; i++){
    tone (8, i, duree);
  }
  //le son devient plus grave
  for (i = freqmax; i>=freqmin; i--){
    tone (9, i, duree);
 }
//tone(pin,1000);
//delay(5000);
}
void loop () {
    lcd.setCursor(0,0);
    lcd.print("Date:  ");
    lcd.print(myRTC.getDate(), DEC);
    lcd.print('/');
    lcd.print(myRTC.getMonth(century), DEC);
    lcd.print('/');
    lcd.print(myRTC.getYear(), DEC);
    lcd.print(' ');
//-----------------------------------------
    lcd.setCursor(0,1);
    lcd.print("Time: ");
    lcd.print(myRTC.getHour(h12Flag, pmFlag), DEC);
    lcd.print(':');
    lcd.print(myRTC.getMinute(), DEC);
    lcd.print(':');
    lcd.print(myRTC.getSecond(), DEC);
//-------------------------------------------       
    jour_son(1);
    jour_son(2);
    jour_son(3);
    jour_son(4);
    vendredi_son();
    jour_son(6);
//-------------------------------------------    
    Serial.print(myRTC.getYear(), DEC);
    Serial.print('/');
    Serial.print(myRTC.getMonth(century), DEC);
    Serial.print('/'); 
    Serial.print(myRTC.getDate(), DEC);
    Serial.print(' ');
    Serial.print(myRTC.getHour(h12Flag, pmFlag), DEC);
    Serial.print(':');
    Serial.print(myRTC.getMinute(), DEC);
    Serial.print(':');
    Serial.print(myRTC.getSecond(), DEC);
    Serial.println();
}
