// Loading libraires
#include<Keypad.h> //Keypad
#include <Wire.h> // Wire
#include <LiquidCrystal_I2C.h> //LCD screen

LiquidCrystal_I2C lcd(0x3F,20,4);

// Keypad characters
char keys[4][3]={
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'*','0','#'}};
 
byte rowPin[4]={6,7,8,9};
byte colPin[3]={3,4,5};

String password = "1234";  // Password 
int position = 0; // Character's password positiion

int wrong = 0; // Failed attempt counter

int redPin = 10; // Locked door output
int greenPin = 11; // Opened door output
int buzzer = 12; // Alarm output

// Keypad mapping 
Keypad keypad=Keypad(makeKeymap(keys),rowPin,colPin,4,3);

int total = 0; // Failed attempt overall
// Initialization 
void setup(){
  
 pinMode(redPin,OUTPUT);
 pinMode(greenPin,OUTPUT);
 pinMode(buzzer, OUTPUT);
 lcd.init(); //LCD initialization
 lcd.backlight();
 lcd.clear(); // Clear LCD screen
 setLocked(true); // Locking
 delay(20);
}

void loop(){
  
  lcd.clear(); // Clear LCD screen
  lcd.print(" Enter the code : ");
  delay(100);
  char pressed=keypad.getKey();//Get the inpur
  String key[3];
  
  if(pressed){
    if(pressed == '#'){ // The door is lock if we press '#'
          position = 0; // Clear character's password position
          setLocked(true); // Locked
          lcd.clear(); // Clear LCD screen
      }

     else if(pressed == password[position]){ //The character is in the right order 
          key[position]=pressed;
          position++; // Incrementation of the position
      }
 
     else if (pressed != password[position] ) // The character is in the wrong order 
      {
          wrong++; // Incrementation of failed attempt counter
          position ++; // Incrementation of the position
      }

    if(position == 4){
          if( wrong >0) // The password is wrong
            {
                
                total++; // Incrementation of the overall failed attempt
                wrong = 0; // clear counter
                position = 0; // Clear character's password position
                lcd.clear(); //  Clear LCD screen 
                lcd.setCursor(0,1);
                lcd.print("  WRONG CODE!");
                lcd.setCursor(0,2);
                lcd.print("  LEFT ATTEMPTS: ");
                lcd.setCursor(19,2);
                lcd.print(3-total);
                setLocked(true); // Vérouillage
            }

          else if(position == 4 && wrong == 0) // The code is right
            {
                buzzer_beep_unlock(); // Unlock the door
            }

             if(total ==3){ // 3 failed attempt in a row
                total=0;  // clear counter
                buzzer_beep_lock(); // Start the alarm
            }

        }

   }

   
}

void setLocked(int locked){ // Lock/unlock function
    if (locked){ // Lock
          digitalWrite(redPin, HIGH); // Set Lock LED to  1
          digitalWrite(greenPin, LOW); // Set Unlock LED to  0
          delay(2000);
      }
    else{ //Unlock
          digitalWrite(redPin, LOW); // Set Lock LED to  0
          digitalWrite(greenPin, HIGH); //Set Unlock LED to  1
          delay(5000);
          digitalWrite(redPin, HIGH); // Set Lock LED to  1
          digitalWrite(greenPin, LOW); // Set Unlock LED to  0
      }
  }
void buzzer_beep_lock(){ // Alarm
   lcd.clear(); // Clear LCD Screen
   lcd.setCursor(0,1);
   lcd.print("   ACCESS DENIED !!!");
   // Start alarm during 10 seconds
   digitalWrite(buzzer,HIGH);
   delay(10000);
   digitalWrite(buzzer,LOW);
   
}
void buzzer_beep_unlock(){ // Alarm
   position = 0; // Clear character's password position
   wrong = 0; // Clear counter
   lcd.clear(); // Clear LCD Screen
   lcd.setCursor(0,1);
   lcd.print("      WELCOME!     ");
   digitalWrite(buzzer,HIGH);
   delay(100);
   digitalWrite(buzzer,LOW);
   setLocked(false); // unlock
   
}
