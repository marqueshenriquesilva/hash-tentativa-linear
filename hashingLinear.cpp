/* 
Esse programa foi escrito, compilado e testado em um ambiente Linux Ubuntu, mas deve funcionar tambem em ambientes Windows
Como pedido no enunciado, possui funcoes de inserir, exibir e remover valores de uma tabela usando hash
Todas as operacoes de busca e remocao sao efetuadas com o uso de uma funcao hash, aplicada via tentativa linear
Eh essencial que o tipo correto de valor seja colocado em cada prompt
As chaves de cada registro possuem capacidade de 2 (incluso) para ate 9 caracteres (o 10o eh o '/0')
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define TF 8

struct registro
{
    char status; // Status pode ser L (livre), O (ocupado) ou R (removido)
	char chave[10]; // A chave representa o nome inserido
};

void criar(struct registro p[TF])
{
	// Inicializa tabela com valores vazios
	int i;
    for (i = 0; i < TF; i++){
        p[i].status = 'L';
        strcpy(p[i].chave, "");
    }
    printf("Tabela Hash de enderecamento aberto (tentativa linear) criada com sucesso\n");
}

int Hash(char chave[]){
	// Funcao hash
	int ender = (chave[0] + chave[1]) % TF;
	return ender;
}

void inserir(struct registro p[TF]){
	int ender;
	char chave[10];

	// Usuario insere registro
	printf("Digite a chave: ");
	scanf("%s", chave);

	// Endereco hash do registro
	ender = Hash(chave);

	// Caso nao haja colisao
	if ((p[ender].status=='L') || (p[ender].status=='R'))
	{
		strcpy(p[ender].chave, chave);
		p[ender].status = 'O';
		printf("Chave inserida com sucesso\n");
	}
	// Em caso de colisao
	else 
	{
		bool fim = false;
		int novoender = ender + 1;
		// Se endereco estiver alem da capacidade da tabela, comeca a iterar do index 0
		if (novoender>=TF)
		{
			novoender = 0;
		}
        while (!fim){
			// Insere valor se houver espaco
        	if ((p[novoender].status == 'L') || (p[novoender].status=='R')) 
			{
			   strcpy(p[novoender].chave, chave);
	           p[novoender].status = 'O';
	           fim = true;
			   printf("Chave inserida com sucesso\n");
	        }
			// Check do tamanho da tabela
        	if (novoender < TF)
			{
				novoender++;
			}    
        	else 
			{
				novoender = 0;
			}
			// Se nao encontrar espaco nenhum na tabela, imprimi aviso de tabela cheia
        	if (novoender == ender) 
			{
        	    fim = true;
				printf("Tabela cheia\n"); 
		    }
		}
    }
}

void mostrar_hash(struct registro p[TF])
{
	int i = 0;
	// Imprimi valores hash
	while (i < TF)
	{
		printf("Chave[%d]: %10s    Status: %c\n", i, p[i].chave, p[i].status);
		i++;
	}
	return;
}

int busca(char chaveprocurada[10], struct registro p[TF]){
	int i = 0;
	int ender = Hash(chaveprocurada);
	// Itera pela tabela procurando chave
	while (i < TF && p[(ender+i)%TF].status != 'L' && strcmp(p[(ender+i)%TF].chave, chaveprocurada))
	{
		i++;
	}
	// Se chave foi achada, retorna index
	if (strcmp(p[(ender+i)%TF].chave, chaveprocurada) == 0)
	{
		return (int) (ender + i) % TF;
	} 
	// Senao, retorna tamanho total da tabela
	else
	{
		return TF;
	}
}

void remover(struct registro p[TF]){
	int ender;
	char chave[10];

	printf ("Digite a chave a ser removida: ");
    scanf ("%s", chave);

	ender = busca(chave, p);

	if (ender < TF)
	{
       p[ender].status = 'R';
       printf("Removeu com sucesso %s\n", chave);
	} 
	else
	{
		printf("Chave nao encontrada na tabela\n");
	}
}

int main(void)
	{
	// Inicializa tabela vazia
	registro p[TF];
    criar(p);

    int opcao=0;
	// Menu
    while (opcao != 4)
	{
		printf("\n1. Inserir Chave");
        printf("\n2. Mostrar tabela Hashing");
        printf("\n3. Remover chave");
        printf("\n4. Sair");
        printf("\nOpcao: ");
        scanf("%d", &opcao);
		printf("\n");
        switch (opcao)
		{
        case 1:
            inserir(p);
            break;
        case 2:
        	mostrar_hash(p);
            break;
        case 3:
		    remover(p);
            break;
        }
    }
	return 0;
}
