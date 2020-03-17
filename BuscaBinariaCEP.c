#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int busca_binaria (FILE *f, long inicio, long fim, char proc_cep[]){

    int contador = 0;
    Endereco e;
    long meio;

    while(inicio <= fim){

        meio = (inicio + fim)/2;
        fseek(f, meio * sizeof(Endereco), SEEK_SET);
        fread(&e,sizeof(Endereco),1,f);
        int result = strncmp(proc_cep,e.cep,8);

        if (result > 0){
            inicio = meio + 1;
        }

        else if (result < 0){
            fim = meio - 1;
        }
        else{
            printf("\n\nPosicao do CEP procurado: %ld\n", ftell(f)/sizeof(Endereco));
            printf("\n\nRegistros percorridos: %d\n", contador);
            printf("\nEndereço encontrado:\n\n%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
            return 1;
        }

        contador++;
    }

    return 0;

}


int main()
{
	FILE *f;
	Endereco e;
	long posicao, primeiro, ultimo, meio;
	char cepbusca [8];
	int resultado;

    printf("----BUSCA BINÁRIA/CEP ----");
	printf("\n\n  Digite o CEP a procurar: ");
	scanf("%s", cepbusca);

	f = fopen("cep_ordenado_novo.dat","r");

	if (f == NULL){
        printf("Arquivo com os CEPs não encontrado.");
        exit(0);
	}

	fseek(f,0,SEEK_END);
	posicao = ftell(f);
    rewind(f);

	printf("\nTamanho do Arquivo CEP: %ld\n", posicao);
	printf("Tamanho de cada Registro: %ld\n", sizeof(Endereco));
	printf("Total de Registros: %ld\n", posicao/sizeof(Endereco));

	primeiro = 0;
	ultimo = (posicao/sizeof(Endereco))-1;

    resultado = busca_binaria(f,primeiro,ultimo,cepbusca);

    if (resultado == 0){
        printf("\nCEP não encontrado!\n\n");
    }
	fclose(f);
	return 0;
}

