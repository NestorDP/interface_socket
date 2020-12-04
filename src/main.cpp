/**
 * @ Copyright 2020
 */


#include <stdio.h>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <string>

#include "interface_socket/ethernet_interface.hpp"

#define MSG_LEN 2764800

std::vector<uint8_t> dados_in(MSG_LEN);
std::vector<uint8_t> dados_out(MSG_LEN);
uint32_t step = 0;

void image_rawCallback (const sensor_msgs::Image::ConstPtr & image){
    // ROS_INFO("I heard: [%d]", sizeof(image->data));
    dados_out = image->data;
    step = image->step;
}

int main(int argc, char **argv) {
    int msg_len;
    std::vector<uint8_t> msg_in(BUFFER_LEN);
    ros::init(argc, argv, "node");
    ros::NodeHandle nh;
    sensor_msgs::Image::Ptr imag(new sensor_msgs::Image());

    int port;
    int height;
    int width;
    int step;
    int fps;
    std::string server_ip;
    std::string encoding;
    std::string frame_id;

    ros::param::get("~/port", port);
    ros::param::get("~/height", height);
    ros::param::get("~/width", width);
    ros::param::get("~/step", step);
    ros::param::get("~/server_ip", server_ip);
    ros::param::get("~/encoding", encoding);
    ros::param::get("~/frame_id", frame_id);
    ros::param::get("~/fps", fps);

    ros::Rate r(fps);

    ros::Publisher pub = nh.advertise<sensor_msgs::Image>("image_filtered", 100);
    ros::Subscriber sub = nh.subscribe("image_raw", 100, image_rawCallback);

    imag->encoding = encoding;
    imag->height = height;
    imag->width = width;
    imag->step = step;
    imag->header.frame_id = frame_id;

    sock::EthernetInterface soc;
    soc.create_socket(server_ip, port, TCP);

    // std::vector<uint8_t> mensagem_teste = {'T','E','S','T','E', '\0'}; 
    // soc.net_send(mensagem_teste.data(), BUFFER_LEN, mensagem_teste.size());

    soc.net_recv(msg_in.data(), BUFFER_LEN, msg_in.size());
    printf("Message received: ");
    printf("%s", msg_in.data());

    unsigned int n = 0;
    while (ros::ok()) {
        if(step > 0){
            soc.net_send(dados_out.data(), BUFFER_LEN, MSG_LEN);
            soc.net_recv(dados_in.data(), BUFFER_LEN, MSG_LEN);
            imag->data = dados_in;
            imag->header.stamp = ros::Time::now();
            pub.publish(imag);
        }
        ros::spinOnce();
        r.sleep();    
    }
}
