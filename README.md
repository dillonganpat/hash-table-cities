# Hash Table — World Cities 🌍

C++ program that stores 1030 world cities in a hash table using chaining for collision resolution, supporting insertion, search, deletion, and statistics.

## Features
- Hash table implemented with linked list chaining
- Custom hash function based on character position weighting
- Insert, search, and delete cities by name
- Displays chain length at any hash location
- Statistics — total elements, filled/empty locations, longest chain
- Command-driven execution from a commands file
- Full memory cleanup on exit

## Tech Stack
C++ · Hash Tables · Linked Lists · Collision Resolution · File I/O

## 🚀 Run
```bash
g++ Assignment3.cpp HashTable.cpp -o hashtable
./hashtable
```

Ensure `WorldCities.txt` and `Commands.txt` are in the same directory.
