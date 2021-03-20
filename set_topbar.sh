#!/bin/sh

# Set topbar information for battery level, ip address, date and time
# using xsetroot.

BAT=`acpi | grep -Po "\d+%"`
IP=`ip route get 1.1.1.1 | grep -Po "(?<=(src ))\d+.\d+.\d+.\d+"`
DATE_TIME=`timedatectl | grep Local | awk '{print $4 " " $5}' | cut -c -16`

xsetroot -name "Battery: $BAT IP: $IP TIME: $DATE_TIME"
