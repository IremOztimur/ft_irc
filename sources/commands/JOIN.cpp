#include "../../includes/ft_irc.hpp"

JOIN::JOIN(Server *server, bool isAutherized) : Command(server, isAutherized) {}

JOIN::~JOIN() {}

void JOIN::execute(std::vector<std::string> command, ClientInfo *client)
{
    std::string channel = command[0];
    std::vector<Channel> channels = server->getChannels();
    bool channelExists = false;

    // Kanalın var olup olmadığını kontrol et
    for (size_t i = 0; i < channels.size(); ++i)
    {
        if (channels[i].name == channel)
        {
            channelExists = true;
            break;
        }
    }

    if (channelExists)
    {
        for (size_t i = 0; i < channels.size(); ++i)
        {
            if (channels[i].name == channel)
            {
                server->getChannels()[i].clients.push_back(*client);
                std::string modeMessage = "MODE " + channel + " +o " + server->getChannels()[i].clients[0].nickname + "\r\n"; //
                sender(client->client_fd, Prefix(*client) + " JOIN " + channel + "\r\n");
                sender(client->client_fd, modeMessage);
                // Kanalda bulunan tüm kullanıcılara JOIN mesajını gönder ve yeni kullanıcının bilgilerini gönder
                for (size_t j = 0; j < server->getChannels()[i].clients.size() - 1; j++)
                {
                    sender(client->client_fd, Prefix(server->getChannels()[i].clients[j]) + " JOIN " + channel + "\r\n");
                    sender(client->client_fd, modeMessage);
                }
                // Yeni kullanıcı, kanalda bulunan diğer kullanıcıları da görsün
                for (size_t j = 0; j < server->getChannels()[i].clients.size() - 1; j++)
                {
                    for(size_t k = 0; k < server->getChannels()[i].clients.size(); k++)
                    {
                        if(server->getChannels()[i].clients[j].client_fd != server->getChannels()[i].clients[k].client_fd)
                        {
                            std::string otherUserMessage = Prefix(server->getChannels()[i].clients[k]) + " JOIN " + channel + "\r\n";
                            sender(server->getChannels()[i].clients[j].client_fd, otherUserMessage);
                            sender(server->getChannels()[i].clients[j].client_fd, modeMessage);
                        }
                    }

                }
                return;
            }
        }
    }
    else
    {
        Channel newChannel;
        newChannel.name = channel;
        newChannel.clients.push_back(*client);
        server->getChannels().push_back(newChannel);

        std::string message = Prefix(*client) + " JOIN " + channel + "\r\n";
        sender(client->client_fd, message);

        // Yeni kullanıcıyı operatör yap
        std::string modeMessage = "MODE " + channel + " +o " + client->nickname + "\r\n";
        sender(client->client_fd, modeMessage);
		server->getChannels()[server->getChannels().size() - 1].operators.push_back(client->client_fd);

    }
}