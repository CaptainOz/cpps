
CWD  = ${shell pwd}
BIN  = bin
CPPS = cpps
CLI  = cli
BUILD = build

# Compiler
CC_BIN = g++

# Linker flags
LFLAGS = 

# Compiler flags
CCFLAGS = $(CLFLAGS)

# Compiler and compiler flags
CC_FLAGS = $(CC_BIN) $(CCFLAGS)


%.o : %.cpp
	$(CC_FLAGS) -I$(CWD) -c -o $(BUILD)/$@ $<

#cli.%.o : $(CLI)/%.cpp
#	$(CC_FLAGS) -I$(CWD) -c -o $(BUILD)/$@ $<

all: cpps cli

# CPPS Core
cppsObjs 	= \
			Interpreter.o \
			Object.o \

cppsBuildObjs = $(patsubst %,$(CPPS)/%,$(cppsObjs))
cppsDirObjs   = $(patsubst %,$(BUILD)/%,$(cppsBuildObjs))
cpps: $(cppsBuildObjs)

# CPPS Command Line Interface
cliObjs		= \
			cppscli.o \

cliBuildObjs = $(patsubst %,$(CLI)/%,$(cliObjs))
cliDirObjs	 = $(patsubst %,$(BUILD)/%,$(cliBuildObjs)) $(cppsDirObjs)
cli: cpps $(cliBuildObjs)
	$(CC_FLAGS) $(LFLAGS) -o $(BIN)/cpps $(cliDirObjs)

