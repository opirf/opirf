#pragma once

#include <fstream>
#include <iostream> // cout

/*! \class Logger
*	\brief This class allows to save whatever we want into a file (log.txt) in order to debug the game even without the window command output
*/
class Logger {	
	public:
        ~Logger();
 
        template <typename T> Logger& operator<< (const T& m)
        {
            stream << m << ' ';
			std::cout << m ; // cout
            return *this;
        }

 
    private:
        static std::ofstream stream;
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