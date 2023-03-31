#include "Parser.h"
#include "Command.h"

void setup()
{
	SerialUSB.begin(9600);
}

Parser par('$', ';');
constexpr size_t COMMAND_NUMBER = 2u;
Command* commands[COMMAND_NUMBER] = {new SayCommand(), new LedCommand()};

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
            for (size_t i = 0u; i < COMMAND_NUMBER; ++i)
                commands[i]->Begin(str);
    	  }
    }
}
