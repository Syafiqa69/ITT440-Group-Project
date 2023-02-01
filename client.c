#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
int client_socket;
struct sockaddr_in server;
char request[1024], response[1024];

client_socket = socket(AF_INET, SOCK_STREAM, 0);
if (client_socket == -1) {
    printf("Could not create socket");
}

server.sin_addr.s_addr = inet_addr("172.104.177.86");
server.sin_family = AF_INET;
server.sin_port = htons(8080);

if (connect(client_socket, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Connection failed");
    return 1;
}

printf("Enter a message to send to the server: ");
scanf("%s", request);

if (send(client_socket, request, strlen(request), 0) < 0) {
    printf("Send failed");
    return 1;
}

if (recv(client_socket, response, 1024, 0) < 0) {
    printf("Recv failed");
    return 1;
}

printf("Server reply: %s\n", response);

close(client_socket);

return 0;
}
