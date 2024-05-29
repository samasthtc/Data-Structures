# 👨‍💻 Data Structures Course Projects

This repository contains two projects developed for the Data Structures and Algorithms course (COMP2421). Each project demonstrates the implementation of various data structures and algorithms.

## Table of Contents

- [👨‍💻 Data Structures Course Projects](#-data-structures-course-projects)
  - [Table of Contents](#table-of-contents)
  - [Projects Overview](#projects-overview)
    - [Project 1: World Cup Teams Management System](#project-1-world-cup-teams-management-system)
    - [Project 2: Pharmacy Management System](#project-2-pharmacy-management-system)
  - [Setup and Usage](#setup-and-usage)
    - [Prerequisites](#prerequisites)
    - [Building and Running the Projects](#building-and-running-the-projects)
  - [Project Details](#project-details)
    - [Project 1: Detailed Description](#project-1-detailed-description)
    - [Project 2: Detailed Description](#project-2-detailed-description)

## Projects Overview

### Project 1: World Cup Teams Management System

This project involves developing a system to manage World Cup teams and match results. The system uses a linked list and a queue to organize teams and players, respectively.

**Features:**

1. Read team information from a file and store it in a linked list.
2. Calculate and store the points for each team.
3. Sort the teams based on points using Radix Sort.
4. Add, modify, and delete team information.
5. Create and manage matches between teams.
6. Manage players within teams, including handling substitutions and red cards.
7. Save updated information back to files.

**Files:**

- `teams.txt`: Contains team information.
- `players.txt`: Contains player information for each team.
- `teamsInfo.txt`: File to save sorted team information.
- `playersInfo.txt`: File to save updated player information.

### Project 2: Pharmacy Management System

This project involves building a system to maintain information about medicines for a pharmacy using a Binary Search Tree (BST) and a Hash Table.

**Features:**

1. Read medicine information from a file and create a BST.
2. Insert, update, and delete medicine records.
3. List medicines in alphabetical order or by category.
4. Save information to a file.
5. Create a Hash Table from the BST data and perform various operations on it.

**Files:**

- `Meds.txt`: Contains initial medicine information.
- `Pharmacy.txt`: File to save updated pharmacy information.

## Setup and Usage

### Prerequisites

- C Compiler (e.g., GCC)
- Make (optional, if using a Makefile)

### Building and Running the Projects

1. Navigate to  either one of `Project1` or `Project2` directories.
2. Compile the project using the C compiler:
   ```sh
   make
   ```

3. Run the executable:
   ```sh
   make run
   ```

## Project Details

### Project 1: Detailed Description

The World Cup Teams Management System involves two phases:

- **Phase One:** Manage team information using a linked list. Calculate and sort points, and provide functionality to add, modify, delete, and print team information.
- **Phase Two:** Manage matches and players. Store player information in linked lists and queues, handle substitutions, and manage red cards.

### Project 2: Detailed Description

The Pharmacy Management System consists of:

- **BST Implementation:** Read and store medicine data in a BST. Provide functionalities to manage and query the data.
- **Hash Table Implementation:** Create a Hash Table from the BST data and provide various operations including insert, search, and delete.
