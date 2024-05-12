#include "../../includes/ft_irc.hpp"

USER::USER(Server *server, bool isAutherized) : Command(server, isAutherized) {}

USER::~USER() {}

void USER::execute(std::vector<std::string> command, ClientInfo *client)
{
	if (client->nick_correct == false)
	{
		sender(client->client_fd, ERR_NONICKNAMEGIVEN(client->hostname, client->nickname));
	}
	else if (client->isRegistered)
	{
		client->username = command[0];
		client->servername = command[1];
		client->hostname = command[2];
		client->realname = command[3];
		for (unsigned long i = 0; i < server->getClients().size(); i++)
		{
			std::cout << "Client: " << client->username << " is registered." << std::endl;
			std::cout << "clientget: " << server->getClients()[i].username << std::endl;
			if ((server->getClients()[i].username == client->username || server->getClients()[i].hostname == client->hostname || server->getClients()[i].realname == client->realname || server->getClients()[i].servername == client->servername) && server->getClients()[i].client_fd != client->client_fd)
			{
				sender(client->client_fd, ERR_ALREADYREGISTRED(client->hostname, client->nickname));
				return;
			}
		}
		if (command.size() != 4)
		{
			sender(client->client_fd, ERR_NEEDMOREPARAMS(client->hostname, client->nickname, "USER") + "you need 4 parameters\r\n");
			return;
		}
		if (client->nick_correct == true)
		{
			client->isRegistered = true;
			std::cout << "Client " << client->nickname << " is registered." << std::endl;
			sender(client->client_fd, Prefix(*client) + "User registered !\r\n");
			server->WELCOME(client);
		}
	}
	else
	{
		sender(client->client_fd, ERR_NOTREGISTERED(client->hostname, client->nickname));
	}
};