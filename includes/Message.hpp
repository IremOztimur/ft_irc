#pragma once

#include <ft_irc.hpp>

class Message: public Server
{
	private:
		Message();
		~Message();
	public:
		void WELCOME(int);
		void PASS(std::string, int);
		void NICK(std::string, int);
		void USER(ClientInfo &, std::string);
		void JOIN(std::string massage, int i);
		void PRIVMSG(std::string massage, int i);
		void KICK(std::string massage, int i);
		void MODE(std::string massage, int i);
		void WHO(std::string massage, int i);
		void TOPIC(std::string massage, int i);
		void LIST(std::string massage, int i);
		void INVITE(std::string massage, int i);
		void QUIT(std::string massage, int i);
};
