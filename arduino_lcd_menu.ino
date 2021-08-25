/*
https://create.arduino.cc/projecthub/electropeak/using-1602-lcd-keypad-shield-w-arduino-w-examples-e02d95

*/
#include <LiquidCrystal.h>

//LCD pin to Arduino
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int pin_BL = 10; // BACKLIGHT PIN
const int brightness = 100;

LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

int menu_id = -1;
int prev_menu_id = 0;
// MENU DATA STRUCTURE
struct menu
  {
      int id;
      int parent;
      String menu;
  };

menu record[] = {
    {0,0,"Nodes"},
    {1,0,"Config"},
    {2,0,"Exit"},
  };


void home_screen(){
  lcd.setCursor(0,0);
  lcd.print("SMARTBIT        ");
  lcd.setCursor(0,1);
  lcd.print("----------------");
 }

void print_menu(int menu_id, int parent_id){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Main Menu");
  lcd.setCursor(0,1);
  lcd.print(">               ");
  lcd.setCursor(2,1);
  lcd.print(record[menu_id].menu);
  delay(100);
}



void setup() { 
 Serial.begin(9600);
 analogWrite(pin_BL, brightness); // SET BackLight of the LCD
 lcd.begin(16, 2);
 home_screen();
 delay(3000);
}







void loop() {
  
 int key_val;
 key_val = analogRead (0); // READING KEY PRESS VALUE
 delay(150);

 
 if (key_val < 60) {
   lcd.print ("Right ");
 }
 else if (key_val < 200) {
   // UP
   Serial.println(key_val);
   Serial.println(menu_id);
     
   
   if(menu_id>0){
      menu_id-=1;
      print_menu(menu_id, 0);
   }
   
   
 }
 
 else if (key_val < 400){
   //DOWN
   Serial.println(key_val);
   
   Serial.println(menu_id);
   
   
  if(menu_id<2){
        menu_id+=1;
        print_menu(menu_id, 0);
     } 
 }
 
 else if (key_val < 600){
   lcd.print ("Left  ");
 }
 else if (key_val < 800){
//   lcd.print ("Select");
   // START
   if(menu_id==2){
    home_screen();
    menu_id=-1;
   }
 }
} 
