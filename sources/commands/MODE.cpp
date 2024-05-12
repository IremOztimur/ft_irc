#include "../../includes/ft_irc.hpp"

MODE::MODE(Server *server, bool isAutherized) : Command(server, isAutherized) {}

MODE::~MODE() {}

void MODE::execute(std::vector<std::string> command, ClientInfo *client)
{
	std::string channel, mode, user;
	if (command.size() < 3)
		return;
	channel = command[0];
	user = command[1];
	mode = command[2];
	std::vector<Channel> &channels = server->getChannels();
	for (std::vector<Channel>::size_type j = 0; j != channels.size(); ++j)
	{
		if (channels[j].name == channel)
		{
			for (std::vector<int>::size_type k = 0; k != channels[j].operators.size(); ++k)
			{
				if (channels[j].operators[k] == client->client_fd)
				{
					for (size_t m = 0; m != channels[j].clients.size(); ++m)
					{
						if (channels[j].clients[m].nickname == user)
						{
							if (mode == "+o")
							{
								channels[j].clients[m].isOperator = true;
								channels[j].operators.push_back(channels[j].clients[m].client_fd);
								for (unsigned long t = 0; t < channels[j].clients.size(); t++)
									sender(channels[j].clients[t].client_fd, Prefix(channels[j].clients[m]) + " MODE " + channel + " +o " + user + "\r\n");

								// sender function needs to be implemented
							}
							else if (mode == "-o")
							{
								channels[j].clients[m].isOperator = false;
								
								for (unsigned long t = 0; t < channels[j].clients.size(); t++)
									sender(channels[j].clients[t].client_fd, Prefix(channels[j].clients[m]) + " MODE " + channel + " -o " + user + "\r\n");
							}
						}
					}
				}
			}
		}
	}
}