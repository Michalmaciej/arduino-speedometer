#include <TimeLib.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);

const int timeZone = +1;

void setup() {
  // UART init
  Serial.begin(9600);

  // Led built in init for communication
  pinMode(LED_BUILTIN, OUTPUT);

  // LCD initialization
  lcd.init();
  lcd.backlight();

  Serial.println("Waiting for sync time:");
  takeTime();
}

void loop() {
  String time = "";
  time = time + hour() + ":" + minute() + ":" + second();

  String date = "";
  date = date + day() + "/" + month() + "/" + year();
  
  
  printTimeInSerial();
  printTimeOnLCD();


  delay(1000);
}

void takeTime() {
  // wait for message
  while(!Serial.available()) {delay(1);}

  unsigned long timeGiven = Serial.parseInt();

  //calculate time for current timezone
  timeGiven = timeGiven + (timeZone * 3600);

  setTime(timeGiven);
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void printTimeInSerial() {
  String clockTime = "";
  clockTime = clockTime + digitFormat(hour()) + ":" + digitFormat(minute()) + ":" + digitFormat(second());

  String date = "";
  date = date + digitFormat(day()) + "/" + digitFormat(month()) + "/" + digitFormat(year());

  String readyString = "";
  readyString = readyString + clockTime + " " + date;

  Serial.println(readyString);
}

void printTimeOnLCD() {
  String clockTime = "";
  clockTime = clockTime + digitFormat(hour()) + ":" + digitFormat(minute()) + ":" + digitFormat(second());

  String date = "";
  date = date + digitFormat(day()) + "/" + digitFormat(month()) + "/" + digitFormat(year());
  
  lcd.setCursor(3, 0);
  lcd.print(clockTime);

  lcd.setCursor(2, 1);
  lcd.print(date);
}

String digitFormat (int number)
{
  String output = "";
  if(number < 10)
  {
    output = output + 0;
  }
  output = output + number;
  return output;
}