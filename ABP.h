/*-----------------------------------------------------------------------
ABP.h
arquivo com as especificações para o TAD árvore binária de pesquisa em ED 1 
professor: Anselmo Cardoso de Paiva
-------------------------------------------------------------------------
Aluno: Guilherme Barrio Nascimento
julho/2024
------------------------------------------------------------------------*/
#ifndef ABP_h
#define ABP_h

// definições locais

typedef struct tnode Tnode;

//especificações para o tad árvore

Tnode *abpCreate(void* data); 
/* Construir uma nova árvore contendo data
Pre-condição: (chamar a função treeCreate)
Pos-condição: retorna uma árvore contendo data */

void preOrdem(Tnode* tree,void(*visit)(void*));

void simetrica(Tnode* tree,void(*visit)(void*));

void abpesvazia(Tnode* tree,int(*cmp)(void*,void*));

void posOrdem(Tnode* tree,void(*visit)(void*));

int abpnNos(Tnode* tree);

void* abpQuery(Tnode* tree,void* key,int(*cmp)(void*,void*));

Tnode* abpInsert(Tnode* tree,void* data,int(*cmp)(void*,void*));

Tnode *abpRemove(Tnode *t, void *key, int(*cmp)(void*, void*), void **data);

Tnode* abpmenorno(Tnode* tree);

Tnode* abpmaiorno(Tnode* tree);

Tnode* abpRemoveMaior(Tnode *t, int (*cmp)( void *, void * ), void **data );

Tnode *abpRemoveMenor(Tnode *t, int (*cmp)( void *, void * ), void **data );

void treeClean(Tnode* tree);

int abpDestroy(Tnode *tree);
/* destroi a árvore
Pre-condição: (chamar a função treeCreate)
Pos-condição: retorna uma árvore contendo data */

#endif /* __ABP_H */