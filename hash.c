#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct hash{
    int info;
    struct hash* prox;
}Hash;






void inserir(Hash* tabela[], int posicao, int numerok){
    Hash* novo = (Hash*)malloc(sizeof(Hash));
    novo->info = numerok;
    novo->prox = tabela[posicao];
    tabela[posicao] = novo;
    //return tabela[posicao];
}



//metodo da divisao
//calcula o resto da divisao do valor k pelo tamanho da tabela hash m
int funcaodivisao(int numerok, int m){
    return (numerok & 0x7FFFFFFF) % m;
}

void imprime(Hash* tabela[], int m){
    Hash* aux;
    int i;
    for(i=0; i<m;i++){
        aux = tabela[i];
        printf("[%d]:", i);
        
        if(aux == NULL){
            printf("Lista vazia!");
        }
        
        while(aux != NULL){
            //i é a entrada
            printf("%d=>", aux->info);
            aux = aux->prox;
        }
        
        
        printf("\n");
    }
}

void remover(Hash* tabela[], int numerok, int m){
    int posicao = funcaodivisao(numerok, m);
    Hash* aux;
    if(tabela[posicao] != NULL){
        if(tabela[posicao]->info == numerok){
            aux = tabela[posicao];
            tabela[posicao] = tabela[posicao]->prox;
        }
        else{
            aux = tabela[posicao]->prox;
            Hash* ant = tabela[posicao];

            while((aux != NULL) && (aux->info != numerok)){
                ant = aux;
                aux = aux->prox;
            }

            if(aux != NULL){
                ant->prox = aux->prox;
                free(aux);
            }
            /*else{
                printf("numero nao encontrado!");
            }*/
        }                  
    }
    /*else{
        printf("numero nao encontrado!");
    }*/
}

void criar(Hash* tabela[], int m){
    int i;
    for(i=0;i<m;i++){
        tabela[i] = NULL;
    }
}

/*
int busca_hash(item x) {
 int i = funcaodivisao(x, N);
 int cont = 0;
 // procura x a partir da posição i 
 while (p[i] != x) {
 if (p[i] == VAZIO) return –1; // não achou x, pois há uma vazia 
 if (++cont == M) return –2; // já verificou todos os elementos 
 i = (i+1)%N; // tabela circular 
 }
 //encontrou 
 return i;
}
*/
void procurar(Hash* tabela[], int numerok, int m){
    int posicao = funcaodivisao(numerok, m);
    Hash* aux;
    int kelementos, kacessados=0;
    
    // (i) o número de elementos presentes na tabela
    int i;
    int qtdelementos=0;
    for(i = 0; i < m; i++){
        aux = tabela[i];
        while(aux != NULL){
            if(aux->info != NULL){
                qtdelementos++;
                if(aux->info == numerok){
                    kacessados = qtdelementos;
                }
            }
            aux = aux->prox;
        }
    }
    printf("numero de elementos da tabela hash: %d\n", qtdelementos);

    // (ii) se o elemento em questão foi encontrado ou não
    if(tabela[posicao] != NULL){
        if(tabela[posicao]->info == numerok){
            printf("elemento %d encontrado!\n", numerok);
        }
        else{
            aux = tabela[posicao]->prox;
            Hash* ant = tabela[posicao];

            while((aux != NULL) && (aux->info != numerok)){
                ant = aux;
                aux = aux->prox;
            }

            if(aux != NULL){
                printf("elemento %d encontrado!\n", numerok);
            }
            else{
                printf("elemento nao encontrado!\n");
            }
        }                  
    }
    else{
        printf("elemento nao encontrado!\n");
    }

    //(iii) quantos elementos da tabela foram acessados (inclusive ele próprio) até que o elemento fosse encontrado
    printf("numero de elementos acessados na tabela hash: %d\n", kacessados);
}

/*void ordem(Hash* tabela[], int m){ 
    int posicao = funcaodivisao(numerok, m);
    int i;
    for(i = 0;i<m;i++){
    Hash *aux1 = tabela[i];
    Hash *aux2 = tabela[i];
    Hash* novo = (Hash*)malloc(sizeof(Hash));
    novo->prox = NULL;
    while((aux2!=NULL) && aux2->info < aux1->info){
        aux1 = aux2;
        aux2 = aux2->prox;
    }

    if(aux1 == aux2){
        novo->prox = aux1;
        tabela[i] = novo;
    }
    else{
        novo->prox = aux1->prox;
        aux1->prox = novo;
    }
    }
}*/

int main(){

    int k=0;
    int m; //valor de m
    char letra=0;
    int posicao;
    
    scanf(" %d", &m);
    
    Hash* tabela[m];
    Hash* aux;

    criar(tabela, m);

    while(letra != 'f'){ //'f': finaliza o programa.
        scanf(" %c", &letra);
        switch (letra){
            case 'a': //'a':  a k inserção do elemento "k"
                scanf(" %d", &k);
                posicao = funcaodivisao(k,m);
                inserir(tabela, posicao, k);
            break;
        
            case 'r': //remover elemento
                scanf(" %d", &k);
                remover(tabela, k, m);   
            break;
           
            case 'i': //'i': imprime
                printf("imprimindo tabela hash:\n");
                //ordem(tabela, m);
                imprime(tabela, m);
            break;

            case 'p': //outros dados de um elemento
                scanf(" %d", &k);
                printf("BUSCA POR %d\n", k);
                procurar(tabela, k, m);
            break;
            
            case 'f':
                printf("\n");
            break;
        }
    
    }
    return 0;
}






