#ifndef SHELL_HPP
#define SHELL_HPP

#include <optional>
#include <string>

enum class Command
{
    TYPE,
    ECHO,
    PWD,
    CD,
    EXIT,
    CUSTOM
};

Command parse_command(const std::string& str);
std::optional<std::string> find_command_path(const std::string& command);
std::pair<std::string, std::string> get_input();
void execute_custom_command(const std::string& command, const std::string& arguments);

#endif // SHELL_HPP
