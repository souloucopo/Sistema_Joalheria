#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
#define MAXC 10

typedef struct{
	int marcaBonus; /*marca o bônus do cliente para que, tendo o teto alterado,
					não venha causar impacto no mesmo*/
	int ultBonus;//armazena o valor do bonus inicial antes da compra
	int teto;//quantidade máxima possível, inicia R$100,00
	float valor; //valor de 1 bônus, inicia com R$0,50
	float valorBonificar; //valor para receber bonus, inicia com R$100,00
}tBonus;

typedef struct{
	float valorCompra;//valor da produto a ser comprado
	float compra;//armazena o valor bruto do produto antes do desconto
	int compraCancelada;//onde armazena o valor 1 para que se identifique a compra cancelada
	tBonus pontos;//direciona a estrutura onde se localiza as configurações de bônus
}tCompra;

typedef struct{
	char nome[50];//armazena o nome do cliente
	char CPF[12];//armazena o CPF do cliente
	char telefone[15];//armazena o telefone do cliente
	char email[30];//armazena o email do cliente
	int bonus;//armazena a quantidade de bonus de um cliente
	float totalCompra;//armazena o valor total de todas as compras do cliente
	tCompra ultimaCompra;//direciona a estrutura onde se localiza as informações de compra
}tCliente;

int procuraCPF(tCliente pessoa[MAX], char CPF[15], int quant){
	/*procura o CPF digitado em "fCadastro" e verifica se o CPF digitado é
	existente no banco de dados ou não. A variável "i" é usada para fazer a contagem
	e localização do CPF desejado. Os parâmetros "tCliente pessoa[MAX]", "CPF[15]" e
	"quant", são responsáveis, respectivamente, fazer a comparação do CPF digitado em
	"fCadastro" que está armazenado no parâmetro "CPF[15]" e efetuar a contagem até o
	limite máximo de clientes armazenados no parâmetro "quant". A variável "achou, retorna
	o valor para a função "fCadastro"*/
	int i;
	int achou;
	for(i=0;i<quant;i++){
		if(strcmp(CPF, pessoa[i].CPF)==0){
			printf("==============================\n");
			printf("Erro: CPF ja cadastrado!\n");
			printf("==============================\n");
			achou = -1;
			break;
		}
	}
	return achou;
}

int identificaCPF(tCliente pessoa[MAX], char CPF[15], int quant){
	/*procura o CPF digitado em "fAlterar" em outras funções futuramente utilizadas
     e verifica se o CPF digitado é existente ou não. Assim como a função "procuraCPF",
	 todas as variáveis e parâmetros presentes tem as mesmas funções.*/
	int i;
	int achou;
	for(i=0;i<quant;i++){	
		if(strcmp(CPF, pessoa[i].CPF)==0){
		achou = -1;
		break;
	}
	}
	if(strcmp(CPF, pessoa[i].CPF)!=0){
		printf("==============================\n");
		printf("Erro: CPF nao cadastrado!\n");
		printf("==============================\n");
		achou = 0;
	}	
	return achou;
}

void compraMaior(int quant, tCliente pessoa[MAX], float valor){
	/*Essa função é responsável em imprimir todos os dados dos clientes com um
	valor superior ao valor estipulado na função "listarClienteCompra". A variável
	"i" faz a contagem até o limite máximo dado pelo parâmetro "quant" que possui a
	quantidade total de todos os clientes. O parâmetro "tCliente pessoa[MAX]" que, possui
	todos os dados dos clientes vai receber uma filtragem de seus dados e apenas exibir
	os dados dos clientes com compras acima do valor estipulado no parâmetro "valor".*/
	int i;
	for(i=0;i<quant;i++){
		if(valor<pessoa[i].totalCompra){
			printf("\n");
			printf("Cliente %d\n", i+1);
			printf("\n");
			printf("Valor total em compras: %.2f\n", pessoa[i].totalCompra);
			printf("\n");
			printf("==============================\n");
		}
	}
}

void compraIgual(int quant,tCliente pessoa[MAX], float valor){
	/*Essa função é responsável em imprimir todos os dados dos clientes com um valor
	igual ao valor estipulado no parâmetro "valor" direcionado da função "listarClienteCompra".
	A variável "i" faz a contagem até o limite máximo dado pelo parâmetro "quant" que possui a
	quantidade total de todos os clientes. O parâmetro "tCliente pessoa[MAX]" que, possui
	todos os dados dos clientes vai receber uma filtragem de seus dados e apenas exibir
	os dados dos clientes com compras acima do valor estipulado no parâmetro "valor".*/
	int i;
	for(i=0;i<quant;i++){
		if(valor==pessoa[i].totalCompra){
			printf("\n");
			printf("Cliente %d\n", i+1);
			printf("\n");
			printf("Valor total em compras: %.2f\n", pessoa[i].totalCompra);
			printf("\n");
			printf("==============================\n");
		}
	}
}

void compraMenor(int quant, tCliente pessoa[MAX], float valor){
	/*Essa função é responsável em imprimir todos os dados dos clientes com um valor
	menor ao valor estipulado no parâmetro "valor" direcionado da função "listarClienteCompra".
	A variável "i" faz a contagem até o limite máximo dado pelo parâmetro "quant" que possui a
	quantidade total de todos os clientes. O parâmetro "tCliente pessoa[MAX]" que, possui
	todos os dados dos clientes vai receber uma filtragem de seus dados e apenas exibir
	os dados dos clientes com compras acima do valor estipulado no parâmetro "valor".*/
	int i;
	for(i=0;i<quant;i++){
		if(valor>pessoa[i].totalCompra){
			printf("\n");
			printf("Cliente %d\n", i+1);
			printf("\n");
			printf("Valor total em compras: %.2f\n", pessoa[i].totalCompra);
			printf("\n");
			printf("==============================\n");
		}
	}
}

void alteraCPF(int quant, tCliente pessoa[MAX], char CPF[15]){
	/*Essa função é responsável em alterar o CPF do cliente desejado. A variável
	CPF[15] recebe o valor do novo CPF do cliente para alteração e leva a um
	comando de repetição(que tem limite estipulado pelo parâmetro "quant")
	 onde será feita uma busca para saber se o novo CPF é igual ao CPF de outro 
	 cliente ou não através do parâmetro "tCliente pessoa[MAX]".
	 Se sim, ele irá interromper a procura sem alterações, caso contrário,
	 a função alterará o CPF do cliente para o novo CPF desejado.*/
	char nCPF[15];
	int i;
	do{
	printf("Digite um novo CPF: ");
	scanf("%s", nCPF);
	printf("\n");
	}while(procuraCPF(pessoa, nCPF, quant)==-1);
    for(i=0;i<quant;i++){
    	if(strcmp(CPF, pessoa[i].CPF)==0){
		if(strcmp(nCPF, pessoa[i].CPF)!=0){
		strcpy(pessoa[i].CPF, nCPF);
		printf("\n");
		printf("Dados alterados com sucesso ;)\n");
		printf("\n");
		break;
	printf("=============================\n");
		}
	}
	}
	
}

