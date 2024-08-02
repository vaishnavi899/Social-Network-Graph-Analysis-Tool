# Social Network Graph Analysis Tool

## Description

This project is a Social Network Graph Analysis Tool developed in C++. It allows for the management and analysis of connections within a social network. The tool uses fundamental data structures and algorithms to perform various graph operations and provides insights into user connections and network structure.

## Features

- **Add and Remove Users**: Add new users to the network and remove existing users.
- **Create and Delete Connections**: Establish and remove connections between users.
- **Display Connections**: View all connections of a specific user.
- **Display All Users**: List all users currently in the network.
- **Mutual Connections**: Find and display mutual connections between two users.
- **Shortest Path**: Calculate and display the shortest path between two users using Breadth-First Search (BFS).
- **Degree Centrality**: Compute and display the degree centrality of a user to gauge their connectedness within the network.

## Usage

1. **Compile the Program**:
   Use a C++ compiler to compile the source code. For example:
   ```bash
   g++ -o SocialNetworkGraph SocialNetworkGraph.cpp
Interact with the Menu:
The program presents a menu with options:

1. Add User: Enter a user name to add to the network.
2. Remove User: Enter a user name to remove from the network.
3. Add Connection: Enter two user names to create a connection between them.
4. Remove Connection: Enter two user names to remove the connection between them.
5. Display Connections: Enter a user name to display their connections.
6. Display All Users: View a list of all users in the network.
7. Display Mutual Connections: Enter two user names to find mutual connections.
8. Find Shortest Path: Enter two user names to find and display the shortest path between them.
9. Display Degree Centrality: Enter a user name to view their degree centrality.
10. Exit: Exit the program.
