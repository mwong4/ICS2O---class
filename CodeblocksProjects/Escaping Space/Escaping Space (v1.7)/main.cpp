/*
>- Author: Max Wong
>- Date: Dec 18, 2018
>- Updated: Dec 21, 2018
>- Purpose: To write a program for a "choose your own adventure" style game.
>- Game should incorperate all the major programming requirements from the course
>-
>- [version 1.7]
>- Credit to Vedaant Srivastava for teaching me how to effectively error trap
>- Credit to the Halo and Fallout franchise for inspiration and consol formatting
>-
>- [TO DO]
>- fix the item menu/error trap - being stuck in a loop
>-
>- Complete scenarios for expeirnece/ use of items
>-
>- ability to move around station
>- puzzles/restrictions big)
>-
>- door hacks (x2-x3)
>- reactor leak
>- broken solar panel/repair
>- collecting materials
*/

/*
[Table of contents - Dec 21, 2018]

Header:1-39
Libraries: 42-49
Function prototypes: 54-68
main: 70-92
*/

//Declaring all used libraries
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <math.h>
#include <iomanip>
#include <sstream>
#include <cstdlib>

using namespace std;

//Declaring all functions
string mainMenu( bool, bool); //The main menu

void setXP( int [], int, string); //Function that allows the user to customize their initial XP distrubution
void consolHeader( string, string, int); //The UNSC header  used for every UNSC terminal
void printInputError(); //Function used to print an input related error message
void normalHeader(); //Function to display the normal header

int actionsMenu( string, string, int ); //Menu to perform an action. Requires a player name, location and authority
void experienceMenu( int [], int, string, string, int, bool ); //Menu to use experience points. Requires the skills array, array size, player name, location and authority
void mapMenu( string, string, int ); //Menu to show player the map. Requires a player name, location and authority
void itemsMenu( int [], int, string, string, int, int ); //Menu that allows the player to see and use collected items. Requires the item list array, player name, location and authority

void scavanging( string , string , int , int [], int , string [], int, bool [], int );


void wakingUp( string, string, int, int[], int, int[], int, bool, int, string[], bool[]); //What the player experiences when waking up. Requires a player name, location and authority

bool stringChecker(string); //Function to check if an input is a float or integer

int main()
{
    //Definig all of my variables
    int playerStats [6]; //Declaring the array the holds the player stats (luck, combat, intelligence, physical, current experience points)
    int foundMaterials [10]; //Declaring the array that holds the items found by the player( tape, wire, cloth, adhesive, space suit, screw sriver, ONI keycard, NAVCOm keycard, note and wire tweezers)
    bool scavanged [10]; //A array that allows the code to know where has already been scavanged
    string playerItemsStrings [10]; //Declaring the array that holds the name of the items found by the player

    //Setting all of the couted strings
    playerItemsStrings [0] = "duck tape roll";
    playerItemsStrings [1] = "small electric wire roll";
    playerItemsStrings [2] = "small cloth";
    playerItemsStrings [3] = "bottle of adhesive";
    playerItemsStrings [4] = "space suit";
    playerItemsStrings [5] = "universal screw driver";
    playerItemsStrings [6] = "ONI ketcard";
    playerItemsStrings [7] = "NAVCOM keycard";
    playerItemsStrings [8] = "note";
    playerItemsStrings [9] = "Wire tweezers";

    //Resetting all of the stats
    playerStats[0] = 0;
    playerStats[1] = 0;
    playerStats[2] = 0;
    playerStats[3] = 0;
    playerStats[4] = 10;
    playerStats[5] = 9;

    for(int i = 0; i < 10; i++)
    {
        //Resetting al of the items
        foundMaterials [i] = 0;
        scavanged [i] = false;
    }

    bool menuLoad = true; //This boolean defines if the menu load-up is required
    bool askName = true; //This boolean defines if the consol should ask for a name
    bool starting = true; //This boolean defines if the player is currently starting the game or not - Used for some game mechinics like custom experience, only allowed when first starting out

    string playerName = ""; //This variabel holds the name of the player
    string locationSerialCode = "K2G 5C9"; //This variable holds the serial code for the location

    int adminPower = 1; //This variable determines the authority that the player currently has
    int scenario = 0; //This variable determines what scenario is currently active and thus what actions can be performed

    playerName = mainMenu( menuLoad, askName);//Initial main menu sequence
    menuLoad = false; //The computer no longer needs to conduct a load-up
    askName = false; //Tghe computer no longer needs to ask for a name

    experienceMenu( playerStats, 6, playerName, locationSerialCode, adminPower, starting); //This function will allow the user to select what their starting skills are

    locationSerialCode = "HAB 4K2"; //Setting location to the HAB
    starting = false; //User is no longer in the starting phase

    wakingUp( playerName, locationSerialCode, adminPower, playerStats, 6, foundMaterials, 10, starting, scenario, playerItemsStrings, scavanged);

    return 0;
}