void alteraNome(int quant, tCliente pessoa[MAX], char CPF[15]){
	/*Essa função é responsável em alterar o nome do cliente desejado. A variável
	nome[100] recebe o valor do novo CPF do cliente para alteração e leva a um
	comando de repetição(que tem limite estipulado pelo parâmetro "quant")
	 onde será feita uma busca do nome é igual ao de outro 
	 cliente ou não através do parâmetro "tCliente pessoa[MAX]".
	 Se sim, ele irá interromper a procura sem alterações, caso contrário,
	 a função alterará o nome do cliente para o novo nome desejado.*/
	char nome[100];
	int i;
	printf("Digite um novo nome: ");
	scanf("%s", nome);
	printf("\n");
	for(i=0;i<quant;i++){
		if(strcmp(CPF, pessoa[i].CPF)==0){
		strcpy(pessoa[i].nome, nome);
		printf("\n");
		printf("Dados alterados com sucesso ;)\n");
		break;
	printf("\n");
	printf("=============================\n");
	}
	}
	
}

void alteraTelefone(int quant, tCliente pessoa[MAX], char CPF[15]){
	/*Essa função é responsável em alterar o telefone do cliente desejado. A variável
	telefone[15] recebe o valor do novo telefone do cliente para alteração e leva a um
	comando de repetição(que tem limite estipulado pelo parâmetro "quant")
	 onde será feita uma busca do telefone é igual ao de outro 
	 cliente ou não através do parâmetro "tCliente pessoa[MAX]".
	 Se sim, ele irá interromper a procura sem alterações, caso contrário,
	 a função alterará o telefone do cliente para o novo telefone desejado.*/
	char telefone[15];
	int i;
	printf("Digite um novo telefone: ");
	scanf("%s", telefone);
	printf("\n");
	for(i=0;i<quant;i++){
		if(strcmp(CPF, pessoa[i].CPF)==0){
		strcpy(pessoa[i].telefone, telefone);
		printf("\n");
		printf("Dados alterados com sucesso ;)\n");
		printf("\n");
		break;
	printf("=============================\n");
	}
	}
	
}

void alteraEmail(int quant, tCliente pessoa[MAX], char CPF[15]){
	/*Essa função é responsável em alterar o nome do cliente desejado. A variável
	email[50] recebe o valor do novo email do cliente para alteração e leva a um
	comando de repetição(que tem limite estipulado pelo parâmetro "quant")
	 onde será feita uma busca do email é igual ao de outro 
	 cliente ou não através do parâmetro "tCliente pessoa[MAX]".
	 Se sim, ele irá interromper a procura sem alterações, caso contrário,
	 a função alterará o email do cliente para o novo email desejado.*/
	char email[50];
	int i;
	printf("Digite um novo e-mail: ");
	scanf("%s", email);
	printf("\n");
	for(i=0;i<quant;i++){
		if(strcmp(CPF, pessoa[i].CPF)==0){
		strcpy(pessoa[i].email, email);	
		printf("\n");
		printf("Dados alterados com sucesso ;)\n");
		printf("\n");
		break;
	printf("=============================\n");
	}
	}
	
}

void fCadastro(int quant, tCliente pessoa[MAX]){
	/*Essa função é responsável de cadastrar todos os dados do cliente e armazená-los
	no parâmetro "tCliente pessoa[MAX]". O parâmetro "quant" conta e armazena a quantidade
	dos clientes cadastrados.*/
	for( ; ; ){
		printf("Cliente %d\n", quant+1);
		printf("\n");
		printf("Digite o CPF: ");
		scanf("%s", pessoa[quant].CPF);
		/*Abaixo, a função "procuraCPF" é usada para verificar a existência do CPF
		digitado em dados de outros clientes e passar a informação para essa função.*/
		if(procuraCPF(pessoa, pessoa[quant].CPF, quant)==-1){
			break;
		}
		printf("Digite o nome: ");
		scanf("%s", pessoa[quant].nome);
		printf("Digite o telefone: ");
		scanf("%s", pessoa[quant].telefone);
		printf("Digite o e-mail: ");
		scanf("%s", pessoa[quant].email);
		printf("Bonus: %d\n", pessoa[quant].bonus=0);
		printf("Valor total em compras: %.2f\n", pessoa[quant].totalCompra=0);
		printf("=============================\n");
		printf("\n");
		printf("CLIENTE CADASTRADO!\n");
		printf("\n");
		printf("=============================\n");
		break;
	}
}

void fAlterar(int quant, tCliente pessoa[MAX]){
	/*Altera os dados existentes dos clientes. Nessa função é apresentado um
	submenu onde existe a opção de alterar cada dado do cliente individualmente.
	Os parâmetros "quant" e "tCliente pessoa[MAX]" são responsáveis por guardar a
	quantidade de clientes e os dados de cada um separadamente. o vetor "CPF[15]"
	recebe o valor do CPF do cliente onde se deseja alterar algum dado e a variável
	"select" armazena a escolha de alteração presente no submenu.*/
	char CPF[15];
	int select;
	for( ; ; ){
	printf("Digite o CPF do cliente: ");
	scanf("%s",CPF);
	/*A função "identificaCPF" presente abaixo verifica se o CPF do 
	cliente está ou não cadastrado no sistema.*/
	if(identificaCPF(pessoa, CPF, quant)==0){
		break;
	}
	printf("=================================\n");
	printf("MENU DE ALTERACAO DE DADOS DOS CLIENTES\n");
	printf("\n");
	printf("1 - Alterar CPF\n");
	printf("2 - Alterar nome\n");
	printf("3 - Alterar telefone\n");
	printf("4 - Alterar e-mail\n");
	printf("0 - Voltar ao menu principal\n");
	printf("\n");
	printf("Selecione a opcao desejada: ");
	scanf("%d", &select);
	printf("==================================\n");
	if(select==1){
		/*Esse comando chama a função que altera o CPF.*/
		alteraCPF(quant, pessoa, CPF);
		break;
	}
	else if(select==2){
		/*Esse comando chama a função que altera o nome.*/
		alteraNome(quant, pessoa, CPF);
		break;
	}
	else if(select==3){
		/*Esse comando chama a função que altera o telefone.*/
		alteraTelefone(quant, pessoa, CPF);
		break;
	}
	else if(select==4){
		/*Esse comando chama a função que altera o e-mail.*/
		alteraEmail(quant, pessoa, CPF);
		break;
	}
	else if(select==0){
		break;
	}
	}
}

