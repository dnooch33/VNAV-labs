#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>

#include <geometry_msgs/msg/transform_stamped.hpp>
#include <iostream>
#include <memory>
#include <rclcpp/create_timer.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/timer.hpp>

class FramesPublisherNode : public rclcpp::Node {
  rclcpp::Time startup_time;

  rclcpp::TimerBase::SharedPtr heartbeat;

  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster;
  // ...

 public:
  FramesPublisherNode() : Node("frames_publisher_node") {
    
    tf_broadcaster = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

    startup_time = now();
    heartbeat = create_timer(this,
                             get_clock(),
                             rclcpp::Duration::from_seconds(0.02),
                             std::bind(&FramesPublisherNode::onPublish, this));
    heartbeat->reset();
  }

  void onPublish() {
    // NOTE: This method is called at 50Hz, due to the timer created on line 25.

    //
    // 1. TODO: Compute time elapsed in seconds since the node has been started
    //    i.e. the time elapsed since startup_time (defined on line 13)
    //   HINTS:
    //   - Get the current time with this->now()
    //   - use the - operator between the current time and startup_time
    //   - convert the resulting Duration to seconds, store result into a double

    double t = (this->get_clock()->now() - startup_time).seconds();

    // Here we declare two geometry_msgs::msg::TransformStamped objects, which
    // need to be populated
    geometry_msgs::msg::TransformStamped world_T_av1;
    geometry_msgs::msg::TransformStamped world_T_av2;

    // 2. TODO: Populate the two transforms for the AVs, using the variable "time"
    //    computed above. Specifically:
    //     - world_T_av1 should have origin in [cos(time), sin(time), 0.0] and
    //       rotation such that:
    //        i) its y axis stays tangent to the trajectory and
    //       ii) the z vector stays parallel to that of the world frame
    //
    //     - world_T_av2 shoud have origin in [sin(time), 0.0, cos(2*time)], the
    //       rotation is irrelevant to our purpose.
    //    NOTE: world_T_av1's orientation is crucial for the rest fo the
    //    assignment,
    //          make sure you get it right
    //
    //    HINTS:
    //    - check out the ROS tf2 Tutorials:
    //    https://docs.ros.org/en/humble/Tutorials/Intermediate/Tf2/Tf2-Main.html
    //    - consider the setRPY method on a tf2::Quaternion for world_T_av1
    world_T_av1.header.stamp = this->get_clock()->now();
    world_T_av1.header.frame_id = "world";
    world_T_av1.child_frame_id = "av1";

    world_T_av1.transform.translation.x = std::cos(t);
    world_T_av1.transform.translation.y = std::sin(t);
    world_T_av1.transform.translation.z = 0.0;

    tf2::Quaternion av1_q;
    av1_q.setRPY(0,0,t);
    world_T_av1.transform.rotation.x = av1_q.x();
    world_T_av1.transform.rotation.y = av1_q.y();
    world_T_av1.transform.rotation.z = av1_q.z();
    world_T_av1.transform.rotation.w = av1_q.w();

    world_T_av2.header.stamp = this->get_clock()->now();
    world_T_av2.header.frame_id = "world";
    world_T_av2.child_frame_id = "av2";

    world_T_av2.transform.translation.x = std::sin(t);
    world_T_av2.transform.translation.y = 0.0;
    world_T_av2.transform.translation.z = std::cos(2*t);

    world_T_av2.transform.rotation.x = 0.0;
    world_T_av2.transform.rotation.y = 0.0;
    world_T_av2.transform.rotation.z = 0.0;
    world_T_av2.transform.rotation.w = 1.0;
    // ...

    // 3. TODO: Publish the transforms, namely:
    //     - world_T_av1 with frame_id "world", child_frame_id "av1"
    //     - world_T_av2 with frame_id "world", child_frame_id "av2"
    //    HINTS:
    //         1. you need to define a
    //         std::unique_ptr<tf2_ros::TransformBroadcaster> as a member of the
    //            node class (line 18) and use its sendTransform method below
    //         2. the frame names are crucial for the rest of the assignment,
    //            make sure they are as specified, "av1", "av2" and "world"

    tf_broadcaster->sendTransform(world_T_av1);
    tf_broadcaster->sendTransform(world_T_av2);
  }
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FramesPublisherNode>());
  rclcpp::shutdown();
  return 0;
}
