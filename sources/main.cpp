/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:22:54 by iremoztimur       #+#    #+#             */
/*   Updated: 2024/04/09 20:30:52 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

int main(int argc, char **av)
{
	if (argc != 3)
		std::cout << RED << "Usage: ./ircserv <port> <password>" << RESET << std::endl;
	else
	{
		try
		{
			isValidPort(av[1]);
			isValidPassword(av[2]);
			Server server(av[1], av[2]);
			server.start();

		}
		catch(const std::exception& e)
		{
			std::cerr << RED << "ERROR: " << RESET << e.what()<< std::endl;
		}
	}
	return (0);
}
