//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//

#include "ros/ros.h"
#include "std_msgs/Int32MultiArray.h"

#include <stdio.h>
#include <sstream>

//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//

int main(int argc, char **argv)
{
    int done = 0;
    int selection = 0;

    ros::init(argc, argv, "safetyHandling");
    ros::NodeHandle nh;

    ros::Publisher systemHandling_pub = nh.advertise<std_msgs::Int32MultiArray>("safetyStateTopic", 1);
    ros::Rate loop_rate(100);

    std_msgs::Int32MultiArray msg;

    while((!done) && (ros::ok()))
    {
        system("clear");
        std::cout << "1: Safety circuit ON" << std::endl;
        std::cout << "2: Safety circuit OFF" << std::endl;
        std::cout << "0: Exit" << std::endl;
        std::cout << "Enter topic number and press enter" << std::endl;
        std::cin >> selection;

        switch (selection)
        {
            // Safety circuit ON
            case 1:
            msg.data[0] = 1; // safetyState

            systemHandling_pub.publish(msg);
            ros::spinOnce;
            std::cout << "Published!" << std::endl;
            std::cout << "Press any key + enter to return to menu" << std::endl;
            std::cin >> selection;
            break;
            // Safety circuit OFF
            case 2:
            msg.data[0] = 0; // safetyState

            systemHandling_pub.publish(msg);
            ros::spinOnce;
            std::cout << "Published!" << std::endl;
            std::cout << "Press any key + enter to return to menu" << std::endl;
            std::cin >> selection;
            break;
            // Exit loop
            case 0:
            done = 1;
            break;
            default:
            std::cout << "Invalid selection" << std::endl;
            break;
        }    
    }

    return 0;   
}