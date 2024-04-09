#include "../includes/ft_irc.hpp"

void isValidPort(std::string port)
{
	for (unsigned long i = 0; i < port.length(); i++)
		if (!isdigit(port[i]))
			throw std::invalid_argument("Port must be a number");
	if(!(std::stoi(port) > 1024 && std::stoi(port) < 49151))
		throw std::invalid_argument("Port must be between 1024 and 49151");
}

void isValidPassword(std::string password)
{
	if (password.length() < 8)
		throw std::invalid_argument("Password must be at least 8 characters long");

	bool hasUpper = false;
	bool hasLower = false;
	bool hasDigit = false;
	bool hasSpecial = false;

	for (unsigned long i = 0; i < password.length(); i++)
	{
		if (isupper(password[i]))
			hasUpper = true;
		if (islower(password[i]))
			hasLower = true;
		if (isdigit(password[i]))
			hasDigit = true;
		if (ispunct(password[i]))
			hasSpecial = true;
	}
	if (!hasUpper || !hasLower || !hasDigit || !hasSpecial)
		throw std::invalid_argument("Password must contain at least one uppercase letter, one lowercase letter, one digit, and one special character");


}
