#include "../../includes/ft_irc.hpp"

MODE::MODE(Server *server, bool isAutherized) : Command(server, isAutherized) {}

MODE::~MODE() {}

void MODE::execute(std::vector<std::string> command, ClientInfo *client)
{
	std::string channel, mode, user, modeParameter;
	channel = command[0];
	user = command[1];
	modeParameter = command[1];
	mode = command[2];
	std::vector<Channel> &channels = server->getChannels();
	for (std::vector<Channel>::size_type j = 0; j != channels.size(); ++j)
	{
		if (channels[j].name == channel)
		{
			for (size_t k = 0; k != channels[j].operators.size(); ++k)
			{
				if (channels[j].operators[k] == client->client_fd)
				{
					if (modeParameter == "+i" || modeParameter == "-i")
					{
						channels[j].isPublic = (modeParameter == "+i") ? false : true;
						for (unsigned long t = 0; t < channels[j].clients.size(); t++)
							sender(channels[j].clients[t].client_fd, Prefix(*client) + " MODE " + channel + " " + modeParameter + "\r\n");
						return;
					}
					else if (modeParameter == "+t" || modeParameter == "-t")
					{
						channels[j].onlyOps = (modeParameter == "+t") ? true : false;
						for (unsigned long t = 0; t < channels[j].clients.size(); t++)
							sender(channels[j].clients[t].client_fd, Prefix(*client) + " MODE " + channel + " " + modeParameter + "\r\n");
						return;
					}
					else if (modeParameter == "+k" || modeParameter == "-k")
					{
						if (modeParameter == "+k")
							channels[j].password = command[2];
						else
							channels[j].password = "";
						for (unsigned long t = 0; t < channels[j].clients.size(); t++)
							sender(channels[j].clients[t].client_fd, Prefix(*client) + " MODE " + channel + " " + modeParameter + " " + ((modeParameter == "+k") ? command[2] : "") + "\r\n");
						return;
					}
					for (size_t m = 0; m != channels[j].clients.size(); ++m)
					{
						if (channels[j].clients[m].nickname == user)
						{
							if (mode == "+o")
							{
								if (client->client_fd == channels[j].clients[m].client_fd)
									return;
								channels[j].clients[m].isOperator = true;
								// Check if the client_fd is already in the operators list before pushing
								if (std::find(channels[j].operators.begin(), channels[j].operators.end(), channels[j].clients[m].client_fd) == channels[j].operators.end())
								{
									channels[j].operators.push_back(channels[j].clients[m].client_fd);
								}
								for (unsigned long t = 0; t < channels[j].clients.size(); t++)
									sender(channels[j].clients[t].client_fd, Prefix(channels[j].clients[m]) + " MODE " + channel + " +o " + user + "\r\n");

								// sender function needs to be implemented
							}
							else if (mode == "-o")
							{
								if (client->client_fd == channels[j].clients[m].client_fd)
									return;
								std::vector<int>::iterator it = std::find(channels[j].operators.begin(), channels[j].operators.end(), channels[j].clients[m].client_fd);
								if (it != channels[j].operators.end())
									channels[j].operators.erase(it); // Use the correct vector here
								channels[j].clients[m].isOperator = false;
								for (unsigned long t = 0; t < channels[j].clients.size(); t++)
									sender(channels[j].clients[t].client_fd, Prefix(channels[j].clients[m]) + " MODE " + channel + " -o " + user + "\r\n");
								break; // Exit the loop after operations are done
							}
						}
					}
					break; // Exit the loop after operations are done
				}
			}
		}
	}
}