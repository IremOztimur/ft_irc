/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:35:22 by iremoztimur       #+#    #+#             */
/*   Updated: 2024/05/12 12:57:45 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

PASS::PASS(Server *server, bool isAutherized): Command(server, isAutherized) {}

PASS::~PASS() {}

void PASS::execute(std::vector<std::string> command, ClientInfo *client)
{
	if (command.size() != 1)
	{
		sender(client->client_fd, ERR_NEEDMOREPARAMS(client->hostname, client->nickname, "PASS"));
		return ;
	}
	if (client->isRegistered)
	{
		sender(client->client_fd, ERR_ALREADYREGISTRED(client->hostname, client->nickname));
		return ;
	}
    if (server->getPassword() != command[0])
    {
        std::string message = Prefix(*client) + " " + ERR_PASSWDMISMATCH(client->hostname, client->nickname);
        sender(client->client_fd, message);
        return ;
    }
	client->isRegistered = true;
	sender(client->client_fd, Prefix(*client) + "Please enter your nick |COMMAND:NICK|\r\n");
	std::cout << "Client " << client->nickname << " is registered." << std::endl;
}
