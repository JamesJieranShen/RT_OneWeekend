TARGET   = main

CC       = g++
# compiling flags here
CFLAGS   = -std=c++11 -Wall -Iinclude

LINKER   = g++
# linking flags here
LFLAGS   = -Wall -I. -lm

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.cc)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)
rm       = rm -f

# .PHONY: all
# all: $(OBJECTS)

$(BINDIR)/$(TARGET): $(OBJECTS)
		@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
		@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cc
		@$(CC) $(CFLAGS) -c $< -o $@
		@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
		@$(rm) $(OBJECTS)
		@echo "Cleanup complete!"

.PHONY: remove
remove: clean
		@$(rm) $(BINDIR)/$(TARGET)
		@echo "Executable removed!"