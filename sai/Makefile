#
#    Licensed under the Apache License, Version 2.0 (the "License"); you may 
#    not use this file except in compliance with the License. You may obtain 
#    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
#
#    THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR 
#    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
#    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS 
#    FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
#
#    See the Apache Version 2.0 License for specific language governing 
#    permissions and limitations under the License. 
#
#    Microsoft would like to thank the following companies for their review and
#    assistance with these files: Intel Corporation, Mellanox Technologies Ltd,
#    Dell Products, L.P., Facebook, Inc
#
IDIR = ./inc
CC = gcc
CFLAGS= -I$(IDIR) -DDebug -g -fPIC
LIBS = -lm

all: libdummy testdummy

_DEPS = sai.h saiacl.h sailag.h sainexthop.h  sairouter.h saistp.h\
	saifdb.h saimirror.h saiport.h sairouterintf.h saiswitch.h \
	saineighbor.h saiqos.h saisamplepacket.h saitypes.h saihostintf.h\
	sainexthopgroup.h sairoute.h saistatus.h saivlan.h\

DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

################################################
#DUMMY SECTIONS

ODIR_DUMMY = ./src/dummy/obj
LDIR_DUMMY = ./lib/dummy
SRCDIR_DUMMY = ./src/dummy

_DEPS_DUMMY = 	dummy_acl.h  dummy_lag.h dummy_nexthop.h dummy_rtr_intf.h\
	dummy_vlan.h dummy_fdb.h dummy_mirror_sess.h dummy_port.h\
	dummy_smpl_pkt_sess.h dummy_vrtr.h dummy_host_intf.h  dummy_nbr.h\
	dummy_qos.h dummy_stp.h test.h dummy_init.h dummy_nexthop_grp.h\
	dummy_route.h dummy_switch.h\

DEPS_DUMMY = $(patsubst %, $(SRCDIR_DUMMY)/%, $(_DEPS_DUMMY))


_OBJ_DUMMY = test.o dummy_switch.o dummy_port.o dummy_fdb.o dummy_vlan.o\
	dummy_vrtr.o dummy_route.o dummy_nexthop.o dummy_nexthop_grp.o\
	dummy_rtr_intf.o dummy_nbr.o dummy_qos.o dummy_acl.o\
	dummy_host_intf.o dummy_mirror_sess.o dummy_smpl_pkt_sess.o\
	dummy_stp.o dummy_lag.o dummy_init.o\

OBJ_DUMMY = $(patsubst %, $(ODIR_DUMMY)/%, $(_OBJ_DUMMY))

LIB_DUMMY = libsaidummy.so.0.9.2

$(ODIR_DUMMY)/%.o: $(SRCDIR_DUMMY)/%.c $(DEPS) $(DEPS_DUMMY)
	$(CC) -c -o $@ $< $(CFLAGS)

libdummy: $(OBJ_DUMMY)
	$(CC) -shared -Wl,-soname,libsaidummy.so.0 -o $(LDIR_DUMMY)/$(LIB_DUMMY)  $(OBJ_DUMMY)

testdummy: $(OBJ_DUMMY)
	gcc -o $@ $(CFLAGS) $(LIBS) $(LDIR_DUMMY)/$(LIB_DUMMY)

.PHONY: clean

clean:
	rm -f $(ODIR_DUMMY)/*.o $(SRCDIR_DUMMY)/*~  $(INDIR)/*~ $(LDIR_DUMMY)/* testdummy core

