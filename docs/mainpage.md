PandoraBotIRC {#mainpage}
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
Clone the git repository, and run `make` from the terminal. 
Execute `pbirc.bin` to run the bot. 

####Other
You're on your own for now.

####Dependencies
- Requires SFML 2.0
- Requires Boost 1.35.0 or greater.

SFML and boost must be built and installed in the default place on os x (/usr/local/lib and /usr/local/include/)

- Requires clang 3.3, which should be installed with the Apple Command Line Tools which you can get from the Apple developer web page.
    If not, you can install it via MacPorts. 
