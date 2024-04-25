#include <iostream>
#include <vector>

std::vector<int> radixSort(std::vector<int>& arr) {
    // Find the maximum number to determine the number of digits
    int maxNum = *std::max_element(arr.begin(), arr.end());
    // Count the number of digits in the maximum number
    int maxDigits = std::to_string(maxNum).length();

    // Create 10 sublists (buckets) for each digit from 0 to 9
    std::vector<std::vector<int>> buckets(10);

    // Iterate through each digit from right to left
    for (int digitPlace = 0; digitPlace < maxDigits; digitPlace++) {
        // Place each number in the corresponding bucket based on the current digit
        for (int num : arr) {
            int digit = (num / static_cast<int>(pow(10, digitPlace))) % 10;
            buckets[digit].push_back(num);
        }

        // Traverse the buckets in sequential order and append each item into a list for the next pass
        arr.clear();
        for (auto& bucket : buckets) {
            arr.insert(arr.end(), bucket.begin(), bucket.end());
            bucket.clear();
        }
    }

    return arr;
}

int main() {
    std::vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    std::vector<int> sortedArr = radixSort(arr);

    std::cout << "Sorted array: ";
    for (int num : sortedArr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
