#ifndef _COMMAND_h
#define _COMMAND_h

#include <Arduino.h>

class Command
{
protected:
	String key_word;
	String argument;
	char devider;
	bool start_command = false;

public:
	Command();
	Command(String key_word, String argument, char devider);
};

class SayCommand : public Command
{
private:
	//Maybe later

public:
	SayCommand()
	{
		key_word = "say";
	}

	void Begin(String& command)
	{
		String str;
		if (command.substring(0, 3) == key_word)
		{
			for (auto c = command.begin() + 4; (c != command.end()) && (*c != ';'); ++c)
			{
				SerialUSB.print(*c);
			}

			SerialUSB.print('\n');

		}
	}
};


class LedCommand : public Command
{
private:
	bool LedOn = false;
	uint8_t LED_PIN;

public:
	LedCommand()
	{
		uint8_t LED_PIN = 13;
		key_word = "led";
		pinMode(LED_PIN, OUTPUT);
	}

	LedCommand(uint8_t PIN)
	{
		LED_PIN = PIN;
		key_word = "led";
		pinMode(LED_PIN, OUTPUT);
	}

	void Begin(String& command)
	{
		if (command.substring(0, 3) == key_word)
		{
			if (command.substring(4, 6) == "on")
			{
				digitalWrite(LED_PIN, HIGH);
				SerialUSB.println("LED has been turned on");
			}
			else if (command.substring(4, 7) == "off")
			{
				digitalWrite(LED_PIN, LOW);
				SerialUSB.println("LED has been turned off");
			}
			else
			{
				SerialUSB.println("-> Syntax error");
			}
		}
	}

};
#endif