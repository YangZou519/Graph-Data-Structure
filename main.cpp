#include <iostream>

#include "graph.h"

void check_for_path(graph Graph, int vertex1, int vertex2) {
    std::cout << "Does a path exist between vertices " << vertex1 << " and " << vertex2 << "? ";
    if (Graph.path_exists(vertex1, vertex2)) {
        std::cout << "Yes." << std::endl;
        std::cout << "  The shortest path between vertices " << vertex1 << " and " << vertex2 << " is ";
        std::cout << Graph.shortest_path(vertex1, vertex2) << " units long.";
        std::cout << std::endl;
    } else {
        std::cout << "No." << std::endl;
    }
}

int main() {
    // Search this graph using Breadth-First Search.
    std::cout << "Searching for shortest paths using Breadth-First Search." << std::endl;

    graph Graph_bfs = graph(true);
    Graph_bfs.insert_vertex(1);
    Graph_bfs.insert_vertex(10);
    Graph_bfs.insert_edge(1,10);

    Graph_bfs.insert_vertex(4);
    Graph_bfs.insert_edge(4,10);
    Graph_bfs.insert_edge(4,1);

    Graph_bfs.insert_vertex(15);
    Graph_bfs.insert_edge(15,10);
    //Graph_bfs.insert_edge(15,1);

    Graph_bfs.remove_edge(4,10);
    Graph_bfs.remove_edge(4,1);
    Graph_bfs.remove_vertex(4);

    Graph_bfs.print_data();

    check_for_path(Graph_bfs, 1, 10);
    check_for_path(Graph_bfs, 5, 6);
    check_for_path(Graph_bfs, 1, 15);
    check_for_path(Graph_bfs, 10, 4);

    int layer_0[1] = {1};
    // need to provide a lot of default parameters to make this function call work
    Graph_bfs.single_source_shortest_paths_bfs(layer_0, 1, 0, 0, true);




    // Now, search this graph using Dijkstra's Algorithm.
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Searching for shortest paths using Dijkstra's Algorithm this time." << std::endl;

    graph Graph_dijkstra = graph(false);
    Graph_dijkstra.insert_vertex(1);
    Graph_dijkstra.insert_vertex(10);
    Graph_dijkstra.insert_edge(1,10);

    Graph_dijkstra.insert_vertex(4);
    Graph_dijkstra.insert_edge(4,10);
    Graph_dijkstra.insert_edge(4,1);

    Graph_dijkstra.insert_vertex(15);
    Graph_dijkstra.insert_edge(15,10);
    //Graph_dijkstra.insert_edge(15,1);

    Graph_dijkstra.remove_edge(4,10);
    Graph_dijkstra.remove_edge(4,1);
    Graph_dijkstra.remove_vertex(4);

    Graph_dijkstra.print_data();

    check_for_path(Graph_dijkstra, 1, 10);
    check_for_path(Graph_dijkstra, 5, 6);
    check_for_path(Graph_dijkstra, 1, 15);
    check_for_path(Graph_dijkstra, 10, 4);

    // need to provide a lot of default parameters to make this function call work
    Graph_dijkstra.single_source_shortest_paths_dijkstra(1, true);

    // Test the count_components function
    std::cout << "\nNumber of connected components by using BFS: " << Graph_bfs.count_components() << std::endl;
    std::cout << "Number of connected components by using Dijkstra: " << Graph_dijkstra.count_components() << std::endl;

    return 0;
}
