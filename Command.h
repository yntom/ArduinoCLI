#ifndef _COMMAND_h
#define _COMMAND_h

#include <Arduino.h>

class Command
{
public:
	virtual void Begin(String& command) = 0;
	virtual ~Command() = default;
};


class CommandSettings : public Command
{
protected:
	String key_word;
  
public:
	void SetKeyWord(String key_word)
	{
		this->key_word = key_word;
	}
};


class SayCommand : public CommandSettings
{
private:
	//Maybe later
public:
	SayCommand(String key_word = "say")
	{
		SetKeyWord(key_word);
	}

	void Begin(String& command) override
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


class LedCommand : public CommandSettings
{
private:
	bool LedOn = false;
	uint8_t LED_PIN;
public:
	LedCommand(String key_word = "led", uint8_t LED_PIN = 13)
	{
		this->LED_PIN = LED_PIN;
		SetKeyWord(key_word);
		pinMode(LED_PIN, OUTPUT);
	}

	void Begin(String& command) override
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