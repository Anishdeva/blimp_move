#include <ros/ros.h>
#include <tf/transform_datatypes.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include<tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include<iostream>
#include <string>

std::string camera_name;

void poseCallback(ar_track_alvar_msgs::AlvarMarkers req){

    static tf::TransformBroadcaster br;
    tf::TransformListener listener;
    tf::Transform transform;
    //transform.setOrigin(tf::Vector3(msg->x, msg->y, msg->z));
    tf::Quaternion q(req.markers[0].pose.pose.orientation.x, req.markers[0].pose.pose.orientation.y, req.markers[0].pose.pose.orientation.z, req.markers[0].pose.pose.orientation.w);
    transform.setOrigin( tf::Vector3(ceil(req.markers[0].pose.pose.position.x), ceil(req.markers[0].pose.pose.position.y), ceil(req.markers[0].pose.pose.position.z)) );
    transform.setOrigin( tf::Vector3(req.markers[0].pose.pose.position.x, req.markers[0].pose.pose.position.y, req.markers[0].pose.pose.position.z) );
    transform.setRotation(tf::Quaternion( req.markers[0].pose.pose.orientation.x, req.markers[0].pose.pose.orientation.y, req.markers[0].pose.pose.orientation.z, req.markers[0].pose.pose.orientation.w));

    if(req.header.frame_id.compare("camera_0"))
    {
     ROS_INFO("req.header.frame_id: %s", req.header.frame_id.c_str());


    listener.waitForTransform(req.markers[0].header.frame_id, "world", ros::Time::now(), ros::Duration(0.01));
    br.sendTransform(tf::StampedTransform(transform.inverse(), ros::Time::now(), "world", req.markers[0].header.frame_id));

    }

    else if(req.header.frame_id.compare("camera_1"))
    {
     //ROS_INFO("req.header.frame_id: %s", req.header.frame_id.c_str());


    listener.waitForTransform(req.markers[0].header.frame_id, "world", ros::Time::now(), ros::Duration(0.01));
    br.sendTransform(tf::StampedTransform(transform.inverse(), ros::Time::now(), "world", req.markers[0].header.frame_id));

    }

    else if(req.header.frame_id.compare("camera_2"))
    {
    //ROS_INFO("req.header.frame_id: %s", req.header.frame_id.c_str());


    listener.waitForTransform(req.markers[0].header.frame_id, "world", ros::Time::now(), ros::Duration(0.01));
    br.sendTransform(tf::StampedTransform(transform.inverse(), ros::Time::now(), "world", req.markers[0].header.frame_id));

    }

    // catch (tf::TransformException ex){
    //   ROS_ERROR("%s",ex.what());
    //   ros::Duration(1.0).sleep();
    // }
}


int main(int argc, char **argv){
    ros::init(argc, argv,"camera_tf_pose");
    if (argc != 2){ROS_ERROR("need camera name as argument"); return -1;};
    camera_name = argv[1];
    ros::NodeHandle nh;
    ros::Subscriber sub=nh.subscribe(camera_name+"/ar_pose_marker",10,&poseCallback);

    ros::spin();
    return 0;
}