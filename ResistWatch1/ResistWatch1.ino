#define ATTINY84
#define SWITCH 10
#define NUMphone 2
#define LOCREFRESH 60//time in secs
#define gsmtx 2
#define gsmrx 3
#include "SoftwareSerial.h"
SoftwareSerial gsm(gsmrx, gsmtx);
#define RI
unsigned long int time = millis();
const char numbers[NUMphone][11] = {
"9718972200",
"9899500189"
};
const char SMSText[] = {"HELP me Location: "};
const char LINK[] = { "www.google.co.in/maps/?q="};
char location[30]={"#"};
volatile byte alarm=0;

void setup() {
  gsm.begin(9600);
  delay(500);
//  gsm.print(F("AT+QIDEACT\r\n"));
  delay(1000);
  // connect2internet();
  gsm.print(F("AT+CMGF=1\r\n"));
  delay(1000);
  gsm.print(F("AT+CFUN=1\r\n"));
  delay(1000);
  getLocation();

  gsm.print(location);
attachInterrupt(0,ALARM,RISING);
}
void ALARM(){  
alarm=1;  
}
void getLocation() {
  gsm.print(F("AT+QCELLLOC=1;\r\n"));
  for (int i =0; i < 8000; i++) {
    delayMicroseconds(1000);
  }
  byte flag = 0;
  byte i = 0;
  if (gsm.available()) {
    while (gsm.available()) {
      if (gsm.peek() == ':') {
        flag = 1;gsm.read();gsm.read();
      }
      else if (flag != 1) {
        gsm.read();
      }
      if (flag == 1) {
        location[i++] = (char)gsm.read();
        if(location[i]=='\n'||location[i]=='\r'){break;}
      }
    }
  }
if(flag==1){  location[i] = '\0';}
//find comma loc and invert
byte comma=0;
for(i =0;location[i]!='\0';i++){  
if(location[i]==','){comma=i;break;}    
}
for(i =0;i<comma;i++){
byte temp=location[i];
location[i]=location[comma+i+1];
location[comma+i+1]=temp;
  }
}


void ACT() {
    char end[] = {(char)26, '\0'};

  for (byte i = 0; i < NUMphone; i++)    {
    gsm.print(F("AT+CMGS=\""));
    gsm.print(numbers[i]);
    gsm.print("\"\r\n");
  for (int i =0; i < 1000; i++) {
    delayMicroseconds(1000);
  }
    for (byte i = 0; SMSText[i] != '\0'; i++) {
      gsm.print(SMSText[i]);
    }

    for (byte i = 0; LINK[i] != '\0'; i++) {
      gsm.print(LINK[i]);
    }
    for (byte i = 0; location[i] != '\0'; i++) {
      gsm.print(location[i]);
    }
    for (byte i = 0; i < 2; i++) {
      gsm.print(end[i]);
    }
    time = millis();
  for (int i =0; i < 5000; i++) {
    delayMicroseconds(1000);
  }
  }
    //CALLLLALALLALALLALALALAALAl
    gsm.print(F("ATD"));
    gsm.print(numbers[NUMphone - 1]);
    gsm.print(F(";\r\n"));
  for (int i =0; i < 5000; i++) {
    delayMicroseconds(1000);
  }
    gsm.print(F("AT+QAUDCH=1\r\n"));  

}
void loop() {

if(millis()-time>LOCREFRESH*1000){
  time=millis();
  getLocation();
  gsm.print(location);
}
if(digitalRead(SWITCH)==1){alarm=1;}
  if(alarm==1){alarm=0;ACT();}
}
