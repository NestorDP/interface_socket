/**
 * @ Copyright 2020
 */

#include <stdio.h>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <string>

#include "interface_socket/ethernet_interface.hpp"

void image_rawCallback (const sensor_msgs::Image::ConstPtr & image){
    ROS_INFO("I heard: [%d]", image->step);
}

int main(int argc, char **argv) {
    int port;
    std::string server_ip;
    std::vector<uint8_t> i {10, 20, 30, 40, 50};
    std::vector<uint8_t> j (BUFFER_LEN);
    ros::init(argc, argv, "node");
    ros::NodeHandle nh;

    sensor_msgs::Image imag;
    
    ros::Publisher pub = nh.advertise<sensor_msgs::Image>("image_filtered", 100);
    ros::Subscriber sub = nh.subscribe("image_raw", 1000, image_rawCallback);
    
    ros::param::get("~/server_ip", server_ip);
    ros::param::get("~/port", port);

    sock::EthernetInterface soc(server_ip, port);

    soc.net_recv(j.data(), BUFFER_LEN);
    printf("Mensagem recebida ...\n");
    printf("%s\n", j.data());

    soc.net_send(i.data(), BUFFER_LEN);

    soc.net_recv(j.data(), BUFFER_LEN);
    printf("Mensagem recebida ...\n");
    // printf("%s\n", j.data());

    for(int x = 0; x < 5; x++ ){
        printf("%d \n", j[x]);
    }
    
    // while (ros::ok()) {
    //     fprintf(stdout, "==================\n");
        
    // }
    ros::spin();
}