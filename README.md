PandoraBotIRC
=============

An IRC bot that acts as a Pandora chatter bot. 
To be entered in the cplusplus.com monthly [community competition](http://cppcomp.netne.net/showthread.php?tid=4)

####Planned features
- [x] Respond to channel messages with chatter bot replies
- [x] Use server/port/nick/channel from command line arguments (not hard coded)
- [x] Keep track of who is talking to the bot -- Be able to run multiple conversations at once.
- [x] Implement !BotID command -- Change the PandoraBot you're talking to
- [x] Implement !BotQuit command -- Exit gracefully
- [x] Implement !BotHalt command -- Temporarily stop the bot from replying to anything to keep the channel quiet. Puts the bot in an idle state.
- [x] Implement !BotResume command -- Resumes the bot after !BotHalt has been called.
- [x] Implement !BotTalk command -- Starts a conversation between a user and the bot. The bot will ignore a user until they have typed !BotTalk, then it will start talking to them.
- [x] Implement !BotStop command -- Stops a conversation between the user and the bot.
- [x] Implement !BotHelp command -- Sends a list of all possible commands
- [ ] Connect to multiple channels (OPTIONAL)

Building
========
####OS x 10.8+
- [Clone](https://github.com/Thumperrr/PandoraBotIRC/archive/master.zip) the git repository.
- Run the CMake GUI.
- Enter the directory you cloned the repo to in the source code field.
- Enter where you want to build the binaries (Usually in the same directory as the source code field)
- Select configure, choose Unix Makefiles.
    (Note: At this point, you may select which compiler you want to use to build the project. You will have to have SFML built properly with the compiler you choose.)
- Select Generate (assuming there have been no errors).
- From the terminal in the directory you chose to build the binaries, run `make`. 

####Other
You're on your own for now.

####Dependencies
- Requires SFML 2.0
- Requires Boost 1.35.0 or greater.

SFML and boost must be built and installed in the default place on os x (/usr/local/lib and /usr/local/include/)

- Requires clang 3.3, which should be installed with the Apple Command Line Tools which you can get from the Apple developer web page.
    If not, you can install it via MacPorts. 

Usage
=====
####Command Line
PandoraBotIRC is designed to be a command line tool. 
Four parameters must be supplied to `pbirc` when ran; server, port, nick, channel.
Example:
`./pbirc irc.freenode.net 6667 pandoraBot, cplusplus`
will start the bot on irc.freenode.net, port 6667, with nick "pandoraBot" in the channel "#cplusplus". 

####Talking to the bot
In an IRC chat, to begin a conversation with the bot, type the !BotTalk command. 
The bot should greet you.
Now, anything you type the bot will consider directed toward it, and will respond promptly.
To stop a conversation with the bot, type !BotStop.

The bot is capable of having conversations with multiple users at the same time. Using !BotTalk will not interfere with another users's conversation.

####Other Commands
- Typing "!BotQuit" will terminate the bot. 
- Typing "!BotHalt" will put the bot in an idle state, temporarily suspending it from responding to anyone. 
- Typing "!BotResume" will reverse the effects of !BotHalt
- Typing "!BotID <ID>" will change the bot you are talking to to the bot specified by the parameter ID. This command only works if you have already started a conversation with the bot by typing !BotTalk. For more on BotIDs, see the PandoraBot reference.
- Typing "!BotHelp" will tell you all of the commands the bot handles.

TODO:
=====
Licensing
