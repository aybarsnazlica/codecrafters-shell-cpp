#include <iostream>
#include <sstream>

enum Command
{
    TYPE,
    ECHO,
    EXIT,
    INVALID
};

Command string_to_command(const std::string& str)
{
    if (str == "type") return TYPE;
    if (str == "echo") return ECHO;
    if (str == "exit") return EXIT;
    return INVALID;
}


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
        std::string head;
        iss >> head;

        std::string command;

        switch (string_to_command(head))
        {
        case ECHO:
            std::getline(iss >> std::ws, command);
            std::cout << command << '\n';
            break;
        case TYPE:
            iss >> command;
            if (string_to_command(command) != INVALID)
            {
                std::cout << command << " is a shell builtin" << '\n';
            }
            else
            {
                std::cout << command << " not found" << '\n';
            }
            break;
        case EXIT:
            return 0;
        default:
            std::cout << input << ": command not found" << '\n';
            break;
        }
    }
}
