#include <iostream>
#include <sstream>

int main()
{
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;


    while (true)
    {
        std::cout << "$ ";
        std::string input;
        std::getline(std::cin, input);

        std::istringstream iss(input);
        std::string command;
        iss >> command;

        if (command == "echo")
        {
            std::string output;
            std::getline(iss >> std::ws, output);
            std::cout << output << '\n';
        }
        else if (command == "exit")
        {
            return 0;
        }
        else
        {
            std::cout << input << ": command not found\n";
        }
    }
}