void fConsultar(int quant, tCliente pessoa[MAX]){
	/*A função "fConsultar" é responsável por exibir os dados dos clientes desejado.
	Nela, os parâmetros "quant" e "tCliente pessoa[MAX]" são usados para analisar todos
	os dados dos clientes em um comando de repetição e retornar esse valor como posição
	do seu respectivo parâmetro. As variáveis "i" e "CPF[15]" são usadas para contagem
	do comando de repetição e para armazenar o valor do CPF do cliente que se deseja
	consultar os dados.*/
	int i;
	char CPF[15];
	if(quant==0){
		printf("==================================\n");
		printf("\n");
		printf("NAO HA DADOS EXISTENTE DE CLIENTES\n");
		printf("\n");
		printf("==================================\n");	
		}
	for(i=0;i<quant;i++){
		
	printf("Digite o CPF do cliente: ");
	scanf("%s", CPF);
	printf("==================================\n");
	/*Abaixo, a função "identificaCPF" analisa se o CPF do cliente está ou não cadastrado*/
	if(identificaCPF(pessoa, CPF, quant)==0){
		break;
	}
		if(strcmp(CPF, pessoa[i].CPF)==0){
		printf("Cliente %d\n", i+1);
		printf("\n");
		printf("Nome: %s\n", pessoa[i].nome);
		printf("CPF: %s\n", pessoa[i].CPF);
		printf("Telefone: %s\n", pessoa[i].telefone);
		printf("E-mail: %s\n", pessoa[i].email);
		printf("Bonus: %d\n", pessoa[i].bonus);
		printf("Total de compras: R$%.2f\n", pessoa[i].totalCompra);
		printf("======================================\n");
		}
	}
}

void fRemover(int *marcar, int quant, tCliente pessoa[MAX]){
	/*A função "fRemover" é responsável por encontrar e excluir todos os dados referente
	a um determinado cliente. Nela, os parâmetros "quant" e "tCliente pessoa[MAX]" são
    usados para analisar todos os dados dos clientes em um comando de repetição e 
	retornar esse valor como posição do seu respectivo parâmetro. As variáveis "i"
	 e "CPF[15]" são usadas para contagem do comando de repetição e para armazenar o 
	 valor do CPF do cliente que se deseja remover os dados.*/
	int i, j;
	int escolha;
	char CPF[15];
	
	for(i=0;i<quant;i++){
	printf("Digite o CPF do cliente: ");
	scanf("%s", CPF);
	
	if(identificaCPF(pessoa, CPF, quant)==0){
		break;
	}
		if(strcmp(CPF, pessoa[i].CPF)==0){
		printf("======================================\n");	
		printf("Cliente %d\n", i+1);
		printf("\n");	
		printf("Nome: %s\n", pessoa[i].nome);
		printf("CPF: %s\n", pessoa[i].CPF);
		printf("Telefone: %s\n", pessoa[i].telefone);
		printf("E-mail: %s\n", pessoa[i].email);
		printf("Bonus: %d\n", pessoa[i].bonus);
		printf("Total de compras: %.2f\n", pessoa[i].totalCompra);
		printf("======================================\n");
		printf("\n");
		printf("Tem certeza que deseja remover este item[1 - sim <outro valor> - nao]?\n");
		scanf("%d", &escolha);
		printf("\n");
		if(escolha==1){
			for(j=i;j<quant;j++){
			strcpy(pessoa[j].nome, pessoa[j+1].nome);
			strcpy(pessoa[j].CPF, pessoa[j+1].CPF);
			strcpy(pessoa[j].telefone, pessoa[j+1].telefone);
			strcpy(pessoa[j].email, pessoa[j+1].email);
			pessoa[j].bonus = pessoa[j+1].bonus;
			pessoa[j].totalCompra = pessoa[j+1].totalCompra;
			
			}
			printf("=================================\n");
			printf("\n");
			printf("CADASTRO DO CLIENTE EXCLUIDO!\n");
			printf("\n");
			printf("=================================\n");
			*marcar = 1;
			break;
		}else  if(escolha!=1){
			printf("=================================\n");
			printf("\n");
			printf("CADASTRO DO CLIENTE NAO EXCLUIDO!\n");
			printf("\n");
			printf("=================================\n");
			*marcar = 0;
			break;
		}
		}
	}
}

void valorPagamentoBonus(int *marcar, float *pagaCliente, float valorAtual,int quantC,
 int quant, tCliente pessoa[MAX], tCompra compra[MAX][MAXC]){
 	/*A função "valorPagamentoBonus" é responsável por efetuar o pagamento do cliente
	 que usou bônus. Os parâmetros "pagaCliente"(onde será digitado o valor do pagamento
	 do cliente), "valorAtual"(onde está armazenado o valor descontado do cliente),
	 "quantC" (que é a posição onde se armazenará o valor do produto comprado na matriz
	 bidimensional "tCliente compra[MAX][MAXC]"), "quant"(que guarda do posição do 
	 cliente que fez a compra), "tCliente pessoa[MAX]"(usado para se armazenar algum dado
	 do cliente) e "tCompra compra[MAX][MAXC]"(responsável por armazenar os dados
	 de compra dos clientes) são apresentadas na função. As variáveis, "escolha" e
	 "pagaCliente1" são usadas para escolher fornecer mais dinheiro a compra quando o
	 mesmo é insuficiente e guardar o dinheiro a ser fornecido caso a escolha for afirmativa.*/
	int escolha;
	float pagaCliente1;
	printf("==============================\n");
	printf("\n");
	printf("Digite o valor do pagamento do cliente: R$");
	scanf("%f", pagaCliente);
	printf("\n");
	printf("==============================\n");
	while(*pagaCliente<0){
		printf("\n");
		printf("Erro! Valor negativo. Digite novamente: R$");
		scanf("%f", pagaCliente);
		printf("\n");
		printf("==============================\n");
	}
	while(valorAtual>*pagaCliente){
		printf("==============================\n");
		printf("\n");
		printf("Erro: Valor do pagamento inferior ao valor da compra.\n");
		printf("\n");
		printf("Deseja fornecer mais dinheiro?[1-sim <outro valor>-nao]\n");
		scanf("%d", &escolha);
		printf("\n");
		printf("==============================\n");
		if(escolha==1){
			printf("\n");
			printf("Digite a quantia a ser fornecida: R$");
			scanf("%f", &pagaCliente1);
			printf("\n");
			printf("==============================\n");
			*pagaCliente+=pagaCliente1;
		}else if(escolha!=1){
			printf("\n");
			printf("COMPRA NAO EFETIVADA. Valor devolvido ao cliente: R$%.2f\n",
			*pagaCliente);
			printf("\n");
			printf("==============================\n");
			*marcar = 0;
			break;
		}
	}
	if(*pagaCliente>=valorAtual){
		printf("=================================\n");
		printf("\n");
		printf("COMPRA EFETIVADA!\n");
		printf("\n");
		printf("TROCO: %.2f\n", *pagaCliente-valorAtual);
		printf("\n");
		printf("==============================\n");	
		*marcar = 1;
		}
	}

