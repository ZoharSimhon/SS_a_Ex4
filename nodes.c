#include <stdio.h>
#include <math.h>
#include "graph.h"
#include <stdlib.h>


void free_graph(pnode *head){
   pnode curr = *head;
   while(curr!=NULL){
        pnode temp =curr->next;
        free_edges(curr);
        free(curr);
        curr=temp;
   }
   //*head= NULL;  
}

pnode find_vertex (pnode head, int num_vertex){
   //check if the num_vertex exist:
   pnode curr = head;
   while((curr!=NULL) && (curr->node_num != num_vertex)){
      curr = curr->next;
   }
   //if the num_vertex exis - return the vertext
   if(curr->node_num == num_vertex){
      return curr;
   }
   //else- return null
   return NULL;

}

void print_node(pnode vertex){
   printf("%d: \n", vertex->node_num);
   pedge curr_edge = vertex->edges;
   while(curr_edge != NULL){
      printf("endpoint: %d, ", curr_edge->endpoint->node_num);
      printf("weight: %d\n", curr_edge->weight);
      curr_edge=curr_edge->next;
   }
   printf("\n");
}
