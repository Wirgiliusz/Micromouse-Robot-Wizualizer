#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "std_msgs/String.h"


visualization_msgs::Marker box;
ros::Publisher marker_pub;
enum Directions {NORTH, SOUTH, WEST, EAST};

void moveRobot(enum Directions direction);

void receiverCallback(const std_msgs::String::ConstPtr& msg) {
  ROS_INFO("I heard: [%s]", msg->data.c_str());

  if(msg->data == "NORTH") {
    moveRobot(NORTH);
  }
  if(msg->data == "EAST") {
    moveRobot(EAST);
  }
  if(msg->data == "SOUTH") {
    moveRobot(SOUTH);
  }
  if(msg->data == "WEST") {
    moveRobot(WEST);
  }
  
  ROS_INFO("Updated box position");

}

void moveRobot(enum Directions direction) {
  switch(direction) {
    case NORTH:
      for(int i=0; i<10; i++) {
        box.pose.position.x -= 0.1;
        marker_pub.publish(box);
        ros::Duration(0.1).sleep();
      }
    break;
    case EAST:
      for(int i=0; i<10; i++) {
          box.pose.position.y += 0.1;
          marker_pub.publish(box);
          ros::Duration(0.1).sleep();
      }
    break;
    case SOUTH:
      for(int i=0; i<10; i++) {
          box.pose.position.x += 0.1;
          marker_pub.publish(box);
          ros::Duration(0.1).sleep();
      }
    break;
    case WEST:
      for(int i=0; i<10; i++) {
          box.pose.position.y -= 0.1;
          marker_pub.publish(box);
          ros::Duration(0.1).sleep();
      }
    break;
  }
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "basic_shapes");
  ros::NodeHandle n;
  ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Publisher marker_pub_lab = n.advertise<visualization_msgs::Marker>("visualization_marker_lab", 1);
  ros::Subscriber sub = n.subscribe("sender", 1000, receiverCallback);


  bool narysowanoLabirynt = false;
  visualization_msgs::Marker line1;
  visualization_msgs::Marker line2;
  

  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  box.header.frame_id = "my_frame";
  box.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  box.ns = "basic_shapes";
  box.id = 0;

  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  box.type = visualization_msgs::Marker::CUBE;

  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  box.action = visualization_msgs::Marker::ADD;

  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  box.pose.position.x = 0.5;
  box.pose.position.y = 0.5;
  box.pose.position.z = 0;
  box.pose.orientation.x = 0.0;
  box.pose.orientation.y = 0.0;
  box.pose.orientation.z = 0.0;
  box.pose.orientation.w = 1.0;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  box.scale.x = 0.66;
  box.scale.y = 0.66;
  box.scale.z = 0.44;

  // Set the color -- be sure to set alpha to something non-zero!
  box.color.r = 0.0f;
  box.color.g = 1.0f;
  box.color.b = 0.0f;
  box.color.a = 1.0;

  box.lifetime = ros::Duration();


  // ________________ RYSOWANIE LABIRYNTU _____________________ //
  if(!narysowanoLabirynt) {
    line1.header.frame_id = "my_frame";
    line1.header.stamp = ros::Time::now();
    line1.ns = "basic_shapes";
    line1.id = 1;
    line1.type = visualization_msgs::Marker::LINE_STRIP;
    line1.action = visualization_msgs::Marker::ADD;
    line1.pose.orientation.w = 1.0;

    line1.scale.x = 0.15;

    line1.color.r = 1.0;
    line1.color.a = 1.0;

    line1.pose.orientation.z = 0.0;

    geometry_msgs::Point p1;
    p1.x = 0;
    p1.y = 0;
    p1.z = 0;
    line1.points.push_back(p1);
    p1.x += 1.0;
    line1.points.push_back(p1);
    p1.y += 2.0;
    line1.points.push_back(p1);
    p1.y -= 2.0;
    line1.points.push_back(p1);
    p1.x += 1.0;
    line1.points.push_back(p1);
    p1.y += 1.0;
    line1.points.push_back(p1);
    p1.x += 1.0;
    line1.points.push_back(p1);
    p1.x -= 1.0;
    line1.points.push_back(p1);
    p1.y -= 1.0;
    line1.points.push_back(p1);
    p1.x += 2.0;
    line1.points.push_back(p1);
    p1.y += 4.0;
    line1.points.push_back(p1);
    p1.x -= 4.0;
    line1.points.push_back(p1);
    p1.y -= 1.0;
    line1.points.push_back(p1);
    p1.x += 1.0;
    line1.points.push_back(p1);
    p1.x -= 1.0;
    line1.points.push_back(p1);
    p1.y -= 3.0;
    line1.points.push_back(p1);


    
    line2.header.frame_id = "my_frame";
    line2.header.stamp = ros::Time::now();
    line2.ns = "basic_shapes";
    line2.id = 2;
    line2.type = visualization_msgs::Marker::LINE_STRIP;
    line2.action = visualization_msgs::Marker::ADD;
    line2.pose.orientation.w = 1.0;

    line2.scale.x = 0.15;

    line2.color.r = 1.0;
    line2.color.a = 1.0;

    line2.pose.orientation.z = 0.0;

    geometry_msgs::Point p2;
    p2.x = 2;
    p2.y = 3;
    p2.z = 0;
    line2.points.push_back(p2);
    p2.y -= 1.0;
    line2.points.push_back(p2);
    p2.x += 1.0;
    line2.points.push_back(p2);
    p2.y += 1.0;
    line2.points.push_back(p2);

    narysowanoLabirynt = true;
    }

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1 || marker_pub_lab.getNumSubscribers() <1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(box);
    marker_pub_lab.publish(line2);
    marker_pub_lab.publish(line1);
    
  
    
    ros::spin();

 return 0;
}