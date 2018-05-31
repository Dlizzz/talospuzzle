SRCDIR = src
BUILDDIR = build
BINDIR = bin
SRCEXT = cpp

CC = g++
CFLAGS = -g -Wall -std=c++17
LFLAGS =

TARGET := $(BINDIR)/talospuzzle

ifeq ($(OS),Windows_NT)
	INC = -I include -isystem ../lib/boost
	LIB = -L ../lib/boost/stage/lib -l libboost_program_options-mgw81-mt-d-x64-1_67
	SOURCES := $(addprefix $(SRCDIR)/,$(shell dir /b $(SRCDIR)\*.$(SRCEXT)))
	OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
	MKDIR_CMD := if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	CLEAN_CMD := $(subst /,\,del $(OBJECTS) $(TARGET).exe 2> nul && rmdir $(BUILDDIR) 2> nul)
else
	INC = -I include
	LIB = -l boost_program_options
	SOURCES := $(shell ls $(SRCDIR)/*.$(SRCEXT))
	OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
	MKDIR_CMD := mkdir -p $(BUILDDIR)
	CLEAN_CMD := $(RM) -r $(BUILDDIR) $(TARGET)
endif

$(TARGET): $(OBJECTS)
	@echo Linking...
	$(CC) $^ $(LFLAGS) -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo Compiling...
	@$(MKDIR_CMD)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

.PHONY: clean
clean:
	@echo Cleaning...
	@$(CLEAN_CMD) || exit 0