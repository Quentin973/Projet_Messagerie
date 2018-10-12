#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFFER_SIZE 256


int cree_socket_tcp_client(int arg, char** argport)
{
struct sockaddr_in adresse;
int sock;
if (arg != 3)
{
fprintf(stderr, "Usage : %s adresse port\n",
argport[0]);
exit(0);
}
if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
{
fprintf(stderr, "Erreur socket\n");
return -1;
}
memset(&adresse, 0, sizeof(struct sockaddr_in));
adresse.sin_family = AF_INET;
adresse.sin_port = htons(atoi(argport[2]));
inet_aton(argport[1], &adresse.sin_addr);
if (connect(sock, (struct sockaddr*) &adresse,
sizeof(struct sockaddr_in)) < 0)
{
close(sock);
fprintf(stderr, "Erreur connect\n");
return -1;
}
return sock;
}

int main(int argc , char **argv){

char message[100];
char message2[100];
int sock_client;

sock_client = cree_socket_tcp_client(argc, argv);
while(1){
scanf("%s",message); 
write(sock_client, message ,100*sizeof (char));

read(sock_client, message2 , 100*sizeof (char));
printf ("%s", message2);

}	
	
			
}