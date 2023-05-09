CC=gcc
CFLAGS=-I.

all: irc_server.c server_tool.c user.c
	$(CC) -o irc_server irc_server.c server_tool.c user.c $(CFLAGS)
	gcc -Wall irc_client.c -o irc_client
	gcc -Wall tcp_client.c -o tcp_client
	gcc -Wall tcp_server.c -o tcp_server
clean:
	rm -f irc_server

client:
	gcc -Wall irc_client.c -o irc_client