//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//

#include "ros/ros.h"
#include "std_msgs/Int8MultiArray.h"
#include "std_msgs/Int16MultiArray.h"
#include "std_msgs/Int32MultiArray.h"

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
    int h_sano = 7;
    int h_faof = 7;
    int h_saok = 7;
    int hs_sast = 7;
    std::string ROSComStr = " - No input on channel";
    std::string sensorComStr = " - No input on channel";
    std::string safetyComStr = " - No input on channel";
    std::string sensorICStr = " - No input on channel";
    std::string safetyICStr = " - No input on channel";

//---Prototypes---//---Prototypes---//---Prototypes---//---Prototypes---//---Prototypes---//---Prototypes---//---Prototypes---//

void chatterCallback(const std_msgs::Int8MultiArray::ConstPtr&);
void handlingCallback (const std_msgs::Int16MultiArray::ConstPtr& msg);
void handlingSafetyCallback (const std_msgs::Int32MultiArray::ConstPtr& msg);
void systemStatus();

//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//

int main(int argc, char **argv)
{
    ros::init(argc, argv, "systemMonitor");

    ros::NodeHandle nh;

    ros::Subscriber sub1 = nh.subscribe("sensorStateTopic", 1000, chatterCallback);
    ros::Subscriber sub2 = nh.subscribe("sensorAndSafetyTopic", 1000, handlingCallback);
    ros::Subscriber sub3 = nh.subscribe("safetyStateTopic", 1000, handlingSafetyCallback);

    ros::Rate loop_rate(20);

    while(ros::ok())
    {
        systemStatus();

        std::string s1status = " - No inout on channel - ";
        std::string s2status = " - No input on channel - ";
        std::string s3status = " - No input on channel - ";

        if(h_s1co == 1)
        {
            s1status = "Contact";
        }
        else if(c_s1io == 0)
        {
            s1status = "OFF";
        }
        else if(c_s1io == 1)
        {
            s1status = "ON";
            if(h_s1e1 == 1)
            {
                s1status = " - No power at sensor - ";
            }
            else if(h_s1e2 = 1)
            {
                s1status = " - Short circuit in sensor - ";
            }
        }

        if(h_s1co == 1)
        {
            s2status = "Contact";
        }
        else if(c_s2io == 0)
        {
            s2status = "OFF";
        }
        else if(c_s2io == 1)
        {
            s2status = "ON";
            if(h_s2e1 == 1)
            {
                s2status = " - No power at sensor - ";
            }
            else if(h_s2e2 = 1)
            {
                s2status = " - Short circuit in sensor - ";
            }
        }

        if(h_s1co == 1)
        {
            s3status = "Contact";
        }
        else if(c_s3io == 0)
        {
            s3status = "OFF";
        }
        else if(c_s3io == 1)
        {
            s3status = "ON";
            if(h_s3e1 == 1)
            {
                s3status = " - No power at sensor - ";
            }
            else if(h_s3e2 = 1)
            {
                s3status = " - Short circuit in sensor - ";
            }
        }
        
        system("clear");
        std::cout << " --- SYSTEM STATUS ---" << std::endl;
        std::cout << "Client <=> ROS communication:           " << ROSComStr << std::endl;
        std::cout << "Client <=> Sensor communication:        " << sensorComStr << std::endl;
        std::cout << "Safety circuit => client communication: " << safetyComStr << std::endl;
        std::cout << "Sensor IC status:                       " << sensorICStr << std::endl;
        std::cout << "Safety IC status:                       " << safetyICStr << std::endl;
        std::cout << "Sensor 1 status:                        " << s1status << std::endl;
        std::cout << "Sensor 2 status:                        " << s2status << std::endl;
        std::cout << "Sensor 3 status:                        " << s3status << std::endl;
        
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
    c_s2io = msg -> data[1]; // Senspr 2 ON/OFF
    c_s3io = msg -> data[2]; // Sensor 3 ON/OFF
}

//---Callback for sensorData---//

void handlingCallback (const std_msgs::Int16MultiArray::ConstPtr& msg)
{
    // Copy message content to var:
    h_s1co = msg -> data[0]; // contact 1
    h_s2co = msg -> data[1]; // contact 2
    h_s3co = msg -> data[2]; // contact 3
    h_sano = msg -> data[3]; // safetyNotOK
    h_faof = msg -> data[5]; // safetyOFF
    h_saok = msg -> data[4]; // safetyOK
    h_s1e1 = msg -> data[6]; // sensor1Error1
    h_s1e2 = msg -> data[7]; // sensor1Error2
    h_s2e1 = msg -> data[8]; // sensor2Error1
    h_s2e2 = msg -> data[9]; // sensor2Error2
    h_s3e1 = msg -> data[10]; // sensor3Error1
    h_s3e2 = msg -> data[11]; // sensor3Error2
    h_icst = msg -> data[12]; // sensorICStatus
}

//---Callback for safetyIO---//

void handlingSafetyCallback (const std_msgs::Int32MultiArray::ConstPtr& msg)
{
    // Copy message content to var
    hs_sast = msg -> data[0]; // SafetyCircuit ON/OFF
}

//---Translation library for system status---//

void systemStatus()
{
    // Chech status of ROS comunication
    if((hs_sast == 1) || (hs_sast == 0) || (hs_sast == 8))
    {
        ROSComStr = "OK";
    }
    else
    {
        ROSComStr = " - Error - ";
    }

    // Chech status of sensor comunication and integrety of ATmega2560 micro controller
    if(h_icst == 1)
    {
        sensorComStr = "OK";
        sensorICStr = "Ok";
    }
    else
    {
        sensorComStr = " - Error - ";
        sensorICStr = " - Error - ";
    }
    
    // // Chech status of safety circuit communication
    if((h_saok == 1) || (h_faof == 1))
    {
        safetyComStr = "Ok";
    }
    else
    {
        safetyComStr = " - Error - ";
    }

    // Chech integrety of ATmega328 micro controller
    if((h_sano != 1) && ((h_saok == 1) || (h_faof == 1)))
    {
        safetyICStr = "Ok";
    }
    else
    {
        safetyICStr = " - Error - ";
    }    
}