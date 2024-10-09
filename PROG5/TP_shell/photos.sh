#!/bin/bash

i=1
for photo in $1/DSC*.JPG
do
    while [ -e $2/DSC$i.JPG ]
    do 
        let "i=i+1"
    done
    mv $photo $2/DSC$i.JPG
    let "i=i+1"
done