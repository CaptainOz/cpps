
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
CCFLAGS = $(CLFLAGS) -Wall -std=c++0x

# Compiler and compiler flags
CC_FLAGS = $(CC_BIN) $(CCFLAGS)


%.o : %.cpp
	$(CC_FLAGS) -I$(CWD) -c -o $(BUILD)/$@ $<

#cli.%.o : $(CLI)/%.cpp
#	$(CC_FLAGS) -I$(CWD) -c -o $(BUILD)/$@ $<

clean:
	find build -name *.o -delete

all: cpps cli bison

# CPPS Core
cppsObjs 	= \
            AbstractSyntaxTree.o \
			Exceptions.o \
			Nodes.o \
			Null.o \
			Number.o \
			Object.o \
			Scriptable.o \
			Token.o \
			Tokenizer.o \
			parser.o \
			parse.o \

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

bison:
	bisonc++ cpps.gr
	mv Parser* cpps/
	mv parse.cc cpps/parse.cpp

# Test Targets
test-all: test-tokenizer test-smartpointer

testTokenizerBuildObjs = $(patsubst %,$(TEST)/%,test_tokenizer.o)
testTokenizerDirObjs   = $(patsubst %,$(BUILD)/%,$(testTokenizerBuildObjs))
test-tokenizer: cpps $(testTokenizerBuildObjs)
	$(CC_FLAGS) $(LFLAGS) -o $(BIN)/test_tokenizer $(testTokenizerDirObjs) $(cppsDirObjs)

testSmartPointerBuildObjs = $(patsubst %,$(TEST)/%,test_smartpointer.o)
testSmartPointerDirObjs   = $(patsubst %,$(BUILD)/%,$(testSmartPointerBuildObjs))
test-smartpointer: cpps $(testSmartPointerBuildObjs)
	$(CC_FLAGS) $(LFLAGS) -o $(BIN)/test_smartpointer $(testSmartPointerDirObjs) $(cppsDirObjs)

