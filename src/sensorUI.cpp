//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//---Includes---//

#include <stdio.h>

#include "std_msgs/String.h"

//---Prototypes---//---Prototypes---//---Prototypes---//---Prototypes---//---Prototypes---//---Prototypes---//---Prototypes---//

void ui();

//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//---Main---//

int main(int argc, char **argv)
{
    ui();
  
    return 0;
}

//---Function libraries---//---Function libraries---//---Function libraries---//---Function libraries---//---Function libraries---//

void ui()
{
    int done = 0;
    int selection = 0;

    while(!done)
    {
        system ("clear");
        std::cout << "1: Sensor control" << std::endl;
        std::cout << "2: Safety control" << std::endl;
        std::cout << "3: System readout" << std::endl;
        std::cout << "4: Mapping services" << std::endl;
        std::cout << "5: Demining services" << std::endl;
        std::cout << "0: Exit" << std::endl;
        std::cout << std::endl;
        std::cout << "Enter topic number and press enter" << std::endl;
        std::cin >> selection;

        switch(selection)
        {
            case 1:
                // Run sensor control aka system_handling
                system ("xterm -e 'rosrun sensor_mannager system_handling' & ");
                break;
         case 2:
                // Run safety control aka safety_handling
                system ("xterm -e 'rosrun sensor_mannager safety_handling' & ");
                break;
            case 3:
                // Run system readout aka system_monitor
                system ("xterm -e 'rosrun sensor_mannager system_monitor' & ");
                break;
            case 4:
                // Run mapping user interface aka mappingui
                system ("xterm -e 'rosrun sensor_mannager mappingui' & ");
                break;
            case 5:
                // Run demining user interface aka deminingui
                system ("xterm -e 'rosrun sensor_mannager deminingui' & ");
                break;
            case 6:
                // Run rosnode for Arduino comms on USB 0 aka rosserial_python
                system ("xterm -e 'rosrun rosserial_python serial_node.py /dev/ttyACM0' & ");
                break;
            case 0:
                // Exit loop (ending program execution with return value "0")
                done = 1;
                break;
            default:
                std::cout << "Invalid selection";
                std::cout << "Press any key + enter to return to menu" << std::endl;
                std::cin >> selection;
                break;
        }
    }
}