/*
>- Author: Max Wong
>- Date: Dec 11, 2018
>- Updated: Dec 12, 2018
>- Purpose: write a calculator that uses imaginary numbers
>-
>- [version 2]
>-
>- Credit to Vedaant Srivastava (shrimp pasta) for introducing me to a new way of error trapping
>-
>- [TO DO]
>- Cleaning code
>- Division
*/

//Include statements
#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <sstream>

using namespace std;

float firstNumber (); //Function to get the first number
float secondNumber (); //Function to get the second number
float thirdNumber (); //function to get the third number
float fourthNumber (); //Function to get the fourth number

void add( float, float, float, float ); //This function is used to perform the addition operation
void sub( float, float, float, float ); //This function is used to perform the subtraction operation
void mul( float, float, float, float ); //This function is used to perform the multiplication operation

int chooseOperation (); //This function allows the user to select an operation

void spacing(); //This function is used for spacing
void printErrorInput(); //This function si for printing an input related error message to the consol
bool stringChecker( string ); //This function is used to check that the input is valid

int main()
{

    //These four variables for the equations "a + bi" and c + di

    float firstInput; //This input represents the "a" term
    float secondInput; //This input represents the "b" term
    float thirdInput; //This input represents the "c" term
    float fourthInput; //This input represents the "d" term

    int operation; //This variable holds the operation selected
    bool endProgram = false; //This variable is used to determine if the program is still running


//Some formatting/spacing
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`" <<endl;

    //This while loop is used, when bool statement is false, in order to shut down the program
    while ( endProgram == false )
    {



        cout << endl;
        cout << ">- Please enter 4 numbers that will be a part of the equations /a + bi/ and /c + di/." << endl;
        cout << endl;


        //Determining the inputs
        firstInput = firstNumber ();
        secondInput = secondNumber ();
        thirdInput = thirdNumber ();
        fourthInput = fourthNumber ();


        //Show the user what they inputed
        cout << ">- You entered: " << firstInput << " + " << secondInput << "i" << endl;
        cout << ">-                     and" << endl;
        cout << ">-              " << thirdInput << " + " << fourthInput << "i" << endl;

        //Determining the operation
        operation = chooseOperation();

        if( operation == 1 )
        {
            add ( firstInput, secondInput, thirdInput, fourthInput );
        }
        if( operation == 2 )
        {
            sub ( firstInput, secondInput, thirdInput, fourthInput );
        }
        if( operation == 3 )
        {
            mul ( firstInput, secondInput, thirdInput, fourthInput );
        }
        if( operation == 9)
        {
            endProgram = true;
        }

        spacing();
    }




    return 0;
}

//Asks the user for the "a"
float firstNumber ()
{

    float firstInput;
    std::string inputValueS;

    do
    {

        cout << ">- please enter your first value" << endl;
        cin >> inputValueS;
        cout << endl;

        if( stringChecker (inputValueS) == 1 )
        {
            firstInput = ::atof(inputValueS.c_str());
        }
        if( stringChecker (inputValueS) == 0 )
        {
            printErrorInput();
        }

    }
    while ( stringChecker(inputValueS) == 0 );


    return firstInput;
}

//Asks the user for the "b"
float secondNumber ()
{

    float secondInput;
    std::string inputValueS;

    do
    {

        cout << ">- please enter your second value" << endl;
        cin >> inputValueS;
        cout << endl;

        if( stringChecker (inputValueS) == 1 )
        {
            secondInput = ::atof(inputValueS.c_str());
        }
        if( stringChecker (inputValueS) == 0 )
        {
            printErrorInput();
        }

    }
    while ( stringChecker(inputValueS) == 0 );

    return secondInput;
}

//Asks the user for the "c"
float thirdNumber ()
{

    float thirdInput;
    std::string inputValueS;

    do
    {

        cout << ">- please enter your third value" << endl;
        cin >> inputValueS;
        cout << endl;

        if( stringChecker (inputValueS) == 1 )
        {
            thirdInput = ::atof(inputValueS.c_str());
        }
        if( stringChecker (inputValueS) == 0 )
        {
            printErrorInput();
        }

    }
    while ( stringChecker(inputValueS) == 0 );

    return thirdInput;
}

//Asks the user for the "d"
float fourthNumber ()
{

    float fourthInput;
    std::string inputValueS;

    do
    {

        cout << ">- please enter your fourth value" << endl;
        cin >> inputValueS;
        cout << endl;

        if( stringChecker (inputValueS) == 1 )
        {
            fourthInput = ::atof(inputValueS.c_str());
        }
        if( stringChecker (inputValueS) == 0 )
        {
            printErrorInput();
        }

    }
    while ( stringChecker(inputValueS) == 0 );

    return fourthInput;
}

//This function is used to determine which operation the user would like
int chooseOperation ()
{

    int opSelected = 0;

    do
    {

        spacing();

        //UI/Menu
        cout << ">- What operation would you like?" << endl;
        cout << ">- " << endl;
        cout << ">- /1/ for addition" << endl;
        cout << ">- /2/ for subtraction" << endl;
        cout << ">- /3/ for multiplication" << endl;
        cout << ">- [or, press /9/ to quit]" << endl;
        cin >> opSelected;
        cout << endl;

        //Making the appropriate response
        if( opSelected == 1)
        {
            cout << ">- You selected: Addition" << endl;
        }
        if( opSelected == 2)
        {
            cout << ">- You selected: Subtraction" << endl;
        }
        if( opSelected == 3)
        {
            cout << ">- You selected: Multiplication" << endl;
        }
        if( opSelected == 9)
        {
            cout << ">- Quitting...." << endl;
        }
        if( opSelected != 1 && opSelected != 2 && opSelected != 3 && opSelected != 9)
        {
            printErrorInput();
        }
    }
    while ( opSelected != 1 && opSelected != 2 && opSelected != 3 && opSelected != 9);

    return opSelected;

}

//Used for spacing
void spacing()
{
    cout << endl;
    cout << "===============================================================================================" << endl;
    cout << endl;
}

//Used to print an input related error message
void printErrorInput()
{
    cout << endl;
    cout << ">- Error, please enter a valid input" << endl;
    cout << endl;
}

//Displaying the addition caculation
void add ( float a, float b, float c, float d )
{
    float realResult = 0;
    float imaginaryResult = 0;

    realResult = a + c;
    imaginaryResult = b + d;


    cout << " ans = ( " << a << " + " << b << "i ) + ( " << c << " + " << d << "i )" << endl;
    cout << endl;
    cout << "     = " << a << " + " << b << "i + " << c << " + " << d << "i" << endl;
    cout << endl;

    //Determins if the ending should use a negative or positive sign
    if( imaginaryResult >= 0 )
    {
        cout << "[ans = " << realResult << " + " << imaginaryResult << "i]" << endl;
        cout << endl;
    }

    if( imaginaryResult < 0 )
    {
        cout << "[ans = " << realResult << "  " << imaginaryResult << "i]" << endl;
        cout << endl;
    }

    return;
}

//Displaying the subtraction calculations
void sub ( float a, float b, float c, float d )
{
    float realResult = 0;
    float imaginaryResult = 0;

    realResult = a - c;
    imaginaryResult = b - d;


    cout << " ans = ( " << a << " + " << b << "i ) - ( " << c << " + " << d << "i )" << endl;
    cout << endl;
    cout << "     = " << a << " + " << b << "i - " << c << " - " << d << "i" << endl;
    cout << endl;

    //Determins if the ending should use a negative or positive sign
    if( imaginaryResult >= 0 )
    {
        cout << "[ans = " << realResult << " + " << imaginaryResult << "i]" << endl;
        cout << endl;
    }

    if( imaginaryResult < 0 )
    {
        cout << "[ans = " << realResult << "  " << imaginaryResult << "i]" << endl;
        cout << endl;
    }


}

//Displaying the multiplication calculations
void mul ( float a, float b, float c, float d )
{

    cout << endl;
    cout << " ans = ( " << a << " + " << b << "i ) ( " << c << " + " << d << "i )" << endl;
    cout << endl;
    cout << " ans = " << a * c << " + " << a * d << " i + " << b * c << "i + " << b * d << "*i*i" << endl;
    cout << endl;
    cout << ">- since i = sqrt( -1 ), i squared is equal to (-1)" << endl;
    cout << endl;
    cout << " ans = " << a * c << " + " << a * d << " i + " << b * c << "i + " << -1 * b * d << endl;
    cout << endl;
    cout << "[ans = " << (a * c) + (-1 * b * d) << " + " << (a * d) + (b * c) << "i]" << endl;

}

//Function that verifies that an input is valid
bool stringChecker(string myString)
{
    //creating a long double
    long double myFloatString;
    ostringstream conversion;

    //converting the string to a float (the process will cut out any unwanted characters)
    stringstream (myString) >> myFloatString;
    conversion << setprecision(9) << myFloatString;

    //COnverting float back into string
    string convertedFloat = conversion.str();


    //If string does equal cleaned float (tring), return true
    if(convertedFloat == myString)
    {
        return true;
    }
    else //Else, return false
    {
        return false;
    }
}
