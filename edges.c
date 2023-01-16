#include <stdio.h>
#include <math.h>
#include "graph.h"
#include <stdlib.h>

void add_edge(pnode vertex,int weight, pnode endpoint){
    //Create an edge
    pedge new_edge = (pedge)malloc(sizeof(edge));
    new_edge->weight= weight;
    new_edge-> endpoint =endpoint;
    //add new_edge to the start:
    new_edge -> next = vertex->edges;
    vertex->edges= new_edge; 
}

void free_edges(pnode vertex){
   pedge curr = vertex -> edges;
   while(curr!=NULL){
        pedge temp =curr->next;
        free(curr);
        curr=temp;
        curr = curr -> next;
   }
}
