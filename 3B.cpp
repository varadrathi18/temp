#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int n, m;
vector<string> cities;
vector<vector<int>> graph;
vector<int> color;

// Check if color is safe
bool isSafe(int city, int c)
{
    for (int i = 0; i < n; i++)
    {
        if (graph[city][i] == 1 && color[i] == c)
            return false;
    }
    return true;
}

// CSP Backtracking
bool solve(int city, int maxColors)
{
    if (city == n)
        return true;

    for (int c = 1; c <= maxColors; c++)
    {
        if (isSafe(city, c))
        {
            color[city] = c;

            if (solve(city + 1, maxColors))
                return true;

            color[city] = 0;
        }
    }

    return false;
}

// Enter cities and connections
void enterCities()
{
    cout << "\nEnter number of cities: ";
    cin >> n;

    cities.resize(n);
    graph.assign(n, vector<int>(n, 0));
    color.assign(n, 0);

    cout << "\nEnter city names:\n";

    for (int i = 0; i < n; i++)
    {
        cout << "City " << i + 1 << ": ";
        cin >> cities[i];
    }

    cout << "\nEnter number of connections: ";
    cin >> m;

    cout << "\nEnter connected city pairs:\n";

    for (int i = 0; i < m; i++)
    {
        string a, b;
        cout << "Connection " << i + 1 << ": ";
        cin >> a >> b;

        int u = -1, v = -1;

        for (int j = 0; j < n; j++)
        {
            if (cities[j] == a) u = j;
            if (cities[j] == b) v = j;
        }

        if (u != -1 && v != -1 && u != v)
        {
            graph[u][v] = 1;
            graph[v][u] = 1;
        }
        else
        {
            cout << "Invalid city names or connection!\n";
            i--;
        }
    }

    cout << "\nCities and connections saved successfully!\n";
}

// Display map coloring
void displayColoring()
{
    if (n == 0)
    {
        cout << "Please enter cities first!\n";
        return;
    }

    bool found = false;

    for (int k = 1; k <= n; k++)
    {
        fill(color.begin(), color.end(), 0);

        if (solve(0, k))
        {
            cout << "\n===== COLORING RESULT =====\n";

            string colors[] = {
                "Red", "Green", "Blue", "Yellow",
                "Orange", "Purple", "Pink", "Cyan",
                "Brown", "Violet"
            };

            for (int i = 0; i < n; i++)
            {
                cout << cities[i] << " -> ";

                if (color[i] <= 10)
                    cout << colors[color[i] - 1];
                else
                    cout << "Color " << color[i];

                cout << endl;
            }

            cout << "\nChromatic Number = " << k << endl;

            found = true;
            break;
        }
    }

    if (!found)
        cout << "No valid coloring found!\n";
}

// Main function
int main()
{
    int choice;

    do
    {
        cout << "\n===== MAP COLORING USING CSP =====\n";
        cout << "1. Enter Cities and Connections\n";
        cout << "2. Display Map Coloring\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                enterCities();
                break;

            case 2:
                displayColoring();
                break;

            case 3:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 3);

    return 0;
}
