#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TamFila 5 //Constante que controla o tamanho da fila (estatica)


//Estrutura dos dados da Lista, Fila e Pilha:
typedef struct _elemlista{
	char banda[30];
	char album[30];
	float preco;
	struct _elemlista *prox;
}ElemLista;

typedef struct _lista{
	ElemLista *inicio;
	ElemLista *final;
}Lista;

typedef struct _clientes{
		Lista *lista;
		char nome[30];
}Clientes;

typedef struct _fila {
	Clientes clientes[TamFila];
	int inicio,final;
}Fila;

typedef struct _recibos{
	float precototal;
	char nome[30];
	struct _recibos *prox;
}Recibos;           

typedef struct _pilharecibos{
	Recibos *topo;		
}PilhaRecibos;

//Inicializacao do TAD lista com alocacao dinamica de memoria, utilizado na funcao EnfileraCliente
Lista  *InicLista(){
	Lista *lista;
	lista=(Lista *)malloc(sizeof(Lista)); //Alocacao de memoria para a lista
	lista->inicio=(ElemLista *)malloc(sizeof(ElemLista));
	lista->final=lista->inicio;
	lista->final->prox=NULL;
	return lista;
}

//Inicializacao do TAD fila com alocacao estatica de memoria, utilizado no inicio do programa (funcao main)
void InicFila(Fila *fila){
	fila->inicio=fila->final=0; //Começo da fila iniciado na posicao 0
}

//Inicializacao do TAD pilha com alocacao dinamica de memoria, utilizado no inicio do programa (funcao main) 
PilhaRecibos *InicPilha(PilhaRecibos *_pilha){
	PilhaRecibos *pilha;
	pilha=(PilhaRecibos *)malloc(sizeof(PilhaRecibos));
	pilha->topo=(Recibos *)malloc(sizeof(Recibos));
	pilha->topo->prox=NULL;
	return pilha;
}

//Funcao que retorna se a fila estah vazia ou nao, utilizada na opcao 2 - Remover cliente do menu    (1 para fila vazia; 0 para fila nao vazia)
int VaziaFila(Fila fila) {
	return(fila.final==fila.inicio);
}

//Funcao que retorna se a fila estah cheia ou nao, utilizada como limite de insercao de clientes     (1 para fila cheia; 0 para fila nao cheia)
int CheiaFila(Fila fila){
	return((fila.final+1)%TamFila==fila.inicio); //A verificacao é feita com mod do tamanho maximo por se tratar de um vetor circular
}

//Funcao que retorna se a pilha estah vazia ou nao, utilizada na opcao 3 - Imprimir recibos do menu  (1 para pilha vazia; 0 para pilha nao vazia)
int VaziaPilha(PilhaRecibos pilha){
	return(pilha.topo->prox==NULL);
}

//Funcao que realiza a leitura dos itens da lista de compras do cliente
void InsereLista(Lista *lista){   
			
	lista->final->prox=(ElemLista *)malloc(sizeof(ElemLista)); //Alocando memoria para inserir os itens da lista 
	lista->final=lista->final->prox;
   	lista->final->prox = NULL;

   	printf("-------------------------------------------\n");
	printf("\n  Insira nome de banda: ");
	scanf("\n");
	scanf("%[^\n]",lista->final->banda);
	printf("  Insira nome de album: ");
	scanf("\n");
	scanf("%[^\n]",lista->final->album);
	printf("  Insira preco: ");
	scanf("%f",&lista->final->preco);


}

//Funcao para inserir um cliente na fila
int EnfileraCliente(Fila *fila) {
	int nvinis,i;
	system("clear");
	if(CheiaFila(*fila))
			return 0;
	else{

		Lista *lista;
	   	lista=InicLista();     //Inicio da lista
		fila->clientes[fila->final].lista = lista;

	   //Leitura dos dados da compra
		printf("\n");
		printf("  Insira nome completo: ");
		scanf("\n");
		scanf("%[^\n]",fila->clientes[fila->final].nome);
		printf("  Insira numero de vinis que deseja comprar: "); 
		scanf("%d",&nvinis);

		for(i=0;i<nvinis;i++){
			InsereLista(fila->clientes[fila->final].lista);	  //Leitura de cada elemento da lista 	
		}                          
		
		return 1;
	}
}

//Funcao que faz a soma dos precos de todos os albuns da lista de compras do cliente
float PrecoTotal(Lista *lista){
	float soma;
	ElemLista *aux;
	aux=lista->inicio->prox;
	soma=0;

	while(aux!=NULL){
		soma=soma+aux->preco;
		aux=aux->prox;
	}
	free(lista);
	return soma;
}

//Funcao que empilha um novo recibo, calculando o preco total das compras do cliente removido da fila
void PushRecibos(PilhaRecibos *pilha,Fila *fila){
	Recibos *aux;
	aux=(Recibos *)malloc(sizeof(Recibos));
	float precototal = PrecoTotal(fila->clientes[fila->inicio].lista);

	aux->prox=pilha->topo;
	pilha->topo->precototal=precototal;
	strcpy(pilha->topo->nome,fila->clientes[fila->inicio].nome);
	pilha->topo=aux;
	
}

