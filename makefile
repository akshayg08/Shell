shell: \
			shell.o \
			ls.o \
			pinfo.o \
			clock.o \
			getcommand.o \
			inbuilt.o 
	$(CC) -g -o shell_my $^

clean:
	@rm -f *.o shell_my

shell.o: headers.h shell.c
	$(CC) -g -c shell.c

ls.o: headers.h ls.c
	$(CC) -g -c ls.c

inbuilt.o: headers.h inbuilt.c
	$(CC) -g -c inbuilt.c

pinfo.o: headers.h pinfo.c
	$(CC) -g -c pinfo.c

clock.o: headers.h clock.c
	$(CC) -g -c clock.c

get_command.o: headers.h getcommand.c
	$(CC) -g -c getcommand.c