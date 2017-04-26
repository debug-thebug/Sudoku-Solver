#include<iostream>
using namespace std;

//Input the sudoku. Put 0 where we have to put numbers.
/*int sud[10][10] = {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //first column for index 0 (useless)
                    {0, 3, 6, 0, 2, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 8, 0, 7, 5},
                    {0, 0, 0, 0, 1, 0, 0, 0, 3, 0},
                    {0, 1, 0, 0, 8, 0, 4, 0, 0, 2},
                    {0, 0, 0, 7, 0, 0, 0, 6, 0, 0},
                    {0, 2, 0, 0, 7, 0, 6, 0, 0, 3},
                    {0, 0, 7, 0, 0, 0, 9, 0, 0, 0},
                    {0, 9, 4, 0, 5, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 1, 0, 9, 4},
                };*/

int sud[10][10] = {
                    {0,0,0,0,0,0,0,0,0,0},
                    {0,8,0,0,0,0,0,0,0,0},	//World's Toughest Sudoku Puzzle by Finnish Mathematician
                    {0,0,0,3,6,0,0,0,0,0},
                    {0,0,7,0,0,9,0,2,0,0},
                    {0,0,5,0,0,0,7,0,0,0},
                    {0,0,0,0,0,4,5,7,0,0},
                    {0,0,0,0,1,0,0,0,3,0},
                    {0,0,0,1,0,0,0,0,6,8},
                    {0,0,0,8,5,0,0,0,1,0},
                    {0,0,9,0,0,0,0,4,0,0}
};

//function that checks if the number input does not collide, according to rules of sudoku
bool check(int no, int r, int c)
{
    int i, j;

    //check row
    for(i=1; i<=9; i++)
        if(sud[r][i] == no)
            return false;

    //check column
    for(i=1; i<=9; i++)
        if(sud[i][c] == no)
            return false;

    //check block
    if(r<=3)
        i=1;
    else if(r<=6)
        i=4;
    else
        i=7;

    if(c<=3)
        j=1;
    else if(c<=6)
        j=4;
    else
        j=7;

    int rt = i+2;
    int ct = j+2;
    int remj = j;

    //for checking block of 9 cubes
    for(; i<=rt; i++)
    {
        for(j=remj; j<=ct; j++)     //IMPORTANT
        {
            if(sud[i][j] == no)
            {
                return false;
            }
        }
    }

    return true;    //return true when it passes all the tests
}

void print()
{
    for(int i=1; i<=9; i++)     //print the current state of sudoku
    {
        for(int j=1; j<=9; j++)
            cout<<sud[i][j]<<" ";
        cout<<endl;
    }
}

bool solver(int r, int c)   //the main driver of program
{
    if(r!=9 || c!=9)
    {
        if(sud[r][c] == 0)      //if the current value is 0, try placing a number and going further
        {
            for(int i=1; i<=9; i++)
            {
                if(check(i, r, c) == true)
                {
                    sud[r][c] = i;

                    if(c != 9)
                    {
                        if(solver(r, c+1) == true)  //we move ahead column wise
                            return true;
                        sud[r][c] = 0;
                    }
                    else
                    {
                        if(solver(r+1, 1) == true)  //if we are in the last column, we move to the next row
                            return true;
                        sud[r][c] = 0;
                    }
                }
            }
        }
        else
        {
            //if number already exists, we move ahead. If we are in last column, we move to the next row
            if(c != 9)
            {
                if(solver(r, c+1) == true)
                    return true;
            }
            else
            {
                if(solver(r+1, 1) == true)
                    return true;
            }
        }
    }
    else        //we are in the last row, last column
    {
        if(sud[r][c] != 0)  //if there is a number at that place
            return true;
        else
        {
            for(int i=1; i<=9; i++)     //otherwise check all different values
                if(check(i, r, c) == true)
                {
                    sud[r][c] = i;
                    return true;        //return value now
                }
            return false;
        }
    }

    return false;       //in case of something really unexpected lol
}

int main()
{

    if(solver(1, 1) == true)
    {
        cout<<"CONGRATS!! SUDOKU SOLVED!!\n\n";
        print();
    }
    else
        cout<<"Oops, there is some mistake! Wrong Sudoku! Can NOT be solved!";
    return 0;
}
