#include <ros/ros.h>
#include <tf/transform_datatypes.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include<tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include<iostream>
#include <string>

void cb(ar_track_alvar_msgs::AlvarMarkers req) {

  tf::TransformBroadcaster tf_br;
  tf::TransformListener listener;
  static  tf::Transform transform;

  if (!req.markers.empty()) {
    tf::Quaternion q(req.markers[0].pose.pose.orientation.x, req.markers[0].pose.pose.orientation.y, req.markers[0].pose.pose.orientation.z, req.markers[0].pose.pose.orientation.w);
    transform.setOrigin( tf::Vector3(ceil(req.markers[0].pose.pose.position.x), ceil(req.markers[0].pose.pose.position.y), ceil(req.markers[0].pose.pose.position.z)) );
    transform.setOrigin( tf::Vector3(req.markers[0].pose.pose.position.x, req.markers[0].pose.pose.position.y, req.markers[0].pose.pose.position.z) );
    //transform.setOrigin( tf::Vector3(0, 0, 0 ));
    transform.setRotation(tf::Quaternion( req.markers[0].pose.pose.orientation.x, req.markers[0].pose.pose.orientation.y, req.markers[0].pose.pose.orientation.z, req.markers[0].pose.pose.orientation.w));
    //br.sendTransform(tf::StampedTransform(transform,ros::Time::now(),"world",ar_maker_255));


    try{

        // this doesn't prints the frame id.
        ROS_INFO("req.markers[0].header.frame_id %s", req.header.frame_id.c_str());
        //ROS_INFO("req.header.frame_id %s", req.header.frame_id.c_str());

      if(req.header.frame_id.compare("ar_marker_255"))
      {
        //  ROS_INFO("req.header.frame_id: %s", req.header.frame_id.c_str());


         listener.waitForTransform(req.markers[0].header.frame_id, "world", ros::Time::now(), ros::Duration(1.0));
         tf_br.sendTransform(tf::StampedTransform(transform.inverse(), ros::Time::now(), "world", req.markers[0].header.frame_id));

      }

    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
    }
  }
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "camera_tf_pose");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("/camera_3/ar_pose_marker", 1, &cb);

  ros::spin();
  return 0;

}