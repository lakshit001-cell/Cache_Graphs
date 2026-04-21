
#include <stdlib.h>
#include "graph.h"
int bfs_csr(CSRGraph* g, int source, int* dist) { 
    int n= g->num_vertices;
    int visited_count=0;
    for(int i=0; i<n;i++){
        dist[i]=-1;
    }
    
    int* queue = (int*)malloc(sizeof(int) * n);
    int head = 0, tail = 0;

    dist[source]=0;
    visited_count++;
    queue[tail++] = source;

    while(head<tail)
    {
        int v= queue[head++];
        int start = g->row_ptr[v];
        int end = g->row_ptr[v + 1];
        for (int i = start; i < end; i++) {
            int u = g->col_idx[i];
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                visited_count++;
                queue[tail++]=u;
            }
        }
    }
    free(queue);
    return visited_count;
}
