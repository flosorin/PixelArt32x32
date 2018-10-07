#include <RGBMatrix.h>
#include <SoftwareSerial.h>

RGBMatrix screen = RGBMatrix();
SoftwareSerial bluetoothSerial(12, 13); // RX, TX

void setup()
{
  bluetoothSerial.begin(9600);
  screen.clearDisplay(); // Reset all LEDs
}

void loop()
{
  if (bluetoothSerial.available()) 
  {
    getPixelArt();
  }
  
  screen.updateDisplay(); 
  
}

void getPixelArt()
{
  byte color = 0;

  screen.clearDisplay(); // Reset all LEDs
  color = bluetoothSerial.read(); // Read the start value

  /* Recover data line by line */
  for (int line = 0; line < 32; line++)
  {
    while(bluetoothSerial.available() < 32);

    /* Then read each pixel of the line */
    for (int column = 0; column < 32; column++)
    {
      color = bluetoothSerial.read();
      screen.drawPixel(line, column, bitRead(color, 2), bitRead(color, 1), bitRead(color, 0));
    }
  }
}
