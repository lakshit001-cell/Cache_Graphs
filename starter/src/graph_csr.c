
#include <stdlib.h>
#include "graph.h"

//Out degree of vertex vi is R[i+1] - R[i] and the end points for that is C[R[i]] to  C[R[i] + degree]
CSRGraph* convert_to_csr(Graph* g) { 
    if(!g) return NULL;

    //total edges
    int m = 0;
    for(int i=0; i<g->num_vertices; i++) {
        Edge* cur = g->vertices[i].head;
        while(cur) {
            m++;
            cur = cur->next;
        }
    }

    CSRGraph* csr = (CSRGraph*)malloc(sizeof(CSRGraph));
    if(!csr) return NULL;
    csr->num_vertices = g->num_vertices;
    csr->num_edges = m;

    csr->row_ptr = (int*)malloc((size_t)(csr->num_vertices + 1) * sizeof(int));
    csr->col_idx = (int*)malloc(m * sizeof(int));

    if(csr->row_ptr == NULL || csr->col_idx == NULL) {
        free_csr(csr);
        return NULL;
    }

    int edge_id = 0;
    for(int i=0;i<g->num_vertices;i++){
        csr->row_ptr[i] = edge_id;

        Edge* curr = g->vertices[i].head;
        while(curr!=NULL){ 
            csr->col_idx[edge_id] = curr->dst;
            edge_id++;
            curr = curr->next;
        }
    }

    csr-> row_ptr[csr->num_vertices] = edge_id; //total number of edges

    return csr;
}
void free_csr(CSRGraph* g){ if (!g) return; free(g->row_ptr); free(g->col_idx); free(g); }
