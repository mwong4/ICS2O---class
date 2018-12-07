#include <iostream>
#include <math.h>

using namespace std;

int treeSize = 0; // This variable is used in order to define the size of the christmas tree

int triangleStart;
int triangleFinish;
int triangleTwoStart;
int triangleTwoFinish;
int triangleThreeStart;
int triangleThreeFinish;


int main()
{

    cout << "please enter a tree size" << endl;
    cout << endl;
    cin >> treeSize;

    //triangleStart = 1;
    triangleFinish = treeSize;
    triangleTwoStart = (treeSize * (3/4));
    triangleTwoFinish = (treeSize * (5/3));
    triangleThreeStart = (treeSize * (4/3));
    triangleThreeFinish = (treeSize * (9/4));

    triangleFinish = treeSize;
    triangleTwoStart = (int)round(triangleTwoStart);
    triangleTwoFinish = (int)round(triangleTwoFinish);
    triangleThreeStart = (int)round(triangleThreeStart);
    triangleThreeFinish = (int)round(triangleThreeFinish);


   /* for (int i = 1; i <= treeSize*2 - 1; i += 2){

        for(int j = 1; j <= ((triangleFinish*2 - 1) - i )/2; j++){
            cout << " ";
        }

        for(int j = 1; j <= i; j++){
            cout << "#";
        }

        cout << endl;

    }

    //cout << triangleTwoStart << endl;

        for (int i = triangleTwoStart * 2 - 1; i <= triangleTwoFinish * 2 - 1; i += 2){

        for(int j = 1; j <= (triangleTwoFinish*2-1 - i )/2; j++){
            cout << " ";
        }

        for(int j = 1; j <= i + 6; j++){
            cout << "#";
        }

            cout << i << " " << triangleTwoStart;

        cout << endl;

    }

    */


 /*   for (int i = 0; i <= triangleFinish; i++ )
    {

        for(int j = (triangleFinish - 1) - i; j >= 0; j--)
        {W
            cout << " ";
        }

        for(int j = 0; j <= 1 + (i * 2); j++)
        {
            //create each line of the triangle
            cout << "#";
        }

        //moves the print to the next line
        cout << endl;
        //diamondLimit -= 2;
    }

    */


/*    for (int i = 0; i <= triangleFinish; i++ )
    {

        for(int j = (triangleFinish - 1) - i; j >= 0; j--)
        {
            //create each line of the triangle
            cout << " ";
        }

        for(int j = triangleTwoStart * 2 - 1; j <= (triangleTwoFinish * 2 - 1) + 2 * i; j++)
        {
            //create each line of the triangle
            cout << "#";
        }

        //moves the print to the next line
        cout << endl;
        //diamondLimit -= 2;
    }

    */



    return 0;
}
