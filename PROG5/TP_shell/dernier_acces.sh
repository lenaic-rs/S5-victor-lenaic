#!/bin/bash

for program in $*
do
    echo $program : $(ls -l $program -d |tr -s ' ' |cut -f 6-8 -d ' ')
done