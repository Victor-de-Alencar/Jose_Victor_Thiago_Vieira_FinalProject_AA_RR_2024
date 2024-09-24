#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <sys/time.h>

#define N 10  // Número de vértices no grafo


int count = 0;
// Matrizes de tempo para carro e bicicleta
double matriz_tempo_carro[N][N] = {
    {0.00000, 1093.73700, 1306.09800, 671.33700, 2288.42600, 2326.09100, 946.82300, 1438.05700, 1114.75700, 1561.64400},
    {1373.65800, 0.00000, 663.88200, 912.00300, 2556.24000, 1903.39200, 576.36400, 970.60000, 542.74500, 986.27900},
    {1646.22600, 657.74100, 0.00000, 1528.81400, 3127.06600, 2138.29400, 729.51900, 693.03700, 1170.98600, 660.24600},
    {824.18000, 1050.47600, 1262.83700, 0.00000, 1644.23700, 1792.98100, 900.31500, 1391.54900, 821.30900, 1515.13600},
    {2095.49400, 2587.29900, 2799.66000, 1641.72800, 0.00000, 2895.70900, 2437.13800, 2319.28000, 2227.41500, 2555.55500},
    {2136.66200, 1636.55700, 1901.65600, 1464.48000, 2767.83000, 0.00000, 1810.14600, 2256.84400, 1305.74900, 2224.05300},
    {916.71000, 661.55100, 873.91200, 799.29800, 2443.53500, 2162.89800, 0.00000, 871.00100, 771.25400, 994.58800},
    {1532.44900, 760.67200, 609.47000, 1517.33300, 2434.02900, 2241.22500, 718.03800, 0.00000, 1159.50500, 236.27500},
    {830.91300, 654.55800, 866.91900, 369.25800, 2013.49500, 1837.88000, 504.39700, 995.63100, 0.00000, 1119.21800},
    {1843.39200, 984.77100, 671.78800, 1741.43200, 2811.31200, 2465.32400, 942.13700, 377.28300, 1383.60400, 0.00000}
};

double matriz_tempo_bike[N][N] = {
    {0.00000, 1111.30600, 1167.44000, 889.13500, 4020.50800, 1652.24900, 732.29700, 1171.53200, 601.85600, 1323.93700},
    {1139.42500, 0.00000, 643.18600, 1331.27700, 4840.66200, 1301.77500, 674.00300, 996.37900, 596.04200, 1015.48300},
    {1168.57100, 699.00900, 0.00000, 1505.80400, 4665.00400, 1340.21600, 703.14900, 593.55500, 767.82500, 586.07600},
    {866.13700, 1287.77300, 1409.80100, 0.00000, 4323.61500, 1394.70300, 1113.23900, 1609.79600, 849.32800, 1704.87900},
    {3820.06300, 4684.70600, 4615.58000, 4124.20200, 0.00000, 5208.55800, 4376.86400, 4424.48600, 4246.42300, 4617.13000},
    {1591.68800, 1213.97000, 1193.67100, 1353.49900, 5374.57100, 0.00000, 1390.85500, 1546.86400, 1120.18500, 1565.96800},
    {760.12400, 604.44700, 660.58100, 1097.35700, 4478.62400, 1392.24800, 0.00000, 743.38800, 367.88500, 851.07200},
    {1220.49700, 984.41300, 669.93800, 1631.12700, 4530.17700, 1625.62000, 828.47200, 0.00000, 901.65500, 587.50600},
    {647.71600, 580.59500, 702.62300, 898.49200, 4459.73200, 1169.41000, 393.62700, 890.18400, 0.00000, 985.26700},
    {1393.58900, 1038.48300, 646.69700, 1730.82200, 4702.42500, 1679.69000, 928.16700, 584.43900, 1001.35000, 0.00000}
};

// Estrutura para armazenar o resultado
typedef struct {
    double distancia_minima;
    int caminho[N];
    int tamanho_caminho;
    char modo_transporte[N];
} Resultado;

