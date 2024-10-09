#!/bin/bash -xe 

if [[ ! -d "$HOME/.corbeille" ]]
then
    mkdir "$HOME/.corbeille"
fi

files=("$@") # partitionne les arguments en conservant les espaces
for fichier in "${files[@]}"
do
    mv "$fichier" "$HOME/.corbeille/"
done
