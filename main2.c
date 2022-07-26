#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>
#include <time.h>

//devolve o indice da mediana entre o inicio, meio e fim do vetor
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

    //retorna o indice do pivo
    return m;
}

//devolve um indice de um valor aleatorio no vetor
int aleatorio(int vet[], int i, int f){
    //escolhe um indice aleatorio entre o inicio e o final do vetor;
   int aleat = i + ( rand() % f );
   //retorna o indice do pivo
   return aleat;
}

// Troca de lugar os elementos
void swap(int vet[], int pos1, int pos2)
{
    // Copy the first position's element
    int temp = vet[pos1];

    // Assign to the second element
    vet[pos1] = vet[pos2];

    // Assign to the first element
    vet[pos2] = temp;
}

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

//--------------------------------------------------------------
int partitionLomuto(int C[], int left, int right)
//--------------------------------------------------------------
{
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

    //coloca o particionador no inicio para particionar
    swap(vet,inicio,p);

    //particiona e coloca o particionador no seu devido lugar
    if (part ==1 || part ==2){
        particionador = partitionLomuto(vet, inicio, f);
    }
    else{
        particionador = partitionHoare(vet, inicio, f);
    }


    //chama o quick_lomuto nos valores menores q o particionador
    quick(vet,inicio,particionador-1,part);
    //chama o quick_lomuto nos valores maiores q o particionador
    quick(vet,particionador+1,f, part);

}



int main(){
    int vetor[] = {1,2,4,6,10,3,9,8,5};

    //lomuto mediana
    //quick(vetor,0,8,1);

    //lomuto aleatorio
    //quick(vetor,0,8,2);

    //hoare mediana
    quick(vetor,0,8,3);

    //hoare aleatorio
    //quick(vetor,0,8,4);


    for (int x =0;x<9;x++){
        printf ("%d ", x);
    }
    return 0;
}


// SAIDA::
// TAMANHO ENTRADA 100
// SWAPS #SWAPS
// RECURSOES #RECURSOES
// TEMPO #TEMPO EM SEGUNDOS
