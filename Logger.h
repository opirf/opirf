#pragma once

#include <fstream>
#include <iostream> // cout
#include <sstream>

/*! \class Logger
*	\brief This class allows to save whatever we want into a file (log.txt) in order to debug the game even without the window command output
*/
class Logger {	
	public:
		
		Logger::Logger(int nLog = -1, bool out = false)
			: _out(out)
		{
			std::stringstream filename;
			filename << "log.";
			if(nLog >= 0) {
				filename << nLog << ".";
			}
			filename << "txt";

			stream = std::ofstream(filename.str().c_str(), std::ios_base::app);
		}

        ~Logger();
 
        template <typename T> Logger& operator<< (const T& m)
        {
            stream << m << ' ';
			
			if(_out)
				std::cout << m ; // cout
			
			return *this;
        }

 
    private:
        std::ofstream stream;
		bool _out;
};

/*template <typename T> std::ostream& operator<<(std::ostream& stream, const std::vector<T>& vector)
{
    for (typename std::vector<T>::const_iterator it = vector.begin(); it != vector.end(); ++it)
    {
        if (it != vector.begin())
            stream << " ; ";
        stream << *it;
    }
    return stream;
}*/