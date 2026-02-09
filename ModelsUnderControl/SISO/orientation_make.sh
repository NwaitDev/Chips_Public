#!/bin/bash

# A changer en fonction de l'installation de BIP
BIP_PATH="/home/julien/bip/compiler/distribution"

echo "=== Nettoyage des fichiers de build précédents ==="
rm -rf ./output/*
mkdir -p ./output/build/

echo "=== Configuration de l'environnement ==="
cd $BIP_PATH
source "./setenv.sh"
cd -

echo "=== Compilation du modèle ==="
$BIP_PATH/build/bipc-latest/bin/bipc.sh \
  -p OrientationBIP -d "System()" \
  -I OrientationController/bip \
  --gencpp-cc-I . \
  --gencpp-cc-I controllers \
  --gencpp-cc-I utils \
  --genbip-follow-used-packages \
  --gencpp-follow-used-packages \
  --gencpp-output output

if [ $? -ne 0 ]; then
    echo "Erreur lors de la compilation du modèle"
    exit 1
fi

echo "=== Compilation C++ ==="
cd ./output/build
cmake .. -Wno-dev

if [ $? -ne 0 ]; then
    echo "Erreur lors de la configuration CMake"
    exit 1
fi

make

if [ $? -ne 0 ]; then
    echo "Erreur lors de la compilation C++"
    exit 1
fi

cd ../../

echo "=== Exécution du système ==="
./output/build/system

echo ""
echo "Terminé !"