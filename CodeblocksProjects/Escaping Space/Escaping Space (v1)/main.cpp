/*
>- Author: Max Wong
>- Date: Dec 18, 2018
>- Updated: Dec 18, 2018
>- Purpose: To write a program for a "choose your own adventure" style game.
>- Game should incorperate all the major programming requirements from the course
>-
>- [version 1]
>-
>- Credit to the Halo and Fallout franchise for inspiration and consol formatting
>-
>- [TO DO]
>- title
>- press any
>-
>- custome skills (out of 10)
>-
>- ability to move around station
>- puzzles/restrictions big)
>-
>- player stats
>- player xp + health + hunger + thirst
>- inventory (simple)
>-
>- door hecks (x2-x3)
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

using namespace std;

//Declaring all functions
string mainMenu( bool, bool); //The main menu

void setXP( int [], int, string); //Function that allows the user to customize their initial XP distrubution
void header( string, string, int); //The UNSC header  used for every UNSC terminal

int main()
{
    //Definig all of my variables
    int playerStats [5]; //Declaring the array the holds the player stats (luck, combat, intelligence, physical)

    bool menuLoad = true; //This boolean defines if the menu load-up is required
    bool askName = true; //This boolean defines if the consol should ask for a name

    string playerName;

    playerName = mainMenu( menuLoad, askName);//Initial main menu sequence
    menuLoad = false; //The computer no longer needs to conduct a load-up
    askName = false; //Tghe computer no longer needs to ask for a name

    setXP( playerStats, 5, playerName);



    return 0;
}

void setXP( int playerStats[], int size, string playerName)
{
    string serialCode = "K2G 5C9";
    int adminPower = 1;

        header( serialCode, playerName, adminPower );
}

string mainMenu( bool menuLoad, bool askName)
{

    string serialCode = "K2G 5C9"; //This string shows your serial code in the header of the consol, reflecting your loction
    string playerName = ""; //This string shows your player name in the consol header
    int adminPower = 0; //This value determines your admin power in the consol header

    //This function goes through the whole main menu sequence including the consol load up, main menu, and name selection. Name selection and Consol loadup can be disabled after the first log in
    if(menuLoad == true)
    {

        header( serialCode, playerName, adminPower );

        cout << ">- Initalizing..." << endl;
        cout << ">- [Press any key to continue]" << endl;

        cin.ignore();

        cout << ">- connecting with server [UNSC SOL] (0/100)" << endl;
        cin.ignore();
        cout << ">- connecting with server [UNSC SOL] (23/100)" << endl;
        cin.ignore();
        cout << ">- connecting with server [UNSC SOL] (47/100)" << endl;

        cin.ignore();

        cout << endl;
        cout << ">- ERROR - Connection failed" << endl;

        cin.ignore();

        cout << endl;
        cout << ">- Local sever status - Damaged - Working at 58% efficiency" << endl;
        cout << ">- [Offline - disconnected]" << endl;

        cin.ignore();

        cout << endl;
        cout << "Auto diagnostics active" << endl;
        cout << "Initializing..." << endl;

        cin.ignore();

        cout << endl;
        cout << ">- Generator - ------------ unresponsive" << endl;
        cout << ">- Backup Generator ------- offine" << endl;
        cout << ">- Solar Cell A ----------- at 23% efficiency" << endl;
        cout << ">- Solar Cell B ----------- offine" << endl;
        cout << ">- Compartenemts A~D ------ offine" << endl;
        cout << ">- Compartements E~H ------ offine" << endl;
        cout << ">- Communications array --- offine" << endl;
        cout << ">- HAB -------------------- Active at 38% eficieny" << endl;

        cin.ignore();

        cout << ">- Maintain emergency oxygen suply at 20.5%" << endl;

        cin.ignore();

        cout << endl;
        cout << ">- Rebooting ..." << endl;

        cin.ignore();

        menuLoad = false;

        system ("CLS");

        cout << endl;
        cout << endl;
        cout << endl;
        cout << ">- ---/ESCAPING SPACE/---" << endl;
        cout << endl;
        cout << "[Press Any Key To Continue]" << endl;
        cin.ignore();

        system ("CLS");

        if(askName == true)
        {
            cout << endl;
            cout << endl;
            cout << "please enter your ID" << endl;
            cout << "[**Note, you will be refered as this ID for the rest of the game]" << endl;
            cout << endl;
            cin >> playerName;

            cout << endl;
            cout << "Welcome <<" << playerName << ">>" << endl;
            cin.ignore();
            system ("CLS");
        }

    }
    return playerName;
}

//This function prints the UNSC header
void header( string serialCode, string userName, int adminPower)
{
    cout << ">- United Nations Space Command (UNSC) Terminal" << endl;
    cout << ">- Space Station Discovery" << endl;
    cout << endl;
    cout << ">- Serial Code [" << serialCode << "]" << endl;
    cout << endl;

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
    }

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
    }

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
    }
    cout << endl;
}
