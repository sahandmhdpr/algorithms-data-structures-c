#include "graphs.h"

#include <stdio.h>
#include <stdlib.h>


static int graph_valid_vertex(const graph_t *g, int vertex)
{
    if (g == NULL) {
        return 0;
    }

    return vertex >= 0 && vertex < g->nv;
}


static int graph_is_avoided(int vertex,
                            const int *avoid,
                            int n_avoid)
{
    int i;

    if (avoid == NULL) {
        return 0;
    }

    for (i = 0; i < n_avoid; i++) {
        if (avoid[i] == vertex) {
            return 1;
        }
    }

    return 0;
}


/* =========================================================
   CREATION / MEMORY
   ========================================================= */

graph_t *graph_create(int n_vertices)
{
    graph_t *g;
    int i;
    int j;

    if (n_vertices <= 0) {
        return NULL;
    }

    g = malloc(sizeof(graph_t));

    if (g == NULL) {
        return NULL;
    }

    g->nv = n_vertices;

    g->g = malloc(n_vertices * sizeof(vertex_t));

    if (g->g == NULL) {
        free(g);
        return NULL;
    }

    for (i = 0; i < n_vertices; i++) {

        g->g[i].rowAdj =
            malloc(n_vertices * sizeof(int));

        if (g->g[i].rowAdj == NULL) {

            for (j = 0; j < i; j++) {
                free(g->g[j].rowAdj);
            }

            free(g->g);
            free(g);

            return NULL;
        }

        for (j = 0; j < n_vertices; j++) {
            g->g[i].rowAdj[j] = 0;
        }
    }

    graph_attribute_init(g);

    return g;
}


void graph_free(graph_t *g)
{
    int i;

    if (g == NULL) {
        return;
    }

    if (g->g != NULL) {

        for (i = 0; i < g->nv; i++) {
            free(g->g[i].rowAdj);
        }

        free(g->g);
    }

    free(g);
}


/* =========================================================
   EDGES
   ========================================================= */

int graph_add_directed_edge(graph_t *g, int from, int to)
{
    if (!graph_valid_vertex(g, from) ||
        !graph_valid_vertex(g, to)) {

        return 0;
    }

    g->g[from].rowAdj[to] = 1;

    return 1;
}


int graph_add_undirected_edge(graph_t *g, int v1, int v2)
{
    if (!graph_valid_vertex(g, v1) ||
        !graph_valid_vertex(g, v2)) {

        return 0;
    }

    g->g[v1].rowAdj[v2] = 1;
    g->g[v2].rowAdj[v1] = 1;

    return 1;
}


int graph_remove_directed_edge(graph_t *g,
                               int from,
                               int to)
{
    if (!graph_valid_vertex(g, from) ||
        !graph_valid_vertex(g, to)) {

        return 0;
    }

    g->g[from].rowAdj[to] = 0;

    return 1;
}


int graph_has_edge(const graph_t *g,
                   int from,
                   int to)
{
    if (!graph_valid_vertex(g, from) ||
        !graph_valid_vertex(g, to)) {

        return 0;
    }

    return g->g[from].rowAdj[to] != 0;
}


/* =========================================================
   ATTRIBUTES
   ========================================================= */

void graph_attribute_init(graph_t *g)
{
    int i;

    if (g == NULL) {
        return;
    }

    for (i = 0; i < g->nv; i++) {

        g->g[i].color = GRAPH_WHITE;

        g->g[i].dist = GRAPH_INF;

        g->g[i].pred = -1;

        g->g[i].disc_time = -1;

        g->g[i].end_time = -1;
    }
}


/* =========================================================
   DEGREE
   ========================================================= */

int graph_out_degree(const graph_t *g, int vertex)
{
    int v;
    int count;

    if (!graph_valid_vertex(g, vertex)) {
        return -1;
    }

    count = 0;

    for (v = 0; v < g->nv; v++) {

        if (g->g[vertex].rowAdj[v] != 0) {
            count++;
        }
    }

    return count;
}


int graph_in_degree(const graph_t *g, int vertex)
{
    int u;
    int count;

    if (!graph_valid_vertex(g, vertex)) {
        return -1;
    }

    count = 0;

    for (u = 0; u < g->nv; u++) {

        if (g->g[u].rowAdj[vertex] != 0) {
            count++;
        }
    }

    return count;
}


/* =========================================================
   BFS
   ========================================================= */

