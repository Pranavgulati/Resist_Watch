#define ATTINY84
#define BUTTON 1
#define NUMphone 2
#include <SoftwareSerial.h>
SoftwareSerial gsm(8,9);
const char PROGMEM numbers[NUMphone][11]={  
  "9718972200",
  "9711487327"
  };
const char PROGMEM SMSText[]="HELP ME,In danger,Location:";
const char PROGMEM LINK[]="www.google.co.in/maps/?q=";
void setup() {
gsm.begin(9600);
Serial.begin(9600);
}
String getLocation(){
  String location;
  gsm.write("AT+QCELLLOC=1\r\n");
  delay(1000);
  String temp;
  if(gsm.available()){
  while(gsm.available()){temp+=(char)gsm.read();}
       }
       location=temp.substring(temp.indexOf(':'),temp.indexOf('\r'));
   
return location;  
}
void loop() {
  char end[]={(char)26,'\0'};
  String location;
location=getLocation();
Serial.println(location);
//sending sms 
//  if(digitalRead(BUTTON)==1){  
//for(byte i=0;i<NUMphone;i++)    {
//    gsm.write("AT+CMGS=\"");
//    gsm.write(numbers[i]);
//    gsm.write("\"\r\n");
//    delay(1000);
//    gsm.write(SMSText);
//    gsm.write(LINK);
//    gsm.write(location);
//    gsm.write(end);
//}
//    }
}
