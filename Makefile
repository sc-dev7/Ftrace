##
## EPITECH PROJECT, 2024
## B-PSU-400-NCY-4-1-ftrace-sofiane.chabane
## File description:
## Makefile
##



CFLAGS := -Wall -g

EXECUTABLE := ftrace
INCLUDES := -Iinclude

SRCDIR := src
OBJDIR := objs

SOURCES := $(shell find $(SRCDIR) -name '*.c')
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -lelf

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $^ -lelf

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(EXECUTABLE)

re: fclean all

.PHONY: all re clean fclean
