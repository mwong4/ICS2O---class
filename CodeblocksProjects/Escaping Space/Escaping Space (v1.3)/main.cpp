/*
>- Author: Max Wong
>- Date: Dec 18, 2018
>- Updated: Dec 19, 2018
>- Purpose: To write a program for a "choose your own adventure" style game.
>- Game should incorperate all the major programming requirements from the course
>-
>- [version 2]
>- Credit to Vedaant Srivastava for teaching me how to effectively error trap
>- Credit to the Halo and Fallout franchise for inspiration and consol formatting
>-
>- [TO DO]
>- Better visual skills components
>-
>- ability to move around station
>- puzzles/restrictions big)
>-
>- player stats
>- player xp + health + hunger + thirst
>- inventory (simple)
>-
>- door hacks (x2-x3)
>- reactor leak
>- broken solar panel/repair
>- collecting materials
>-
>- sleep cycles
>- hours/effort
*/

//Declaring all used libraries
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <math.h>
#include <iomanip>
#include <sstream>
#include <conio.h>

using namespace std;

//Declaring all functions
string mainMenu( bool, bool); //The main menu

void setXP( int [], int, string); //Function that allows the user to customize their initial XP distrubution
void consolHeader( string, string, int); //The UNSC header  used for every UNSC terminal
void printInputError(); //Function used to print an input related error message
void normalHeader();

int actionsMenu( string, string, int ); //Menu to perform an action. Requires a player name, location and authority
void experienceMenu( int [], int, string, string, int ); //Menu to use experience points. Requires the skills array, array size, player name, location and authority
void mapMenu( string, string, int ); //Menu to show player the map. Requires a player name, location and authority
int itemsMenu( int [], string, string, int ); //Menu that allows the player to see and use collected items. Requires the item list array, player name, location and authority

void wakingUp(); //What the player experiences when waking up

bool stringChecker(string);

int main()
{
    //Definig all of my variables
    int playerStats [5]; //Declaring the array the holds the player stats (luck, combat, intelligence, physical)

    bool menuLoad = true; //This boolean defines if the menu load-up is required
    bool askName = true; //This boolean defines if the consol should ask for a name

    string playerName = ""; //This variabel holds the name of the player
    string locationSerialCode = "HAB 4K2"; //This variable holds the serial code for the location

    int adminPower = 1; //This variable determines the authority that the player currently has

    playerName = mainMenu( menuLoad, askName);//Initial main menu sequence
    menuLoad = false; //The computer no longer needs to conduct a load-up
    askName = false; //Tghe computer no longer needs to ask for a name

    setXP( playerStats, 5, playerName); //This function will allow the user to select what their starting skills are

    //consolHeader( locationSerialCode, playerName, adminPower ); //This function is the consol header when the player is using a computer in the game

    wakingUp();

    return 0;
}

//First part of the game when you wake up
void wakingUp()
{

    system("color 7");

    string inputAnything;

    normalHeader();

    cin >> inputAnything;

    //If A is inputed, load action menu
    if( inputAnything == "A" || inputAnything == "a")
    {

    }

    //If X is inputed, load experience menu
    if( inputAnything == "X" || inputAnything == "x")
    {

    }

    //If M is inputed, load map menu
    if( inputAnything == "M" || inputAnything == "m")
    {

    }

    //If I is inputed, load items menu
    if( inputAnything == "I" || inputAnything == "i")
    {

    }


}

//This function allows you to pick your next action. This is the main story section
int actionsMenu ( string playerName, string serialCode, int auth)
{
    normalHeader();


}

//This section is the experience menu. It allows you to upgrade your skills
void experienceMenu ( int playerStats[], int size, string playerName, string serialCode, int auth)
{
    consolHeader( playerName, serialCode, auth);


}

//This section shows the user the map
void mapMenu ( string playerName, string serialCode, int auth )
{
    consolHeader( playerName, serialCode, auth);


}

//This section allows the user to use items
int itemsMenu ( int playerItems[], string playerName, string serialCode, int auth)
{
    consolHeader( playerName, serialCode, auth);


}

//This is the normal, non consol header
void normalHeader()
{

    system("color 7");

    cout << endl;
    cout << "========================================================================================" << endl;
    cout << "| press: [A] for action menu || [X] for experience menu || [M] for map || [I] for items " << endl;
    cout << "|_______________________________________________________________________________________" << endl;

}

