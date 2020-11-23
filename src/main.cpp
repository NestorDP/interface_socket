/**
 * @ Copyright 2020
 */


#include <stdio.h>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <string>

#include "interface_socket/ethernet_interface.hpp"

#define MSG_LEN 2764800

sensor_msgs::Image::Ptr imag(new sensor_msgs::Image());
std::vector<uint8_t> dados_in(MSG_LEN);
std::vector<uint8_t> dados_out(MSG_LEN);
uint32_t step = 0;

void image_rawCallback (const sensor_msgs::Image::ConstPtr & image){
    ROS_INFO("I heard: [%d]", image->step);
    dados_out = image->data;
    step = image->step;
}

int main(int argc, char **argv) {
    int port;
    int n_bytes;
    std::string server_ip;
    std::vector<uint8_t> msg_in(BUFFER_LEN);
    ros::init(argc, argv, "node");
    ros::NodeHandle nh;
    ros::Rate r(10);

    ros::Publisher pub = nh.advertise<sensor_msgs::Image>("image_filtered", 100);
    ros::Subscriber sub = nh.subscribe("image_raw", 100, image_rawCallback);
    
    ros::param::get("~/server_ip", server_ip);
    ros::param::get("~/port", port);

    imag->encoding = "rgb8";
    imag->height = 720;
    imag->width = 1280;
    imag->step = 3840;
    imag->header.frame_id = "camera_link";

    sock::EthernetInterface soc;
    soc.create_socket();
    soc.connect_server(server_ip, port);

    soc.net_recv(msg_in.data(), BUFFER_LEN);
    printf("Message received: ");
    printf("%s", msg_in.data());

    while (ros::ok()) {
        if(step > 0){
            soc.net_send(dados_out.data(), BUFFER_LEN, MSG_LEN);
            n_bytes = soc.net_recv(dados_in.data(), BUFFER_LEN, MSG_LEN);
            imag->data = dados_in;
            imag->header.stamp = ros::Time::now();
            pub.publish(imag);
            // printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
        }
        ros::spinOnce();
        r.sleep();    
    }
    // ros::spin();
}
