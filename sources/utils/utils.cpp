#include "../includes/ft_irc.hpp"
#include <utils.hpp>

std::string Prefix(ClientInfo users)
{
    return ":" + users.nickname + "!" + users.username + "@" + users.hostname;
}

void sender(int fd, const std::string msj)
{
	send(fd, msj.c_str(), msj.size(), 0);
}

std::string parseMessage(int fd)
{
	const int MAX_BUFFER_SIZE = 256;
	char buffer[MAX_BUFFER_SIZE];

	ssize_t recvSize = recv(fd, buffer, MAX_BUFFER_SIZE - 1, 0);

	if (recvSize == -1)
		throw std::runtime_error("Failed to receive data from socket");

	else if (recvSize > 0)
	{
		buffer[recvSize] = '\0';
		std::string receivedData = buffer;
		std::cout << "readed = " << receivedData << std::endl;
		size_t newlinePos = receivedData.find_first_of("\r\n");
		std::string parsedMessage = receivedData.substr(0, newlinePos);

		return parsedMessage;
	}
	else
		return "";
}


// bool isPropertyInUse(Server *server, const std::string& value, ClientInfo *client, const std::string& errormessage)
// {
//     std::vector<ClientInfo>::const_iterator it;
//     for (it = server->getClients().begin(); it != server->getClients().end(); ++it)
//     {
//         if (it->username == value)
//         {
//             sender(client->client_fd, errormessage);
//             return true;
//         }
//     }
//     return false;
// }


int isClientInChannel(ClientInfo client, Channel channel)
{
	for (size_t i = 0; i < channel.clients.size(); ++i)
	{
		if (client.client_fd == channel.clients[i].client_fd)
			return true;
	}
	return false;
}
