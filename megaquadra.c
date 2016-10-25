#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define quadra 4

//impressao dos elementos do vetor
void ImprimeVetor(int vetor[],int TamMax){
	int i;
	printf("[");
	for(i = 0 ; i <= TamMax-1; i++){
		printf("%d ", vetor[i]);
	}
	printf("]\n");
}

//Copia todos os elementos do vetor aleatorio ao vetor auxiliar "vetor_ordenacao"
void Des_Ordenado(int vetor_desordenado[],int vetor_ordenado[],int TamMax){
	int i;
	for (i=0;i<=TamMax;i++)
		vetor_ordenado[i]=vetor_desordenado[i];
}

//Sorteia o "vetor_desordenado" com numeros aleatorios entre 0-NMax
void SorteiaVetor(int vetor[], int TamMax, int NMax){
	int i;

	for(i=0; i <= TamMax-1; i++){
		vetor[i] = rand() %NMax +1;
	}
}
void Troca (int *Vetor, int i, int j) {
	int aux;

	aux = Vetor[i];
	Vetor [i] = Vetor[j];
	Vetor [j] = aux;
}

//Ordena o primeiro,ultimo e o elemento do meio de modo que a mediana entre eles seja colocado na posicao do meio
void Mediana(int v[],int esq,int dir){
	int meio= (esq+dir)/2;	
	if (v[dir] >= v[esq] && v[esq] >= v[meio]) 
		Troca(v,esq,meio);

	else if (v[meio] >= v[esq] && v[esq] >= v[dir]){
		Troca(v,meio,dir);
		Troca(v,meio,esq);
	}  
	else if (v[meio] >= v[dir] && v[dir] >=v[esq]) {
		Troca(v,meio,dir);
	}
	
        else if (v[esq] >= v[dir] && v[dir] >= v[meio]) {
		Troca(v,esq,meio);
		Troca(v,meio,dir);
	}
	else if (v[esq] >= v[meio] && v[meio] >= v[dir]){
		Troca(v,esq,dir);
		Troca(v,meio,esq);
	}
	if (v[dir] >= v[meio] && v[meio] >= v[esq]){
	}

}

//Particiona o Quick Sort Recursivo
int Particao(int v[],int esq,int dir){
	int i, fim;
	Mediana(v,esq,dir);
	Troca(v,dir-1,(esq+dir)/2);//troca o pivo com o elemento mais a direita
	//pescorre o algoritmo de particao da posicao a esquerda ate a direita-1
	fim=esq;	
	for(i=esq+1;i<=dir;i++)
		if(v[i]<v[esq]) 
		Troca(v,++fim,i);
		Troca(v,esq,fim);
	return fim;
}

//Particiona o Quick Sort Iterativo
int Particao_iterativa(int vetor[], int esq, int dir){
	int aux = vetor[dir];
	int i = (esq - 1);
	int j;
	for(j = esq; j <= dir- 1; j++)
	{
		if (vetor[j] <= aux){
			i++;
			Troca(vetor,i,j);
		}
	}
	Troca(vetor,i + 1, dir);
	return (i + 1);
}

//Ordenacao Quick Sort Recursivo
void QuickSort_Recursivo(int v[], int esq, int dir){
	int i;
	if(esq>=dir) return ;
	i=Particao(v,esq,dir);
	QuickSort_Recursivo(v,esq,i-1);
	QuickSort_Recursivo(v,i+1,dir);

}

//Ordenacao Quick Sort Iterativo
void QuickSort_Iterativo(int vetor[], int esq, int dir){
	int k;
	int pilha[ dir + 1 ];
	int top = -1;
	int pivo;
	pilha[ ++top ] = esq;
	pilha[ ++top ] = dir;
	while ( top >= 0 ){
		dir = pilha[ top-- ];
        	esq = pilha[ top-- ];

        pivo = Particao_iterativa( vetor, esq, dir);

        if ( pivo-1 > esq ){
            pilha[ ++top ] = esq;
            pilha[ ++top ] = pivo - 1;
        }
        if ( pivo+1 < dir){
            pilha[ ++top ] = pivo+ 1;
            pilha[ ++top ] = dir;
        }
    }
}

//Ordenacao Select Sort
void SelectSort(int vetor[], int N){
	int i, j, k, menor, aux;
	menor = 0;
	for (i=1; i<N; i++){
		for(j = i+1; j<N; j++){
			if( vetor[j] <vetor[menor] )
				menor = j;
		}
			Troca(vetor,menor,i);	
	}
}

//Ordenacao Bubble Sort
void BubbleSort(int vetor[], int N){
	int i, j, aux;
	for (i = 1; i < N; i++)
		for (j = N; j >= 1; j--)
			if( vetor[j] < vetor[j-1] ){
				Troca(vetor,j,j-1);
			}
}

//Tempo de execucao dos processos de ordenacao
void Tempo_Executa(int NMax,int TamMax) {
	int i,j;
	int vetor[TamMax];// vetor auxiliar de tamanho 100
	clock_t inicio,fim;
	double time_spent; //variavel do tempo final calculado

	printf("  Tempo Decorrido: \n");
	for(j=1;j<=4;j++){
		inicio=clock();
		for (i = 1; i <= 10000; i ++){
			SorteiaVetor(vetor,TamMax,NMax);
			switch(j){
					case 1:QuickSort_Recursivo(vetor, 0, TamMax);	break;
					case 2:SelectSort(vetor, TamMax); break;
					case 3:BubbleSort(vetor, TamMax); break;
					case 4:QuickSort_Iterativo(vetor,0,TamMax);break;			
			}
		}
		fim=clock();
		time_spent=(double)(fim-inicio);

			switch(j){
					case 1:	printf("  Quick Sort Recursivo: %.2f ms\n", (double)(time_spent));
						break;
					case 2:	printf("  Select Sort: %.2f ms\n", (double)(time_spent));	
						break;
					case 3:	printf("  Bubble Sort: %.2f ms\n", (double)(time_spent));
						break;
					case 4: printf("  Quick Sort Iterativo: %.2f ms\n",(double)(time_spent));
						break;
		}
	}
}

