//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int8.h"

#include <sstream>

#include "sensor_mannager/sensorData.h"
#include "sensor_mannager/sensorIO.h"
#include "sensor_mannager/safetyIO.h"

//---Global variables---//---Global variables---//---Global variables---//---Global variables---//---Global variables---//

    int c_s1io = 1;
    int c_s2io = 1;
    int c_s3io = 1;
    int h_s1e1 = 0;
    int h_s1e2 = 0;
    int h_s2e1 = 0;
    int h_s2e2 = 0;
    int h_s3e1 = 0;
    int h_s3e2 = 0;
    int h_icst = 1;
    int h_s1co = 0;
    int h_s2co = 0;
    int h_s3co = 0;
    int h_sano = 0;
    int h_faof = 0;
    int h_saok = 1;
    int hs_sast = 1;
    std::string ROSComStr = " - No input on channel";
    std::string sensorComStr = " - No input on channel";
    std::string safetyComStr = " - No input on channel";
    std::string sensorICStr = " - No input on channel";
    std::string safetyICStr = " - No input on channel";

//---Prototypes---//---Prototypes---//---Prototypes---//---Prototypes---//---Prototypes---//---Prototypes---//---Prototypes---//

void chatterCallback(const sensor_mannager::sensorIO::ConstPtr&);
//void handlingCallback (const sensor_mannager::sensorData::ConstPtr& msg);
void handlingCallback (const std_msgs::Int8::ConstPtr& msg);
void handlingSafetyCallback (const sensor_mannager::safetyIO::ConstPtr& msg);
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
            s2status = "Contact";
            s3status = "Contact";
        }
        else if(c_s1io == 0)
        {
            s1status = "OFF";
        }
        else if(c_s1io == 1)
        {
            s1status = "ON";
            /*if(h_s1e1 == 1)
            {
                s1status = " - No power at sensor - ";
            }
            else if(h_s1e2 = 1)
            {
                s1status = " - Short circuit in sensor - ";
            }*/
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
            /*if(h_s2e1 == 1)
            {
                s2status = " - No power at sensor - ";
            }
            else if(h_s2e2 = 1)
            {
                s2status = " - Short circuit in sensor - ";
            }*/
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
            /*if(h_s3e1 == 1)
            {
                s3status = " - No power at sensor - ";
            }
            else if(h_s3e2 = 1)
            {
                s3status = " - Short circuit in sensor - ";
            }*/
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

void chatterCallback (const sensor_mannager::sensorIO::ConstPtr& msg)
{
    // Copy message content to var
    c_s1io = msg -> sensor1IO;
    c_s2io = msg -> sensor2IO;
    c_s3io = msg -> sensor3IO;
}

//---Callback for sensorDate---//

void handlingCallback (const std_msgs::Int8::ConstPtr& msg)
{
    // Copy message content to var
    h_s1co = msg -> data;
    /*h_s2co = msg -> contact2;
    h_s3co = msg -> contact3;
    h_sano = msg -> safetyNotOK;
    h_faof = msg -> safetyOff;
    h_saok = msg -> safetyOk;
    h_s1e1 = msg -> sensor1Error1;
    h_s1e2 = msg -> sensor1Error2;
    h_s2e1 = msg -> sensor2Error1;
    h_s2e2 = msg -> sensor2Error2;
    h_s3e1 = msg -> sensor3Error1;
    h_s3e2 = msg -> sensor3Error2;
    h_icst = msg -> sensorICStatus;*/
}

//---Callback for safetyIO---//

void handlingSafetyCallback (const sensor_mannager::safetyIO::ConstPtr& msg)
{
    // Copy message content to var
    hs_sast = msg -> safetyState;
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