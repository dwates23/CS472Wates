#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

vector<int> sorter(vector<int>& arr) 
{
    int maxNum = *max_element(arr.begin(), arr.end());
    int maxDigits = to_string(maxNum).length();
    vector<vector<int>> buckets(10);

    for (int digitPlace = 0; digitPlace < maxDigits; digitPlace++) 
    {
        for (int num : arr) 
        {
            int digit = (num / static_cast<int>(pow(10, digitPlace))) % 10;
            buckets[digit].push_back(num);
        }

        arr.clear();
        for (auto& bucket : buckets) 
        {
            arr.insert(arr.end(), bucket.begin(), bucket.end());
            bucket.clear();
        }
    }

    return arr;
}

int main() 
{
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    vector<int> sorted = sorter(arr);

    cout << "Sorted array: ";
    for (int num : sorted) 
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