//First part of the game when you wake up
void wakingUp( string playerName, string location, int adminAuth, int playerStats[], int statsSize, int foundMaterials[], int materialsSize, bool starting, int scenario, string itemNames[], bool scavanged[])
{
    std::string inputAnything = "";
    bool makingDesition = true;
    bool storyOver = false;
    int randomNumber = rand() %10;
    int inputValue = 0;

    //Some story
    normalHeader();

    cout << "// As your cryo chamber disengages, you start to feel more and more in control of your muscles" << endl;
    cout << "// With what strength you have, you push the hatch to your chamber open" << endl;
    cout << endl;

    getch();
    cout << "//With your return to the living world, the dark empty HAB or habitation room greets you" << endl;
    cout << "//You know that at any moment, disaster could struck and you could die instantly" << endl;
    cout << "//This is, of course, the nature of space" << endl;
    cout << endl;

    do
    {
        if(storyOver == true)
        {
            normalHeader();
        }
        //Shot the options
        getch();
        cout << endl;
        cout << "[1]To your left, you spot the entrance to the medical bay" << endl;
        cout << "[2]In front of you stands the central airlocks" << endl;
        cout << "[3]To your right is another door for the cafiteria" << endl;
        cout << "[4]Behind you lies a solid door labeled [REACTOR]" << endl;
        cout << "[5]All aroud you lies scraps and shelves that you could possibly scavange something from" << endl;
        storyOver = true;
        //Ask what used would like to input
        getch;
        do
        {
            cout << endl;
            cout << "What would you like to do?" << endl;
            cout << endl;
            cin >> inputAnything;
            //If A is inputed, load action menu
            if( inputAnything == "A" || inputAnything == "a")
            {
                cout << endl;
                cout << ">- You are currenty in the action menu" << endl;
                cout <<">- [Press An Key To Continue]" << endl;
                cout << endl;
                getch();
                system ("CLS");
            }
            //If V is inputed, load vitals + experience menu
            if( inputAnything == "V" || inputAnything == "v")
            {
                system ("CLS");
                experienceMenu( playerStats, 5, playerName, location, adminAuth, starting);
            }
            //If M is inputed, load map menu
            if( inputAnything == "M" || inputAnything == "m")
            {
                system ("CLS");
                mapMenu( location, playerName, adminAuth);
            }
            //If I is inputed, load items menu
            if( inputAnything == "I" || inputAnything == "i")
            {
                system ("CLS");
                itemsMenu ( foundMaterials, 10, playerName, location, adminAuth, scenario);
            }
            //If the input does not reference a menu, check to see that the input is an integer
            if( stringChecker( inputAnything ) == 0)
            {
                printInputError();
            }
            if( stringChecker( inputAnything ) == 1)
            {
                inputValue = ::atof(inputAnything.c_str());
            }
            if( inputValue != 1 && inputValue != 2 && inputValue != 3 && inputValue != 4 && inputValue != 5 )
            {
                printInputError();
            }
            if( inputValue == 1)
            {
                system("CLS");
            }
            if( inputValue == 2)
            {
                system("CLS");
            }
            if( inputValue == 3)
            {
                system("CLS");
            }
            if( inputValue == 4)
            {
                system("CLS");
            }
            if( inputValue == 5)
            {
                system("CLS");
                scavanging( playerName , location , adminAuth , foundMaterials, 10 , itemNames, 10, scavanged, 10 );
            }
        }
        while( stringChecker( inputAnything ) == 0);
    }
    while( makingDesition == true );
}

