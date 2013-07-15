#usage 
# make CFG=release

CPP = clang++
CC = clang
CPPFLAGS += -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors
INCLUDE = -Isrc -I/usr/local/include/ -Iinclude/ -Iinclude/chatterbot/ -Iinclude/irc/ -Iinclude/util/

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
TARGET_LOC=bin/$(CFG)
TARGET=$(TARGET_LOC)/pbirc

SRC = \
    main.cpp \
    Utility.cpp \
    PandoraBot.cpp \
    TCPConnection.cpp \
    IRCMessage.cpp \
    IRCConnection.cpp \
    PandoraIRCBot.cpp

OBJ = $(patsubst %.cpp, $(TARGET_LOC)/objs/%.o, ${SRC})
DEP = $(patsubst %.cpp, $(TARGET_LOC)/deps/%.d, ${SRC})

all: ${TARGET}

${TARGET}: ${OBJ}
	mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) $^ $(LIBDIR) $(LIB) -o $@

test:
	echo $(OBJ)
	echo $(DEP)


$(TARGET_LOC)/deps/%.d: %.cpp
	mkdir -p $(dir $@)
	$(CPP) -MM -MP $(CPPFLAGS) $< | perl -pe 's#^(.*\.o)#deps.$(CFG)/$$1 objs.$(CFG)/$$1#' > $@

$(TARGET_LOC)/objs/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CPP) -c $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	-rm -rf bin

# Unless "make clean" is called, include the dependency files
# which are auto-generated. Don't fail if they are missing
# (-include), since they will be missing in the first invocation!
-include ${DEP}