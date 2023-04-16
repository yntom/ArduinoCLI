#include <DueTimer.h>
#include "Parser.h"
#include "Interface.h"
#include "Command.h"


Parser par('$', ';');
constexpr size_t COMMAND_NUMBER = 3u;
constexpr size_t INTERFACE_NUMBER = 3u;

constexpr uint8_t PIN_4 = 4;
constexpr uint8_t PIN_5 = 5;
constexpr uint8_t PIN_6 = 6;

uint8_t counter = 0;

Command* commands[COMMAND_NUMBER] = {new SetCommand(), new SayCommand(), new GetCommand(&counter)};
Interface* interfaces[INTERFACE_NUMBER] = { new SerialUSBInterface(), new SerialInterface(),  new EthernetInterface() };
uint8_t active_interface;
bool is_interface_selected = false;

void Handler()
{
    counter++;
}

void setup()
{
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    Timer3.attachInterrupt(Handler).start(300000);  
}

void loop()
{
    if (!is_interface_selected)
    {
        for (size_t i = 0u; i < INTERFACE_NUMBER; ++i)
        {
            if (interfaces[i]->is_active())
            {
                active_interface = i;
                interfaces[active_interface]->Begin(9600);
                is_interface_selected = true;
                break;
            }
        }
    }
    
    if (interfaces[active_interface]->Available() > 0)
    {
        char c = interfaces[active_interface]->Read();
        par.Search(c, interfaces, active_interface);
        if (par.IsCommandReady())
        {
            for (size_t i = 0u; i < COMMAND_NUMBER; ++i)
            {
                commands[i]->Begin(&par, interfaces, active_interface);
            }    
            par.Clear();
        }  
    } 
}
