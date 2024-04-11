#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<pair<int, int>> solvePuzzle(int n, unordered_map<int, vector<pair<int, int>>>& memo) {
    if (n % 2 != 0) {
        return {};
    } else if (n == 2) {
        return {{0, 1}}; 
    }

    if (memo.find(n) != memo.end()) {
        return memo[n];
    }

    int minMoves = INT_MAX;
    vector<pair<int, int>> minMoveSeq;

    for (int i = 0; i < n - 1; ++i) {
        vector<pair<int, int>> moves = {{i, i + 2}};
        vector<pair<int, int>> remainingMoves = solvePuzzle(n - 2, memo);
        if (!remainingMoves.empty() && remainingMoves.size() < minMoves) {
            minMoves = remainingMoves.size();
            minMoveSeq = moves;
            for (auto& move : remainingMoves) {
                minMoveSeq.push_back({move.first + 2, move.second + 2});
            }
        }

        moves = {{i + 2, i}};
        remainingMoves = solvePuzzle(n - 2, memo);
        if (!remainingMoves.empty() && remainingMoves.size() < minMoves) {
            minMoves = remainingMoves.size();
            minMoveSeq = moves;
            for (auto& move : remainingMoves) {
                minMoveSeq.push_back({move.first + 2, move.second + 2});
            }
        }
    }

    memo[n] = minMoveSeq;
    return minMoveSeq;
}

int main() {
    unordered_map<int, vector<pair<int, int>>> memo;
    while (true) {
        int n;
        cout << "Enter an even number (or 0 to exit): ";
        cin >> n;
        if (n == 0) {
            cout << "Exiting program." << endl;
            break;
        } else if (n % 2 != 0) {
            cout << "Please enter an even number." << endl;
        } else {
            auto solution = solvePuzzle(n, memo);
            if (!solution.empty()) {
                cout << "Minimum number of moves needed to solve this puzzle: " << solution.size() << endl;
                cout << "Solution for n = " << n << endl;
                for (auto& move : solution) {
                    cout << "(" << move.first << ", " << move.second << ") ";
                }
                cout << endl;
            } else {
                cout << "There's no solution for n = " << n << endl;
            }
        }
    }

    return 0;
}
