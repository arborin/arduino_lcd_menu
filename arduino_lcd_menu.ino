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
    

String menuItems[3] = {"Nodes", "Date", "Exit M"};
String nodeItems[3] = {"Node 1", "Node 2", "Exit N"};
String dateItems[6] = {"Hour", "Min", "Day", "Month", "Year", "Exit D"};
int dateVals[6] = {0,0,1,1,20};
String days[8] = {"Mon","Tues","Wed","Thu","Fri","Sat","San", "Exit"};
int node1_on_day[7] = {0,0,0,0,0,0,0};
int node2_on_day[7] = {0,0,0,0,0,0,0};
int node1_start_hour = 0;
int node2_start_hour = 0;

String node_sub_menu[4]={"Set Day", "Set hour", "Set interval", "Exit subnode"};


void home_screen(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SMARTBIT   15:45");
  lcd.setCursor(0,1);
  lcd.print("        08/28/21");
 }


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


void main_menu() { 
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
              node1_conf_menu();
              break;
            case 1:
              node2_conf_menu();
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

void node1_conf_menu(){
  //{"Set Day", "Set hour", "Set interval", "Exit subnode"};
  int activeButton = 0;
  int menu_index = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Node_1 conf");
  lcd.setCursor(0, 1);
  lcd.print(">");
  lcd.setCursor(2, 1);
  lcd.print(node_sub_menu[menu_index]);
 
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
          lcd.print(node_sub_menu[menu_index]);
          break;
        case 3:
          Serial.println("DOWN");
          menu_index+=1;
          lcd.setCursor(0, 1);
          lcd.print(">                ");
          lcd.setCursor(2, 1);
          lcd.print(node_sub_menu[menu_index]);
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
              // SET NODE 1 DAY MENU
              node1_set_day();
              break;
            case 1:
              // SET RUN HOUR MENU
              break;
            case 2:
              // SET INTERVAL MENU
              break;
            case 3:
              node_menu();
              break;
          }
          break;
      }
    }
  }
}


void node2_conf_menu(){
  //{"Set Day", "Set hour", "Set interval", "Exit subnode"};
  int activeButton = 0;
  int menu_index = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Node_2 conf");
  lcd.setCursor(0, 1);
  lcd.print(">");
  lcd.setCursor(2, 1);
  lcd.print(node_sub_menu[menu_index]);
 
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
          lcd.print(node_sub_menu[menu_index]);
          break;
        case 3:
          Serial.println("DOWN");
          menu_index+=1;
          lcd.setCursor(0, 1);
          lcd.print(">                ");
          lcd.setCursor(2, 1);
          lcd.print(node_sub_menu[menu_index]);
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
              // SET DAY MENU
              break;
            case 1:
              // SET RUN HOUR MENU
              break;
            case 2:
              // SET INTERVAL MENU
              break;
            case 3:
              node_menu();
              break;
          }
          break;
      }
    }
  }
}

void node1_set_day(){
  int activeButton = 0;
  int menu_index = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Day Settings");
  lcd.setCursor(0, 1);
  lcd.print(">");
  lcd.setCursor(2, 1);
  lcd.print(days[menu_index]);
  lcd.setCursor(14, 1);
  lcd.print(node1_on_day[menu_index]);

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
          node1_on_day[menu_index]+=1;
          
          lcd.setCursor(0, 1);
          lcd.print(">                ");
          lcd.setCursor(2, 1);
          lcd.print(days[menu_index]);
          lcd.setCursor(14, 1);
          lcd.print(node1_on_day[menu_index]);
          break;
        case 2:
          Serial.println("UP");
          menu_index-=1;
          lcd.setCursor(0, 1);
          lcd.print(">                ");
          lcd.setCursor(2, 1);
          lcd.print(days[menu_index]);
          lcd.setCursor(14, 1);
          lcd.print(node1_on_day[menu_index]);
          break;
        case 3:
          Serial.println("DOWN");
          menu_index+=1;
          lcd.setCursor(0, 1);
          lcd.print(">                ");
          lcd.setCursor(2, 1);
          lcd.print(days[menu_index]);
          lcd.setCursor(14, 1);
          lcd.print(node1_on_day[menu_index]);
          break;
        case 4:
          Serial.println("LEFT");
          node1_on_day[menu_index]-=1;
          lcd.setCursor(0, 1);
          lcd.print(">                ");
          lcd.setCursor(2, 1);
          lcd.print(days[menu_index]);
          lcd.setCursor(14, 1);
          lcd.print(node1_on_day[menu_index]);
          break;
        case 5:  
          Serial.println("SELECT");
          button = 0;
          activeButton = 1;
          switch(menu_index){
            case 7:
              node1_conf_menu();
              break;
          }    
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
