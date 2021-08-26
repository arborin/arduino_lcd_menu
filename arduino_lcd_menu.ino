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

int menu_id = 0;
//int menu_index = 0;
String empty_string="                ";

int hour=0;
int min=0;
int year=2020;
int month=0;
int day=0;

//int prev_menu_id = 0;
//// MENU DATA STRUCTURE
//struct menu
//  {
//      int id;
//      int parent_id;
//      String menu;
//  };
//
//menu main_menu[] = {
//    {0,1,"Nodes"},
//    {1,1,"Set time"},
//    {2,1,"Exit"},
//};
//
//
//menu node_menu[] = {
//    // NODES MENU
//    {0,2,"Node 1"},
//    {1,2,"Node 2"},
//    {2,2,"Exit"},
//};
//
//menu node1_menu[] = {
//    // NODES MENU
//    {0,3,"Node 1"},
//    {1,3,"Set interval"},
//    {2,3,"Set period"},
//    {3,3,"Exit"},
//};
//
//menu node2_menu[] = {
//    // NODES MENU
//    {0,4,"Node 2"},
//    {1,4,"Set interval"},
//    {2,4,"Set period"},
//    {3,4,"Exit"},
//};
    

String menuItems[3] = {"Nodes", "Date", "Exit M"};
String nodeItems[3] = {"Node 1", "Node 2", "Exit N"};
String dateItems[6] = {"Hour", "Min", "Day", "Month", "Year", "Exit D"};
int dateVals[6] = {0,0,1,1,20};


void home_screen(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SMARTBIT   15:45");
  lcd.setCursor(0,1);
  lcd.print("        08/28/21");
 }


//void main_menu(){
//  int activeButton = 0;
//  lcd.clear();
//  lcd.setCursor(0, 0);
//  lcd.print("MAIN MENU");
//
//  while (activeButton == 0) {
//    int button;
//    readKey = analogRead(0);
//    if (readKey < 800) {
//      delay(100);
//      readKey = analogRead(0);
//    }
//    button = evaluateButton(readKey);
//    switch (button) {
//      case 4:  // This case will execute if the "back" button is pressed
//        button = 0;
//        activeButton = 1;
//        digitalWrite(13,LOW);
//        break;
//    }
//  }
//}

//
//void print_menu(int menu_id, int index){
//    lcd.clear();
//    // MAIN MENU
//    if(menu_id == 1){
//      if(index>2){
//        index=2;
//        menu_index = 2;
//      }
//      lcd.setCursor(0,0);
//      lcd.print("MAIN MENU");
//      lcd.setCursor(0,1);
//      lcd.print(">               ");
//      lcd.setCursor(2,1);
//      lcd.print(main_menu[index].menu);
//      delay(100);
//    }
//
//    if(menu_id == 2){
//      if(index>2){
//        index=2;
//        menu_index = 2;
//      }
//      lcd.setCursor(0,0);
//      lcd.print("MAIN MENU");
//      lcd.setCursor(0,1);
//      lcd.print(">               ");
//      lcd.setCursor(2,1);
//      lcd.print(main_menu[index].menu);
//      delay(100);
//    }
//}

int evaluateButton(int x) {
  int result = 0;
  if (x < 60) {
    result = 1; // Right
  } else if (x < 200) {
    result = 2; // up
  } else if (x < 400) {
    result = 3; // down
  } else if (x < 600) {
    result = 4; // left
  }else if (x < 800) {
    result = 5; // left
  }
  delay(20);
  return result;
}


void main_menu() { // Function executes when you select the Green item from main menu
  int activeButton = 0;
  int menu_index = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Main Menu");
  lcd.setCursor(0, 1);
  lcd.print(">");
  lcd.setCursor(2, 1);
  lcd.print(menuItems[menu_index]);

  while (activeButton == 0) {
    delay(100);
    int button;
    int readKey = analogRead(0);
    Serial.println(readKey);
    if (readKey < 800) {
      delay(100);
      readKey = analogRead(0);

      button = evaluateButton(readKey);
      switch (button) {
        case 1:
          Serial.println("Right");
          
          break;
        case 2:
          Serial.println("UP");
          menu_index-=1;
          lcd.setCursor(0, 1);
          lcd.print(">                ");
          lcd.setCursor(2, 1);
          lcd.print(menuItems[menu_index]);
          break;
        case 3:
          Serial.println("DOWN");
          menu_index+=1;
          lcd.setCursor(0, 1);
          lcd.print(">                ");
          lcd.setCursor(2, 1);
          lcd.print(menuItems[menu_index]);
          break;
        case 4:
          Serial.println("LEFT");
          
          break;
        case 5:  
          Serial.println("SELECT");
          Serial.println(menu_index);
          button = 0;
          activeButton = 1;
          switch(menu_index){
            case 0:
              node_menu();
              break;
            case 1:
              date_menu();
              break;
            case 2:
              home_screen();
              break;
          }
          break;
        }
  
        
      }
  }
  
}



