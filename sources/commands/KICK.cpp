#include "../../includes/ft_irc.hpp"

KICK::KICK(Server *server, bool isAutherized) : Command(server, isAutherized) {}

KICK::~KICK() {}

void KICK::execute(std::vector<std::string> command, ClientInfo *client)
{
	if (command.size() < 2)
	{
		sender(client->client_fd, ERR_NEEDMOREPARAMS(client->hostname, client->nickname, "KICK"));
		return;
	}

	std::string channelName = command[0];
	std::string target = command[1];

	std::vector<Channel> &channels = server->getChannels();
	bool targetExists = false;
	bool channelExists = false;

	size_t i = 0;
	size_t j = 0;

	for (i = 0; i < channels.size(); i++)
	{
		if (channels[i].name == channelName)
		{
			channelExists = true;
			break;
		}
	}

	if (!channelExists)
	{
		sender(client->client_fd, ERR_NOSUCHCHANNEL(client->hostname, client->nickname, channelName));
		return;
	}

	for (j = 0; j < channels[i].clients.size(); j++)
	{
		if (channels[i].clients[j].nickname == target)
		{
			targetExists = true;
			break;
		}
	}

	if (!targetExists)
	{
		sender(client->client_fd, ERR_NOSUCHNICK(client->hostname, client->nickname));
		return;
	}

	bool hasPrivileges = false;
	for (size_t m = 0; m < channels[i].operators.size(); m++)
	{
		if (channels[i].operators[m] == client->client_fd)
		{
			hasPrivileges = true;
			break;
		}
	}

	if (!hasPrivileges)
	{
		sender(client->client_fd, ERR_CHANOPRIVSNEEDED(client->hostname, client->nickname, channelName));
		return;
	}
	std::string kickMessage = Prefix(*client) + " KICK " + channelName + " " + target + "\r\n";
	sender(channels[i].clients[j].client_fd, kickMessage);
	channels[i].clients.erase(channels[i].clients.begin() + j);

	// Check if the user is an operator and remove them from the operator list
	std::vector<int>::iterator opIt = std::find(channels[i].operators.begin(), channels[i].operators.end(), client->client_fd);
	if (opIt != channels[i].operators.end())
	{
		channels[i].operators.erase(opIt);
	}
	// Send kick message to all other users in the channel
	for (size_t k = 0; k < channels[i].clients.size(); k++)
{
    std::string otherKickMessage = Prefix(*client) + " KICK " + channelName + " " + target + "\r\n";
    sender(channels[i].clients[k].client_fd, otherKickMessage);
}
}
