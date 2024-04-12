/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:05:08 by iremoztimur       #+#    #+#             */
/*   Updated: 2024/04/12 15:09:16 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

class Server;

class Command
{
	protected:
		Server *server;
		bool isAutherized;

	public:
		Command(Server *server, bool isAutherized = true): server(server), isAutherized(isAutherized) {};
		virtual ~Command(){};

		bool getAuthStatus() const { return isAutherized; };

		virtual void execute(std::vector<std::string> command, ClientInfo *client) = 0;
};


class PASS: public Command
{
	public:
		PASS(Server *server, bool isAutherized);
		~PASS();

		void execute(std::vector<std::string> command, ClientInfo *client);
};
