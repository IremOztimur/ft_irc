#include "../includes/Server.hpp"

Server::Server(std::string port, std::string password): port(port), password(password){}

Server::~Server()
{
	std::cout << RED << "-----------------------" << RESET << std::endl;
	std::cout << RED << "Server destroyed" << RESET << std::endl;
}

void Server::start()
{
	std::cout << std::endl;
	std::cout << GREEN << "----- Server started -----" << RESET << std::endl;
	std::cout << "Port: " << this->port << std::endl;
	std::cout << "Pass: " << this->password << std::endl;

	setup();

	while (poll(&poll_fd[0], poll_fd.size(), -1))
		MessageHandler();
}

void Server::setup()
{
	int opt = 1;
	this->socket_fd = socket(AF_INET6, SOCK_STREAM, 0);
	fcntl(this->socket_fd, F_SETFL, O_NONBLOCK);

	if (this->socket_fd < 0)
		throw std::runtime_error("server socket creation failed");

	sockaddr_in6 server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin6_family = AF_INET6;
	server_addr.sin6_addr = in6addr_any;
	server_addr.sin6_port = htons(std::stoi(port));

	if (setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw std::runtime_error("socket option");

	if (bind(this->socket_fd, reinterpret_cast<sockaddr *>(&server_addr), sizeof(server_addr)) < 0)
		throw std::runtime_error("bind server socket failed");

	else
		std::cout << "Server is active now" << std::endl;

	if (listen(this->socket_fd, 5) < 0)
		throw std::runtime_error("listening error");

	poll_fd.resize(1);
	poll_fd[0].fd = socket_fd;
	poll_fd[0].events = POLLIN;
}

void Server::MessageHandler()
{
	for (size_t i = 0; i < poll_fd.size(); i++)
	{
		if (poll_fd[i].revents & POLLIN)
		{
			ClientAccept();
			if (i != 0)
			{
				std::string buffer = parseMessage(poll_fd[i].fd);
				//printf("Received message: %s\n", buffer.c_str());
			}
			if (poll_fd[i].revents & POLLHUP)
			{
				//QUIT("Control + C", i - 1);
				continue;
			}
		}
	}
}

void Server::ClientAccept()
{
		if (poll_fd[0].revents & POLLIN) {
			sockaddr_in6 client_addr;
			socklen_t client_len = sizeof(client_addr);
            int client_fd = accept(this->socket_fd, reinterpret_cast<sockaddr *>(&client_addr), &client_len);
            if (client_fd < 0)
                throw std::runtime_error("accept error");
            else {
                ClientInfo client;
                ClientInit(client, client_fd);

                char ipstr[INET6_ADDRSTRLEN];
                inet_ntop(AF_INET6, &(client_addr.sin6_addr), ipstr, sizeof(ipstr));

                sender(client.client_fd, "Welcome to the server, please enter your password: |COMMAND:PASS|\r\n");

                this->clients.push_back(client);
                std::cout << "New connection from " << ipstr << ":" << ntohs(client_addr.sin6_port) << std::endl;
                fcntl(client_fd, F_SETFL, O_NONBLOCK);

                poll_fd.resize(poll_fd.size() + 1);
                poll_fd[poll_fd.size() - 1].fd = client_fd;
                poll_fd[poll_fd.size() - 1].events = POLLIN;
			}
			printf("New connection %d\n" , client_fd);
		}
}