void scavanging  (string playerName, string location, int authority, int foundItems[], int itemsSize, string itemNames[], int namesSize, bool scavanged[], int scavangedSize)
{
    int randomQuantity = 0;
    //This calls in the header
    consolHeader( location, playerName, authority );

    //If location is right but player has already scavanged in this location
    if( location == "HAB 4K2" && scavanged[0] == true ) {
        cout << endl;
        cout << ">- sorry, you have already scavanged" << endl;
        cout << endl;
    }
    //If location is right but player has not scavanged in this location yet:
    if( location == "HAB 4K2" && scavanged[0] == false )
    {
        for(int i = 0; i <= 10; i++)
        {
            //Generate a random nummber
            randomQuantity = rand() %2;
            //cout and assign the values to the array
            if((i == 2 || i == 0) && randomQuantity != 0)
            {
                foundItems [i] += randomQuantity;
                cout << "you found " << itemNames [i] << " x" << randomQuantity << endl;
                cout << endl;
            }
        }
        scavanged[0] = true;
    }

    cout << ">- [Press Any Key To Continue]" << endl;
    getch();
    system("CLS");
    return;
}

//This function allows you to pick your next action. This is the main story section
int actionsMenu ( string playerName, string serialCode, int auth)
{
    normalHeader();
}