//This function, credit to Vedaant, verifies an input has valid characters (is an integer)
bool stringChecker(string myString)
{
    //creating a long double
    long double myFloatString;
    ostringstream conversion;

    //converting the string to a float (the process will cut out any unwanted characters)
    stringstream (myString) >> myFloatString;
    conversion << setprecision(9) << myFloatString;

    //Converting float back into string
    string convertedFloat = conversion.str();


    //If string does equal cleaned float (tring), return true
    if(convertedFloat == myString)
    {
        return true;
    }
    else //Else, return false (meaning the cleaned and orignial strings do  not match)
    {
        return false;
    }
}

//This function is used for the player to define their custom skills at the sart of the game
void setXP( int playerStats[], int size, string playerName)
{
    //Resetting al of the stats
    playerStats[0] = 0;
    playerStats[1] = 0;
    playerStats[2] = 0;
    playerStats[3] = 0;

    string serialCode = "K2G 5C9"; //This value determines the serial code on the UNSC header
    string confirmInput = "";

    int adminPower = 1; //This value determines the authority on the UNSC header
    int currentXPPoints = 10; //This is the variable that holds the amount of points the player has to spend

    int inputValueI = 0;
    std::string inputValueS = "";

    bool customXP = true; //This bool helps to determine when the computer shoudl stop asking the player to pick skills

    do
    {

        //This calls in the header
        consolHeader( serialCode, playerName, adminPower );


        //System diagnostics + player icon
        cout << endl;
        cout << "           _" << endl;
        cout << "         _( )_" << endl;
        cout << "       ||[===]||" << endl;
        cout << "       || [=] ||" << endl;
        cout << "         {---}" << endl;
        cout << "         || ||" << endl;
        cout << "         || ||" << endl;

        //Usedfull information
        cout << endl;
        cout << ">- UNSC user ID - [" << playerName << "]" << endl;
        cout << endl;
        cout << ">- HEALTH: #########-" << endl;
        cout << ">- HUNGER: ####------" << endl;
        cout << ">- THIRST: #####-----" << endl;
        cout << endl;
        cout << endl;

        //[TO DO] - Better visual skills components

        //Current Skills
        cout << ">- LUCK:         ---------- " << playerStats[0] << endl;
        cout << ">- COMBAT:       ---------- " << playerStats[1] << endl;
        cout << ">- INTELLIGENCE: ---------- " << playerStats[2] << endl;
        cout << ">- STRENGTH:     ---------- " << playerStats[3] << endl;


        if(currentXPPoints > 0)
        {
            //Showing the player the options
            cout << endl;
            cout << ">- Please select a number to assign an xp point" << endl;
            cout << endl;
            cout << ">- [1] Luck" << endl;
            cout << ">- [2] Combat" << endl;
            cout << ">- [3] Intelligency" << endl;
            cout << ">- [4] Strength" << endl;
            cout << ">- [9] To reset previous selections (reset xp)" << endl;
            cout << endl;
            cout << ">- You have " << currentXPPoints << " points left" << endl;

            //Error trapping and getting the players choice of skills
            do
            {
                cout << endl;
                cout << "please enter a number" << endl;
                cin >> inputValueS;

                //Error trapping to see if the input is an integer
                if(stringChecker( inputValueS ) == 1)
                {
                    inputValueI = ::atof(inputValueS.c_str());
                }
                if(stringChecker( inputValueS ) == 0)
                {
                    printInputError();
                }

            }
            while(stringChecker( inputValueS ) == 0);

            //If 1 is entered, add to luck
            if(inputValueI == 1)
            {
                playerStats[0] += 1;
                currentXPPoints -= 1;
            }
            //If 2 is entered, add to combat
            if(inputValueI == 2)
            {
                playerStats[1] += 1;
                currentXPPoints -= 1;
            }
            //If 3 is entered, add to Intelligence
            if(inputValueI == 3)
            {
                playerStats[2] += 1;
                currentXPPoints -= 1;
            }
            //If 4 is entered, add to Strength
            if(inputValueI == 4)
            {
                playerStats[3] += 1;
                currentXPPoints -= 1;
            }

            //If 9 is entered, reset everything
            if(inputValueI == 9)
            {
                playerStats[0] = 0;
                playerStats[1] = 0;
                playerStats[2] = 0;
                playerStats[3] = 0;
                currentXPPoints = 10;
            }
            if(inputValueI != 1 && inputValueI != 2 && inputValueI != 3 && inputValueI != 4 && inputValueI != 9)
            {
                printInputError();
            }
        }
        if(currentXPPoints < 1)
        {
            do
            {
                //confirming stats + error trapping for invalid inputs
                cout << endl;
                cout << "do you cofirm these stats? /y/ for yes, /n/ for no" << endl;
                cin >> confirmInput;

                if(confirmInput == "y" || confirmInput == "Y" || confirmInput == "yes" || confirmInput == "Yes")
                {
                    customXP = false;
                }

                if(confirmInput == "n" || confirmInput == "N" || confirmInput == "no" || confirmInput == "No")
                {
                    customXP = true;
                }

                else if (confirmInput != "y" && confirmInput != "Y" && confirmInput != "yes" && confirmInput != "Yes" && confirmInput != "n" && confirmInput != "N" && confirmInput != "no" && confirmInput != "No")

                {
                    printInputError();
                }

            }
            while(confirmInput != "y" && confirmInput != "Y" && confirmInput != "yes" && confirmInput != "Yes" && confirmInput != "n" && confirmInput != "N" && confirmInput != "no" && confirmInput != "No");

        }
        system ("CLS");
    }
    while( customXP == true );


    //cout << endl;
    return;
}

