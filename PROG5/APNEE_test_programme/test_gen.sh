#!/bin/bash -e

declare -A table_mauvais
declare -A different_bug

dir="bons/programs"
lines=$(ls -l $dir | wc -l)
lines=$(expr $lines - 1)
echo ieohozeifhzoeifh

for i in $(seq 1 10)
do
    input=$(./a.out)

    for program in $dir/*
    do
        echo $program
        if [ -e $program ]
        then
            output=$(echo $input |./$program)
            if [[ $output != "Mauvais parenthesage" ]]
            then
                echo $output
                table_mauvais[$program]=$program
                #different_bug[$bon]=$bon
                echo "Error in $program: $input"
                rm $program || true 
            fi
        fi
    done
done




# echo ""
# echo ""
# echo Clés : ${!table_mauvais[*]}
# echo ""
echo Nb de program mauvais: ${#table_mauvais[@]}
echo Nb de program bon: $(expr $lines - ${#table_mauvais[@]})
echo Nb de bug differents: ${#different_bug[@]}