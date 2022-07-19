 #include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  
  pinMode(A0,INPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
}

int i = 0;
int c = 0;
void loop()
{
  
  i = analogRead(A0);
  Serial.println(i);
  delay(500);
  if(i>100)
  {
    c = 1;
    digitalWrite(5,1);
    tone(6,1000,1000);
    sent_sms();
    
  }
  else
  {
    digitalWrite(5,0);
  }

  if(c==1)
  {
    i = 0;
    c = 0;
    delay(1000);
  }
  
}



void sent_sms()
{
     mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     mySerial.println("AT+CMGS=\"+916305809415\"\r"); // Replace x with mobile number
     delay(1000);
     
     mySerial.println("Alert!!! \n Some one is trying to Hang!!!");// The SMS text you want to send
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
}
