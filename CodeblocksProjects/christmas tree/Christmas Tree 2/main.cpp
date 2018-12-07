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
    triangleTwoFinish = (treeSize * (9/4));
    triangleThreeStart = (treeSize * (5/4));
    triangleThreeFinish = (treeSize * (11/4));

    triangleFinish = treeSize;
    triangleTwoStart = (int)round(triangleTwoStart);
    triangleTwoFinish = (int)round(triangleTwoFinish);
    triangleThreeStart = (int)round(triangleThreeStart);
    triangleThreeFinish = (int)round(triangleThreeFinish);


    for (int i = 1; i <= treeSize*2 + 3; i += 2){

        for(int j = 1; j <= ((triangleThreeFinish*2 - 1) - i )/2; j++){
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

        for(int j = 1; j <= i + triangleThreeStart*2; j++){
            cout << "#";
        }

          //  cout << i << " " << triangleTwoStart;

        cout << endl;

    }

        for (int i = triangleThreeStart * 2 - 1; i <= triangleThreeFinish * 2 - 1; i += 2)
    {

        for(int j = 1; j <= (triangleThreeFinish*2-1 - i )/2; j++)
        {
            cout << " ";
        }

        for(int j = 1; j <= i + triangleThreeStart*2; j++)
        {
            cout << "#";
        }

        //cout << i << " " << triangleThreeStart;

        cout << endl;

    }



    return 0;
}
