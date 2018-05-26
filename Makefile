SRCDIR = src
HEADDIR = include
BUILDDIR = build
BINDIR = bin

CC = g++
CFLAGS = -g -Wall

INC := -I $(HEADDIR)
LIB = -L lib

ifeq ($(OS),Windows_NT)
	TARGET := $(BINDIR)\talospuzzle.exe
    SOURCES := $(SRCDIR)\$(shell dir /b $(SRCDIR))
	ifeq ($(SOURCES),$(SRCDIR)\)
		SOURCES :=
	endif
	HEADERS := $(HEADDIR)\$(shell dir /b $(HEADDIR))
	ifeq ($(HEADERS),$(HEADDIR)\)
		HEADERS :=
	endif
	OBJECTS := $(patsubst $(SRCDIR)\\%,$(BUILDDIR)\\%,$(SOURCES:.cpp=.o))
	CLEAN_CMD := del $(OBJECTS) $(TARGET)
else
	TARGET := $(BINDIR)/talospuzzle
    SOURCES := $(SRCDIR)/$(shell ls $(SRCDIR))
	HEADERS := $(HEADDIR)/$(shell ls $(HEADDIR))
	OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))
	CLEAN_CMD := $(RM) $(OBJECTS) $(TARGET)
endif

$(TARGET): $(OBJECTS)
	@echo Linking...
	$(CC) $^ -o $(TARGET) $(LIB)

$(OBJECTS): $(SOURCES) $(HEADERS)
	@echo Building...
	$(CC) $(CFLAGS) $(INC) -c -o $@ $(SOURCES)

clean:
	@echo Cleaning...
	$(CLEAN_CMD)	