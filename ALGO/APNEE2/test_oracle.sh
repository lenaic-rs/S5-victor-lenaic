#!/bin/bash

# Ce script utilisera les chaines contenu dans les fichiers du repertoire supp/tests/
# Il executera tous les programmes present dans le repertoire
# "bons/programs"
# Grace a l'oracle, il verifira si le resultat est le bon, et supprimera le program si
# il est mauvais. 
# Il donne aussi des stats a la fin de son execution.

declare -A table_mauvais
declare -A different_bug

dir="bons/programs"
test_dir ="supp/tests"
lines=$(ls -l $dir | wc -l)
lines=$(expr $lines - 1)

for i in $(seq 1 1)
do

    for test_file in $test_dir/*
    do
        input=$(cat $test_file)

        for program in $dir/*
        do
            #echo $program
            if [ -e $program ]
            then
                output=$(echo $input |./$program)

                echo $output > tmp
                echo $input > tmp2

                ./oracle tmp2 tmp

                res=$?

                echo $res

                if [[ $res -ne 0 ]]
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

    
done




# echo ""
# echo ""
# echo Clés : ${!table_mauvais[*]}
# echo ""
echo Nb de program mauvais: ${#table_mauvais[@]}
echo Nb de program bon: $(expr $lines - ${#table_mauvais[@]})
echo Nb de bug differents: ${#different_bug[@]}