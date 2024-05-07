#pragma once

#include "structs.hpp"
#include "Command.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "macros.hpp"
#include "utils.hpp"

// to-do: add exception classes for more accurate representation of errors

/**
 * Validates if the given string is a valid port number.
 *
 * Verifies that the string contains only numeric characters and falls within
 * the range of valid port numbers (1024 to 49151, inclusive).
 *
 * @param port The string representing the port number to validate.
 *
 * @throws std::invalid_argument If the string is not a valid port number or
 *                               if it falls outside the valid port range.
 */
void isValidPort(std::string port);
std::string Prefix(ClientInfo users);

/**
 * Validates whether the provided string meets password requirements.
 *
 * This function checks if the provided string meets certain password requirements,
 * such as length, complexity, or any other specified criteria.
 *
 * @param password The string representing the password to validate.
 *
 * @throws std::invalid_argument If the provided password does not meet the specified
 *                               requirements or is considered invalid.
 */
void isValidPassword(std::string password);


void ClientInit(ClientInfo &user, int client_fd);
