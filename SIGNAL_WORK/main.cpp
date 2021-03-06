#include <iostream>
#include <string>
#include <exception>

#define __MAKE_BIBART__

#include "ForkThread.hpp"

template<int var>
void                    Troll_func(std::string msg)
    {
        bibArtFork << msg << var << "." << std::endl;
    }

void                    BasicForkAction(void *time_data)
    {
        std::this_thread::sleep_for(std::chrono::seconds(*((int *) time_data)));
        bibArtFork << "Child BASICALY ended after: " << *((int *) time_data) << " seconds." << std::endl;
    }

int                     main(int argc, char **argv)
    {
        int             max_fork = 1000;
        std::size_t     junk_var;

        Troll_func<10>("Whats that 10: ");
        bibArtFork << "You can specify a number as first argument of this program to set the number of fork to launch during the test. (not mandatory and set to: " << max_fork << ")." << std::endl;
        try {
            if (argc == 2) max_fork = std::stoi(std::string(argv[1]), &junk_var);
            if (max_fork <= 0) throw ("The number of fork to do must not be null or negative!");
        } catch (std::exception e) {
            bibArtFork << "You specified an entry to the program that is NaN or too extreme!" << std::endl;
            bibArtFork << e.what() << std::endl;
            exit(0);
        }
        for (int i = 1; i <= max_fork; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            bibArtFork << "This is the: " << i << " over: " << max_fork << "." <<  std::endl;
            bibArtFork->Fork();
        }
        return (0);
    }
