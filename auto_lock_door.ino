// Importation des bibliothèques 
#include<Keypad.h> //Clavier
#include <Wire.h>
#include <LiquidCrystal_I2C.h> //Ecran LCD

LiquidCrystal_I2C lcd(0x3F,20,4);

// Caractères du clavier
char keys[4][3]={
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'*','0','#'}};
 
byte rowPin[4]={6,7,8,9};
byte colPin[3]={3,4,5};

String password = "1234";  // Le mot de passe. Il peut être modifié 
int position = 0; // Pointeur indiquant la position du caractère saisie dans le mot de passe

int wrong = 0; // Variable permettant de calculer le nombre de tentatives ratées

int redPin = 10; // Sortie indiquant que la porte est bloquée
int greenPin = 11; // Sortie indiquant que la porte est ouverte
int buzzer = 12; // Sortie de l'alarme
 
Keypad keypad=Keypad(makeKeymap(keys),rowPin,colPin,4,3);
// Mapping du clavier

int total = 0; // nombre de tentatives ratées totale
// Initialisation 
void setup(){
  
 pinMode(redPin,OUTPUT);
 pinMode(greenPin,OUTPUT);
 pinMode(buzzer, OUTPUT);
 lcd.init(); //Initialisation du lcd
 lcd.backlight();
 lcd.clear(); // Reinitialisation de l'écran
 setLocked(true); // Verrouillage
 delay(20);
}

void loop(){
  
  lcd.clear(); // Reinitialisation de l'écran
  lcd.print(" Entrer le code : ");
  delay(100);
  char pressed=keypad.getKey();//Récuperation de la touche pressée
  String key[3];
  
  if(pressed){
    if(pressed == '#'){ // Verrouillage à l'appui de la touche #
          position = 0; // Reinitilisation du pointeur
          setLocked(true); // Verrouillage
          lcd.clear(); // Reinitialisation de l'écran
      }

     else if(pressed == password[position]){ // Le caractère pressé est dans le bon ordre 
          key[position]=pressed;
          position++; // Incrémentation du pointeur
      }
 
     else if (pressed != password[position] ) // Le caractère n'est pas dans le bon ordre
      {
          wrong++; // Incrémentation du nombre d'échecs
          position ++; // Incrémentation du pointeur
      }

    if(position == 4){
          if( wrong >0) // Le mot de passe inséré n'est pas le bon
            {
                
                total++; // Incrémentation du nombre global d'echecs
                wrong = 0; // Reinitialisation du compteur
                position = 0; // Reinitilisation du pointeur
                lcd.clear(); // Reinitialisation de l'écran LCD
                lcd.setCursor(0,1);
                lcd.print("  CODE ERRONE!");
                lcd.setCursor(0,2);
                lcd.print("  ESSAIS RESTANTS: ");
                lcd.setCursor(19,2);
                lcd.print(3-total);
                setLocked(true); // Vérouillage
            }

          else if(position == 4 && wrong == 0) // Le mot de passe inséré est le bon
            {
                buzzer_beep_unlock(); // Dévérouillage
            }

             if(total ==3){ // 3 Echecs successifs
                total=0;  // Reinitialisation du nombre total d'échecs
                buzzer_beep_lock(); // Déclenchement de l'alarme
            }

        }

   }

   
}

void setLocked(int locked){ // Fonction de vérouillage/dévérouillage de la porte
    if (locked){ // vérouillage
          digitalWrite(redPin, HIGH); // LED de vérouillage à 1
          digitalWrite(greenPin, LOW); // LED de dévérouillage à 0
          delay(2000);
      }
    else{ //dévérouillage
          digitalWrite(redPin, LOW); // LED de vérouillage à 0
          digitalWrite(greenPin, HIGH); // LED de dévérouillage à 1
          delay(5000);
          digitalWrite(redPin, HIGH); // LED de vérouillage à 1
          digitalWrite(greenPin, LOW); // LED de dévérouillage à 0
      }
  }
void buzzer_beep_lock(){ // Fonction alarme
   lcd.clear(); // Reinitialisation de l'écran
   lcd.setCursor(0,1);
   lcd.print("   ACCES REFUSE !!!");
   // Déclenchement de l'alarme pendant 10 secondes
   digitalWrite(buzzer,HIGH);
   delay(10000);
   digitalWrite(buzzer,LOW);
   
}
void buzzer_beep_unlock(){ // Fonction alarme
   position = 0; // Reinitilisation du pointeur
   wrong = 0; // Reinitialisation du compteur
   lcd.clear(); // Reinitialisation de l'écran LCD
   lcd.setCursor(0,1);
   lcd.print("      BIENVENUE!     ");
   digitalWrite(buzzer,HIGH);
   delay(100);
   digitalWrite(buzzer,LOW);
   setLocked(false); // Dévérouillage
   
}
