#!/bin/bash -e

declare -A table_mauvais
declare -A different_bug

dir="bons/programs"


for i in $(seq 1 10)
do
    input=$(./a.out)

    for program in $dir/*
    do
        output=$(echo $input |./$program)
        if [[ $output != "Mauvais parenthesage" ]]
        then
            table_mauvais[$program]=$program
            #different_bug[$bon]=$bon
            echo "Error in $program: $bon"
            rm $program || true 
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