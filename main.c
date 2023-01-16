#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

int main() {

    pnode graph =NULL;
    char choise_function;

    while (!feof(stdin)) {
        scanf("%c", &choise_function);

        switch(choise_function){
            case 'A':   
                build_graph_cmd(&graph);
                break;
            case 'B':
                insert_node_cmd(&graph);
                break;
            case 'D':
                delete_node_cmd(&graph);
                break;
            case 'S':
                //get the value of the vertexes
                int source_num=0;
                scanf("%d", &source_num);
                int dest_num=0;
                scanf("%d", &dest_num);

                int shortest = shortsPath_cmd(graph,source_num,dest_num);
                printf("Dijsktra shortest path: %d \n", shortest);

                break;
            case 'T': 
                TSP_cmd(graph);
                break;
            default:
                break;
        }

    }

    free_graph(&graph);
    return 0;
}