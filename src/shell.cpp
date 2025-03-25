#include <iostream>
#include <sstream>
#include <filesystem>
#include "shell.hpp"

// Convert string to Command enum
Command parse_command(const std::string& str)
{
    if (str == "type") return Command::TYPE;
    if (str == "echo") return Command::ECHO;
    if (str == "pwd") return Command::PWD;
    if (str == "exit") return Command::EXIT;
    return Command::CUSTOM;
}

// Find command path in system PATH
std::optional<std::string> find_command_path(const std::string& command)
{
    const char* path_env = std::getenv("PATH");
    if (!path_env) return std::nullopt;

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
    return std::nullopt;
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

// Execute a custom command
void execute_custom_command(const std::string& command, const std::string& arguments)
{
    if (auto path = find_command_path(command))
    {
        const std::string command_name = std::filesystem::path(*path).filename().string();
        const std::string full_command = command_name + " " + arguments;

        int ret_code = std::system(full_command.c_str());
        if (ret_code == -1)
        {
            std::cerr << "Failed to execute command: " << command << '\n';
        }
    }
    else
    {
        std::cout << command << ": command not found\n";
    }
}