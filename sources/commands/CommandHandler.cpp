/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:58:57 by iremoztimur       #+#    #+#             */
/*   Updated: 2024/05/09 23:12:35 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"


CommandHandler::CommandHandler(Server *server): server(server)
{
	commands["PASS"] = new PASS(server, false);
    commands["NICK"] = new NICK(server, false);
    commands["USER"] = new USER(server, false);
	commands["JOIN"] = new JOIN(server, true);
	commands["PRIVMSG"] = new PRIVMSG(server, true);
	commands["NOTICE"] = new NOTICE(server, true);
	commands["WHO"] = new WHO(server, true);
	commands["MODE"] = new MODE(server, true);
	commands["PING"] = new PING(server, false);
	commands["TOPIC"] = new TOPIC(server, true);
	commands["PART"] = new PART(server, true);
	commands["KICK"] = new KICK(server, true);
	commands["INVITE"] = new INVITE(server, true);
    commands["QUIT"] = new QUIT(server, true);
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