void valorPagamento(int *marcar, float *pagaCliente, float valorAtual,int quantC, int quant,
 tCliente pessoa[MAX], int bonus[MAX], tCompra compra[MAX][MAXC]){
 	/*A função "valorPagamento" é responsável por efetuar o pagamento do cliente
	 que não usou bônus. Os parâmetros "pagaCliente"(onde será digitado o valor do pagamento
	 do cliente),"quantC" (que é a posição onde se armazenará o valor do produto comprado na matriz
	 bidimensional "tCliente compra[MAX][MAXC]"), "quant"(que guarda do posição do 
	 cliente que fez a compra), "bonus[MAXC]" (onde guarda o valor do bonus que pode eventualmente
	 ser removido quando a compra não for efetivada),
	  "tCliente pessoa[MAX]"(usado para se armazenar algum dado
	 do cliente) e "tCompra compra[MAX][MAXC]"(responsável por armazenar os dados
	 de compra dos clientes) são apresentadas na função. As variáveis, "escolha" e
	 "pagaCliente1" são usadas para escolher fornecer mais dinheiro a compra quando o
	 mesmo é insuficiente e guardar o dinheiro a ser fornecido caso a escolha for afirmativa.*/
	int escolha;
	float pagaCliente1;
	printf("==============================\n");	
	printf("\n");
	printf("Digite o valor do pagamento do cliente: R$");
	scanf("%f", pagaCliente);
	printf("\n");
	printf("==============================\n");
	while(*pagaCliente<0){
		printf("\n");
		printf("Erro! Valor negativo. Digite novamente: R$");
		scanf("%f", pagaCliente);
		printf("\n");
		printf("==============================\n");
	}
	while(compra[quant][quantC].valorCompra>*pagaCliente){
		printf("==============================\n");
		printf("\n");
		printf("Erro: Valor do pagamento inferior ao valor da compra.\n");
		printf("\n");
		printf("Deseja fornecer mais dinheiro?[1-sim <outro valor>-nao]\n");
		printf("\n");
		scanf("%d", &escolha);
		printf("\n");
		printf("==============================\n");
		if(escolha==1){
			printf("Digite a quantia a ser fornecida: R$");
			scanf("%f", &pagaCliente1);
			printf("==============================\n");
			*pagaCliente+=pagaCliente1;
		}else if(escolha!=1){
			printf("\n");
			printf("COMPRA NAO EFETIVADA. Valor devolvido ao cliente: R$%.2f\n",
			*pagaCliente);
			pessoa[quant].bonus -= bonus[quant];
			printf("\n");
			printf("==============================\n");
			*marcar = 0;
			break;
		}
	}
	if(*pagaCliente>=compra[quant][quantC].valorCompra){
		printf("=================================\n");
		printf("\n");
		printf("COMPRA EFETIVADA!\n");
		printf("\n");
		printf("TROCO: %.2f\n", *pagaCliente-compra[quant][quantC].valorCompra);
		printf("\n");
		printf("==============================\n");	
		*marcar = 1;
		}
	}

