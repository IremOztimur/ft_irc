#include "../../includes/ft_irc.hpp"

USER::USER(Server *server, bool isAutherized) : Command(server, isAutherized) {}

USER::~USER() {}

void USER::execute(std::vector<std::string> command, ClientInfo *client)
{
    if (client->isRegistered)
    {
        // if (client->isRegistered)
        // {
        //     sender(client->client_fd, ERR_ALREADYREGISTRED(client->hostname, client->nickname));
        //     return;
        // }
        if (command.size() != 4)
        {
            sender(client->client_fd, ERR_NEEDMOREPARAMS(client->hostname, client->nickname, "USER") + "you need 4 parameters\r\n");
            return;
        }
        client->username = command[0];
        client->servername = command[1];
        client->hostname = command[2];
        client->realname = command[3];

        client->isRegistered = true;
		client->user_correct = true;
        std::cout << "Client " << client->nickname << " is registered." << std::endl;
		    sender(client->client_fd, "User registered !\r\n");
        sender(client->client_fd, "Please enter your nick |COMMAND:NICK|\r\n");
    }
    else
    {
        sender(client->client_fd, ERR_NOTREGISTERED(client->hostname, client->nickname));
    }
};