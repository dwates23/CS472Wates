#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

using Point = pair<int, int>;

int orientation(Point p, Point q, Point r) {
    int val = (q.second - p.second) * (r.first - q.first) -
              (q.first - p.first) * (r.second - q.second);

    if (val == 0) return 0;     
    return (val > 0) ? 1 : 2;    
}

bool comparePoints(Point p1, Point p2, Point reference) {
    int orientation_val = orientation(reference, p1, p2);
    if (orientation_val == 0)
        return (p1.first + p1.second) < (p2.first + p2.second);

    return (orientation_val == 2);
}

vector<Point>& convexHull(vector<Point>& pointsVector) {
    int n = pointsVector.size();
    if (n < 3) {
    return pointsVector;
}

int minIndex = 0;
for (int i = 1; i < n; i++) {
    if (pointsVector[i].second < pointsVector[minIndex].second ||
        (pointsVector[i].second == pointsVector[minIndex].second &&
         pointsVector[i].first < pointsVector[minIndex].first)) {
        minIndex = i;
    }
}

swap(pointsVector[0], pointsVector[minIndex]);

sort(pointsVector.begin() + 1, pointsVector.end(), [pointsVector](Point p1, Point p2) {
    return comparePoints(p1, p2, pointsVector[0]);
});

vector<Point> convexHullPoints;
convexHullPoints.push_back(pointsVector[0]);
convexHullPoints.push_back(pointsVector[1]);

for (int i = 2; i < n; i++) {
    while (convexHullPoints.size() > 1 &&
           orientation(convexHullPoints[convexHullPoints.size() - 2],
                       convexHullPoints[convexHullPoints.size() - 1],
                       pointsVector[i]) != 2) {
        convexHullPoints.pop_back();
    }
    convexHullPoints.push_back(pointsVector[i]);
}

pointsVector = convexHullPoints;
return pointsVector;
}

int main() 
{
vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
cout << "Original Points:" << endl;
for (const auto& point : points) {
    cout << "(" << point.first << ", " << point.second << ") ";
}
cout << endl;

convexHull(points);

cout << "Convex Hull Points:" << endl;
for (const auto& point : points) {
    cout << "(" << point.first << ", " << point.second << ") ";
}
cout << endl;

cout << "Press Enter to exit..." << endl;
getchar(); 

return 0;

}
