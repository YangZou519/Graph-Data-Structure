#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <algorithm>

#include "graph.h"

graph::graph(bool search_with_bfs) {
    min_vertex = 0;
    max_vertex = 0;
    number_of_vertices = 0;
    search_using_bfs = search_with_bfs; // if true, use BFS; if false, use DFS
}

void graph::insert_vertex(int vertex) {
    int lower_range_addition = 0;
    int upper_range_addition = 0;
    int** temp_adjacency_list;
    int* temp_secondary_array_lengths;

    // adjust min_vertex and max_vertex
    if (min_vertex == 0) {
        min_vertex = vertex;
    }
    if (max_vertex == 0) {
        max_vertex = vertex;
    }
    if (vertex < min_vertex) {
        lower_range_addition = min_vertex - vertex;
        min_vertex = vertex;
    }
    if (vertex > max_vertex) {
        upper_range_addition = vertex - max_vertex;
        max_vertex = vertex;
    }

    // increment number of vertices
    number_of_vertices++;

    // rebuild direct access array that points into subarrays
    if (number_of_vertices==1) {
        // this is our first vertex, and our first direct access array
        adjacency_list = new int*[number_of_vertices];
        adjacency_list[0] = new int[1];
        adjacency_list[0][0] = vertex;
        // update secondary_array_lengths
        secondary_array_lengths = new int[number_of_vertices];
        secondary_array_lengths[0] = 1;
    } else {
        if (lower_range_addition > 0 || upper_range_addition > 0) {
            // we'll need to copy over all existing information from the previous direct access array

            // adjacency_list first
            temp_adjacency_list = new int*[max_vertex - min_vertex + 1];
            if (lower_range_addition==0) {
                for (int i = 0; i < (max_vertex - min_vertex + 1 - upper_range_addition); i++) {
                    temp_adjacency_list[i] = adjacency_list[i];
                }
                for (int j = (max_vertex - min_vertex + 1 - upper_range_addition); j < (max_vertex - min_vertex + 1); j++) {
                    temp_adjacency_list[j] = 0;
                }
            } else if (upper_range_addition==0) {
                for (int i = 0; i < lower_range_addition; i++) {
                    temp_adjacency_list[i] = 0;
                }
                for (int j = lower_range_addition; j < (max_vertex - min_vertex + 1); j++) {
                    temp_adjacency_list[j + lower_range_addition] = adjacency_list[j];
                }
            }
            adjacency_list = temp_adjacency_list;

            // now secondary_array_lengths
            temp_secondary_array_lengths = new int[max_vertex - min_vertex + 1];
            if (lower_range_addition > 0) {
                for (int i = 0; i < lower_range_addition; i++) {
                    temp_secondary_array_lengths[i] = 0;
                }
                for (int j = lower_range_addition; j < (max_vertex - min_vertex + 1); j++) {
                    temp_secondary_array_lengths[j + lower_range_addition] = secondary_array_lengths[j];
                }
            } else if (upper_range_addition > 0) {
                for (int i = 0; i < (max_vertex - min_vertex + 1 - upper_range_addition); i++) {
                    temp_secondary_array_lengths[i] = secondary_array_lengths[i];
                }
                for (int j = (max_vertex - min_vertex + 1 - upper_range_addition); j < (max_vertex - min_vertex + 1); j++) {
                    temp_secondary_array_lengths[j] = 0;
                }
            }
            secondary_array_lengths = temp_secondary_array_lengths;
        }
        // add our new vertex
        adjacency_list[vertex - min_vertex] = new int[1];
        adjacency_list[vertex - min_vertex][0] = vertex;
        secondary_array_lengths[vertex - min_vertex] = 1;
    }
}

void graph::insert_edge(int vertex1, int vertex2) {
    // first, confirm these vertices are in the graph
    if (secondary_array_lengths[vertex1 - min_vertex]==0 || secondary_array_lengths[vertex2 - min_vertex]==0 ) {
        std::cout << "At least one of vertices " << vertex1 << " and " << vertex2 << " does not exist." << std::endl;
    } else {
        // vertices are in the graph; now just modify the adjacency_list and secondary_array_lengths
        adjacency_list[vertex1-min_vertex][ secondary_array_lengths[vertex1-min_vertex] ] = vertex2;
        secondary_array_lengths[vertex1-min_vertex]++;
        adjacency_list[vertex2-min_vertex][ secondary_array_lengths[vertex2-min_vertex] ] = vertex1;
        secondary_array_lengths[vertex2-min_vertex]++;
    }
}

