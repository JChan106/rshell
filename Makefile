CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic -Qunused-arguments 
DIRECT = bin
SRCS = src/
SRC := $(wildcard src/*.cpp) #list of source files
OBJS := $(addprefix bin/, $(notdir $(SRC:.cpp=.o))) #object file list

# @ puts all outputs of compilation in the file on the left of the :
#  < is first item in dependencies list
#  input   output
rshell: $(DIRECT)/rshell

all: $(DIRECT)/ $(OBJS)

$(DIRECT)/rshell: $(DIRECT)/ $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(DIRECT)/%.o: $(SRCS)/%.cpp #rule for building objects
	$(CC) $(CFLAGS) -c -o $@ $<

$(DIRECT)/:
	mkdir -p $@

clean:
	rm -r $(DIRECT)
