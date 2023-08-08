CC = gcc

SRCDIR = .
OBJDIR = obj

SOURCES = dropbox.h request_buff_handle.c send_data.c server_file_handle.c server_thread.c server.c
OBJECTS = $(patsubst %.c,$(OBJDIR)/%.o,$(SOURCES))

TARGET = BibakBOXServer

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TARGET)
