# Algorithms and Data Structures in C

A collection of data structures and algorithms implemented in C, developed while studying Algorithms and Programming at Politecnico di Torino.

The project focuses on practical implementation of fundamental programming concepts including dynamic memory management, linked data structures, binary search trees, graph traversal, recursion, and algorithmic problem solving.

## Topics

### Linked Lists
- Head and tail insertion
- Counting and summing elements
- List reversal
- Merging sorted lists
- List partitioning
- Node extraction
- List intersection
- Deleting occurrences
- Dynamic memory cleanup

### Doubly Linked Lists
- Node insertion
- Node deletion
- Forward and backward traversal
- List reversal
- Middle-node search

### Binary Search Trees
- Node insertion
- Search
- Tree traversal
- Node counting
- Tree height and level operations
- Range operations
- BST deletion
- Memory cleanup

### Graphs
- Adjacency-matrix representation
- Directed and undirected edges
- In-degree and out-degree
- Breadth-First Search (BFS)
- Depth-First Search (DFS)
- Reachability
- Unweighted shortest paths
- Distance calculations

### Dynamic Arrays
- Dynamic allocation
- Array copying
- Reverse copying
- Filtering
- Appending and removing elements
- In-place insertion and removal
- Ordered insertion

### Dynamic Matrices
- Dynamic 2D allocation
- Matrix initialization
- Deep copying
- Matrix filling
- Memory cleanup

### Strings
- Dynamic string copying
- Concatenation
- String reversal
- Removing spaces
- Extracting digits
- Dynamic arrays of strings
- Memory management

### Recursion
- Recursive binary search
- Decimal-to-binary conversion
- Recursive exponentiation
- Divide-and-conquer maximum
- Recursive character counting
- Recursive pattern generation

## Project Structure

```text
algorithms-data-structures-c/
├── linked_lists/
├── doubly_linked_lists/
├── trees/
├── graphs/
├── dynamic_arrays/
├── dynamic_matrices/
├── strings/
├── recursion/
├── main.c
├── CMakeLists.txt
└── README.md
```

Each module contains a `.c` implementation file and a corresponding `.h` header file.

## Build

The project uses CMake.

From the project directory:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Then run:

```bash
./algorithms_data_structures_c
```

## Purpose

This repository was created to consolidate and organize the C programming, algorithms, and data-structure concepts studied during my university coursework.

The implementations emphasize manual memory management, pointer manipulation, recursion, and understanding how fundamental data structures work internally.

## Language

- C