# Uses iptables to change the value of the Differentiated Services Code Point (DSCP) in
# outgoing IP packets to different Assured Forwarding (AF) values chosen by the user. (e.g. AF22, AF31, AF13)
# 
# On the same output interface, a DSMARK queueing discipline (qdisc) is configured with 3 classes, one for 
# best-effort traffic, one for traffic from UDP port 6000, and the last for traffic from UDP port 7000.
# 
# The second class is configured to set the first two bits in the DSCP field of the packet while leaving
# the other bits unchanged. Very much the same happens for the third class, but instead of setting the first
# two bits, this one sets the last two.
# 
# All of this is done for educational purposes in order to test out the DSMARK qdisc by analyzing the traffic
# on the receiving end, and seeing if the values have been set correctly.
# 
# Components:
#
# +-------------------+                              +--------------------+              +--------------------+
# |   Linux router    |                              | End device running |              |      Results       |
# |                   | -------------------------->  | packet analyzer    | -----------> |                    |
# | iptables + DSMARK |                              | tool,              |              |     DSCP field     |
# +-------------------+                              +--------------------+              +--------------------+
#
# Example:  AF22 is            010100 (6 bits)
#           DS field will be   01010000 (DSCP + ECN bits) (8 bits)
# Considering UDP port 6000, on the receiving end, after applying the qdisc and sending the packet we will have:
#           Received DS field: 11010000 
# Considering UDP port 7000, on the receiving end, after applying the qdisc and sending the packet we will have:
#           Received DS field: 01011100
# Considering Best-Effort (DSCP 0) traffic, on the receiving end, after applying the qdisc and sending the packet we will have:
#           Received DS field: 00000000

# clear previous qdiscs
tc qdisc del dev eth1 root &> /dev/null

# clear iptables mangle rules
iptables -t mangle -F

# create dsmark qdisc
echo "Adding DSMARK qdisk..."
tc qdisc add dev eth1 handle 1:0 root dsmark indices 8

# edit classes
# best effort traffic (DSCP 0)
echo "Changing DSCP value in first DSMARK class..."
tc class change dev eth1 classid 1:1 dsmark mask 0x0 value 0x0

# udp 6000
# set first 2 bits in dscp field, leaving others unchanged
echo "Changing DSCP value in second DSMARK class..."
tc class change dev eth1 classid 1:2 dsmark mask 0x3f value 0xc0

# udp 7000 dscp
# set last 2 bits in dscp field, leaving others unchanged
echo "Changing DSCP value in third DSMARK class..."
tc class change dev eth1 classid 1:3 dsmark mask 0xf3 value 0xc

# user input and iptables 
while true
do
    read -p "Enter DSCP value:" dscp
    echo "Setting DSCP value using iptables..."
    iptables -t mangle -A OUTPUT -p udp \
      --match multiport --dports 6000,7000 \
      -j DSCP --set-dscp $dscp

    read -p "Enter another DSCP value?(y/n) " choice
    if [ "$choice" = "n" ] ;
    then
	break
    fi
done
