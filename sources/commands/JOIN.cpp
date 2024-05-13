#include "../../includes/ft_irc.hpp"

JOIN::JOIN(Server *server, bool isAutherized) : Command(server, isAutherized) {}

JOIN::~JOIN() {}

void JOIN::execute(std::vector<std::string> command, ClientInfo *client)
{
    std::string channel = command[0];
    bool channelExists = false;

    for (size_t i = 0; i < server->getChannels().size(); ++i)
    {
        if (server->getChannels()[i].name == channel)
        {
            channelExists = true;
            break;
        }
    }

    if (channelExists)
    {
        for (size_t i = 0; i < server->getChannels().size(); i++)
        {
            if (server->getChannels()[i].name == channel)
            {
                if (server->getChannels()[i].isPublic == false)
                {
                    sender(client->client_fd, Prefix(*client) + ":server.name 473 " + client->nickname + " " + channel + " :Cannot join channel (+i) - you must be invited.\r\n");
                    return;
                }
                for (size_t j = 0; j < server->getChannels()[i].clients.size(); j++)
                {
                    if (server->getChannels()[i].clients[j].client_fd == client->client_fd)
                        return;
                }
            }
        }
        for (size_t i = 0; i < server->getChannels().size(); ++i)
        {
            if (server->getChannels()[i].name == channel)
            {
                server->getChannels()[i].clients.push_back(*client);
                sender(client->client_fd, Prefix(*client) + " JOIN " + channel + "\r\n");
                if (server->getChannels()[i].topic != "")
                    sender(client->client_fd, RPL_TOPIC(client->hostname, client->nickname, server->getChannels()[i].name, server->getChannels()[i].topic));
                for (size_t j = 0; j < server->getChannels()[i].clients.size() - 1; j++)
                {
                    sender(client->client_fd, Prefix(server->getChannels()[i].clients[j]) + " JOIN " + channel + "\r\n");
                    if (server->getChannels()[i].clients[j].isOperator)
                    {
                        sender(client->client_fd, "MODE " + channel + " +o " + server->getChannels()[i].clients[j].nickname + "\r\n");
                    }
                }
                for (size_t j = 0; j < server->getChannels()[i].clients.size() - 1; j++)
                {
                    for (size_t k = 0; k < server->getChannels()[i].clients.size(); k++)
                    {
                        if (server->getChannels()[i].clients[j].client_fd != server->getChannels()[i].clients[k].client_fd)
                        {
                            std::string otherUserMessage = Prefix(server->getChannels()[i].clients[k]) + " JOIN " + channel + "\r\n";
                            sender(server->getChannels()[i].clients[j].client_fd, otherUserMessage);
                            if (server->getChannels()[i].clients[k].isOperator)
                            {
                                sender(server->getChannels()[i].clients[j].client_fd, "MODE " + channel + " +o " + server->getChannels()[i].clients[k].nickname + "\r\n");
                            }
                        }
                    }
                }
                return;
            }
        }
    }
    else
    {
        if (channel[0] == '#' && channel.size() > 1)
        {

            Channel newChannel;
            newChannel.name = channel;
            newChannel.topic = "";
            newChannel.isPublic = true;
            newChannel.clients.push_back(*client);
            server->getChannels().push_back(newChannel);

            std::string message = Prefix(*client) + " JOIN " + channel + "\r\n";
            // Yeni kullanıcıyı operatör yap
            std::string modeMessage = "MODE " + channel + " +o " + client->nickname + "\r\n";
            server->getChannels()[server->getChannels().size() - 1].operators.push_back(client->client_fd);
            server->getChannels()[server->getChannels().size() - 1].clients[0].isOperator = true;
            server->getChannels()[server->getChannels().size() - 1].isPublic = true;
            sender(client->client_fd, message);
            sender(client->client_fd, modeMessage);
            return;
        }
        else
            sender(client->client_fd, Prefix(*client) + "need #\r\n");
    }
}
