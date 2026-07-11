#include<LiquidCrystal.h>
LiquidCrystal lcd(3,4,5,6,7,8);
#include<DHT.h>
# define Type DHT11
int sensepin=2;
DHT HT(sensepin,Type);
float temp;
float humidity;
int buttonread1;
int buttonread2;
int count1=0;
int count2=0;
int temp1;
int temp2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   pinMode(12,INPUT);
  pinMode(9,INPUT);
  HT.begin();
  lcd.begin(16,2);
 

}

void loop() {
  // put your main code here, to run repeatedly:
    buttonread1=digitalRead(12);
    Serial.println(buttonread1);
  delay(50);
   buttonread2=digitalRead(9);
    Serial.println(buttonread2);
  delay(50);
   temp= HT.readTemperature();
  humidity= HT.readHumidity();
//    lcd.setCursor(0,0);
//    lcd.print("HUMIDITY=");
//    lcd.print( humidity);
//    lcd.setCursor(0,1);
    if(buttonread1==0){
      count1++;
      temp1=temp+count1;
      if(temp1==){
        lcd.setCursor(0,0);
        lcd.print("FAVOURABLE");
      }
      if(temp1!=45){
        lcd.setCursor(0,0);
        lcd.print("UNFAVOURABLE");
      }
    }
      lcd.setCursor(0,1);
      lcd.print("TEMPEATURE=");
      lcd.print(temp1);
    if(buttonread2==1){
      count2++;
      temp2=temp1-count2;
      if(temp2==45){
        lcd.setCursor(0,0);
        lcd.print("FAVOURABLE");
      }
      if(temp2!=45){
        lcd.setCursor(0,0);
        lcd.print("UNFAVOURABLE");
      }
    }
      lcd.setCursor(0,1);
      lcd.print("TEMPEATURE=");
      lcd.print(temp1);
     
}
