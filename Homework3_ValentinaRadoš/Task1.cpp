#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <windows.h>

using namespace std;

struct Point {
    int row;
    int column;
};

bool check(int row, int colum) {
    if (row > 0 and row < 21 and colum > 0 and colum < 41) return true;
    else return false;
}

void print(const vector<vector<char>>& area, const Point& X, const Point& A, const Point& B) {
    system("cls");
    
    for (int i = 1; i <= 20; ++i) {
        for (int j = 1; j <= 40; ++j) {
            if (i == X.row and j == X.column) {
                cout << 'X';
            }
            else {
                cout << area[i][j];
            }
        }
        cout << endl;
    }
    cout << "Point A (" << A.row << ", " << A.column << "), POint B (" << B.row << ", " << B.column << "), POint X (" << X.row << ", " << X.column << ")" << endl;
}

vector<Point> bfs(const Point& A, const Point& B) {
   vector<vector<bool>> c(21, vector<bool>(41, false));
    vector<vector<Point>> d(21, vector<Point>(41, { -1, -1 }));
    const int move_R[] = { -1, 1, 0, 0 };
    const int move_C[] = { 0, 0, -1, 1 };
    queue<Point> q;

    q.push(A);
    c[A.row][A.column] = true;

    while (!q.empty()) {
        Point X = q.front();
        q.pop();

        if (X.row == B.row and X.column == B.column) {
           vector<Point> road;
            for (Point p = B; p.row != -1; p = d[p.row][p.column]) {
                road.push_back(p);
            }
            reverse(road.begin(), road.end());
            return road;
        }

        for (int i = 0; i < 4; ++i) {
            int new_R = X.row + move_R[i];
            int new_C = X.column + move_C[i];
            if (check(new_R, new_C) and !c[new_R][new_C]) {
                c[new_R][new_C] = true;
                d[new_R][new_C] = X;
                q.push({ new_R, new_C });
            }
        }
    }
    return vector<Point>();
}


int main() {
    Point A;
    Point B;

    cout << "Enter the row of A point (1 to 20): ";
    cin >> A.row;
    cout << "Enter the column of A point (1 to 40): ";
    cin >> A.column;
    cout << "Enter the row of B point (1 to 20): ";
    cin >> B.row;
    cout << "Enter the column of B point (1 to 40): ";
    cin >> B.column;

    if (!check(A.row, A.column) or !check(B.row, B.column)) {
        cout << endl;
        cout << "Points mot in range (row[1,20], column[1, 40])" << endl;
        return 1;
    }

    vector<vector<char>> area(21, vector<char>(41, '-')); //20+1, 40+1
    area[A.row][A.column] = 'A';
    area[B.row][B.column] = 'B';

    vector<Point> road = bfs(A, B);

    for (int i = 0; i < road.size(); ++i) {
        print(area, road[i], A,B);
        this_thread::sleep_for(chrono::milliseconds(100));
    }


    return 0;
}
