/*
>- Author: Max Wong
>- Date: Dec 18, 2018
>- Updated: Jan 9, 2018
>- Purpose: To write a program for a "choose your own adventure" style game.
>- Game should incorperate all the major programming requirements from the course
>-
>- [version 2.1]
>- Credit to Vedaant Srivastava for teaching me how to effectively error trap
>- Credit to the Halo and Fallout franchise for inspiration and consol formatting
>-
>- [TO DO]
>- Complete scenarios for expeirnece/ use of items
>-
>- puzzles/restrictions (big)
>-
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
void scavanging( string, string, int, int [], int, string [], int, bool [], int, int [] ); //Menu that allows scavanging for suplies
bool hackTerminal(  string, string, int, int [], int ); //This military menu allows you to try hacking a consol. Requires the player name, location, suthority, tems array and item array size


int habRoom( string, string, int, int[], int, int[], int, bool, int, string[], bool[], bool[] ); //What the player experiences when waking up. Requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings, knowing if the player is scavanging and knowing if power is restored
int airLockRoom( string, string, int, int[], int, int[], int, bool, int, string[], bool[] ); //The airlock room requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings and knowing if the player is scavanging
int cafRoom( string, string, int, int[], int, int[], int, bool, int, string[], bool[] ); //The cafiteria room  requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings and knowing if the player is scavanging
int solarCellA( string, string, int, int[], int, int[], int, bool, int, string[], bool[], bool[] ); //The solar cell A maintenance room requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings and knowing if the player is scavanging
int medRoom( string, string, int, int[], int, int[], int, bool, int, string[], bool[] ); //The cafiteria room  requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings and knowing if the player is scavanging
int solarCellB( string, string, int, int[], int, int[], int, bool, int, string[], bool[]); //The solar cell A maintenance room requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings and knowing if the player is scavanging
int reactorRoom( string, string, int, int[], int, int[], int, bool, int, string[], bool[]); //The reactor room requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings and knowing if the player is scavanging
int commandDeck( string, string, int, int[], int, int[], int, bool, int, string[], bool[]); //Thecommand deck requires a player name, location, authority, playerStats, foundMaterials, knowing if player is starting, scenario, playerItemsStrings and knowing if the player is scavanging

bool stringChecker(string); //Function to check if an input is a float or integer

int main()
{
    //Definig all of my variables
    int playerStats [6]; //Declaring the array the holds the player stats (luck, combat, intelligence, physical, current experience points)
    int foundMaterials [10]; //Declaring the array that holds the items found by the player( tape, wire, cloth, adhesive, space suit, screw sriver, ONI keycard, NAVCOm keycard, note and wire tweezers)

    bool scavanged [10]; //A array that allows the code to know where has already been scavanged
    bool recoveredPower [1]; //An array that will be true when the power is recovered
    string playerItemsStrings [10]; //Declaring the array that holds the name of the items found by the player

    int playerChoice = 0; //This varible holds the value of what choice the player made previously (1 for return to HAB, 2 for MED, 3 for CAF, 4 for Solar cell B, 5 for Solar cell Z, 6 for Airlock, 7 for reactor, 8 for command deck, 9 for coms, 10 for supplies, 11 for escape pod)

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

    //Set power to false
    recoveredPower[0] = false;

    //(1 for return to HAB, 2 for MED, 3 for CAF, 4 for Solar cell B, 5 for Solar cell A, 6 for Airlock, 7 for reactor, 8 for command deck, 9 for coms, 10 for supplies, 11 for escape pod)
    for(int i = 0; i < 10; i++)
    {
        //Resetting al of the items
        foundMaterials [i] = 0;
        scavanged [i] = false;
    }

    bool menuLoad = true; //This boolean defines if the menu load-up is required
    bool askName = true; //This boolean defines if the consol should ask for a name
    bool starting = true; //This boolean defines if the player is currently starting the game or not - Used for some game mechinics like custom experience, only allowed when first starting out
    bool playingGame = true; //If this is false, game will quit

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

    playerChoice = habRoom( playerName, locationSerialCode, adminPower, playerStats, 6, foundMaterials, 10, starting, scenario, playerItemsStrings, scavanged, recoveredPower);

    while( playingGame == true )
    {
        //Go tp HAB
        if(playerChoice == 1)
        {
            locationSerialCode = "HAB 4K2"; //Setting location to the HAB
            playerChoice = habRoom( playerName, locationSerialCode, adminPower, playerStats, 6, foundMaterials, 10, starting, scenario, playerItemsStrings, scavanged, recoveredPower );
        }
        if(playerChoice == 2)
        {
            locationSerialCode = "MED 89S"; //Setting location to the medical bay
            playerChoice = medRoom( playerName, locationSerialCode, adminPower, playerStats, 6, foundMaterials, 10, starting, scenario, playerItemsStrings, scavanged);
        }
        if(playerChoice == 3)
        {
            locationSerialCode = "CAF 1D9"; //Setting location to the cafiteria
            playerChoice = cafRoom( playerName, locationSerialCode, adminPower, playerStats, 6, foundMaterials, 10, starting, scenario, playerItemsStrings, scavanged );
        }
        if(playerChoice == 4)
        {
            locationSerialCode = "SOL B02"; //Setting location to the solar cell B
            playerChoice = solarCellB( playerName, locationSerialCode, adminPower, playerStats, 6, foundMaterials, 10, starting, scenario, playerItemsStrings, scavanged );
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
        }
        if(playerChoice == 10)
        {
            locationSerialCode = "SPL 9J2"; //Setting location to the suplies room
        }
        //Win the game and escape in the escape pod
        if(playerChoice == 11)
        {
            locationSerialCode = "ESC POD"; //Setting location to the escape pod room
        }
    }

    return 0;
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
        cout << "//you hopes of escape slip slghtly when you realize the majority of the computers have been destroyed" << endl;
        cout << "//Even more, according to the cole protocol, in the case of capture all computers were to be wiped or destroyed to hide the location of earth" << endl;
        cout << "//Any working computers would not be of much use" << endl;
        getch();
        cout << endl;
        cout << "On either sides of the room are thin metal and glass doors labeled <supplies> and <communications>" << endl;
        cout << "between the two large windows is a heavily armored door labeled <escape>" << endl;
        cout << endl;
        cout << "//What would you like to do?" << endl;
        cout << endl;
        cout << "[1]Scavange the room for supplies" << endl;
        cout << "[2]Return to the reactor room" << endl;
        cout << "[3]Try going through the escape pod door" << endl;
        cout << "[4]go to <comunications>" << endl;
        cout << "[5]go to <supplies>" << endl;
        cin >> inputAnything;
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
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputValue != 3 && inputValue != 4 && inputValue != 5 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V")
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
            playerChoice = 8;
            usingRoom = false;
            system("CLS");
        }
        //If player chooses to go to escape pod
        if( inputValue == 3 )
        {
            hackSucess = hackTerminal( playerName, location, adminAuth, foundMaterials, 10 );
            if( hackSucess == true )
            {
                cout << endl;
                cout << "//Pressing the [open door] request button, the door slowly opens" << endl;
                cout << "//Thankfully this door is not broken and no longer senses an error" << endl;
                getch();
                playerChoice = 11;
                usingRoom = false;
            }
            if( hackSucess == false )
            {
                cout << endl;
                cout << "//Perhaps you need an ONI keycard" << endl;
                getch();
            }
            system("CLS");

        }
        //If player chooses to go to communications
        if( inputValue == 4 )
        {
            cout << endl;
            cout << "//Walking up to the door, you realize notice small metal box beside the door, like the one in the medbay" << endl;
            cout << "//It also looks jammed. Maybe some wire tweezers and a screw driver will help" << endl;
            if( foundMaterials[5] >= 1 || foundMaterials[6] >= 1 || foundMaterials[9] >= 1 )
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
            if( foundMaterials[5] == 0 || foundMaterials[6] == 0 || foundMaterials[9] == 0 )
            {
                cout << endl;
                cout << "//Perhaps an ONI keycard, a wire tweezer and a screw driver will help" << endl;
            }
            cout << "//Thankfully this door is not broken and no longer senses an error" << endl;
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
        cout << "Walking around the large generator in the midle of the room, a sealed door stands on the other side" << endl;
        cout << endl;
        cout << "//What would you like to do?" << endl;
        cout << endl;
        cout << "[1]Look around for any scavangable supplies" << endl;
        cout << "[2]Return to the HAB" << endl;
        cout << "[3]Try going through the sealed door" << endl;
        cin >> inputAnything;
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
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputValue != 3 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V")
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
int solarCellB( string playerName, string location, int adminAuth, int playerStats[], int statsSize, int foundMaterials[], int materialsSize, bool starting, int scenario, string itemNames[], bool scavanged[] )
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
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputValue != 3 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V")
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
            cout << "//Carefully examining the circuit box, you realize that someone has emptied multiple plasma rounds into the box" << endl;
            cout << "//There is alost no chance that you can attempt any sort of repair" << endl;
            cout << "//Any attempt would be a waste of time and resources, which you can not spare" << endl;
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
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputValue != 3 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V")
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
            cout << "//Once again, you have to manually crank open the door" << endl;
            cout << "//Out of habt, you close the door behind you" << endl;
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
        cout << "//The terminal indicates that it's assigned room is [Solar Cell A]" << endl;
        cout << endl;
        cout << "//To the side, you notice a small gash in the metal with exposed and sparking wires" << endl;
        cout << endl;
        cout << "//What would you like to do?" << endl;
        cout << endl;
        cout << "[1]Scavange the room for any supplies" << endl;
        cout << "[2]Return to the CAF" << endl;
        cout << "[3]Try repairing the solar cell" << endl;
        cin >> inputAnything;
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
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputValue != 3 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V")
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
                cout << "//Perhapse some tape, wire and a screw driver will help" << endl;
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
                cout << "//First you unscrew the outlet panel to give you acess" << endl;
                cout << "//Next you notice a rip in the electrical wire so you replace it" << endl;
                cout << "//To hopefully preserve the wire bonds without any soldering tools, you wrap the bond with duck tape" << endl;
                cout << "//Hopefully the bond will last long enough for you to escape this station" << endl;
                getch();
                cout << endl;
                cout << "//With one final look, you turn the power back on and the dim lights turn on" << endl;
                cout << "//For serval mineutes, no explosions or fires occur so you feel reasonably safe" << endl;
                cout << endl;
                cout << "//You have gained [x1] experience point. Go to the experience menu to upgrade you skills" << endl;
                playerStats[4] += 1;
                getch();
            }

            system("CLS");
        }
    }
    return playerChoice;
}
//Cafiteria room
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
        cout << "//Seeing that the body is in a naval officer uniform, perhaps you can find something usefull" << endl;
        cout << "//Straight in front of you, you can also see a door that leads farther forwards" << endl;
        cout << endl;
        cout << "//What would you like to do?" << endl;
        cout << endl;
        cout << "[1]Scavange the body and the room for supplies" << endl;
        cout << "[2]Return to the HAB" << endl;
        cout << "[3]Continue forwards" << endl;
        cin >> inputAnything;
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
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputValue != 3 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V")
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
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputValue != 3 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V")
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
int habRoom( string playerName, string location, int adminAuth, int playerStats[], int statsSize, int foundMaterials[], int materialsSize, bool starting, int scenario, string itemNames[], bool scavanged[], bool recoveredPower[] )
{
    std::string inputAnything = "";// Variable where you can input anything
    bool storyOver = false; //To know when to display the story
    bool usingRoom = true; //to know when to quit the room

    int randomNumber = rand() %10; //Randomely generated number between 0 and 10
    int inputValue = 0;// Once verified as an integer, yor input is stored here
    int playerChoice = 0; //This varible holds the value of what choice the player made previously (1 for return to HAB, 2 for MED, 3 for CAF, 4 for Solar cell B, 5 for Solar cell Z, 6 for Airlock, 7 for reactor, 8 for command deck, 9 for coms, 10 for supplies, 11 for escape pod)

    normalHeader();
    //Some story
    cout << "// As your cryo chamber disengages, you start to feel more and more in control of your muscles" << endl;
    cout << "// With what strength you have, you push the hatch to your chamber open" << endl;
    cout << endl;

    getch();
    cout << "//With your return to the living world, the dark empty HAB or habitation room greets you" << endl;
    cout << "//You know that at any moment, disaster could struck and you could die instantly" << endl;
    cout << "//This is, of course, the nature of space" << endl;
    cout << endl;

    while( usingRoom == true )
    {

        inputValue = 0;
        inputAnything = "";

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
        cout << endl;
        cout << "//What would you like to do?" << endl;
        cout << endl;
        cin >> inputAnything;
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
        //If the input is an integer, set it's value to inputValue
        if( stringChecker( inputAnything ) == 1)
        {
            inputValue = ::atof(inputAnything.c_str());
        }
        //If the inputed value does not match any of the menu options, print an error message
        if( inputValue != 1 && inputValue != 2 && inputValue != 3 && inputValue != 4 && inputValue != 5 && inputAnything != "a" && inputAnything != "A" && inputAnything != "i" && inputAnything != "I" && inputAnything != "m" && inputAnything != "M" && inputAnything != "v" && inputAnything != "V")
        {
            printInputError();
            system("CLS");
        }
        //If player chooses to go to Medbay
        if( inputValue == 1)
        {
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
            //If all the required elements to open the reactor door are present:
            if( foundMaterials[1] >= 1 && foundMaterials[4] >= 1 && foundMaterials[9] >= 1 && recoveredPower[0] == true )
            {
                //Consume the used materials
                foundMaterials[1] -= 1; //consume wire

                cout << endl;
                cout << "[Access Granted]" << endl;
                cout << endl;
                cout << "//With a hiss from re-pressurization, the reactor door swings open" << endl;
                cout << "//You make a note that the safety system will require a system reset to pass through again" << endl;
                cout << endl;
                playerChoice = 7;
                getch();
                system("CLS");
                usingRoom = false;
            }
            //If all the required elements to open the reactor door are not present:
            if( foundMaterials[1] < 1 || foundMaterials[4] < 1 || foundMaterials[9] < 1 || recoveredPower[0] == false )
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
    int randomQuantity = 0;
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
            }
        }
        scavanged[5] = true;
    }
    //If location (Cafiteria) is right but player has already scavanged in this location
    if( location == "CAF 1D9" && scavanged[2] == true )
    {
        cout << endl;
        cout << ">- sorry, you have already scavanged" << endl;
        cout << endl;
    }
    //If location (Cafiteria) is right but player has not scavanged in this location yet:
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
            }
        }
        scavanged[6] = true;
    }
    //If location (Command deck) is right but player has already scavanged in this location
    if( location == "CND 3C9" && scavanged[7] == true )
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
            }
        }
        scavanged[7] = true;
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
            if((( inputValueI == 1 || inputValueI == 2 || inputValueI == 3 || inputValueI == 4) && playerStats[4] >=  1) && starting == false)
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
                cout << "   113 929" << endl;
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
    cout << ">- please present propper authority and enter the password" << endl;
    getch();

    while(gettingInput == true)
    {
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
                cout << ">- ERROR, password is incorrect" << endl;
            }
        }
        else if( locationCode == "ALO 557" && playerItems[7] == 0 )
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
            cout << endl;
            cout << ">- Enter the password below [press A to quit]" << endl;
            cin >> enterAnything;
            //if player chooses to quit
            if( enterAnything == "a" || enterAnything == "A" )
            {
                gettingInput = false;
            }
            //if password is correct
            if( enterAnything == "113 929" || enterAnything == "113929" )
            {
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
            if( (enterAnything != "113 929" || enterAnything != "113929") && enterAnything != "a" && enterAnything != "A" )
            {
                cout << endl;
                cout << ">- ERROR, password is incorrect" << endl;
            }
        }
        else if( locationCode == "CND 3C9" && playerItems[6] == 0 )
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
}
//Used to print any input related errors
void printInputError()
{
    cout << endl;
    cout << ">- Error, please input a valid input" << endl;
    cout << ">- [Press Any Key To Continue]" <<endl;
    getch();
}
