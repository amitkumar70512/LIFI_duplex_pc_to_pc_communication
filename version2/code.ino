#include <SoftwareSerial.h>

// Set up a new SoftwareSerial object  SoftwareSerial GSerial (rxPin, txPin)   

SoftwareSerial GSerial(10,11);
void recv();
void transmit();
int c=0;
void setup()
{
 pinMode(10,INPUT);
Serial.begin(9600);
GSerial.begin(1000); // increase baud to reduce blink effect
Serial.println("Waiting...");
}

void loop()
{

if(Serial.available())
transmit();
if(GSerial.available())
recv();
}

void recv()
{
char r=GSerial.read();
Serial.print(r);
Serial.flush();
}

void transmit()
{
String a=Serial.readString();
int l=a.length();
Serial.print("\nTRANSMITTER : ");
Serial.println(a);
for(int i=0;i<l;i++)
{
GSerial.print(a[i]);
}

}
