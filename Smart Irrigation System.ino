#include <SoftwareSerial.h>

String apiKey = "6ZVL17YAGOVUSAUY";  
String Host_Name = "Abhishek";            
String Password = "abhishek1996"; 

SoftwareSerial ser(3, 2); 
int count1=0;
int count2=0;
int total_cost;
int sensor_pin = A0;
int output_value ;
#define RELAY1 7 
int pirSensor = 8;
int buzzer = 9;

void setup() {

Serial.begin(115200);                 
ser.begin(115200);                     

ser.println("AT+RST");               

char inv ='"';

String cmd = "AT+CWJAP";

       cmd+= "=";

       cmd+= inv;

       cmd+= Host_Name;

       cmd+= inv;

       cmd+= ",";

       cmd+= inv;

       cmd+= Password;


       
ser.println(cmd);

  pinMode(RELAY1, OUTPUT);

   Serial.println("Reading From the Sensor ...");

   delay(2000);
    pinMode(pirSensor, INPUT);
  pinMode(buzzer, OUTPUT);
  

   }

void loop()
{

   String y="RAJASTHAN DIGIFEST";
   output_value= analogRead(sensor_pin);

   output_value = map(output_value,550,0,0,100);

   Serial.print("Mositure : ");

   Serial.print(output_value);

   Serial.println("%");
   if(output_value<20&&output_value>10)
   {
    digitalWrite(RELAY1,HIGH);
    delay(300000);
    digitalWrite(RELAY1,LOW);
    count1=count1+1;
   }
   else if(output_value <50 &&output_value>40)
   {
    digitalWrite(RELAY1,HIGH);
    delay(10000);
    digitalWrite(RELAY1,LOW);
    count2=count2+1;
   }

   int cost=count1*10+ count2*5;
   total_cost=cost*2;
  
   y=String(total_cost);
    int sensorValue = digitalRead(pirSensor);
    if(sensorValue==1)
    {
      digitalWrite(buzzer,HIGH);
    }

     String cmd = "AT+CIPSTART=\"TCP\",\"";         

  cmd += "184.106.153.149";                       

  cmd += "\",80";                                 

  ser.println(cmd);

  Serial.println(cmd);

 if(ser.find("Error")){

    Serial.println("AT+CIPSTART error");

    return;

  }
  String getStr = "GET /update?api_key=";         // prepare GET string

  getStr += apiKey;

  getStr +="&field1=";

  getStr +=String (sensorValue);

   getStr +="&field2=";

   getStr +=String (y);

  getStr += "\r\n\r\n";

  cmd = "AT+CIPSEND=";

  cmd += String(getStr.length());                // Total Length of data

  ser.println(cmd);

  Serial.println(cmd);
  if(Serial.find(">")){

    Serial.print(getStr);

    Serial.print(getStr);

  }

  else{

    Serial.println("AT+CIPCLOSE");                  // closing connection

    Serial.println("AT+CIPCLOSE");

  }

   delay(1000);

   }
