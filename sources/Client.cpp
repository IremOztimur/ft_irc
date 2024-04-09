#include "../includes/ft_irc.hpp"

void ClientInit(ClientInfo &user, int client_fd)
{
	user.client_fd = client_fd;
	user.nickname = "";
	user.username = "";
	user.hostname = "";
	user.servername = "";
	user.realname = "";
	user.pass_correct = 0;
	user.user_correct = 0;
	user.nick_correct = 0;
}
