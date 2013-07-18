add_subdirectory(chatterbot)
add_subdirectory(irc)
add_subdirectory(util)

set(SRCROOT "${PROJECT_SOURCE_DIR}/src")
set(SOURCES 
    ${SRCROOT}/main.cpp
    ${SOURCES}
    PARENT_SCOPE)