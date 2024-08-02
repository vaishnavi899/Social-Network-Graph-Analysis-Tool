#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <queue>
#include <vector>
#include <algorithm> // Needed for std::reverse

using namespace std;

class SocialNetworkGraph {
private:
    unordered_map<string, unordered_set<string>> adjacencyList;

public:
    void addUser(const string& user) {
        if (adjacencyList.find(user) == adjacencyList.end()) {
            adjacencyList[user] = unordered_set<string>();
            cout << "User " << user << " added.\n";
        } else {
            cout << "User " << user << " already exists.\n";
        }
    }

    void removeUser(const string& user) {
        if (adjacencyList.find(user) != adjacencyList.end()) {
            adjacencyList.erase(user);
            for (auto& pair : adjacencyList) {
                pair.second.erase(user);
            }
            cout << "User " << user << " removed.\n";
        } else {
            cout << "User " << user << " does not exist.\n";
        }
    }

    void addConnection(const string& user1, const string& user2) {
        if (adjacencyList.find(user1) != adjacencyList.end() && adjacencyList.find(user2) != adjacencyList.end()) {
            adjacencyList[user1].insert(user2);
            adjacencyList[user2].insert(user1);
            cout << "Connection added between " << user1 << " and " << user2 << ".\n";
        } else {
            cout << "One or both users do not exist.\n";
        }
    }

    void removeConnection(const string& user1, const string& user2) {
        if (adjacencyList.find(user1) != adjacencyList.end() && adjacencyList.find(user2) != adjacencyList.end()) {
            adjacencyList[user1].erase(user2);
            adjacencyList[user2].erase(user1);
            cout << "Connection removed between " << user1 << " and " << user2 << ".\n";
        } else {
            cout << "One or both users do not exist.\n";
        }
    }

    void displayConnections(const string& user) const {
        if (adjacencyList.find(user) != adjacencyList.end()) {
            cout << "Connections of " << user << ": ";
            for (const auto& connection : adjacencyList.at(user)) {
                cout << connection << " ";
            }
            cout << "\n";
        } else {
            cout << "User " << user << " does not exist.\n";
        }
    }

    void displayMutualConnections(const string& user1, const string& user2) const {
        if (adjacencyList.find(user1) != adjacencyList.end() && adjacencyList.find(user2) != adjacencyList.end()) {
            cout << "Mutual connections between " << user1 << " and " << user2 << ": ";
            for (const auto& connection : adjacencyList.at(user1)) {
                if (adjacencyList.at(user2).find(connection) != adjacencyList.at(user2).end()) {
                    cout << connection << " ";
                }
            }
            cout << "\n";
        } else {
            cout << "One or both users do not exist.\n";
        }
    }

    vector<string> shortestPath(const string& start, const string& end) {
        unordered_map<string, string> predecessors;
        unordered_map<string, bool> visited;
        queue<string> q;

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            string current = q.front();
            q.pop();

            if (current == end) {
                vector<string> path;
                for (string at = end; at != ""; at = predecessors[at]) {
                    path.push_back(at);
                }
                reverse(path.begin(), path.end());
                return path;
            }

            for (const auto& neighbor : adjacencyList[current]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                    predecessors[neighbor] = current;
                }
            }
        }

        return {}; // Return an empty path if no path exists
    }

    void displayDegreeCentrality(const string& user) const {
        if (adjacencyList.find(user) != adjacencyList.end()) {
            cout << "Degree centrality of " << user << ": " << adjacencyList.at(user).size() << "\n";
        } else {
            cout << "User " << user << " does not exist.\n";
        }
    }

    void displayAllUsers() const {
        cout << "All users in the social network:\n";
        for (const auto& pair : adjacencyList) {
            cout << pair.first << "\n";
        }
    }
};

int main() {
    SocialNetworkGraph network;
    int choice;
    string user1, user2;

    while (true) {
        cout << "Menu:\n";
        cout << "1. Add User\n";
        cout << "2. Remove User\n";
        cout << "3. Add Connection\n";
        cout << "4. Remove Connection\n";
        cout << "5. Display Connections\n";
        cout << "6. Display All Users\n";
        cout << "7. Display Mutual Connections\n";
        cout << "8. Find Shortest Path\n";
        cout << "9. Display Degree Centrality\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Clear input buffer to avoid issues with getline after cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "Enter user name to add: ";
                cin >> user1;
                network.addUser(user1);
                break;
            case 2:
                cout << "Enter user name to remove: ";
                cin >> user1;
                network.removeUser(user1);
                break;
            case 3:
                cout << "Enter first user name: ";
                cin >> user1;
                cout << "Enter second user name: ";
                cin >> user2;
                network.addConnection(user1, user2);
                break;
            case 4:
                cout << "Enter first user name: ";
                cin >> user1;
                cout << "Enter second user name: ";
                cin >> user2;
                network.removeConnection(user1, user2);
                break;
            case 5:
                cout << "Enter user name to display connections: ";
                cin >> user1;
                network.displayConnections(user1);
                break;
            case 6:
                network.displayAllUsers();
                break;
            case 7:
                cout << "Enter first user name: ";
                cin >> user1;
                cout << "Enter second user name: ";
                cin >> user2;
                network.displayMutualConnections(user1, user2);
                break;
            case 8:
                cout << "Enter start user name: ";
                cin >> user1;
                cout << "Enter end user name: ";
                cin >> user2;
                {
                    vector<string> path = network.shortestPath(user1, user2);
                    if (path.empty()) {
                        cout << "No path exists between " << user1 << " and " << user2 << ".\n";
                    } else {
                        cout << "Shortest path: ";
                        for (const string& user : path) {
                            cout << user << " ";
                        }
                        cout << "\n";
                    }
                }
                break;
            case 9:
                cout << "Enter user name to display degree centrality: ";
                cin >> user1;
                network.displayDegreeCentrality(user1);
                break;
            case 10:
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
