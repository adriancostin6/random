#!/bin/sh

# Script to merge PDF files
# Takes a list of PDF files as input, decodes them if they are encrypted
# then merges them together. 

file_encryption=$false

if [ "$#" -lt 1 ]; then
    echo "Script that merges PDF files"
    echo "Usage: ./merge-pdf.sh <options> <file_names>"
    echo "OPTIONS: -e (encrypted files) -h (print help)"
    echo "Example: ./merge-pdf.sh -e pdf1.pdf pdf2.pdf pdf3.pdf"
    exit
fi

while :; do
    case $1 in
        -h|-\?|--help)
            echo "Script that merges PDF files"
            echo "Usage: ./merge-pdf.sh <options> <file_names>"
            echo "OPTIONS: -e (encrypted files)"
            echo "Example: ./merge-pdf.sh -e pdf1.pdf pdf2.pdf pdf3.pdf"
            exit
            ;;
        -e|--encrypted)
            file_encryption=$true
            shift
            ;;
        *)      # No more options
            break;
    esac
done

if $file_encryption; then
    pdf_order=""
    read -s -p "Enter password for PDF(s): " pdfpass
    i=0
    for var in "$@"
    do
        ofname="${var}.decr" 

        # decrypt the pdf files and store them in ofname
        pdftk $var input_pw $pdfpass output $ofname

        # update pdf order
        if [ $i -eq 0 ]; then
            pdf_order="$ofname"
        else
            pdf_order="$pdf_order $ofname"
        fi

        i=$((i+1))
    done

    echo "Used PDF files: $pdf_order"
    pdfunite $pdf_order output.pdf
    echo "Merged PDF saved as output.pdf"
    rm *.decr
    exit
fi

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

