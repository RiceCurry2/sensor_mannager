//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//

#include "ros/ros.h"
#include "std_msgs/String.h"

#include <stdio.h>
#include <sstream>

#include "sensor_mannager/safetyIO.h"

//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//

int main(int argc, char **argv)
{
    int done = 0;
    int selection = 0;

    ros::init(argc, argv, "safetyHandling");
    ros::NodeHandle nh;

    ros::Publisher systemHandling_pub = nh.advertise<sensor_mannager::safetyIO>("safetyStateTopic", 1);
    ros::Rate loop_rate(100);

    sensor_mannager::safetyIO msg;

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
            case 1:
            msg.safetyState = 1;

            systemHandling_pub.publish(msg);
            ros::spinOnce;
            std::cout << "Published!" << std::endl;
            std::cout << "Press any key + enter to return to menu" << std::endl;
            std::cin >> selection;
            break;
            case 2:
            msg.safetyState = 0;

            systemHandling_pub.publish(msg);
            ros::spinOnce;
            std::cout << "Published!" << std::endl;
            std::cout << "Press any key + enter to return to menu" << std::endl;
            std::cin >> selection;
            break;
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