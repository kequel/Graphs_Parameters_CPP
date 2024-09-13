# Graphs Parameters in C++

Graphs Parameters written in C++, developed as part of the Algorithms and Data Structures course in my second semester at Gdańsk University of Technology.

## Author
- Karolina Glaza [GitHub](https://github.com/kequel)

### Version
- Current version: **1.2**
- Upcoming version: **2.0** (In development: 4c. SLF method and an optimized solution for 5)

## Features
The program calculates the following parameters for each graph:

1. Degree sequence – the list of vertex degrees

2.  Number of connected components

3. Bipartiteness check – determines if the graph is bipartite

4. Vertex coloring (using consecutive natural numbers starting from 1) with the following algorithms:
   
- 4a. Greedy method

- 4b. Largest First (LF) method

5. Count of distinct C4 subgraphs

6. Number of edges in the graph’s complement


## Input and Output
### Input
In the first line there's a number `k` of graphs.

The following lines contain `k` graph data sets.

_A single data set contains a number `n` - the graph order - and `n` lists of neighbours for each vertex. A list contains the number of neighbours `s` and `s` neighbours IDs.
Neighbours IDs are numbers from 1 to `n`._

### Output
Print of k sets of responses. Each set contain the designated parameters in the order in which the parameters are listed. For point

1, 4 - sequence of `n` numbers

2, 3 - character `T` or `F` (true/false)

5, 6 - number.




