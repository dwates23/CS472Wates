#include <iostream>

bool isComposite(int n) {
    // Check successive integers from 2 to n/2 as possible divisors of n
    for (int i = 2; i <= n / 2; ++i) {
        // If the divisor being checked divides n evenly, return true (indicating n is composite)
        if (n % i == 0) {
            return true;
        }
    }
    // If no divisor divides n evenly, return false (indicating n is possibly prime)
    return false;
}

int main() {
    int num = 21;
    std::cout << "Is " << num << " a composite number? " << (isComposite(num) ? "Yes" : "No") << std::endl;
    return 0;
}
