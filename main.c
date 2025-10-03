#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


//fila
typedef struct no {
    int valor;
    struct no *proximo;
} no;

typedef  struct {
    no *inicio;
    no *fim;
}fila;

void inicia_fila(fila *f){
    f->inicio = NULL;
    f->fim = NULL;
}

bool add_fila(fila *f, int valor){
    no * novono = malloc(sizeof(no));
    if(novono == NULL) return false;
    novono->valor=valor;
    novono->proximo=NULL;

    if(f->fim !=NULL){
        f->fim->proximo = novono;
    }
    f->fim=novono;

    if(f->inicio==NULL){
        f->inicio=novono;
    }
    return true;
}

int remover_fila(fila *f){
    if(f->inicio == NULL){
        return NULL;
    }
    no *aux=f->inicio;
    int resul = aux->valor;
    f->inicio=f->inicio->proximo;
    if(f->inicio==NULL){
        f->fim=NULL;
    }
    free(aux);
    return resul;
}

//grafo

typedef struct grafo{
    int numno;
    bool **arestas;
} grafo;

grafo *criar_grafo(int numnos){
    grafo *g = malloc(sizeof(*g));
    if(g == NULL){
        return NULL;
    }

    g->numno = numnos;

    g->arestas = calloc(sizeof(bool*), g->numno);
    if(g->arestas == NULL){
        free(g);
        return NULL;
    }

    for(int i=0; i < g->numno; i++){
        g->arestas[i] = calloc(sizeof(bool),g->numno);
        if(g->arestas[i] == NULL){
            destruir_grafo(g);
            return NULL;
        }
    }

    return g;
}

void destruir_grafo(grafo* g){
    if(g->arestas == NULL){
        return;
    }

    for (int i=0; i < g->numno; i++){
        if(g->arestas[i] != NULL){
            free(g->arestas[i]);
        }
    }

    free(g->arestas);
    free(g);
}

void printar_grafo(grafo *g){
    printf("grafo \n");

    for (int de=0; de < g->numno; de++){
        for(int para=0; para < g->numno; para++){
            if(g->arestas[de][para]){
                printf("%c -> %c\n", de, para);
            }
        }
    }
    printf("\n");
}

bool tem_aresta(grafo *g, unsigned int de_no, unsigned int para_no){
    assert(g!=NULL);
    assert(de_no < g->numno);
    assert(para_no < g->numno);

    return g->arestas[de_no][para_no];
}

bool adicionar_aresta(grafo *g, unsigned int de_no, unsigned int para_no){
    assert(g!=NULL);
    assert(de_no < g->numno);
    assert(para_no < g->numno);

    if(tem_aresta(g, de_no, para_no)){
        return false;
    }

    g->arestas[de_no][para_no] = true;
    g->arestas[para_no][de_no] = true;
    return true;
}

void buscaLargura(grafo *graph, int ini, int fim, int *visitado){
    int i=ini-1;
    //cria fila
    fila *fila;
    //inicializa a fila
    inicia_fila(fila);
    //adiciona o no inicial A/65 a fila
    add_fila(fila,ini);
    //marca o no inicial A/65 como visitado
    visitado[ini]=1;

    while(fila != NULL){
        i++;
        //verificando se ja foi visitado
        if(visitado[i]!=1){
            //verificando nos vizinho
            if(graph->arestas[ini][i]){
                //marca o no visinho como visitado
                visitado[i]=1;
                //adiciona o no vizinho a lista
                add_fila(fila,i);
            }
        }
        if(i==89){
            //se n tem mais no a ser verificado, reinicia o i
            i=65;
            //remove no atual da fila
            remover_fila(fila);
            //seleciona o proximo no a ser verificado
            ini=fila->inicio->valor;
        }
        if(ini==fim){
            //no de destino achado
            printf("A saida S foi encontrada!\n");
            break;
        }
    }
}

void buscaLargura_prep(grafo *gr,int ini,int fim){
    int visitado[90]={0};

    buscaLargura(gr,ini,fim,visitado);
}


int main()
{
    grafo *g1 = criar_grafo(90);


    /*codigo ansi usado para representar as letras
    A=65 , B=66, C=67, etc.*/

    adicionar_aresta(g1, 65, 66);
    adicionar_aresta(g1, 66, 67);
    adicionar_aresta(g1, 66, 70);
    adicionar_aresta(g1, 70, 71);
    adicionar_aresta(g1, 71, 72);
    adicionar_aresta(g1, 72, 68);
    adicionar_aresta(g1, 71, 76);
    adicionar_aresta(g1, 77, 81);
    adicionar_aresta(g1, 80, 83);
    adicionar_aresta(g1, 80, 79);
    adicionar_aresta(g1, 79, 82);
    adicionar_aresta(g1, 79, 74);
    adicionar_aresta(g1, 74, 73);
    adicionar_aresta(g1, 73, 78);
    adicionar_aresta(g1, 73, 69);
    adicionar_aresta(g1, 69, 65);
    adicionar_aresta(g1, 76, 77);
    adicionar_aresta(g1, 80, 81);

    buscaLargura_prep(g1,65,83);

    destruir_grafo(g1);

}
