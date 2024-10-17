#!/bin/bash -e

declare -A table_mauvais
declare -A different_bug

dir="bons/programs"
lines=$(ls -l $dir | wc -l)
echo $lines
lines=$(expr $lines - 1)

for program in $dir/*
do
    echo $program
    if [ -e $program ]
    then
        echo existe
        for bon in tests_bon/*
        do
            if [ -e $program ]
            then
                output=$(./$program <$bon)
                if [[ $output != "Bon parenthesage" ]]
                then
                    table_mauvais[$program]=$program
                    different_bug[$bon]=$bon
                    # echo "Error in $program: $bon"
                    rm $program || true
                fi
            fi
        done
    fi

    echo $program
    if [ -e $program ]
    then
        echo existe
        for mauvais in tests_mauvais/*
        do
            if [ -e $program ]
            then
                output=$(./$program <$mauvais)
                if [[ $output != "Mauvais parenthesage" ]]
                then
                    table_mauvais[$program]=$program
                    different_bug[$mauvais]=$mauvais
                    # echo "Error in $program: $mauvais"
                    rm $program || true
                fi
            fi
        done
    fi

    
done


# echo ""
# echo ""
# echo Clés : ${!table_mauvais[*]}
# echo ""
echo Nb de program mauvais: ${#table_mauvais[@]}
echo Nb de program bon: $(expr $lines - ${#table_mauvais[@]})
echo Nb de bug differents: ${#different_bug[@]}