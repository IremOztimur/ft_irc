#include "../../includes/ft_irc.hpp"

QUIT::QUIT(Server *server, bool isAutherized) : Command(server, isAutherized) {}

QUIT::~QUIT() {}

void Server::removeClient(int client_fd)
{
	for (size_t i = 0; i < clients.size(); ++i)
	{
		if (clients[i].client_fd == client_fd)
		{
			close(clients[i].client_fd);
			clients.erase(clients.begin() + i);
			break;
		}
	}
	for (size_t i = 0; i < poll_fd.size(); ++i)
	{
		if (poll_fd[i].fd == client_fd)
		{
			poll_fd.erase(poll_fd.begin() + i);
			break;
		}
	}
}

void QUIT::execute(std::vector<std::string> command, ClientInfo *client)
{
	if (command.size() < 1)
	{
		std::vector<Channel> &channels = server->getChannels();
		for (size_t j = 0; j < channels.size(); ++j)
		{
			if (isClientInChannel(*client, channels[j]))
			{
				PART partCommand(server, isAutherized);
				std::vector<std::string> partArgs;
				partArgs.push_back(channels[j].name);
				partCommand.execute(partArgs, client);
				partCommand.~PART();
			}
		}

		std::string message = Prefix(*client) + "QUIT" + " :" + "Client disconnected";
		sender(client->client_fd, message);

		server->removeClient(client->client_fd);
	}
}
