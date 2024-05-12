#include "../../includes/ft_irc.hpp"

NICK::NICK(Server *server, bool isAutherized) : Command(server, isAutherized) {}

NICK::~NICK() {}

void NICK::execute(std::vector<std::string> command, ClientInfo *client)
{
	if (client->user_correct == false)
	{
		sender(client->client_fd, "Please enter your user info |COMMAND:USER|\r\n");
		return;
	}
	if (command.size() != 1)
	{
		sender(client->client_fd, ERR_NEEDMOREPARAMS(client->hostname, client->nickname, "NICK"));
		return;
	}
    if (client->isRegistered && client->user_correct)
    {
        client->nickname = command[0];
        client->isRegistered = true;
        sender(client->client_fd, Prefix(*client));
        server->WELCOME(client);
    }
};