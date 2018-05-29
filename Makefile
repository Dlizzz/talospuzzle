SRCDIR = src
BUILDDIR = build
BINDIR = bin
SRCEXT = cpp

CC = g++
CFLAGS = -g -Wall

INC = -I include -isystem ../lib/boost_1_67_0
LIB = -L lib -llibboost_program_options-mgw81-x64-1_67

TARGET := $(BINDIR)/talospuzzle

ifeq ($(OS),Windows_NT)
	SOURCES := $(addprefix $(SRCDIR)/,$(shell dir /b $(SRCDIR)\*.$(SRCEXT)))
	OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
	MKDIR_CMD := if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	CLEAN_CMD := $(subst /,\,del $(OBJECTS) $(TARGET).exe 2> nul && rmdir $(BUILDDIR) 2> nul)
else
	SOURCES := $(addprefix $(SRCDIR)/,$(shell ls $(SRCDIR)\*.$(SRCEXT)))
	OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
	MKDIR_CMD := mkdir -p $(BUILDDIR)
	CLEAN_CMD := $(RM) -r $(BUILDDIR) $(TARGET)
endif

$(TARGET): $(OBJECTS)
	@echo Linking...
	$(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo Compiling...
	@$(MKDIR_CMD)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

.PHONY: clean
clean:
	@echo Cleaning...
	@$(CLEAN_CMD) || exit 0