//Funcao que contabiliza o valor total da compra do primeiro cliente da fila e cria o respectivo recibo e insere o mesmo na pilha de recibos
int DesenfileraCliente(Fila *fila,PilhaRecibos *pilha){
	if (VaziaFila(*fila))
		return 0;
	else{	
		PushRecibos(pilha,fila);		
		 	
		return 1;
	}
}

//Funcao que faz a impressao da fila de clientes, verifica se a mesma esta vazia, se nao estiver, imprime os clientes que estao na fila
int ImprimeFila(Fila fila){	
	int aux;

	if (VaziaFila(fila))
		return 0;
	else{
		system("clear");
		printf(" ------------- Fila de clientes -------------\n"); 
		aux= fila.inicio;
		while(aux!=fila.final){
			printf(" - %s\n",fila.clientes[aux].nome);
			aux = (aux+1) % TamFila;
		}
		return 1;
	}
}

//Funcao que realiza a inversao da pilha de recibos, para que a impressao dos recibos seja feita na ordem de chegada dos clientes 
//		(o primeiro cliente a chegar é o primeiro a ser impresso)

void InvertePilha(PilhaRecibos *pilha,PilhaRecibos *aux){
	Recibos *i;
	for(i=pilha->topo->prox;i!=NULL;i=i->prox){
		Recibos *novotopo;
		novotopo=(Recibos *)malloc(sizeof(Recibos));
		novotopo->prox=aux->topo;
		aux->topo->precototal=i->precototal;
		strcpy(aux->topo->nome,i->nome);           
		aux->topo=novotopo;
	}
}

// Funcao que faz a impressao dos recibos das compras dos clientes, onde e utilizada a inversao de pilha descrita acima
int ImprimeRecibos(PilhaRecibos *pilha,Fila fila){
	if(!VaziaFila(fila))
		return 0;       //Os recibos nao podem ser impressos caso ainda tenha clientes na loja, ou seja, se a fila nao estiver vazia
	else if(VaziaPilha(*pilha))
		return -1;	    //Se nenhum recibo foi feito (pilha de recibos vazia) nao pode ser feita a impressao dos mesmos
	else {	

		Recibos *i;	      //Criando uma variavel auxiliar para percorrer a pilha
		PilhaRecibos *aux;
		aux=InicPilha(aux);
		
		InvertePilha(pilha,aux); //Inversao da pilha
	
		system("clear");
		printf("  ------------- Recibos -------------\n");
		printf("\n");
		for(i=aux->topo->prox;i!=NULL;i=i->prox){
			printf("  %s --------------------------- Total R$ %0.2f\n",i->nome,i->precototal);					
		}
		return 1;
	}
}

//Funcao que faz a gerencia da opcao selecionada do menu e direciona o programa para a funcao desejada                 
void opcoes(Fila *fila,int opc,PilhaRecibos *pilha){
	int aux;
	switch(opc){
	         	
				case 0://	Opcao 0 selecionada
						free(pilha); //Antes de sair eh realizada a desalocação da memoria utilizada pela pilha
						break;

			   case 1: //	Opcao 1 selecionada 
						if(!EnfileraCliente(fila)){
							system("clear");
					  		printf(" ...ERRO:Fila Cheia...\n");						
						}else{
							system("clear");
							printf("\n ...Cliente %s inserido com sucesso...\n",fila->clientes[fila->final].nome);
							fila->final = (fila->final+1) % TamFila; 
						}
						break;

				case 2://	Opcao 2 selecionada 					  	
						if(!DesenfileraCliente(fila,pilha)){
							system("clear");
							printf("\n  ...ERRO:Fila Vazia...\n");
						}else{
							system("clear");
							printf("\n  ... Cliente %s removido da fila ...\n",fila->clientes[fila->inicio].nome);
							fila->inicio=(fila->inicio+1) % TamFila; }
						break;

				case 3://	Opcao 3 selecionada
						aux = ImprimeRecibos(pilha,*fila);
						if(aux==0){
							system("clear");
							printf("\n  ...ERRO: Ainda ha clientes na fila..\n");
						}else if(aux==-1){
							system("clear");
							printf("\n  ...Nenhum cliente...\n");
						}else{
							printf("\n");
						}
						break;

				case 4://	Opcao 4 selecionada					   
						if (!ImprimeFila(*fila)){
 							system("clear");
							printf("\n  ...Fila vazia...\n");
						}else{
							printf("\n");
						}
						break;

				default://	Opcao invalida
						system("clear");
						printf("\n ...Opcao Invalida...\n");
	}
}



int main(void){ 
	
	system("clear");
																								  
	Fila fila;
	PilhaRecibos *pilha;

	pilha=InicPilha(pilha);		//Iniciacao da pilha de recibos
	InicFila(&fila);           //Iniciacao da fila de clientes

	
	int opc;
	
	//Menu de opcoes
	do{
		printf("\n");
		printf("  Escolha sua opcao: \n");
		printf("  0.Sair. \n");
		printf("  1.Inserir cliente. \n");
		printf("  2.Remover cliente. \n");
		printf("  3.Imprimir recibos. \n");
		printf("  4.Mostrar fila. \n");
		printf("\n  Opcao: ");
	   scanf("%d",&opc);
 	   opcoes(&fila,opc,pilha); //Funcao que direciona o programa para a funcionalidade escolhida
	}while(opc!=0);
	
}
