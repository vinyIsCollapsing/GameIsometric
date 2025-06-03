#!/bin/bash

# Cores para destaque
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
RED="\033[1;31m"
RESET="\033[0m"

echo -e "${YELLOW}Deseja pular o menu e ir direto para o jogo? (s/n)${RESET}"
read -r SKIP_INPUT

# Define flag para o CMake
if [[ "$SKIP_INPUT" == "s" || "$SKIP_INPUT" == "S" ]]; then
    SKIP_FLAG="-DSKIP_MENU=ON"
    echo -e "${GREEN}Menu será pulado.${RESET}"
else
    SKIP_FLAG="-DSKIP_MENU=OFF"
    echo -e "${GREEN}Menu será exibido normalmente.${RESET}"
fi

# Cria o diretório build, se necessário
mkdir -p build

# Executa o CMake e compila
cmake $SKIP_FLAG -Bbuild
cmake --build build

# Checa se o executável foi gerado
if [[ -f build/game ]]; then
    echo -e "${GREEN}Removendo arquivos intermediários...${RESET}"

    # Remove todos os arquivos de build, exceto o executável
    find build -type f ! -name 'game' -delete

    echo -e "${YELLOW}Executando o jogo...${RESET}"
    ./build/game
else
    echo -e "${RED}Erro: o binário não foi encontrado.${RESET}"
fi
