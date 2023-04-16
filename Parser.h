#ifndef _PARSER_h
#define _PARSER_h

#define _CRT_SECURE_NO_WARNINGS

constexpr int MAX_BUFF_SIZE = 50;
constexpr int MAX_COMMAND_COUNT = 10;


#include <Arduino.h>
#include "Interface.h"

class Parser
{
private:
	char input_data[MAX_BUFF_SIZE];
	String commands[MAX_COMMAND_COUNT];

	int command_counter = 0;
	char incoming_byte;

	int cur_counter = 0;
	int prev_counter = 0;

	// protocol:
	bool get_started = false;
	char start_symb;
	char end_symb;
	
	bool command_ready = false;

public:
	Parser(char start_symb, char end_symb);

	void ResetBuffer();

	bool IsCommandReady();

	void Search(char& in, Interface** inter, uint8_t inter_num);

	String GetCommand(uint8_t index);
	
	String GetBuffer();

	int GetCommandCounter();

	void Clear();
};

#endif

