# UDP based single server and 2 clients(sensor and actuator) encrypted chat program written in C language
gcc server.c -o server
./server 32505
 gcc -o client.c -o client
./client 127.0.0.1 32505

