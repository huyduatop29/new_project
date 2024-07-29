// huytran

#include <iostream>
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

// Ð?nh nghia tr?ng thái c?a Koibik
struct State {
    string config;  // Tr?ng thái
    int moves;      // S? bu?c dã di chuy?n d? d?t du?c tr?ng thái này

    // Constructor
    State(string c, int m) : config(c), moves(m) {}
};

// Hàm ki?m tra xem m?t tr?ng thái có ph?i là tr?ng thái cu?i cùng không
bool isGoalState(const string& config, const string& goal) {
    return config == goal;
}

// Hàm xoay m?t m?t c?a Koibik
string rotateFace(const string& face, bool clockwise) {
    if (clockwise) {
        return face.substr(6, 2) + face.substr(0, 6);
    } else {
        return face.substr(2, 6) + face.substr(0, 2);
    }
}

// Hàm xoay Koibik
string rotateKoibik(const string& config, int faceIndex, bool clockwise) {
    string newConfig = config;

    for (int i = 0; i < 3; ++i) {
        swap(newConfig[faceIndex * 6 + i], newConfig[faceIndex * 6 + i + 3]);
    }

    newConfig.replace(faceIndex * 6, 6, rotateFace(newConfig.substr(faceIndex * 6, 6), clockwise));

    return newConfig;
}

// Hàm tìm du?ng di ng?n nh?t t? tr?ng thái ban d?u d?n tr?ng thái cu?i
int minMovesToGoal(const string& start, const string& goal) {
    queue<State> q;
    unordered_set<string> visited;

    q.push(State(start, 0));
    visited.insert(start);

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        if (isGoalState(current.config, goal)) {
            return current.moves;
        }

        for (int i = 0; i < 6; ++i) {
            q.push(State(rotateKoibik(current.config, i, true), current.moves + 1));
            q.push(State(rotateKoibik(current.config, i, false), current.moves + 1));
        }
    }

    // Không tìm th?y du?ng di
    return -1;
}

int main() {
    string start, goal;
    cin >> start >> goal;

    int result = minMovesToGoal(start, goal);

    if (result == -1) {
        cout << -1 << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}


