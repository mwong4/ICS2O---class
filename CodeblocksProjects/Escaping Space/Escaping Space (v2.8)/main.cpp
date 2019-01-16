/*
>- Author: Max Wong
>- Date: Dec 18, 2018
>- Updated: Jan 16, 2019
>- Purpose: To write a program for a "choose your own adventure" style game.
>- Game should incorperate all the major programming requirements from the course.
>-
>- [version 2.8]
>- Credit to Vedaant Srivastava for teaching me how to effectively error trap
>- Credit to Rahgav Srinivasan for helping me play-test
>- Credit to the Halo and Fallout franchise for inspiration and consol formatting
>-
>- [TO DO]
>- Debugging
>-
>- [Table of contents - Jan 15, 2019]
>-
>- Header:
>- Libraries:
>- Structure:
>- Function prototypes:
>- main:
>- Escape pod
>- Communications room
>- Supplies room
>- Command deck
>- Reactor
>- Solar Cell B
>- Medical room
>- cafeteria
>- Airlock room
>- Habitation room
>- Scavanging
>- Action
>- Experience
>- Map
>- Items
>- Hack Terminal
>- Normal header
>- String checker
>- Main menu/Startup menu
>- Consol header
>- Print Input Error
>- Check input/In Game Menu
>- Game Over
>- Take Damage
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
void gameOver( bool[] ); //Function loaded when game is over. Gives option to restart

int actionsMenu( string, string, int ); //Menu to perform an action. Requires a player name, location and authority
void experienceMenu( int [], int, string, string, int, bool ); //Menu to use experience points. Requires the skills array, array size, player name, location and authority
void mapMenu( string, string, int ); //Menu to show player the map. Requires a player name, location and authority
void itemsMenu( int [], int, string, string, int, int ); //Menu that allows the player to see and use collected items. Requires the item list array, player name, location and authority
void scavanging( string, string, int, int [], int, string [], int, bool [], int, int [] ); //Menu that allows scavanging for suplies
bool hackTerminal(  string, string, int, int [], int ); //This military menu allows you to try hacking a consol. Requires the player name, location, suthority, tems array and item array size
int checkInput( string, string, string, int, bool, int [], int [], int, int ); //This function is used in order to check if the input will call a menu tab

int habRoom( string, string, int, int[], int, int[], int, bool, int, string[], bool[], bool[], bool[], bool[] ); //What the player experiences when waking up. Requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings, knowing if the player is scavanging, knowing if power is restored and knowing if the player wants to play again
int airLockRoom( string, string, int, int[], int, int[], int, bool, int, string[], bool[] ); //The airlock room requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings and knowing if the player is scavanging
int cafRoom( string, string, int, int[], int, int[], int, bool, int, string[], bool[] ); //The cafeteria room  requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings and knowing if the player is scavanging
int solarCellA( string, string, int, int[], int, int[], int, bool, int, string[], bool[], bool[] ); //The solar cell A maintenance room requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings and knowing if the player is scavanging
int medRoom( string, string, int, int[], int, int[], int, bool, int, string[], bool[] ); //The solar cell b maintenance room  requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings and knowing if the player is scavanging
int solarCellB( string, string, int, int[], int, int[], int, bool, int, string[], bool[], bool[]); //The solar cell A maintenance room requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings, knowing if the player is scavanging and knowing if the player wants to play again
int reactorRoom( string, string, int, int[], int, int[], int, bool, int, string[], bool[]); //The reactor room requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings and knowing if the player is scavanging
int commandDeck( string, string, int, int[], int, int[], int, bool, int, string[], bool[]); //The command deck requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings and knowing if the player is scavanging
int suppliesRoom( string, string, int, int[], int, int[], int, bool, int, string[], bool[], bool[]); //The spply room requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings, knowing if the player is scavanging and knowing if the player wants to play again
int commsRoom( string, string, int, int[], int, int[], int, bool, int, string[], bool[]); //The comms room requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings and knowing if the player is scavanging
void escapePod( string, string, int ); //The escape pod simply requires a player name, location and authority

bool stringChecker(string); //Function to check if an input is a float or integer
bool takeDamage( int[], int, string, bool[] ); //Function that makes you take damage

int main()
{
    //Definig all of my variables
    int playerStats [6]; //Declaring the array the holds the player stats (luck, combat, intelligence, physical, current experience points)
    int foundMaterials [10]; //Declaring the array that holds the items found by the player( tape, wire, cloth, adhesive, space suit, screw sriver, ONI keycard, NAVCOm keycard, note and wire tweezers)

    bool scavanged [10]; //A array that allows the code to know where has already been scavanged
    bool recoveredPower [1]; //An array that will be true when the power is recovered
    bool wokeUp [1]; //This array will let the code know when to display certain parts of the story
    bool playAgain [1]; //This boolean array determines if you want to replay the game once dying
    string playerItemsStrings [10]; //Declaring the array that holds the name of the items found by the player

    int playerChoice = 0; //This varible holds the value of what choice the player made previously (1 for return to HAB, 2 for MED, 3 for CAF, 4 for Solar cell B, 5 for Solar cell Z, 6 for Airlock, 7 for reactor, 8 for command deck, 9 for coms, 10 for supplies, 11 for escape pod)
    int adminPower = 1; //This variable determines the authority that the player currently has
    int scenario = 0; //This variable determines what scenario is currently active and thus what actions can be performed

    bool menuLoad = true; //This boolean defines if the menu load-up is required
    bool askName = true; //This boolean defines if the consol should ask for a name
    bool starting = true; //This boolean defines if the player is currently starting the game or not - Used for some game mechinics like custom experience, only allowed when first starting out
    bool playingGame = true; //If this is false, game will quit

    string playerName = ""; //This variabel holds the name of the player
    string locationSerialCode = "K2G 5C9"; //This variable holds the serial code for the location

    do
    {

        //Resetting all the values
        playerChoice = 0; //This varible holds the value of what choice the player made previously (1 for return to HAB, 2 for MED, 3 for CAF, 4 for Solar cell B, 5 for Solar cell Z, 6 for Airlock, 7 for reactor, 8 for command deck, 9 for coms, 10 for supplies, 11 for escape pod)
        adminPower = 1; //This variable determines the authority that the player currently has
        scenario = 0; //This variable determines what scenario is currently active and thus what actions can be performed

        menuLoad = true; //This boolean defines if the menu load-up is required
        askName = true; //This boolean defines if the consol should ask for a name
        starting = true; //This boolean defines if the player is currently starting the game or not - Used for some game mechinics like custom experience, only allowed when first starting out
        playingGame = true; //If this is false, game will quit

        playerName = ""; //This variabel holds the name of the player
        locationSerialCode = "K2G 5C9"; //This variable holds the serial code for the location

        //Setting all of the couted strings
        playerItemsStrings [0] = "duct tape roll";
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
        playerStats[3] = 10;
        playerStats[4] = 9;
        playerStats[5] = 10;

        //Set power and woken up to false
        recoveredPower[0] = false;
        wokeUp[0] = false;
        playAgain[0] = true;

        //(1 for return to HAB, 2 for MED, 3 for CAF, 4 for Solar cell B, 5 for Solar cell A, 6 for Airlock, 7 for reactor, 8 for command deck, 9 for coms, 10 for supplies, 11 for escape pod)
        for(int i = 0; i < 10; i++)
        {
            //Resetting al of the items
            foundMaterials [i] = 0;
            scavanged [i] = false;
        }

        playerName = mainMenu( menuLoad, askName);//Initial main menu sequence
        menuLoad = false; //The computer no longer needs to conduct a load-up
        askName = false; //Tghe computer no longer needs to ask for a name

        experienceMenu( playerStats, 5, playerName, locationSerialCode, adminPower, starting); //This function will allow the user to select what their starting skills are

        locationSerialCode = "HAB 4K2"; //Setting location to the HAB
        starting = false; //User is no longer in the starting phase

        playerChoice = habRoom( playerName, locationSerialCode, adminPower, playerStats, 6, foundMaterials, 10, starting, scenario, playerItemsStrings, scavanged, recoveredPower, wokeUp, playAgain );

        while( playingGame == true )
        {
            //Go tp HAB
            if(playerChoice == 1)
            {
                locationSerialCode = "HAB 4K2"; //Setting location to the HAB
                playerChoice = habRoom( playerName, locationSerialCode, adminPower, playerStats, 6, foundMaterials, 10, starting, scenario, playerItemsStrings, scavanged, recoveredPower, wokeUp, playAgain );
            }
            if(playerChoice == 2)
            {
                locationSerialCode = "MED 89S"; //Setting location to the medical bay
                playerChoice = medRoom( playerName, locationSerialCode, adminPower, playerStats, 6, foundMaterials, 10, starting, scenario, playerItemsStrings, scavanged);
            }
            if(playerChoice == 3)
            {
                locationSerialCode = "CAF 1D9"; //Setting location to the cafeteria
                playerChoice = cafRoom( playerName, locationSerialCode, adminPower, playerStats, 6, foundMaterials, 10, starting, scenario, playerItemsStrings, scavanged );
            }
            if(playerChoice == 4)
            {
                locationSerialCode = "SOL B02"; //Setting location to the solar cell B
                playerChoice = solarCellB( playerName, locationSerialCode, adminPower, playerStats, 6, foundMaterials, 10, starting, scenario, playerItemsStrings, scavanged, playAgain );
            }
            if(playerChoice == 5)
            {
                locationSerialCode = "SOL A01"; //Setting location to the solar cell A
                playerChoice = solarCellA( playerName, locationSerialCode, adminPower, playerStats, 6, foundMaterials, 10, starting, scenario, playerItemsStrings, scavanged, recoveredPower );
            }
            if(playerChoice == 6)
            {
                locationSerialCode = "ALO 557"; //Setting location to the airlock
                playerChoice = airLockRoom( playerName, locationSerialCode, adminPower, playerStats, 6, foundMaterials, 10, starting, scenario, playerItemsStrings, scavanged );
            }
            if(playerChoice == 7)
            {
                locationSerialCode = "RTR D8A"; //Setting location to the reactor room
                playerChoice = reactorRoom( playerName, locationSerialCode, adminPower, playerStats, 6, foundMaterials, 10, starting, scenario, playerItemsStrings, scavanged );
            }
            if(playerChoice == 8)
            {
                locationSerialCode = "CND 3C9"; //Setting location to the command deck
                playerChoice = commandDeck( playerName, locationSerialCode, adminPower, playerStats, 6, foundMaterials, 10, starting, scenario, playerItemsStrings, scavanged );
            }
            if(playerChoice == 9)
            {
                locationSerialCode = "CMS 2SL"; //Setting location to the communication room
                playerChoice = commsRoom( playerName, locationSerialCode, adminPower, playerStats, 6, foundMaterials, 10, starting, scenario, playerItemsStrings, scavanged );

            }
            if(playerChoice == 10)
            {
                locationSerialCode = "SPL 9J2"; //Setting location to the suplies room
                playerChoice = suppliesRoom( playerName, locationSerialCode, adminPower, playerStats, 6, foundMaterials, 10, starting, scenario, playerItemsStrings, scavanged, playAgain );
            }
            //Win the game and escape in the escape pod
            if(playerChoice == 11)
            {
                locationSerialCode = "ESC POD"; //Setting location to the escape pod room
                escapePod( playerName, locationSerialCode, adminPower );
                playingGame = false;
            }
            //If player ides
            if(playerChoice == 12)
            {
                playingGame = false;
            }
        }
    }
    while( playAgain[0] == true );
    //If true, player can play again

    return 0;
}
//Load the escape pod scene
void escapePod( string playerName, string location, int adminAuth )
{
    int sceneCounter = 0;

    consolHeader( playerName, location, adminAuth );
    cout << endl;
    cout << "[Press any key to initiate escape sequence]" << endl;
    getch();
    system("CLS");
    //Ending animation
    while ( sceneCounter < 5)
    {
        //Top of the frame is constant
        cout << endl;
        cout << ">___________________________________*______________________________________" << endl;
        cout << ">_____________________________________/____________________________________" << endl;
        cout << ">__~__________________________________\\_____________________________~______" << endl;
        cout << ">_______________________________[O]==[+]==[O]______________________________" << endl;
        cout << ">__________[]________________________|+|___________________________________" << endl;
        cout << ">____________________________________|+|___________________________________" << endl;
        cout << ">______________[#][#][#]|____/\\____/(=-=)\\___/\\_____|[#][#][#]_____________" << endl;
        cout << ">______________[#][#][#]>===[()]==<[ ~0~ ]>==[()]===<[#][#][#]_____________" << endl;
        cout << ">______________[#][#][#]|__________\\(-=-)/__________|[#][#][#]_____________" << endl;
        cout << ">____________________________________[+]___________________________________" << endl;
        cout << ">__________________________________{|-^-|}_____________________________()__" << endl;
        cout << ">________________________[-0-0-]==={|-V-|}===[00]__________________________" << endl;
        cout << ">__________________________|+|_______|+|_____\\oo/__________________________" << endl;
        //Frame 1
        if( sceneCounter == 0 )
        {
            cout << ">_______*___________________*________|+|___________________________________" << endl;
            cout << ">__________________________(0)______{<=>}__________________________________" << endl;
            cout << ">____________________________________(0)___________________________________" << endl;
            cout << ">___________________________________/---\\__________________________________" << endl;
            cout << ">_____________~_______________________|_____________________*______________" << endl;
            cout << ">_____________________________________V____________________________________" << endl;
            cout << ">__________________________________________________________________________" << endl;
            cout << "[Press any key to continue]" << endl;
        }
        //Frame 2
        if( sceneCounter == 1 )
        {
            cout << ">_______*___________________*________|+|___________________________________" << endl;
            cout << ">__________________________*#*______{<=>}__________________________________" << endl;
            cout << ">_________________________*$#$*______(0)___________________________________" << endl;
            cout << ">__________________________(0)______/---\\__________________________________" << endl;
            cout << ">_____________~_______________________|_____________________*______________" << endl;
            cout << ">_____________________________________V____________________________________" << endl;
            cout << ">__________________________________________________________________________" << endl;
            cout << "[Press any key to continue]" << endl;
        }
        //Frame 3
        if( sceneCounter == 2 )
        {
            cout << ">_______*___________________*________|+|___________________________________" << endl;
            cout << ">___________________________*_______{<=>}__________________________________" << endl;
            cout << ">__________________________*#*_______(0)___________________________________" << endl;
            cout << ">_________________________*$#$*_____/---\\__________________________________" << endl;
            cout << ">_____________~____________*#*________|_____________________*______________" << endl;
            cout << ">__________________________(0)________V____________________________________" << endl;
            cout << ">__________________________________________________________________________" << endl;
            cout << "[Press any key to continue]" << endl;
        }
        //Frame 4
        if( sceneCounter == 3 )
        {
            cout << ">_______*____________________________|+|___________________________________" << endl;
            cout << ">___________________________*_______{<=>}__________________________________" << endl;
            cout << ">___________________________*________(0)___________________________________" << endl;
            cout << ">___________________________*_______/---\\__________________________________" << endl;
            cout << ">_____________~____________*#*________|_____________________*______________" << endl;
            cout << ">_________________________*$#$*_______V____________________________________" << endl;
            cout << ">__________________________*#*_____________________________________________" << endl;
            cout << "[Press any key to continue]" << endl;

        }
        //Frame 5
        if( sceneCounter == 4 )
        {
            cout << ">_______*____________________________|+|___________________________________" << endl;
            cout << ">___________________________________{<=>}__________________________________" << endl;
            cout << ">____________________________________(0)___________________________________" << endl;
            cout << ">___________________________*_______/---\\__________________________________" << endl;
            cout << ">_____________~_____________*_________|_____________________*______________" << endl;
            cout << ">___________________________*_________V____________________________________" << endl;
            cout << ">__________________________*#*_____________________________________________" << endl;
            cout << "[Press any key to continue]" << endl;
        }
        getch();
        sceneCounter += 1;
        //After every frame update, the consol is wiped
        system("CLS");
    }
    cout << endl;
    cout << "Project by: Max Wong" << endl;
    cout << endl;
    cout << "Thanks to:" << endl;
    cout << "               >- Andrew Do for helping with play-testing the game" << endl;
    cout << "               >- Raghav Srinivasan for helping play-test the game" << endl;
    cout << "               >- Vedaant Srivastava for the error trapping system and play-testing" << endl;
    cout << endl;
    cout << "               >- 343 and Bungie for creating HALO" << endl;
    cout << "               >- Bethesda and Obsidian for creating Fallout" << endl;
    cout << "               >- Valve for creating Portal and Portal 2" << endl;
    cout << endl;
    cout << endl;
    cout << "                 .,-:;//;:=,                       " << endl;
    cout << "             . :H@@@MM@M#H/.,+%;,                  " << endl;
    cout << "          ,/X+ +M@@M@MM%=,-%HMMM@X/,               " << endl;
    cout << "        -+@MM; $M@@MH+-,;XMMMM@MMMM@+-             " << endl;
    cout << "       ;@M@@M- XM@X;. -+XXXXXHHH@M@M#@/.           " << endl;
    cout << "     ,%MM@@MH ,@%=             .---=-=:=,.         " << endl;
    cout << "     =@#@@@MX.,                -%HX$$%%%:;         " << endl;
    cout << "    =-./@M@M$                   .;@MMMM@MM:        " << endl;
    cout << "    X@/ -$MM/                    . +MM@@@M$        " << endl;
    cout << "   ,@M@H: :@:                    . =X#@@@@-        " << endl;
    cout << "   ,@@@MMX, .                    /H- ;@M@M=        " << endl;
    cout << "   .H@@@@M@+,                    %MM+..%#$.        " << endl;
    cout << "    /MMMM@MMH/.                  XM@MH; =;         " << endl;
    cout << "     /%+%$XHH@$=              , .H@@@@MX,          " << endl;
    cout << "      .=--------.           -%H.,@@@@@MX,          " << endl;
    cout << "      .%MM@@@HHHXX$$$%+- .:$MMX =M@@MM%.           " << endl;
    cout << "        =XMMM@MM@MM#H;,-+HMM@M+ /MMMX=             " << endl;
    cout << "          =%@M@M#@$-.=$@MM@@@M; %M%=               " << endl;
    cout << "            ,:+$+-,/H#MMMMMMM@= =,                 " << endl;
    cout << "                  =++%%%%+/:-.                     " << endl;
    cout << endl;
    cout << "    [Apature science: For those still alive]" << endl;
    getch();
    system("CLS");
    return;
}
//communications room
int commsRoom( string playerName, string location, int adminAuth, int playerStats[], int statsSize, int foundMaterials[], int materialsSize, bool starting, int scenario, string itemNames[], bool scavanged[] )
{
    bool usingRoom = true; //This bool holds true if the player is using the room. Turn false to end the loop

    std::string inputAnything = "";// Variable where you can input anything

    int inputValue = 0;// Once verified as an integer, yor input is stored here
    int playerChoice = 0; //This varible holds the value of what choice the player made previously (1 for return to HAB, 2 for MED, 3 for CAF, 4 for Solar cell B, 5 for Solar cell Z, 6 for Airlock, 7 for reactor, 8 for command deck, 9 for coms, 10 for supplies, 11 for escape pod)

    while( usingRoom == true )
    {
        //Resetting values
        inputValue = 0;
        inputAnything = "";

        normalHeader();
        //Story
        cout << endl;
        cout << "//You walk into a room with a single row of computers" << endl;
        cout << "//Once again, some of the computers are damaged, however some are still intact" << endl;
        cout << endl;
        cout << "//Checking one of the intact stations" << endl;
        cout << "//All the databases have been wiped with only a single communication line left untouched" << endl;
        cout << endl;
        getch();
        cout << "//Looking over it, you realize that this message link will be sent to the planet <Harvest>" << endl;
        cout << "//According to UNSC Emergency Priority Order 098831A-1, all communications can not be directed towards any population centers" << endl;
        cout << "//<Harvest>, however, has already been discovered by the invading Covenant and glassed so no future harm can be done" << endl;
        cout << "//Hopefully any ship in the general area will pick up you distress signal" << endl;
        cout << endl;
        getch();
        cout << "//Quickly writing a simple SOS message, you press send and watch as the loading bar finishes" << endl;
        cout << endl;
        cout << "//What would you like to do?" << endl;
        cout << endl;
        cout << "[1]look around for supplies" << endl;
        cout << "[2]Return to the command deck" << endl;
        cin >> inputAnything;
        //Call function for all menu inputs
        playerChoice = checkInput( inputAnything, playerName, location, adminAuth, starting, playerStats, foundMaterials, scenario, playerChoice );

        if( playerChoice == 12 )
        {
            usingRoom = false;
        }
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V" && inputAnything != "r" && inputAnything != "R" )
        {
            printInputError();
            system("CLS");
        }
        //If player chooses to go to scavanging
        if( inputValue == 1 )
        {
            system("CLS");
            scavanging( playerName, location, adminAuth, foundMaterials, 10, itemNames, 10, scavanged, 10, playerStats );
        }
        //If player chooses to go to HAB
        if( inputValue == 2 )
        {
            cout << endl;
            cout << "//You walk up to the glass and metal" << endl;
            cout << "//For some reason, from this side the door opens for you" << endl;
            getch();
            playerChoice = 8;
            usingRoom = false;
            system("CLS");
        }
        system("CLS");
    }
    return playerChoice;
}
//supply room
int suppliesRoom( string playerName, string location, int adminAuth, int playerStats[], int statsSize, int foundMaterials[], int materialsSize, bool starting, int scenario, string itemNames[], bool scavanged[], bool playAgain[] )
{
    bool usingRoom = true; //This bool holds true if the player is using the room. Turn false to end the loop
    bool isDead = false; //If player is dead, this is true

    std::string inputAnything = "";// Variable where you can input anything

    int inputValue = 0;// Once verified as an integer, yor input is stored here
    int playerChoice = 0; //This varible holds the value of what choice the player made previously (1 for return to HAB, 2 for MED, 3 for CAF, 4 for Solar cell B, 5 for Solar cell Z, 6 for Airlock, 7 for reactor, 8 for command deck, 9 for coms, 10 for supplies, 11 for escape pod)

    while( usingRoom == true )
    {
        //Resetting values
        inputValue = 0;
        inputAnything = "";

        normalHeader();
        //Story
        cout << endl;
        cout << "//You enter a room filled with shelves and boxes" << endl;
        cout << "//This is a great chance to scavange" << endl;
        cout << endl;
        cout << "//Around a corner, you find another body in uniform" << endl;
        cout << endl;
        cout << "//What would you like to do?" << endl;
        cout << endl;
        cout << "[1]Loot the room and body" << endl;
        cout << "[2]Return to the command deck" << endl;
        cin >> inputAnything;
        //Call function for all menu inputs
        playerChoice = checkInput( inputAnything, playerName, location, adminAuth, starting, playerStats, foundMaterials, scenario, playerChoice );

        if( playerChoice == 12 )
        {
            usingRoom = false;
        }
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V" && inputAnything != "r" && inputAnything != "R" )
        {
            printInputError();
            system("CLS");
        }
        //If player chooses to go to scavanging
        if( inputValue == 1 )
        {
            system("CLS");
            scavanging( playerName, location, adminAuth, foundMaterials, 10, itemNames, 10, scavanged, 10, playerStats );

            isDead = takeDamage( playerStats, 6, location, playAgain );
            //If player is dead
            if( isDead == true )
            {
                usingRoom = false;
                playerChoice = 12;
            }
        }
        //If player chooses to go to HAB
        if( inputValue == 2 )
        {
            cout << endl;
            cout << "//You walk up to the glass and metal door as it opens for you" << endl;
            cout << "//as you walk through, it closes behind you" << endl;
            getch();
            playerChoice = 8;
            usingRoom = false;
            system("CLS");
        }
        system("CLS");
    }
    return playerChoice;
}
//Command Deck
int commandDeck( string playerName, string location, int adminAuth, int playerStats[], int statsSize, int foundMaterials[], int materialsSize, bool starting, int scenario, string itemNames[], bool scavanged[] )
{
    bool usingRoom = true; //This bool holds true if the player is using the room. Turn false to end the loop
    bool hackSucess = false; //This boolean determines if the player can escape from the station

    std::string inputAnything = "";// Variable where you can input anything

    int inputValue = 0;// Once verified as an integer, yor input is stored here
    int playerChoice = 0; //This varible holds the value of what choice the player made previously (1 for return to HAB, 2 for MED, 3 for CAF, 4 for Solar cell B, 5 for Solar cell Z, 6 for Airlock, 7 for reactor, 8 for command deck, 9 for coms, 10 for supplies, 11 for escape pod)

    while( usingRoom == true )
    {
        //Resetting values
        inputValue = 0;
        inputAnything = "";

        normalHeader();
        //Story
        cout << endl;
        cout << "//You enter a large room filled with rows and rows of computers" << endl;
        cout << "//Sitting in the midle of the room is a big chair and at the very front of the room stands two large glass window" << endl;
        cout << endl;
        cout << "//Your hopes of escape slip slightly when you realize the majority of the computers have been destroyed" << endl;
        cout << "//Even more, according to the cole protocol, in the case of capture all computers were to be wiped or destroyed to hide the location of earth" << endl;
        cout << "//Any working computers would not be of much use" << endl;
        getch();
        cout << endl;
        cout << "//On either sides of the room are thin metal and glass doors labeled <supplies> and <communications>" << endl;
        cout << "//Between the two large windows is a heavily armored door labeled <escape>" << endl;
        cout << endl;
        cout << "//What would you like to do?" << endl;
        cout << endl;
        cout << "[1]Scavange the room for supplies" << endl;
        cout << "[2]Return to the reactor room" << endl;
        cout << "[3]Try going through the escape pod door" << endl;
        cout << "[4]go to <comunications>" << endl;
        cout << "[5]go to <supplies>" << endl;
        cin >> inputAnything;
        //Call function for all menu inputs
        playerChoice = checkInput( inputAnything, playerName, location, adminAuth, starting, playerStats, foundMaterials, scenario, playerChoice );

        if( playerChoice == 12 )
        {
            usingRoom = false;
        }
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputValue != 3 && inputValue != 4 && inputValue != 5 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V" && inputAnything != "r" && inputAnything != "R" )
        {
            printInputError();
            system("CLS");
        }
        //If player chooses to go to scavanging
        if( inputValue == 1 )
        {
            system("CLS");
            scavanging( playerName, location, adminAuth, foundMaterials, 10, itemNames, 10, scavanged, 10, playerStats );
        }
        //If player chooses to go to reactor room
        if( inputValue == 2 )
        {
            cout << endl;
            cout << "//You walk back through the large heavy blast doors that lead to the reactor room" << endl;
            cout << "//The heavy metal doors close behind you, re-instituting an airtight seal" << endl;
            getch();
            playerChoice = 7;
            usingRoom = false;
            system("CLS");
        }
        //If player chooses to go to escape pod
        if( inputValue == 3 )
        {
            system("CLS");
            hackSucess = hackTerminal( playerName, location, adminAuth, foundMaterials, 10 );
            if( hackSucess == false )
            {
                cout << endl;
                cout << "//Perhaps you need an ONI keycard" << endl;
                cout << "//Also, maybe someone on the station left a note with the password (hint: check your items list and use the note)" << endl;
                getch();
                system("CLS");
            }
            if( hackSucess == true )
            {
                system("CLS");
                playerChoice = 11;
                usingRoom = false;
            }
        }
        //If player chooses to go to communications
        if( inputValue == 4 )
        {
            cout << endl;
            cout << "//Walking up to the door, you realize notice small metal box beside the door, like the one in the medbay" << endl;
            cout << "//It also looks jammed. Maybe some wire tweezers and a screw driver will help" << endl;
            if( foundMaterials[5] == 0 || foundMaterials[6] == 0 || foundMaterials[9] == 0 )
            {
                cout << endl;
                cout << "//Perhaps an ONI keycard, a wire tweezer and a screw driver will help" << endl;
            }
            if( foundMaterials[5] >= 1 && foundMaterials[6] >= 1 && foundMaterials[9] >= 1 )
            {
                cout << endl;
                cout << "//Opening the box with your screw driver you find a broken switch linked to a keycard sensor" << endl;
                cout << "//When using the keycard, the switch only opens slightly" << endl;
                cout << "//Thankfully this door has a a tiny manual overide switch but it still requires a keycard to activate" << endl;
                getch();
                cout << endl;
                cout << "//Simultaneously, you scan your ONI keycard and twist the switch with your wire tweezers at the same time" << endl;
                cout << "//With a satisfying thud, the door slides open" << endl;
                cout << endl;
                playerChoice = 9;
                usingRoom = false;
            }
            getch();
            system("CLS");
        }
        //If player chooses to go to supplies
        if( inputValue == 5 )
        {
            cout << endl;
            cout << "//Walking up to the door, an automatic sensor detects you" << endl;
            cout << "//The door slides open without a problem" << endl;
            getch();
            playerChoice = 10;
            usingRoom = false;
            system("CLS");
        }
        system("CLS");
    }
    return playerChoice;
}
//Reactor room
int reactorRoom( string playerName, string location, int adminAuth, int playerStats[], int statsSize, int foundMaterials[], int materialsSize, bool starting, int scenario, string itemNames[], bool scavanged[] )
{
    bool usingRoom = true; //This bool holds true if the player is using the room. Turn false to end the loop

    std::string inputAnything = "";// Variable where you can input anything

    int inputValue = 0;// Once verified as an integer, yor input is stored here
    int playerChoice = 0; //This varible holds the value of what choice the player made previously (1 for return to HAB, 2 for MED, 3 for CAF, 4 for Solar cell B, 5 for Solar cell Z, 6 for Airlock, 7 for reactor, 8 for command deck, 9 for coms, 10 for supplies, 11 for escape pod)

    while( usingRoom == true )
    {
        //Resetting values
        inputValue = 0;
        inputAnything = "";

        normalHeader();
        //Story
        cout << endl;
        cout << "//Entering the large room, you immediately spot a big hole in the side of the room" << endl;
        cout << "//Somehow, the automatic safety system did not activate" << endl;
        cout << endl;
        cout << "//You hit a large red button on the side and immidietly a strong looking foam emerges and covers the hole" << endl;
        cout << "//Hopefully the seal will hold" << endl;
        getch();
        cout << endl;
        cout << "//Walking around the large generator in the midle of the room, a sealed door stands on the other side" << endl;
        cout << endl;
        cout << "//What would you like to do?" << endl;
        cout << endl;
        cout << "[1]Look around for any scavangable supplies" << endl;
        cout << "[2]Return to the HAB" << endl;
        cout << "[3]Try going through the sealed door" << endl;
        cin >> inputAnything;
        //Call function for all menu inputs
        playerChoice = checkInput( inputAnything, playerName, location, adminAuth, starting, playerStats, foundMaterials, scenario, playerChoice );

        if( playerChoice == 12 )
        {
            usingRoom = false;
        }
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputValue != 3 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V" && inputAnything != "r" && inputAnything != "R" )
        {
            printInputError();
            system("CLS");
        }
        //If player chooses to go to scavanging
        if( inputValue == 1 )
        {
            system("CLS");
            scavanging( playerName, location, adminAuth, foundMaterials, 10, itemNames, 10, scavanged, 10, playerStats );
        }
        //If player chooses to go to HAB
        if( inputValue == 2 )
        {
            cout << endl;
            cout << "//You walk back through the large heavy doors into the HAB" << endl;
            cout << "//closing behind you, the door resets the airtight seal" << endl;
            getch();
            playerChoice = 1;
            usingRoom = false;
            system("CLS");
        }
        //If player chooses to go to HAB
        if( inputValue == 3 )
        {
            cout << endl;
            cout << "//Pressing the [open door] request button, the door slowly opens" << endl;
            cout << "//Thankfully this door is not broken and no longer senses an error" << endl;
            getch();
            playerChoice = 8;
            usingRoom = false;
            system("CLS");
        }
        system("CLS");
    }
    return playerChoice;
}
//SOlar cell b maintenance room
int solarCellB( string playerName, string location, int adminAuth, int playerStats[], int statsSize, int foundMaterials[], int materialsSize, bool starting, int scenario, string itemNames[], bool scavanged[], bool playAgain[] )
{
    bool usingRoom = true; //This bool holds true if the player is using the room. Turn false to end the loop
    bool isDead = false; //If player is dead, this is true

    std::string inputAnything = "";// Variable where you can input anything

    int inputValue = 0;// Once verified as an integer, yor input is stored here
    int playerChoice = 0; //This varible holds the value of what choice the player made previously (1 for return to HAB, 2 for MED, 3 for CAF, 4 for Solar cell B, 5 for Solar cell Z, 6 for Airlock, 7 for reactor, 8 for command deck, 9 for coms, 10 for supplies, 11 for escape pod)

    while( usingRoom == true )
    {
        //Resetting values
        inputValue = 0;
        inputAnything = "";

        normalHeader();
        //Story
        cout << endl;
        cout << "//You enter a small cramped room, almost identical to the other maintenance room" << endl;
        cout << "//once again a heavily damaged " << endl;
        cout << endl;
        cout << "//To your left is the circuit box and infront of you stands a terminal" << endl;
        cout << "//The terminal is designated to [Solar Cell B]" << endl;
        cout << endl;
        cout << "//What would you like to do?" << endl;
        cout << endl;
        cout << "[1]Look around for any scavangable supplies" << endl;
        cout << "[2]Return to the Med Bay" << endl;
        cout << "[3]Try repairing the solar cell" << endl;
        cin >> inputAnything;
        //Call function for all menu inputs
        playerChoice = checkInput( inputAnything, playerName, location, adminAuth, starting, playerStats, foundMaterials, scenario, playerChoice );

        if( playerChoice == 12 )
        {
            usingRoom = false;
        }
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputValue != 3 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V" && inputAnything != "r" && inputAnything != "R" )
        {
            printInputError();
            system("CLS");
        }
        //If player chooses to go to scavanging
        if( inputValue == 1)
        {
            system("CLS");
            scavanging( playerName, location, adminAuth, foundMaterials, 10, itemNames, 10, scavanged, 10, playerStats );
        }
        //If player chooses to go to HAB
        if( inputValue == 2)
        {
            cout << endl;
            cout << "//You turn a big metal handle and the exit door slowly opens" << endl;
            cout << "//Once you are on the other side, you crank the door shut behind yourself" << endl;
            getch();
            playerChoice = 2;
            usingRoom = false;
            system("CLS");
        }
        if( inputValue == 3)
        {
            cout << "//Carefully examining the circuit box, you realize that someone has emptied multiple plasma pistol rounds into the box" << endl;
            cout << "//There is almost no chance that you can attempt any sort of repair" << endl;
            cout << "//Any attempt would be a waste of time and resources, which you can not spare" << endl;
            getch();
            isDead = takeDamage( playerStats, 6, location, playAgain );
            //If player is dead
            if( isDead == true )
            {
                usingRoom = false;
                playerChoice = 12;
            }
            getch();
            system("CLS");
        }
        system("CLS");
    }
    return playerChoice;
}
//Medical room
int medRoom( string playerName, string location, int adminAuth, int playerStats[], int statsSize, int foundMaterials[], int materialsSize, bool starting, int scenario, string itemNames[], bool scavanged[] )
{
    bool usingRoom = true; //This bool holds true if the player is using the room. Turn false to end the loop

    std::string inputAnything = "";// Variable where you can input anything

    int inputValue = 0;// Once verified as an integer, yor input is stored here
    int playerChoice = 0; //This varible holds the value of what choice the player made previously (1 for return to HAB, 2 for MED, 3 for CAF, 4 for Solar cell B, 5 for Solar cell Z, 6 for Airlock, 7 for reactor, 8 for command deck, 9 for coms, 10 for supplies, 11 for escape pod)

    while( usingRoom == true )
    {
        //Resetting values
        inputValue = 0;
        inputAnything = "";

        normalHeader();
        //Story
        cout << endl;
        cout << "//You enter the medical room and you take a quick glance around" << endl;
        cout << "//This room is filled with many cabinets, definitely a good chance to scavange some supplies" << endl;
        cout << endl;
        cout << "//In front of you, you see another door that looks very similar to the solar cell A maintenance room" << endl;
        cout << endl;
        cout << "//What would you like to do?" << endl;
        cout << endl;
        cout << "[1]Look around for supplies" << endl;
        cout << "[2]Return to the HAB" << endl;
        cout << "[3]Continue forwards" << endl;
        cin >> inputAnything;
        //Call function for all menu inputs
        playerChoice = checkInput( inputAnything, playerName, location, adminAuth, starting, playerStats, foundMaterials, scenario, playerChoice );

        if( playerChoice == 12 )
        {
            usingRoom = false;
        }
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputValue != 3 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V" && inputAnything != "r" && inputAnything != "R" )
        {
            printInputError();
            system("CLS");
        }
        //If player chooses to go to scavanging
        if( inputValue == 1)
        {
            system("CLS");
            scavanging( playerName, location, adminAuth, foundMaterials, 10, itemNames, 10, scavanged, 10, playerStats );
        }
        //If player chooses to go to HAB
        if( inputValue == 2)
        {
            cout << endl;
            cout << "//You turn around to leave the room" << endl;
            cout << "//Pressing your NavCOM keycard on a metal box, the doors automatically swing open for you" << endl;
            getch();
            playerChoice = 1;
            usingRoom = false;
            system("CLS");
        }
        //If player chooses to go to Solar Cell B
        if( inputValue == 3)
        {
            cout << endl;
            cout << "//Once again, you have to manually crank open the door" << endl;
            cout << "//Out of habit, you close the door behind you" << endl;
            getch();
            playerChoice = 4;
            usingRoom = false;
            system("CLS");
        }
        system("CLS");
    }
    return playerChoice;
}
//Solar Cell A Maintenance Room
int solarCellA( string playerName, string location, int adminAuth, int playerStats[], int statsSize, int foundMaterials[], int materialsSize, bool starting, int scenario, string itemNames[], bool scavanged[], bool recoveredPower[] )
{
    bool usingRoom = true; //This bool holds true if the player is using the room. Turn false to end the loop

    std::string inputAnything = "";// Variable where you can input anything

    int inputValue = 0;// Once verified as an integer, yor input is stored here
    int playerChoice = 0; //This varible holds the value of what choice the player made previously (1 for return to HAB, 2 for MED, 3 for CAF, 4 for Solar cell B, 5 for Solar cell Z, 6 for Airlock, 7 for reactor, 8 for command deck, 9 for coms, 10 for supplies, 11 for escape pod)

    while( usingRoom == true )
    {
        //Resetting values
        inputValue = 0;
        inputAnything = "";

        normalHeader();
        //Story
        cout << endl;
        cout << "//You enter a small room with a single maintenance terminal" << endl;
        cout << "//Most likely this room is for maintenance" << endl;
        cout << "//The terminal indicates that its assigned room is [Solar Cell A]" << endl;
        cout << endl;
//If player has not fixed the solar cell yet
        if( recoveredPower[0] == false )
        {
            cout << "//To the side, you notice a small gash in the metal with exposed and sparking wires" << endl;
            cout << endl;
        }
        cout << "//What would you like to do?" << endl;
        cout << endl;
        cout << "[1]Scavange the room for any supplies" << endl;
        cout << "[2]Return to the CAF" << endl;
        cout << "[3]Try repairing the solar cell" << endl;
        cin >> inputAnything;
        //Call function for all menu inputs
        playerChoice = checkInput( inputAnything, playerName, location, adminAuth, starting, playerStats, foundMaterials, scenario, playerChoice );

        if( playerChoice == 12 )
        {
            usingRoom = false;
        }
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputValue != 3 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V" && inputAnything != "r" && inputAnything != "R" )
        {
            printInputError();
            system("CLS");
        }
        //If player chooses to go to scavanging
        if( inputValue == 1)
        {
            system("CLS");
            scavanging( playerName, location, adminAuth, foundMaterials, 10, itemNames, 10, scavanged, 10, playerStats );
        }
        //If player chooses to go to HAB
        if( inputValue == 2)
        {
            cout << endl;
            cout << "//You turn around to leave the room, manually opening the door" << endl;
            cout << "//Once you are on the other side, you close the door manually behind you" << endl;
            getch();
            playerChoice = 3;
            usingRoom = false;
            system("CLS");
        }
        //If player chooses to go to Solar Cell A2
        if( inputValue == 3)
        {
            if( recoveredPower == false )
            {
                cout << endl;
                cout << "//First you turn off the local power in the room so as not to kill yourself" << endl;
                cout << "//Next you oberserve that someone has violently pulled the power connection plugs out" << endl;
                cout << "//The outlet is damaged so any permanant attemps to restore power from this cell will require these plugs to be permanantly pluged in" << endl;
                getch();
            }
            //if materials are present
            if( recoveredPower[0] == false && (foundMaterials[5] < 1 || foundMaterials[1] < 1 || foundMaterials[0] < 1 ))
            {
                cout << endl;
                cout << "//Perhaps some tape, wire and a screw driver will help" << endl;
                getch();
            }
            if( recoveredPower[0] == true )
            {
                cout << endl;
                cout << "//The solar cell power conection has already been repaired" << endl;
                getch();
            }
            //If materials are present
            if( foundMaterials[5] >= 1 && foundMaterials[1] >= 1 && foundMaterials[0] >= 1 && recoveredPower[0] == false)
            {
                //Consuming the materials (tape and wire)
                foundMaterials[0] -= 1;
                foundMaterials[1] -= 1;
                recoveredPower[0] = true;

                cout << endl;
                cout << "//First you unscrew the outlet panel to give you access" << endl;
                cout << "//Next you notice a rip in the electrical wire so you replace it" << endl;
                cout << "//To hopefully preserve the wire bonds without any soldering tools, you wrap the bond with duct tape" << endl;
                cout << "//Hopefully the bond will last long enough for you to escape this station" << endl;
                getch();
                cout << endl;
                cout << "//With one final look, you turn the power back on and the dim lights turn on" << endl;
                cout << "//For serval mineutes, no explosions or fires occur so you feel reasonably safe" << endl;
                cout << endl;
                cout << "//You have gained [x1] experience point. Go to the experience menu to upgrade you skills" << endl;
                playerStats[3] += 1;
                getch();
            }

            system("CLS");
        }
    }
    return playerChoice;
}
//Cafeteria room
int cafRoom( string playerName, string location, int adminAuth, int playerStats[], int statsSize, int foundMaterials[], int materialsSize, bool starting, int scenario, string itemNames[], bool scavanged[] )
{
    bool usingRoom = true; //This bool holds true if the player is using the room. Turn false to end the loop

    std::string inputAnything = "";// Variable where you can input anything

    int inputValue = 0;// Once verified as an integer, yor input is stored here
    int playerChoice = 0; //This varible holds the value of what choice the player made previously (1 for return to HAB, 2 for MED, 3 for CAF, 4 for Solar cell B, 5 for Solar cell Z, 6 for Airlock, 7 for reactor, 8 for command deck, 9 for coms, 10 for supplies, 11 for escape pod)

    while( usingRoom == true )
    {
        //Resetting values
        inputValue = 0;
        inputAnything = "";

        normalHeader();
        //Story
        cout << endl;
        cout << "//When you enter the room, a terrible smell greets you" << endl;
        cout << "//Most likely the smell is originating from the body in front of you" << endl;
        cout << "//Seeing that the body is in a naval officer uniform, perhaps you can find something useful" << endl;
        cout << "//Straight in front of you, you can also see a door that leads farther forwards" << endl;
        cout << endl;
        cout << "//What would you like to do?" << endl;
        cout << endl;
        cout << "[1]Scavange the body and the room for supplies" << endl;
        cout << "[2]Return to the HAB" << endl;
        cout << "[3]Continue forwards" << endl;
        cin >> inputAnything;
        //Call function for all menu inputs
        playerChoice = checkInput( inputAnything, playerName, location, adminAuth, starting, playerStats, foundMaterials, scenario, playerChoice );

        if( playerChoice == 12 )
        {
            usingRoom = false;
        }
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputValue != 3 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V" && inputAnything != "r" && inputAnything != "R" )
        {
            printInputError();
            system("CLS");
        }
        //If player chooses to go to scavanging
        if( inputValue == 1)
        {
            system("CLS");
            scavanging( playerName, location, adminAuth, foundMaterials, 10, itemNames, 10, scavanged, 10, playerStats );
        }
        //If player chooses to go to HAB
        if( inputValue == 2)
        {
            cout << endl;
            cout << "//You turn around to leave the room, pushing the double doors out of the way" << endl;
            cout << "//As you continue, you hear the heavy doors close behind you" << endl;
            getch();
            playerChoice = 1;
            usingRoom = false;
            system("CLS");
        }
        //If player chooses to go to Solar Cell A
        if( inputValue == 3)
        {
            cout << endl;
            cout << "//Opening the manual airlock, you step through" << endl;
            cout << "//Once you are on the other side, you manually close the door behind yourself" << endl;
            getch();
            playerChoice = 5;
            usingRoom = false;
            system("CLS");
        }
    }
    return playerChoice;
}
//Air lock room
int airLockRoom( string playerName, string location, int adminAuth, int playerStats[], int statsSize, int foundMaterials[], int materialsSize, bool starting, int scenario, string itemNames[], bool scavanged[] )
{
    bool usingRoom = true; //This bool holds true if the player is using the room. Turn false to end the loop
    bool hackSuccess = false; //If this boolean is true, the terminal hack is sucessfull

    std::string inputAnything = "";// Variable where you can input anything

    int inputValue = 0;// Once verified as an integer, yor input is stored here
    int playerChoice = 0; //This varible holds the value of what choice the player made previously (1 for return to HAB, 2 for MED, 3 for CAF, 4 for Solar cell B, 5 for Solar cell Z, 6 for Airlock, 7 for reactor, 8 for command deck, 9 for coms, 10 for supplies, 11 for escape pod)

    while( usingRoom == true )
    {
        //Resetting values
        inputValue = 0;
        inputAnything = "";

        normalHeader();
        //Story
        cout << endl;
        cout << "//What greets you is a plain room with benches and sealed shelves on the side" << endl;
        cout << "//Each shelve is sealed with scraps of materials that no doubt were used for excursions outside the station in the past" << endl;
        cout << "//Now they are a great chance for you to find potentialy usefull supplies" << endl;
        cout << endl;
        cout << "//To the side stands a terminal" << endl;
        cout << endl;
        cout << "//What would you like to do?" << endl;
        cout << endl;
        cout << "[1]Scavange the shelves" << endl;
        cout << "[2]Return to the HAB" << endl;
        cout << "[3]Examine the terminal" << endl;
        cin >> inputAnything;
        //Call function for all menu inputs
        playerChoice = checkInput( inputAnything, playerName, location, adminAuth, starting, playerStats, foundMaterials, scenario, playerChoice );

        if( playerChoice == 12 )
        {
            usingRoom = false;
        }
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputValue != 3 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V" && inputAnything != "r" && inputAnything != "R" )
        {
            printInputError();
            system("CLS");
        }
        //If player chooses to go to scavanging
        if( inputValue == 1 )
        {
            system("CLS");
            scavanging( playerName, location, adminAuth, foundMaterials, 10, itemNames, 10, scavanged, 10, playerStats );
        }
        //If player chooses to go to HAB
        if( inputValue == 2 )
        {
            cout << endl;
            cout << "//You turn around and decide to return back to the HAB" << endl;
            cout << "//Pressing the request open button, you wait" << endl;
            cout << "//One door opens, you walk through" << endl;
            cout << "//The first door closes as the second opens and you walk through" << endl;
            getch();
            playerChoice = 1;
            usingRoom = false;
            system("CLS");
        }
        if( inputValue == 3 )
        {
            system("CLS");
            hackSuccess = hackTerminal(  playerName, location, adminAuth, foundMaterials, 10 );

        }
    }
    return playerChoice;
}

//First part of the game when you wake up
int habRoom( string playerName, string location, int adminAuth, int playerStats[], int statsSize, int foundMaterials[], int materialsSize, bool starting, int scenario, string itemNames[], bool scavanged[], bool recoveredPower[], bool wokeUp[], bool playAgain[] )
{
    std::string inputAnything = "";// Variable where you can input anything
    bool storyOver = false; //To know when to display the story
    bool usingRoom = true; //to know when to quit the room
    bool isDead = false; //If player is dead, this is true

    int randomNumber = rand() %10; //Randomely generated number between 0 and 10
    int inputValue = 0;// Once verified as an integer, yor input is stored here
    int playerChoice = 0; //This varible holds the value of what choice the player made previously (1 for return to HAB, 2 for MED, 3 for CAF, 4 for Solar cell B, 5 for Solar cell Z, 6 for Airlock, 7 for reactor, 8 for command deck, 9 for coms, 10 for supplies, 11 for escape pod)

    normalHeader();

    if( wokeUp[0] == false)
    {
        //Some story
        cout << "// As your cryo chamber disengages, you start to feel more and more in control of your muscles" << endl;
        cout << "// With what strength you have, you push the hatch to your chamber open" << endl;
        cout << endl;

        getch();
        cout << "//With your return to the living world, the dark empty HAB or habitation room greets you" << endl;
        cout << "//You know that at any moment, disaster could strike and you could die instantly" << endl;
        cout << "//This is, of course, the nature of space" << endl;
        getch();
        wokeUp[0] = true;
    }

    while( usingRoom == true )
    {

        inputValue = 0;
        inputAnything = "";

        if(storyOver == true)
        {
            normalHeader();
        }
        //Show the options
        cout << endl;
        cout << "[1]To your left, you spot the entrance to the medical bay" << endl;
        cout << "[2]In front of you stands the central airlocks" << endl;
        cout << "[3]To your right is another door for the cafeteria" << endl;
        cout << "[4]Behind you lies a solid door labeled [REACTOR]" << endl;
        cout << "[5]All aroud you lies scraps and shelves that you could possibly scavange something from" << endl;
        storyOver = true;
        //Ask what used would like to input
        getch;
        cout << endl;
        cout << "//What would you like to do?" << endl;
        cout << endl;
        cin >> inputAnything;
        //Call function for all menu inputs
        playerChoice = checkInput( inputAnything, playerName, location, adminAuth, starting, playerStats, foundMaterials, scenario, playerChoice );

        if( playerChoice == 12 )
        {
            usingRoom = false;
        }
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputValue != 3 && inputValue != 4 && inputValue != 5 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V" && inputAnything != "r" && inputAnything != "R" )
        {
            printInputError();
            system("CLS");
        }
        //If player chooses to go to Medbay
        if( inputValue == 1)
        {
            //If NAVcom keycard is not present
            if( foundMaterials[7] < 1)
            {
                cout << endl;
                cout << "[Access Denied]" << endl;
                cout << endl;
                cout << "//The computer requires proper authority to open" << endl;
                cout << endl;
                getch();
                system("CLS");
                usingRoom = true;
            }
            //If NAVcom keycard is present
            if( foundMaterials[7] >= 1)
            {
                cout << endl;
                cout << "[Access Granted]" << endl;
                cout << endl;
                cout << "//The door to the Medbay opens up" << endl;
                cout << endl;
                playerChoice = 2;
                getch();
                system("CLS");
                usingRoom = false;
            }
        }
        //If player chooses to go to Airlock
        if( inputValue == 2)
        {
            cout << endl;
            cout << "//You press the open request button and the big heavy door slides open" << endl;
            cout << endl;
            playerChoice = 6;
            getch();
            cout <<"//once the first layer of the airlock closes, the second door opens" << endl;
            getch();
            system("CLS");
            usingRoom = false;
        }
        //If player chooses to go to Caf
        if( inputValue == 3)
        {
            cout << endl;
            cout << "//Pushing the double doors out of your way, you enter the CAF" << endl;
            cout << endl;
            playerChoice = 3;
            getch();
            system("CLS");
            usingRoom = false;
        }
        //If player chooses to try going to reactor
        if( inputValue == 4)
        {
            //If all the required elements to open the reactor door are not present:
            if( foundMaterials[1] < 1 || foundMaterials[9] < 1 || recoveredPower[0] == false )
            {

                cout << endl;
                cout << "[Access Denied]" << endl;
                cout << endl;
                cout << "//You realize that behind this sealed door may hold a DANGER. You must find a space suit" << endl;
                cout << "//You also require some wire and a wire tweezer to reset the computer system" << endl;
                cout << "//Finally, you also notice that the door requires power to function" << endl;
                cout << endl;
                getch();
                system("CLS");
            }
            //If all the required elements to open the reactor door are present:
            if( foundMaterials[1] >= 1 && foundMaterials[9] >= 1 && recoveredPower[0] == true )
            {
                //Consume the used materials
                foundMaterials[1] -= 1; //consume wire

                cout << endl;
                cout << "[Access Granted]" << endl;
                cout << endl;
                cout << "//With a hiss from re-pressurization, the reactor door swings open" << endl;
                cout << "//You make a note that the safety system will require a system reset to pass through again" << endl;
                cout << endl;
                getch();
                //If player has no space suit
                if( foundMaterials[4] == 0 )
                {
                    isDead = takeDamage( playerStats, 6, location, playAgain );
                    //If player is dead
                    if( isDead = false)
                    {
                        playerChoice = 7;
                    }
                    //If player is alive
                    if( isDead = true )
                    {
                        playerChoice = 12;
                    }
                }
                if( foundMaterials[4] != 0 )
                {
                    playerChoice = 7;
                }
                system("CLS");
                usingRoom = false;
            }
        }
        if( inputValue == 5)
        {
            system("CLS");
            scavanging( playerName, location, adminAuth, foundMaterials, 10, itemNames, 10, scavanged, 10, playerStats );
        }
    }

    return playerChoice;
}

void scavanging  (string playerName, string location, int authority, int foundItems[], int itemsSize, string itemNames[], int namesSize, bool scavanged[], int scavangedSize, int playerStats[] )
{
    int randomQuantity = 0;//This is a randomely generated number that determines if the player found anything
    bool foundSomething = false; //This boolean will be turned true if anything is found.
    //This calls in the header
    consolHeader( location, playerName, authority );
    //(1 for return to HAB, 2 for MED, 3 for CAF, 4 for Solar cell B, 5 for Solar cell A, 6 for Airlock, 7 for reactor, 8 for command deck, 9 for coms, 10 for supplies, 11 for escape pod)

    //If location (HAB) is right but player has already scavanged in this location
    if( location == "HAB 4K2" && scavanged[0] == true )
    {
        cout << endl;
        cout << ">- sorry, you have already scavanged" << endl;
        cout << endl;
    }
    //If location (HAB) is right but player has not scavanged in this location yet:
    if( location == "HAB 4K2" && scavanged[0] == false )
    {
        for(int i = 0; i <= 10; i++)
        {
            //Generate a random nummber
            randomQuantity = rand() %2 + round(playerStats[0]/3);
            //cout and assign the values to the array + display result to user
            if((i == 2 || i == 0 || i == 1) && randomQuantity != 0)
            {
                foundItems [i] += randomQuantity;
                cout << "you found " << itemNames [i] << " x" << randomQuantity << endl;
                cout << endl;
                foundSomething = true;
            }
        }
        scavanged[0] = true;
    }
    //If location (Airlock) is right but player has already scavanged in this location
    if( location == "ALO 557" && scavanged[5] == true )
    {
        cout << endl;
        cout << ">- sorry, you have already scavanged" << endl;
        cout << endl;
    }
    //If location (Airlock) is right but player has not scavanged in this location yet:
    if( location == "ALO 557" && scavanged[5] == false )
    {
        for(int i = 0; i <= 10; i++)
        {
            //Generate a random nummber
            randomQuantity = rand() %2 + round(playerStats[0]/3);
            //if item is space suit (), force minimum generation number to be 1
            if((i == 4))
            {
                randomQuantity = 1;
            }
            //cout and assign the values to the array + display result to user
            if(( i == 0 || i == 1 || i == 4 || i == 5 ) && randomQuantity != 0)
            {
                foundItems [i] += randomQuantity;
                cout << "you found " << itemNames [i] << " x" << randomQuantity << endl;
                cout << endl;
                foundSomething = true;
            }
        }
        scavanged[5] = true;
    }
    //If location (Cafeteria) is right but player has already scavanged in this location
    if( location == "CAF 1D9" && scavanged[2] == true )
    {
        cout << endl;
        cout << ">- sorry, you have already scavanged" << endl;
        cout << endl;
    }
    //If location (Cafeteria) is right but player has not scavanged in this location yet:
    if( location == "CAF 1D9" && scavanged[2] == false )
    {
        for(int i = 0; i <= 10; i++)
        {
            //Generate a random nummber
            randomQuantity = rand() %2 + round(playerStats[0]/3);
            //if item is NavCOM keycard or note, force minimum generation number to be 1
            if(( i == 7 || i == 8 ))
            {
                randomQuantity = 1;
            }
            //cout and assign the values to the array + display result to user
            if(( i == 0 || i == 1 || i == 2 || i == 7 || i == 8 ) && randomQuantity != 0)
            {
                foundItems [i] += randomQuantity;
                cout << "you found " << itemNames [i] << " x" << randomQuantity << endl;
                cout << endl;
                foundSomething = true;
            }
        }
        scavanged[2] = true;
    }
    //If location (solar cell A) is right but player has already scavanged in this location
    if( location == "SOL A01" && scavanged[4] == true )
    {
        cout << endl;
        cout << ">- sorry, you have already scavanged" << endl;
        cout << endl;
    }
    //If location (Solar Cell A) is right but player has not scavanged in this location yet:
    if( location == "SOL A01" && scavanged[4] == false )
    {
        for(int i = 0; i <= 10; i++)
        {
            //Generate a random nummber
            randomQuantity = rand() %2 + round(playerStats[0]/3);
            //if item is universal screw driver, force minimum generation number to be 1
            if(( i == 5 ))
            {
                randomQuantity = 1;
            }
            //cout and assign the values to the array + display result to user
            if(( i == 3 || i == 5 || i == 1 ) && randomQuantity != 0)
            {
                foundItems [i] += randomQuantity;
                cout << "you found " << itemNames [i] << " x" << randomQuantity << endl;
                cout << endl;
                foundSomething = true;
            }
        }
        scavanged[4] = true;
    }
    //If location (Medbay) is right but player has already scavanged in this location
    if( location == "MED 89S" && scavanged[1] == true )
    {
        cout << endl;
        cout << ">- sorry, you have already scavanged" << endl;
        cout << endl;
    }
    //If location (Medbay) is right but player has not scavanged in this location yet:
    if( location == "MED 89S" && scavanged[1] == false )
    {
        for(int i = 0; i <= 10; i++)
        {
            //Generate a random nummber
            randomQuantity = rand() %3 + round(playerStats[0]/3);
            //if item is wire tweezers, force minimum generation number to be 1
            if(( i == 9 ))
            {
                randomQuantity = 1;
            }
            //cout and assign the values to the array + display result to user
            if(( i == 9 || i == 3 || i == 2 || i == 0 ) && randomQuantity != 0)
            {
                foundItems [i] += randomQuantity;
                cout << "you found " << itemNames [i] << " x" << randomQuantity << endl;
                cout << endl;
                foundSomething = true;
            }
        }
        scavanged[1] = true;
    }
    //If location (solar cell B) is right but player has already scavanged in this location
    if( location == "SOL B02" && scavanged[3] == true )
    {
        cout << endl;
        cout << ">- sorry, you have already scavanged" << endl;
        cout << endl;
    }
    //If location (solar cell B) is right but player has not scavanged in this location yet:
    if( location == "SOL B02" && scavanged[3] == false )
    {
        for(int i = 0; i <= 10; i++)
        {
            //Generate a random nummber
            randomQuantity = rand() %2 + round(playerStats[0]/3);
            //cout and assign the values to the array + display result to user
            if(( i == 1 || i == 2 ) && randomQuantity != 0)
            {
                foundItems [i] += randomQuantity;
                cout << "you found " << itemNames [i] << " x" << randomQuantity << endl;
                cout << endl;
                foundSomething = true;
            }
        }
        scavanged[3] = true;
    }
    //If location (Reactor) is right but player has already scavanged in this location
    if( location == "RTR D8A" && scavanged[6] == true )
    {
        cout << endl;
        cout << ">- sorry, you have already scavanged" << endl;
        cout << endl;
    }
    //If location (Reactor) is right but player has not scavanged in this location yet:
    if( location == "RTR D8A" && scavanged[6] == false )
    {
        for(int i = 0; i <= 10; i++)
        {
            //Generate a random nummber
            randomQuantity = rand() %2 + round(playerStats[0]/3);
            //cout and assign the values to the array + display result to user
            if(( i == 0 || i == 1 || i == 3 || i == 4 || i == 5 || i == 9 ) && randomQuantity != 0)
            {
                foundItems [i] += randomQuantity;
                cout << "you found " << itemNames [i] << " x" << randomQuantity << endl;
                cout << endl;
                foundSomething = true;
            }
        }
        scavanged[6] = true;
    }
    //If location (Command deck) is right but player has already scavanged in this location
    if( location == "CMS 2SL" && scavanged[8] == true )
    {
        cout << endl;
        cout << ">- sorry, you have already scavanged" << endl;
        cout << endl;
    }
    //If location (Command deck) is right but player has not scavanged in this location yet:
    if( location == "CND 3C9" && scavanged[7] == false )
    {
        for(int i = 0; i <= 10; i++)
        {
            //Generate a random nummber
            randomQuantity = rand() %2 + round(playerStats[0]/3);
            //cout and assign the values to the array + display result to user
            if(( i == 7 || i == 1) && randomQuantity != 0)
            {
                foundItems [i] += randomQuantity;
                cout << "you found " << itemNames [i] << " x" << randomQuantity << endl;
                cout << endl;
                foundSomething = true;
            }
        }
        scavanged[7] = true;
    }
    //If location (Medbay) is right but player has already scavanged in this location
    if( location == "SPL 9J2" && scavanged[9] == true )
    {
        cout << endl;
        cout << ">- sorry, you have already scavanged" << endl;
        cout << endl;
    }
    //If location (Medbay) is right but player has not scavanged in this location yet:
    if( location == "SPL 9J2" && scavanged[9] == false )
    {
        for(int i = 0; i <= 10; i++)
        {
            //Generate a random nummber
            randomQuantity = rand() %3 + round(playerStats[0]/3);
            //if item is wire tweezers, force minimum generation number to be 1
            if(( i == 6 ))
            {
                randomQuantity = 1;
            }
            //cout and assign the values to the array + display result to user
            if(( i == 0 || i == 1 || i == 2 || i == 3 || i == 5 || i == 6 ) && randomQuantity != 0)
            {
                foundItems [i] += randomQuantity;
                cout << "you found " << itemNames [i] << " x" << randomQuantity << endl;
                cout << endl;
                foundSomething = true;
            }
        }
        scavanged[9] = true;
    }
    //If location (Command deck) is right but player has already scavanged in this location
    if( location == "CMS 2SL" && scavanged[8] == true )
    {
        cout << endl;
        cout << ">- sorry, you have already scavanged" << endl;
        cout << endl;
    }
    //If location (Command deck) is right but player has not scavanged in this location yet:
    if( location == "CMS 2SL" && scavanged[8] == false )
    {
        for(int i = 0; i <= 10; i++)
        {
            //Generate a random nummber
            randomQuantity = rand() %2 + round(playerStats[0]/3);
            //cout and assign the values to the array + display result to user
            if(( i == 6 || i == 1) && randomQuantity != 0)
            {
                foundItems [i] += randomQuantity;
                cout << "you found " << itemNames [i] << " x" << randomQuantity << endl;
                cout << endl;
                foundSomething = true;
            }
        }
        scavanged[8] = true;
    }
    //If player found nothing, tell player
    if( foundSomething == false )
    {
        cout << endl;
        cout << ">- You found nothing" << endl;
    }
    getch();
    //If randomely generated number is over or equal to five (chance increased by upgrading intelligence) and player has found something, give the player x1 xp point
    if( ((rand() %6) + (round(playerStats[2]/2)) >= 5) && foundSomething == true )
    {
        cout << endl;
        cout << ">- You have gained [x1] experience point. Go to the experience menu to upgrade you skills" << endl;
        playerStats[3] += 1;
    }
    cout << endl;
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
        for( int i = 0; i < (playerStats[4]); i++ )
        {
            cout << "#";
        }
        for( int i = 0; i < (playerStats[5] - playerStats[4]); i++ )
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

        cout << ">- RESILIENCE:   ";
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

        if(playerStats[3] > 0)
        {
            //Showing the player the options
            cout << endl;
            cout << ">- Please select a number to assign an xp point" << endl;
            cout << endl;
            cout << ">- [1] Luck (Increase loot)" << endl;
            cout << ">- [2] Combat (Increase health)" << endl;
            cout << ">- [3] Intelligency (Increase XP)" << endl;

            if(starting == true)
            {
                cout << ">- [9] To reset previous selections (reset xp)" << endl;
            }
            cout << endl;
            cout << ">- You have " << playerStats[3] << " points left" << endl;

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
            if(inputValueI == 1 && playerStats[0] < 10 && playerStats[3] > 0)
            {
                playerStats[0] += 1;
                playerStats[3] -= 1;
            }
            //If 2 is entered, add to combat
            if(inputValueI == 2 && playerStats[1] < 10 && playerStats[3] > 0)
            {
                playerStats[1] += 1;
                playerStats[3] -= 1;
                //Increasing the health of the player
                playerStats[4] += 1;
                playerStats[5] += 1;
            }
            //If 3 is entered, add to Intelligence
            if(inputValueI == 3 && playerStats[2] < 10 && playerStats[3] > 0)
            {
                playerStats[2] += 1;
                playerStats[3] -= 1;
            }
            //If player tries to fill a full skill bar
            if(( inputValueI == 1 && playerStats[0] == 10) || (inputValueI == 2 && playerStats[1] == 10) || (inputValueI == 3 && playerStats[2] == 10) )
            {
                cout << endl;
                cout << "ERROR, Skill bar is full" << endl;
                cout << "[Press Any Key To Continue]" << endl;
                getch();
                cout << endl;
            }
            //If player tries to fill a bar with no points
            if((( inputValueI == 1 || inputValueI == 2 || inputValueI == 3 ) && playerStats[3] >=  1) && starting == false)
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
                playerStats[3] = 10;
            }
            if(inputValueI != 1 && inputValueI != 2 && inputValueI != 3 && inputValueI != 9)
            {
                printInputError();
            }
        }
        if(playerStats[3] < 1)
        {
            do
            {
                //Telling the player that they do not have any xp points left
                cout << endl;
                cout << ">- You have 0 points remaining" << endl;

                //confirming stats + error trapping for invalid inputs
                cout << endl;
                cout << ">- do you cofirm these stats? /y/ for yes, /n/ for no" << endl;
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
    cout << endl;
    cout << endl;
    cout << ">__________________________________________________________________________" << endl;
    cout << ">__________________________________________________________________________" << endl;
    cout << ">__________________________________________________________________________" << endl;
    cout << ">__________________________________________________________________________" << endl;
    cout << ">_________________";

    //With all the sections below, if the player is in that location, show that they are at that location. Otherwise, show regular name
    if( serialCode == "SOL B02" )
    {
        cout << "_________[<V>]";
    }
    if( serialCode != "SOL B02" )
    {
        cout << "[SOLAR CELL B]";
    }
    cout << "__";
    if( serialCode == "ALO 557" )
    {
        cout << "__[<V>]__";
    }
    if( serialCode != "ALO 557" )
    {
        cout << "[AIRLOCK]";
    }
    cout << "__";
    if( serialCode == "SOL A01" )
    {
        cout << "[<V>]_________";
    }
    if( serialCode != "SOL A01" )
    {
        cout << "[SOLAR CELL A]";
    }
    cout << "________________" << endl;
    cout << ">________________________|____________|____________|_______________________" << endl;
    cout << ">________________________|____________|____________|_______________________" << endl;
    cout << ">______________________";
    if( serialCode == "MED 89S" )
    {
        cout << "[<V>]";
    }
    if( serialCode != "MED 89S" )
    {
        cout << "[MED]";
    }
    cout << "--------";
    if( serialCode == "HAB 4K2" )
    {
        cout << "[<V>]";
    }
    if( serialCode != "HAB 4K2" )
    {
        cout << "[HAB]";
    }
    cout << "--------";
    if( serialCode == "CAF 1D9" )
    {
        cout << "[<V>]";
    }
    if( serialCode != "CAF 1D9" )
    {
        cout << "[CAF]";
    }
    cout << "_____________________" << endl;
    cout << ">_____________________________________|____________________________________" << endl;
    cout << ">_____________________________________|____________________________________" << endl;
    cout << ">_________________________________";
    if( serialCode == "RTR D8A" )
    {
        cout << "_[<VV>]_";
    }
    if( serialCode != "RTR D8A" )
    {
        cout << "[REACTOR]";
    }
    cout << "________________________________" << endl;
    cout << ">_____________________________________|____________________________________" << endl;
    cout << ">_____________________________________|____________________________________" << endl;
    cout << ">______________________";
    if( serialCode == "CMS 2SL" )
    {
        cout << "[<VV>]";
    }
    if( serialCode != "CMS 2SL" )
    {
        cout << "[COMS]";
    }
    cout << "-----";
    if( serialCode == "CND 3C9" )
    {
        cout << "__[<V>]__";
    }
    if( serialCode != "CND 3C9" )
    {
        cout << "[COMMAND]";
    }
    cout << "-----";
    if( serialCode == "SPL 9J2" )
    {
        cout << "[<VV>]____";
    }
    if( serialCode != "SPL 9J2" )
    {
        cout << "[SUPPLIES]";
    }
    cout << "_________________" << endl;
    cout << ">_____________________________________|____________________________________" << endl;
    cout << ">_____________________________________|____________________________________" << endl;
    cout << ">__________________________________";
    if( serialCode == "ESC POD" )
    {
        cout << "_[<VV>]_";
    }
    if( serialCode != "ESC POD" )
    {
        cout << "[ESCAPE]";
    }
    cout << "________________________________" << endl;
    cout << ">__________________________________________________________________________" << endl;
    cout << ">__________________________________________________________________________" << endl;
    cout << ">__________________________________________________________________________" << endl;
    cout << endl;
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
            cout << ">- [1] Duct Tape Roll: x" << playerItems[0] << endl;
        }
        if(playerItems[1] != 0)
        {
            cout << ">- [2] Small Roll Of Wire: x" << playerItems[1] << endl;
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
            inputValue = 0;

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
            //If player selects anything and player has that item
            if( inputValue != 9 && playerItems[inputValue] != 0 )
            {
                cout << endl;
                cout << ">- You can not currently use this item" << endl;
                getch();
            }
            //If player selects anything and player does not have that item
            if( inputValue != 9 && playerItems[inputValue] == 0 )
            {
                cout << endl;
                cout << ">- You do not have this item" << endl;
                getch();
            }
            //If player selects note player has a note
            if( inputValue == 9 && playerItems[8] == 1)
            {
                cout << endl;
                cout << "--------------------------------------------------" << endl;
                cout << endl;
                cout << "   I don't have much time left. The station" << endl;
                cout << "    is being overrun and I think it's the Covenant" << endl;
                cout << endl;
                cout << "   Anyways, the code to the escape pods is" << endl;
                cout << endl;
                cout << "   113929, no spaces" << endl;
                cout << endl;
                cout << "   I really hope someone reads this" << endl;
                cout << endl;
                cout << "-------------------------------------------------" << endl;
                cout << endl;
                getch();
            }
        }
        while( stringChecker( enterAnything ) == 0 && enterAnything != "a" && enterAnything != "A");

        //if(scenario == 1 && inputValue == 1)
        system ("CLS");
    }
    //system ("CLS");
    return;
}
//Gives you a chance to hack a terminal
bool hackTerminal(  string playerName, string locationCode, int authority, int playerItems[], int size )
{
    string enterAnything = ""; //Variable where you can enter anything
    bool gettingInput = true; //Boolean that when false, ends the function. A quit feature
    bool hackSucess = false; //If true, the player has sucessfully hacked the terminal

    consolHeader( playerName, locationCode, authority);
    cout << ">- please present proper authority and enter the password" << endl;
    getch();

    while(gettingInput == true)
    {
        enterAnything = "";
        //if location is correct and player has a navcom identity
        if( locationCode == "ALO 557" && playerItems[7] >= 1 )
        {
            cout << endl;
            cout << ">- Enter the password below [press A to quit]" << endl;
            cin >> enterAnything;
            //if player chooses to quit
            if( enterAnything == "a" || enterAnything == "A" )
            {
                gettingInput = false;
            }
            //if password is correct
            if( enterAnything == "030205" )
            {
                cout << endl;
                cout << ">> [Verification complete]" << endl;
                cout << "-------------------------------------------------" << endl;
                cout << endl;
                cout << ">- Identified user as [" << playerName << "].ONI" << endl;
                cout << ">- NavCOM Identification ----- detected" << endl;
                cout << ">- ONI Identification -------- undetected" << endl;
                cout << endl;
                cout << ">- Providing ONI Identification now" << endl;
                cout << endl;
                getch();
                playerItems[6] += 1;
                cout << ">- you found ONI KeyCard  x1" << endl;
                hackSucess = true;
                cout << endl;
                getch();
                gettingInput = false;
            }
            //If password is incorrect
            if( enterAnything != "030205" && enterAnything != "a" && enterAnything != "A" )
            {
                cout << endl;
                cout << ">- ERROR, NavCOM password is incorrect" << endl;
            }
        }

        if( (locationCode == "ALO 557" && playerItems[7] == 0) )
        {
            cout << endl;
            cout << ">- [ERROR] Keycard not detected" << endl;
            cout << ">- Please have the right authority" << endl;
            cout << ">- [Press any key to continue]" << endl;
            getch();
            gettingInput = false;
        }
        //if location is correct and player has a navcom identity
        if( locationCode == "CND 3C9" && playerItems[6] >= 1 )
        {
            enterAnything = "";

            cout << endl;
            cout << ">- Enter the password below [press A to quit]" << endl;
            cin >> enterAnything;
            //if player chooses to quit
            if( enterAnything == "a" || enterAnything == "A" )
            {
                gettingInput = false;
            }
            //if password is correct
            if( enterAnything == "113929" )
            {
                cout << endl;
                cout << ">> [Verification complete]" << endl;
                cout << "-------------------------------------------------" << endl;
                cout << endl;
                cout << ">- Identified user as [" << playerName << "].ONI" << endl;
                cout << ">- NavCOM Identification ----- unknown" << endl;
                cout << ">- ONI Identification -------- detected" << endl;
                cout << endl;
                cout << ">- Initiating escape protocol now" << endl;
                cout << endl;
                getch();
                hackSucess = true;
                gettingInput = false;
            }
            //If password is incorrect
            if( enterAnything != "113929" && enterAnything != "a" && enterAnything != "A" )
            {
                cout << endl;
                cout << ">- ERROR, ONI password is incorrect" << endl;
            }
        }
        if( locationCode == "CND 3C9" && playerItems[6] == 0 )
        {
            cout << endl;
            cout << ">- [ERROR] ONI authority not detected" << endl;
            cout << ">- Please have the right authority" << endl;
            cout << ">- [Press any key to continue]" << endl;
            getch();
            gettingInput = false;
        }
    }
    system("CLS");
    return hackSucess;
}

//This is the normal, non consol header
void normalHeader()
{
    system("color 7");
    cout << endl;
    cout << "===================================================================================================================" << endl;
    cout << "| press: [A] for action menu || [V] for vitals + experience menu || [M] for map || [I] for items | [R] to restart |" << endl;
    cout << "|____________________________||__________________________________||_____________||_______________|________________|" << endl;

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
        cout << ">- [Please use full screen]" << endl;
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
        cout << ">- [Please use full screen]" << endl;
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
        cout << "|  >> Administrator (UNSC ID 2947-C)" << endl;
        cout << "|  >>> " << userName << ".FLEETCOM" << "_userGroup" << endl;
    }
    //specialized user header
    if( adminPower == 2)
    {
        cout << "|  >> Administrator (UNSC ID 3194 - P)" << endl;
        cout << "|  >>> " << userName << ".NAVCOM" << "_userGroup" << endl;
    }
    //ONI (Office of Naval Intelligence) user header. Overides all. Used for hacking
    if( adminPower == 3)
    {
        cout << "|  >> Administrator (UNSC ID 3194 - P)" << endl;
        cout << "|  >>> " << userName << ".ONI" << "_userGroup" << endl;
    }
    cout << endl;

    return;
}
//Used to print any input related errors
void printInputError()
{
    cout << endl;
    cout << ">- Error, please input a valid input" << endl;
    cout << ">- [Press Any Key To Continue]" <<endl;
    getch();

    return;
}
//
int checkInput( string inputAnything, string playerName, string location, int adminAuth, bool starting, int playerStats[], int foundMaterials[], int scenario, int playerChoice )
{
    playerChoice = 0;

    //If A is inputed, load action menu
    if( inputAnything == "A" || inputAnything == "a")
    {
        cout << endl;
        cout << "// You are currenty in the action menu" << endl;
        cout <<"// [Press An Key To Continue]" << endl;
        cout << endl;
        getch();
        system ("CLS");
    }
    //If V is inputed, load vitals + experience menu
    if( inputAnything == "V" || inputAnything == "v")
    {
        system ("CLS");
        experienceMenu( playerStats, 5, location, playerName, adminAuth, starting);
    }
    //If M is inputed, load map menu
    if( inputAnything == "M" || inputAnything == "m")
    {
        system ("CLS");
        mapMenu( playerName, location, adminAuth);
    }
    //If I is inputed, load items menu
    if( inputAnything == "I" || inputAnything == "i")
    {
        system ("CLS");
        itemsMenu ( foundMaterials, 10, playerName, location, adminAuth, scenario);
    }
        //If I is inputed, load items menu
    if( inputAnything == "R" || inputAnything == "r")
    {
        system ("CLS");
        playerChoice = 12;
    }
    return playerChoice;
}
//This function is called when you die
void gameOver( bool playAgain[] )
{
    system("CLS"); //Wipe consol

    bool gettingInput = true; //This boolean will keep the while loop active. If it becomes false, an input has been found
    string inputAnything = ""; //This is a string/input tat will be screened to know if the player wants to play again

    //This loop is active only when getting an input
    while( gettingInput == true )
    {
        cout << "    _______   ______   _________   ______      ______  __        __  ______   _____   " << endl;
        cout << "   |  _____| |  __  | |  _   _  | | _____|    |  __  | \\ \\      / / | _____| |  _  |  " << endl;
        cout << "   | |  ___  | |__| | | | | | | | | |____     | |  | |  \\ \\    / /  | |____  | |_| |  " << endl;
        cout << "   | | |__ | |  __  | | | |_| | | |  ____|    | |  | |   \\ \\  / /   |  ____| |    _|  " << endl;
        cout << "   | |___| | | |  | | | |     | | | |____     | |__| |    \\ \\/ /    | |____  | |\\ \\ "  << endl;
        cout << "   |_______| |_|  |_| |_|     |_| |______|    |______|     \\__/     |______| |_| \\_\\" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "                                           You died" << endl;
        cout << endl;
        cout << ">-                                [Enter /Y/ to play again]" << endl;

        //Get an input
        cin >> inputAnything;
        if( inputAnything == "y" || inputAnything == "Y" || inputAnything == "yes" )
        {
            playAgain[0] = true;
            gettingInput = false;
        }
        if( inputAnything == "n" || inputAnything == "N" || inputAnything == "no" )
        {
            playAgain[0] = false;
            gettingInput = false;
        }
        if( inputAnything != "n" && inputAnything != "N" && inputAnything != "no" && inputAnything != "y" && inputAnything != "Y" && inputAnything != "yes" )
        {
            printInputError();
        }
        system("CLS");
    }
    return;
}
//This function is called when you take damage. Note, traps can be re-triggered
bool takeDamage( int playerStats[], int size, string location, bool playAgain[] )
{
    int randomNumber = rand() %5; //This random number determines your damage
    bool isDead = false;

    if( location == "SOL B02" )
    {
        cout << endl;
        cout << "//As you finish fidling with the box, all of a sudden, the box starts sparking, than explodes" << endl;
        cout << endl;
        cout << "//You take " << randomNumber << " damage" << endl;
        playerStats[4] -= randomNumber;
        cout << endl;
        cout << "//You have " << playerStats[4] << " health left" << endl;
        cout << endl;
        getch();
        //If your health is below 0
        if( playerStats[4] <= 0 )
        {
            gameOver( playAgain );
            isDead = true;
        }
        //If your health si above 0
        if( playerStats[4] > 0 )
        {
            cout << "//you survived the small explosion. Thankfully the room did not de-pressurize" << endl;
        }
    }
    if( location == "HAB 4K2" )
    {
        cout << endl;
        cout << "//When you open the door, the whole room instantly de-pressurizes" << endl;
        cout << "//You slowly suffocate" << endl;
        cout << endl;
        cout << "//You take 9999999 damage" << endl;
        playerStats[4] -= 99;
        cout << endl;
        getch();
        //You die instantly
        gameOver( playAgain );
        isDead = true;
    }
    if( location == "SPL 9J2" )
    {
        cout << endl;
        cout << "//All of a sudden, you trip a mine" << endl;
        cout << "//Across the room, a plasma cannon fires and you are hit" << endl;
        cout << endl;
        cout << "//You take " << randomNumber*2 << " damage" << endl;
        playerStats[4] -= randomNumber*2;
        cout << endl;
        cout << "//You have " << playerStats[4] << " health left" << endl;
        cout << endl;
        getch();
        //If your health is under 0
        if( playerStats[4] <= 0 )
        {
            gameOver( playAgain );
            isDead = true;
        }
        //If your health si above 0
        if( playerStats[4] > 0 )
        {
            cout << "//you survived the trap" << endl;
        }
    }
    cout << endl;
    cout << "//[Press any key to continue]" << endl;
    getch();
    return isDead;
}
