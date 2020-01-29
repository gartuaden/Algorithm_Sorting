all: mp2_20171672

CC=gcc
TARGET=mp2_20171672
OBJECT=mp2_20171672.o

mp2_20171672 : $(OBJECT) 
	$(CC) -o $(TARGET) mp2_20171672.o -lm

main.o : main.c
	$(CC) -c -o mp2_20171672.o mp2_20171672.c

clean:
	rm *.o $(TARGET)
