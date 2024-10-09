#!/bin/bash -e

if [[ ! -d "$HOME/.corbeille" ]]
then
    mkdir "$HOME/.corbeille"
fi

if [[ $1 == "efface" ]]
then
    for fichier in "${@:2}"
    do
        mv "$fichier" "$HOME/.corbeille/"
    done
elif [[ $1 == "restaure" ]]
then
    for fichier in "${@:2}"
    do
        base=$(dirname $fichier)
        mkdir -p $base
        mv "$HOME/.corbeille/$fichier" "$base/"
    done
elif [[ $1 == "info" ]]
then
    if [[ $# -eq 1 ]]
    then
        for fichier in $HOME/.corbeille/**
        do
            echo Statistiques de $(basename $fichier) : $(stat -c"%y" "$fichier")
        done
    else
        for fichier in "${@:2}"
        do
            echo Statistiques : $(stat -c"%y" "$HOME/.corbeille/$fichier")
        done
    fi
elif [[ $1 == "vide" ]]
then
    if [[ $# -eq 1 ]]
    then
        rm -rf "$HOME/.corbeille/"*
    else
        for fichier in "${@:2}"
        do
            rm -rf "$HOME/.corbeille/$fichier"
        done
    fi
else
    echo "Erreur d'argument"
fi