void graph_bfs(graph_t *g, int source)
{
    int *queue;
    int head;
    int tail;
    int u;
    int v;

    if (!graph_valid_vertex(g, source)) {
        return;
    }

    graph_attribute_init(g);

    queue = malloc(g->nv * sizeof(int));

    if (queue == NULL) {
        return;
    }

    head = 0;
    tail = 0;

    g->g[source].color = GRAPH_GREY;
    g->g[source].dist = 0;
    g->g[source].pred = -1;

    queue[tail] = source;
    tail++;

    while (head < tail) {

        u = queue[head];
        head++;

        for (v = 0; v < g->nv; v++) {

            if (g->g[u].rowAdj[v] != 0 &&
                g->g[v].color == GRAPH_WHITE) {

                g->g[v].color = GRAPH_GREY;

                g->g[v].dist =
                    g->g[u].dist + 1;

                g->g[v].pred = u;

                queue[tail] = v;
                tail++;
            }
        }

        g->g[u].color = GRAPH_BLACK;
    }

    free(queue);
}


/* =========================================================
   REACHABILITY
   ========================================================= */

int graph_reachable_count(graph_t *g, int source)
{
    int i;
    int count;

    if (!graph_valid_vertex(g, source)) {
        return 0;
    }

    graph_bfs(g, source);

    count = 0;

    for (i = 0; i < g->nv; i++) {

        if (g->g[i].dist != GRAPH_INF) {
            count++;
        }
    }

    return count;
}


int graph_reachable_within(graph_t *g,
                           int source,
                           int max_level)
{
    int *queue;
    int head;
    int tail;
    int u;
    int v;
    int count;

    if (!graph_valid_vertex(g, source) ||
        max_level < 0) {

        return 0;
    }

    graph_attribute_init(g);

    queue = malloc(g->nv * sizeof(int));

    if (queue == NULL) {
        return 0;
    }

    head = 0;
    tail = 0;
    count = 1;

    g->g[source].color = GRAPH_GREY;
    g->g[source].dist = 0;
    g->g[source].pred = -1;

    queue[tail] = source;
    tail++;

    while (head < tail) {

        u = queue[head];
        head++;

        for (v = 0; v < g->nv; v++) {

            if (g->g[u].rowAdj[v] != 0 &&
                g->g[v].color == GRAPH_WHITE &&
                g->g[u].dist + 1 <= max_level) {

                g->g[v].color = GRAPH_GREY;

                g->g[v].dist =
                    g->g[u].dist + 1;

                g->g[v].pred = u;

                count++;

                queue[tail] = v;
                tail++;
            }
        }

        g->g[u].color = GRAPH_BLACK;
    }

    free(queue);

    return count;
}


int graph_reachable_avoiding(graph_t *g,
                             int source,
                             const int *avoid,
                             int n_avoid)
{
    int *queue;
    int head;
    int tail;
    int u;
    int v;
    int count;

    if (!graph_valid_vertex(g, source)) {
        return 0;
    }

    if (graph_is_avoided(source, avoid, n_avoid)) {
        return 0;
    }

    graph_attribute_init(g);

    queue = malloc(g->nv * sizeof(int));

    if (queue == NULL) {
        return 0;
    }

    head = 0;
    tail = 0;
    count = 1;

    g->g[source].color = GRAPH_GREY;
    g->g[source].dist = 0;
    g->g[source].pred = -1;

    queue[tail] = source;
    tail++;

    while (head < tail) {

        u = queue[head];
        head++;

        for (v = 0; v < g->nv; v++) {

            if (g->g[u].rowAdj[v] != 0 &&
                g->g[v].color == GRAPH_WHITE &&
                !graph_is_avoided(v,
                                  avoid,
                                  n_avoid)) {

                g->g[v].color = GRAPH_GREY;

                g->g[v].dist =
                    g->g[u].dist + 1;

                g->g[v].pred = u;

                count++;

                queue[tail] = v;
                tail++;
            }
        }

        g->g[u].color = GRAPH_BLACK;
    }

    free(queue);

    return count;
}


/* =========================================================
   MAXIMUM BFS DISTANCE
   ========================================================= */

int graph_max_distance(graph_t *g, int source)
{
    int i;
    int max;

    if (!graph_valid_vertex(g, source)) {
        return -1;
    }

    graph_bfs(g, source);

    max = 0;

    for (i = 0; i < g->nv; i++) {

        if (g->g[i].dist != GRAPH_INF &&
            g->g[i].dist > max) {

            max = g->g[i].dist;
        }
    }

    return max;
}


