#include <iostream>
#include <sstream>
#include "shell.hpp"

int main()
{
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    while (true)
    {
        auto [command, arguments] = get_input();

        switch (parse_command(command))
        {
        case Command::ECHO:
            std::cout << arguments << '\n';
            break;

        case Command::TYPE:
            {
                if (parse_command(arguments) != Command::CUSTOM)
                {
                    std::cout << arguments << " is a shell builtin\n";
                }
                else if (auto path = find_command_path(arguments))
                {
                    std::cout << arguments << " is " << *path << '\n';
                }
                else
                {
                    std::cout << arguments << " not found\n";
                }
                break;
            }

        case Command::EXIT:
            return 0;

        case Command::CUSTOM:
            execute_custom_command(command, arguments);
            break;

        default:
            std::cout << command << ": command not found\n";
            break;
        }
    }
}
