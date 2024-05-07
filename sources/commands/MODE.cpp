#include "../../includes/ft_irc.hpp"

MODE::MODE(Server *server, bool isAutherized) : Command(server, isAutherized) {}

MODE::~MODE() {}

void MODE::execute(std::vector<std::string> command, ClientInfo *client)
{
	(void)command;
	(void)client;
};