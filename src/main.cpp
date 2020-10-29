/**
 * @ Copyright 2020
 */


#include <stdio.h>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <string>

#include "interface_socket/ethernet_interface.hpp"

sensor_msgs::Image imag;
std::vector<uint8_t> dados;

void image_rawCallback (const sensor_msgs::Image::ConstPtr & image){
    ROS_INFO("I heard: [%d]", image->step);
    imag = *image;
    dados = image->data;
}

int main(int argc, char **argv) {
    int port;
    std::string server_ip;
    std::vector<uint8_t> msg_out (BUFFER_LEN);
    std::vector<uint8_t> msg_in (BUFFER_LEN);
    ros::init(argc, argv, "node");
    ros::NodeHandle nh;
    ros::Rate r(3);
    
    ros::Publisher pub = nh.advertise<sensor_msgs::Image>("image_filtered", 100);
    ros::Subscriber sub = nh.subscribe("image_raw", 1000, image_rawCallback);
    
    ros::param::get("~/server_ip", server_ip);
    ros::param::get("~/port", port);

    // for(int x = 0; x < BUFFER_LEN * 2; x++ ){
    //     msg_out[x] = x + 10;
    // }

    sock::EthernetInterface soc;
    soc.create_socket();
    soc.connect_server(server_ip, port);


    soc.net_recv(msg_in.data(), BUFFER_LEN);
    printf("Message received: ");
    printf("%s", msg_in.data());

    // soc.net_send(msg_out.data(), BUFFER_LEN);

    // soc.net_recv(msg_in.data(), BUFFER_LEN);
    // printf("Mensagem recebida ...\n");
    // for(int x = 0; x < BUFFER_LEN; x++ ){
    //     printf("%d \n", msg_in[x]);
    // }
    
    
    while (ros::ok()) {
        // pub.publish(imag);
        soc.net_send(dados.data(), dados.size());
        ros::spinOnce();
        r.sleep();        
    }
    // ros::spin();
}
