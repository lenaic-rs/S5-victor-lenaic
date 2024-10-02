#!/bin/bash -e

declare -A table_mauvais
declare -A different_bug

dir="bons/programs"

for program in $dir/*
do
    for bon in tests_bon/*
    do
        output=$(./$program <$bon)
        if [[ $output != "Bon parenthesage" ]]
        then
            table_mauvais[$program]=$program
            different_bug[$bon]=$bon
            # echo "Error in $program: $bon"
            rm bons/$program || true
        fi
    done

    for mauvais in tests_mauvais/*
    do
        output=$(./$program <$mauvais)
        if [[ $output != "Mauvais parenthesage" ]]
        then
            table_mauvais[$program]=$program
            different_bug[$mauvais]=$mauvais
            # echo "Error in $program: $mauvais"
            rm bons/$program || true
        fi
    done

    
done


# echo ""
# echo ""
# echo Clés : ${!table_mauvais[*]}
# echo ""
lines=$(ls -l $dir | wc -l)
lines=$(expr $lines - 1)
echo Nb de program mauvais: ${#table_mauvais[@]}
echo Nb de program bon: $(expr $lines - ${#table_mauvais[@]})
echo Nb de bug differents: ${#different_bug[@]}