#!/bin/sh

# Script to automatically start the CUPS server and setup the printer.
# Make sure cups is installed and configured properly before running.

# Start the service if it is installed and inactive 
if systemctl is-active --quiet cups; then 
printf "CUPS service is active...\n"
else
printf "Starting CUPS...\n"
systemctl start cups
fi

# Get retur value of lpstat command to see if any printers are available.
# Redirect all output to /dev/null to hide it.
if ! lpstat -p &>/dev/null; then
printf "No printer added, configure a printer from localhost:631 in your browser and try again...\n"
exit 1
fi

printf "Printer(s) found, starting setup...\n\n"
printf "Default configuration is:\n"

lpstat -p -d

no_printers=$(lpstat -p | wc -l)

printf "\n"

if [ $no_printers -gt 0 ]; then
    echo "Setup an alternative default printer?(y/n)"
    read choice

    if [ $choice = "y" ]; then 
        echo "Enter printer name: "
        read name 
        lpoptions -d $name
    fi
fi

echo "Setup complete. To print from the command line use the lpr command"
