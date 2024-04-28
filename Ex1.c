#include <stdio.h>
#include <stdlib.h>

///Definesc nodul 
typedef struct Node {
    int data;
    struct Node *next;
} NODE;

///Definesc graful 
typedef struct Graph {
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} GPH;

///Functie nod
NODE *create_node(int v) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

///Functie graf
GPH *create_graph(int vertices) {
    int i;
    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * vertices);
    for (i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

///Functie muchie
void add_edge(GPH *graph, int src, int dest) {
    NODE *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;
    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

///Parcurgere DFS
void DFS(GPH *graph, int vertex_nr, int target) {
    graph->visited[vertex_nr] = 1;
    if (vertex_nr == target) {
        printf("Drum gasit!\n");
        return;
    }
    NODE *adj_list = graph->adjacency_lists[vertex_nr];
    while (adj_list) {
        int connected_vertex = adj_list->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex, target);
        }
        adj_list = adj_list->next;
    }
}

///Resetez
void wipe_visited_list(GPH *graph, int nr_of_vertices) {
    for (int i = 0; i < nr_of_vertices; i++) {
        graph->visited[i] = 0;
    }
}

int main() {
    int nr_of_vertices, nr_of_edges;
    GPH *graph;

    printf("Cate noduri are graful? ");
    scanf("%d", &nr_of_vertices);
    printf("Cate muchii are graful? ");
    scanf("%d", &nr_of_edges);

    graph = create_graph(nr_of_vertices);
    printf("Introduceti nodurile sursa si destinatie (spatiu intre ele): \n");
    for (int i = 0; i < nr_of_edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
    int start, end;
    printf("De la ce nod doriti sa porniti? ");
    scanf("%d", &start);
    printf("La ce nod doriti sa ajungeti? ");
    scanf("%d", &end);
    wipe_visited_list(graph, nr_of_vertices); // Reseteaza lista de vizitati
    DFS(graph, start, end); // Apeleaza DFS cu nodurile de pornire si destinatie
    if (graph->visited[end] == 0) {
        printf("Nu s-a gasit drum intre nodurile %d si %d.\n", start, end);
    }
    for (int i = 0; i < nr_of_vertices; i++) {
        free(graph->adjacency_lists[i]);
    }
    free(graph->adjacency_lists);
    free(graph->visited);
    free(graph);
    return 0;
}
