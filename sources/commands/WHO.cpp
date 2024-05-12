#include "../../includes/ft_irc.hpp"

WHO::WHO(Server *server, bool isAutherized) : Command(server, isAutherized) {}

WHO::~WHO() {}

void WHO::execute(std::vector<std::string> command, ClientInfo *client)
{
	if (command.size() == 0)
	{
		sender(client->client_fd, ERR_NEEDMOREPARAMS(client->hostname, client->nickname, "WHO"));
		return;
	}
	else if (command.size() > 1)
	{
		sender(client->client_fd, ERR_TOOMANYTARGETS(client->hostname, client->nickname, "WHO"));
		return;
	}

	else
	{
		std::string target = command[0];
		for (unsigned long j = 0; j < server->getChannels().size(); j++)
		{
			if (server->getChannels()[j].name == target)
			{
				for (unsigned long k = 0; k < server->getChannels()[j].clients.size(); k++)
				{
					sender(client->client_fd, RPL_WHOREPLY(server->getChannels()[j].name.substr(1, server->getChannels()[j].name.length() - 1), server->getChannels()[j].clients[k].nickname, server->getChannels()[j].clients[k].username, "127.0.0.1", server->getChannels()[j].clients[k].realname));
				}
			}
		}
	}
}