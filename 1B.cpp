#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

struct Node {
    vector<int> state;
    int g, h;

    bool operator<(const Node &other) const {
        return g + h > other.g + other.h;
    }
};

// Manhattan Distance
int heuristic(vector<int> s, vector<int> goal, int n) {
    int h = 0;

    for (int i = 0; i < n*n; i++) {
        if (s[i] == 0) continue;

        int pos = find(goal.begin(), goal.end(), s[i]) - goal.begin();

        h += abs(i/n - pos/n) + abs(i%n - pos%n);
    }
    return h;
}

// Check solvability
bool solvable(vector<int> start, vector<int> goal, int n) {
    int inv = 0;

    for (int i = 0; i < n*n; i++) {
        if (start[i] == 0) continue;

        for (int j = i+1; j < n*n; j++) {
            if (start[j] == 0) continue;

            int a = find(goal.begin(), goal.end(), start[i]) - goal.begin();
            int b = find(goal.begin(), goal.end(), start[j]) - goal.begin();

            if (a > b) inv++;
        }
    }

    if (n % 2 == 1)
        return inv % 2 == 0;

    int row1 = n - (find(start.begin(), start.end(), 0) - start.begin()) / n;
    int row2 = n - (find(goal.begin(), goal.end(), 0) - goal.begin()) / n;

    return (inv + row1) % 2 == row2 % 2;
}

// Display puzzle
void display(vector<int> s, int n) {
    for (int i = 0; i < n*n; i++) {
        if (s[i] == 0) cout << "_ ";
        else cout << s[i] << " ";

        if ((i+1) % n == 0) cout << endl;
    }
}

// A* Algorithm
void solve(vector<int> start, vector<int> goal, int n) {
    priority_queue<Node> pq;
    map<vector<int>, int> dist;
    map<vector<int>, vector<int>> parent;

    pq.push({start, 0, heuristic(start, goal, n)});
    dist[start] = 0;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        if (cur.g != dist[cur.state]) continue;

        if (cur.state == goal) {
            vector<vector<int>> path;
            vector<int> temp = goal;

            while (temp != start) {
                path.push_back(temp);
                temp = parent[temp];
            }

            path.push_back(start);
            reverse(path.begin(), path.end());

            cout << "\nSolution Found!\n";
            cout << "Minimum moves = " << path.size()-1 << endl;

            for (int i = 0; i < path.size(); i++) {
                cout << "\nStep " << i << ":\n";
                display(path[i], n);
            }
            return;
        }

        int pos = find(cur.state.begin(), cur.state.end(), 0) - cur.state.begin();
        int x = pos / n, y = pos % n;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx < 0 || ny < 0 || nx >= n || ny >= n)
                continue;

            vector<int> next = cur.state;
            swap(next[pos], next[nx*n + ny]);

            int newG = cur.g + 1;

            if (!dist.count(next) || newG < dist[next]) { //*************** */
                dist[next] = newG;
                parent[next] = cur.state;

                int newH = heuristic(next, goal, n);
                pq.push({next, newG, newH});
            }
        }
    }

    cout << "\nNo Solution Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n1. Solve N-Puzzle";
        cout << "\n2. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            int n;

            cout << "\nEnter N: ";
            cin >> n;

            if (n <= 0) {
                cout << "Invalid N!\n";
                continue;
            }

            vector<int> start(n*n), goal(n*n);

            cout << "Enter Initial State:\n";
            for (int i = 0; i < n*n; i++)
                cin >> start[i];

            cout << "Enter Goal State:\n";
            for (int i = 0; i < n*n; i++)
                cin >> goal[i];

            vector<int> a = start, b = goal;
            sort(a.begin(), a.end());
            sort(b.begin(), b.end());

            bool valid = true;
            for (int i = 0; i < n*n; i++) {
                if (a[i] != i || b[i] != i)
                    valid = false;
            }

            if (!valid) {
                cout << "Invalid Puzzle!\n";
            }
            else if (!solvable(start, goal, n)) {
                cout << "Puzzle is not solvable!\n";
            }
            else {
                solve(start, goal, n);
            }
        }
        else if (choice != 2) {
            cout << "Invalid Choice!\n";
        }

    } while (choice != 2);

    return 0;
}
