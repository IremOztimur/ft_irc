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
};