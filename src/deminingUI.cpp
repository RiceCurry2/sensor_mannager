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
        std::cout << "1: Initiate demining" << std::endl;
        std::cout << "2: Load costum map" << std::endl;
        std::cout << "3: Manual emergency control" << std::endl;
        std::cout << "0: Exit" << std::endl;
        std::cout << std::endl;
        std::cout << "Enter topic number and press enter" << std::endl;
        std::cin >> selection;

        switch(selection)
        {
            case 1:
                // Launch deming system aka deminerdeminer
                system ("xterm -e 'roslaunch deminer deminer.launch' & ");
                break;
         case 2:
                // Run mapserver to retrive map aka mapserver
                system ("xterm -e 'rosrun mapserver mapsaver −f deminingarea' & ");
                break;
            case 3:
                // Launch manual controls aka deminingmanualcontrol
                system ("xterm -e 'roslaunch deminer manualcontrol.launch' & ");
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
