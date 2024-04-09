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

	public:
		Server(std::string port, std::string password);
		~Server();

		void start();
		void setup();
		void ClientAccept();
		void MessageHandler();
};
