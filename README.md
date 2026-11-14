# Projeto de Jogo Isométrico em C++ com Raylib

Este projeto é um protótipo de jogo isométrico desenvolvido em C++ utilizando a biblioteca [Raylib](https://www.raylib.com/). O objetivo é criar uma base sólida para jogos com visão isométrica, com foco em arquitetura de código bem estruturada, modularidade, e paradigmas modernos de desenvolvimento de jogos.

## Funcionalidades

- Renderização de mapa com tiles isométricos
- Player com sistema de estados (`Idle`, `Running`)
- Lógica de movimento em grade isométrica
- Câmera que segue o jogador corretamente com ajuste de offset
- Separação em módulos: núcleo do jogo, renderização, entidades, utilitários, mundo
- Estrutura de build automatizada com `CMake` e `buildAndRun.sh`

## Estrutura do Projeto

```

.
├── assets/                # Recursos gráficos (tiles, imagens, etc.)
├── buildAndRun.sh         # Script para compilar e executar o projeto
├── CMakeLists.txt         # Configuração do CMake
├── include/               # Headers (.h)
│   ├── core/              # Núcleo do jogo (Game, Câmera)
│   ├── entities/          # Entidades do jogo (Player, Estados)
│   ├── renderer/          # Lógica de renderização
│   ├── utils/             # Utilitários gerais (isometria, etc.)
│   └── world/             # Elementos do mundo (Map)
├── src/                   # Implementações (.cpp)
│   ├── core/
│   ├── entities/
│   ├── renderer/
│   ├── world/
│   └── main.cpp           # Ponto de entrada do jogo
├── external/
|   └──glm/                # Header-only biblioteca para calculo de matriz
├── README.md              # Este arquivo

````

## Requisitos

- C++17 ou superior
- [Raylib](https://github.com/raysan5/raylib) instalada
- `cmake` para geração do build
- Sistema compatível (testado em Linux)

## Compilação e Execução

Para compilar e rodar o jogo:

```bash
./buildAndRun.sh
````

Esse script configura o `build/`, compila o projeto com `CMake`, e executa o binário gerado.

> Dica: você pode ativar/desativar o menu inicial modificando a macro `SKIP_MENU` no código.

## Paradigmas e Arquitetura

O projeto utiliza:

* **Programação Orientada a Objetos**: com classes para entidades e controle de estados.
* **Finite State Machine (FSM)**: para controlar o comportamento do jogador.
* **Modularidade**: com separação lógica em pastas.
* **Sistema de Câmera desacoplado**: a lógica da câmera está isolada do restante do jogo.

## Possibilidades de Expansão

* Sistema de colisão
* Inventário ou sistema de blocos tipo Minecraft
* IA simples para inimigos
* Interação com o mundo (blocos dinâmicos, destruição, construção)
* Som e música com `raylib` ou `miniaudio`
