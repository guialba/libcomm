gcc -c -Iinclude src/comm.c -o bin/comm.o
ar rcs bin/libcomm.a bin/comm.o