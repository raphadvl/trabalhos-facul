#include <stdio.h>
//o programa gera um arquivo txt com os dados do Modelo SIR
int main() {
    FILE *saida;
    int dias = 25;
    int tempo[dias];
    float suscetiveis[dias], infectados[dias], recuperados[dias];
    float coeficiente_transmissao = 0.001; //a
    float fator_recuperacao = 0.6; //b
    int populacao = 1200;
    int infec_inic = 1;
    
    saida = fopen("SIR.txt", "w");

    suscetiveis[0] = populacao - infec_inic; //alunos suscetiveis
    infectados[0] = infec_inic; //alunos infectados
    recuperados[0] = 0; //alunos recuperados

    for (int t = 1; t <= dias; t++) {
        suscetiveis[t] = suscetiveis[t-1] - coeficiente_transmissao * suscetiveis[t-1] * infectados[t-1];

        infectados[t] = infectados[t-1] + coeficiente_transmissao * suscetiveis[t-1] * infectados[t-1] - fator_recuperacao * infectados[t-1];

        recuperados[t] = recuperados[t-1] + fator_recuperacao * infectados[t-1];

        tempo[t] = t;
    }
    //relatório
    fprintf(saida,"Parâmetros: \n");
    fprintf(saida,"\t\tPopulação: %d\n\t\tInfectados inicialmente: %d\n\t\tCoeficiente de transmissão: %.4f\n\t\tTaxa de recuperação: %.2f",populacao,infec_inic,coeficiente_transmissao,fator_recuperacao);
    fprintf(saida,"\n\n\n\t\tResultado dos 25 dias: \n\n");
    fprintf(saida,"\nDIA | SUSCETÍVEIS | INFECTADOS | RECUPERADOS\n");

    for (int i = 0; i <= dias; i++) {
        fprintf(saida,"%d\t%.2f\t\t%.2f\t\t%.2f\n", tempo[i], suscetiveis[i], infectados[i], recuperados[i]);
    }

    fclose(saida);
    return 0;
}
