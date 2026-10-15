#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "pt_PT.UTF-8");

    char linha[100];
    char extra;
    float temp;
    int valor;
    int arr_in[100];
    int i;

    i = 0;

    do{
        while (1) {
            printf("(Introduza -1 para terminar.)\nDigite um valor inteiro entre 0 e 1023: ");

            // sizeof(entrada) garante que nunca escreve mais de 100 caracteres
            // O fgets devolve NULL quando não conseguiu ler nenhum caractere e
            // dá se return 1 para interromper o programa, pois não há nada para ler

            if (fgets(linha, sizeof(linha), stdin) == NULL) {
                return 1;  // fim da entrada
            }
            
            int chave = sscanf(linha, "%d %c", &valor, &extra);

            // chave == EOF -> a string é inválida, não há nada para ler
            // chave == 0 -> leu algum caractere primeiro que um número
            // chave == 1 -> só leu um número (espaços finais são ignorados)
            // chave == 2 -> havia mais algum caractere inválido depois do número

            if (valor == -1) {
                goto Resume_Here;
            }

            if (chave == 1 && valor >= 0 && valor <= 1023) {
                break;
            }

            printf("Valor inválido.\n");
        }

        arr_in[i] = valor;

        i++;

    }while(1);

    Resume_Here:

    float arr_out[100];
    int j;

    printf("%-10s | %-15s\n", "Entradas:", "Saídas:");
    for (j = 0; j < i; j++) {

        arr_out[j] = 260.0*arr_in[j]/1023.0 - 20.0;

        if ( arr_out[j] < -10 || arr_out[j] > 190 ) {
            printf("%-10d | %-15s\n", arr_in[j], "Fora da Gama", arr_out[j]);
        } else {
            printf("%-10d | %-15.2f (°C)\n", arr_in[j], arr_out[j]);
        }
    }
}
