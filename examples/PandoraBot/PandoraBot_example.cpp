#include "chatterbot/PandoraBot.hpp"
#include <iostream>

int main()
{
    pbirc::cb::PandoraBot chomsky("b0dafd24ee35a477");
    std::cout << chomsky.think("Hello there!") << std::endl;

    return 0;
}