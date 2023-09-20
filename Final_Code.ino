#include <Servo.h>                            // Library for Servo motors
#include <Wire.h>                             // Library for I2C protocol
#include <LiquidCrystal_I2C.h>                // Library for I2C LCD

Servo myservo;                                //servo as exit gate
Servo myservos;                                //servo as entry gate
LiquidCrystal_I2C lcd(0x3f,16,2);             // set the LCD Address

int carEnter  = D0;                          // entry sensor 
int carExited = D6;                         //exit sensor                
int slot1     = D7;
int slot2     = D3;
int count     = 0; 
int CLOSE_ANGLE = 100;         // The closing angle of the servo motor arm
int OPEN_ANGLE = 0;            // The opening angle of the servo motor arm              
int s1=0, s2=0;
int slot = 2;

boolean entrysensor, exitsensor;

void setup() 
{
  Serial.begin (9600); 
  Wire.begin(D2, D1);                            // i2c start
  myservo.attach(D8);                            // servo pin to D4
  myservos.attach(D5);                           // servo pin to D5 FOR ENTRY
  pinMode(carEnter, INPUT);                     // ir as input
  pinMode(carExited, INPUT);                      // ir as input
  pinMode(slot1, INPUT);
  pinMode(slot2, INPUT);
  lcd.begin(16,2);                              //begin lcd
  lcd.backlight();
  lcd.setCursor (0,0);
  lcd.print("  SMART PARKING   ");
  lcd.setCursor (0,1);
  lcd.print("     SYSTEM ");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Available Slot:");
  lcd.setCursor(0,1);
  lcd.print(slot);
  delay(3000);
  lcd.clear();
}
void loop()
{
  entrysensor= !digitalRead(carEnter);
  exitsensor = !digitalRead(carExited);
  s1 = digitalRead(slot1);
  s2 = digitalRead(slot2);

   if (entrysensor == 1 && count<2)
   {                                             
    count=  count+1; 
    lcd.setCursor(1,0);
    lcd.print(count);
    lcd.print(" Car Entered");
    myservos.write(OPEN_ANGLE);
    delay(3000);
    myservos.write(CLOSE_ANGLE);    
    lcd.clear();
    slot=slot - 1;
    lcd.setCursor(0,0);
    lcd.print("Available Slot: ");
    lcd.setCursor(0,1);
    lcd.print(slot);
    delay(3000);
    lcd.clear();
    if(count>=2)
    {
     delay(200);
     lcd.setCursor(1,0);
     lcd.print("Space Full");
     myservos.write(CLOSE_ANGLE);
    }
   }
   if (exitsensor == 1 && count>0) 
   {   
    count= count-1;                      
   if(count==1)
   {
    lcd.setCursor(1,0);
    lcd.clear();
    lcd.print(" 1 Space");  
    lcd.setCursor(1,1);
    lcd.print("Available");                                
    myservo.write(OPEN_ANGLE);
    delay(2500);
    myservo.write(CLOSE_ANGLE);
    lcd.clear();
    slot = slot + 1;
   }

   if(count==0)
   {
    lcd.setCursor(1,0);
    lcd.print("2 Space");  
    lcd.setCursor(1,1);
    lcd.print("Available");                                
    myservo.write(OPEN_ANGLE);
    delay(2500);
    myservo.write(CLOSE_ANGLE);
    lcd.clear();
    slot = slot + 1;
   }
 }
}