void graph::remove_vertex(int vertex) {
    // we're only going to remove the vertex itself, not records of edges pointing to the vertex from other vertices
    adjacency_list[vertex - min_vertex] = 0;
    secondary_array_lengths[vertex - min_vertex] = 0;
}

void graph::remove_edge(int vertex1, int vertex2) {
    for (int i = 0; i < secondary_array_lengths[vertex1 - min_vertex]; i++) {
        if (adjacency_list[vertex1 - min_vertex][i] == vertex2) {
            adjacency_list[vertex1 - min_vertex][i] = adjacency_list[vertex1 - min_vertex][ secondary_array_lengths[vertex1 - min_vertex] - 1 ];
            secondary_array_lengths[vertex1 - min_vertex]--;
        }
    }

    for (int i = 0; i < secondary_array_lengths[vertex2 - min_vertex]; i++) {
        if (adjacency_list[vertex2 - min_vertex][i] == vertex1) {
            adjacency_list[vertex2 - min_vertex][i] = adjacency_list[vertex2 - min_vertex][ secondary_array_lengths[vertex2 - min_vertex] - 1 ];
            secondary_array_lengths[vertex2 - min_vertex]--;
        }
    }
}


// This routine is a subset of graph::shortest_path().
// We will call graph::shortest_path() and just read our answer from its output.
bool graph::path_exists(int vertex1, int vertex2) const {
    // Create an array with the source vertex
    int layer_0[1] = {vertex1};
    // Choose BFS or Dijkstra based on the search_using_bfs flag to find shortest paths
    int* shortest_paths = search_using_bfs ? single_source_shortest_paths_bfs(layer_0, 1, 0, nullptr, false)
                                           : single_source_shortest_paths_dijkstra(vertex1, false);
    // Check if the path exists by verifying the shortest path value
    bool exists = shortest_paths[vertex2 - min_vertex] != INT_MAX;
    delete[] shortest_paths; // Free allocated memory
    return exists; // Return whether the path exists
}


// This routine is a subset of graph::single_source_shortest_paths().
// We will call graph::single_source_shortest_paths() and just read our answer from its output.
int graph::shortest_path(int vertex1, int vertex2) const {
    // Create an array with the source vertex
    int layer_0[1] = {vertex1};
    // Choose BFS or Dijkstra based on the search_using_bfs flag to find shortest paths
    int* shortest_paths = search_using_bfs ? single_source_shortest_paths_bfs(layer_0, 1, 0, nullptr, false)
                                           : single_source_shortest_paths_dijkstra(vertex1, false);
    // Get the shortest path length
    int path_length = shortest_paths[vertex2 - min_vertex];
    delete[] shortest_paths; // Free allocated memory
    return path_length == INT_MAX ? -1 : path_length; // Return the path length or -1 if no path exists
}


/*
This function should call itself recursively.

The idea is that, on the first call, current_level_vertices will be a single-member array
containing only the source vertex.

All subsequent calls will be made by passing in the next "level" of vertices in as
current_level_vertices. (See the lecture slides on graphs for that graph I created with the levels
highlighted - the source node is one color, the source's neighbors are another color, and those
nodes' neighbors are a third color, etc.)

Parameters:
current_level_vertices - all vertices in the current "level"
num_current_vertices - number of vertices in current_level_vertices
current_distance - distance of current level from source
shortest_paths - array containing shortest known paths from source to all vertices in the graph
print_flag - boolean flag indicating whether we want to print out all the shortest paths
*/
int* graph::single_source_shortest_paths_bfs(int current_level_vertices[], int num_current_vertices, int current_distance, int shortest_paths[], bool print_flag) const {
    // Initialize shortest_paths array if this is the first call
    if (shortest_paths == nullptr) {
        shortest_paths = new int[max_vertex - min_vertex + 1];
        std::fill(shortest_paths, shortest_paths + (max_vertex - min_vertex + 1), INT_MAX);
        for (int i = 0; i < num_current_vertices; i++) {
            shortest_paths[current_level_vertices[i] - min_vertex] = current_distance;
        }
    }

    // Initialize the queue for BFS
    std::queue<int> q;
    for (int i = 0; i < num_current_vertices; i++) {
        q.push(current_level_vertices[i]);
    }

    // Perform BFS to find shortest paths
    while (!q.empty()) {
        int current_vertex = q.front();
        q.pop();
        int current_level = shortest_paths[current_vertex - min_vertex];

        for (int j = 1; j < secondary_array_lengths[current_vertex - min_vertex]; j++) {
            int neighbor = adjacency_list[current_vertex - min_vertex][j];
            if (shortest_paths[neighbor - min_vertex] == INT_MAX) {
                shortest_paths[neighbor - min_vertex] = current_level + 1;
                q.push(neighbor);
            }
        }
    }

    // Print the results if print_flag is true
    if (print_flag) {
        int source_vertex = current_level_vertices[0];
        std::cout << "Shortest paths from vertex " << source_vertex << ":" << std::endl;
        for (int i = 0; i <= max_vertex - min_vertex; i++) {
            if (shortest_paths[i] != INT_MAX) {
                std::cout << "Shortest path from " << source_vertex << " to " << (min_vertex + i) << " is " << shortest_paths[i] << std::endl;
            }
        }
    }

    return shortest_paths; // Return the shortest_paths array
}

