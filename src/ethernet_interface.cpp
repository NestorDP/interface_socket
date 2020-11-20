/**
 * @ Copyright 2020
 */


#include "interface_socket/ethernet_interface.hpp" 

sock::EthernetInterface::EthernetInterface () {
    struct sockaddr_in server;
    fprintf(stdout, "Starting Client ...\n");
}

sock::EthernetInterface::~EthernetInterface (){
    close(sockfd);
}

void sock::EthernetInterface::create_socket(void){
    if ((sockfd = socket(AF_INET,  SOCK_STREAM, 0)) == -1) {
        perror("\e[1;31mError on client socket creation:");
        printf("\e[0m");
        exit (EXIT_FAILURE);
    }
    printf("Client socket created with fd: %d\n", sockfd);
}

void sock::EthernetInterface::connect_server(std::string ip, int port){
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip.c_str());
    memset(server.sin_zero, 0x0, 8);

    if (connect(sockfd, (struct sockaddr*) &server, sizeof(server)) == -1) {
        perror("\e[1;31mCan't connect to server");
        printf("\e[0m");
        exit (EXIT_FAILURE);
    }

    printf("Connection established with the server\n");
    return;
}

int sock::EthernetInterface::net_send(uint8_t *msg, unsigned int len_buffer){
    return send(sockfd, msg , len_buffer, 0);
}

int sock::EthernetInterface::net_send(uint8_t *msg, unsigned int len_buffer, int unsigned len_msg){
    unsigned int num = 0;
    for (size_t i = 0; i < len_msg; i = i + len_buffer){
        num = num + send(sockfd, msg + i , len_buffer, 0);
    }
    return num;  
}

int sock::EthernetInterface::net_recv(uint8_t *msg, unsigned int len_buffer){
    return recv(sockfd, msg, len_buffer, 0);
}

int sock::EthernetInterface::net_recv(uint8_t *msg, unsigned int len_buffer, int unsigned len_msg){
    unsigned int num = 0;
    for(int i = 0; i < len_msg; i = i + len_buffer){
            num = num + recv(sockfd, msg + i, len_buffer, 0);
    }
    return num;
}
