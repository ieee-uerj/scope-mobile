#include <SoftwareSerial.h>

#define OWNER /*owner of global variables*/
#include <global.h>
#include <prototypes.h>

SoftwareSerial mySerial(2,3); // RX, TX

void setup ()
{
  Serial.begin(9600); /* WHY TWO BAUD RATES!?*/
  mySerial.begin(BAUDRATE);
  memset( (void *)ADCBuffer, 0, sizeof(ADCBuffer) ); /* Clear the buffer*/
  ADCCounter = 0; /* Set pointer to begin */
  counter = 0;
  setupTimerInterruption();
  setupADC();
}   

void loop ()
{
 
  /*if (mySerial.available())
    Serial.write(mySerial.read());*/
  
  /*if (Serial.available())
    mySerial.write(Serial.read());
    
  for (int j = 0; j < SIZE_ARRAY; j++)
  {  
     intArray[j] = analogRead(A0);
  } */


  /*if (counter >= SIZE_ARRAY)
  {
    stopTimerInterruption();
    mySerial.flush();
    mySerial.print("A%");  
    for (int j = 0; j < SIZE_ARRAY; j++)
    {
      mySerial.print(intArray[j]);   
      mySerial.print("%");
      //mySerial.print(intArray[j++]);   
      //mySerial.print("%");
      delay(40);  
    } 
    for (int j = 0; j < SIZE_ARRAY; j++)
    {
      intArray[j] = 0; 
    }
    counter = 0;
    startTimerInterruption();
  }*/
}

String concatSensorValue(int sensorValue)
{
  String aux;
  switch(String(sensorValue).length())
  {
    case 1:
      aux += "000";
      aux += sensorValue;
      return aux;
    case 2:
      aux += "00";
      aux += sensorValue;
      return aux;
    case 3:
      aux += "0";
      aux += sensorValue;
      return aux;
    default:
      aux += sensorValue;
      return aux;
  }  
}

