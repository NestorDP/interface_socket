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
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error on client socket creation:");
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
        perror("Can't connect to server");
        ros::shutdown();
        exit (EXIT_FAILURE);
    }

    printf("Connection established with the server\n");
    return;
}

int sock::EthernetInterface::net_send(uint8_t *msg, unsigned int len){
    return send(sockfd, msg , len, 0);
}

// receber o ponteiro para o vetor maior dos dados
// criar um buffer (local) com largura BUFFER_LEN para receber o pacote 
// montar a mensagem recebida 
int sock::EthernetInterface::net_recv(uint8_t *msg, unsigned int len){
    return recv(sockfd, msg, len, 0);
}
