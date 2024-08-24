#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <limits>
#include <set>
#include <map>

using namespace std;

class SocialNetworkGraph {
private:
    struct User {
        unordered_map<string, int> connections; // Connection with weights
        bool isPrivate = false; // Privacy setting
        vector<string> groups; // Groups user is part of
    };

    unordered_map<string, User> adjacencyList;

public:
    void addUser(const string& user, bool isPrivate = false) {
        if (adjacencyList.find(user) == adjacencyList.end()) {
            adjacencyList[user] = User{unordered_map<string, int>(), isPrivate};
            cout << "User " << user << " added.\n";
        } else {
            cout << "User " << user << " already exists.\n";
        }
    }

    void removeUser(const string& user) {
        if (adjacencyList.find(user) != adjacencyList.end()) {
            adjacencyList.erase(user);
            for (auto& pair : adjacencyList) {
                pair.second.connections.erase(user);
            }
            cout << "User " << user << " removed.\n";
        } else {
            cout << "User " << user << " does not exist.\n";
        }
    }

    void addConnection(const string& user1, const string& user2, int weight = 1) {
        if (adjacencyList.find(user1) != adjacencyList.end() && adjacencyList.find(user2) != adjacencyList.end()) {
            adjacencyList[user1].connections[user2] = weight;
            adjacencyList[user2].connections[user1] = weight;
            cout << "Connection added between " << user1 << " and " << user2 << " with weight " << weight << ".\n";
        } else {
            cout << "One or both users do not exist.\n";
        }
    }

    void removeConnection(const string& user1, const string& user2) {
        if (adjacencyList.find(user1) != adjacencyList.end() && adjacencyList.find(user2) != adjacencyList.end()) {
            adjacencyList[user1].connections.erase(user2);
            adjacencyList[user2].connections.erase(user1);
            cout << "Connection removed between " << user1 << " and " << user2 << ".\n";
        } else {
            cout << "One or both users do not exist.\n";
        }
    }

    void displayConnections(const string& user) const {
        if (adjacencyList.find(user) != adjacencyList.end()) {
            cout << "Connections of " << user << ": ";
            for (const auto& connection : adjacencyList.at(user).connections) {
                cout << connection.first << "(Weight: " << connection.second << ") ";
            }
            cout << "\n";
        } else {
            cout << "User " << user << " does not exist.\n";
        }
    }

