#include "Parser.h"


Parser::Parser(char start_symb = '$', char end_symb = ';')
{
	incoming_byte = ' ';
	this->start_symb = start_symb;
	this->end_symb = end_symb;
	ResetBuffer();
}

void Parser::ResetBuffer()
{
	memset(input_data, ' ', MAX_BUFF_SIZE);
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

void Parser::Search(char& in, Interface** inter, uint8_t inter_num)
{

	incoming_byte = in;

	if (cur_counter >= MAX_BUFF_SIZE)
	{
		cur_counter = 0;
		ResetBuffer();
		inter[inter_num]->Writeln("Command buffer overflow");
		//SerialUSB.println("Command buffer overflow");
	}

	if (incoming_byte == start_symb)
	{
		get_started = true;
	}

	else if (incoming_byte != end_symb && get_started)
	{
		input_data[cur_counter] = incoming_byte;
		cur_counter++;		
	}


	if (incoming_byte == ' ' && get_started)
	{
		commands[command_counter] = String(input_data).substring(prev_counter, cur_counter-1);
		command_counter++;
		cur_counter++;
		prev_counter = cur_counter;
	}

	if (incoming_byte == end_symb && get_started)
	{
		commands[command_counter] = String(input_data).substring(prev_counter, cur_counter);
		command_ready = true;
		get_started = false;
	}
	
	if (incoming_byte == '\n')
	{
		cur_counter = 0;
		ResetBuffer();
	}
}

String Parser::GetCommand(uint8_t index)
{
	return commands[index];
}

int Parser::GetCommandCounter()
{
	return command_counter;
}

void Parser::Clear()
{
	cur_counter = 0;
	prev_counter = 0;
	command_ready = false;
	get_started = false;
	for (int i = 0; i <= command_counter; i++)
	{
		commands[i] = "";
	}
	command_counter = 0;
}

// for debug:
String Parser::GetBuffer()
{
	String str = String(input_data);
	return str;
}





