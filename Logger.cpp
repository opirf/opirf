#include "logger.h"
 
std::ofstream Logger::stream("log.txt");
 
Logger::~Logger()
{
    stream << std::endl;
	std::cout << std::endl; // cout
}