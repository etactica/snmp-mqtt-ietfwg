
CC=gcc
TABLE_PREFIX=netSnmpIETFWGTable

NETSNMPCONFIG=net-snmp-config


# uncomment this if you have GNU make
NETSNMPCFLAGS := $(shell $(NETSNMPCONFIG) --base-cflags)
NETSNMPLIBS := $(shell $(NETSNMPCONFIG) --agent-libs)

LIBS=$(NETSNMPLIBS)


STRICT_FLAGS = -Wall -Wstrict-prototypes
CFLAGS=-I. $(NETSNMPCFLAGS) $(STRICT_FLAGS)

SRCS = 	$(TABLE_PREFIX).c
SRCS +=	$(TABLE_PREFIX)_subagent.c

OBJS = $(SRCS:.c=.o)

TARGETS=$(TABLE_PREFIX)

.SUFFIXES:
.SUFFIXES: .c .o .deps


all: $(TARGETS)


$(TARGETS): $(LIB_DEPS)

$(TABLE_PREFIX): $(OBJS) Makefile
	$(CC) -o $(TABLE_PREFIX) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS) $(TARGETS)

