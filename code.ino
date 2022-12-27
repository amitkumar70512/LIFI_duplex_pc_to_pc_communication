// author: amit kumar
// upload this code to both sender and receiver pc , make connections as mentioned and thats all ,  both pc are now ready to share data

int incomingByte = 0; // serial data that is receive from serial monitor
const int rxspeed=5; // Feel free to lower this value to increase the transmission speed. 
// You need to lower it on both receiver and transmitter

const int five = 5;

const int LED =13;  
const int ldr = 12;
int a[7];
unsigned long mili =millis();

void setup() 
{
  pinMode(LED, OUTPUT); 
  Serial.begin(1000000); 
}

void loop() 
{
  
  if(digitalRead(ldr)==LOW)   //beginning of transmission
    receive();
  if (Serial.available()) 
  transmit();
  
}


//function definition to convert binary array to integer

void transmit(){
  
    incomingByte = Serial.read(); //read one character
    int b[10], i ;       
    for(i = 0; incomingByte > 0; i++)    
    {    
      b[i] = incomingByte%2;    
      incomingByte = incomingByte/2;  
    }    
  
    for(i = i-1; i >= 0; i--) // loop for 8 bit
    {   
      digitalWrite(LED, HIGH); // trigger Signal
      delay(five);
      digitalWrite(LED, b[i]); // bit signal either High or Low
      delay(2 * five); 
      digitalWrite(LED, LOW); // turn down the Led before next Bit
      delay(2 * five);
    }    
    Serial.flush();
}



void receive(){
  int j=0;
  for (int i=0;i<7;i++)
    {
      mili=millis();
      while((digitalRead(ldr)!=LOW)&&(i!=7))
      if  (millis()-mili>3*rxspeed)  //stops
      {
        i=7;
        Serial.println(" ") ;
         //this is to wait for the next signal
      }
      delay(2*rxspeed);
      a[i]=!digitalRead(ldr);
      delay(2*rxspeed);

      j++;
    }
     // want to skip enter
   
    int m=decimal(a);

    char l= char(m);
    Serial.print(l);

Serial.flush();
}


int decimal(int c[])
{
 int i, j=0 , decimal=0, temp;
  for(i=6;i>=0;i--)
  {
    temp=c[i];
    for(int m=0;m<j;m++) temp=temp*2; //power j times, j is the digit position from the right
    decimal=decimal +temp;
    j++;
  }
  
  return decimal;
  }
