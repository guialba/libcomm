#include "comm.h"


int new_socket = 0;

int server_cnt(int porta)
{
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int err = 0, sock=0;

    new_socket=0;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( porta );
   
    if( (sock = socket (AF_INET, SOCK_STREAM, 0)) == 0 )
        return err-1;
    if( setsockopt(sock, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT,  &(int){ 1 }, sizeof(int)) )
        return err-2;
    if( bind(sock, (struct sockaddr *)&address, sizeof(address)) < 0 )
        return err-3;    
    if( listen(sock, 3) < 0 )
        return err-4;
    if( (new_socket = accept(sock, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0 )
        return err-5;

    
    return err;
}
int client_cnt(char* ip, int porta)
{
    struct sockaddr_in serv_addr;
    int err = 0;
    
    new_socket=0;

    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons( porta );

    if( (new_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
        return err-1;
    if( inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0 ) 
        return err-2;
    if( connect(new_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 )
        return err-3;

    return err;
}
int sock_close()
{
    close(new_socket);
}


int msg_snd(char* msg, int size)
{
    int err = 0, valread=0;
    if( new_socket == 0 )
        return err-1;
    
    send(new_socket, msg, size, 0 );

    return err;
}
int msg_recv(char* buffer, int size)
{ 
    int err = 0, valread=0;

    if( new_socket == 0 )
        return err-1;
    
    valread = read( new_socket , buffer, size);
    
    return valread;
}
