//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//

#include "ros/ros.h"
#include "std_msgs/Int8MultiArray.h"
#include "std_msgs/Int16MultiArray.h"

#include <sstream>


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

void chatterCallback(const std_msgs::Int8MultiArray::ConstPtr&);
void handlingCallback (const std_msgs::Int16MultiArray::ConstPtr& msg);

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

void chatterCallback (const std_msgs::Int8MultiArray::ConstPtr& msg)
{
    // Copy message content to var
    c_s1io = msg -> data[0]; // Sensor 1 ON/OFF
    c_s2io = msg -> data[1]; // Sensor 2 ON/OFF
    c_s3io = msg -> data[2]; // Sensor 3 ON/OFF
}

//---Callback for sensorData---//

void handlingCallback (const std_msgs::Int16MultiArray::ConstPtr& msg)
{
    // Copy message content to var
    h_s1e1 = msg -> data[6]; // sensor1Error1
    h_s1e2 = msg -> data[7]; // sensor1Error2
    h_s2e1 = msg -> data[8]; // sensor2Error1
    h_s2e2 = msg -> data[9]; // sensor2Error2
    h_s3e1 = msg -> data[10]; // sensor3Error1
    h_s3e2 = msg -> data[11]; // sensor3Error2
    h_icst = msg -> data[12]; // sensorICStatus
    h_s1co = msg -> data[0]; // contact1
    h_s2co = msg -> data[1]; // contact2
    h_s3co = msg -> data[2]; // contact3
}