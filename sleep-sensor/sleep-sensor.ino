#include <CapacitiveSensor.h>

CapacitiveSensor sensor = CapacitiveSensor(4,2);

// Define the number of samples to keep track of. The higher the number, the
// more the readings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the readings array.
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

void setup()                    
{
   Serial.begin(9600);
   
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop()                    
{
  // read from the sensor:
  readings[readIndex] = sensor.capacitiveSensor(20);
  total = total + readings[readIndex];
  
  // advance to the next position in the array:
  readIndex = readIndex + 1;
  
  // if we're at the end of the array...
  if (readIndex >= numReadings) {
      
    // calculate the average:
    average = total / numReadings;
    
    // send it to the computer as ASCII digits
    Serial.print( "average " );
    Serial.println(average);
    
    readIndex = 0;
    total = 0;
  }
  else{
    // add the reading to the total:
    total = total + readings[readIndex];
  }

  delay(10);       
}
