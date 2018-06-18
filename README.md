# Snaze

## Desenvolvedores:

- Henrique David de Medeiros	(henriquemed101@gmail.com)
- Pablo Emanuell L. Targino	(pabloemanuell@academico.ufrn.br)

## Instruções de Compilação:

Na pasta src, da pasta snaze, execute o seguinte código:

```
g++ -Wall -std=c++11 snaze.cpp -o snaze
```

ou

Abra a pasta principal (snaze) no terminal e execute (é necessário ter instalado o cmake):

```
cmake -H. -Bbuild
cmake --build build -- -j3
```

## Instruções de Execução:

Na pasta do executável:

```
./snaze arqEntrada
```

ou

Caso o executável foi gerado pelo cmake, na pasta principal execute 

```
./bin/snaze arqEntrada
```

Modelos de arquivos de entradas estão na pasta data/.

### O trabalho está dividindo em dois tipo:

execução no terminal, pasta snaze; e
execução visual, pasta snaze_sfml.

### Acesso pelo GitHub:

Organização dos dados em githubs diferentes.
[Snaze](https://github.com/henriquedavidufrn/snaze) -> Jogo completo e funcional, sem erros. Branch master.
[Snaze_SFML](https://github.com/pabloufrn/snaze_sfml) -> Versão visual, pode conter alguns erros.

### [A* Algorithm (utilização na IA)](https://www.geeksforgeeks.org/a-search-algorithm/)

O algoritmo A* (ou A star) é um dos principais meios de se encontrar um determinado caminho utilizando vias.
A sua utilização garante que seja possivel encontrar um caminho mesmo com obstáculos, como no jogo é necessário
encontrar um caminho, em que possui paredes o qual pode atrapalhar o caminho, então é uma boa forma de resolver o problema.

### Criar mapas

Para criar novos mapas basta tratar todas as paredes como #, e o local da cobra basta coloca-la em qualquer posição utilizando >, <, v ou ^.
Note que para o mapa funcionar corretamente é recomendado que todos os mapas possuam as mesmas dimensões. Primeiramente você insere a dimensão,
e então informa o mapa, e por fim insere -. O '-' serve como indicação que aquele é o final do mapa, devendo assim ser incluido até mesmo no último mapa.
Mais opções de como devem ser os mapas basta acessar a pasta data/.