void efetivarCompra(int quantC, int quant, tCliente pessoa[MAX], 
int bonus1[MAX], tCompra compra[MAX][MAXC], int contI[MAX], int contJ[MAX],int bonusAdd[MAX]){
	/*A função "realizaCompra" é responsável por efetivar a compra de um determinado
	cliente. Os parâmetros "bonusAdd[MAX]" (onde se armazena os bonus adquiridos na compra),
	"quantC" (onde se armazena a posição da compra efetuada),
	"quant" (onde se guarda a posição a posição dos dados do cliente que irá fazer a
	compra), "tCliente pessoa[MAX]" (onde se guarda os dados do cliente e onde os armazena),
	"bonus1[MAXC]" (onde se armazena a última quantidade de bônus concedida ao cliente),
	"tCompra[MAX][MAXC]" (onde se armazena as compras já efetuadas pelo cliente), "contI[MAX]"
	e "contJ[MAX]"(onde se armazena a posição do cliente e da última compra efetuada).
	As variáveis "CPF[15]", "i", "j", "escolha", "valorAtual", "pagaCliente", "valor" e
	"bonusAtual", são responsáveis por receber o CPF do cliente, procurar o cliente e
	o valor da compra zerada, escolher, futuramente, a opção de usar o bônus ou não,
	armazenar o valor da compra usando o bonus, o valor do pagamento do cliente, o valor
	da compra e o valor do bônus descontado, respectivamente.*/
	char CPF[15];
	int i=0, j, escolha, marcar;
	float valorAtual=0, pagaCliente=0, valor;
	int bonusAtual=0;
	for(i=0;i<quant;i++){
		printf("\n");
		printf("Digite o CPF: ");
		scanf("%s", CPF);
		printf("\n");
	/*Abaixo, a função "identificaCPF" verifica se o CPF é existente ou não.*/	
	if(identificaCPF(pessoa, CPF, quant)==0){
		break;
	}
		
	
		if(strcmp(CPF, pessoa[i].CPF)==0){
		for(j=0;j<MAX;j++){
		if(compra[i][j].valorCompra==0.00){
			compra[i][j].compraCancelada = 0;
			printf("=================================\n");
			printf("\n");
			printf("BONUS: %d\n", pessoa[i].bonus);
			printf("VALOR CORRESPONDENTE: R$%.2f\n", pessoa[i].bonus*
			pessoa[i].ultimaCompra.pontos.valor);
			printf("\n");
			printf("=================================\n");
			printf("\n");
			printf("Digite o valor da compra: R$");
			scanf("%f", &compra[i][j].valorCompra);
			printf("\n");
			while(compra[i][j].valorCompra<0){
				printf("=================================\n");
				printf("\n");
				printf("Erro! Valor negativo. Digite novamente: R$");
				scanf("%f", &compra[i][j].valorCompra);
				printf("\n");
				printf("=================================\n");
			}
			pessoa[i].ultimaCompra.pontos.ultBonus = pessoa[i].bonus;
			if(pessoa[i].bonus!=0){
			printf("=================================\n");
			printf("\n");	
			printf("Deseja utilizar seu bonus?[1 - sim <outro valor> - nao]\n");
			scanf("%d", &escolha);
			printf("\n");
			printf("=================================\n");
			if(escolha==1){
				
				if(pessoa[i].bonus*pessoa[i].ultimaCompra.pontos.valor>=
				compra[i][j].valorCompra){
					bonus1[i] = pessoa[i].bonus;
					
				valorAtual = 0.00;

				bonusAtual = pessoa[i].bonus-(compra[i][j].valorCompra/pessoa[i].ultimaCompra.pontos.valor);
				printf("\n");	
				printf("BONUS ATUAL: %d\n", pessoa[i].bonus=bonusAtual);
				printf("VALOR DE COMPRA ATUALIZADO: R$%.2f\n", compra[i][j].compra
				=valorAtual);
				printf("\n");
				printf("=================================\n");
					valorPagamentoBonus(&marcar, &pagaCliente, valorAtual, j, i, pessoa, compra);
					if(marcar==1){
					pessoa[i].totalCompra+=compra[i][j].compra;	
					}
					else if(marcar==0){
						pessoa[i].bonus = bonus1[i];
						break;
					}
				
				if(compra[i][j].compra>=
				pessoa[i].ultimaCompra.pontos.valorBonificar){
				
				if(pessoa[i].bonus<pessoa[i].ultimaCompra.pontos.teto){	
					
				pessoa[i].bonus += compra[i][j].compra/
				pessoa[i].ultimaCompra.pontos.valorBonificar;
				bonusAdd[i] = compra[i][j].compra/
				pessoa[i].ultimaCompra.pontos.valorBonificar;
				pessoa[i].ultimaCompra.pontos.marcaBonus = 0;
				
				}
				
				if(pessoa[i].bonus>=pessoa[i].ultimaCompra.pontos.teto){
					if(pessoa[i].ultimaCompra.pontos.marcaBonus!=1){
					pessoa[i].bonus = pessoa[i].ultimaCompra.pontos.teto;
					
					pessoa[i].ultimaCompra.pontos.marcaBonus = 1;
					}
				}
				}
				printf("=================================\n");
				printf("\n");
				printf("COMPRA EFETIVADA\n");
				printf("\n");
				printf("=================================\n");
				}
				else if(pessoa[i].bonus*pessoa[i].ultimaCompra.pontos.valor<
				compra[i][j].valorCompra){
					
					bonus1[i] = pessoa[i].bonus;
					valorAtual = compra[i][j].valorCompra-
					(pessoa[i].bonus*pessoa[i].ultimaCompra.pontos.valor);
					printf("\n");
					printf("BONUS ATUAL: %d\n", pessoa[i].bonus=0.00);
					printf("VALOR DE COMPRA ATUALIZADO: R$%.2f\n", compra[i][j].compra
					=valorAtual);
					printf("\n");
					printf("=================================\n");
					bonusAdd[i] = pessoa[i].bonus;
					/*Abaixo, a função "valorPagamentoBonus" realiza a compra com 
				      o bônus utilizado*/
					valorPagamentoBonus(&marcar, &pagaCliente, valorAtual, j, i, pessoa, compra);
					if(marcar==1){
					pessoa[i].totalCompra+=compra[i][j].compra;	
					}
					else if(marcar==0){
						pessoa[i].bonus = bonus1[i];
						break;
					}
					
					if(compra[i][j].compra>=
				pessoa[i].ultimaCompra.pontos.valorBonificar){
				
				if(pessoa[i].bonus<pessoa[i].ultimaCompra.pontos.teto){	
					
				pessoa[i].bonus += compra[i][j].compra/
				pessoa[i].ultimaCompra.pontos.valorBonificar;
				bonusAdd[i] = compra[i][j].compra/
				pessoa[i].ultimaCompra.pontos.valorBonificar;
				pessoa[i].ultimaCompra.pontos.marcaBonus = 0;
				}
				
				if(pessoa[i].bonus>=pessoa[i].ultimaCompra.pontos.teto){
					if(pessoa[i].ultimaCompra.pontos.marcaBonus!=1){
					pessoa[i].bonus = pessoa[i].ultimaCompra.pontos.teto;
					
					pessoa[i].ultimaCompra.pontos.marcaBonus = 1;
					}
				}
				}
			}
			}
			if(escolha!=1){
				
				/*Abaixo, a função "valorPagamento" realiza a compra sem 
    			o bônus utilizado*/
    			compra[i][j].compra = compra[i][j].valorCompra;
				valorPagamento(&marcar, &pagaCliente, valorAtual, j, i, pessoa, bonus1, compra);
				if(marcar==1){
				pessoa[i].totalCompra+=compra[i][j].compra;
				}else if(marcar==0){
					pessoa[i].bonus = bonus1[i];
					break;
				}
				if(compra[i][j].valorCompra>=
				pessoa[i].ultimaCompra.pontos.valorBonificar){
				
				if(pessoa[i].bonus<pessoa[i].ultimaCompra.pontos.teto){	
					
				pessoa[i].bonus += compra[i][j].valorCompra/
				pessoa[i].ultimaCompra.pontos.valorBonificar;
				bonusAdd[i] = compra[i][j].compra/
				pessoa[i].ultimaCompra.pontos.valorBonificar;
				pessoa[i].ultimaCompra.pontos.marcaBonus = 0;
				}
				
				if(pessoa[i].bonus>=pessoa[i].ultimaCompra.pontos.teto){
					if(pessoa[i].ultimaCompra.pontos.marcaBonus!=1){
					pessoa[i].bonus = pessoa[i].ultimaCompra.pontos.teto;
					
					pessoa[i].ultimaCompra.pontos.marcaBonus = 1;
					}
					
				}
			}
			bonus1[i] = 0;
			}
			}
			else if(pessoa[i].bonus == 0){
				compra[i][j].compra = compra[i][j].valorCompra;
				valor = compra[i][j].valorCompra;
				/*Abaixo, a função "valorPagamento" realiza a compra sem 
				 o bônus utilizado*/
				valorPagamento(&marcar, &pagaCliente, valor, j, i, pessoa, bonus1, compra);
				if(marcar==1){
				pessoa[i].totalCompra+=compra[i][j].compra;
				}else if (marcar==0){
					pessoa[i].bonus = bonus1[i];
				}
				if(compra[i][j].valorCompra>=
				pessoa[i].ultimaCompra.pontos.valorBonificar){
				
				if(pessoa[i].bonus<pessoa[i].ultimaCompra.pontos.teto){	
				pessoa[i].bonus += compra[i][j].valorCompra/
				pessoa[i].ultimaCompra.pontos.valorBonificar;
				bonusAdd[i] = compra[i][j].compra/
				pessoa[i].ultimaCompra.pontos.valorBonificar;
				pessoa[i].ultimaCompra.pontos.marcaBonus = 0;
				}
				if(pessoa[i].bonus>=pessoa[i].ultimaCompra.pontos.teto){
					if(pessoa[i].ultimaCompra.pontos.marcaBonus!=1){
					pessoa[i].bonus = pessoa[i].ultimaCompra.pontos.teto;
					
					pessoa[i].ultimaCompra.pontos.marcaBonus = 1;
					}
				}
			}
			bonus1[i] = 0;
		}
	contJ[i] = j;
	contI[i] = i;
	break;
	}else{
		continue;
		}
	}
		}
		if(marcar==0){
			break;
		}	
	}
	}

