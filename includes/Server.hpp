/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioztimur <ioztimur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:43:30 by ioztimur          #+#    #+#             */
/*   Updated: 2024/05/14 18:43:33 by ioztimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

class Server
{
	protected:
		int							socket_fd;
		std::string					port;
		std::string					password;
		std::vector<ClientInfo>		clients;
		std::vector<struct pollfd>	poll_fd;
		std::vector<Channel>		channels;
		CommandHandler				*commandHandler;


	public:
		Server(std::string port, std::string password);
		~Server();

		void start();
		void setup();
		void ClientAccept();
		void MessageHandler();
		void WELCOME(ClientInfo *client);
		void removeClient(int client_fd);


	// Getters
		std::string getPassword() const { return password; };
		std::vector<ClientInfo>& getClients() { return clients; }
		std::vector<Channel>& getChannels() {return channels;}
};
