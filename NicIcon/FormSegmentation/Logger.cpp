#include "logger.h"

Logger::~Logger()
{
    stream << std::endl;

	if(_out)
		std::cout << std::endl; // cout
}