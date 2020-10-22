/**
 * @ Copyright 2020
 */


#include "interface_socket/ethernet_interface.hpp" 

sock::EthernetInterface::EthernetInterface (std::string server_ip, int port) {

    struct sockaddr_in server;
    int len = sizeof(server);

    fprintf(stdout, "Starting Client ...\n");

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error on client socket creation:");
        // return EXIT_FAILURE;
    }
    fprintf(stdout, "Client socket created with fd: %d\n", sockfd);

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(server_ip.c_str());
    memset(server.sin_zero, 0x0, 8);

    if (connect(sockfd, (struct sockaddr*) &server, len) == -1) {
        perror("Can't connect to server");
        // return EXIT_FAILURE;
    }
}

sock::EthernetInterface::~EthernetInterface (){
    close(sockfd);
}

void sock::EthernetInterface::net_send(std::vector<uint8_t> msg){
    send(sockfd, msg.data(), msg.size(), 0);
}