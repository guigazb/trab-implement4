/*-----------------------------------------------------------------------
ABP.c
arquivo com a implementação para o TAD árvore binária de pesquisa em ED 1 
professor: Anselmo Cardoso de Paiva
-------------------------------------------------------------------------
Aluno: Guilherme Barrio Nascimento
julho/2024
------------------------------------------------------------------------*/

#ifndef _ABP_C_
#define _ABP_C_
#include <stdio.h>
#include <stdlib.h>

#include "abp.h" /* inclui a especificacao do TAD */

#define true  1
#define false 0


typedef struct tnode{
    void* data;
    struct tnode* l;
    struct tnode* r;
} Tnode;


Tnode* abpCreate(void* data){
    Tnode* tree = (Tnode*) malloc(sizeof(Tnode));
    if(tree != NULL){
        tree->data = data;
        tree->l = NULL;
        tree->r = NULL;
        return tree;
    }
    return NULL;
}

void preOrdem(Tnode* tree,void(*visit)(void*)){
    if(tree != NULL){
        visit(tree->data);
        preOrdem(tree->l,visit);
        preOrdem(tree->r,visit);
    }
}

void simetrica(Tnode* tree,void(*visit)(void*)){
    if(tree != NULL){
        simetrica(tree->l,visit);
        visit(tree->data);
        simetrica(tree->r,visit);
    }
}

void abpesvazia(Tnode* tree,int(*cmp)(void*,void*)){
    void** data;
    if(tree != NULL){
        abpesvazia(tree->l,cmp);
        abpRemove(tree,tree,cmp,data);
        abpesvazia(tree->r,cmp);
    }
}

void posOrdem(Tnode* tree,void(*visit)(void*)){
    if(tree != NULL){
        posOrdem(tree->l,visit);
        posOrdem(tree->r,visit);
        visit(tree->data);
    }
}

int abpnNos(Tnode* tree){ // visitação simetrica, qualquer visitação pode ser usada
    int nl,n,nr;
    if(tree != NULL){
        nl = abpnNos(tree->l);
        n = 1;
        nr = abpnNos(tree->r);
        return nl+n+nr;
    }
    return 0;
}

void* abpQuery(Tnode* tree,void* key,int(*cmp)(void*,void*)){
    void* data;
    if(tree != NULL){
        int stat = cmp(key,tree->data);
        if(stat == 0){
            data = tree->data;
            return data;
        }else if(stat == 1){
            data = abpQuery(tree->r,key,cmp);
            return data;
        }else if(stat == -1){
            data = abpQuery(tree->l,key,cmp);
            return data;
        }
    }
    return NULL;
}

Tnode* abpInsert(Tnode* tree,void* data,int(*cmp)(void*,void*)){
    void* data2; // n sei 
    Tnode* newnode;
    if(tree != NULL){
        int stat = cmp(data,tree->data);
        if(stat >= 0){
            tree->r = abpInsert(tree->r,data,cmp);
        }else{
            tree->l = abpInsert(tree->l,data,cmp);
        }
        return tree;
    }else{
        newnode = (Tnode*)malloc(sizeof(Tnode));
        if(newnode != NULL){
            newnode->l = newnode->r = NULL;
            newnode->data = data;
            return newnode;
        }
        return NULL;
    }
}

/*Tnode *abpRemove(Tnode *t, void *key, int (*cmp)(void *, void *), void **data){ 
    void *data2;
    Tnode* aux;
    if( t != NULL ){
        int stat = cmp(data, t->data);
        if ( stat < 0 ) {
            t->l = abpRemove(t->l, key, cmp,data);
            return t;
        } else if ( stat > 0 ) {
            t->r = abpRemove(t->r, key, cmp,data);
            return t;
        } else {
            if (t->l == NULL && t->r == NULL) {
                // é um nó folha
                *data = t->data;
                free(t);
                return NULL;
            } else if (t->l == NULL ) {
                aux = t->r; 
                *data = t->data;
                free(t);
                return aux;
            } else if ( t->r == NULL ) {
                aux = t->l; 
                *data = t->data;
                free(t);
                return aux;
            } else {
                *data = t->data;
                t->l = abpRemoveMaior(t->l, cmp, &data2);
                t->data = data2;
                return t;
            }
        }
    }
    *data = NULL;
    return NULL;    
}*/

