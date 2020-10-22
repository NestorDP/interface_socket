/**
 * @ Copyright 2020
 */

#include <stdio.h>
#include <ros/ros.h>

#include <string>

#include "interface_socket/ethernet_interface.hpp"

int main(int argc, char **argv) {
    ros::init(argc, argv, "node");
    ros::NodeHandle nh;
    std::string server_ip;
    int port;

    std::vector<uint8_t> i {10, 20, 30, 40, 50};
    
    ros::param::get("~/server_ip", server_ip);
    ros::param::get("~/port", port);

    sock::EthernetInterface soc(server_ip, port);
    soc.net_send(i);

    // while (ros::ok()) {

    // }
    
    ros::spin();
}