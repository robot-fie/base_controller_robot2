
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <motors_panda/Motors.h>

const int LEFT = -1;
const int RIGHT = 1;

class BaseController {
    ros::NodeHandle n;
    ros::NodeHandle private_n;
    // Subscriptores
    ros::Subscriber twist;
    // Publicadores
    ros::Publisher tracksNode;

public:
    BaseController();
    void twistMsgCallback(const geometry_msgs::Twist::ConstPtr&);
    void motorDriver(const double, const double);
};