//This function goes through the initial computer "loadup" sequence and the main menu + player name selection
string mainMenu( bool menuLoad, bool askName)
{

    string serialCode = "K2G 5C9"; //This string shows your serial code in the header of the consol, reflecting your loction
    string playerName = ""; //This string shows your player name in the consol header
    int adminPower = 0; //This value determines your admin power in the consol header

    //This function goes through the whole main menu sequence including the consol load up, main menu, and name selection. Name selection and Consol loadup can be disabled after the first log in
    if(menuLoad == true)
    {

        //All below is decoration

        consolHeader( serialCode, playerName, adminPower );

        cout << ">- Initalizing..." << endl;
        cout << ">- [Press Any Key To Continue]" << endl;
        cout << ">- [**Also, use full screen**]" << endl;
        cout << endl;

        getch();

        cout << ">- connecting with server [UNSC SOL] (0/100)" << endl;
        cout << ">- [Press Any Key To Continue]" << endl;
        getch();
        cout << ">- connecting with server [UNSC SOL] (23/100)" << endl;
        getch();
        cout << ">- connecting with server [UNSC SOL] (31/100)" << endl;
        getch();
        cout << ">- connecting with server [UNSC SOL] (47/100)" << endl;
        cout << endl;

        getch();

        cout << endl;
        system("color 4");
        cout << ">- ERROR - Connection failed" << endl;
        cout << endl;


        getch();

        system("color 2");

        cout << endl;
        cout << ">- Local sever status - Damaged - Working at 58% efficiency" << endl;
        cout << ">- [Offline - disconnected]" << endl;
        cout << endl;

        getch();

        cout << endl;
        cout << ">- Auto diagnostics active" << endl;
        cout << ">- Initializing..." << endl;
        cout << endl;

        getch();

        cout << endl;
        cout << ">- Generator - ------------ unresponsive" << endl;
        cout << ">- Backup Generator ------- offine" << endl;
        cout << ">- Solar Cell A ----------- at 23% efficiency" << endl;
        cout << ">- Solar Cell B ----------- offine" << endl;
        cout << ">- Compartenemts A~D ------ offine" << endl;
        cout << ">- Compartements E~H ------ offine" << endl;
        cout << ">- Communications array --- offine" << endl;
        cout << ">- HAB -------------------- Active at 38% eficieny" << endl;
        cout << endl;

        getch();

        cout << ">- Maintain emergency oxygen suply at 20.5%" << endl;
        cout << endl;

        getch();
        cout << endl;
        cout << ">- Rebooting ..." << endl;
        cout << endl;

        getch();

        menuLoad = false;

        cout << endl;

        system ("CLS");

        system("color 7");


        //Title screen
        cout << endl;
        cout << "    ______   _______    ______   ______    _____   _____   ___     _   _______         _______   _____   ______   ______   ______ " << endl;
        cout << "   | _____| |  _____|  |  ____| |  __  |  |  _  | |_   _| |   \\   | | |  _____|       |  _____| |  _  | |  __  | |  ____| | _____|" << endl;
        cout << "   | |____  |  |____   | |      | |__| |  | |_| |   | |   | |\\ \\  | | | |  ___        |  |____  | |_| | | |__| | | |      | |____ " << endl;
        cout << "   |  ____| |_____  |  | |      |  __  |  |  ___|   | |   | | \\ \\ | | | | |__ |       |_____  | |  ___| |  __  | | |      |  ____|" << endl;
        cout << "   | |____  _____|  |  | |____  | |  | |  | |      _| |_  | |  \\ \\| | | |___| |       _____|  | | |     | |  | | | |____  | |____ " << endl;
        cout << "   |______| |_______|  |______| |_|  |_|  |_|     |_____| |_|   \\___| |_______|       |_______| |_|     |_|  |_| |______| |______|" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

        system("color 2");
        cout << endl;
        cout << ">-                                                    [Press Any Key To Continue]" << endl;
        getch();
        cout << endl;

        system ("CLS");

        //Asking for a name
        if(askName == true)
        {
            cout << endl;
            cout << endl;
            cout << ">- please enter your ID" << endl;
            cout << ">- [**Note, you will be refered as this ID for the rest of the game]" << endl;
            cout << endl;
            cin >> playerName;

            cout << endl;
            cout << ">- Welcome <<" << playerName << ">>" << endl;
            getch();
            system ("CLS");
        }

    }
    return playerName;
}

