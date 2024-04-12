/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:58:57 by iremoztimur       #+#    #+#             */
/*   Updated: 2024/04/10 19:35:02 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"


CommandHandler::CommandHandler(Server *server): server(server)
{
	commands["PASS"] = new PASS(server, false);
}

CommandHandler::~CommandHandler()
{
	for (std::map<std::string, Command*>::iterator it = commands.begin(); it != commands.end(); it++)
		delete it->second;
}

void CommandHandler::invoke(const std::string &message, ClientInfo *client)
{
	std::stringstream MessageParser(message);
	std::string syntax;

	while (std::getline(MessageParser, syntax))
	{
		syntax.erase(std::find(syntax.begin(), syntax.end(), '\r'), syntax.end());
		std::string command_name = syntax.substr(0, syntax.find(' '));

		try {
			Command *command = commands.at(command_name);

			std::vector<std::string> args;
			std::string buffer;
			std::stringstream	ss(syntax.substr(command_name.length(), syntax.length()));

			while (ss >> buffer)
				args.push_back(buffer);

			if (!client->isRegistered && command->getAuthStatus())
			{
				sender(client->client_fd, ERR_NOTREGISTERED(client->hostname, client->nickname));
				return ;
			}
			command->execute(args, client);
		}
		catch (const std::out_of_range &e){
			sender(client->client_fd, ERR_UNKNOWNCOMMAND(client->hostname, client->nickname, command_name));
		}
	}
}
