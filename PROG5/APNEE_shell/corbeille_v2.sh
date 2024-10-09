#!/bin/bash -xe 

if [[ ! -d "$HOME/.corbeille" ]]
then
    mkdir "$HOME/.corbeille"
fi

if [[ $1 == "efface" ]]
then
    shift
    files=("$@") # partitionne les arguments en conservant les espaces
    for fichier in "${files[@]}"
    do
        mv "$fichier" "$HOME/.corbeille/"
    done
elif 
