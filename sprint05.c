#include <math.h>
#include <stdio.h>
#include <locale.h>

float input_check(int leituras, int arr_in[], int *i)
{

    // Verifica os valores introduzidos pelo utilizador e garante que são valores válidos.
    // Além de devolver o valor de i, também devolve o array arr_in com os valores válidos introduzidos.

char linha[100];
char extra;
float temp;
int valor;
*i = 0;

do{
        if (*i == leituras) {
                goto Resume_Here;
            }

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

        arr_in[*i] = valor;

        (*i)++;

    }while(1);

    Resume_Here:

}

float temp_conversion(int arr_in[], float arr_out[], int i)
{

    // Converte os valores introduzidos pelo utilizador em temperaturas
    // Devolve o array arr_out com os valores das temperaturas correspondentes.

    int j;

    for (j = 0; j < i; j++) {

        arr_out[j] = (((260.0*arr_in[j])/1023.0) - 20.0);

    }

}

float temp_regulator(float arr_out[], int arr_in[], int j)
{
    // Verifica se os valores das temperaturas estão dentro da gama de -10 a 190 °C.
    // Senão tiverem devolve 0, caso contrário mantém o valor inicial de result de 1.

    int result = 1;

    arr_out[j] = (((260.0*arr_in[j])/1023.0) - 20.0);

    if ( arr_out[j] < -10 || arr_out[j] > 190 ) {
            
        result = 0;

    }

    return result;

}

float maximum(float arr_out[], float max, int j)
{
    // Compara os valores das temperaturas e devolve o valor máximo.

    if (arr_out[j] > max) {
        max = arr_out[j];
    }
    
    return max;
}

float minimum(float arr_out[], float min, int j)
{
    // Compara os valores das temperaturas e devolve o valor mínimo.

    if (arr_out[j] < min) {
        min = arr_out[j];
    }

    return min;

}

float mean(float sum, int k)
{
    // Cálcula e devolve o valor da média das temperaturas válidas.

    float mean = sum / k;
    return mean;
    
}

float deviation(float arr_out[], float média, int i, int k)
{
    // Cálcula e devolve o valor do desvio padrão das temperaturas válidas.

    int j;
    float desvio = 0.0;

    for (j = 0; j < i; j++) {

        if ( arr_out[j] >= -10 && arr_out[j] <= 190 ) {
            desvio += (arr_out[j] - média) * (arr_out[j] - média);
            }
        }

        desvio = sqrt(desvio / k);
        return desvio;
}

float data_print(int i, int arr_in[], float arr_out[], float max, float min, float média, float desvio, float soma, int k)
{
    // Imprime os valores dos sensores, das temperaturas válidas e inválidas correspondentes,
    // Assim como as estatísticas finais e o número de valores válidos lidos.

    printf("\n%-10s | %-15s\n", "Entradas:", "Saídas:");

    int j;
    for (j = 0; j < i; j++) {

        if ( temp_regulator(arr_out, arr_in, j) == 0 ) {

            printf("%-10d | %-15s\n", arr_in[j], "Fora da Gama");

        } else {
            printf("%-10d | %-5.2f (°C)\n", arr_in[j], arr_out[j]);

            k++;
            soma += arr_out[j];
            
            max = maximum(arr_out, max, j);
            min = minimum(arr_out, min, j);

        }
    }

    if (k == 0) {
        printf("\nNão foram lidos valores válidos para calcular as estatísticas desejadas.\n\n");
        return 0;
    } else {

        média = mean(soma, k);

        printf("\nNúmero de Valores Lidos: %d\n"
       "Mínima: %-10.2f (°C)\n"
       "Máxima: %-10.2f (°C)\n"
       ,j, min, max);

        desvio = deviation(arr_out, média, i, k);

        printf("Média: %-11.2f (°C)\n", média);
        printf("Desvio Padrão: %-10.2f \n\n", desvio);
    }

}

int test_values(int arr_in[])
{
    arr_in[0] = 0;
    arr_in[1] = 400;
    arr_in[2] = 523;
    arr_in[3] = 600;
    arr_in[4] = 1023;

}

int main() {
    setlocale(LC_ALL, "pt_PT.UTF-8");

    // Caso queira usar valores de teste pré-definidos altere a variável teste para 1.
    // Caso contrário deixe a variável teste com o valor 0 para introduzir os valores manualmente.

    int teste = 1;

    int leituras = 5;

    if ( teste == 1 ) {
        leituras = 5;
    } 

    int arr_in[leituras];
    int i;

    if ( teste == 1 ){

        i = 5;
        test_values(arr_in);

    }else{

        input_check(leituras, arr_in, &i);

    }

    float arr_out[leituras];
    
    temp_conversion(arr_in, arr_out, i);

    float max = -1000.0;
    float min = 1000.0;
    float desvio = 0.0;
    float média = 0.0;
    float soma = 0.0;
    int k = 0;
    int j;

    data_print(i, arr_in, arr_out, max, min, média, desvio, soma, k);

}
