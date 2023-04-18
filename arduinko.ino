#include <TimeLib.h>

#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

int g;
int m;
int s;

void setup()  {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  setSyncProvider( requestSync);  //set function to call when sync required
  Serial.println("Waiting for sync message");
  pinMode(10, OUTPUT);
  //HH:ii:ss
  //23:11:25
  //godzinaBudzika
  String a = "23:11:25";
  
}

void loop(){    
  if (Serial.available()) {
    processSyncMessage();
  }
  if (timeStatus()!= timeNotSet) {
    digitalClockDisplay();  
  }
  if (timeStatus() == timeSet) {
    digitalWrite(13, HIGH); // LED on if synced
  } else {
    digitalWrite(13, LOW);  // LED off if needs refresh
  }
  if (second() %2 == 0)
  {
    tone(10, 1000);
    delay(1000);
    noTone(10);
  }
  
  delay(1000);
  
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
  
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
       setTime(pctime); // Sync Arduino clock to the time received on the serial port
     }
  }
}

time_t requestSync()
{
  Serial.write(TIME_REQUEST);  
  return 0; // the time will be sent later in response to serial mesg
}

void pobierzCzas()
{
  Serial.println("Podaj godzine: HH:MM:SS");
  if(Serial.available() > 0)
  {
    String received = Serial.readStringUntil('\n');
    char* params = strchr(received, ':');

    Serial.print("Godzina: ");
    Serial.println(params[0]);
  }
}