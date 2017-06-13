CC=gcc
CFLAGS=-Wall

tp1 : main.c countWords.c countSentences.c countSpecialChars.c parse.c
	$(CC) -o $@ $^ $(CFLAGS)

test:
	cat noticia1 | ./tp1

clean:
	rm tp1
