#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
    
pnode* create_vertexes_list (int size_vertex){
    pnode* graph_arr = (pnode*)malloc(size_vertex * sizeof(pnode));
    //check if the malloc succeed
    if(graph_arr == NULL){
        return NULL;
    }

    //Create the last vertex in the list
    graph_arr[size_vertex-1]= (pnode)malloc(sizeof(node));
    graph_arr[size_vertex-1] -> node_num = size_vertex-1;
    graph_arr[size_vertex-1] -> edges = NULL;
    graph_arr[size_vertex-1] -> next =NULL;
    
    //create the other vertexes
    for(int index =size_vertex-2; 0<=index; index--){
        graph_arr[index] = (pnode)malloc(sizeof(node));
        graph_arr[index] -> node_num = index;
        graph_arr[index] -> edges = NULL;
        graph_arr[index] -> next =graph_arr[index+1];
    }

    return graph_arr;
}

void build_graph_cmd(pnode *head){
    //Delete the current graph:
    free_graph(head);

    //Create a new graph:
        //get the number of the vertexes 
        int size_vertex = 0;
        scanf("%d", &size_vertex);
        if(size_vertex == 0){
            return;
        }

        //Create a list of the vertexes
        pnode * graph_arr = create_vertexes_list(size_vertex);
        *head = graph_arr[0];

        //Get the values of the vertexes
        int first_vertex;
        int second_vertex;
        int weight;
        char n;
        for(size_t index=0; index<size_vertex; index++){
        scanf("%c", &n);
        scanf("%d", &first_vertex);
        int result_scan= scanf("%d", &second_vertex);
        while((!feof(stdin)) && (result_scan != 0)){
            scanf("%d", &weight);
            add_edge(graph_arr[first_vertex], weight, graph_arr[second_vertex]);
            result_scan= scanf("%d", &second_vertex);
        }
    }
    //free graph_arr
    free(graph_arr); 
}


void insert_node_cmd(pnode *head){
    //get the number of the vertexes 
    int num_vertex = 0;
    scanf("%d", &num_vertex);

    //check if the vertex exist:
    pnode first_vertex = find_vertex(*head, num_vertex);
    //if the verte exis - delete all its edges
    if(first_vertex != NULL){
        pedge curr_edge = first_vertex -> edges;
        while(curr_edge!=NULL){
                pedge temp =curr_edge->next;
                free(curr_edge);
                curr_edge=temp;
        }
        first_vertex->edges=NULL;
    }
    //else: create a new node which contains the num_vertex we have got
    else{
        first_vertex =(pnode)malloc(sizeof(node));
        first_vertex -> node_num = num_vertex;
        first_vertex -> edges = NULL;
        first_vertex -> next =*head; 
        *head = first_vertex;
    }

    //add all the edges
    int num_second_vertex; 
    int weight =0;
    while(( (scanf("%d", &num_second_vertex))) != 0){
        scanf("%d", &weight);
        pnode second_vertex = find_vertex(*head, num_second_vertex);
        add_edge(first_vertex, weight, second_vertex);
    }

}

void delete_node_cmd(pnode *head){
    //cheak if the list is empty:
    if(head == NULL){
        return;
    }

    int num_vertex;
    scanf("%d", &num_vertex);

    //first -find the vertex
    pnode vertex = find_vertex(*head, num_vertex);
    //if the vertex doesn't exist - done
    if(vertex == NULL){
        return;
    }

    //remove the node from the list:
    remove_node(head, num_vertex);

    //delete the node
    free_edges(vertex);
    free(vertex);

    //delete all the edges which connected to that node
    pnode curr_vertex = *head;
    pedge curr_edge;
    int found = 0;
    //check all the vertexes
    while(curr_vertex!=NULL){
        curr_edge= curr_vertex -> edges;
        //check all the edges in the current vertex
        while((curr_edge != NULL) && !found){
            //if the edge points to the node we deleted
            if (curr_edge-> endpoint -> node_num == num_vertex){
                pedge temp =curr_edge->next;
                free(curr_edge);
                curr_edge=temp;
                found =1;
            }
            else{
                curr_edge = curr_edge->next;
            }
        }
        curr_vertex = curr_vertex->next;
    }
}

