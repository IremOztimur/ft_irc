#include "../../includes/ft_irc.hpp"

NOTICE::NOTICE(Server *server, bool isAutherized) : Command(server, isAutherized) {}

NOTICE::~NOTICE() {}

void NOTICE::execute(std::vector<std::string> command, ClientInfo *client)
{
	if (command.size() < 2)
	{
		sender(client->client_fd, ERR_NEEDMOREPARAMS(client->hostname, client->nickname, "NOTICE"));
		return;
	}

	std::string target = command[0];
	std::string message = "";
	for (std::vector<std::string>::size_type i = 1; i < command.size(); ++i)
	{
		message += command[i];
		if (i != command.size() - 1)
		{
			message += " ";
		}
	}

	const std::vector<ClientInfo> &clients = server->getClients();
	std::vector<Channel> &channels = server->getChannels();
	bool targetExists = false;

	// Kullanıcının var olup olmadığını kontrol et
	for (size_t i = 0; i < clients.size(); ++i)
	{
		if (clients[i].nickname == target)
		{
			targetExists = true;
			std::string fullMessage = Prefix(*client) + " NOTICE " + target + " :" + message + "\r\n";
			if (clients[i].client_fd != client->client_fd)
				sender(clients[i].client_fd, fullMessage);
			break;
		}
	}

	// Eğer hedef bir kanalsa, kanaldaki kullanıcılara mesaj gönder
	if (!targetExists)
	{
		for (size_t i = 0; i < channels.size(); ++i)
		{
			if (channels[i].name == target)
			{
				bool userInChannel = false;
				targetExists = true;
				std::string fullMessage = Prefix(*client) + " NOTICE " + target + " :" + message + "\r\n";
				for (size_t j = 0; j < channels[i].clients.size(); ++j)
				{
					if (channels[i].clients[j].nickname == client->nickname)
					{
						userInChannel = true;
						break;
					}
				}
				for (size_t j = 0; j < channels[i].clients.size(); ++j)
				{
					if (channels[i].clients[j].nickname != client->nickname && userInChannel)
					{
						sender(channels[i].clients[j].client_fd, fullMessage);
					}
					else
					{
						sender(client->client_fd, ERR_CANNOTSENDTOCHAN(client->hostname, client->nickname, target));
						return;
					}
				}
				break;
			}
		}
	}

	// Hedef bulunamazsa, hata mesajı gönder
	if (!targetExists)
	{
		sender(client->client_fd, ERR_NOSUCHNICK(client->hostname, client->nickname));
	}
}
