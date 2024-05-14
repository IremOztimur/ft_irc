#include "../../includes/ft_irc.hpp"

NICK::NICK(Server *server, bool isAutherized) : Command(server, isAutherized) {}

NICK::~NICK() {}

void NICK::execute(std::vector<std::string> command, ClientInfo *client)
{
	if (command.size() != 1)
	{
		sender(client->client_fd, ERR_NEEDMOREPARAMS(client->hostname, client->nickname, "NICK"));
		return;
	}
	if (client->isRegistered)
	{
		client->nickname = command[0];
		client->isRegistered = true;
		client->nick_correct = true;
		sender(client->client_fd, "Please enter your user info |COMMAND:USER|\r\n");
	}
	for (unsigned long i = 0; i < server->getClients().size(); i++)
	{
		if ((server->getClients()[i].nickname == client->nickname) && server->getClients()[i].client_fd != client->client_fd)
		{
			sender(client->client_fd, ERR_ALREADYREGISTRED(client->hostname, client->nickname));
			return;
		}
	}
};