//This function prints the UNSC header
void consolHeader( string serialCode, string userName, int adminPower)
{

    system("color 2");

    //standard header
    cout << ">- United Nations Space Command (UNSC) Terminal" << endl;
    cout << ">- Space Station Discovery" << endl;
    cout << endl;
    cout << ">- Serial Code [" << serialCode << "]" << endl;
    cout << endl;

//standard user header
    if( adminPower == 1)
    {
        cout << ">- -UNSC User Management System-" << endl;
        cout << "================================" << endl;
        cout << "________________________________" << endl;
        cout << "UNSC TacOS  v.235" <<  endl;
        cout << "(S) 2278 FLEETCOM" << endl;
        cout << "=======================" <<  endl;
        cout << "|  User Log:" << endl;
        cout << "|  >> Administrator (UNSD ID 2947-C)" << endl;
        cout << "|  >>> " << userName << ".FLEETCOM" << "_userGroup" << endl;
        //getch();
    }

    //specialized user header
    if( adminPower == 2)
    {
        cout << ">- -UNSC User Management System-" << endl;
        cout << "================================" << endl;
        cout << "________________________________" << endl;
        cout << "UNSC TacOS  v.235" << endl;
        cout << "(S) 2278 FLEETCOM" << endl;
        cout << "=======================" << endl;
        cout << "|  User Log:" << endl;
        cout << "|  >> Administrator (UNSD ID 3194 - P)" << endl;
        cout << "|  >>> " << userName << ".NAVCOM" << "_userGroup" << endl;
        //getch();
    }

    //ONI (Office of Naval Intelligence) user header. Overides all. Used for hacking
    if( adminPower == 3)
    {
        cout << ">- -UNSC User Management System-" << endl;
        cout << "================================" << endl;
        cout << "________________________________" << endl;
        cout << "UNSC TacOS  v.235" << endl;
        cout << "(S) 2278 FLEETCOM" << endl;
        cout << "=======================" << endl;
        cout << "|  User Log:" << endl;
        cout << "|  >> Administrator (UNSD ID 3194 - P)" << endl;
        cout << "|  >>> " << userName << ".ONI" << "_userGroup" << endl;
        //getch();
    }
    cout << endl;
    system ("CLS");
}

//Used to print any input related errors
void printInputError()
{
    cout << endl;
    cout << ">- Error, please input a valid input" << endl;
    cout << ">- [Press Any Key To Continue]" <<endl;
    getch();
}
