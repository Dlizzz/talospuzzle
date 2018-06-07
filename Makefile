BUILDDIR = bld
BINDIR = bin
SRCEXT = cpp

CC = g++
CFLAGS = -c -g -Wall -std=c++17
LFLAGS =

TARGET := $(BINDIR)/talospuzzle
INC =
LIB = -l boost_program_options
SOURCES := $(shell ls *.$(SRCEXT))
OBJECTS := $(addprefix $(BUILDDIR)/,$(SOURCES:.$(SRCEXT)=.o))
MKDIR_CMD := mkdir -p $(BUILDDIR)
CLEAN_CMD := $(RM) -r $(BUILDDIR) $(TARGET)

$(TARGET): $(OBJECTS)
	@echo Linking...
	$(CC) $^ $(LFLAGS) -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: %.$(SRCEXT)
	@echo Compiling...
	@$(MKDIR_CMD)
	$(CC) $(CFLAGS) $(INC) -o $@ $<

.PHONY: clean
clean:
	@echo Cleaning...
	@$(CLEAN_CMD) || exit 0