void cancelarCompra(int quantC, int quant, tCliente pessoa[MAX],
 int bonus[MAX], tCompra compra[MAX][MAXC], int contI[MAX], int contJ[MAX], int bonusAdd[MAX]){
/*A função "cancelaCompra" é responsável por cancelar a compra de um determinado
cliente. Os parâmetros "bonusAdd[MAX]" (onde se armazena os bônus adquiridos pelo cliente),
"quantC" (onde se armazena a posição da compra efetuada),
"quant" (onde se guarda a posição a posição dos dados do cliente que irá fazer a
compra), "tCliente pessoa[MAX]" (onde se guarda os dados do cliente e onde os armazena),
"bonus[MAXC]" (onde se armazena a última quantidade de bônus concedida ao cliente),
"tCompra compra[MAX][MAXC]" (onde se armazena as compras já efetuadas pelo cliente), "contI[MAX]"
e "contJ[MAX]"(onde se armazena a posição do cliente e da última compra efetuada).
As variáveis "i", "j", "escolha", "CPF[15]", "valorCompra" 
são responsáveis por procurar o cliente e o valor da compra zerada, escolher, 
futuramente, a opção de cancelar a compra ou não, receber o CPF do cliente e 
o valor da compra a ser usada para procurar outra compra que não seja a última
para efetuar o cancelamento, respectivamente.*/
	int i, j, escolha, bonusR, X;
	char CPF[15];
	float valorCompra;
	
	for(i=0;i<=quant;i++){
		printf("\n");
		printf("Digite o CPF: ");
		scanf("%s", CPF);
		printf("\n");
	if(identificaCPF(pessoa, CPF, quant)==0){
		break;
	}
	
		if(strcmp(CPF, pessoa[i].CPF)==0){
			printf("=================================\n");
			do{
			printf("\n");	
			printf("Qual compra deseja cancelar[1-Ultima compra 2-outra compra]?\n");
			scanf("%d", &escolha);
			printf("\n");
			printf("=================================\n");
			}while(escolha!=1&&escolha!=2);
			if(escolha==1){
				if(compra[contI[i]][contJ[i]].compraCancelada==1){
					printf("\n");
					printf("ERRO: Ultima compra ja cancelada\n");
					break;
					printf("\n");
				printf("=================================\n");
				}
			
				if(compra[contI[i]][contJ[i]].compraCancelada!=1){
					printf("\n");
					printf("Valor da compra: R$%.2f\n", compra[contI[i]][contJ[i]].valorCompra);
					printf("Valor pago: R$%.2f\n", compra[contI[i]][contJ[i]].compra);
					printf("Bonus usados: %d\n", bonus[i]);	
					printf("Bonus ganhos: %d\n", bonusAdd[i]);
					printf("\n");
					printf("Tem certeza que deseja cancelar essa compra [1-sim outro valor>-nao]?\n");
					printf("\n");
					scanf("%d", &escolha);
					printf("=================================\n");
					if(escolha==1){
						pessoa[i].bonus = pessoa[i].ultimaCompra.pontos.ultBonus;
						pessoa[i].totalCompra-=compra[contI[i]][contJ[i]].compra;
						compra[contI[i]][contJ[i]].compraCancelada = 1;
						compra[contI[i]][contJ[i]].compra = 0.00;
						printf("\n");
						printf("COMPRA CANCELADA\n");
						printf("\n");
						printf("=================================\n");
						break;	
					}
					if(escolha!=1){
						printf("\n");
						printf("COMPRA NAO CANCELADA\n");
						printf("\n");
						printf("=================================\n");
						break;
					}
				}
			}
			else if(escolha==2){
				printf("=================================\n");
				printf("\n");
				printf("Digite o valor pago da compra a ser cancelada: R$");
				scanf("%f", &valorCompra);
				printf("\n");
				printf("=================================\n");
				for(j=0;j<quantC;j++){
					if(valorCompra == compra[i][j].compra){
					if(compra[i][j].compraCancelada==1){
					printf("\n");	
					printf("ERRO: Compra ja cancelada\n");
					printf("\n");
					break;
					printf("=================================\n");
					}
					else if(compra[i][j].compraCancelada!=1){
					printf("Valor da compra: R$%.2f\n", compra[i][j].valorCompra);
					printf("Bonus a ser retirado do cliente: %d\n", bonusAdd[i]);
					printf("\n");
					printf("=================================\n");
						printf("\n");
						printf("Vendedor, deseja informar um valor menor de bonus?[1- sim <outro valor> - nao]\n");
						printf("\n");
						scanf("%d", &escolha);
						printf("=================================\n");
						if(escolha==1){
							do{
                            printf("\n");
							printf("Digite o valor a ser retirado do cliente(menor ou igual a %d)\n",
							 bonusAdd[i]);
							 printf("\n");
							 scanf("%d", &bonusR);
							 printf("=================================\n");
							}while(bonusR>bonusAdd[i]);
							printf("\n");
							printf("Tem certeza que deseja cancelar essa compra [1-sim outro valor>-nao]?\n");
							printf("\n");
					        scanf("%d", &escolha);
					        printf("=================================\n");
						if(escolha==1){
						pessoa[i].bonus -= bonusR;
						pessoa[i].totalCompra-=compra[i][j].compra;
						compra[i][j].compraCancelada = 1;
						X = 1;
						printf("\n");
						printf("COMPRA CANCELADA\n");
						printf("\n");
						printf("=================================\n");
						break;	
					}
					else if(escolha!=1){
						printf("\n");
						printf("COMPRA NAO CANCELADA\n");
						printf("\n");
						printf("=================================\n");
						break;
					}
						}else if(escolha!=1){
						printf("\n");
						printf("Tem certeza que deseja cancelar essa compra [1-sim outro valor>-nao]?\n");
						printf("\n");
	   	   	   	   	    scanf("%d", &escolha);
	   	   	   	   	    printf("=================================\n");
						if(escolha==1){
						pessoa[i].bonus = pessoa[i].ultimaCompra.pontos.ultBonus;
						pessoa[i].totalCompra-=compra[i][j].compra;
						compra[i][j].compraCancelada = 1;
						X = 1;
						printf("\n");
						printf("COMPRA CANCELADA\n");
						printf("\n");
						printf("=================================\n");
						break;	
					}
					else if(escolha!=1){
						X = 1;
						printf("\n");
						printf("COMPRA NAO CANCELADA\n");
						printf("\n");
						printf("=================================\n");
						break;
					}				
						}
					}
				}
				
			}
	}
}
if(X==1){
	break;
}
	}
 }

void exibirBonus(int quant, tCliente pessoa[MAX]){
	/*Essa função é responsável por exibir o total de bônus de um cliente e seu
	valor correspondente. Os parâmetros "quant" (onde se guarda o total de clientes
	já cadastrados) e "tCliente pessoa[MAX]" (onde se armazena os dados do cliente).
	As variáveis "CPF[15]" e "i", são responsáveis por ler o CPF do cliente e procurá-lo
	em um comando de repetição, respectivamente.*/
	char CPF[15];
	int i;
	for(i=0;i<quant;i++){
	printf("\n");
	printf("Digite o CPF: ");
	scanf("%s", CPF);
	printf("\n");
	if(identificaCPF(pessoa, CPF, quant)==0){
		break;
	}
	printf("=================================\n");
	
	if(strcmp(CPF, pessoa[i].CPF)!=0){
		printf("\n");
		printf("Erro: CPF nao cadastrado\n");
		printf("\n");
		break;
	}
	else if(strcmp(CPF, pessoa[i].CPF)==0){
		printf("\n");
		printf("BONUS: %d\n", pessoa[i].bonus);
		printf("VALOR CORRESPONDENTE: %.2f\n", pessoa[i].bonus*
		pessoa[i].ultimaCompra.pontos.valor);
		printf("\n");
		printf("=================================\n");
	}
	}
}
 
