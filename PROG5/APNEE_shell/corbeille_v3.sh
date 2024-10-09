#!/bin/bash -ex

if [[ ! -d "$HOME/.corbeille" ]]
then
    mkdir "$HOME/.corbeille"
fi

if [[ $1 == "efface" ]]
then
    search=0
    if [[ $2 == "-r" ]]
    then
        search=1
        shift
    fi
    for fichier in "${@:2}"
    do
        if [[ $search -eq 1 ]]
        then
            # https://stackoverflow.com/questions/23356779/how-can-i-store-the-find-command-results-as-an-array-in-bash
            array=()
            while IFS=  read -r -d $'\0'; do
                array+=("$REPLY")
            done < <(find . -name "${fichier}" -print0)

            case ${#array[@]} in
                0)
                    echo pas trouvé
                    ;;
                1)
                    mv "${array[0]}" "$HOME/.corbeille/"
                    ;;
            
                *)
                    for i in "${!array[@]}"; do
                        mv "${array[$i]}" "$HOME/.corbeille/"
                    done
                    ;;
            esac
            
        else
            mv "$fichier" "$HOME/.corbeille/"
        fi
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


