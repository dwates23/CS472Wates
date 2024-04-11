#include <iostream>
#include <fstream>
using namespace std;

const int N = 9;
int grid[N][N];

bool isValid(int row, int col, int num) 
{
    for (int x = 0; x < N; x++) 
    {
        if (grid[row][x] == num || grid[x][col] == num) 
        {
            return false;
        }
    }
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            if (grid[i + startRow][j + startCol] == num) 
            {
                return false;
            }
        }
    }
    return true;
}

bool findEmptyPosition(int &row, int &col) 
{
    for (row = 0; row < N; row++) 
    {
        for (col = 0; col < N; col++) 
        {
            if (grid[row][col] == 0) 
            {
                return true;
            }
        }
    }
    return false;
}

bool solveSudoku() 
{
    int row, col;
    if (!findEmptyPosition(row, col)) 
    {
        return true;
    }

    for (int num = 1; num <= 9; num++) 
    {
        if (isValid(row, col, num)) 
        {
            grid[row][col] = num;
            if (solveSudoku()) 
            {
                return true;
            }
            grid[row][col] = 0; // Backtrack
        }
    }
    return false;
}

void printGrid() 
{
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            cout << grid[i][j] << " ";
        }

        cout << endl;
    }
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) 
    {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            inputFile >> grid[i][j];
        }
    }
    inputFile.close();

    if (solveSudoku()) 
    {
        printGrid();
        ofstream outputFile("output.txt");
        if (!outputFile) 
        {
            cerr << "Error opening output file." << endl;
            return 1;
        }

        for (int i = 0; i < N; i++) 
        {
            for (int j = 0; j < N; j++) 
            {
                outputFile << grid[i][j] << " ";
            }

            outputFile << endl;
        }

        outputFile.close();
    } 
    else 
    {
        cout << "No solution exists." << endl;
    }

    return 0;
}
