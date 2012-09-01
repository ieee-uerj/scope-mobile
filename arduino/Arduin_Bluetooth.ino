#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3); // RX, TX

const int SIZE_ARRAY = 101;

volatile int intArray[SIZE_ARRAY];
volatile int counter = 0;

void setup ()
{
  Serial.begin(9600);
  mySerial.begin(115200);
  setupInterruption();
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


  if (counter >= SIZE_ARRAY)
  {
    stopInterruption();
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
    startInterruption();
  }
}
 

ISR(TIMER1_COMPA_vect)
{
  intArray[counter++] = analogRead(A0);
}

void stopInterruption()
{
  TIMSK1 = 0;
}

void startInterruption()
{
  TIMSK1 |= (1 << OCIE1A);
}

void setupInterruption()
{
    // initialize Timer1 48kHz
    cli();          // disable global interrupts
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B
 
    // set compare match register to desired timer count:
    OCR1A = 40;
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 8 prescaler:
    //TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS11); 
    //TCCR1B |= (1 << CS12);
    // enable timer compare interrupt:
    TIMSK1 |= (1 << OCIE1A);
    sei();          // enable global interrupts  
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

