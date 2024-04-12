/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:35:22 by iremoztimur       #+#    #+#             */
/*   Updated: 2024/04/10 17:53:17 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

PASS::PASS(Server *server, bool isAutherized): Command(server, isAutherized) {}

PASS::~PASS() {}

void PASS::execute(std::vector<std::string> command, ClientInfo *client)
{
	if (command.size() != 2)
	{
		sender(client->client_fd, ERR_NEEDMOREPARAMS(client->hostname, client->nickname, "PASS"));
		return ;
	}
	if (client->isRegistered)
	{
		sender(client->client_fd, ERR_ALREADYREGISTRED(client->hostname, client->nickname));
		return ;
	}

	if (server->getPassword() != command[1])
	{
		sender(client->client_fd, ERR_PASSWDMISMATCH(client->hostname, client->nickname));
		return ;
	}
	client->isRegistered = true;
}
