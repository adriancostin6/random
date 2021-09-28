#!/bin/sh

printf "%s\n" \
       "+=================================================+" \
       "|   CONVERSION SCRIPT - CONVERTS BETWEEN BASES    |" \
       "+=================================================+"
read -p "Enter base (2, 8, 10, 16): " b
read -p "Enter number to convert: " i
printf "%s\n" \
       "+=================================================+" \
       "|                CONVERSION RESULTS               |" \
       "+=================================================+"

if [ $b -eq 2 ]; then
res=`bin2oct $i | awk 'FNR == 2 {print $2}'`
printf "Base $b: $i\n"
printf "Base 8: $res\n"
res=`bin2dec $i | awk 'FNR == 2 {print $2}'`
printf "Base 10: $res\n"
res=`bin2hex $i | awk 'FNR == 2 {print $2}'`
printf "Base 16: $res\n"

elif [ $b -eq 8 ]; then
res=`oct2bin $i | awk 'FNR == 2 {print $2}'`
printf "Base 2: $res\n"
printf "Base $b: $i\n"
res=`oct2dec $i | awk 'FNR == 2 {print $2}'`
printf "Base 10: $res\n"
res=`oct2hex $i | awk 'FNR == 2 {print $2}'`
printf "Base 16: $res\n"

elif [ $b -eq 10 ]; then
res=`dec2bin $i | awk 'FNR == 2 {print $2}'`
printf "Base 2: $res\n"
res=`dec2oct $i | awk 'FNR == 2 {print $2}'`
printf "Base 8: $res\n"
printf "Base $b: $i\n"
res=`dec2hex $i | awk 'FNR == 2 {print $2}'`
printf "Base 16: $res\n"

elif [ $b -eq 16 ]; then
res=`hex2bin $i | awk 'FNR == 2 {print $2}'`
printf "Base 2: $res\n"
res=`hex2oct $i | awk 'FNR == 2 {print $2}'`
printf "Base 8: $res\n"
res=`hex2dec $i | awk 'FNR == 2 {print $2}'`
printf "Base 10: $res\n"
printf "Base $b: $i\n"

else
printf "Invalid base, try again.\n"

fi