Tnode *abpRemove(Tnode *t, void *key, int(*cmp)(void* a, void* b), void **data){
    if(t != NULL){ 
        int stat = cmp(key, t->data);
        if(stat < 0){
            t->l = abpRemove(t->l, key, cmp, data);
            return t;
        }else if(stat > 0){
            t->r = abpRemove(t->r, key, cmp, data);
            return t;
        }else{
            *data = t->data;
            if(t->l == NULL && t->r == NULL){ // Folha
                free(t);
                return NULL;
            }else if(t->l == NULL && t->r != NULL){ // Nó somente com filho direito 
                Tnode *aux = t->r;
                free(t);
                return aux;
            }else if(t->l != NULL && t->r == NULL){ // Nó somente com filho esquerdo
                Tnode *aux = t->l;
                free(t);
                return aux;
            }else{ //Nó com dois filhos
                //TNode *aux = findMin(t->r); // Acha o sucessor, o menor dos maiores
                Tnode *aux = abpmaiordata(t->l); // Acha o sucessor, o maior dos menores
                t->data = aux->data;    // Substitui o dado do nó a ser removido pelo dado do sucessor
                void *data2 = (void*)malloc(sizeof(void));
                t->l = abpRemove(t->l, aux->data, cmp, data2); // Remove o sucessor da subárvore esquerda
                //t->r = abpRemove(t->r, aux->data, cmp, data); // Remove o sucessor da subárvore direita
                
                /*
                    pra escolher o sucessor é opcional, pode ser o maior dos menores (subárvores esquerda) ou o menor dos maiores (subárvore direita)
                    dependendo da escolha você vai precisar fazer umas modificações como descomentar as linhas

                     //TNode *aux = findMin(t->r); // Acha o sucessor, o menor dos maiores
                     //t->r = abpRemove(t->r, aux->data, cmp, data); // Remove o sucessor da subárvore direita

                     e comentar as linhas 

                      TNode *aux = findMax(t->l); // Acha o sucessor, o maior dos menores
                      t->l = abpRemove(t->l, aux->data, cmp, data); // Remove o sucessor da subárvore esquerda
                */
                
                return t;
            }
        }
    }
    
    return NULL;
}

void* abpmenordata(Tnode* tree){
    if(tree != NULL){
        if(tree->l != NULL){
            return abpmenordata(tree->l);
        }else{
            return tree->data;
        }
    }else{
        return NULL;
    }
}

void* abpmaiordata(Tnode* tree){
    if(tree != NULL){
        if(tree->r != NULL){
            return abpmaiordata(tree->r);
        }else{
            return tree->data;
        }
    }else{
        return NULL;
    }
}


Tnode *abpRemoveMaior( Tnode *t, int (*cmp)( void *, void * ), void **data ){
    if ( t != NULL ){    
        void *data2;
        Tnode *aux;
        if ( t->r != NULL ){
            t->r = abpRemoveMaior( t->r, cmp, &data2 );
            return t;
        } else {
            if ( t->l != NULL ){
                aux = t->l;
                *data = t->data;
                free( t );
                return aux;
            } else {
                *data = t->data;
                free( t );
                return NULL;
            }
        }
    }
    *data = NULL;
    return NULL;
}

Tnode *abpRemoveMenor(Tnode *t, int (*cmp)( void *, void * ), void **data ){
    if ( t != NULL ){    
        void *data2;
        Tnode* aux;
        if ( t->l != NULL ){
            t->l = abpRemoveMaior( t->l, cmp, &data2 );
            return t;
        } else {
            if ( t->r != NULL){
                aux = t->r;
                *data = t->data;
                free( t );
                return aux;
            } else {
                *data = t->data;
                free( t );
                return NULL;
            }
        }
    }
    *data = NULL;
    return NULL;
}



int abpDestroy(Tnode *tree){
    if(tree != NULL){
        if(tree->l == NULL && tree->r == NULL && tree->data == NULL){
            free(tree);
            return true;
        }
        return false;
    }
    return -1;
}


#endif /* __ABP_C */