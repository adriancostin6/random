#!/bin/sh

# Configure iptables for a basic stateful firewall

if [ $(id -u) -ne 0 ]
then 
    echo "This script requires elevated privileges. Exiting..."
    exit
fi

echo "Current iptables configuration is:"
iptables -nvL
echo

echo "Select option:"
echo "1. Reset iptables to empty default configuration"
echo "2. Configure iptables for basic stateful firewall"
echo

read -p "Choose option. (1/2) " choice

if [ $choice -eq 1 ]
then
    echo "Clearing iptables configuration..."
    iptables-restore < /etc/iptables/empty.rules
    exit
fi

# Require the user to clear the previous configurations
echo "Clearing previous iptables configuration..."
iptables-restore < /etc/iptables/empty.rules

echo
echo "Starting basic stateful firewall configuration..."

echo "Creating user-defined chains for TCP and UDP..."
iptables -N TCP
iptables -N UDP

echo
echo "Setting policies for default chains..."

echo "FORWARD chain policy: DROP all forwarding traffic"
iptables -P FORWARD DROP

echo "OUTPUT chain policy: allow all outbound traffic"
iptables -P OUTPUT ACCEPT

echo "INPUT chain policy: DROP all inbound traffic"
iptables -P INPUT DROP

echo
echo "Appending additional rules to INPUT..."

echo "INPUT chain rule: allow traffic from RELATED and ESTABLISHED connections"
iptables -A INPUT -m conntrack --ctstate RELATED,ESTABLISHED -j ACCEPT

echo "INPUT chain rule: allow loopback traffic"
iptables -A INPUT -i lo -j ACCEPT

echo "INPUT chain rule: drop all traffic with and invalid state"
# Account for ICMPv6 neighbour discovery that remains untracked and is marked
# as invalid.
iptables -A INPUT -p 41 -j ACCEPT
iptables -A INPUT -m conntrack --ctstate INVALID -j DROP

echo "INPUT chain rule: allow new ICMP echo requests"
iptables -A INPUT -p icmp --icmp-type 8 -m conntrack --ctstate NEW -j ACCEPT

echo "Attaching user created TCP and UDP to INPUT chain..."
iptables -A INPUT -p udp -m conntrack --ctstate NEW -j UDP
iptables -A INPUT -p tcp --syn -m conntrack --ctstate NEW -j TCP

echo "Adding rules for rejecting incoming traffic..."

# Reject TCP connections with TCP RESET
iptables -A INPUT -p tcp -j REJECT --reject-with tcp-reset

# Reject UDP streams with ICMP port unreachable
iptables -A INPUT -p udp -j REJECT --reject-with icmp-port-unreachable

# Reject all other incoming traffic with ICMP protocol unreachable
iptables -A INPUT -j REJECT --reject-with icmp-proto-unreachable

echo "Saving base configuration for stateful firewall..."
iptables-save -f /etc/iptables/iptables.rules

echo
read -p "Add basic TCP/UDP rules? (y/n)" choice

if [ "$choice" != "y" ]
then
echo
echo "Configure custom TCP/UDP rules using iptables."
echo "Example: iptables -A <TCP/UDP> -p <PROTOCOL> [OPTIONS] -j <TARGET>"
echo "For more information see: man iptables and iptables -h."
echo "When you have reached your desired configuration save it using:"
echo "iptables-save -f /etc/iptables/iptables.rules"
echo "To clear all iptables configurations use: iptables-restore < /etc/iptables/empty.rules"
exit 
fi

read -p "Allow SSH connections on port 22? (y/n)" choice
if [ "$choice" = "y" ]
then
iptables -A TCP -p tcp --dport 22 -j ACCEPT
fi

read -p "Allow HTTP connections (TCP port 80)? (y/n)" choice
if [ "$choice" = "y" ]
then
iptables -A TCP -p tcp --dport 80 -j ACCEPT
fi

read -p "Allow HTTPS connections (TCP port 443)? (y/n)" choice
if [ "$choice" = "y" ]
then
iptables -A TCP -p tcp --dport 443 -j ACCEPT
fi

read -p "Allow TCP/UDP requests for a DNS server (port 53)? (y/n)" choice
if [ "$choice" = "y" ]
then
iptables -A TCP -p tcp --dport 53 -j ACCEPT
iptables -A TCP -p tcp --dport 53 -j ACCEPT
fi

echo "Saving current rules..."
iptables-save -f /etc/iptables/iptables.rules

echo
echo "Configure other custom TCP/UDP rules using iptables."
echo "Example: iptables -A <TCP/UDP> -p <PROTOCOL> [OPTIONS] -j <TARGET>"
echo "For more information see: man iptables and iptables -h."
echo "When you have reached your desired configuration save it using:"
echo "iptables-save -f /etc/iptables/iptables.rules"
echo "To clear all iptables configurations use: iptables-restore < /etc/iptables/empty.rules"
