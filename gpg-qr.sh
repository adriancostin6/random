
#!/bin/sh

# Turn exported GPG keys in ASCII armor format to QR codes.

if  [[ $# -ne 2 ]]
    then
        echo "Encodes the GPG key into QR code(s)"
        echo "Usage: gpg-qr gpg_key output_file"
        echo "Example: gpg-qr private.asc private"
        exit 1
fi

gpg=$1
out=$2

split -C 2500 $gpg $out-

for key in $out-*; do
    qrencode -r $key -o $key.png
done

mv $out-*.png /tmp/
rm $out-* 
mv "/tmp/$out-"*".png" ./ 
