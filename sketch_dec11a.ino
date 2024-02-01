#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define card "0A 9F FE BE"
#define tag "AC 0F EF 5B"
#define card2 "23 2F B4 18"
#define card3 "C3 01 B8 18"
#define card4 "D3 85 A8 18"

MFRC522 mfrc522(SS_PIN, RST_PIN);

const int buttonPin = 6;     // the number of the pushbutton pin
const int ledPin =  7;      // the number of the LED pin
int x=0;
int y=0;
int buttonState = 0; 
int b = 0;

void setup() {
  // put your setup code here, to run once:
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Approximate your card to the reader...");
  Serial.println();


}

void loop() {
  // put your main code here, to run repeatedly:
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
   return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  delay(2000);

  if (content.substring(1) == tag ) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized Doctor access to this card");
    
  }

  else if (content.substring(1) == card && x==0) //change here the UID of the card/cards that you want to give access
  { 
    if(y==0){
      y=1;
      Serial.println("Serial 1 access to this card");
    }
    else{
      y=0;
      Serial.println("Next is 2");
      x++;
    }
    
    
  }

  else if (content.substring(1) == card2 && x==1) //change here the UID of the card/cards that you want to give access
  { 
    if(y==0){
      y=1;
      Serial.println("Serial 2 access to this card");
    }
    else{
      y=0;
      Serial.println("Next is 3");
      x++;
    }
    
    
  }

  else if (content.substring(1) == card3 && x==2) //change here the UID of the card/cards that you want to give access
  { 
    if(y==0){
      y=1;
      Serial.println("Serial 3 access to this card");
    }
    else{
      y=0;
      Serial.println("Next is 4");
      x++;
    }
    
    
  }

  else if (content.substring(1) == card3 && x==3) //change here the UID of the card/cards that you want to give access
  { 
    if(y==0){
      y=1;
      Serial.println("Serial 3 access to this card");
    }
    else{
      y=0;
      Serial.println("Next is 1");
      x=0;
    }
    
    
  }
  
  else   
  {
    Serial.println(" Access denied");
    delay(1000);
    
   }

  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    
    if(b==0){
      b = 1;
    }
    else{
      b=0;
    }
    
    if(b==1){
    digitalWrite(ledPin, HIGH);
    } 
    else{
      digitalWrite(ledPin, LOW);
    }
  }

}
