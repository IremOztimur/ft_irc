#pragma once

#include "ft_irc.hpp"


// COLOR CODES
#define RESET "\033[39m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLACK "\033[30m"
#define GREY "\033[90m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define BLUE "\033[94m"
#define MAGENTA "\033[35m"

// ERROR MESSAGES
#define RPL_WELCOME(hostname, nickName, user) (std::string(":")  + " 001 " + nickName + " :Welcome to the Internet Relay Network " + nickName + "!" + user + "@"  + "\r\n")
#define RPL_YOURHOST(hostname, nickName) (std::string(":") + hostname + " 002 " + nickName + " :Your host is "  + hostname + "\r\n")
#define RPL_CREATED(hostname, nickName) (std::string(":") + hostname + " 003 " + nickName + " :This server was created " +  "\r\n")

#define RPL_NOTOPIC(hostname, nickName, channel) (std::string(":") + hostname + " 331 " + nickName + " " + channel + " :No topic is set" + "\r\n")
#define RPL_TOPIC(hostname, nickName, channel, topic) (std::string(":") + hostname + " 332 " + nickName + " " + channel + " :" + topic + "\r\n")
#define RPL_NAMEREPLY(hostname, nickName, channel, users) (std::string(":") + hostname + " 353 " + nickName + " = " + channel + " :" + users + "\r\n")
#define RPL_ENDOFNAMES(hostname, nickName, channel) (std::string(":") + hostname + " 366 " + nickName + " " + channel + " :End of /NAMES list" + "\r\n")

#define ERR_NOSUCHNICK(hostname, nickName) (std::string(":") + hostname + " 401 " + nickName + " :No such nick/channel" + "\r\n")
#define ERR_NOSUCHCHANNEL(hostname, nickName, channel) (std::string(":") + hostname + " 403 " + nickName + " " + channel + " :No such channel" + "\r\n")
#define ERR_UNKNOWNCOMMAND(hostname, nickName, cmd) (std::string(":") + hostname + " 421 " + nickName + " " + cmd + " :Unknown command" + "\r\n")
#define ERR_NONICKNAMEGIVEN(hostname, nickName) (std::string(":") + hostname + " 431 " + nickName + " :No nickname given" + "\r\n")
#define ERR_ERRONEUSNICKNAME(hostname, nickName, nick) (std::string(":") + hostname + " 432 " + nickName + " " + nick + " :Erroneus nickname" + "\r\n")
#define ERR_NICKNAMEINUSE(hostname, nickName) (std::string(":") + hostname + " 433 " + nickName + " :Nickname is already in use" + "\r\n")
#define ERR_USERNOTINCHANNEL(hostname, nickName, nick, channel) (std::string(":") + hostname + " 441 " + nickName + " " + nick + " " + channel + " :They aren't on that channel" + "\r\n")
#define ERR_NOTONCHANNEL(hostname, nickName, channel) (std::string(":") + hostname + " 442 " + nickName + " " + channel + " :You're not on that channel" + "\r\n")
#define ERR_USERONCHANNEL(hostname, nickName, nick, channel) (std::string(":") + hostname + " 443 " + nickName + " " + nick + " " + channel + " :is already on channel" + "\r\n")
#define ERR_NOTREGISTERED(hostname, nickName) (std::string(":") + hostname + " 451 " + nickName + " :You have not registered" + "\r\n")
#define ERR_NEEDMOREPARAMS(hostname, nickName, cmd) (std::string(":") + hostname + " 461 " + nickName + " " + cmd + " :Not enough parameters\r\n")
#define ERR_ALREADYREGISTRED(hostname, nickName) (std::string(":") + hostname + " 462 " + nickName + " :Unauthorized command (already registered)" + "\r\n")
#define ERR_PASSWDMISMATCH(hostname, nickName) (std::string(":") + hostname + " 464 " + nickName + " :Password incorrect" + "\r\n")
#define ERR_CHANOPRIVSNEEDED(hostname, nickName, channel) (std::string(":") + hostname + " 482 " + nickName + " " + channel + " :You're not channel operator" + "\r\n")
#define ERR_UMODEUNKNOWNFLAG(hostname) (std::string(":") + hostname + " 501 " + ":Unknown MODE flag" + "\r\n")
#define RPL_WHOREPLY(channel, nickname, username, hostname, servername, nickname2, hopcount, realname) (":myIRCServ 352 " + channel + " " + nickname + " " + username + " " + hostname + " " + servername + " " + nickname2 + " " + hopcount + " " + realname + " H :0 " + realname + "\r\n")
#define RPL_PASS(hostname, nickName) (std::string(":") + hostname + " 462 " + nickName + " :Password correct" + "\r\n")