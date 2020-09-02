# UDP-chatting-multiple-client
gcc server.c -o server
./server 32505
 gcc -o client.c -o client
./client 127.0.0.1 32505
