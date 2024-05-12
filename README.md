# Internet Relay Chat Project (42 Style)

## USAGE

```bash
make
./ircserv PORT PASS
```

## Terminologies
### Clients
A client is anything connecting to a server that is not another
   server.  Each client is distinguished from other clients by a unique
   nickname having a maximum length of nine (9) characters. In addition to the nickname, all servers must have the
   following information about all clients: the real name of the host
   that the client is running on, the username of the client on that
   host, and the server to which the client is connected.

## Operators
 To allow a reasonable amount of order to be kept within the IRC
   network, a special class of clients (operators) is allowed to perform
   general maintenance functions on the network. For this project we granted these commands:
   - MODE
- KICK
- TOPIC
- NOTICE
- INVITE

## Channels
A channel is a named group of one or more clients which will all
   receive messages addressed to that channel.  The channel is created
   implicitly when the first client joins it, and the channel ceases to
   exist when the last client leaves it.  While channel exists, any
   client can reference the channel using the name of the channel.

Channels names are strings (beginning with a '&' or '#' character) of
length up to 200 characters.

### Channel Operators
The commands which may only be used by channel operators are:

        KICK    - Eject a client from the channel
        MODE    - Change the channel's mode
        INVITE  - Invite a client to an invite-only channel (mode +i)
        TOPIC   - Change the channel topic in a mode +t channel

## Connection Registration Commands

## PASS

**Command:** `PASS`

**Parameters:** `<password>`

The `PASS` command is used to set a 'connection password'.  The
password can and must be set before any attempt to register the
connection is made. 

Example:

           PASS secretpasswordhere

## NICK

**Command:** `NICK`

**Parameters:** `<nickname> [ <hopcount> ]`

NICK message is used to give user a nickname or change the previous
one.  The <hopcount> parameter is only used by servers to indicate
how far away a nick is from its home server.  A local connection has
a hopcount of 0.


## USER

**Command:** `USER`

**Parameters:** `<username> <hostname> <servername> <realname>`

The USER message is used at the beginning of connection to specify
the username, hostname, servername and realname of s new user.  It is
also used in communication between servers to indicate new user
arriving on IRC, since only after both USER and NICK have been
received from a client does a user become registered.

## Channel operations

## JOIN

**Command:** `JOIN`

**Parameters:** `<channel>{,<channel>} [<key>{,<key>}]`

The JOIN command is used by client to start listening a specific
   channel. Whether or not a client is allowed to join a channel is
   checked only by the server the client is connected to; all other
   servers automatically add the user to the channel when it is received
   from other servers.  The conditions which affect this are as follows:

  1.  the user must be invited if the channel is invite-only;

  2.  the user's nick/username/hostname must not match any
               active bans;

  3.  the correct key (password) must be given if it is set.

Examples:

   ```bash
JOIN #foobar
```
; join channel #foobar.

## MODE

**Command:** `MODE`

The MODE command is a dual-purpose command in IRC. It allows both
   usernames and channels to have their mode changed.

### Channel modes
**Parameters:**  `<channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>]
               [<ban mask>]`

The MODE command is provided so that channel operators may change the
   characteristics of `their' channel.  It is also required that servers
   be able to change channel modes so that channel operators may be
   created.

   The various modes available for channels are as follows:

           o - give/take channel operator privileges;
           p - private channel flag;
           s - secret channel flag;
           i - invite-only channel flag;
           t - topic settable by channel operator only flag;
           b - set a ban mask to keep users out;
           v - give/take the ability to speak on a moderated channel;
           k - set a channel key (password).
           n - no messages to channel from clients on the outside;
           m - moderated channel;
           l - set the user limit to channel;

### User modes
**Parameters:**  `<nickname> {[+|-]|i|w|s|o}]`

 The user MODEs are typically changes which affect either how the
   client is seen by others or what 'extra' messages the client is sent.
   A user MODE command may only be accepted if both the sender of the
   message and the nickname given as a parameter are both the same.

   The available modes are as follows:

           i - marks a users as invisible;
           s - marks a user for receipt of server notices;
           w - user receives wallops;
           o - operator flag.

## INVITE
**Command:** `INVITE`

**Parameters:** `<nickname> <channel>`

The INVITE message is used to invite users to a channel.  The
   parameter <nickname> is the nickname of the person to be invited to
   the target channel <channel>.

 Examples:

```bash
:Irem INVITE Fatih #42
```

; User Irem inviting Fatih to channel #42

## TOPIC
**Command:** `TOPIC`

**Parameters:** `<channel> [<topic>]`

 The TOPIC message is used to change or view the topic of a channel.
   The topic for channel <channel> is returned if there is no <topic>
   given.  If the <topic> parameter is present, the topic for that
   channel will be changed, if the channel modes permit this action.

```bash
 :Irem TOPIC #42 :New topic
```

;User Irem setting the topic.

## KICK
**Command:** `KICK`

**Parameters:** `<channel> <user> [<comment>]`

The KICK command can be  used  to  forcibly  remove  a  user  from  a
   channel.   It  'kicks  them  out'  of the channel (forced PART). Only a channel operator may kick another user out of a  channel.

```bash
:Irem KICK #42 Fatih 
```
KICK message from Irem to remove Fatih from channel #42

## PART
**Command:** `PART`

**Parameters:** `<channel>{,<channel>}`

The PART message causes the client sending the message to be removed
   from the list of active users for all given channels listed in the
   parameter string.

```bash
PART #42,&group5 
```

; leave both channels "&group5" and "#42".

## Sending Messages
The main purpose of the IRC protocol is to provide a base for clients
   to communicate with each other. `PRIVMSG` and `NOTICE` are the only
   messages available which actually perform delivery of a text message
   from one client to another - the rest just make it possible and try
   to ensure it happens in a reliable and structured manner.

## PRIVMSG
**Command:** `PRIVMSG`

**Parameters:** `<receiver>{,<receiver>} <text to be sent>`
 
 PRIVMSG is used to send private messages between users.  <receiver>
   is the nickname of the receiver of the message.  <receiver> can also
   be a list of names or channels separated with commas.

```bash
:Irem PRIVMSG Fatih :HEYYYYY
```
; Message from Irem to Fatih.
   
## NOTICE
**Command:** `NOTICE`

**Parameters:** `<nickname> <text>`

The NOTICE message is used similarly to PRIVMSG.  The difference
   between NOTICE and PRIVMSG is that automatic replies must never be
   sent in response to a NOTICE message.

## User Based Queries
**Command:** `WHO`

**Parameters:** `[<name> [<o>]]`

 The WHO message is used by a client to generate a query which returns
   a list of information which 'matches' the <name> parameter given by
   the client.  In the absence of the <name> parameter, all visible
   (users who aren't invisible (user mode +i) and who don't have a
   common channel with the requesting client) are listed.

```bash
WHO *.fi 
```
; List all users who match against "*.fi".

## Miscellaneous Messages
Messages in this category do not fit into any of the above categories
   but are nonetheless still a part of and required by the protocol.
   
## PING
**Command:** `PING`

**Parameters:** `<server1> [<server2>]`

The PING message is used to test the presence of an active client at
   the other end of the connection.  A PING message is sent at regular
   intervals if no other activity detected coming from a connection.  If
   a connection fails to respond to a PING command within a set amount
   of time, that connection is closed.

```bash
PING tolsun.oulu.fi 
```
; server sending a PING message to another server to indicate it is still alive.
