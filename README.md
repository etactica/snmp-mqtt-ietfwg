## Introduction

An exploration of implementing a custom MIB as a sub agent of net-snmp

This implements the NET-SNMP-EXAMPLES-MIB [1] IETF working group table example,
and allows the entries in that table to be updated via MQTT messages.

The very basic steps of starting this project were

1. mib2c -c mib2c.table_data.conf netSnmpIETFWGTable
2. grab the subagent/agent code and makefile from mib2c.mfd.conf or the web [2]
3. Add in mqtt, json parsing and the table update code.

This example project uses the "tdata" style, even though the mib2c config file
implies table_data.  net-snmp provides _many_ ways of working with tables! [3]
This is the way I found it easiest to understand and get started, but it is
by no means the only way to do this!  (I'm a complete net-snmp novice!)

## Dependencies
netsnmp (obviously, tested with net-snmp 5.7.2)
libmosquitto (Tested with mosquitto 1.2.3 and 1.3.1)
json-c (Tested with 0.11)

## Examples:

### Building the SNMP Agent

```
$ make
# run in foreground, as a master agent, with some logging, on an unprivileged port
$ ./netSnmpIETFWGTable -f -M -L -Dmosquitto,verbose,snmp-mqtt-ietfwg udp:localhost:1161
```

### Query the default entries

```
$ snmptable  -v 2c -c public -C i udp:localhost:1161 NET-SNMP-EXAMPLES-MIB::netSnmpIETFWGTable
SNMP table: NET-SNMP-EXAMPLES-MIB::netSnmpIETFWGTable

                 index  nsIETFWGChair1   nsIETFWGChair2
           "second wg"      "Andy Awe"     "Bobby Bush"
       "make it three" "Alan Aardvark" "Bruce Bullwhip"
"karls working group1"  "Albert Apple"    "Bill Braggy"
```

### Delete an entry:
```
$ mosquitto_pub -t "test/ietfwg/second wg/delete" -m body_ignored
$ snmptable  -v 2c -c public -C i udp:localhost:1161 NET-SNMP-EXAMPLES-MIB::netSnmpIETFWGTable
SNMP table: NET-SNMP-EXAMPLES-MIB::netSnmpIETFWGTable

                 index  nsIETFWGChair1   nsIETFWGChair2
       "make it three" "Alan Aardvark" "Bruce Bullwhip"
"karls working group1"  "Albert Apple"    "Bill Braggy"
```

### Add a new working group
```
$ mosquitto_pub -t "test/ietfwg/some_new_wg/update" -m '{"chair1" : "karlos", "chair2": "second karlos"}'
$ snmptable  -v 2c -c public -C i udp:localhost:1161 NET-SNMP-EXAMPLES-MIB::netSnmpIETFWGTableSNMP
table: NET-SNMP-EXAMPLES-MIB::netSnmpIETFWGTable

                 index  nsIETFWGChair1   nsIETFWGChair2
         "some_new_wg"        "karlos"  "second karlos"
       "make it three" "Alan Aardvark" "Bruce Bullwhip"
"karls working group1"  "Albert Apple"    "Bill Braggy"
```

### Update an existing group
This is the same as update, just using a working group name that already exists


[1] http://net-snmp.sourceforge.net/docs/mibs/NET-SNMP-EXAMPLES-MIB.txt
[2] http://www.net-snmp.org/docs/man/snmp_agent_api.html
[3] http://www.net-snmp.org/wiki/index.php/FAQ:Coding_07
