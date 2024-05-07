#include "../../includes/ft_irc.hpp"

WHO::WHO(Server *server, bool isAutherized) : Command(server, isAutherized) {}

WHO::~WHO() {}

void WHO::execute(std::vector<std::string> command, ClientInfo *client)
{
	(void)command;
	(void)client;	
};