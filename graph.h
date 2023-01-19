#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
    int dist;
    int visited;
} node, *pnode;

//graph
void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void deleteGraph_cmd(pnode* head);
int shortsPath_cmd(pnode head,int source_num, int dest_num);
void TSP_cmd(pnode head);
pnode* create_vertexes_list (int size_vertex);
void printGraph_cmd(pnode head); //for self debug

pnode min_not_visited(pnode head);
void set_start_value(pnode head);
void swap_place(int *vertexes, int indes1, int indes2);
void TSP_helper(pnode head, int *vertexes, int k, int curr, int *pmin);

//edges
void add_edge(pnode vertex,int weight, pnode endpoint);
void free_edges(pnode vertex);

//nodes
void free_graph(pnode *head);
pnode find_vertex (pnode head, int num_vertex);
void print_node(pnode vertex);
void remove_node(pnode *head,  int num_vertex);

#endif