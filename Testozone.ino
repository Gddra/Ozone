
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(11,12);

#define relayPin 13

#include <LiquidCrystal_I2C.h> // Library for LCD
// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); // Change to (0x27,16,2) for 16x2 LCD.

#define relayType 'L' // Relay trigger type. L for low and H for high
#define TogglePin 6 // the pin where start switch is connected

String counttime;
String value;
int values;

/////////

int firstTime = 1;
int firstToggle = 1;
unsigned long CountDown = 2000;
int relayState = 0;
int FinishBeep = 1;
int InProcess = 0;
float StartTime = 0.0;
int i = 0;
int Cmin = 0;
int Csec = 0;
char str[16];
float SetTimeSec = 0.0; 
//float IncrementButton = 300000; // [millisec] 300 sec = 5 min
float IncrementButton = 60000.0; // [millisec] 60 sec = 1 min
float OzoneTurnOnTime = 3000000.0; // Turn-On Time for Ozone Generator = 50 min = 3000 sec

void setup() {
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();

  
  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, LOW);


  BTSerial.begin(9600);

  Serial.begin(9600);

  Serial.print("ready");
  

    Serial.begin(9600);// initialize serial monitor with 9600 baud
  if(relayType == 'L') {
      digitalWrite(relayPin, LOW);// turn the relay OFF and keep it OFF
      Serial.println("Relay Timer"); 
      Serial.println("Relay Type: LOW Trigger");      
  }else{
      digitalWrite(relayPin, HIGH);// turn the relay OFF and keep it OFF
      Serial.println("Relay Timer"); 
      Serial.println("Relay Type: HIGH Trigger");
        } 
  lcd.setCursor(0, 0); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรตำแหน่งที่0 แถวที่ 1 เตรียมพิมพ์ข้อความ
  lcd.print("Ozone Sterilizer"); //พิมพ์ข้อความ 
  lcd.setCursor(0, 1); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรกำแหน่งที0 แถวที่ 2 เตรียมพิมพ์ข้อความ
  lcd.print("TSE:Thammasat U."); //พิมพ์ข้อความ 
  delay(4000);

  
}

void loop() {
   if (firstTime==1) {
      lcd.setCursor(0, 0); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรตำแหน่งที่0 แถวที่ 1 เตรียมพิมพ์ข้อความ
      lcd.print("-- Bluetooth -- "); 
      lcd.setCursor(0, 1); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรกำแหน่งที0 แถวที่ 2 เตรียมพิมพ์ข้อความ
      lcd.print("    is ready!!    "); 
      delay(2000);
      SetTimeSec = 0; 
      firstTime = 0;
    
   }

   if ( BTSerial.available()) {

      SetTimeSec = 0; 
      firstTime = 0;
      value = BTSerial.readString();

    
   if (value == "ปิด" ) {
      digitalWrite(relayPin, LOW);
      Serial.print("close \n");
      Serial.print(value);
      
    }

     if (value == "เปิด" ) {
      digitalWrite(relayPin, HIGH);
      Serial.print("open \n");
      Serial.print(value);
     }
     
    else {

      values = value.toInt();
      
    if (values >0){
      while (values > 0) {
          
          Serial.print("CountDown time: ");
    
          //Serial.print(" ");
          Serial.print(values);
          Serial.println(" Seconds");
          lcd.setCursor(0, 0); 
          lcd.print("Countdown (Sec) "); //พิมพ์ข้อความ 
          lcd.setCursor(0, 1); 
          lcd.print(values); //พิมพ์ข้อความ 
          delay(1000);
          values = values - 1;
      }
      digitalWrite(relayPin, HIGH);
      Serial.print("open \n");
      Serial.print(value);
    }

     }
      
      lcd.setCursor(0, 0); 
      lcd.print("Ozone Sterilizer"); //พิมพ์ข้อความ 
      lcd.setCursor(0, 1); 
      lcd.print("   is working   "); //พิมพ์ข้อความ 
   
    }
   }


   