    void displayMutualConnections(const string& user1, const string& user2) const {
        if (adjacencyList.find(user1) != adjacencyList.end() && adjacencyList.find(user2) != adjacencyList.end()) {
            cout << "Mutual connections between " << user1 << " and " << user2 << ": ";
            for (const auto& connection : adjacencyList.at(user1).connections) {
                if (adjacencyList.at(user2).connections.find(connection.first) != adjacencyList.at(user2).connections.end()) {
                    cout << connection.first << " ";
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

            for (const auto& neighbor : adjacencyList[current].connections) {
                if (!visited[neighbor.first]) {
                    q.push(neighbor.first);
                    visited[neighbor.first] = true;
                    predecessors[neighbor.first] = current;
                }
            }
        }

        return {}; // Return an empty path if no path exists
    }

    void displayDegreeCentrality(const string& user) const {
        if (adjacencyList.find(user) != adjacencyList.end()) {
            cout << "Degree centrality of " << user << ": " << adjacencyList.at(user).connections.size() << "\n";
        } else {
            cout << "User " << user << " does not exist.\n";
        }
    }

    void displayAllUsers() const {
        cout << "All users in the social network:\n";
        for (const auto& pair : adjacencyList) {
            cout << pair.first << " (Private: " << (pair.second.isPrivate ? "Yes" : "No") << ")\n";
        }
    }

    void suggestFriends(const string& user) const {
        if (adjacencyList.find(user) == adjacencyList.end()) {
            cout << "User " << user << " does not exist.\n";
            return;
        }
        
        unordered_map<string, int> suggestionCount;
        for (const auto& friendName : adjacencyList.at(user).connections) {
            for (const auto& potentialFriend : adjacencyList.at(friendName.first).connections) {
                if (potentialFriend.first != user && adjacencyList.at(user).connections.find(potentialFriend.first) == adjacencyList.at(user).connections.end()) {
                    suggestionCount[potentialFriend.first]++;
                }
            }
        }

        vector<pair<string, int>> suggestions(suggestionCount.begin(), suggestionCount.end());
        sort(suggestions.begin(), suggestions.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        cout << "Friend suggestions for " << user << ":\n";
        for (const auto& suggestion : suggestions) {
            cout << suggestion.first << " (Mutual friends: " << suggestion.second << ")\n";
        }
    }

    void joinGroup(const string& user, const string& groupName) {
        if (adjacencyList.find(user) != adjacencyList.end()) {
            adjacencyList[user].groups.push_back(groupName);
            cout << user << " joined group " << groupName << ".\n";
        } else {
            cout << "User " << user << " does not exist.\n";
        }
    }

    void createEvent(const string& user, const string& eventName) {
        if (adjacencyList.find(user) != adjacencyList.end()) {
            // In a real application, you might want to create an Event class or structure
            cout << user << " created event " << eventName << ".\n";
        } else {
            cout << "User " << user << " does not exist.\n";
        }
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        for (const auto& user : adjacencyList) {
            file << user.first << ":";
            for (const auto& connection : user.second.connections) {
                file << connection.first << "," << connection.second << ";";
            }
            file << (user.second.isPrivate ? "private" : "public") << ",";
            for (const auto& group : user.second.groups) {
                file << group << ",";
            }
            file << "\n";
        }
        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string user, connections, privacy, groups;
            getline(ss, user, ':');
            addUser(user);
            getline(ss, connections, ',');
            stringstream css(connections);
            string conn;
            while (getline(css, conn, ';')) {
                if (!conn.empty()) {
                    stringstream cstream(conn);
                    string friendName;
                    int weight;
                    getline(cstream, friendName, ',');
                    cstream >> weight;
                    addConnection(user, friendName, weight);
                }
            }
            getline(ss, privacy, ',');
            adjacencyList[user].isPrivate = (privacy == "private");
            while (getline(ss, groups, ',')) {
                if (!groups.empty()) {
                    joinGroup(user, groups);
                }
            }
        }
        file.close();
    }
};

int main() {
    SocialNetworkGraph network;
    int choice;
    string user1, user2, groupName, eventName;
    int weight;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add User\n";
        cout << "2. Remove User\n";
        cout << "3. Add Connection\n";
        cout << "4. Remove Connection\n";
        cout << "5. Display Connections\n";
        cout << "6. Display Mutual Connections\n";
        cout << "7. Find Shortest Path\n";
        cout << "8. Display Degree Centrality\n";
        cout << "9. Display All Users\n";
        cout << "10. Suggest Friends\n";
        cout << "11. Join Group\n";
        cout << "12. Create Event\n";
        cout << "13. Save Network to File\n";
        cout << "14. Load Network from File\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter user name: ";
            cin >> user1;
            network.addUser(user1);
            break;
        case 2:
            cout << "Enter user name: ";
            cin >> user1;
            network.removeUser(user1);
            break;
        case 3:
            cout << "Enter first user name: ";
            cin >> user1;
            cout << "Enter second user name: ";
            cin >> user2;
            cout << "Enter connection weight: ";
            cin >> weight;
            network.addConnection(user1, user2, weight);
            break;
        case 4:
            cout << "Enter first user name: ";
            cin >> user1;
            cout << "Enter second user name: ";
            cin >> user2;
            network.removeConnection(user1, user2);
            break;
        case 5:
            cout << "Enter user name: ";
            cin >> user1;
            network.displayConnections(user1);
            break;
        case 6:
            cout << "Enter first user name: ";
            cin >> user1;
            cout << "Enter second user name: ";
            cin >> user2;
            network.displayMutualConnections(user1, user2);
            break;
        case 7:
            cout << "Enter start user name: ";
            cin >> user1;
            cout << "Enter end user name: ";
            cin >> user2;
            {
                vector<string> path = network.shortestPath(user1, user2);
                if (!path.empty()) {
                    cout << "Shortest path from " << user1 << " to " << user2 << ": ";
                    for (const string& user : path) {
                        cout << user << " ";
                    }
                    cout << "\n";
                } else {
                    cout << "No path exists between " << user1 << " and " << user2 << ".\n";
                }
            }
            break;
        case 8:
            cout << "Enter user name: ";
            cin >> user1;
            network.displayDegreeCentrality(user1);
            break;
        case 9:
            network.displayAllUsers();
            break;
        case 10:
            cout << "Enter user name: ";
            cin >> user1;
            network.suggestFriends(user1);
            break;
        case 11:
            cout << "Enter user name: ";
            cin >> user1;
            cout << "Enter group name: ";
            cin >> groupName;
            network.joinGroup(user1, groupName);
            break;
        case 12:
            cout << "Enter user name: ";
            cin >> user1;
            cout << "Enter event name: ";
            cin >> eventName;
            network.createEvent(user1, eventName);
            break;
        case 13:
            cout << "Enter file name to save network: ";
            cin >> eventName;
            network.saveToFile(eventName);
            break;
        case 14:
            cout << "Enter file name to load network: ";
            cin >> eventName;
            network.loadFromFile(eventName);
            break;
        case 0:
            return 0;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    }
    return 0;
}
