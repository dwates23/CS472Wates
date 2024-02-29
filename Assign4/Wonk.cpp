#include <iostream>
#include <string>
using namespace std;

string sortCandies(string candies) 
{
    int red = 0;
    int white = 0; 
    int blue = candies.length() - 1;
    while (white <= blue) 
    {
        if (candies[white] == 'r') 
        {
            swap(candies[red], candies[white]);
            red++;
            white++;

        } 
        
        else if (candies[white] == 'w') 
        {
            white++;
        } 
        
        else 
        {
            swap(candies[white], candies[blue]);
            blue--;
        }
    }
    return candies;
}

int main() 
{
    string candies = "rwbwbrwrwb";
    cout << "Original string: " << candies << endl;
    string sortedCandies = sortCandies(candies);
    cout << "Sorted string: " << sortedCandies << endl;
    return 0;
}
