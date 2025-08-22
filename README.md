# Homework Assignments: Linked List and Hash Table in C++

## Project Overview
This repository contains two homework assignments focused on implementing custom data structures in C++:

1. **Linked List (List)**
   - Implemented as a doubly linked list with support for insertion, deletion, sorting, and element access.
   - List elements are represented by the classes `Package` and `PackOfCoins`, which store information about name, price, size, and computed value.
   - Iterator support for sequential traversal of elements.
   - Methods for reading from and writing to files.

2. **Hash Table (HTable)**
   - Template class `HTable<K, V>` implements a hash table with collision resolution using chaining (linked lists).
   - Supports core operations: insertion, deletion, search, and key existence check.
   - Overloaded `[]` and `==` operators for convenient access and table comparison.
   - Methods for saving and loading the table from a file.
   - Automatic resizing to maintain efficiency when needed.

## Key Technologies
- **Language:** C++ (C++11 standard or higher)
- **Libraries:** `<vector>`, `<string>`, `<fstream>`, `<functional>`
- **Data Structures:**
  - Doubly linked list
  - Hash table with chaining
- **File Handling:** Reading and writing element data for testing and state persistence.

## Methods and Functionality
### List
- `add(Package*)` — Adds an element to the end of the list.
- `insertBetween(Package*, int, int)` — Inserts an element between two positions.
- `insertWSort(Package*)` — Inserts an element maintaining sorted order by value.
- `del(int)` — Deletes an element by position.
- `sort()` — Sorts elements by value.
- `fromFile(string)` and `toFile(string)` — Loads and saves data.
- `Iterator` — Class for sequential traversal of the list.

### HTable
- `insert(K, V)` — Inserts a key-value pair.
- `removePair(K)` — Removes a pair by key.
- `inTable(K)` — Checks if a key exists.
- `operator[](K)` — Accesses a value by key.
- `operator==` — Compares two tables.
- `toFile(string)` and `fromFile(string)` — Saves and loads table data.
- Automatic table resizing to reduce collisions.

