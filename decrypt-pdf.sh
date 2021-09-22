#!/bin/sh
read -s -p "Enter password for PDF(s): " pdfpass
i=0
for var in "$@"
do
  ofname="${var}.decr" 

  # decrypt the pdf files and store them in ofname
  pdftk $var input_pw $pdfpass output $ofname
done