//Tentativa do usuario no MegaQuadra
void TentaQuadra(int cliente[],int NMax){
	int i,check;

	printf("\n  Digite os %d numeros para a MegaQuadra: ",quadra);
	printf("  ");
	check=0;

	do{
		for(i = 0; i <=quadra-1; i++){//leitura dos elementos que o usuario deseja apostar
			scanf("%d", &cliente[i]);
		} 
		for(i = 0; i <= 3; i++){
			if (cliente[i] < 0 || cliente[i] > NMax){//confere se o numero escolhido esta dentro do limite 0-NMax
			printf("  ERRO: Numero fora da faixa 0-%d.Insira nova sequencia.\n  ",NMax);
			check=0;
			break;			
			}
			else
			check=1;
		}
	}while(check==0);
}


//Pesquisa sequencial em vetor desordenado
int PesqSeq(int vetor[], int numero, int TamMax){
	int i,aux;
	aux=0;
	for( i = TamMax-1; i >= 0; i--){
		if(vetor[i] == numero)
			aux=1;
	}
	return aux;
}

//Pesquisa Binaria de vetor ordenado
int PesqBin(int vetor[], int numero, int esq, int dir){
	int meio,aux;
	aux = 0;
	do{
		meio = (esq + dir) /2;
		if (numero > vetor[meio])
			esq = meio + 1;
		else
			dir = meio - 1;
	} while ( numero != vetor[meio] && esq <= dir);
	if( numero == vetor [meio])
		aux=1;
	return aux;
}


//Confere se os elementos escolhidos pelo usuario estao contidos no vetor aleatorio
int BuscaQuadra(int vetor_ordenado[],int vetor_desordenado[],int cliente[], int TamMax,int TipoPesq){					
	int cont,i;
	if(TipoPesq==1){//Tipo de pesquisa 1. Sequencial
		cont=0;
		for (i = 0; i <= 3 ; i++){
			if (PesqSeq(vetor_desordenado,cliente[i],TamMax)){				
				cont++;
			}
		}
	return cont;
	}else{//Tipo de pesquisa 2. Binaria
		cont=0;
		for (i = 0; i <= 3 ; i++){
			if (PesqBin(vetor_ordenado,cliente[i],0,TamMax)){				
				cont++;
			}
		}	
	return cont;
	}
}






int Menu(){
	int opc;
	printf("\n-----------------------------------------------------------------------------------------------------");
	printf("\n  Escolha sua opcao: ");
	printf("\n  0.Sair ");
	printf("\n  1.Tentar Mega Quadra ");
	printf("\n  2.Imprimir sequencia de numeros aleatorios ");
	printf("\n  3.Tempo de Execucao ");
	printf("\n  Opcao: ");
	scanf("%d",&opc);
	return opc;
}


int main(){
	system("clear");
	srand(time(NULL));
	int TamMax;// tamanho do vetor aleatorio
	int NMax,i,k;	//valor do limite maximo do vetor aleatorio
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("                                        M E G A   Q U A D R A             				  \n");
	printf("-----------------------------------------------------------------------------------------------------\n");

	printf("  Insira numero de elementos do vetor: ");
	scanf("%d", &TamMax);

	printf("\n  Insira numero máximo de sorteio: ");
	scanf("%d", &NMax);

	int vetor_desordenado[TamMax],vetor_ordenado[TamMax];
	int cliente[4];
	int opc,acertos;

	SorteiaVetor(vetor_desordenado, TamMax, NMax);// Sorteio do vetor aleatorio
	Des_Ordenado(vetor_desordenado,vetor_ordenado,TamMax);// Copia os elementos do vetor aleatorio para um auxiliar
	QuickSort_Iterativo(vetor_ordenado,0,TamMax);// Vetor auxiliar eh ordenado por Quick Sort Iterativo
	
	opc = Menu();		
	while ( opc != 0){
		switch(opc){
				case 1: //Tentativa de jogo
					TentaQuadra(cliente,NMax);
					acertos=BuscaQuadra(vetor_ordenado,vetor_desordenado,cliente,TamMax,1);//Pesquisa Sequencial com vetor desordenado						
					acertos=BuscaQuadra(vetor_ordenado,vetor_desordenado,cliente,TamMax,2); //Pesquisa Binaria com vetor ordenado    
					switch(acertos){
							case 0: //nenhum acerto
								printf("\n  ...Nenhum acerto.Tente Novamente!...\n");
								break;
							case 4: //acertou os 4 numeros sorteados
								printf("\n  ...PARABENS!VOCE ACERTOU TODOS OS NUMEROS!...\n");
								break;
							default:
								printf("\n  ...Parabens!Voce acertou %d numeros!...\n",acertos);
					}
					break;
				case 2: //imprime vetor aleatorio desordenado
					printf("  ");
					ImprimeVetor(vetor_desordenado,TamMax);	
					break;						
				case 3: //Tempo de execucao dos tipos de ordenacao
					Tempo_Executa(NMax,TamMax);
					break;	
				
				default://escolha diferente entre 1-3
					printf("\n  ...Opcao Invalida...");
					 break;
		}
		opc=Menu();
	}
	return 0;
}
