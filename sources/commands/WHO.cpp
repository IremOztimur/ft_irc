#include "../../includes/ft_irc.hpp"

WHO::WHO(Server *server, bool isAutherized) : Command(server, isAutherized) {}

WHO::~WHO() {}

void WHO::execute(std::vector<std::string> command, ClientInfo *client)
{
	if (command.size() < 2)
		return; // Not enough parameters

	std::string target = command[0];
	std::vector<Channel> &channels = server->getChannels();

	for (unsigned long j = 0; j < channels.size(); j++)
	{
		if (channels[j].name == target)
		{
			for (unsigned long k = 0; k < channels[j].clients.size(); k++)
			{
				// Assuming sender function takes client_fd, message as parameters
				// Assuming RPL_WHOREPLY function generates the appropriate message
				sender(client->client_fd, RPL_WHOREPLY(channels[j].clients[k].realname, channels[j].name.substr(1, channels[j].name.length() - 1), channels[j].clients[k].nickname, "127.0.0.1", "myIRCServ", channels[j].clients[k].nickname, "1", channels[j].clients[k].realname));
			}
		}
	}
}