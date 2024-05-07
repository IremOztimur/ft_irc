#include "../../includes/ft_irc.hpp"

NICK::NICK(Server *server, bool isAutherized) : Command(server, isAutherized) {}

NICK::~NICK() {}

void NICK::execute(std::vector<std::string> command, ClientInfo *client)
{
    if (client->isRegistered)
    {
        client->nickname = command[0];
        client->isRegistered = true;
        sender(client->client_fd, Prefix(*client) + client->nickname);
        server->WELCOME(client->client_fd - 4);
    }
};