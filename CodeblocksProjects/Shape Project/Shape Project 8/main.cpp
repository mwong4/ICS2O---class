#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>

/*
>- Author: Max Wong
>- Date: Nov 22, 2018
>- Updated: Dec 3, 2018
>- Purpose: to experiment with for loops in order to create ASCII art
>-
>- [version 8]
>-
>- Credit to Vedaant Srivastava for helping me error trap, checking my work and introducing me to "round"
*/

using namespace std;

//int triangleLimit = 1; //This variable was used in the for loop that created the first triangle;
//int triangleLimitTwo = 4; //This variable was used in the for loop that created the second triangle;
//int triangleLimitThree = 4; //This variable was used in the for loop that created the third triangle;

int triangleLimitFour = 3; //This variable was used in the for loop that created the fourth triangle;
int diamondLimit; //This variable was used in the for loop that created the first half of the diamond. Ised to know the spacing of the first half of the diamond
int diamondLimitTwo = 3; //This variable was used in the for loop that created the second half of the diamond. Used to know how many #   to display per line for second half of diamond
int treeTopLimit; //This variable was used to create the top of the tree. Holds the value for spacing
int treeTopLimitTwo; //This variable was used to create the trunk of the tree. Holds the max width of the tree top
int treeTrunk; //This variable is used to create the width of the tree trunk

int shapeSelected = 0; //This variable is assigned to receive  the selected shape. Allows the program to know which shape to display/make

int currentlyLooping = 1; //This variable is used in the while loop that allows the while code to function. If turned off, the program will end
int restartLoop = 1; //This variable is used in a contained loop that checks to see if the player wishes to restart. If false, the program has confirmed a validinput to restart/not restart
int validNumber = 1; //Used in the loop that confirms a integer. If false, a valid shape selection has been confirmed

std::string shapeSizeS; //String that initially holds the shape size (! only the height for the rectangle) before integer varification
std::string rectWidthS; //String that initially holds the rectangle width before integer verification

int shapeSizeI; //Integer that will hold the shape size once integer input is confirmed
int rectWidthI; //Integer that will hold the rectangle width once integer input is confirmed

string restartProgram; //A string to check if the player wants to re-play the program

std::string currentShape; //getting the first input as a string that defines what shape the user wants

//Integer checker for shape selection
bool stringChecker( string currentShape )
{
    for( string::size_type i = 0; i < currentShape.size(); ++i )
    {
        if ( ( currentShape[i] != '0' )&&( currentShape[i] != '1' )&&( currentShape[i] != '2' )&&( currentShape[i] != '3' )&&( currentShape[i] != '4' )&&( currentShape[i] != '5' )&&( currentShape[i] != '6' )&&( currentShape[i] != '7' )&&( currentShape[i] != '8' )&&( currentShape[i] != '9' ) )
        {
            return false;
        }
    }
    return true;
}

//Integer checker for shape size (! only the height of the rectangle)
bool stringCheckerTwo( string shapeSizeS )
{
    for( string::size_type i = 0; i < shapeSizeS.size(); ++i )
    {
        if ( ( shapeSizeS[i] != '0' )&&( shapeSizeS[i] != '1' )&&( shapeSizeS[i] != '2' )&&( shapeSizeS[i] != '3' )&&( shapeSizeS[i] != '4' )&&( shapeSizeS[i] != '5' )&&( shapeSizeS[i] != '6' )&&( shapeSizeS[i] != '7' )&&( shapeSizeS[i] != '8' )&&( shapeSizeS[i] != '9' ) )
        {
            return false;
        }
    }
    return true;
}

//Integer checker for shape size (! only the height of the rectangle)
bool stringCheckerThree( string rectWidthS)
{
    for( string::size_type i = 0; i < rectWidthS.size(); ++i )
    {
        if ( ( rectWidthS[i] != '0' )&&( rectWidthS[i] != '1' )&&( rectWidthS[i] != '2' )&&( rectWidthS[i] != '3' )&&( rectWidthS[i] != '4' )&&( rectWidthS[i] != '5' )&&( rectWidthS[i] != '6' )&&( rectWidthS[i] != '7' )&&( rectWidthS[i] != '8' )&&( rectWidthS[i] != '9' ) )
        {
            return false;
        }
    }
    return true;
}


