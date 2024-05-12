#include "../../includes/ft_irc.hpp"

PART::PART(Server *server, bool isAutherized) : Command(server, isAutherized) {}

PART::~PART() {}

void PART::execute(std::vector<std::string> command, ClientInfo *client)
{
	std::string channel = command[0]; // Çıkılacak kanalın ismi

	// İstemciyi belirtilen kanaldan çıkar
	for (unsigned long j = 0; j < server->getChannels().size(); j++)
	{
		if (server->getChannels()[j].name == channel)
		{
			for (unsigned long k = 0; k < server->getChannels()[j].clients.size(); k++)
			{
				if (client->client_fd == server->getChannels()[j].clients[k].client_fd)
				{
					std::cout << client->nickname << " has left the channel " << channel << std::endl;
					for (unsigned long m = 0; m < server->getChannels()[j].operators.size(); m++)
					{
						if (client->client_fd == server->getChannels()[j].operators[m])
						{
							server->getChannels()[j].operators.erase(server->getChannels()[j].operators.begin() + m);
						}
					}
					for (unsigned long b = 0; b < server->getChannels()[j].clients.size(); b++)
					{
						sender(server->getChannels()[j].clients[b].client_fd, Prefix(*client) + " PART " + channel + "\r\n");
					}
					server->getChannels()[j].clients.erase(server->getChannels()[j].clients.begin() + k);
					if (server->getChannels()[j].clients.empty())
					{
						server->getChannels().erase(server->getChannels().begin() + j);
						break;
					}
					else if (server->getChannels()[j].operators.empty() && server->getChannels()[j].clients.size() > 0)
					{
						std::string modeMessage = "MODE " + channel + " +o " + server->getChannels()[j].clients[0].nickname + "\r\n";
						server->getChannels()[j].operators.push_back(server->getChannels()[j].clients[0].client_fd);
						server->getChannels()[j].clients[0].isOperator = true;
						for (unsigned long b = 0; b < server->getChannels()[j].clients.size(); b++)
						{
							sender(server->getChannels()[j].clients[b].client_fd, modeMessage);
						}
					}
					break;
				}
			}
			break;
		}
	}
}