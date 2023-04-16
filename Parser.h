#ifndef _PARSER_h
#define _PARSER_h

#define _CRT_SECURE_NO_WARNINGS
constexpr int MAX_BUFF_SIZE = 30;

#include <Arduino.h>

class Parser
{
private:
	char input_data[MAX_BUFF_SIZE];
	char command_data[MAX_BUFF_SIZE];

	char incoming_byte;
	int counter = 0;

	// protocol:
	bool get_started = false;
	char start_symb;
	char end_symb;
	
	bool command_ready = false;

public:
	Parser();

	Parser(char start_symb, char end_symb);

	void ResetBuffers();

	bool IsCommandReady();

	void Search(char& in);

	String GetCommand();
};

#endif

