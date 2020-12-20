#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <stdlib.h>
#include "std_msgs/Int8.h"
#include <iostream>
#include <string>

using namespace std;


// function to start/stop painting
void paint_now(int painting, double paint_delay, int loop_case) {

    ros::NodeHandle a_node;
    ros::Publisher paint_system_pub = a_node.advertise<std_msgs::Int8>("paint_action", 10);

    std_msgs::Int8 a_msg;

    int down_loop = 70;
    int up_loop = 215;
//the following if statement are to optimize the amount of iteration for the amount of commands send
    if (loop_case == 0) {          //line
        down_loop = 50;
        up_loop = 50;

    }
    else if (loop_case == 1) {     //circle
        down_loop = 50;
        up_loop = 160;

    }

    else if (loop_case == 2) {     //box
        down_loop = 175;
        up_loop = 180;

    }
    else {

        ROS_INFO("%s", "error: wrong unkown loop_case [int]");
    }
	
	//start painting
    if (painting == 1)
    {

        a_msg.data = 1;
        ROS_INFO("%d", a_msg.data);
        ROS_INFO("%s", "start painting");

        int i = 0;
        for (int i = 0; i < down_loop; i++)     // down loop
        {

            ROS_INFO("%i", i);
            paint_system_pub.publish(a_msg);
            ros::Duration(0.2).sleep();
        }
    }

	//stop painting
    else // if (painting == 0)
    {
        a_msg.data = 0;
        ROS_INFO("%d", a_msg.data);
        ROS_INFO("%s", "stop painting");

        int k = 0;
        for (int k = 0; k < up_loop; k++)        // up loop
        {
            ROS_INFO("%i", k);

            paint_system_pub.publish(a_msg);
            ros::Duration(0.1).sleep();
        }
    }
    ROS_INFO("%s", "sleep");
    ros::Duration(paint_delay).sleep();
    ROS_INFO("%s", "done");
}

//straight line - autonomous drawing
void straight_line(double meters) {

    ros::NodeHandle nh;
    ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 10);


    ros::Duration(1.0).sleep();

    paint_now(1, 1.0, 0);

    for (int i = 0;i < ((meters + 0.1538) * 40); i++) {
        geometry_msgs::Twist msg;
        msg.linear.x = 0.25;
        msg.angular.z = -0.021;
        cmd_vel_pub.publish(msg);
        ros::Duration(0.1).sleep();
    }

    ros::Duration(1.5).sleep();
    paint_now(0, 1.0, 0);
    cout << "The turtlebot drove " << meters << "m" << endl;
}


//circle - autonomous drawing
void make_circle(double radius) {
    double speedvalue = 0;
    speedvalue = 0.5 * (radius - 0.24);
    ros::NodeHandle nh;
    ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 10);
    ros::Duration(1.5).sleep();

    paint_now(1, 1, 1);

    for (int i = 0;i < (6, 7 * 21); i++) {   //int i=0;i<(6.28319*21); i++){
        geometry_msgs::Twist msg;
        msg.linear.x = speedvalue;
        msg.angular.z = 0.5 - 0.015;
        cmd_vel_pub.publish(msg);
        ros::Duration(0.1).sleep();
    }

    ros::Duration(0.5).sleep();
    paint_now(0, 1.0, 1);
    cout << "Please choose new case" << endl;
}


//box - autonomous drawing
void make_box(double side_length) {
    ros::NodeHandle nh;
    ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 10);

    for (int k = 0;k < (4); k++) {


        ros::Duration(1.0).sleep();
        std::cout << "start painting: ";
        paint_now(1, 1.0, 2);
        std::cout << "done" << '\n';


        std::cout << "f-loop +25" << '\n';
        for (int i = 0;i < ((side_length + 0.1581) * 98.5); i++) { 
            geometry_msgs::Twist msg;
            msg.linear.x = 0.1;
            msg.angular.z = -0.010;
            cmd_vel_pub.publish(msg);
            ros::Duration(0.1).sleep();
        }
        ros::Duration(1.5).sleep();

        std::cout << "stop painting: ";
        paint_now(0, 1.5, 2);
        std::cout << "done" << '\n';


        std::cout << "f-loop 25" << '\n';
        for (int i = 0;i < ((0.15 + 0.15) * 100); i++) { 
            geometry_msgs::Twist msg;
            msg.linear.x = -0.1;
            msg.angular.z = 0.010;
            cmd_vel_pub.publish(msg);
            ros::Duration(0.1).sleep();
        }

        ros::Duration(1.5).sleep();
        std::cout << "f-loop turn" << '\n';
        for (int j = 0;j < (53.16552); j++) {		//turning
            geometry_msgs::Twist msg;
            msg.linear.x = 0.0;
            msg.angular.z = 0.5;
            cmd_vel_pub.publish(msg);
            ros::Duration(0.1).sleep();
        }
        ros::Duration(1.0).sleep();

        std::cout << "f-loop -25" << '\n';
        for (int i = 0;i < ((0.15 + 0.15) * 100); i++) { 
            geometry_msgs::Twist msg;
            msg.linear.x = -0.1;
            msg.angular.z = 0.010;
            cmd_vel_pub.publish(msg);
            ros::Duration(0.1).sleep();
        }
    }

    ros::Duration(1.5).sleep();

    cout << "Please choose new case" << endl;
}

void Path_box_Callback(const std_msgs::Int8::ConstPtr& msg)
{
    //call your function here
    ROS_INFO("I heard: [%i]", msg->data);
    double side_length = 0.5;						//  <-- size of the box is defind here 
    make_box(side_length);

}

void Path_circle_Callback(const std_msgs::Int8::ConstPtr& msg) {
    //call your function hereasd
    ROS_INFO("I heard: [%i]", msg->data);
    double dis_radius = 0.75;						// <-- size of the circle is defind here
    make_circle(dis_radius);
}

void Path_line_Callback(const std_msgs::Int8::ConstPtr& msg) {
    ROS_INFO("I heard: [%i]", msg->data);
    double distance = 1;							// <-- size of the line is defind here.
    straight_line(distance);
}


//main loop
int main(int argc, char** argv)
{
	// ros nodes which are used in this code
    std::cout << "Ready" << '\n';
    ros::init(argc, argv, "listener");
    ros::NodeHandle drive_node;
    ros::Subscriber box_sub = drive_node.subscribe("path_box", 10000, Path_box_Callback);
    ros::Subscriber circle_sub = drive_node.subscribe("path_circle", 10000, Path_circle_Callback);
    ros::Subscriber line_sub = drive_node.subscribe("path_line", 10000, Path_line_Callback);

    while (ros::ok()) {					//keep running until ctrl + c is pressed
        ros::spinOnce();      
    }

    return 0;
}
