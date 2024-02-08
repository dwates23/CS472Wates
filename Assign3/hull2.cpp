#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib> 
#include <ctime>   

using namespace std;

using Point = pair<int, int>;

vector<Point>& convexHull(vector<Point>& pointsVector);

void generateRandomDataFile(const string& filename, int numPoints);

int main() 
{
    generateRandomDataFile("observations.txt", 100);

    vector<Point> observations;
    ifstream inputFile("observations.txt");
    int x, y;
    while (inputFile >> x >> y) 
    {
        observations.emplace_back(x, y);
    }
    inputFile.close();

    convexHull(observations);

    cout << "Convex Hull Points (Home Range):" << endl;
    for (const auto& point : observations) 
    {
        cout << "(" << point.first << ", " << point.second << ") ";
    }
    cout << endl;

    return 0;
}

void generateRandomDataFile(const string& filename, int numPoints) 
{
    srand(static_cast<unsigned>(time(nullptr)));
    ofstream outputFile(filename);

    for (int i = 0; i < numPoints; i++) 
    {
        int x = rand() % 1000; 
        int y = rand() % 1000; 
        outputFile << x << " " << y << endl;
    }

    outputFile.close();
}

vector<Point>& convexHull(vector<Point>& pointsVector) 
{
   
}
