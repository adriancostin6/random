#!/bin/sh

__usage="\
Creates windows bootable USB drive from ISO.
Usage: ./winusb_boot.sh DEVICE ISO_PATH
Example: ./winusb_boot.sh /dev/sdb1 ~/path/to/iso\
"

if [ "$#" -ne 2 ];then
    echo "$__usage"
    exit
fi

# fill /dev/sdx with 0
dd if=/dev/zero of=$1 bs=1M count=10 oflag=sync

printf '%s\n' \
    "Format the input device, creating a bootable windows partition" \
    "Instructions: o - Create new empty DOS partition" \
    "              n - New partition" \
    "              t - Change partition type (to W95 FAT32 (LBA)" \
    "              a - Set bootable flag"

fdisk $1

# create filesystem for /dev/sdx1
mkfs.ntfs "$11"

# create and mount iso and usb directories
mkdir ~/winiso ~/winusb
mount -o loop $2 ~/winiso
mount "$11" ~/winusb

# copy data from the iso to the usb
cd ~/winiso
cp -r * ~/winusb
sync

# unmount and remove directories
cd
umount ~/winiso
umount ~/winusb
rm -rf ~/winiso ~/winusb
