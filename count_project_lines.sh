#!/bin/bash

# check for input arguments
if [ $# -eq 0 ]
    then
        echo "Error: Enter file type (extension)."
        exit 1
fi

# init file type from supplied arguments
filetype=$1

total_lines=0

# sum up all lines from files with given filetype inside working directory
for file in `ls "./"*.$filetype`
do
    lines=`wc -l $file | grep -Eo '[[:digit:]]+'`
    total_lines=$(($total_lines+$lines))
done

echo "Total number of lines in project is $total_lines"