void configTeto(int quant, tCliente pessoa[MAX]){
	/*Essa função é responsável por alterar o teto de bônus ofertados. 
	Os parâmetros "quant" (onde se guarda o total de clientes
	já cadastrados) e "tCliente pessoa[MAX]" (onde se armazena os dados do cliente).
	A variável "i", é responsável por alterar o teto para todos os clientes em cadeia.*/
	int i;
	
	printf("==============================\n");
	printf("\n");
	printf("Digite o novo teto: ");
	scanf("%d", &pessoa[quant].ultimaCompra.pontos.teto);
	printf("\n");
	while(pessoa[quant].ultimaCompra.pontos.teto<0){
	printf("==============================\n");	
	printf("\n");
	printf("Erro: valor negativo. Digite novamente: ");
	scanf("%d", &pessoa[quant].ultimaCompra.pontos.teto);
	printf("\n");
	printf("==============================\n");
	}
	
	for(i=0;i<quant;i++){
		pessoa[i].ultimaCompra.pontos.teto=pessoa[quant].ultimaCompra.pontos.teto;
	}
}

void configBonus (int quant, tCliente pessoa[MAX]){
	/*Essa função é responsável por alterar o valor de 1 bônus ofertado. 
	Os parâmetros "quant" (onde se guarda o total de clientes
	já cadastrados) e "tCliente pessoa[MAX]" (onde se armazena os dados do cliente).
	A variável "i", é responsável por alterar o valor de 1 bônus para todos os clientes 
	em cadeia.*/
	int i;
	printf("==============================\n");
	printf("\n");
	printf("Digite o valor de 1 bonus: ");
	scanf("%f", &pessoa[quant].ultimaCompra.pontos.valor);
	printf("\n");
	while(pessoa[quant].ultimaCompra.pontos.valor<0){
	printf("==============================\n");	
	printf("\n");
	printf("Erro: valor negativo. Digite novamente: ");
	scanf("%f", &pessoa[quant].ultimaCompra.pontos.valor);
	printf("\n");
	printf("==============================\n");
	}
	
	for(i=0;i<quant;i++){
		pessoa[i].ultimaCompra.pontos.valor=pessoa[quant].ultimaCompra.pontos.valor;
	}
}

void configBonificar(int quant, tCliente pessoa[MAX]){
	/*Essa função é responsável por alterar o limite de compra para dar o bônus ao cliente . 
	Os parâmetros "quant" (onde se guarda o total de clientes
	já cadastrados) e "tCliente pessoa[MAX]" (onde se armazena os dados do cliente).
	A variável "i", é responsável por alterar o limite de compra para dar o bônus
    para todos os clientes em cadeia.*/
	int i;
	printf("==============================\n");
	printf("\n");
	printf("Digite o novo valor para receber o bonus: ");
	scanf("%f", &pessoa[quant].ultimaCompra.pontos.valorBonificar);
	printf("\n");
	while(pessoa[quant].ultimaCompra.pontos.valorBonificar<0){
	printf("==============================\n");	
	printf("\n");
	printf("Erro: valor negativo. Digite novamente: ");
	scanf("%f", &pessoa[quant].ultimaCompra.pontos.valorBonificar);
	printf("\n");
	printf("==============================\n");
	}
	
	for(i=0;i<quant;i++){
		pessoa[i].ultimaCompra.pontos.valorBonificar=
		pessoa[quant].ultimaCompra.pontos.valorBonificar;
	}
}

void listarCliente(int quant, tCliente pessoa[MAX]){
	/*Essa função cria uma lista de todos os clientes e seus dados já cadastrados.
	Os parâmetros "quant" (onde se guarda o total de clientes
	já cadastrados) e "tCliente pessoa[MAX]" (onde se armazena os dados do cliente).
	A variável "i", é responsável por listar todos os dados dos clientes em cadeia.*/
	int i;
	for(i=0;i<quant;i++){
		printf("\n");
		printf("Cliente %d\n", i+1);
		printf("\n");
		printf("Nome: %s\n", pessoa[i].nome);
		printf("CPF: %s\n", pessoa[i].CPF);
		printf("Telefone: %s\n", pessoa[i].telefone);
		printf("E-mail: %s\n", pessoa[i].email);
		printf("Bonus: %d\n", pessoa[i].bonus);
		printf("Total de compras: R$%.2f\n", pessoa[i].totalCompra);
		printf("\n");
		printf("======================================\n");
		
	}
}

void listarBonus(int quant, tCliente pessoa[MAX]){
	/*Essa função cria uma lista de todos os clientes e seus dados já cadastrados.
	Os parâmetros "quant" (onde se guarda o total de clientes
	já cadastrados) e "tCliente pessoa[MAX]" (onde se armazena os dados do cliente).
	A variável "i", é responsável por listar todos os dados sobre o bônus de cada
	cliente em cadeia.*/
	int i;
	for(i=0;i<quant;i++){
		printf("\n");
		printf("Cliente %d\n", i+1);
		printf("\n");
		printf("Bonus: %d\n", pessoa[i].bonus);
		printf("Valor correspondente: %.2f\n",pessoa[i].bonus*
		pessoa[i].ultimaCompra.pontos.valor);
		printf("\n");
		printf("======================================\n");
	}
}

void listarClienteCompra(int quant, tCliente pessoa[MAX]){
	/*Essa função cria uma lista de todos os clientes por compras maiores, menores
	ou iguais ao valor-base desejado pelo cliente.
	Os parâmetros "quant" (onde se guarda o total de clientes
	já cadastrados) e "tCliente pessoa[MAX]" (onde se armazena os dados do cliente).
	As variáveis "select" e "valor", são responsáveis por escolher o tipo de filtragem
	(compras maiores, menores e iguais) e estipular um valor-base para essa filtragem.
	cliente em cadeia.*/
	int selectC;
	float valor;

	printf("\n");
	printf("Digite um valor base: ");
	scanf("%f", &valor);
	printf("\n");
	printf("======================================\n");
	printf("\n");
	printf("LISTAR CLIENTES EM: \n");
	printf("\n");
	printf("1 - Compras maiores a %.2f\n", valor);
	printf("0 - Compras iguais a %.2f\n", valor);
	printf("-1 - Compras menores a %.2f\n", valor);
	printf("\n");
	printf("Selecione a opcao desejada: ");
	scanf("%d", &selectC);
	if(selectC==1){
		compraMaior(quant, pessoa, valor);
	}
	else if(selectC==0){
		compraIgual(quant, pessoa, valor);
	}
	else if(selectC==-1){
		compraMenor(quant, pessoa, valor);
	}
}

