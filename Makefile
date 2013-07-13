#usage 
# make CFG=release

CPP = clang++
CC = clang
CPPFLAGS += -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors
INCLUDE = -Isrc -I/usr/local/include/

LIB = -framework sfml-network -framework sfml-system

ifeq ($(CFG),)
CFG=debug
endif

ifeq ($(CFG),debug)
CPPFLAGS += -ggdb -DDEBUG
else
CPPFLAGS += -O2
endif
CPPFLAGS += $(INCLUDE)


VPATH=src:src/util/:src/chatterbot/:src/irc/
TARGET=pbirc.bin

SRC = \
    main.cpp \
    Utility.cpp \
    PandoraBot.cpp \
    TCPConnection.cpp \
    IRCMessage.cpp \
    IRCConnection.cpp \
    PandoraIRCBot.cpp

OBJ = $(patsubst %.cpp, objs.$(CFG)/%.o, ${SRC})
DEP = $(patsubst %.cpp, deps.$(CFG)/%.d, ${SRC})

all: ${TARGET}

${TARGET}: ${OBJ}
	mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) $^ $(LIBDIR) $(LIB) -o $@

test:
	echo $(OBJ)
	echo $(DEP)


deps.$(CFG)/%.d: %.cpp
	mkdir -p $(dir $@)
	$(CPP) -MM -MP $(CPPFLAGS) $< | perl -pe 's#^(.*\.o)#deps.$(CFG)/$$1 objs.$(CFG)/$$1#' > $@

objs.$(CFG)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CPP) -c $(CPPFLAGS) $< -o $@

.PHONY: clean deps

clean:
	-rm -r objs.debug deps.debug ${TARGET}
	-rm -r objs.release deps.release 



# Unless "make clean" is called, include the dependency files
# which are auto-generated. Don't fail if they are missing
# (-include), since they will be missing in the first invocation!
-include ${DEP}