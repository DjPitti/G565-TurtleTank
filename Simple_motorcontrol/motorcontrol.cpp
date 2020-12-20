#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include<stdlib.h>
using namespace std;

////////////////////////////////////////////////
void straight_line(){                         //This loop will ask the user for how long a distance the robot should drive, as well as what speed setting they wish to use
  cout<<"Give distance in meters"<<endl;
  double meters = 0;
  cin>>meters;
  cout<<"Desired speed? 1 fast, 2 medium, 3 slow, 4 backwards"<<endl;
  double drivespeed =0;       //The speed setting for the robot
  double random = 0;          //Depending on the choice the user makes for speed setting, a value assigned to that speed setting is included in the for loop
  cin>>drivespeed;

  if (drivespeed==1){         //Speed setting 1 is on 0.5m/s
    double random = 20;
    ros::NodeHandle nh;
    ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 10);
    ros::Duration(1.0).sleep();
    for(int i=0;i<((meters+0.0856)*random); i++){                //Number of repeats in the forloop will depend on user input
      geometry_msgs::Twist msg;
      msg.linear.x = 0.5;
      msg.angular.z = -0.024;
      cmd_vel_pub.publish(msg);
      ros::Duration(0.1).sleep();
    }
    cout<<"The turtlebot drove "<< meters << "m"<<endl;
  }
  else if (drivespeed==2) {   //Speed setting 2 is on 0.25m/s
    double random = 40;
    ros::NodeHandle nh;
    ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 10);
    ros::Duration(1.0).sleep();
    for(int i=0;i<((meters+0.1538)*random); i++){                //Number of repeats in the forloop will depend on user input
      geometry_msgs::Twist msg;
      msg.linear.x = 0.25;
      msg.angular.z = -0.021;
      cmd_vel_pub.publish(msg);
      ros::Duration(0.1).sleep();
    }
    cout<<"The turtlebot drove "<< meters << "m"<<endl;
  }
  else if (drivespeed==3) { //Speed setting 3 is on 0.1m/s
    double random = 100;
    ros::NodeHandle nh;
    ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 10);
    ros::Duration(1.0).sleep();
    for(int i=0;i<((meters+0.1581)*random); i++){
      geometry_msgs::Twist msg;
      msg.linear.x = 0.1;
      msg.angular.z = -0.010;
      cmd_vel_pub.publish(msg);
      ros::Duration(0.1).sleep();
    }
    cout<<"The Turtlebot drove "<< meters << "m"<<endl;
  }
  else if (drivespeed==4) {   //Speed setting 4 is 0.1m/s in reverse
    double random = 100;
    ros::NodeHandle nh;
    ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 10);
    ros::Duration(1.0).sleep();
    for(int i=0;i<(meters+0.1581*random); i++){                //Number of repeats in the forloop will depend on user input
      geometry_msgs::Twist msg;
      msg.linear.x = -0.1;
      msg.angular.z = 0.010;
      cmd_vel_pub.publish(msg);
      ros::Duration(0.1).sleep();
    }
    cout<<"The Turtlebot drove "<< meters << "m"<<endl;
    }

  else std::cout << "Wrong value. Please try again" <<endl;
  cout<<"Please pick new case"<<endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////


void rotation(){                    //This for loop will ask how many times the robot should turn around
  double valueDeg = 0;
  double valueRad = 0;
  cout<<"How many times should the turtlebot turn around? " << endl;
  cin >> valueDeg;
  ros::NodeHandle nh;
  ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 10);
  ros::Duration(1.0).sleep();
    for(int i=0;i<(valueDeg*(167.761173));i++){                //Number of repeats in the forloop will depend on user input
    geometry_msgs::Twist msg;
    msg.linear.x = 0.0;
    msg.angular.z = 0.5;
    cmd_vel_pub.publish(msg);
    ros::Duration(0.1).sleep();
  }
  cout<<"Please pick new case"  <<endl;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
void make_circle(){                           //This for loop will ask the user how big a radius a circle should have
  double radius = 0;
  double speedvalue = 0;
  cout<<"What radius should the circle have? " << endl;
  cin >> radius;
  speedvalue = 0.5 * radius;
  ros::NodeHandle nh;
  ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 10);


  //Rotate in a circle
  ros::Duration(1.0).sleep();
  for(int i=0;i<(150.79656); i++){                 //Number of repeats in the forloop will depend on user input
    geometry_msgs::Twist msg;
    msg.linear.x = speedvalue;
    msg.angular.z = 0.5-0.015;
    cmd_vel_pub.publish(msg);
    ros::Duration(0.1).sleep();
  }
  cout<<"Please choose new case"<<endl;

}
/////////////////////////////////////////////////////////////////////////////////////////

void make_box(){          //This loop will ask the user for a side length for a box and then begin moving around in a square afterwards
double side_length = 0;
  cout<<"How large should the sides on the box be?" <<endl;
  cin >> side_length;
  for(int k=0;k<(4); k++){              //A for loop will begin that has the robot move forward then turn 90 degrees, and repeat 3 times

  ros::NodeHandle nh;
  ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 10);

  // Move forward
  ros::Duration(1.0).sleep();
for(int i=0;i<((side_length+0.1581)*100); i++){                //Number of repeats in the forloop will depend on user input
    geometry_msgs::Twist msg;
    msg.linear.x = 0.1;
    msg.angular.z = -0.010;
    cmd_vel_pub.publish(msg);
    ros::Duration(0.1).sleep();
}

//Turn 90 degrees
  ros::Duration(10.0).sleep();
  for(int j=0;j<(55.46); j++){
    geometry_msgs::Twist msg;
    msg.linear.x = 0.0;
    msg.angular.z = 0.5;
    cmd_vel_pub.publish(msg);
    ros::Duration(0.1).sleep();
}
ros::Duration(1.0).sleep();
}
cout<<"Please choose new case"<<endl;

}


int main(int argc, char *argv[]) {
  bool bExit = false;
  int method=0;
  srand(time(NULL));
  ros::init(argc, argv, "move_turtlesim");
  cout<<"Please pick one of following cases 1. Distance or 2. Rotation or 3. Circle or 4. Make box"<<endl;

do {

  cin>>method;
  switch (method) {
    case 1:
      straight_line();
      break;

    case 2:
      rotation();
      break;

    case 3:
      make_circle();
      break;

    case 4:
      make_box();
      break;

    case 'e':
      cout << "You chose to exit the program." << endl;
      bExit = true;
      cout << "Closing" << endl;
      break;

}
} while (!bExit);

  ros::spin();
  return 0;
}
