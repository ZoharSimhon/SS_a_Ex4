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
   //if the num_vertex doesn't exis - return NULL
   if(curr == NULL){
      return NULL;
   }

   //else- return the vertext
   return curr;
}

void remove_node(pnode *head, int num_vertex){
    //case - we need to delete the head
    if((*head)->node_num == num_vertex){
        *head = (*head)->next;
        return;
    }
    
   pnode curr = *head;
   while((curr->next!=NULL) && (curr->next->node_num != num_vertex)){
      curr = curr->next;
   }

   //if the vertex doesn't exist
   if(curr->next==NULL){
      return;
   }

   //in case we found:
   pnode delete= curr->next;
   curr->next= delete->next;
   delete->next=NULL;
    
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
