#ifndef ALGORITHMS_DATA_STRUCTURES_C_GRAPHS_H
#define ALGORITHMS_DATA_STRUCTURES_C_GRAPHS_H

#define GRAPH_WHITE 0
#define GRAPH_GREY  1
#define GRAPH_BLACK 2
#define GRAPH_INF   (-1)

typedef struct vertex_s {
    int *rowAdj;

    int color;
    int dist;
    int pred;

    int disc_time;
    int end_time;
} vertex_t;


typedef struct graph_s {
    int nv;
    vertex_t *g;
} graph_t;


/* Graph creation and memory */
graph_t *graph_create(int n_vertices);
void graph_free(graph_t *g);

/* Edges */
int graph_add_directed_edge(graph_t *g, int from, int to);
int graph_add_undirected_edge(graph_t *g, int v1, int v2);
int graph_remove_directed_edge(graph_t *g, int from, int to);
int graph_has_edge(const graph_t *g, int from, int to);

/* Vertex attributes */
void graph_attribute_init(graph_t *g);

/* Degree */
int graph_out_degree(const graph_t *g, int vertex);
int graph_in_degree(const graph_t *g, int vertex);

/* BFS */
void graph_bfs(graph_t *g, int source);
int graph_reachable_count(graph_t *g, int source);
int graph_reachable_within(graph_t *g, int source, int max_level);
int graph_reachable_avoiding(graph_t *g,
                             int source,
                             const int *avoid,
                             int n_avoid);

int graph_max_distance(graph_t *g, int source);

/* Paths */
int graph_shortest_path(graph_t *g,
                        int start,
                        int end,
                        int *path,
                        int path_capacity);

/* Reachability from every vertex */
int *graph_reachable_counts(graph_t *g);

/* Exam-style source vertices */
int *graph_source_vertices(graph_t *g,
                           int end_id,
                           int *n_vertices);

/* DFS */
void graph_dfs(graph_t *g, int source);

/* Structural queries */
int graph_is_reachable(graph_t *g, int source, int destination);

/* Utility */
void graph_print_matrix(const graph_t *g);

#endif