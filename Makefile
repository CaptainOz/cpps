
CWD  = ${shell pwd}
BIN  = bin
CPPS = cpps
CLI  = cli
TEST = tests
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
			Exceptions.o \
			Token.o \

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


# Test Targets
test-all: test-tokenizer

testTokenizerBuildObjs = $(patsubst %,$(TEST)/%,test_tokenizer.o)
testTokenizerDirObjs   = $(patsubst %,$(BUILD)/%,$(testTokenizerBuildObjs))
test-tokenizer: cpps $(testTokenizerBuildObjs)
	$(CC_FLAGS) $(LFLAGS) -o $(BIN)/test_tokenizer $(testTokenizerDirObjs) $(cppsDirObjs)