// Função DFS modificada para imprimir todos os caminhos
void dfs(int vertice_atual, int destino, int visitados[N], double distancia_atual, int caminho_atual[N], int tamanho_caminho, char modo_transporte_atual[N], Resultado *resultado) {
    // Verifica se o destino foi atingido
    if (vertice_atual == destino) {
        // Imprime o caminho encontrado
        count = count + 1;
        // Verifica se a nova distância é menor que a mínima
        if (distancia_atual < resultado->distancia_minima) {
            resultado->distancia_minima = distancia_atual;
            resultado->tamanho_caminho = tamanho_caminho;
            for (int i = 0; i < tamanho_caminho; i++) {
                resultado->caminho[i] = caminho_atual[i];
            }
            for (int i = 0; i < tamanho_caminho - 1; i++) {
                resultado->modo_transporte[i] = modo_transporte_atual[i];
            }
        }
        return;
    }

    // Marca o vértice como visitado
    visitados[vertice_atual] = 1;

    // Explora os vizinhos
    for (int i = 0; i < N; i++) {
        if (!visitados[i]) {
            if (matriz_tempo_carro[vertice_atual][i] > 0) {
                // Cria cópias das estruturas para a recursão
                int visitados_copy[N];
                int caminho_copy[N];
                char modo_transporte_copy[N];
                for (int j = 0; j < N; j++) {
                    visitados_copy[j] = visitados[j];
                    caminho_copy[j] = caminho_atual[j];
                    modo_transporte_copy[j] = modo_transporte_atual[j];
                }
                caminho_copy[tamanho_caminho] = i;
                modo_transporte_copy[tamanho_caminho - 1] = 'C';  // Carro

                // Cria uma nova tarefa para a chamada recursiva
                #pragma omp task
                dfs(i, destino, visitados_copy, distancia_atual + matriz_tempo_carro[vertice_atual][i], caminho_copy, tamanho_caminho + 1, modo_transporte_copy, resultado);
            }

            if (matriz_tempo_bike[vertice_atual][i] > 0) {
                // Cria cópias das estruturas para a recursão
                int visitados_copy[N];
                int caminho_copy[N];
                char modo_transporte_copy[N];
                for (int j = 0; j < N; j++) {
                    visitados_copy[j] = visitados[j];
                    caminho_copy[j] = caminho_atual[j];
                    modo_transporte_copy[j] = modo_transporte_atual[j];
                }
                caminho_copy[tamanho_caminho] = i;
                modo_transporte_copy[tamanho_caminho - 1] = 'B';  // Bicicleta

                // Cria uma nova tarefa para a chamada recursiva
                #pragma omp task
                dfs(i, destino, visitados_copy, distancia_atual + matriz_tempo_bike[vertice_atual][i], caminho_copy, tamanho_caminho + 1, modo_transporte_copy, resultado);
            }
        }
    }

    // Desmarca o vértice ao voltar na recursão
    visitados[vertice_atual] = 0;
}

// Função para encontrar o melhor caminho
Resultado encontrar_melhor_caminho(int origem, int destino) {
    Resultado resultado;
    resultado.distancia_minima = DBL_MAX;
    resultado.tamanho_caminho = 0;

    int visitados[N] = {0};
    int caminho_atual[N];
    char modo_transporte_atual[N];

    caminho_atual[0] = origem;
    resultado.caminho[0] = origem;

    // Inicia a região paralela
    #pragma omp parallel
    {
        // Inicia a tarefa única
        #pragma omp single nowait
        {
            dfs(origem, destino, visitados, 0.0, caminho_atual, 1, modo_transporte_atual, &resultado);
        }
    }

    return resultado;
}

int main() {
    int origem, destino;
    printf("Digite a origem (0 a %d): \n", N - 1);
    printf("0- Torre Eiffel\n1- Museu do Louvre\n2- Catedral de Notre-Dame\n3- Arco do Triunfo\n4- Palácio de Versalhes\n5- Basílica de Sacré-Cœur\n6- Museu d'Orsay\n7- Jardim de Luxemburgo\n8- Place de la Concorde\n9- Panteão\n");
    scanf("%d", &origem);
    printf("Digite o destino (0 a %d): \n", N - 1);
    printf("0- Torre Eiffel\n1- Museu do Louvre\n2- Catedral de Notre-Dame\n3- Arco do Triunfo\n4- Palácio de Versalhes\n5- Basílica de Sacré-Cœur\n6- Museu d'Orsay\n7- Jardim de Luxemburgo\n8- Place de la Concorde\n9- Panteão\n");
    scanf("%d", &destino);

    struct timeval begin, end;
    gettimeofday(&begin, 0);

    Resultado resultado = encontrar_melhor_caminho(origem, destino);

    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6; 

    printf("\nMenor Caminho Possível: ");
    printf("%d", resultado.caminho[0]);
    for (int i = 1; i < resultado.tamanho_caminho; i++) {
        printf(" -%s- %d", resultado.modo_transporte[i - 1] == 'C' ? "carro" : "bike", resultado.caminho[i]);
    }
    printf("\nDistância Mínima: %.2f\n", resultado.distancia_minima);
    printf("\nNúmero de caminhos explorados: %.d\n", count);
    printf("\nTempo de Execução em segundos: %.3f\n", elapsed);

    return 0;
}
