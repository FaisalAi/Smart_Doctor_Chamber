#include <LiquidCrystal_I2C.h>

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h> 

#define SS_PIN 10
#define RST_PIN 9
#define card "0A 9F FE BE"
#define tag "AC 0F EF 5B"
#define card2 "23 2F B4 18"
#define card3 "C3 01 B8 18"
#define card4 "D3 85 A8 18"

MFRC522 mfrc522(SS_PIN, RST_PIN);


const int led1 =  6;
const int led2 =  7;
int btn =  5; 
int servo =  3;     
int x=0;
int y=0;
int buttonState = 0; 
int b = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo s1;
void setup() {
  s1.attach(servo);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(btn, INPUT);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin(); 
  lcd.backlight();
  lcd.clear();                 
  lcd.setCursor(0, 0);         
  lcd.print("Welcome To You"); 
  lcd.setCursor(0, 1);         
  lcd.print("Scan Your Card");       
  s1.write(0);


}

void loop() {

  buttonState = digitalRead(btn);

  if (buttonState == LOW) {
    delay(500);
    if(b==0){
      b = 1;
    }
    else{
      b=0;
    }
    
    if(b==1){
    digitalWrite(led1, HIGH);
    } 
    else{
      digitalWrite(led1, LOW);
    }
  } 
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
   return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  lcd.clear();                 
  lcd.setCursor(0, 0);         
  lcd.print("Card Scaned");
  digitalWrite(led2, HIGH);
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));

  }
  
  content.toUpperCase();
  
  delay(2000);

  if (content.substring(1) == tag ) 
  {
   
    lcd.setCursor(0, 1);        
    lcd.print("Welcome Doctor!!");
    s1.write(90); 
      delay(1000); 
     
      s1.write(0);
    digitalWrite(led2, LOW);
    
  }

  else if (content.substring(1) == card && x==0) 
  { 
    digitalWrite(led2, LOW);
    if(y==0){
      y=1;
      lcd.setCursor(0, 1);
      lcd.print("Serial 1 can go"); 
      s1.write(90); 
      delay(1000); 
     
      s1.write(0); 
      Serial.println("1");
      
    }
    else{
      y=0;
      lcd.setCursor(0, 1);        
      lcd.print("Serial 1 Done");
      s1.write(90); 
      delay(1000); 
     
      s1.write(0); 
      lcd.setCursor(0, 2);         
      lcd.print("Next is 2");
      Serial.println("1");
      x++;
    }
    
    
  }

  else if (content.substring(1) == card2 && x==1)
  { 
    digitalWrite(led2, LOW);
    if(y==0){
      y=1;
      lcd.setCursor(0, 1);        
      lcd.print("Serial 2 can go");
      s1.write(90); 
      delay(1000); 
     
      s1.write(0); 
      Serial.println("2");
    }
    else{
      y=0;
      lcd.setCursor(0, 1);        
      lcd.print("Serial 2 Done");
      s1.write(90); 
      delay(1000); 
     
      s1.write(0); 
      lcd.setCursor(0, 2);        
      lcd.print("Next is 3");
      Serial.println("2");
      x++;
    }
    
    
  }

  else if (content.substring(1) == card3 && x==2)
  { 
    digitalWrite(led2, LOW);
    if(y==0){
      y=1;
      lcd.setCursor(0, 1);       
      lcd.print("Serial 3 can go");
      s1.write(90); 
      delay(1000); 
     
      s1.write(0); 
      Serial.println("3");
    }
    else{
      y=0;
      lcd.setCursor(0, 1);   
      lcd.print("Serial 3 Done");
      s1.write(90); 
      delay(1000); 
     
      s1.write(0); 
      lcd.setCursor(0, 2);  
      lcd.print("Next is 4");
      Serial.println("3");
      x++;
    }
    
    
  }

  else if (content.substring(1) == card4 && x==3)
  { 
    digitalWrite(led2, LOW);
    if(y==0){
      y=1;
      lcd.setCursor(0, 1);      
      lcd.print("Serial 4 can go");
      s1.write(90); 
      delay(1000); 
     
      s1.write(0); 
      Serial.println("4");
    }
    else{
      y=0;
      lcd.setCursor(0, 1);  
      lcd.print("Serial 4 Done");
      s1.write(90); 
      delay(1000); 
     
      s1.write(0); 
      lcd.setCursor(0, 2);   
      lcd.print("Next is 1");
      Serial.println("4");
      x=0;
    }  
  }
  
  else   
  {
    lcd.setCursor(0, 1);        
    lcd.print("Wrong Card");
    lcd.setCursor(0, 2);         
    lcd.print("Access denied");
    digitalWrite(led2, LOW);
    delay(1000);
    
   }
}
