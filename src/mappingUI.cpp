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
        std::cout << "1: Initiate mapping" << std::endl;
        std::cout << "2: Initiate keyboard input" << std::endl;
        std::cout << "3: Save map" << std::endl;
        std::cout << "0: Exit" << std::endl;
        std::cout << std::endl;
        std::cout << "Enter topic number and press enter" << std::endl;
        std::cin >> selection;

        switch(selection)
        {
            case 1:
                // Launch mapping aka turtlebotgmapping
                system ("xterm -e 'roslaunch deminer turtlebot_gmapping.launch' & ");
                break;
         case 2:
                // Launch kayboard control via teleop aka keyboardteleop
                system ("xterm -e 'roslaunch turtlebot_teleop keyboard_teleop.launch' & ");
                break;
            case 3:
                // Run map saver aka mapsaver
                system ("xterm -e 'rosrun mapserver mapsaver −f deminingarea' & ");
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