/*
This function is not recursive.

It follows Dijkstra's Algorithm for finding shortest paths, starting with the source node.

Parameters:
source_vertex - the vertex we're starting from (will have path length = 0)
print_flag - boolean flag indicating whether we want to print out all the shortest paths
*/
int* graph::single_source_shortest_paths_dijkstra(int source_vertex, bool print_flag) const {
    // Initialize the shortest_paths array
    int* shortest_paths = new int[max_vertex - min_vertex + 1];
    std::fill(shortest_paths, shortest_paths + (max_vertex - min_vertex + 1), INT_MAX);
    shortest_paths[source_vertex - min_vertex] = 0;

    // Initialize visited array to keep track of visited vertices
    std::vector<bool> visited(max_vertex - min_vertex + 1, false);

    // Perform Dijkstra's algorithm
    for (int i = 0; i <= max_vertex - min_vertex; i++) {
        int u = -1;
        for (int j = 0; j <= max_vertex - min_vertex; j++) {
            if (!visited[j] && (u == -1 || shortest_paths[j] < shortest_paths[u])) {
                u = j;
            }
        }

        if (shortest_paths[u] == INT_MAX)
            break;

        visited[u] = true;

        for (int j = 1; j < secondary_array_lengths[u]; j++) {
            int neighbor = adjacency_list[u][j];
            int alt = shortest_paths[u] + 1; // Assuming all edges have weight 1
            if (alt < shortest_paths[neighbor - min_vertex]) {
                shortest_paths[neighbor - min_vertex] = alt;
            }
        }
    }

    // Print the results if print_flag is true
    if (print_flag) {
        std::cout << "Shortest paths from vertex " << source_vertex << ":" << std::endl;
        for (int i = 0; i <= max_vertex - min_vertex; i++) {
            if (shortest_paths[i] != INT_MAX) {
                std::cout << "Shortest path from " << source_vertex << " to " << (min_vertex + i) << " is " << shortest_paths[i] << std::endl;
            }
        }
    }

    return shortest_paths; // Return the shortest_paths array
}

void graph::print_data() const {
    // print out all contents of adjacency_list
    for (int i = 0; i <= (max_vertex-min_vertex); i++) {
        std::cout << "index " << (min_vertex + i) << ": ";
        if (adjacency_list[i]!=0) {
            std::cout << "| ";
            for (int j = 0; j < secondary_array_lengths[i]; j++) {
                std::cout << adjacency_list[i][j] << " | ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "empty" << std::endl;
        }
    }

    // also print search_using_bfs
    std::cout << "search_using_bfs: " << search_using_bfs << std::endl;

}

int graph::count_components() const {
    // Initialize visited array to keep track of visited vertices
    std::vector<bool> visited(max_vertex - min_vertex + 1, false);
    int component_count = 0;

    // Helper function to perform BFS
    auto bfs = [&](int start_vertex) {
        std::queue<int> q;
        q.push(start_vertex);
        visited[start_vertex - min_vertex] = true;

        while (!q.empty()) {
            int current_vertex = q.front();
            q.pop();

            for (int j = 1; j < secondary_array_lengths[current_vertex - min_vertex]; j++) {
                int neighbor = adjacency_list[current_vertex - min_vertex][j];
                if (!visited[neighbor - min_vertex]) {
                    visited[neighbor - min_vertex] = true;
                    q.push(neighbor);
                }
            }
        }
    };

    // Loop through all vertices and perform BFS if not visited
    for (int i = 0; i <= max_vertex - min_vertex; i++) {
        if (secondary_array_lengths[i] > 0 && !visited[i]) {
            component_count++;
            bfs(min_vertex + i);
        }
    }

    return component_count;
}