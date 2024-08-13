# Graph Data Structure Implementation
This project provides a C++ implementation of a graph data structure. The implementation includes both basic functionalities for manipulating graphs and advanced algorithms for pathfinding and component counting. The graph is represented using an adjacency list structure.

## Files in the Project

### 1. `graph.h`
This header file defines the `graph` class, which includes the following functionalities:

- **Basic Functions**:
  - `graph(bool search_using_bfs = true)`: Constructor that initializes the graph. The `search_using_bfs` parameter determines whether to use Breadth-First Search (BFS) or Dijkstra's algorithm for certain operations.
  - `void insert_vertex(int vertex)`: Adds a vertex to the graph.
  - `void insert_edge(int vertex1, int vertex2)`: Adds an edge between two vertices.
  - `void remove_vertex(int vertex)`: Removes a vertex from the graph.
  - `void remove_edge(int vertex1, int vertex2)`: Removes an edge between two vertices.
  
- **Extended Functions**:
  - `bool path_exists(int vertex1, int vertex2) const`: Checks if a path exists between two vertices.
  - `int shortest_path(int vertex1, int vertex2) const`: Finds the shortest path between two vertices.
  - `int* single_source_shortest_paths_bfs(int current_vertices[], int num_current_vertices = 1, int current_distance = 0, int shortest_paths[] = 0, bool print_flag = false) const`: Calculates the shortest paths from a source vertex using BFS.
  - `int* single_source_shortest_paths_dijkstra(int current_vertex, bool print_flag = false) const`: Calculates the shortest paths from a source vertex using Dijkstra's algorithm.
  - `int count_components() const`: Counts the number of connected components in the graph.

- **Debugging Functions**:
  - `void print_data() const`: Prints the graph's adjacency list and other debug information.
  - `int get_max_vertex() const`: Returns the maximum vertex value in the graph.
  - `int get_min_vertex() const`: Returns the minimum vertex value in the graph.

### 2. `graph.cpp`
This source file contains the implementation of the functions declared in `graph.h`. Key functions include:

- **Graph Constructor**: Initializes the graph and sets up the adjacency list.
- **Insertion/Removal of Vertices and Edges**: Manages adding and removing vertices and edges within the graph.
- **Pathfinding Algorithms**: Implements BFS and Dijkstra's algorithm to find the shortest paths between vertices.
- **Component Counting**: Uses BFS to count the number of connected components in the graph.
- **Debugging**: Implements functions to print the graph structure and other internal data.

### 3. `main.cpp`
This file serves as the entry point for the program. It contains:

- **Sample Graph Creation**: Creates a sample graph with predefined vertices and edges.
- **Function Testing**: Demonstrates the use of various graph functions, such as inserting vertices/edges, finding paths, and counting components.
- **Output**: Prints the results of operations like shortest path calculation and component counting to the console.
