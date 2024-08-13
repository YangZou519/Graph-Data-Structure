#ifndef GRAPH_H
#define GRAPH_H

class graph {

    public:
        // basic functions
        // These are given to you.
        graph(bool search_using_bfs = true);
        void insert_vertex(int vertex);
        void insert_edge(int vertex1, int vertex2);
        void remove_vertex(int vertex);
        void remove_edge(int vertex1, int vertex2);

        // extended functions
        // YOU MUST IMPLEMENT THESE!
        bool path_exists(int vertex1, int vertex2) const;
        int shortest_path(int vertex1, int vertex2) const;
        int* single_source_shortest_paths_bfs(int current_vertices[], int num_current_vertices = 1, int current_distance = 0, int shortest_paths[] = 0, bool print_flag = false) const;
        int* single_source_shortest_paths_dijkstra(int current_vertex, bool print_flag = false) const;
        int count_components() const;

        // debugging functions
        // These are also given to you.
        void print_data() const;
        int get_max_vertex() const { return max_vertex; }
        int get_min_vertex() const { return min_vertex; }

    private:
        // This is the smallest label assigned to any vertex in your graph.
        // In the case of the sample graph created in main(), min_vertex=1.
        int min_vertex = 0;

        // This is the largest label assigned to any vertex in your graph.
        // In the case of the sample graph created in main(), max_vertex=15.
        int max_vertex = 0;

        // This is the total number of vertices in your graph.
        int number_of_vertices;

        // If this is true, single_source_shortest_paths will use Breadth-First Search.
        // If this is false, single_source_shortest_paths will use Dijkstra's Algorithm.
        bool search_using_bfs;

        // This is the data structure that stores our graph.
        // The top level is a direct access array.
        // Each slot in the direct access array may or may not point to a dynamic array.
        int** adjacency_list;

        // This is an array that stores the number of elements in each dynamic array that
        // adjacency_list points to.
        int* secondary_array_lengths;
};

#endif
