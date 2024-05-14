#include "../../includes/ft_irc.hpp"

PRIVMSG::PRIVMSG(Server *server, bool isAutherized) : Command(server, isAutherized) {}

PRIVMSG::~PRIVMSG() {}

void PRIVMSG::execute(std::vector<std::string> command, ClientInfo *client)
{
    std::string target = command[0];
    std::string message = "";
    for (std::vector<std::string>::size_type i = 1; i != command.size(); ++i)
    {
        message += command[i];
        if (i != command.size() - 1)
        {
            message += " ";
        }
    }
    bool targetExists = false;

    size_t i;

    for (i = 0; i < server->getClients().size(); ++i)
    {
        if (server->getClients()[i].nickname == target)
        {
            targetExists = true;
            break;
        }
    }

    if (targetExists)
    {
        std::string fullMessage = Prefix(*client) + " PRIVMSG " + target + " :" + message + "\r\n";
        sender(server->getClients()[i].client_fd, fullMessage);
    }
    else
    {
        for (i = 0; i < server->getChannels().size(); i++)
        {
            if (server->getChannels()[i].name == target)
            {
                std::cout << "--->in" << std::endl;
                std::string fullMessage = Prefix(*client) + " PRIVMSG " + target + " :" + message + "\r\n";
                std::cout << "size = " << server->getChannels()[i].clients.size() << std::endl;
                for (size_t j = 0; j < server->getChannels()[i].clients.size(); j++)
                    if ( server->getChannels()[i].clients[j].nickname != client->nickname)
                    {
                        std::cout << server->getChannels()[i].clients[j].client_fd << std::endl;
                        sender(server->getChannels()[i].clients[j].client_fd, fullMessage);
                    }
                std::cout << "---------------------" << "\n";
                break;
            }
        }
    }
}
