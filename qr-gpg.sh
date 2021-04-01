#!/bin/sh

# Turn QR codes into GPG keys is ASCII armor format.

if [[ $# -ne 3 ]]
    then 
        echo "Decodes all the QR codes for the GPG key and reproduces the key."
        echo "Usage: qr-gpg input_qr file_fmt output_file"
        echo "Input requires the base filename and extension"
        echo "Example filenames: private1.png private-1.png"
        echo "Example input_qr: private"
        echo "Example file_fmt: png"
        echo "The base name and extension ensures that the wildcard matching will work"
        echo "Example command: qr-gpg private png privatekey"
        exit 1
fi


qr=$1
fmt=$2
out=$3

for image in $qr*.$fmt; do
    zbarimg $image | sed '1s/^.*://' | sed '$d' > .$image.qrtmp
done

for temp in .*.qrtmp;do
    cat $temp >> $out.asc
done

rm .$qr*.qrtmp
