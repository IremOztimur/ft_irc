#pragma once

#include "ft_irc.hpp"


class Server
{
	protected:
		int socket_fd;
		std::string port;
		std::string password;
		std::vector<ClientInfo> clients;
		std::vector<struct pollfd> poll_fd;
		std::vector<Channel> channels;
        CommandHandler *commandHandler;


	public:
		Server(std::string port, std::string password);
		~Server();

    std::vector<Channel>& getChannels() {
    return channels;
}
		void start();
		void setup();
		void ClientAccept();
		void MessageHandler();
		void WELCOME(ClientInfo *client);
		void removeClient(int client_fd);
		std::vector<ClientInfo>& getClients() { return clients; }


    // Getters
		std::string getPassword() const { return password; };
};