int main()
{
    //Program Information
    cout << ">- Author: Max Wong" << endl;
    cout << ">- Date: Nov 22, 2018" << endl;
    cout << ">- Updated: Dec 3, 2018" << endl;
    cout << ">- Purpose: to experiment with for loops in order to create ASCII art" << endl;
    cout << ">-" << endl;
    cout << ">- [version 8]" << endl;
    cout << ">-" << endl;
    cout << ">- Credit to Vedaant Srivastava for helping me error trap, checking my work and introducing me to round" << endl;

    while(0 < currentlyLooping)
    {
        //Resetting all the values
        validNumber = 1;
        restartLoop = 1;

        while (validNumber == 1)
        {
            //Spacing
            cout << "" << endl;
            cout << "-------------------------------------------------------------------------------" << endl;
            cout << "" << endl;

            //Ask what shape the player would like
            cout << "" << endl;
            cout << ">- please enter a number to select a shape" << endl;
            cout << ">- " << endl;
            cout << ">- 1. Rectangle" << endl;
            cout << ">- 2-6. Triangle" << endl;
            cout << ">- 7. Diamond" << endl;
            cout << ">- 8. Tree" << endl;
            cout << "" << endl;
            cin >> currentShape;

            //Error trapping: If the input is not a int
            if( stringChecker ( currentShape ) == 0 )
            {
                cout << "" << endl;
                cout << "ERROR, invalid input" << endl;
                cout << "" << endl;
            }

            //Error trapping: If the input is an int
            if( stringChecker ( currentShape ) == 1 )
            {
                validNumber = 0;
                shapeSelected = ::atof(currentShape.c_str());
            }
        }

        //spacing
        cout << "" << endl;
        cout << "==========================================================================" << endl;
        cout << "" << endl;

        if(shapeSelected == 1)
        {

            do
            {
                // ask for a height and check that the input is an integer
                cout << "What would you like your height to be? Please eneter a nmber" << endl;
                cout << endl;
                cin >> shapeSizeS;

                // ask for a width and check that the input is an integer
                cout << "And what would you like your width to be? Please eneter a number" << endl;
                cout << endl;
                cin >> rectWidthS;

                //Error trapping: If the input is not a int
                if( stringCheckerTwo ( shapeSizeS ) == 0 || stringCheckerThree ( rectWidthS ) == 0 )
                {
                    cout << "" << endl;
                    cout << "ERROR, invalid input" << endl;
                    cout << "" << endl;
                }

                //Error trapping: If the input is an int
                if( stringCheckerTwo ( shapeSizeS ) == 1 && stringCheckerThree ( rectWidthS ) == 1 )
                {
                    shapeSizeI = ::atof(shapeSizeS.c_str());
                    rectWidthI = ::atof(rectWidthS.c_str());
                    cout << endl;
                }
            }
            while( stringCheckerTwo ( shapeSizeS ) == 0 || stringCheckerThree ( rectWidthS ) == 0);

            cout << ">- Rectangle at " << shapeSizeI << " and " << rectWidthI << endl;
            cout << endl;

            //create a rectangle
            for (int i = 0; i < shapeSizeI; i++ )
            {
                for(int j = 0; j < rectWidthI; j++)
                {
                    //create each line of the rectangle
                    cout << "#";
                }
                //moves the print to the next line
                cout << endl;
            }
        }
//Create a triangle
        if(shapeSelected == 2)
        {
            do
            {
                // ask for a size and check that the input is an integer
                cout << "What would you like your size to be? Please enter a number" << endl;
                cout << endl;
                cin >> shapeSizeS;

                //Error trapping: If the input is not a int
                if( stringCheckerTwo ( shapeSizeS ) == 0 )
                {
                    cout << "" << endl;
                    cout << "ERROR, invalid input" << endl;
                    cout << "" << endl;
                }

                //Error trapping: If the input is an int
                if( stringCheckerTwo ( shapeSizeS ) == 1 )
                {
                    shapeSizeI = ::atof(shapeSizeS.c_str());
                    cout << endl;
                }
            }
            while( stringCheckerTwo ( shapeSizeS ) == 0 );

            cout << ">- Triangle at " << shapeSizeI << endl;
            cout << endl;

            for (int i = 0; i < shapeSizeI; i++ )
            {
                for(int j = 0; j < i + 1; j++)
                {
                    //create each line of the triangle
                    cout << "#";
                }
                //moves the print to the next line
                cout << endl;
                // triangleLimit ++;
            }

        }

        //Create a triangle
        if(shapeSelected == 3)
        {
            do
            {
                // ask for a size and check that the input is an integer
                cout << "What would you like your size to be? Please enter a number" << endl;
                cout << endl;
                cin >> shapeSizeS;

                //Error trapping: If the input is not a int
                if( stringCheckerTwo ( shapeSizeS ) == 0 )
                {
                    cout << "" << endl;
                    cout << "ERROR, invalid input" << endl;
                    cout << "" << endl;
                }

                //Error trapping: If the input is an int
                if( stringCheckerTwo ( shapeSizeS ) == 1 )
                {
                    shapeSizeI = ::atof(shapeSizeS.c_str());
                    cout << endl;
                }
            }
            while( stringCheckerTwo ( shapeSizeS ) == 0 );

            cout << ">- Triangle at " << shapeSizeI << endl;
            cout << endl;

            for (int i = shapeSizeI; i > 0; i -- )
            {
                for(int j = 0; j < i; j++)
                {
                    //create each line of the triangle
                    cout << "#";
                }
                //moves the print to the next line
                cout << endl;
                //triangleLimitTwo -= 1;
            }
        }
//Create a triangle
        if(shapeSelected == 4)
        {

            do
            {
                // ask for a size and check that the input is an integer
                cout << "What would you like your size to be? Please enter a number" << endl;
                cout << endl;
                cin >> shapeSizeS;

                //Error trapping: If the input is not a int
                if( stringCheckerTwo ( shapeSizeS ) == 0 )
                {
                    cout << "" << endl;
                    cout << "ERROR, invalid input" << endl;
                    cout << "" << endl;
                }

                //Error trapping: If the input is an int
                if( stringCheckerTwo ( shapeSizeS ) == 1 )
                {
                    shapeSizeI = ::atof(shapeSizeS.c_str());
                    cout << endl;
                }
            }
            while( stringCheckerTwo ( shapeSizeS ) == 0 );

            cout << ">- Triangle at " << shapeSizeI << endl;
            cout << endl;

            for (int i = 0; i < shapeSizeI; i++ )
            {
                for(int j = 0; j < i; j++)
                {
                    //create each line of the triangle
                    cout << " ";
                }

                for(int j = 0; j < shapeSizeI - i; j++)
                {
                    //create each line of the triangle
                    cout << "#";
                }



                //moves the print to the next line
                cout << endl;
            }
        }

        //Create a triangle
        if(shapeSelected == 5)
        {
            do
            {
                // ask for a size and check that the input is an integer
                cout << "What would you like your size to be? Please eneter a number" << endl;
                cout << endl;
                cin >> shapeSizeS;

                //Error trapping: If the input is not a int
                if( stringCheckerTwo ( shapeSizeS ) == 0 )
                {
                    cout << "" << endl;
                    cout << "ERROR, invalid input" << endl;
                    cout << "" << endl;
                }

                //Error trapping: If the input is an int
                if( stringCheckerTwo ( shapeSizeS ) == 1 )
                {
                    shapeSizeI = ::atof(shapeSizeS.c_str());
                    cout << endl;
                }
            }
            while( stringCheckerTwo ( shapeSizeS ) == 0 );

            cout << ">- Triangle at " << shapeSizeI << endl;
            cout << endl;

            for (int i = 0; i < shapeSizeI; i++ )
            {
                for(int j = 0; j < shapeSizeI - ( i + 1 ); j++)
                {
                    //create each line of the triangle
                    cout << " ";
                }

                for(int j = 0; j < i + 1; j++)
                {
                    //create each line of the triangle
                    cout << "#";
                }



                //moves the print to the next line
                cout << endl;
            }
        }

        //Create a triangle
        if(shapeSelected == 6)
        {
            do
            {
                // ask for a size and check that the input is an integer
                cout << "What would you like your size to be? Please enter a number" << endl;
                cout << endl;
                cin >> shapeSizeS;

                //Error trapping: If the input is not a int
                if( stringCheckerTwo ( shapeSizeS ) == 0 )
                {
                    cout << "" << endl;
                    cout << "ERROR, invalid input" << endl;
                    cout << "" << endl;
                }

                //Error trapping: If the input is an int
                if( stringCheckerTwo ( shapeSizeS ) == 1 )
                {
                    shapeSizeI = ::atof(shapeSizeS.c_str());
                    cout << endl;
                }
            }

            while( stringCheckerTwo ( shapeSizeS ) == 0 );

            cout << ">- Triangle at " << shapeSizeI << endl;
            cout << endl;

            for (int i = 1; i <= shapeSizeI ; i += 2)
            {
                for(int j = 0; j < (shapeSizeI - i) / 2; j++)
                {
                    //create each line of the triangle
                    cout << " ";
                }

                for(int j = 0; j < i; j++)
                {
                    //create each line of the triangle
                    cout << "#";
                }



                //moves the print to the next line
                cout << endl;
            }
        }

//Create the diamond
        if(shapeSelected == 7)
        {
            do
            {
                // ask for a size and check that the input is an integer
                cout << "What would you like your size to be? Please enter a number" << endl;
                cout << endl;
                cin >> shapeSizeS;

                //Error trapping: If the input is not a int
                if( stringCheckerTwo ( shapeSizeS ) == 0 )
                {
                    cout << "" << endl;
                    cout << "ERROR, invalid input" << endl;
                    cout << "" << endl;
                }

                //Error trapping: If the input is an int
                if( stringCheckerTwo ( shapeSizeS ) == 1 )
                {
                    shapeSizeI = ::atof(shapeSizeS.c_str());
                    cout << endl;
                    diamondLimit = shapeSizeI + (shapeSizeI - 1);
                    diamondLimitTwo = diamondLimit - 2;
                }
            }
            while( stringCheckerTwo ( shapeSizeS ) == 0 );

            cout << ">- Diamond at " << shapeSizeI << endl;
            cout << endl;

            for (int i = 0; i < shapeSizeI; i++ )
            {

                for(int j = (diamondLimit -1)/2; j > 0; j--)
                {
                    //create each line of the triangle
                    cout << " ";
                }

                for(int j = 0; j < 1 + (i * 2); j++)
                {
                    //create each line of the triangle
                    cout << "#";
                }

                //moves the print to the next line
                cout << endl;
                diamondLimit -= 2;
            }

            for (int i = 0; i < shapeSizeI - 1; i++ )
            {

                for(int j = 0; j < i + 1; j++)
                {
                    //create each line of the triangle
                    cout << " ";
                }

                for(int j = 0; j < diamondLimitTwo; j++)
                {
                    //create each line of the triangle
                    cout << "#";
                }

                //moves the print to the next line
                cout << endl;
                diamondLimitTwo -= 2;
            }
        }

        //Create the Tree
        if(shapeSelected == 8)
        {
            do
            {
                // ask for a size and check that the input is an integer
                cout << "What would you like your size to be? Please enter a number" << endl;
                cout << endl;
                cin >> shapeSizeS;

                //Error trapping: If the input is not a int
                if( stringCheckerTwo ( shapeSizeS ) == 0 )
                {
                    cout << "" << endl;
                    cout << "ERROR, invalid input" << endl;
                    cout << "" << endl;
                }

                //Error trapping: If the input is an int
                if( stringCheckerTwo ( shapeSizeS ) == 1 )
                {
                    shapeSizeI = ::atof(shapeSizeS.c_str());
                    cout << endl;
                    treeTopLimit = shapeSizeI + (shapeSizeI - 1);
                    treeTopLimitTwo = shapeSizeI + (shapeSizeI - 1);
                    treeTrunk = (round(treeTopLimitTwo/5))*2 - 1;
                }
            }
            while( stringCheckerTwo ( shapeSizeS ) == 0 );

            cout << ">- Tree at " << shapeSizeI << endl;
            cout << endl;

            for (int i = 0; i < shapeSizeI; i++ )
            {

                for(int j = (treeTopLimit -1)/2; j > 0; j--)
                {
                    //create each line of the triangle
                    cout << " ";
                }

                for(int j = 0; j < 1 + (i * 2); j++)
                {
                    //create each line of the triangle
                    cout << "#";
                }

                //moves the print to the next line
                cout << endl;
                treeTopLimit -= 2;
            }

            for (int i = 0; i < round(shapeSizeI/2); i++ )
            {
                for (int j = 0; j < (treeTopLimitTwo - treeTrunk)/2; j++)
                {
                    cout << " ";

                }
                for (int j = 0; j < treeTrunk; j++)
                {
                    //create each line of the rectangle
                    cout << "#";
                }
                //moves the print to the next line

                cout << endl;
            }

        }
        //If a valid shape is not selected, notify the user and allow them to re-pick a shape
        else if(shapeSelected != 1 && shapeSelected != 2 && shapeSelected != 3 && shapeSelected != 4 && shapeSelected != 5 && shapeSelected != 6 && shapeSelected != 7 && shapeSelected != 8)
        {

            cout << endl;
            cout << ">- Please enter a valid input" << endl;
            cout << endl;
        }

        while(restartLoop == 1)
        {
            //ask user if they would like to restart
            cout << endl;
            cout << ">- would you like to play again? y for yes, n for no" << endl;
            cin >> restartProgram;


            //If user enters yes, restart the program
            if(restartProgram == "y" || restartProgram == "Y" || restartProgram == "yes" || restartProgram == "Yes")
            {
                restartLoop = 0;
                currentlyLooping = 1;
            }
            //If user enters no, restart the program
            if(restartProgram == "n" || restartProgram == "N" || restartProgram == "no" || restartProgram == "No")
            {
                restartLoop = 0;
                currentlyLooping = 0;
            }

            //If input is ivlid, notify the user
            if(restartProgram != "y" && restartProgram != "Y" && restartProgram != "yes" && restartProgram != "Yes" && restartProgram != "n" && restartProgram != "N" && restartProgram != "no" && restartProgram != "No")
            {
                restartLoop  = 1;
                cout << endl;
                cout << ">- Please enter a --y-- or --n-- " << endl;
                cout << endl;
            }


        }
    }

    return 0;
}
