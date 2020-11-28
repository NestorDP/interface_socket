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

void sock::EthernetInterface::create_socket(std::string ip_server, int port, bool protocol){
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip_server.c_str());
    memset(server.sin_zero, 0x0, 8);

    if(protocol){
        if ((sockfd = socket(AF_INET,  SOCK_STREAM, 0)) == -1) {
            perror("\e[1;31mError on client socket creation:");
            printf("\e[0m");
            exit (EXIT_FAILURE);
        }
        printf("Client socket created with fd: %d\n", sockfd);
        
        if (connect(sockfd, (struct sockaddr*) &server, sizeof(server)) == -1) {
            perror("\e[1;31mCan't connect to server");
            printf("\e[0m");
            exit (EXIT_FAILURE);
        }
        printf("Connection established with the server\n");
    }
    else{
        if ((sockfd = socket(AF_INET,  SOCK_DGRAM, 0)) == -1) {
            perror("\e[1;31mError on client socket creation:");
            printf("\e[0m");
            exit (EXIT_FAILURE);
        }
        printf("Client socket created with fd: %d\n", sockfd);
    }
    return;
}

int sock::EthernetInterface::net_send(uint8_t *msg, unsigned int len_buffer, int unsigned len_msg){
    unsigned int num = 0;
    for (size_t i = 0; i < len_msg; i = i + len_buffer){
        num = num + send(sockfd, msg + i , len_buffer, 0);
    }
    return num;  
}

int sock::EthernetInterface::net_recv(uint8_t *msg, unsigned int len_buffer, int unsigned len_msg){
    unsigned int num = 0;
    for(int i = 0; i < len_msg; i = i + len_buffer){
            num = num + recv(sockfd, msg + i, len_buffer, 0);
    }
    return num;
}

int sock::EthernetInterface::net_sendto(uint8_t *msg, unsigned int len_buffer, int unsigned len_msg){
    unsigned int num = 0;
    for (size_t i = 0; i < len_msg; i = i + len_buffer){
        num = num + sendto(sockfd, msg + i , len_buffer, 0, 
                        (const struct sockaddr *) &server, sizeof(server));
    }
    return num;  
}

int sock::EthernetInterface::net_recvfrom(uint8_t *msg, unsigned int len_buffer, int unsigned len_msg){
    unsigned int num = 0;
    unsigned int len;
    for(int i = 0; i < len_msg; i = i + len_buffer){
            num = num + recvfrom(sockfd, msg + i, len_buffer, 0,
                        (struct sockaddr *) &server, &len);
    }
    return num;
}