void menu(tCliente pessoa[MAX], tCompra compra[MAX][MAXC]){
/*A função menu consiste em operar todos os menus presentes no programa desde o cadastro,
compra até alteração dos dados dos clientes ou das compras dos mesmos. As variáveis
i, j, k, l e m, farão as distribuições dos valores aos respectivos vetores. O
 selectC, selectM, selectCB, selectB e o selectR, são responsáveis por fazer a
 seleção das opções desejadas em cada menu. Os vetores bonus[MAX](responsável
 pelo armzenamento dos bonus brutos, ou seja, o valor inicial sem descontar),
 bonusAdd[MAX](responsável por armazenar um valor de bônus que foi adicionado ao cliente),
 contI[MAX](responsável a dar a posição do cliente em relação a última compra)
 e contJ[MAX](responsável a dar a posição da última compra de um determinado cliente), além 
 da variável bonusAdd[MAX] (responsável por guarda o valor de bônus adicionados após uma compra
 usando bonus)são os utilizados para a lógica de compra.*/
int i=0, j, k=0, l, m, marcar;
int selectC, selectM, selectCB, selectB, selectR, select;
int bonus[MAX], contI[MAX], contJ[MAX], bonusAdd[MAX];

for(l=0;l<MAX;l++){
	for(m=0;m<MAXC;m++){
		/*Dentro desse "for", o valor 0 é atribuido para a variável "compraCancelada"
		para que o programa, quando executado, não mostre um valor aleatório e
		cause futuros problemas a função "cancelaCompra" futuramente.*/
	compra[l][m].compraCancelada = 0;
	}
}

for(j=0;j<MAX;j++){
	/*Dentro desse "for", o valores são atribuidos as variáveis abaixo dentro do menu,
	pois não é possível atribuir valores iniciais dentro de uma estrutura.*/
	pessoa[j].ultimaCompra.pontos.teto=100;
	pessoa[j].ultimaCompra.pontos.valor=0.50;
	pessoa[j].ultimaCompra.pontos.valorBonificar=100.00;
}

for(l=0;l<MAX;l++){
	for(m=0;m<MAXC;m++){
		/*Assim como os comandos de repetição de "compraCancelada", esse "for"
		é usado para atribuir o valor 0.00 a variável presente na estrutura para que
		a mesma não apresente valores aleatórios na função "realizaCompra".*/
	compra[l][m].valorCompra = 0.00;
	}
}
	for( ; ; ){
		/*Esse "for" tem o encadeiamento de todos os menus e alguns submenus. Todos eles
		utilizam a variável select e seus semelhantes e direcionam a suas determinadas
		funções. No menu principal se localizam as funções de cadastro de clientes;
		efetivação de compras, ou até mesmo um eventual cancelamento; configuração ou
		exibição de bonus; e relatários ou listagem de clientes seguindo uma preferência
		de organização. */
		printf("MENU PRINCIPAL\n");
		printf("\n");
		printf("1 - Cliente\n");
		printf("2 - Compra\n");
		printf("3 - Bonus\n");
		printf("4 - Relatorios\n");
		printf("0 - Sair\n");
		printf("\n");
		printf("Selecione a opcao desejada: ");
		scanf("%d", &select);
  		printf("==============================\n");
  		if(select==1){
		for( ; ; ){
			/*O submenu "MENU CLIENTE" localizado abaixo desse comentário faz os
			cadastros do cliente, faz eventuais alterações dos dados do mesmo,
			consulta os dados do cliente desejado e remove os dados do comprador
			caso seja desejado.*/
		printf("MENU CLIENTE\n");
		printf("\n");
		printf("1 - Cadastrar\n");
		printf("2 - Alterar\n");
		printf("3 - Consultar\n");
		printf("4 - Remover\n");
		printf("0 - Sair\n");
		printf("\n");
		printf("Selecione a opcao desejada: ");
		scanf("%d", &selectC);
		printf("===============================\n");
			if(selectC==1){
			fCadastro(i, pessoa);
			i++;
		}
		else if(selectC==2){
			fAlterar(i, pessoa);
		}
		else if(selectC==3){
			fConsultar(i, pessoa);
		}
		else if(selectC==4){
			fRemover(&marcar, i, pessoa);
			if(marcar==1){
				i--;
			}
		}
		else if(selectC==0){
			break;
		}
		}
		  }
		else if(select==2){
			for( ; ; ){
			printf("MENU COMPRA\n");
			printf("\n");
			printf("1 - Realizar compra\n");
			printf("2 - Cancelar compra\n");
			printf("0 - Sair\n");
			printf("\n");
			printf("Selecione a opcao desejada: ");
			scanf("%d", &selectM);
			printf("==============================\n");
			if(selectM==1){
				efetivarCompra(k, i, pessoa, bonus, compra, contI, contJ, bonusAdd);
				k++;
			}
			else if(selectM==2){
				cancelarCompra(k, i, pessoa, bonus, compra, contI, contJ, bonusAdd);
			}
			else if(selectM==0){
				break;
			}
			}
			}
			else if(select==3){
				for( ; ; ){
					printf("MENU BONUS\n");
					printf("\n");
					printf("1 - Configurar\n");
					printf("2 - Exibir\n");
					printf("3 - Sair\n");
					printf("\n");
					printf("Selecione a opcao desejada: ");
					scanf("%d", &selectB);
				printf("==============================\n");
				if(selectB==1){	
				for( ; ; ){
				printf("CONFIGURAR BONUS\n");
				printf("\n");
				printf("1 - Alterar teto\n");
				printf("2 - Alterar valor de bonus\n");
				printf("3 - Alterar valor para receber bonus\n");
				printf("0 - Sair\n");
				printf("\n");
				printf("Selecione a opcao desejada: ");
				scanf("%d", &selectCB);
				printf("==============================\n");
				if(selectCB==1){
					configTeto(i, pessoa);
				}
				else if(selectCB==2){
					configBonus(i, pessoa);
				}
				else if(selectCB==3){
					configBonificar(i, pessoa);
				}
				else if(selectCB==0){
					break;
				}
			}
				}
				else if(selectB==2){
					exibirBonus(i, pessoa);
				}
				else if(selectB==0){
					break;
				}
				}
			}
			else if(select==4){
				printf("MENU RELATORIOS\n");
				printf("\n");
				printf("1 - Listar clientes\n");
				printf("2 - Listar bonus\n");
				printf("3 - listar clientes por compra\n");
				printf("\n");
				printf("Selecione a opcao desejada: ");
				scanf("%d", &selectR);
				printf("==============================\n");
				if(selectR==1){
					listarCliente(i, pessoa);
				}
				else if(selectR==2){
					listarBonus(i, pessoa);
				}
				else if(selectR==3){
					listarClienteCompra(i, pessoa);
				}
			}
			else if(select==0){
				break;
			}
		  }
}

int main(){
	/*Os vetores apresentados no main são responsáveis por guardar as informações
	do cliente e seus dados de compra.  A variável de tipo inteiro X serve como 
	uma variável de seleção para a função "menu" chamada mais abaixo. A estrutura
	tCompra é uma matriz bidimensional para que, mais tarde, consiga armazenar a
	posição de um determinado cliente e dá os seus valores de compra.*/
	tCliente pessoa[MAX];
	tCompra compra[MAX][MAXC];
	menu(pessoa, compra); 
	return 0;
}