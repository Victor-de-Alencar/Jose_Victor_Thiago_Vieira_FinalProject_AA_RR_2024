# Resumo da atividade

Estamos desenvolvendo um sistema de navegação para uma extensa rede de transportes urbanos, que abrange ônibus, trens e metrôs. A cidade é dividida em regiões interconectadas por diversas rotas de transporte, e o objetivo é identificar rotas alternativas entre diferentes pontos de interesse, levando em conta congestionamentos e interrupções no serviço.

A rede de transportes pode ser representada como um grafo, onde os vértices correspondem a estações ou pontos de interesse e as arestas representam as rotas, cada uma com um custo associado, como tempo de viagem, distância ou custo monetário. Dado que a rede é grande e possui múltiplas rotas alternativas, é essencial um algoritmo eficiente para explorar esses caminhos de forma paralela.

Assim, a tarefa é implementar um algoritmo que utilize a Busca em Profundidade Paralela (Parallel Depth-First Search - DFS) para percorrer o grafo de fluxo e descobrir todas as rotas alternativas entre dois pontos de interesse específicos na cidade.

# Integrantes do grupo
* José Victor Rocha de Alencar
* Thiago Vieira Camara

# Disciplina
* Análise de algoritmos

# Observação
* Os códigos escritos em python são apenas para fins de criação de gráficos e matrizes, os códigos principais, onde acontecem a aplicação do DFS nas matrizes, estão escritos em C conforme o requisitado pelo professor da disciplina.

# Recursos utilizados

* OpenMP - biblioteca para a linguagem C para realizar as atividades de paralelização de certos blocos de código do DFS.
* requests e numpy - para acessar a API do Graph Hopper e organizar as informações em matrizes.
* matplotlib - para plotar os graficos necessários para termos uma comparação visual das diferenças entre o DFS normal e o paralelizado
