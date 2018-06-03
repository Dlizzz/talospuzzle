SRCDIR = src
BUILDDIR = bld
BINDIR = bin
SRCEXT = cpp

CC = g++
CFLAGS = -g -Wall -std=c++17
LFLAGS =

TARGET := $(BINDIR)/talospuzzle
INC = -I include
LIB = -l boost_program_options
SOURCES := $(shell ls $(SRCDIR)/*.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
MKDIR_CMD := mkdir -p $(BUILDDIR)
CLEAN_CMD := $(RM) -r $(BUILDDIR) $(TARGET)

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