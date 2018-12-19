/*
>- Author: Max Wong
>- Date: Dec 18, 2018
>- Updated: Dec 18, 2018
>- Purpose: To write a program for a "choose your own adventure" style game.
>- Game should incorperate all the major programming requirements from the course
>-
>- [version 2]
>-
>- Credit to the Halo and Fallout franchise for inspiration and consol formatting
>-
>- [TO DO]
>- custom skills (out of 10) ~
>-Error trapping custom skills
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
void printInputError(); //Function used to print an input related error message

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
    //Resetting al of the stats
    playerStats[0] = 0;
    playerStats[1] = 0;
    playerStats[2] = 0;
    playerStats[3] = 0;

    string serialCode = "K2G 5C9"; //This value determines the serial code on the UNSC header
    string confirmInput = "";

    int adminPower = 1; //This value determines the authority on the UNSC header
    int currentXPPoints = 10; //This is the variable that holds the amount of points the player has to spend

    int inputValue = 0;

    bool customXP = true; //This bool helps to determine when the computer shoudl stop asking the player to pick skills

    do
    {

        //This calls in the header
        header( serialCode, playerName, adminPower );


        //System diagnostics + player icon
        cout << endl;
        cout << "           _" << endl;
        cout << "         _( )_" << endl;
        cout << "       ||[===]||" << endl;
        cout << "       || [=] ||" << endl;
        cout << "         {---}" << endl;
        cout << "         || ||" << endl;
        cout << "         || ||" << endl;

        cout << endl;
        cout << ">- UNSC - " << playerName << endl;
        cout << endl;
        cout << ">- HEALTH: #########-" << endl;
        cout << ">- HUNGER: ####------" << endl;
        cout << ">- THIRST: #####-----" << endl;
        cout << endl;
        cout << endl;

        cout << ">- LUCK:         ----------" << playerStats[0] << endl;
        cout << ">- COMBAT:       ----------" << playerStats[1] << endl;
        cout << ">- INTELLIGENCE: ----------" << playerStats[2] << endl;
        cout << ">- STRENGTH:     ----------" << playerStats[3] << endl;


        if(currentXPPoints > 0)
        {
            cout << ">- Please select a number to assign an xp point" << endl;
            cout << endl;
            cout << ">- [1] Luck" << endl;
            cout << ">- [2] Combat" << endl;
            cout << ">- [3] Intelligency" << endl;
            cout << ">- [4] Strength" << endl;
            cout << ">- [9] To reset previous selections (reset xp)" << endl;
            cout << endl;
            cout << ">- You have " << currentXPPoints << " Left" << endl;
            cout << endl;
            cin >> inputValue;

            if(inputValue == 1)
            {
                playerStats[0] += 1;
                currentXPPoints -= 1;
            }
            if(inputValue == 2)
            {
                playerStats[1] += 1;
                currentXPPoints -= 1;
            }
            if(inputValue == 3)
            {
                playerStats[2] += 1;
                currentXPPoints -= 1;
            }
            if(inputValue == 4)
            {
                playerStats[3] += 1;
                currentXPPoints -= 1;
            }
            if(inputValue == 9)
            {
                playerStats[0] = 0;
                playerStats[1] = 0;
                playerStats[2] = 0;
                playerStats[3] = 0;
                currentXPPoints = 10;
            }
            else if(inputValue != 1 && inputValue != 2 && inputValue != 3 && inputValue != 4 && inputValue != 9)
            {
                printInputError();
            }
        }
        if(currentXPPoints <= 0)
        {
            do
            {
                cout << endl;
                cout << "do you cofirm these stats?" << endl;
                cin >> confirmInput;

                if(confirmInput == "y" || confirmInput == "Y" || confirmInput == "yes" || confirmInput == "Yes")
                {
                    customXP = false;
                }

                if(confirmInput == "n" || confirmInput == "N" || confirmInput == "no" || confirmInput == "No")
                {
                    customXP = true;
                }

                else
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
        cout << ">- [Press Any Key To Continue]" << endl;
        cin.ignore();

        system ("CLS");

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

void printInputError()
{
    cout << endl;
    cout << ">- Error, please input a valid input" << endl;
    cout << endl;
}
