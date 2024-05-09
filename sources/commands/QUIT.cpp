//
// Created by fatih soymaz on 13.04.2024.
//
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
			break; // Bu break ifadesini kaldırın
		}
	}

	// Poll_fd dizisinden de ilgili girişi kaldırın
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
				// Call PART command for each channel the client is in
				PART partCommand(server, isAutherized);
				std::vector<std::string> partArgs;
				partArgs.push_back(channels[j].name);
				partCommand.execute(partArgs, client);
				partCommand.~PART();
			}
		}

		std::string message = Prefix(*client) + "QUIT" + " :" + "Client disconnected";
		sender(client->client_fd, message);

		// İstemciyi kanallardan çıkar
		for (unsigned long j = 0; j < server->getChannels().size(); j++)
		{
			for (unsigned long k = 0; k < server->getChannels()[j].clients.size(); k++)
			{
				if (client->client_fd == server->getChannels()[j].clients[k].client_fd)
				{
					std::cout << client->nickname << " has left the server" << std::endl;
					for (unsigned long m = 0; m < server->getChannels()[j].operators.size(); m++)
					{
						if (client->client_fd == server->getChannels()[j].operators[m])
							server->getChannels()[j].operators.erase(server->getChannels()[j].operators.begin() + m);
					}
					for (unsigned long b = 0; b < server->getChannels()[j].clients.size(); b++)
					{
						sender(server->getChannels()[j].clients[b].client_fd, Prefix(*client) + " QUIT " + message + "\r\n");
					}
					server->getChannels()[j].clients.erase(server->getChannels()[j].clients.begin() + k);
				}
			}
		}
		// İstemciyi kaldır
		server->removeClient(client->client_fd);
	}
}
