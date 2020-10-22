#ifndef ETHERNET_INTERFACE_HPP
#define ETHERNET_INTERFACE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <ros/ros.h>

#include <string>
#include <vector>

#define BUFFER_LEN 1024

namespace sock {

class EthernetInterface{
  public:
    EthernetInterface(std::string server_ip, int port);
    ~EthernetInterface();
    void net_send(std::vector<uint8_t> msg);


  private:
    uint8_t buffer_in[BUFFER_LEN];
    uint8_t buffer_out[BUFFER_LEN];
    int port;
    int sockfd;
      
};
}




#endif // ETHERNET_INTERFACE_HPP