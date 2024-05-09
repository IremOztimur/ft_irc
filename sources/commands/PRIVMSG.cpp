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

    // Hedef bir kanal mı yoksa kullanıcı mı olduğunu kontrol et
    if (targetExists)
    {
        // Hedef bir kullanıcı ise mesajı gönder
        std::string fullMessage = Prefix(*client) + " PRIVMSG " + target + " :" + message + "\r\n";
        sender(server->getClients()[i].client_fd, fullMessage);
    }
    else
    {
        // Hedef bir kanal ise mesajı gönder
        for (i = 0; i < server->getChannels().size(); i++)
        {
            if (server->getChannels()[i].name == target)
            {
                std::string fullMessage = Prefix(*client) + " PRIVMSG " + target + " :" + message + "\r\n";

                for (size_t j = 0; j <  server->getChannels()[i].clients.size(); j++)
                    if ( server->getChannels()[i].clients[j].nickname != client->nickname)
                        sender( server->getChannels()[i].clients[j].client_fd, fullMessage);
                break;
            }
        }
    }
}
