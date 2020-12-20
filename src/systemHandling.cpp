//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//

#include "ros/ros.h"
#include "std_msgs/Int8MultiArray.h"

#include <stdio.h>
#include <sstream>


//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//

int main(int argc, char **argv)
{
    int done = 0;

    ros::init(argc, argv, "systemHandling");
    ros::NodeHandle nh;

    ros::Publisher systemHandling_pub = nh.advertise<const std_msgs::Int8MultiArray>("sensorStateTopic", 1);
    ros::Rate loop_rate(100);

    //int done = 0;
    int selection = 0;
    std_msgs::Int8MultiArray msg;


    while((!done) && (ros::ok()))
    {
        system("clear");
        std::cout << "1: All sensors ON" << std::endl;
        std::cout << "2: All sensors OFF" << std::endl;
        std::cout << "3: Sensor 1 ON" << std::endl;
        std::cout << "4: Sensor 1 OFF" << std::endl;
        std::cout << "5: Sensor 2 ON" << std::endl;
        std::cout << "6: Sensor 2 OFF" << std::endl;
        std::cout << "7: Sensor 3 ON" << std::endl;
        std::cout << "8: Sensor 3 OFF" << std::endl;
        std::cout << "9: Calibrate sensors" << std::endl;
        std::cout << "0: Exit" << std::endl;
        std::cout << std::endl;
        std::cout << "Enter topic number and press enter" << std::endl;
        std::cin >> selection;

        switch (selection)
        {
            case 1:
            // Publish sensor state ON for sensor 1+2+3
            msg.data[0] = 1;
            msg.data[1] = 1;
            msg.data[2] = 1;

            systemHandling_pub.publish(msg);
            ros::spinOnce;
            std::cout << "Published!" << std::endl;
            std::cout << "Press any key + enter to return to menu" << std::endl;
            std::cin >> selection;
            break;
            case 2:
            // Publish sensor state OFF for sensor 1+2+3
            msg.data[0] = 0;
            msg.data[1] = 0;
            msg.data[2] = 0;

            systemHandling_pub.publish(msg);
            ros::spinOnce;
            std::cout << "Published!" << std::endl;
            std::cout << "Press any key + enter to return to menu" << std::endl;
            std::cin >> selection;
            break;
            case 3:
            // Publish sensor state ON for sensor 1
            msg.data[0] = 1;

            systemHandling_pub.publish(msg);
            ros::spinOnce;
            std::cout << "Published!" << std::endl;
            std::cout << "Press any key + enter to return to menu" << std::endl;
            std::cin >> selection;
            break;
            case 4:
            // Publish sensor state OFF for sensor 1
            msg.data[0] = 0;

            systemHandling_pub.publish(msg);
            ros::spinOnce;
            std::cout << "Published!" << std::endl;
            std::cout << "Press any key + enter to return to menu" << std::endl;
            std::cin >> selection;
            break;
            case 5:
            // Publish sensor state ON for sensor 2
            msg.data[1] = 1;

            systemHandling_pub.publish(msg);
            ros::spinOnce;
            std::cout << "Published!" << std::endl;
            std::cout << "Press any key + enter to return to menu" << std::endl;
            std::cin >> selection;
            break;
            case 6:
            // Publish sensor state OFF for sensor 2
            msg.data[1] = 0;

            systemHandling_pub.publish(msg);
            ros::spinOnce;
            std::cout << "Published!" << std::endl;
            std::cout << "Press any key + enter to return to menu" << std::endl;
            std::cin >> selection;
            break;
            case 7:
            // Publish sensor state ON for sensor 3
            msg.data[2] = 1;

            systemHandling_pub.publish(msg);
            ros::spinOnce;
            std::cout << "Published!" << std::endl;
            std::cout << "Press any key + enter to return to menu" << std::endl;
            std::cin >> selection;
            break;
            case 8:
            // Publish sensor state OFF for sensor 3
            msg.data[2] = 0;

            systemHandling_pub.publish(msg);
            ros::spinOnce;
            std::cout << "Published!" << std::endl;
            std::cout << "Press any key + enter to return to menu" << std::endl;
            std::cin >> selection;
            break;
            case 9:
            // Run sensor calibration aka sensor_cal
            system ("xterm -e 'rosrun sensor_mannager sensor_cal' & ");
            break;
            case 0:
            // Exit loop (ending program execution with return value "0")
            done = 1;
            break;
            default:
            std::cout << "Invalid selection" << std::endl;
            break;
        }    
    }
    return 0;   
}