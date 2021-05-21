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
# This example assumes that the ECN value stays unchanged at 0. When choosing the mask for the DSMARK qdisc, maintaining
# the ECN field value was taken into consideration.

# get default network interface
niface=`route | awk '/^default/{print $NF}'`

# clear previous qdiscs
tc qdisc del dev $niface root &> /dev/null

# clear iptables mangle rules
iptables -t mangle -F

# create dsmark qdisc
echo "Adding DSMARK qdisk..."
tc qdisc add dev $niface handle 1:0 root dsmark indices 8

# edit classes
# best effort traffic (DSCP 0)
echo "Changing DSCP value in first DSMARK class..."
#tc class change dev $niface classid 1:1 dsmark mask 0x0 value 0x0
# sau (punem in 0 valoarea dscp mentinand ecn in caz ca e folosit)
tc class change dev $niface classid 1:1 dsmark mask 0x3 value 0x0

# udp 6000
# set first 2 bits in dscp field, leaving others unchanged
echo "Changing DSCP value in second DSMARK class..."
tc class change dev $niface classid 1:2 dsmark mask 0x3f value 0xc0

# udp 7000 dscp
# set last 2 bits in dscp field, leaving others unchanged
echo "Changing DSCP value in third DSMARK class..."
tc class change dev $niface classid 1:3 dsmark mask 0xf3 value 0xc

# clear up previous tc filters, if any
tc filter del dev $niface prio 1 &> /dev/null

echo "Setting up tc filters..."
# set filters to add traffic to specific classes in the qdisc
# udp traffic on port 6000 on class 2
tc filter add dev $niface  parent 1: protocol ip prio 1 u32 \
    match ip dport 6000 0xffff match ip protocol 17 0xff flowid 10:2
# udp traffic on port 7000 on class 3
tc filter add dev $niface  parent 1: protocol ip prio 1 u32 \
    match ip dport 7000 0xffff match ip protocol 17 0xff flowid 10:3
# all other udp traffic on class 1
tc filter add dev $niface  parent 1: protocol ip prio 1 u32 \
    match ip protocol 17 0xff flowid 10:1

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
