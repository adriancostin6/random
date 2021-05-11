# Create DSMARK queuing disciplines(qdisc) using the tc(traffic control) command on linux
# to change the values of the DSCP field in network packets using a mask and value pair.
# Also mangles OUTPUT table using the iptables command to set the DSCP field to different 
# values for assured forwarding.
# From my limited understanding of Linux QoS at the moment, this configuration will split 
# the output traffic into three classes, one for best effort(dscp=0), one for port udp 7000,
# and one for udp port 6000. 

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
tc class change dev eth1 classid 1:3 dsmark mask 0xf0 value 0xc

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
