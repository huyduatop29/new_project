// huytran

#include <iostream>
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

// �?nh nghia tr?ng th�i c?a Koibik
struct State {
    string config;  // Tr?ng th�i
    int moves;      // S? bu?c d� di chuy?n d? d?t du?c tr?ng th�i n�y

    // Constructor
    State(string c, int m) : config(c), moves(m) {}
};

// H�m ki?m tra xem m?t tr?ng th�i c� ph?i l� tr?ng th�i cu?i c�ng kh�ng
bool isGoalState(const string& config, const string& goal) {
    return config == goal;
}

// H�m xoay m?t m?t c?a Koibik
string rotateFace(const string& face, bool clockwise) {
    if (clockwise) {
        return face.substr(6, 2) + face.substr(0, 6);
    } else {
        return face.substr(2, 6) + face.substr(0, 2);
    }
}

// H�m xoay Koibik
string rotateKoibik(const string& config, int faceIndex, bool clockwise) {
    string newConfig = config;

    for (int i = 0; i < 3; ++i) {
        swap(newConfig[faceIndex * 6 + i], newConfig[faceIndex * 6 + i + 3]);
    }

    newConfig.replace(faceIndex * 6, 6, rotateFace(newConfig.substr(faceIndex * 6, 6), clockwise));

    return newConfig;
}

// H�m t�m du?ng di ng?n nh?t t? tr?ng th�i ban d?u d?n tr?ng th�i cu?i
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

    // Kh�ng t�m th?y du?ng di
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


