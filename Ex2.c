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

///Functie adaugare muchii
void add_edges_by_user(int nr_of_vertices, int nr_of_edges, GPH *graph) {
    int src, dest, i;
    printf("adauga %d muchii (de la 0 la %d)\n", nr_of_edges, nr_of_vertices-1);
    for (i = 0; i < nr_of_edges; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

int is_empty(NODE *queue) {
    return queue == NULL;
}

void enqueue(NODE **queue, int data) {
    NODE *new_node = create_node(data);
    if (is_empty(*queue)) {
        *queue = new_node;
    } else {
        NODE *temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE **queue) {
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

///Parcurgere DFS
void DFS(GPH *graph, int vertex_nr) {
    NODE *adj_list = graph->adjacency_lists[vertex_nr];
    NODE *temp = adj_list;
    graph->visited[vertex_nr] = 1;
    printf("%d ", vertex_nr);
    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

///Parcurgere BFS
void BFS(GPH *graph, int start) {
    NODE *queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);
    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);
        NODE *temp = graph->adjacency_lists[current];
        while (temp) {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

void wipe_visited_list(GPH *graph, int nr_of_vertices) {
    for (int i = 0; i < nr_of_vertices; i++) {
        graph->visited[i] = 0;
    }
}

///print_graph si print_queue nu erau necesare


int main() {
    int nr_of_vertices;
    int nr_of_edges;
    int starting_vertex;
    printf("Cate noduri are graful? ");
    scanf("%d", &nr_of_vertices);
    printf("Cate muchii are graful? ");
    scanf("%d", &nr_of_edges);
    GPH *graph = create_graph(nr_of_vertices);
    add_edges_by_user(nr_of_vertices, nr_of_edges, graph);
    printf("De unde plecam in DFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu DFS: ");
    DFS(graph, starting_vertex);
    wipe_visited_list(graph, nr_of_vertices);
    printf("\n");
    printf("De unde plecam in BFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu BFS: ");
    BFS(graph, starting_vertex);
    return 0;
}