//This section is the experience menu. It allows you to upgrade your skills
void experienceMenu ( int playerStats[], int size, string playerName, string serialCode, int auth, bool starting)
{
    string confirmInput = "";
    std::string inputValueS = "";

    int inputValueI = 0;

    bool customXP = true; //This bool helps to determine when the computer shoudl stop asking the player to pick skills

    do
    {
        //This calls in the header
        consolHeader( serialCode, playerName, auth );

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
        cout << ">- HEALTH:";
        //For printing the sharps
        for( int i = 0; i < (playerStats[5]); i++ )
        {
            cout << "#";
        }
        for( int i = 0; i < (10 - playerStats[5]); i++ )
        {
            cout << "-";
        }
        cout << endl;
        cout << endl;

        //Showing player stats
        cout << ">- LUCK:         ";
        //For printing the sharps and dashes
        for( int i = 0; i < (playerStats[0]); i++ )
        {
            cout << "#";
        }
        for( int i = 0; i < (10 - playerStats[0]); i++ )
        {
            cout << "-";
        }
        cout << endl;

        cout << ">- COMBAT:       ";
        for( int i = 0; i < (playerStats[1]); i++ )
        {
            cout << "#";
        }
        for( int i = 0; i < (10 - playerStats[1]); i++ )
        {
            cout << "-";
        }
        cout << endl;

        cout << ">- INTELLIGENCE: ";
        for( int i = 0; i < (playerStats[2]); i++ )
        {
            cout << "#";
        }
        for( int i = 0; i < (10 - playerStats[2]); i++ )
        {
            cout << "-";
        }
        cout << endl;

        cout << ">- STRENGTH:     ";
        for( int i = 0; i < (playerStats[3]); i++ )
        {
            cout << "#";
        }
        for( int i = 0; i < (10 - playerStats[3]); i++ )
        {
            cout << "-";
        }
        cout << endl;

        if(playerStats[4] > 0)
        {
            //Showing the player the options
            cout << endl;
            cout << ">- Please select a number to assign an xp point" << endl;
            cout << endl;
            cout << ">- [1] Luck" << endl;
            cout << ">- [2] Combat" << endl;
            cout << ">- [3] Intelligency" << endl;
            cout << ">- [4] Strength" << endl;

            if(starting == true)
            {
                cout << ">- [9] To reset previous selections (reset xp)" << endl;
            }
            cout << endl;
            cout << ">- You have " << playerStats[4] << " points left" << endl;

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
            if(inputValueI == 1 && playerStats[0] < 10 && playerStats[4] > 0)
            {
                playerStats[0] += 1;
                playerStats[4] -= 1;
            }
            //If 2 is entered, add to combat
            if(inputValueI == 2 && playerStats[1] < 10 && playerStats[4] > 0)
            {
                playerStats[1] += 1;
                playerStats[4] -= 1;
            }
            //If 3 is entered, add to Intelligence
            if(inputValueI == 3 && playerStats[2] < 10 && playerStats[4] > 0)
            {
                playerStats[2] += 1;
                playerStats[4] -= 1;
            }
            //If 4 is entered, add to Strength
            if(inputValueI == 4 && playerStats[3] < 10 && playerStats[4] > 0)
            {
                playerStats[3] += 1;
                playerStats[4] -= 1;
            }
            //If player tries to fill a full skill bar
            if((inputValueI == 1 && playerStats[0] == 10) || (inputValueI == 2 && playerStats[1] == 10) || (inputValueI == 3 && playerStats[2] == 10) || (inputValueI == 4 && playerStats[3] == 10))
            {
                cout << endl;
                cout << "ERROR, Skill bar is full" << endl;
                cout << "[Press Any Key To Continue]" << endl;
                getch();
                cout << endl;
            }
            //If player tries to fill a bar with no points
            if((inputValueI == 1 || inputValueI == 2 || inputValueI == 3 || inputValueI == 4 && playerStats[4] <= 0) && starting == false)
            {
                cout << endl;
                cout << "ERROR, no skill points detected" << endl;
                cout << endl;
            }
            //If 9 is entered, reset everything (only available at the start
            if(inputValueI == 9 && starting == true)
            {
                playerStats[0] = 0;
                playerStats[1] = 0;
                playerStats[2] = 0;
                playerStats[3] = 0;
                playerStats[4] = 10;
            }
            if(inputValueI != 1 && inputValueI != 2 && inputValueI != 3 && inputValueI != 4 && inputValueI != 9)
            {
                printInputError();
            }
        }
        if(playerStats[4] < 1)
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

    return;
}

//This section shows the user the map
void mapMenu ( string playerName, string serialCode, int auth )
{
    string inputValue;
    consolHeader( playerName, serialCode, auth);

    cout << endl;
    cout << " _________    ______    _____ " << endl;
    cout << "|  _   _  |  |  __  |  |  _  |" << endl;
    cout << "| | | | | |  | |__| |  | |_| |" << endl;
    cout << "| | | | | |  |  __  |  |  ___|" << endl;
    cout << "| | | | | |  | |  | |  | |    " << endl;
    cout << "|_| |_| |_|  |_|  |_|  |_|    " << endl;

    cout << endl;
    cout << ">___________________________________*______________________________________" << endl;
    cout << ">_____________________________________/____________________________________" << endl;
    cout << ">__~_____________________________=____\\_____________________________~______" << endl;
    cout << ">_____________________________==[O]==[+]==[]=______________________________" << endl;
    cout << ">__________[]____________________=___|+|___________________________________" << endl;
    cout << ">____________________________________|+|___________________________________" << endl;
    cout << ">______________[#][#][#]|____/\\____/(=-=)\\___/\\_____|[#][#][#]_____________" << endl;
    cout << ">______________[#][#][#]>===[()]==<[ ~0~ ]>==[()]===<[#][#][#]_____________" << endl;
    cout << ">______________[#][#][#]|__________\\(-=-)/__________|[#][#][#]_____________" << endl;
    cout << ">____________________________________[+]=-=-=-=[]__________________________" << endl;
    cout << ">__________________________________{|-^-|}____=||______________________()__" << endl;
    cout << ">________________________[-0-0-]==={|-V-|}===[00]__________________________" << endl;
    cout << ">__________________________|+|_______|+|_____\\oo/__________________________" << endl;
    cout << ">_______*__________________(0)_______|+|___________________________________" << endl;
    cout << ">___________________________________{<=>}__________________________________" << endl;
    cout << ">____________________________________(0)___________________________________" << endl;
    cout << ">___________________________________/---\\__________________________________" << endl;
    cout << ">_____________~_______________________|_____________________*______________" << endl;
    cout << ">_____________________________________V____________________________________" << endl;
    cout << ">__________________________________________________________________________" << endl;
    cout << ">- [Press A to return to |Actions|]" << endl;

    do
    {
        cin >> inputValue;
        //If input value is A, return tp actions menu, else print error
        if(inputValue == "A" || inputValue == "a" )
        {

            cout << "quitting" << endl;
            system ("CLS");
        }
        else if( inputValue != "A" && inputValue != "a" )
        {
            printInputError();
        }
    }
    while( inputValue != "A" && inputValue != "a" );
    return;
}

//This section allows the user to use items
void itemsMenu ( int playerItems[], int size,  string playerName, string serialCode, int auth, int scenario)
{
    std::string enterAnything = "";
    int inputValue = 0;
    bool gettingInput = true;

    while(gettingInput == true)
    {
        consolHeader( playerName, serialCode, auth);
        cout << endl;
//Showing what items are in the inventory
        if(playerItems[0] != 0)
        {
            cout << ">- [1] Duck Tape Role: x" << playerItems[0] << endl;
        }
        if(playerItems[1] != 0)
        {
            cout << ">- [2] Small Role Of Wire: x" << playerItems[1] << endl;
        }
        if(playerItems[2] != 0)
        {
            cout << ">- [3] Cloth: x" << playerItems[2] << endl;
        }
        if(playerItems[3] != 0)
        {
            cout << ">- [4] Adhesive: x" << playerItems[3] << endl;
        }
        if(playerItems[4] != 0)
        {
            cout << ">- [5] Space Suit x" << playerItems[4] << endl;
        }
        if(playerItems[5] != 0)
        {
            cout << ">- [6] Universal Screw Driver: x" << playerItems[5] << endl;
        }
        if(playerItems[6] != 0)
        {
            cout << ">- [7] ONI keycard: x" << playerItems[6] << endl;
        }
        if(playerItems[7] != 0)
        {
            cout << ">- [8] NAVCOM keycard: x" << playerItems[7] << endl;
        }
        if(playerItems[8] != 0)
        {
            cout << ">- [9] Note: x" << playerItems[8] << endl;
        }
        if(playerItems[9] != 0)
        {
            cout << ">- [10] Wire tweezers: x" << playerItems[9] << endl;
        }
        if(playerItems[0] == 0 && playerItems[1] == 0 && playerItems[2] == 0 && playerItems[3] == 0 && playerItems[4] == 0 && playerItems[5] == 0 && playerItems[6] == 0 && playerItems[7] == 0 && playerItems[8] == 0 && playerItems[9] == 0)
        {
            //If no items are in the inventory, print this: Your inventory is empty
            cout << endl;
            cout << ">- Your inventory is empty" << endl;
            cout << endl;
        }
        cout << ">- [A] To return to the Actions menu" << endl;
        cout << endl;

        do
        {
            cout << endl;
            cout << ">- Please enter a number to select an item to use. Please enter A to return to the action menu" << endl;
            cin >> enterAnything;
//If input is A, allow player to return to actions menu
            if(enterAnything == "a" || enterAnything == "A")
            {
                gettingInput = false;
            }
//If input is invalid, print an error message
            if( stringChecker(enterAnything) == 0 && enterAnything != "a" && enterAnything != "A")
            {
                printInputError();
            }
            //If input is valid, transfer value to a devoted integer
            if( stringChecker(enterAnything) == 1)
            {
                inputValue = ::atof(enterAnything.c_str());
            }
        }
        while( stringChecker( enterAnything ) == 0 && enterAnything != "a" && enterAnything != "A");

        //if(scenario == 1 && inputValue == 1)
        system ("CLS");
    }
    //system ("CLS");
    return;
}

//This is the normal, non consol header
void normalHeader()
{
    system("color 7");
    cout << endl;
    cout << "==================================================================================================" << endl;
    cout << "| press: [A] for action menu || [V] for vitals + experience menu || [M] for map || [I] for items |" << endl;
    cout << "|____________________________||__________________________________||_____________||_______________|" << endl;

    return;
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
        system("color C");
        cout << ">- ERROR - Connection failed" << endl;
        cout << endl;


        getch();
        system("color A");
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

        //Title screen
        cout << endl;
        cout << "    ______   _______    ______   ______    _____   _____   ___     _   _______         _______   _____   ______   ______   ______ " << endl;
        cout << "   | _____| |  _____|  |  ____| |  __  |  |  _  | |_   _| |   \\   | | |  _____|       |  _____| |  _  | |  __  | |  ____| | _____|" << endl;
        cout << "   | |____  |  |____   | |      | |__| |  | |_| |   | |   | |\\ \\  | | | |  ___        |  |____  | |_| | | |__| | | |      | |____ " << endl;
        cout << "   |  ____| |_____  |  | |      |  __  |  |  ___|   | |   | | \\ \\ | | | | |__ |       |_____  | |  ___| |  __  | | |      |  ____|" << endl;
        cout << "   | |____  _____|  |  | |____  | |  | |  | |      _| |_  | |  \\ \\| | | |___| |       _____|  | | |     | |  | | | |____  | |____ " << endl;
        cout << "   |______| |_______|  |______| |_|  |_|  |_|     |_____| |_|   \\___| |_______|       |_______| |_|     |_|  |_| |______| |______|" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

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
    system("color A");
    //standard header
    cout << ">- United Nations Space Command (UNSC) Terminal" << endl;
    cout << ">- Space Station Discovery" << endl;
    cout << endl;
    cout << ">- Serial Code [" << serialCode << "]" << endl;
    cout << endl;
    //Standard header
    if( adminPower == 1 || adminPower == 2 || adminPower == 3)
    {
        cout << ">- -UNSC User Management System-" << endl;
        cout << "================================" << endl;
        cout << "________________________________" << endl;
        cout << "UNSC TacOS  v.235" <<  endl;
        cout << "(S) 2278 FLEETCOM" << endl;
        cout << "=======================" <<  endl;
        cout << "|  User Log:" << endl;
    }
    //regular solider user header
    if( adminPower == 1)
    {
        cout << "|  >> Administrator (UNSD ID 2947-C)" << endl;
        cout << "|  >>> " << userName << ".FLEETCOM" << "_userGroup" << endl;
    }
    //specialized user header
    if( adminPower == 2)
    {
        cout << "|  >> Administrator (UNSD ID 3194 - P)" << endl;
        cout << "|  >>> " << userName << ".NAVCOM" << "_userGroup" << endl;
    }
    //ONI (Office of Naval Intelligence) user header. Overides all. Used for hacking
    if( adminPower == 3)
    {
        cout << "|  >> Administrator (UNSD ID 3194 - P)" << endl;
        cout << "|  >>> " << userName << ".ONI" << "_userGroup" << endl;
    }
    cout << endl;
}

//Used to print any input related errors
void printInputError()
{
    cout << endl;
    cout << ">- Error, please input a valid input" << endl;
    cout << ">- [Press Any Key To Continue]" <<endl;
    getch();
}
