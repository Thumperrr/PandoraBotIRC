PandoraBotIRC
=============

An IRC bot that acts as a Pandora chatter bot. 
To be entered in the cplusplus.com monthly [http://cppcomp.netne.net/showthread.php?tid=4](community competition)

####Planned features
- [x] Respond to channel messages with chatter bot replies
- [ ] Use server/port/nick/channel from command line arguments (not hard coded)
- [ ] Connect to multiple channels
- [ ] Speak only when spoken to
- [ ] Keep track of who is talking to the bot -- Be able to run multiple conversations at once.
- [ ] Implement !BotID command -- Change the PandoraBot you're talking to
- [ ] Implement !BotQuit command -- Exit gracefully
- [ ] Implement !BotHalt command -- Temporarily stop the bot from replying to anything to keep the channel quiet
- [ ] Implement !BotResume command -- Resumes the bot after !BotHalt has been called.

Building
========
####OS x 10.8+
Clone the git repository, and run `make` from the terminal. 
Execute `pbirc.bin` to run the bot. 

####Other
You're on your own for now.

####Dependencies
Requires SFML 2.0
Requires Boost 1.35.0 or greater.

SFML and boost must be built and installed in the default place on os x (/usr/local/lib and /usr/local/include/)

Requires clang 3.3, which should be installed with the Apple Command Line Tools which you can get from the Apple developer web page.
    If not, you can install it via MacPorts. 
