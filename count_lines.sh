#!/bin/bash

# check for input arguments
if [ $# -eq 0 ]
    then
        echp "Count lines of specific file in specified dir and all subdirs." 
        echo "Usage: count /path/to/dir file_type"
        exit 1
fi

dir=$1
filetype=$2

total_lines=0


# count lines for all files of a specific type from the specified directory
# and all subdirectories, ignoring hidden
for d in $(find $dir -maxdepth 3 -type d -not -path '*/\.*')
do
    for file in `ls $dir/*.$filetype`
    do
    lines=`wc -l $file | grep -Eo '[[:digit:]]+'`
    total_lines=$(($total_lines+$lines))
    done

done

echo "Total number of lines in project is $total_lines"
