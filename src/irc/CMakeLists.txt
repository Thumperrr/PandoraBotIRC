set(INCROOT "${PROJECT_SOURCE_DIR}/include/irc")
set(SRCROOT "${PROJECT_SOURCE_DIR}/src/irc")

set(SOURCES
    ${INCROOT}/IRCBot.hpp
    ${INCROOT}/IRCConnection.hpp
    ${SRCROOT}/IRCConnection.cpp
    ${INCROOT}/IRCMessage.hpp
    ${SRCROOT}/IRCMessage.cpp
    ${INCROOT}/PandoraIRCBot.hpp
    ${SRCROOT}/PandoraIRCBot.cpp
    ${INCROOT}/TCPConnection.hpp
    ${SRCROOT}/TCPConnection.cpp
    ${SOURCES}
    PARENT_SCOPE
)