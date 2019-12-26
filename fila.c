#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct lista{
    int info;
    int id;
    struct lista* prox;
}Lista;

typedef struct fila{
    Lista* inicio;
    Lista* fim;
}Fila;

Fila* cria(){
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

int fila_vazia(Fila* f){
    if (f==NULL)
        return true;
    return (f->inicio==NULL);
}

Fila *inserir(Fila* f, float valor, float identificador){
    Lista* novo = (Lista*)malloc(sizeof(Lista));
    novo->info = valor;
    novo->id = identificador;
    novo->prox = NULL;
    
    if(fila_vazia(f)){
        f->inicio = novo;
    }
    else{
        f->fim->prox = novo;
    }
    f->fim = novo;
  	return f;
}

Fila *remover(Fila* f){ //mudando o tipo da função
    Lista* aux;
    
    if(fila_vazia(f)){
        //printf("fila vazia!");
        return f;
    }
    
    aux = f->inicio;
    f->inicio = aux->prox;
    if(f->inicio == NULL){
        f->fim = NULL;
    }
    free(aux);
  	return f;
}

void libera(Fila** f){
    if(fila_vazia(*f)){
        return;
    }
    
    Lista* var = (*f)->inicio;
    
    while(var != NULL){
        Lista* aux = var->prox;
        free(var);
        var = aux;
    }
    
    free(*f);
    (*f) = NULL;
}

void imprime(Fila* f){
    if(fila_vazia(f)){
        printf("fila vazia!\n");
        return;
    }
    //printf("\n");
    Lista* var;
    
    for(var = f->inicio; var != NULL; var = var->prox){
        printf("ID: %d IDADE: %d\n", var->id, var->info);
    }

}

int main(){
    Fila* naoidoso = cria();
    Fila* idoso = cria();
    
    int id=0, idade=0;
    int n=0; //prioridade para a fila de idosos
    int auxn=0;
    
    scanf(" %d", &n);
    auxn = n;
    char letra=0;
    
    while(letra != 'f'){ //'f': finaliza o programa.
        scanf(" %c", &letra);
        switch (letra){
           case 'a': //'a': adiciona uma nova pessoa na fila. ap?s o 'a' a linha seguinte deve conter o valor do identificador da pessoa (inteiro) e sua idade (inteiro);
             scanf(" %d %d", &id, &idade);
             if(idade > 60){
                idoso = inserir(idoso, idade, id);
                //printf("\n");
             }else{
                naoidoso = inserir(naoidoso, idade, id);
                //printf("\n");
             }
           break;
        
           case 'r': //'r': remove uma pessoa da fila (de idosos ou n?o-idosos) para ser atendida;
             /*if(fila_vazia(idoso) == 0){
                 remover(naoidoso);
             }
             if(fila_vazia(naoidoso) == 0){
                 remover(idoso);
             }
             if(n==0){
                remover(naoidoso);
                //printf("\n");
                n = auxn;
             }
             else{
                remover(idoso);
                //printf("\n");
                n--;
             } */
            if(!(fila_vazia(idoso)) && n > 0){
                    remover(&idoso);
                    n--;
                }else{
                    remover(&naoidoso);
                    n = auxn;
                }
           break;
           
           case 'i': //'i': imprime todos os elementos de cada uma das filas (de idosos ou n?o-idosos);
             printf("fila de idosos:\n");
             imprime(idoso);
             //printf("\n");
             printf("fila de nao-idosos:\n");
             imprime(naoidoso);
             //printf("\n");
             printf("----------\n\n");
           break;
           
           //default:
             //printf("Valor invalido!\n");

        }
    }
    return 0;
}






