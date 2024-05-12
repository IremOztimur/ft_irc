#include "../../includes/ft_irc.hpp"

PING::PING(Server *server, bool isAutherized) : Command(server, isAutherized) {}

PING::~PING() {}

void PING::execute(std::vector<std::string> command, ClientInfo *client)
{
	if (client->isRegistered)
	{
		if (command.size() == 0)
		{
			sender(client->client_fd, "PONG\r\n");
		}
		else
		{
			sender(client->client_fd, "PONG " + command[0] + "\r\n");
		}
	}
};