int shortsPath_cmd(pnode head,int source_num, int dest_num){
    //find the vertexes
    pnode source = find_vertex(head, source_num);
    pnode dest = find_vertex(head, dest_num);

    //set all the vertexes:
    set_start_value(head);

    //update the source->dist to 0, according the algorithm 
    source->dist =0;

    // dijkstra's algorithm
    //pnode curr_vertex = min_not_visited(head);
    pnode curr_vertex = source;
    while (curr_vertex!= NULL)
    {
        curr_vertex->visited = 1;
        pedge curr_edge = curr_vertex->edges;
        while (curr_edge != NULL)
        {
            int dist_by_curr_edge = curr_vertex->dist + curr_edge->weight;
            if (!(curr_edge->endpoint->visited) && (dist_by_curr_edge < curr_edge->endpoint->dist))
            {
                curr_edge->endpoint->dist = dist_by_curr_edge;
            }
            curr_edge = curr_edge->next;
        }
        curr_vertex = min_not_visited(head);
    }
    //if there isn't a path between the vertexes
    if (dest->dist == __INT_MAX__)
    {
        dest->dist = -1;
    }
    return dest->dist;
}

pnode min_not_visited(pnode head){
    pnode answer = NULL;
    pnode curr = head;
    int min = __INT_MAX__;
    while (curr!= NULL)
    {
        //if we didn't visit curr yet, and its dist is smaller than the minimum value
        if (!curr->visited && curr->dist < min)
        {
            min = curr->dist;
            answer = curr;
        }
        curr = curr->next;
    }
    return answer;
}

void set_start_value(pnode head){
    pnode current = head;
    while(current!=NULL)
    {  
        current->visited = 0;
        current-> dist = __INT_MAX__;

        current = current->next;
    }
}

void TSP_cmd(pnode head){
    // get the nember of vertexes
    int k;
    scanf("%d", &k);

    //get all the vertexes in the path
    int *vertexes = (int *)(malloc(sizeof(int) * k));
    int min = __INT_MAX__;
    for (size_t index = 0; index < k; index++) {
        scanf("%d", (vertexes+index));
    }

    //check where we should start the path
    for (size_t index = 0; index < k; index++) {
        swap_place(vertexes, 0, index);
        TSP_helper(head, vertexes, k, 0, &min);
        swap_place(vertexes, index, 0);
    }

    //if there isn't a path between the vertexes
    if (min == __INT_MAX__) {
        min = -1;
    }

    free(vertexes);

    printf("TSP shortest path: %d \n", min);
}

void swap_place(int *vertexes, int indes1, int indes2){
    int temp = vertexes[indes1];
    vertexes[indes1]=vertexes[indes2];
    vertexes[indes2]=temp;
}

void TSP_helper(pnode head, int *vertexes, int k, int curr, int *pmin) {
    // if there are two vertices
    if (k == 2)
    {
        int dist = shortsPath_cmd(head, vertexes[0], vertexes[1]);
        //if we found better path - update min value
        if (dist != -1 && (curr + dist) < *pmin)
        {
            *pmin = (curr + dist);
        }
        return;
    }

    // cheak all the paths
    for (size_t index = 1; index < k; index++)
    {
        swap_place(vertexes, 1, index);
        int dist = shortsPath_cmd(head, vertexes[0], vertexes[1]);
        if (dist == -1)
        {
            return;
        }
        TSP_helper(head, (vertexes + 1), k - 1, curr + dist, pmin);
        swap_place(vertexes, index, 1);
    }
}

//for self debug
void printGraph_cmd(pnode head) {
    pnode curr_vertex = head;
    while(curr_vertex!=NULL)
    {
        print_node(curr_vertex);
        curr_vertex = curr_vertex->next; 
    }        

}
