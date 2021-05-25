# get default network interface
niface=`route | awk '/^default/{print $NF}'`

# clear previous qdiscs
tc qdisc del dev $niface root &> /dev/null

# clear iptables mangle rules
iptables -t mangle -F

# create dsmark qdisc
echo "Adding DSMARK qdisk..."
tc qdisc add dev $niface handle 1:0 root dsmark indices 8 default_index 1

# Configure DSMARK qdisc
# Best-effort traffic (DSCP 0)
echo "Configuring Class 1: Best Effort (DSCP 0)..."
tc class change dev $niface classid 1:1 dsmark mask 0x3 value 0x0

# UDP 6000: set first 2 bits in dscp field, leaving others unchanged
echo "Configuring Class 2: Set first two DSCP bits, leave others unchanged..."
tc class change dev $niface classid 1:2 dsmark mask 0x3f value 0xc0

# UDP 7000 dscp, set last 2 bits in dscp field, leaving others unchanged
echo "Configuring Class 3: Set last two DSCP bits, leave others unchamged..."
tc class change dev $niface classid 1:3 dsmark mask 0xf3 value 0xc

# Clear up previous tc filters
tc filter del dev $niface prio 1 &> /dev/null
tc filter del dev $niface prio 2 &> /dev/null

# Configure tc fitlers
echo "Configuring tc filters..."
# UDP traffic on port 6000 on qdisc class 2
tc filter add dev $niface  parent 1: protocol ip prio 1 u32 \
    match ip dport 6000 0xffff match ip protocol 17 0xff flowid 1:2

# UDP traffic on port 7000 on qdisc class 3
tc filter add dev $niface  parent 1: protocol ip prio 1 u32 \
    match ip dport 7000 0xffff match ip protocol 17 0xff flowid 1:3

# All other traffic, on qdisc class 1 (Best-Effort Traffic)
#tc filter add dev $niface parent 1: protocol ip prio 2 flowid 10:1

# Set DSCP value for UDP 6000,7000 using iptables
read -p "Enter DSCP value for Assured-Forwarding on UDP ports 6000,7000:" dscp
echo "Setting DSCP value using iptables..."

iptables -t mangle -A OUTPUT -p udp \
  --match multiport --dports 6000,7000 \
  -j DSCP --set-dscp $dscp
