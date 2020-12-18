#include "ros/ros.h"
#include "std_msgs/String.h"
#include <stdio.h>
#include <sstream>
#include "sensor_mannager/sensorData.h"
#include "sensor_mannager/sensorIO.h"



int main(int argc, char **argv)
{

    ros::init(argc, argv, "dummy");
    ros::NodeHandle nh;

    ros::Publisher systemHandling_pub = nh.advertise<sensor_mannager::sensorData>("sensorAndSafetyTopic", 1);
    ros::Rate loop_rate(100);



    int done = 0;
    int selection = 0;
    sensor_mannager::sensorData msg;


    while(!done)
    {
        
    
        std::cout << "Enter sensor status input: ";
        std::cin >> selection;

        switch (selection)
        {
            case 1:
            msg.contact1 = 1;
            msg.contact2 = 1;
            msg.contact3 = 1;
            msg.safetyNotOK = 1;
            msg.safetyOff = 1;
            msg.safetyOk = 1;
            msg.safetyState = 1;
            msg.sensor1Error1 = 1;
            msg.sensor1Error2 = 1;
            msg.sensor2Error1 = 1;
            msg.sensor2Error2 = 1;
            msg.sensor3Error1 = 1;
            msg.sensor3Error2 = 1;
            msg.sensorICStatus = 0;


            systemHandling_pub.publish(msg);
            ros::spinOnce;
            std::cout << "Published!" << std::endl;
            break;
            case 2:

            break;
            case 3:
            system ("xterm -e 'rosrun sensor_mannager sensor_cal' & ");
            default:

            break;
        }    
    }
    return 0;   
}