#include "Parser.h"

Parser::Parser(char start_symb = '$', char end_symb = ';')
{
	incoming_byte = ' ';
	this->start_symb = start_symb;
	this->end_symb = end_symb;
	ResetBuffers();
}

void Parser::ResetBuffers()
{
	memset(input_data, ' ', MAX_BUFF_SIZE);
	memset(command_data, ' ', MAX_BUFF_SIZE);
}

bool Parser::IsCommandReady()
{
	if (command_ready)
	{
		command_ready = false;
		return true;
	}
	else
		return false;
}

void Parser::Search(char& in)
{

	incoming_byte = in;

	if (counter >= MAX_BUFF_SIZE)
	{
		counter = 0;
		ResetBuffers();
		SerialUSB.println("Command buffer overflow");
	}

	if (incoming_byte == start_symb)
	{
		get_started = true;
	}

	else if (incoming_byte != end_symb && get_started)
	{
		input_data[counter] = incoming_byte;
		counter++;		
	}

	if (get_started && incoming_byte == end_symb)
	{
		strncpy(command_data, input_data, counter);
		counter = 0;
		get_started = false;
		command_ready = true;
	}

	if (incoming_byte == '\n')
	{
		counter = 0;
	}
}

String Parser::GetCommand()
{
	String str(command_data);
	ResetBuffers();
	return str;
}





