#include "../../includes/ft_irc.hpp"

TOPIC::TOPIC(Server *server, bool isAutherized) : Command(server, isAutherized) {}

TOPIC::~TOPIC() {}

void TOPIC::execute(const std::vector<std::string> command, ClientInfo *client)
{
	(void)client;
	std::string channel = command[0];
	std::string topic = command[1];
	bool isOperator = false;
	if (topic[0] == ':')
	{
		topic = topic.substr(1);
	}
	for (size_t i = 0; i < server->getChannels().size(); ++i)
	{
		if (server->getChannels()[i].name == channel)
		{
			if (server->getChannels()[i].onlyOps == true)
			{

				for (size_t j = 0; j < server->getChannels()[i].operators.size(); ++j)
				{
					if (server->getChannels()[i].operators[j] == client->client_fd)
					{
						isOperator = true;
						break;
					}
				}

				if (!isOperator)
				{
					perror("Error: TOPIC: client is not an operator");
					sender(client->client_fd, ERR_CHANOPRIVSNEEDED(client->hostname, client->nickname, channel));
					return;
				}
			}
		}
		for (size_t j = 0; j < server->getChannels()[i].clients.size(); ++j)
		{
			server->getChannels()[i].topic = topic;
			if (server->getChannels()[i].topic.empty())
			{
				server->getChannels()[i].topic = "No topic is set";
			}
			for (size_t k = 0; k < server->getChannels()[i].clients.size(); ++k)
			{
				sender(server->getChannels()[i].clients[k].client_fd, RPL_TOPIC(server->getChannels()[i].clients[k].hostname, server->getChannels()[i].clients[k].nickname, channel, topic));
			}
			break;
		}
		break;
	}
}
