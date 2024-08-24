# Social Network Graph Analysis Tool

## Description

This project is a Social Network Graph Analysis Tool developed in C++. It allows for the management and analysis of connections within a social network. The tool employs fundamental data structures and algorithms to perform various graph operations, providing insights into user connections, network structure, and user influence within the network.

## Features

- **Add and Remove Users**: Add new users to the network, specify privacy settings, and remove existing users.
- **Create and Delete Connections**: Establish and remove connections between users with optional weights to represent the strength of the connection.
- **Display Connections**: View all connections of a specific user along with the connection weights.
- **Display All Users**: List all users currently in the network, showing their privacy status.
- **Mutual Connections**: Find and display mutual connections between two users.
- **Shortest Path**: Calculate and display the shortest path between two users using Breadth-First Search (BFS).
- **Degree Centrality**: Compute and display the degree centrality of a user to gauge their connectedness within the network.
- **Friend Suggestions**: Suggest friends for a user based on mutual connections.
- **Join Groups**: Allow users to join groups, making it easier to identify common interests.
- **Create Events**: Enable users to create events within the network.
- **Data Persistence**: Save the network state to a file and load it later to restore the state of the network.


https://github.com/user-attachments/assets/66e2caf9-d5f1-4726-be7b-ad925ff37b28


## Usage

### 1. Compile the Program

Use a C++ compiler to compile the source code. For example:

```bash
g++ -o SocialNetworkGraph SocialNetwork.cpp
```

### 2. Run the Program

Execute the compiled program:

```bash
./SocialNetworkGraph
```

### 3. Interact with the Menu

The program presents a menu with the following options:

1. **Add User**: Enter a user name to add to the network. You can specify whether the user profile is private.
2. **Remove User**: Enter a user name to remove from the network.
3. **Add Connection**: Enter two user names to create a connection between them, with an optional weight to indicate the strength of the connection.
4. **Remove Connection**: Enter two user names to remove the connection between them.
5. **Display Connections**: Enter a user name to display all their connections along with the connection weights.
6. **Display All Users**: View a list of all users in the network, including their privacy status.
7. **Display Mutual Connections**: Enter two user names to find and display their mutual connections.
8. **Find Shortest Path**: Enter two user names to find and display the shortest path between them.
9. **Display Degree Centrality**: Enter a user name to view their degree centrality.
10. **Suggest Friends**: Get friend suggestions for a user based on mutual connections.
11. **Join Group**: Enter a user name and group name to add the user to the specified group.
12. **Create Event**: Enter a user name and event name to create an event within the network.
13. **Save to File**: Save the current state of the network to a file for later use.
14. **Load from File**: Load the state of the network from a previously saved file.
15. **Exit**: Exit the program.

### 4. Data Persistence

To save the network state:

1. Select the "Save to File" option from the menu.
2. Enter the desired filename (e.g., `network_data.txt`).

To load the network state:

1. Select the "Load from File" option from the menu.
2. Enter the filename of the saved network state.

## Example Interaction

```text
Menu:
1. Add User
2. Remove User
3. Add Connection
4. Remove Connection
5. Display Connections
6. Display All Users
7. Display Mutual Connections
8. Find Shortest Path
9. Display Degree Centrality
10. Suggest Friends
11. Join Group
12. Create Event
13. Save to File
14. Load from File
15. Exit
Enter your choice:
```

Follow the on-screen prompts to interact with the program.

