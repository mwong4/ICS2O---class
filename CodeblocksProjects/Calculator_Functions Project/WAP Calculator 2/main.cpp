/*
>- Author: Max Wong
>- Date: Dec 6, 2018
>- Updated: Dec 7, 2018
>- Purpose: write a function that will perform addition, subtraction, multiplication... and return the result
>-
>- [version 2]
>-
>-
*/

/*
[TO DO]

- Currently nothing

*/

//Include statements
#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>

using namespace std;

//Defining all of my operations as functions (prototype)
float addOperation ( float, float ); //Function prototype for adding operation
float subOperation ( float, float ); //Function prototype for subtracting operation
float multOperation ( float, float ); //Function prototype for multiplying operation
float divOperation ( float, float ); //Function prototype for dividing operation
float powOperation ( float, float ); //Function prototype for "power of" operation
float sqrtOperation ( float); //Function prototype for square root operation

float firstInputValue (); //Function prototype to get the first input
float secondInputValue ( int ); //Function prototype to get the second input

void spacing (); //Function for spacing
void printErrorInput (); //Function to print input error
void performOperation ( int, int, int ); //Function to perform the operation

int mainMenu(); //Function to print the menu and get the input

bool stringChecker( string ); //Function used to check if an input is a float


int main()
{
    //Defining variables
    float firstInput = 0; //First input used in all opeations
    float secondInput = 0; //Second input used in all operations

    float opSelected = 0; //Variable that defines the operation selected

    bool projectRunning = true; //Bool that defines if the project is still running

    //While loop that, when false, quits program
    while ( projectRunning == true)
    {

    //Used to select operation
        opSelected = mainMenu();

        //Spacing
        spacing();

        cout << endl;
        cout << ">- You entered: " << opSelected << endl;
        cout << endl;

        //Get the inputs for the operations and erro trapping unknown integers. Also checking for quit
        if( opSelected == 1 || opSelected == 2 || opSelected == 3 || opSelected == 4 || opSelected == 5 || opSelected == 6)
        {
            firstInput = firstInputValue();
        }

        if( opSelected == 1 || opSelected == 2 || opSelected == 3 || opSelected == 4 || opSelected == 5)
        {
            secondInput = secondInputValue( opSelected );
        }

        if( opSelected == 9 )
        {

            projectRunning = false;
        }

        if( opSelected != 1 && opSelected != 2 && opSelected != 3 && opSelected != 4 && opSelected != 5 && opSelected != 6 && opSelected != 9)
        {
            printErrorInput();
        }

//Perform Operations
        performOperation ( opSelected, firstInput, secondInput);

    }

    return 0;
}

//Adding operation
float addOperation ( float firstInput, float secondInput)
{
    float result;
    result = firstInput + secondInput;

    cout << endl;
    cout << firstInput << " + " << secondInput << " = " << result << endl;
    cout << endl;

    return result;
}

//Subtraction operation
float subOperation ( float firstInput, float secondInput)
{
    float result;
    result = firstInput - secondInput;

    cout << endl;
    cout << firstInput << " - " << secondInput << " = " << result << endl;
    cout << endl;

    return result;
}

//Multiplication operation
float multOperation ( float firstInput, float secondInput)
{
    float result;
    result = firstInput * secondInput;

    cout << endl;
    cout << firstInput << " * " << secondInput << " = " << result << endl;
    cout << endl;

    return result;
}

//Divide operation
float divOperation ( float firstInput, float secondInput)
{
    float result;
    result = firstInput / secondInput;

    cout << endl;
    cout << firstInput << " / " << secondInput << " = " << result << endl;
    cout << endl;

    return result;
}

//Power of operation
float powOperation ( float firstInput, float secondInput)
{
    float result = 1;

    for(int i = 0; i < secondInput; i++)
    {
        result = firstInput * result;

    }

    cout << endl;
    cout << firstInput << " ^ " << secondInput << " = " << result << endl;
    cout << endl;

    return result;
}

//Square root operation
float sqrtOperation ( float firstInput)
{
    float result = 0;

    result = sqrt ( firstInput);

    cout << endl;
    cout << " 2 /- " << firstInput << " = " << result << endl;
    cout << endl;

    return result;
}

