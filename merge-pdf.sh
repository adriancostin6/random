#!/bin/sh

# Script to merge PDF files
# Takes a list of PDF files as input then merges them together. 

if [ "$#" -lt 1 ]; then
    echo "Script that merges PDF files"
    echo "Usage: ./merge-pdf.sh <options> <file_names>"
    echo "OPTIONS: -h (print help)"
    echo "Example: ./merge-pdf.sh pdf1.pdf pdf2.pdf pdf3.pdf"
    exit
fi

while :; do
    case $1 in
        -h|-\?|--help)
            echo "Script that merges PDF files"
            echo "Usage: ./merge-pdf.sh <options> <file_names>"
            echo "OPTIONS: -h (print help)"
            echo "Example: ./merge-pdf.sh pdf1.pdf pdf2.pdf pdf3.pdf"
            exit
            ;;
        *)      # No more options
            break;
    esac
done

pdf_order=""
i=0
for var in "$@"
do
    # update pdf order
    if [ $i -eq 0 ]; then
        pdf_order="$var"
    else
        pdf_order="$pdf_order $var"
    fi
    i=$((i+1))
done

echo "Used PDF files: $pdf_order"
pdfunite $pdf_order output.pdf
echo "Merged PDF saved as output.pdf"

