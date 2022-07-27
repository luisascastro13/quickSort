#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>
#include <time.h>

int SWAPS = 0;
int RECURSOES = 0;
char filename[] = "entrada-quicksort.txt";

// Troca de lugar os elementos
void swap(int vet[], int pos1, int pos2){
    // Copy the first position's element
    int temp = vet[pos1];

    // Assign to the second element
    vet[pos1] = vet[pos2];

    // Assign to the first element
    vet[pos2] = temp;

    SWAPS = SWAPS + 1;
}

//devolve o indice da mediana entre o inicio, meio e fim do vetor, bota o particionador escolhido no inicio
int medianaDeTres(int vet[], int i, int f){
    int pivo, aux, indice;
    int m = floor((f-i)/2);
    int inicio, meio, final;

    inicio = vet[i];
    meio   = vet[m];
    final  = vet[f];

    if(inicio > meio){
        if(meio > final){
            //inicio > meio > fim
            pivo = meio;
            indice = m;

        }
        else{
            if(inicio > final){
                //inicio > final > meio
                pivo = final;
                indice = f;
            }
            else{
                //final > inicio > meio
                pivo = inicio;
                indice = i;
            }
        }

    }
    else{
        if(meio > final){
            if(inicio > final){
                //meio > inicio > final
                pivo = inicio;
                indice = i;
            }
            else{
                //meio > final > inicio
                pivo = final;
                indice = f;
            }
        }
        else{
            //final > meio > inicio
            pivo = meio;
            indice = m;
        }
    }
    //coloca o particionador na frente e troca com o primeiro
    swap(vet,i,indice);

    //retorna o indice do pivo
    return indice;
}

//devolve um indice de um valor aleatorio no vetor, bota o particionador escolhido no inicio
int aleatorio(int vet[], int i, int f){
    //escolhe um indice aleatorio entre o inicio e o final do vetor;
   int aleat = i + ( rand() % f );
   //coloca o particionador na frente e troca com o primeiro
   swap(vet,i,aleat);
   //retorna o indice do pivo
   return aleat;
}

//particiona o vetor de acordo com a tecnica de hoare
int partitionHoare(int vet[], int ini, int fim){

    int i = ini;
    int f = fim;
    int pivo = vet[i];

    while (i<f){
        while(vet[f] > pivo && i < f) f--;
        vet[i] = vet[f];
        while(vet[i] <= pivo && i < f) i++ ;
        vet[f] = vet[i];
    }
    vet[f] = pivo;
    return i;

}

//particiona o vetor de acordo com a tecnica de lomuto
int partitionLomuto(int C[], int left, int right){
    int chave = C[left];
    int storeindex = left + 1;  // Index of smaller element

    for (int i = left+1; i <= right; i++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (C[i] < chave)
        {
            swap(C, i, storeindex);
            storeindex++;    // increment index of smaller element
        }
    }
    swap(C, left, storeindex-1);

    return (storeindex-1);
}

//recebe o vetor, indices de inicio e fim e qual estrategia de particionador
void quick(int vet, int inicio, int f, int part){

    int p;
    int particionador;
    //p é o valor do indice que contem o pivô

     if (inicio >= f) {
        return;
    }

    switch (part){
        //part 1 == MEDIANA DE TRES
        case 1:
        case 3:
            p = medianaDeTres(vet, inicio, f);
            break;
        //part 2 == ALEATORIO
        case 2:
        case 4:
            p = aleatorio(vet, inicio, f);
            break;
    }

    //particiona e coloca o particionador no seu devido lugar
    if (part ==1 || part ==2){
        RECURSOES++;
        particionador = partitionLomuto(vet, inicio, f);
    }
    else{
        RECURSOES++;
        particionador = partitionHoare(vet, inicio, f);
    }

    //chama o quick_lomuto nos valores menores q o particionador
    quick(vet,inicio,particionador-1,part);
    //chama o quick_lomuto nos valores maiores q o particionador
    quick(vet,particionador+1,f, part);
}

//faz a leitura dos vetores no arquivo e executa o ordenamento
int main(){

        FILE *in_file = fopen(filename, "r");
        int linha = 0;
        int size;
        int *vetor;

        //variaveis auxiliares para calcular o tempo de execucao
        clock_t t;

        struct stat sb;
        stat(filename, &sb);

        char *file_contents = malloc(sb.st_size);

        //percorre o arquivo linha por linha ate terminar.
        //salva cada linha na variavel file_contents.
        while (fscanf(in_file, "%[^\n] ", file_contents) != EOF) {
            linha++; //pra comecar em 1
            //le a quantidade de numeros, primeiro numero no arquivo
            char *token;
            token = strtok(file_contents, " ");

            int i=0; //contador para saber se é o primeiro token

            while(token != NULL){
                    //se for o primeiro token, eh o tamanho do vetor
                    if(i==0){
                        size = atoi(token);
                        vetor = (int *)malloc(size * sizeof(int));
                    }
                    token = strtok(NULL, " ");
                    vetor[i] = atoi(token);
                    i++;
            }

        // printf("\nVETORZINHO NOVO NA AREA!!!");
        printf("\n");
        t = clock();

        //ESCOLHA UMA ENTRE AS QUATRO OPCOES ABAIXO APENAS REMOVENDO O COMENTARIO

        //lomuto mediana
        quick(vetor,0,size,1);

        //lomuto aleatorio
        //quick(vetor,0,tam,2);

        //hoare mediana
        //quick(vetor,0,tam,3);

        //hoare aleatorio
        //quick(vetor,0,tam,4);

        t = clock() - t;

        printf ("\nTAMANHO ENTRADA %d", size);
        printf ("\nSWAPS %d", SWAPS);
        printf ("\nRECURSOES %d",RECURSOES);
        printf("\nTEMPO%lf\n",((double)t)/((CLOCKS_PER_SEC)));

    }
    return 0;
}
