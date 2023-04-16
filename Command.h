#ifndef _COMMAND_h
#define _COMMAND_h

#include <Arduino.h>
#include "Interface.h"

class Command
{
protected:
	String key_word;
public:
	virtual void Begin(Parser* par, Interface** inter, uint8_t inter_num) = 0;
	virtual ~Command() = default;
};

class SayCommand : public Command
{
private:
	//Maybe later
public:
	SayCommand(String key_word = "say")
	{
		this->key_word = key_word;
	}

	void Begin(Parser* par, Interface** inter, uint8_t inter_num) override
	{
		if (par->GetCommand(0) == key_word)
		{
			for (uint8_t i = 1; i <= par->GetCommandCounter(); ++i)
			{
				inter[inter_num]->Write(par->GetCommand(i));
				inter[inter_num]->Write(" ");
			}
			inter[inter_num]->Write("\n");
		}
	}
};

class SetCommand : public Command
{
private:
	uint8_t PIN;
public:
	SetCommand(String key_world = "set")
	{
		this->key_word = key_word;
	}

	void Begin(Parser* par, Interface** inter, uint8_t inter_num) override
	{
		
		if (par->GetCommand(0) == "set" &&
			(par->GetCommand(1)).toInt() >= 0 &&
			(par->GetCommand(1)).toInt() <= 53)
		{
			if (par->GetCommand(2) == "on")
			{
				digitalWrite((par->GetCommand(1)).toInt(), HIGH);
			}
			if (par->GetCommand(2) == "off")
			{
				digitalWrite((par->GetCommand(1)).toInt(), LOW);
			}
		}
	}
};

class GetCommand : public Command
{
private:
	uint8_t* counter;
public:
	GetCommand(uint8_t* counter, String key_world = "get")
	{
		this->counter = counter;
		this->key_word = key_word;
	}

	void Begin(Parser* par, Interface** inter, uint8_t inter_num) override
	{

		if (par->GetCommand(0) == "get" && par->GetCommand(1) == "counter")	
		{
			inter[inter_num]->Writeln(String(*counter));
		}
	}
};
#endif