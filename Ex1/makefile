CC = gcc
AR = ar
FLAGS= -Wall -g
basicandloop= advancedClassificationLoop.o basicClassification.o
basicandrec= advancedClassificationRecursion.o basicClassification.o

loops: libclassloops.a
loopd: libclassloops.so
recursives: libclassrec.a
recursived: libclassrec.so

all: libclassloops.a libclassloops.so libclassrec.a libclassrec.so mains maindrec maindloop 

mains: main.o libclassrec.a
	$(CC) $(FLAGS)  -o mains main.o libclassrec.a 
maindloop: main.o libclassloops.so 
	$(CC) $(FLAGS)  -o maindloop main.o ./libclassloops.so 
maindrec: main.o libclassrec.so 
	$(CC) $(FLAGS)  -o maindrec main.o ./libclassrec.so 
libclassloops.a: $(basicandloop)
	$(AR) -rcs libclassloops.a $(basicandloop)
libclassloops.so: $(basicandloop)
	$(CC) -shared -o libclassloops.so $(basicandloop)
libclassrec.a: $(basicandrec)
	$(AR) -rcs libclassrec.a $(basicandrec)
libclassrec.so: $(basicandrec)
	$(CC) -shared -o libclassrec.so $(basicandrec)
basicClassification.o: basicClassification.c NumClass.h
	$(CC) $(FLAGS) -c basicClassification.c 
advancedClassificationLoop.o: advancedClassificationLoop.c NumClass.h
	$(CC) $(FLAGS) -c advancedClassificationLoop.c 
advancedClassificationRecursion.o: advancedClassificationRecursion.c NumClass.h
	$(CC) $(FLAGS) -c advancedClassificationRecursion.c 


main.o: main.c NumClass.h
	$(CC) $(FLAGS) -c main.c
 

clean:
	rm -f *.o *.a *.so maindloop maindrec mains