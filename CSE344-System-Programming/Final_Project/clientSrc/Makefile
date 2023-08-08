CC = gcc

SRCDIR = .
OBJDIR = obj

SOURCES = client_helper.c client.c server_side.c dropbox.h
OBJECTS = $(patsubst %.c,$(OBJDIR)/%.o,$(SOURCES))

TARGET = BibakBOXClient

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TARGET)