int mainMenu ()
{

    std::string pickNumber = " ";
    int pickNumberI = 0;

    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << ">- " << endl;
    cout << ">- welcome, please enter a number to select the operation you would like to use" << endl;
    cout << ">- " << endl;
    cout << ">- /1/. for addition (+) " << endl;
    cout << ">- /2/. for subtraction (-) " << endl;
    cout << ">- /3/. for multiplication (*) " << endl;
    cout << ">- /4/. for division (/) " << endl;
    cout << ">- /5/. for power of (^) " << endl;
    cout << ">- /6/. for square root of (/-) " << endl;
    cout << ">- " << endl;
    cout << ">- /9/. to quit" << endl;

//Error trapping to make sure the input is an int
    do
    {

        cin >> pickNumber;

        if( stringChecker ( pickNumber ) == 0 )
        {
            printErrorInput();
        }
        if( stringChecker ( pickNumber ) == 1 )
        {
            pickNumberI = ::atof(pickNumber.c_str());
        }
    }
    while( stringChecker ( pickNumber ) == 0);

    return pickNumberI;

}

float firstInputValue ()
{

    float firstInput = 0;
    std::string input = " ";

    //Error trapping make sure input is a float
    do
    {
        cout << "What is your first number?" << endl;
        cin >> input;

        if( stringChecker ( input ) == 0)
        {
            printErrorInput();
        }

        if( stringChecker ( input ) == 1)
        {
            firstInput = ::atof(input.c_str());
        }

    }
    while ( stringChecker ( input ) == 0);

    return firstInput;
}

float secondInputValue ( int operation )
{

    float secondInput = 0;
    std::string input = " ";

//Error trapping make sure input is a float
//This loop is for when not using division
    if ( operation != 4 )
    {
        do
        {
            cout << "What is your second number?" << endl;
            cin >> input;

            if( stringChecker ( input ) == 0 )
            {
                printErrorInput();
            }

            if( stringChecker ( input ) == 1 )
            {
                secondInput = ::atof(input.c_str());
            }


        }
        while ( stringChecker ( input ) == 0 );
    }

    //This loop is for when division is being used
    if (operation == 4)
    {

        do
        {

            cout << "What is your second number?" << endl;
            cin >> input;

            if( stringChecker ( input ) == 0 || secondInput == 0)
            {
                printErrorInput();
            }

            if( stringChecker ( input ) == 1)
            {
                secondInput = ::atof(input.c_str());
            }


        }
        while ( stringChecker ( input ) == 0 || secondInput == 0);

    }

    return secondInput;
}

//Spacing
void spacing ()
{
    cout << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << endl;

    return;
}

//To print an error message
void printErrorInput ()
{
    cout << endl;
    cout << "Error" << endl;
    cout << "Please enter a valid input" << endl;
    cout << endl;
}

//To perform the operation
void performOperation ( int opSelected        secondInput = secondInputValue();, int firstInput, int secondInput )
{
    //Performing the operations

    if( opSelected == 1)
    {
        addOperation ( firstInput, secondInput );
    }

    if( opSelected == 2)
    {
        subOperation ( firstInput, secondInput );
    }

    if( opSelected == 3)
    {
        multOperation ( firstInput, secondInput );
    }

    if( opSelected == 4)
    {
        divOperation ( firstInput, secondInput );
    }

    if( opSelected == 5)
    {
        powOperation ( firstInput, secondInput );
    }

    if( opSelected == 6)
    {
        sqrtOperation ( firstInput );
    }
}

//Integer checker for shape selection
bool stringChecker( string currentNumber )
{
    for( string::size_type i = 0; i < currentNumber.size(); ++i )
    {
        if ( ( currentNumber[i] != '0' ) && ( currentNumber[i] != '1' ) && ( currentNumber[i] != '2' ) && ( currentNumber[i] != '3' ) && ( currentNumber[i] != '4' ) && ( currentNumber[i] != '5' ) && ( currentNumber[i] != '6' ) && ( currentNumber[i] != '7' ) && ( currentNumber[i] != '8' ) && ( currentNumber[i] != '9' ) && ( currentNumber[i] != '.' ))
        {
            return false;
        }
    }
    return true;
}

