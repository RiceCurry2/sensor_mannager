//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//

#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

#include "sensor_mannager/sensorData.h"
#include "sensor_mannager/sensorIO.h"

//---Global variables---//---Global variables---//---Global variables---//---Global variables---//---Global variables---//

    int c_s1io = 7;
    int c_s2io = 7;
    int c_s3io = 7;
    int h_s1e1 = 7;
    int h_s1e2 = 7;
    int h_s2e1 = 7;
    int h_s2e2 = 7;
    int h_s3e1 = 7;
    int h_s3e2 = 7;
    int h_icst = 7;
    int h_s1co = 7;
    int h_s2co = 7;
    int h_s3co = 7;

//---Prototypes---//---Prototypes---//---Prototypes---//---Prototypes---//---Prototypes---//---Prototypes---//---Prototypes---//

void chatterCallback(const sensor_mannager::sensorIO::ConstPtr&);
void handlingCallback (const sensor_mannager::sensorData::ConstPtr& msg);

//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//

int main(int argc, char **argv)
{
    

    ros::init(argc, argv, "sensorCal");

    ros::NodeHandle nh;

    ros::Subscriber sub1 = nh.subscribe("sensorStateTopic", 1000, chatterCallback);
    ros::Subscriber sub2 = nh.subscribe("sensorAndSafetyTopic", 1000, handlingCallback);

    ros::Rate loop_rate(20);

    while(ros::ok())
    {
        std::string s1status = " - No inout on channel - ";
        std::string s2status = " - No input on channel - ";
        std::string s3status = " - No input on channel - ";

        // Check for contact on sensor
        if(h_s1co == 1)
        {
            s1status = "Contact";
        }
        // Check if sensor is OFF
        else if(c_s1io == 0)
        {
            s1status = "OFF";
        }
        // Check if sensor is ON
        else if(c_s1io == 1)
        {
            s1status = "ON";
            // Check if sensor has error 1
            if(h_s1e1 == 1)
            {
                s1status = " - Error - ";
            }
            // Check if sensor has error 2
            else if(h_s1e2 = 1)
            {
                s1status = " - Error - ";
            }
        }

        // Check for contact on sensor
        if(h_s2co == 1)
        {
            s2status = "Contact";
        }
        // Check if sensor is OFF
        else if(c_s2io == 0)
        {
            s2status = "OFF";
        }
        // Check if sensor is ON
        else if(c_s2io == 1)
        {
            s2status = "ON";
            // Check if sensor has error 1
            if(h_s2e1 == 1)
            {
                s2status = " - Error - ";
            }
            // Check if sensor has error 2
            else if(h_s2e2 = 1)
            {
                s2status = " - Error - ";
            }
        }

        // Check for contact on sensor
        if(h_s3co == 1)
        {
            s3status = "Contact";
        }
        // Check if sensor is OFF
        else if(c_s3io == 0)
        {
            s3status = "OFF";
        }
        // Check if sensor is ON
        else if(c_s3io == 1)
        {
            s3status = "ON";
            // Check if sensor has error 1
            if(h_s3e1 == 1)
            {
                s3status = " - Error - ";
            }
            // Check if sensor has error 2
            else if(h_s3e2 = 1)
            {
                s3status = " - Error - ";
            }
        }
        system ("clear");
        std::cout << "Sensor 1 status: " << s1status << std::endl;
        std::cout << "Sensor 2 status: " << s2status << std::endl;
        std::cout << "Sensor 3 status: " << s3status << std::endl;

        // Check if any sensor has contact and make buzzer sound on speaker
        if(h_s1co == 1 || h_s2co == 1 || h_s3co == 1)
        {
            std::cout << "\a";
        }

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

//---Function libraries---//---Function libraries---//---Function libraries---//---Function libraries---//---Function libraries---//

//---Callback for sensorIO---//

void chatterCallback (const sensor_mannager::sensorIO::ConstPtr& msg)
{
    // Copy message content to var
    c_s1io = msg -> sensor1IO;
    c_s2io = msg -> sensor2IO;
    c_s3io = msg -> sensor3IO;
}

//---Callback for sensorData---//

void handlingCallback (const sensor_mannager::sensorData::ConstPtr& msg)
{
    // Copy message content to var
    h_s1e1 = msg -> sensor1Error1;
    h_s1e2 = msg -> sensor1Error2;
    h_s2e1 = msg -> sensor2Error1;
    h_s2e2 = msg -> sensor2Error2;
    h_s3e1 = msg -> sensor3Error1;
    h_s3e2 = msg -> sensor3Error2;
    h_icst = msg -> sensorICStatus;
    h_s1co = msg -> contact1;
    h_s2co = msg -> contact2;
    h_s3co = msg -> contact3;
}