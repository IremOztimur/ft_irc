#include "../../includes/ft_irc.hpp"

INVITE::INVITE(Server *server, bool isAutherized) : Command(server, isAutherized) {}

INVITE::~INVITE() {}

void INVITE::execute(std::vector<std::string> command, ClientInfo *client)
{
    std::string user = command[0];
    std::string channel = command[1];
    for (unsigned int a = 0; a < server->getChannels().size(); a++)
    {
        if (server->getChannels()[a].name == channel)
        {
            // İlgili kullanıcının kanalda olup olmadığını kontrol et
            bool foundClient = false;
            for (unsigned int k = 0; k < server->getChannels()[a].clients.size(); k++)
            {
                if (client->client_fd == server->getChannels()[a].clients[k].client_fd)
                {
                    foundClient = true;
                    break;
                }
            }

            if (foundClient)
            {
                // Kullanıcı kanalda ise, operator mü kontrol et
                for (unsigned int k = 0; k < server->getChannels()[a].operators.size(); k++)
                {
                    if (client->client_fd == server->getChannels()[a].operators[k])
                    {
                        // Tüm kullanıcıları döngüye al ve davet edilecek kullanıcıyı bul
                        for (unsigned long j = 0; j < server->getClients().size(); j++)
                        {
                            if (server->getClients()[j].nickname == user)
                            {
                                sender(server->getClients()[j].client_fd, Prefix(*client) + " " + "INVITE " + user + " " + channel + "\r\n");
                                break; // Kullanıcıyı bulduk, döngüyü sonlandır
                            }
                        }
                    }
                }
            }
        }
    }
}
