#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "abp.h"
#include "abp.c"
#define true 1
#define false 0

typedef struct {
    char nome[30];
    int temporadas;
    float nota;
}Serie;


void pegaelm(void* data){
    Serie* var = (Serie*) data;
    printf("aqui esta o item encontrado: \n");
    printf("nome: %s ,temporadas: %d ,nota: %.2f \n", var->nome, var->temporadas, var->nota);
    printf("\n");
}

void listarColecao(Tnode *tree){ 
    int num = abpnNos(tree);
    if(tree != NULL && num > 0){
        printf("elementos ordenados: \n");
        simetrica(tree,pegaelm);
    }else if(num <= 0){
            printf("sem itens para imprimir \n");
        }
}  

int cmp(void* a, void* b){
    Serie *pa = (Serie *) a;
    Serie *pb = (Serie*) b;
    if(pa != NULL && pb != NULL){
        if(strcmp(pa->nome,pb->nome) == 0 && pa->temporadas == pb->temporadas && pa->nota == pb->nota){
           return 0;
        }else if(pa->temporadas > pb->temporadas){
            return 1;
        }else{
            return -1;
        }
        
    }
    return -2;
}

int main(){
    
    int flag = true;
    void listarColecao(Tnode *tree);
    int cmp(void* a, void* b);

    Tnode *tree = NULL;

    while(flag == true){
        
        printf("1 - Criar colecao \n");
        printf("2 - Inserir um elemento \n");
        printf("3 - Remover um elemento \n");
        printf("4 - Consultar um elemento \n");
        printf("5 - listar os elementos \n");
        printf("6 - Destruir a colecao \n");
        printf("7 - Esvaziar a colecao (destroi a colecao caso possua mais de um item) \n");
        printf("0 - Sair \n");
        printf("deseja realizar qual operacao? \n ");
        
        int opcao;
        scanf("%d", &opcao);
        switch(opcao){
            case 1:{
                if(tree != NULL){
                    printf("existe uma colecao criada \n");
                    printf("destrua a colecao anterior antes de criar uma nova \n");
                    printf("\n");
                    break;
                }

                Serie *item = (Serie*)malloc(sizeof(Serie));
                printf("digite qual sera o primeiro item: \n");
                printf("Nome: ");
                scanf(" %[^\n]s", item->nome);
                printf("temporadas: ");
                scanf("%d", &item->temporadas);
                printf("nota: ");
                scanf("%f", &item->nota);
                tree = abpCreate(item);

                if(tree != NULL){
                    printf("Colecao criada com sucesso! \n");
                    printf("\n");
                    break;
                }else{
                    printf("a coleção não foi criada, tente novamente... \n");
                    printf("\n");
                    break;
                }
            }
            case 2:{
                Serie *item = (Serie *) malloc(sizeof(Serie));
                if(tree != NULL && item != NULL){
                    printf("Nome: ");
                    scanf(" %[^\n]s", item->nome);
                    printf("temporadas: ");
                    scanf("%d", &item->temporadas);
                    printf("nota: ");
                    scanf("%f", &item->nota);

                    if(abpInsert(tree,item,cmp) != NULL){ 
                        printf("Serie inserida com sucesso \n");
                        printf("\n");
                        break;
                    }else{
                        printf("Erro ao inserir Serie \n");
                        printf("\n");
                        break;
                    }
                }
                printf("erro de parametro \n");
                printf("crie uma colecao antes... \n");
                printf("\n");
                break;
            }
            case 3:{
                Serie *item = (Serie *) malloc(sizeof(Serie));
                void* salvo = NULL;
                Serie* salvado;
                if(tree != NULL && item != NULL){
                    printf("Nome: ");
                    scanf(" %[^\n]s", item->nome);
                    printf("temporadas: ");
                    scanf("%d", &item->temporadas);
                    printf("nota: ");
                    scanf("%f", &item->nota);

                    abpRemove(tree,item,cmp,&salvo);
                    if(salvo != NULL){
                        printf("item removido com sucesso! \n");
                        printf("\n");
                        salvado = (Serie*) salvo;
                        printf("nome: %s ,temporadas: %d ,nota: %.2f \n", salvado->nome, salvado->temporadas, salvado->nota);
                        printf("\n");
                        break;
                    }else{
                       printf("nao foi possivel remover o item \n");
                       printf("\n");
                       break; 
                    }
                }
                printf("erro de parametro \n");
                printf("crie uma colecao antes ou insira um item valido... \n");
                printf("\n");
                break;
            }
            case 4:{
                Serie *item = (Serie*) malloc(sizeof(Serie));
                if(tree != NULL && item != NULL){
                    printf("Nome: ");
                    scanf(" %[^\n]s", item->nome);
                    printf("temporadas: ");
                    scanf("%d", &item->temporadas);
                    printf("nota: ");
                    scanf("%f", &item->nota);

                    Serie *chave = (Serie*) abpQuery(tree, item, cmp); 
                    if(chave != NULL){
                        printf("Serie encontrada ! \n");
                        printf("Nome: %s, temporadas: %d, nota: %.2f \n", chave->nome, chave->temporadas, chave->nota);
                        printf("\n");
                        break;
                    }else{
                        printf("a Serie nao foi encontrada \n");
                        printf("\n");
                        break;
                    }  
                }
                printf("erro de parametro \n");
                printf("crie uma colecao antes ou insira um item valido... \n");
                printf("\n");
                break;
            }
            case 5:{ 
                if(tree != NULL){
                    printf("aqui estao os itens da colecao: \n");
                    listarColecao(tree);
                    printf("\n");
                    break;
                }
                printf("erro de parametro \n");
                printf("crie uma colecao antes ... \n");
                printf("\n");
                break;
            }
            case 6:{
                if(tree != NULL){
                    if(abpDestroy(tree) == true){
                        printf("Colecao destruida \n");
                        printf("\n");
                        tree = NULL;
                        break;
                    }else{
                        printf("A colecao nao foi destruida \n");
                        printf("esvazie a colecao antes de destruir \n");
                        printf("\n");
                        break;
                    }
                }
                printf("erro de parametro \n");
                printf("crie uma colecao antes ... \n");
                printf("\n");
                break;
            }
            case 7:{
                if(tree != NULL){
                    treeClean(tree);
                    printf("A colecao foi esvaziada \n");
                    printf("\n");
                    tree = NULL;
                    break;
                }else{
                    printf("A colecao nao foi esvaziada \n");
                    printf("\n");
                    break;
                }
                printf("erro de parametro \n");
                printf("crie uma colecao antes ... \n");
                printf("\n");
                break;
            }
            case 0:{
                printf("sistema encerrado com sucesso! \n");
                printf("\n");
                return 0;
            }
            default:{
                printf("opcao invalida \n");
                printf("\n");
                break;
            }
        }
    } flag = false;
}