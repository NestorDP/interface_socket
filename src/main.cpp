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

    ros::param::get("~/server_ip", server_ip);
    ros::param::get("~/port", port);

    sock::EthernetInterface soc(server_ip, port);


    // communication::SerialCommunication serial;
    // serial.send_msg(mensagem.c_str());
    // serial.send_msg(mensagem2);
    // serial.send_msg("1234567890123456789");
    // while (ros::ok()) {
    //   mensagem = serial.receive_msg();
    //   ROS_INFO("Recebido %s", mensagem.data());
    //   serial.send_msg(mensagem.c_str());
    //   serial.send_msg("1234567890123456789");
    // }
    ros::spin();
}