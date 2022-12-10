account_exe : main.o account.o
	gcc -o account_exe main.o account.o

main.o : main.c
	gcc -c -o main.o main.c

account.o : account.c
	gcc -c -o account.o account.c

clean :
	rm *.o account_exe