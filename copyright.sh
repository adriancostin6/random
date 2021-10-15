#!/bin/sh

if [ $# -ne 5 ];then
    printf "%s\n" \
           "Adds copyright statement to source files in current dir" \
           "Usage: ./copyright.sh YEAR NAME SURNAME MAIL LICENSE FILE" \
           "Example: ./copyright.sh 2021 John Smith johm@mail.com MIT file.cpp"
    exit 1
fi


for i in *; do
    sed -i "1s/^/\/*\n * Copyright (c) $1, $2 $3 <$4>\n * All rights reserved.\n *\n * $5 License\n*\/\n/" $i
done
