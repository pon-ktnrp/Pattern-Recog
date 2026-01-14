#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
    int cluster; // 0, 1, or 2

    Point(double x = 0, double y = 0) : x(x), y(y), cluster(-1) {}
};

double distance(const Point& a, const Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// RENAMED VARIABLE HERE TO FIX THE ERROR
vector<Point> points;    
vector<Point> centroids; 

int main() {
    // 1. Hardcoding the Data Points (Renamed variable used here)
    points = {
        {1, 2}, {3, 3}, {2, 2}, 
        {8, 8}, {6, 6}, {7, 7}, 
        {-3, -3}, {-2, -4}, {-7, -7}
    };

    int K = 3; 

    // --- SETUP FOR T5 OR T6 ---
    // Uncomment the line for the specific problem you want to solve:
    
    // T5 Starting Centroids:
    // centroids = { {3, 3}, {2, 2}, {-3, -3} }; 
    
    // T6 Starting Centroids (Uncomment to run T6):
    centroids = { {-3, -3}, {2, 2}, {-7, -7} }; 

    cout << fixed << setprecision(2);
    bool converged = false;
    int iteration = 1;

    while (!converged) {
        cout << "--- Iteration " << iteration << " ---" << endl;
        converged = true; 

        // STEP 2: ASSIGN
        vector<vector<Point>> clusterPoints(K);
        // Loop over 'points' instead of 'data'
        for (auto& p : points) {
            int bestCluster = -1;
            double minDist = 1e9; 

            for (int i = 0; i < K; i++) {
                double d = distance(p, centroids[i]);
                if (d < minDist) {
                    minDist = d;
                    bestCluster = i;
                }
            }
            
            p.cluster = bestCluster;
            clusterPoints[bestCluster].push_back(p);
        }

        // Print Assignments
        for(int i=0; i<K; i++) {
            cout << "Cluster " << i << " (Centroid " << centroids[i].x << ", " << centroids[i].y << "): ";
            if(clusterPoints[i].empty()) {
                cout << "(Empty)";
            } else {
                for(auto p : clusterPoints[i]) cout << "(" << p.x << "," << p.y << ") ";
            }
            cout << endl;
        }

        // STEP 3: UPDATE
        for (int i = 0; i < K; i++) {
            if (clusterPoints[i].empty()) continue;

            double sumX = 0, sumY = 0;
            for (auto p : clusterPoints[i]) {
                sumX += p.x;
                sumY += p.y;
            }

            double newX = sumX / clusterPoints[i].size();
            double newY = sumY / clusterPoints[i].size();

            if (abs(newX - centroids[i].x) > 1e-6 || abs(newY - centroids[i].y) > 1e-6) {
                converged = false;
            }

            centroids[i].x = newX;
            centroids[i].y = newY;
        }

        cout << "Updated Centroids: ";
        for(auto c : centroids) cout << "(" << c.x << "," << c.y << ") ";
        cout << endl << endl;

        iteration++;
    }

    cout << "Converged!" << endl;
    return 0;
}