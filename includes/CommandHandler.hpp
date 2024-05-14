#include "ft_irc.hpp"

class CommandHandler
{
	protected:
		Server								*server;
		std::map<std::string, Command *>	commands;

	public:
		CommandHandler(Server *server);
		~CommandHandler();

		void invoke(const std::string &message, ClientInfo *client);
};
