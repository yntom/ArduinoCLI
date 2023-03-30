#include "Command.h"

Command::Command()
{
	devider = ' ';
}

Command::Command(String key_word, String argument, char devider)
{
	this->devider = devider;
	this->key_word = key_word;
	this->argument = argument;
}
