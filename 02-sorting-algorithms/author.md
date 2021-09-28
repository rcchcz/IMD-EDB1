# Identificação Pessoal

- Nome: *Rita de Cássia Chagas da Cruz*
- Email: *rcchcz@gmail.com*
- Turma: *DIM0119 - T01*

- Nome: *Victor Vieira Targino*
- Email: *victorvieira.rn@gmail.com*
- Turma: *DIM0119 - T01*

# Indique quais algoritmos foram implementados nos experimentos

- [x] Insertion sort
- [x] Selection sort
- [x] Bubble sort
- [x] Shell sort
- [x] Quick sort
- [x] Merge sort
- [x] Radix sort

# Indique quais dos cenários de dados abaixo você conseguiu simular nos experimentos

- [x] todos randômicos
- [x] parcialmente ordenado (75%)
- [x] parcialmente ordenado (50%)
- [x] parcialmente ordenado (25%)
- [x] dados em ordem não-decrescente
- [x] dados em ordem não-crescente

# Escreva a quantidade de amostras coletadas por experimento
- O vetor mínimo foi _10^2_ vetor máximo foi de _10^5_;
- _25_ Amostras foram utilizadas;
- Utilizamos _5_ amostras por experimento;
- Média cumulativa calculada.

# Indique quais das perguntas abaixo foram respondidas no relatório

- [X] O que você descobriu de maneira geral.
- [X] Quais algoritmos são recomendados para quais cenários?
- [X] Como o algoritmo de decomposição de chave (radix) se compara com o melhor algoritmo baseado em _comparação_ de chaves?
- [X] É verdade que o _quick sort_, na prática, é mesmo mais rápido do que o _merge sort_?
- [X] Aconteceu algo inesperado nas medições? (por exemplo, picos ou vales nos gráficos) Se sim, por que?
- [X] Com base nos resultados empíricos, faça uma estimativa para os 7 algoritmos estudados de quanto tempo seria necessário para rodar uma amostra de $10^{12}$ elementos.
- [x] A análise empírica é compatível com a análise de complexidade matemática? Ou seja, você consegui ajustar uma curva compatível com a complexidade aos dados?

# Como executar os testes
~~~bash
g++ -std=c++14 -Wall main.cpp sorting.h -o a
./a
~~~

# Limitações/Problemas

- Radix funciona exlusivamente com números inteiros positivos;
- Como foi discutido no relatório, alguns algoritmos apresentam comportamentos anômalos, demorando muito para executar a partir de certo tamanho.
--------
&copy; DIMAp/UFRN 2021.
