#pragma once

#include "ft_irc.hpp"

/**
 * Sends a message over the specified file descriptor.
 *
 * This function sends the provided message over the specified file descriptor.
 * It is typically used in socket programming to send data over a network connection.
 *
 * @param fd The file descriptor to send the message over.
 * @param msj The message to send. Should be a null-terminated string.
 *
 * @return Returns 0 on success, or -1 if an error occurs.
 */
void sender(int fd, const std::string msj);


/**
 * Parses a message received from a socket.
 *
 * @param fd The socket's file descriptor.
 * @return The parsed message, or an empty string on error.
 * @throws std::runtime_error If there's an error receiving data.
 */
std::string parseMessage(int fd);
