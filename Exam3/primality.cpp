#include <iostream>
using namespace std;

bool composite(int n) 
{
    for (int i = 2; i <= n / 2; ++i) 
    {
        if (n % i == 0) 
        {
            return true;
        }
    }
    return false;
}

int main() 
{
    int num = 21;
    cout << "Is " << num << " a composite number? " << (composite(num) ? "Yes it is" : "No it is not") << endl;
    return 0;
}
