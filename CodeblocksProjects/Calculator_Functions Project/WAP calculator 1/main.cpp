/*
>- Author: Max Wong
>- Date: Dec 6, 2018
>- Updated: Dec 6, 2018
>- Purpose: write a function that will perform addition, subtraction, multiplication... and return the result
>-
>- [version 1]
>-
>-
*/

/*
[TO DO]

- Set up error trapping
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>

using namespace std;

//Defining all of my operations as functions (prototype)
float addOperation ( float, float );
float subOperation ( float, float );
float multOperation ( float, float );
float divOperation ( float, float );
float powOperation ( float, float );
float sqrtOperation ( float);

float firstInputValue ();
float secondInputValue ();

void spacing ();
void printErrorInput ();
void performOperation ( int, int, int );

int mainMenu();


int main()
{
    //Defining variables
    float firstInput = 0; //First input used in all opeations
    float secondInput = 0; //Second input used in all operations

    float result = 0;
    float opSelected = 0;

    bool projectRunning = true;

    while ( projectRunning == true)
    {

        opSelected = mainMenu();

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
            secondInput = secondInputValue();
        }

        if( opSelected == 9 )
        {W

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

    int pickNumber;

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

    cin >> pickNumber;

    return pickNumber;

}

float firstInputValue ()
{

    float firstInput = 0;

    cout << "What is your first number?" << endl;
    cin >> firstInput;

    return firstInput;
}

float secondInputValue ()
{

    float secondInput = 0;

    cout << "What is your second number?" << endl;
    cin >> secondInput;

    return secondInput;
}

void spacing ()
{
    cout << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << endl;

    return;
}

void printErrorInput ()
{
    cout << endl;
    cout << "Error" << endl;
    cout << "Please enter a valid input" << endl;
    cout << endl;
}

void performOperation ( int opSelected, int firstInput, int secondInput )
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