/* =========================================================
   SHORTEST PATH + PATH RECONSTRUCTION
   ========================================================= */

int graph_shortest_path(graph_t *g,
                        int start,
                        int end,
                        int *path,
                        int path_capacity)
{
    int *reverse_path;
    int current;
    int length;
    int i;
    int distance;

    if (!graph_valid_vertex(g, start) ||
        !graph_valid_vertex(g, end) ||
        path == NULL ||
        path_capacity <= 0) {

        return -1;
    }

    graph_bfs(g, start);

    if (g->g[end].dist == GRAPH_INF) {
        return -1;
    }

    distance = g->g[end].dist;

    reverse_path =
        malloc(g->nv * sizeof(int));

    if (reverse_path == NULL) {
        return -1;
    }

    length = 0;
    current = end;

    while (current != -1) {

        reverse_path[length] = current;
        length++;

        current = g->g[current].pred;
    }

    if (length > path_capacity) {
        free(reverse_path);
        return -1;
    }

    for (i = 0; i < length; i++) {

        path[i] =
            reverse_path[length - 1 - i];
    }

    free(reverse_path);

    return distance;
}


/* =========================================================
   REACHABLE COUNT FROM EVERY VERTEX
   ========================================================= */

int *graph_reachable_counts(graph_t *g)
{
    int *result;
    int i;

    if (g == NULL) {
        return NULL;
    }

    result =
        malloc(g->nv * sizeof(int));

    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < g->nv; i++) {

        result[i] =
            graph_reachable_count(g, i);
    }

    return result;
}


/* =========================================================
   SOURCE VERTICES

   Return all vertices from which end_id is reachable.
   This comes directly from the exam-style source_vertices()
   problem in the notebook.
   ========================================================= */

int *graph_source_vertices(graph_t *g,
                           int end_id,
                           int *n_vertices)
{
    int *result;
    int count;
    int i;

    if (g == NULL ||
        n_vertices == NULL ||
        !graph_valid_vertex(g, end_id)) {

        return NULL;
    }

    result =
        malloc(g->nv * sizeof(int));

    if (result == NULL) {
        return NULL;
    }

    count = 0;

    for (i = 0; i < g->nv; i++) {

        graph_bfs(g, i);

        if (g->g[end_id].dist != GRAPH_INF) {

            result[count] = i;
            count++;
        }
    }

    *n_vertices = count;

    return result;
}


/* =========================================================
   DFS
   ========================================================= */

static int graph_dfs_recursive(graph_t *g,
                               int u,
                               int current_time)
{
    int v;

    g->g[u].color = GRAPH_GREY;

    current_time++;

    g->g[u].disc_time = current_time;

    for (v = 0; v < g->nv; v++) {

        if (g->g[u].rowAdj[v] != 0 &&
            g->g[v].color == GRAPH_WHITE) {

            g->g[v].pred = u;

            current_time =
                graph_dfs_recursive(g,
                                    v,
                                    current_time);
        }
    }

    g->g[u].color = GRAPH_BLACK;

    current_time++;

    g->g[u].end_time = current_time;

    return current_time;
}


void graph_dfs(graph_t *g, int source)
{
    int current_time;
    int v;

    if (!graph_valid_vertex(g, source)) {
        return;
    }

    graph_attribute_init(g);

    current_time = 0;

    g->g[source].pred = -1;

    current_time =
        graph_dfs_recursive(g,
                            source,
                            current_time);

    /*
     * Continue DFS for disconnected components.
     */
    for (v = 0; v < g->nv; v++) {

        if (g->g[v].color == GRAPH_WHITE) {

            g->g[v].pred = -1;

            current_time =
                graph_dfs_recursive(g,
                                    v,
                                    current_time);
        }
    }
}


/* =========================================================
   SIMPLE REACHABILITY QUERY
   ========================================================= */

int graph_is_reachable(graph_t *g,
                       int source,
                       int destination)
{
    if (!graph_valid_vertex(g, source) ||
        !graph_valid_vertex(g, destination)) {

        return 0;
    }

    graph_bfs(g, source);

    return g->g[destination].dist != GRAPH_INF;
}


/* =========================================================
   PRINT ADJACENCY MATRIX
   ========================================================= */

void graph_print_matrix(const graph_t *g)
{
    int i;
    int j;

    if (g == NULL) {
        return;
    }

    for (i = 0; i < g->nv; i++) {

        for (j = 0; j < g->nv; j++) {

            printf("%d ",
                   g->g[i].rowAdj[j]);
        }

        printf("\n");
    }
}