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

Abra a pasta principal (snaze) no terminal e execute:

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

Caso o executável foi gerado pelo make, na pasta principal execute 

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