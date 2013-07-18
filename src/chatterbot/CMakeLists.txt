set(INCROOT "${PROJECT_SOURCE_DIR}/include/chatterbot")
set(SRCROOT "${PROJECT_SOURCE_DIR}/src/chatterbot")

set(SOURCES
    ${INCROOT}/ChatterBot.hpp
    ${INCROOT}/PandoraBot.hpp
    ${SRCROOT}/PandoraBot.cpp
    ${SOURCES}
    PARENT_SCOPE
)