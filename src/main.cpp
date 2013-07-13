#include "irc/PandoraIRCBot.hpp"

#include <iostream>
#include <string>

int main()
{
	pbirc::irc::PandoraIRCBot bot("irc.freenode.net", 6667, "thumperrr_bot", "#ChessPlusPlus");

	return bot.run();
}