void node_menu() { // Function executes when you select the Green item from main menu
  int activeButton = 0;
  int menu_index = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Node Menu");
  lcd.setCursor(0, 1);
  lcd.print(">");
  lcd.setCursor(2, 1);
  lcd.print(nodeItems[menu_index]);

  while (activeButton == 0) {
    delay(100);
    int button;
    int readKey = analogRead(0);
    Serial.println(readKey);
    if (readKey < 800) {
      delay(100);
      readKey = analogRead(0);

      button = evaluateButton(readKey);
      switch (button) {
        case 1:
          Serial.println("Right");
          break;
        case 2:
          Serial.println("UP");
          menu_index-=1;
          lcd.setCursor(0, 1);
          lcd.print(">                ");
          lcd.setCursor(2, 1);
          lcd.print(nodeItems[menu_index]);
          break;
        case 3:
          Serial.println("DOWN");
          menu_index+=1;
          lcd.setCursor(0, 1);
          lcd.print(">                ");
          lcd.setCursor(2, 1);
          lcd.print(nodeItems[menu_index]);
          break;
        case 4:
          Serial.println("LEFT");
          break;
        case 5:  
          Serial.println("SELECT");
          button = 0;
          activeButton = 1;
          switch(menu_index){
            case 0:
              node_menu();
              break;
            case 1:
              //date_menu();
              break;
            case 2:
              main_menu();
              break;
          }
          break;
        }
  

      }
  }
  
}


void date_menu() { // Function executes when you select the Green item from main menu
  int activeButton = 0;
  int menu_index = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Date Settings");
  lcd.setCursor(0, 1);
  lcd.print(">");
  lcd.setCursor(2, 1);
  lcd.print(dateItems[menu_index]);
  lcd.setCursor(14, 1);
  lcd.print(dateVals[menu_index]);

  while (activeButton == 0) {
    delay(100);
    int button;
    int readKey = analogRead(0);
    Serial.println(readKey);
    if (readKey < 800) {
      delay(100);
      readKey = analogRead(0);

      button = evaluateButton(readKey);
      switch (button) {
        case 1:
          Serial.println("Right");
          dateVals[menu_index]+=1;
          
          lcd.setCursor(0, 1);
          lcd.print(">                ");
          lcd.setCursor(2, 1);
          lcd.print(dateItems[menu_index]);
          lcd.setCursor(14, 1);
          lcd.print(dateVals[menu_index]);
          break;
        case 2:
          Serial.println("UP");
          menu_index-=1;
          lcd.setCursor(0, 1);
          lcd.print(">                ");
          lcd.setCursor(2, 1);
          lcd.print(dateItems[menu_index]);
          lcd.setCursor(14, 1);
          lcd.print(dateVals[menu_index]);
          break;
        case 3:
          Serial.println("DOWN");
          menu_index+=1;
          lcd.setCursor(0, 1);
          lcd.print(">                ");
          lcd.setCursor(2, 1);
          lcd.print(dateItems[menu_index]);
          lcd.setCursor(14, 1);
          lcd.print(dateVals[menu_index]);
          break;
        case 4:
          Serial.println("LEFT");
          dateVals[menu_index]-=1;
          lcd.setCursor(0, 1);
          lcd.print(">                ");
          lcd.setCursor(2, 1);
          lcd.print(dateItems[menu_index]);
          lcd.setCursor(14, 1);
          lcd.print(dateVals[menu_index]);
          break;
        case 5:  
          Serial.println("SELECT");
          button = 0;
          activeButton = 1;    
          main_menu();
          break;
      }
  }
  }
  
}








void setup() { 
   Serial.begin(9600);
   analogWrite(pin_BL, brightness); // SET BackLight of the LCD
   lcd.begin(16, 2);
   home_screen();
}









void loop() {
   // READ BUTTONS
   int key_val = 0;
   key_val = analogRead (0); // READING KEY PRESS VALUE
 
   if(key_val < 800){
      delay(100);      
      key_val = analogRead (0);
   }
   int btn = evaluateButton(key_val);

   switch (btn) { // The case that is selected here is dependent on which menu page you are on and where the cursor is.
      case 1:
        Serial.println("Right");
        break;
      case 2:
        Serial.println("UP");
        break;
      case 3:
        Serial.println("DOWN");
        break;
      case 4:
        Serial.println("LEFT");
        break;
      case 5:
        Serial.println("SELECT");
        main_menu();
        break;
    }
} 
