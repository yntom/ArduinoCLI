#include "Parser.h"
#include "Command.h"

Parser par('$', ';');

void setup()
{
	SerialUSB.begin(9600);
}

SayCommand com;
LedCommand led(13);

void loop()
{
	String str;
  if (SerialUSB.available() > 0)
  {
    	char c = SerialUSB.read();
      par.Search(c);
      if (par.IsCommandReady())
      {
        str = par.GetCommand();
        com.Begin(str);
        led.Begin(str);
    	}
  }
}
