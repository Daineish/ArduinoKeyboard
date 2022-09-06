/*
  Piezo Keyboard

  This sketch reads multiple piezo sensors and prints to serial when
  a gesture is recorded.

  Ideally this will be extended to be a somewhat-functional wearable keyboard.

  1MΩ resistor between ground and input to piezo sensors. Sensors to analog
  inputs on Arduino Uno.
*/

// Currently only have 2 sensors connected to A0 and A1. Can expand up to A5 right now.
const static int sensorList[6] = {A0, A1, A2, A3, A4, A5};
const int numSensors = 2;

// A list corresponding to sensors recording how many cyles left to delay read for
static int delayList[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// How many cycles to delay another input for. I'm getting multiple readings
// on input sometimes. Likely need to play with delayCyles + threshold + loopDelay
const static int delayCycles = 10;

// Threshold for piezo sensor to detect input
const int threshold = 100;

// How many ms to delay loop()
const int loopDelay = 10;

void setup()
{
  Serial.begin(115200);       // use the serial port
  Serial.println("Setup complete\n");
}

// Record data to send to serial. Only send data when all
// sensors are pressed simultaneously.
// chars 0-9 correspond to each piezo sensor (up to 10).
String dataSend = "";

void loop()
{
  bool pressAll = true;
  for(int i = 0; i < numSensors; i++)
  {
    // read data from sensor
    const int sensorReading = analogRead(sensorList[i]);

    if(sensorReading >= threshold)
    {
      if(delayList[i] == 0)
      {
        // if we don't have to delay this input, we can append to dataSend
        dataSend += String(i);
        delayList[i] = delayCycles; // Delay for x cycles
      }
    }
    else if(delayList[i] > 0)
    {
      // otherwise, if we still have delay left, decrement
      delayList[i]--;
    }

    if(sensorReading < threshold)
      pressAll = false;
  }

  if(pressAll)
  {
    // currently using this as a gesture to send input
    // to serial.
      Serial.println(dataSend);
      dataSend = "";
  }
 
  delay(loopDelay);
}
