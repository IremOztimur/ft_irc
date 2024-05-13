#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <algorithm>
#include <poll.h>
#include <map>
#include <sstream>

struct ClientInfo
{
	std::string username;
	std::string hostname;
	std::string servername;
	std::string realname;
	std::string nickname;

	int client_fd;
	int user_correct;
	int nick_correct;
	bool isOperator;
	bool isRegistered;
};

struct Channel
{
	std::string name;
	std::vector<ClientInfo> clients;
	std::vector<int> operators;
	std::string topic;
	bool isPublic;
};
