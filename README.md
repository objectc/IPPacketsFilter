# IPV4 Packets Filter with 2d Range Tree


A filter rule set is a set of rules of the form:

sourceIP, destIP, action 

where action is either allow or block.  sourceIP is of the form a.b.c.d/k  (look up "slash ip address" for an explanation).  For destIP, a=1 and k<= 24.  You may think of destIP as the address space that our filter rules are protecting from external attack.

Notes:

1. When a packet arrives at the filter, we look for the first rule that matches the sourceIP and destIP fields of the incoming packet.  The action field determines whether the packet is blocked or forwarded to the destination.

2. Filter rules in practice also specify a  "port number" field which is used to block specific protocols.  We will ignore that for our project.

Getting Started:  Here is a list of things to complete first.

1. Generate test files consisting of filter rules.  To make sure that every incoming packet matches a rule, the last rule in your file should be of the form  *.*.*.*  ,  1.*.*.*  , action  No incoming packet with a=1 should be allowed.  This corresponds to disallowing spoofing attempts.  Generate test files of different sizes - tens, hundreds, thousands of rules.

2. Generate test files of incoming packets.

3. Implement the naive algorithm that, for each incoming packet, looks in linear order for a matching rule and records the action.

4.  For each (rules, packets) file pairs, record which packets are blocked and which are allowed.  Later we will share test files with other teams and make sure all teams agree on the outcome.


