zq: utils.o zq.o
	gcc -Wall -Werror -std=c11 utils.o zq.o main.c -g -o zq
utils.o: utils.c
		gcc -Wall -Werror -std=c11 utils.c -g -c
zq.o: zq.c
		gcc -Wall -Werror -std=c11 zq.c -g -c
clean:
	rm -f zq utils.o zq.o
#debug rules
zq_db: utils_db zq_db
	gcc -Wall -Werror -std=c11 utils_db zq_db main.c -g -o zq_db
