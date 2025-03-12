#include <iostream>
#include <sstream>
#include <filesystem>

enum class Command
{
    TYPE,
    ECHO,
    EXIT,
    INVALID
};

// Convert string to Command enum
Command parse_command(const std::string& str)
{
    if (str == "type") return Command::TYPE;
    if (str == "echo") return Command::ECHO;
    if (str == "exit") return Command::EXIT;
    return Command::INVALID;
}

// Check if a command exists in system PATH
std::string find_command_path(const std::string& command)
{
    const char* path_env = std::getenv("PATH");
    if (!path_env) return "";

    std::istringstream paths(path_env);
    std::string directory;

    while (std::getline(paths, directory, ':'))
    {
        std::filesystem::path full_path = std::filesystem::path(directory) / command;
        if (exists(full_path))
        {
            return full_path.string();
        }
    }

    return "";
}

// Read and parse user input
std::pair<std::string, std::string> get_input()
{
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);

    std::istringstream iss(input);
    std::string command;
    iss >> command;

    std::string arguments;
    std::getline(iss >> std::ws, arguments);

    return {command, arguments};
}

int main()
{
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    while (true)
    {
        switch (auto [command, arguments] = get_input(); parse_command(command))
        {
        case Command::ECHO:
            std::cout << arguments << '\n';
            break;

        case Command::TYPE:
            if (parse_command(arguments) != Command::INVALID)
            {
                std::cout << arguments << " is a shell builtin\n";
            }
            else
            {
                std::string path = find_command_path(arguments);
                if (!path.empty())
                {
                    std::cout << arguments << " is " << path << '\n';
                }
                else
                {
                    std::cout << arguments << " not found\n";
                }
            }
            break;

        case Command::EXIT:
            return 0;

        default:
            std::cout << command << ": command not found\n";
            break;
        }
    }
}
