#!/bin/bash

for program in $*
do
    echo $program : $(ls -lu $program -d |cut -f -1 -d ' ')
done