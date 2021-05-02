CC=gcc
FILES=./src/main.c ./src/includes.h ./src/operation.c ./src/menu.c
OUT=PersonApp

target:
	${CC} ${FILES} -lsqlite3 -o ${OUT}

clean:
	rm ./${OUT}
