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

CC = gcc
CFLAGS = -I$(IDIR) -Wall -DDebug -g -fPIC
LIBS = -lm

ODIR = ./lib/obj
DDIR = ./lib/dummy
IDIR = ./inc
LDIR = ./lib

all: libdummy testdummy dummy_unittest lltest bsttest

##########################################################
# SAI headers

_DEPS = sai.h saiacl.h sailag.h sainexthop.h  sairouter.h saistp.h\
		saifdb.h saimirror.h saiport.h sairouterintf.h saiswitch.h \
		saineighbor.h saiqos.h saisamplepacket.h saitypes.h saihostintf.h\
		sainexthopgroup.h sairoute.h saistatus.h saivlan.h\
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

##########################################################
#DUMMY SECTIONS

ODIR_DUMMY = ./lib/dummy/obj
LDIR_DUMMY = ./lib/dummy
SRCDIR_DUMMY = ./src/dummy

_DEPS_DUMMY =   dummy_acl.h  dummy_lag.h dummy_nexthop.h dummy_rtr_intf.h\
		dummy_vlan.h dummy_fdb.h dummy_mirror_sess.h dummy_port.h\
		dummy_smpl_pkt_sess.h dummy_vrtr.h dummy_host_intf.h  dummy_nbr.h\
		dummy_qos.h dummy_stp.h test.h dummy_init.h dummy_nexthop_grp.h\
		dummy_route.h dummy_switch.h dummy_init.h dummy_util.h dummy.h\
		dummy_ll.h dummy_bst.h

DEPS_DUMMY = $(patsubst %, $(LDIR_DUMMY)/%, $(_DEPS_DUMMY))

_OBJ_DUMMY = dummy_port.o dummy_switch.o dummy_fdb.o dummy_vlan.o\
		dummy_vrtr.o dummy_route.o dummy_nexthop.o dummy_nexthop_grp.o\
		dummy_rtr_intf.o dummy_nbr.o dummy_qos.o dummy_acl.o\
		dummy_host_intf.o dummy_mirror_sess.o dummy_smpl_pkt_sess.o\
		dummy_stp.o dummy_lag.o dummy_init.o dummy_util.o\
		dummy_ll.o dummy_bst.o

OBJ_DUMMY = $(patsubst %, $(ODIR_DUMMY)/%, $(_OBJ_DUMMY))

LIB_DUMMY = libsaidummy.so.0.9.2

$(ODIR_DUMMY)/%.o: $(LDIR_DUMMY)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -I$(LDIR_DUMMY) -I$(IDIR)

libdummy: $(OBJ_DUMMY)
	$(CC) -shared -Wl,-soname,libsaidummy.so.0 -o $(LDIR)/$(LIB_DUMMY)  $(OBJ_DUMMY) -I$(LDIR_DUMMY)

testdummy: $(OBJ_DUMMY) src/dummy/test.c
	gcc src/dummy/test.c -I$(DDIR) -o $@ $(CFLAGS) $(LIBS) $(LDIR)/$(LIB_DUMMY) -I$(LDIR_DUMMY)

lltest: $(OBJ_DUMMY) src/dummy/testll.c
	gcc src/dummy/testll.c -I$(DDIR) -o $@ $(CFLAGS) $(LIBS) $(LDIR)/$(LIB_DUMMY) -I$(LDIR_DUMMY)

bsttest: $(OBJ_DUMMY) src/dummy/testbst.c
	gcc src/dummy/testbst.c -I$(DDIR) -o $@ $(CFLAGS) $(LIBS) $(LDIR)/$(LIB_DUMMY) -I$(LDIR_DUMMY)

.PHONY: clean

clean:
	rm -f $(ODIR_DUMMY)/*.o $(SRCDIR_DUMMY)/*~  $(INDIR)/*~ $(LDIR)/libsaidummy.so.0.9.2 testdummy core \
$(TESTS) $(USER_ODIR)/gtest.a $(USER_ODIR)/gtest_main.a $(USER_ODIR)/*.o lltest bsttest


###########################################################
#GTEST SECTIONS COMMON

GTEST_DIR = ../../../GTEST/gtest-1.7.0
USER_DIR = ./src/dummy_unittest
USER_ODIR = ./src/dummy_unittest/obj
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread
TESTS = libdummy dummy_unittest 
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h
gall : $(TESTS)

gclean :
	rm -f $(TESTS) $(USER_ODIR)/gtest.a $(USER_ODIR)/gtest_main.a $(USER_ODIR)/*.o

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

$(USER_ODIR)/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
	$(GTEST_DIR)/src/gtest-all.cc -o $@

$(USER_ODIR)/gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
	$(GTEST_DIR)/src/gtest_main.cc -o $@

$(LDIR)/gtest.a : $(USER_DIR)/gtest-all.o
	$(AR) $(ARFLAGS) -o $@ $^ 

$(LDIR)/gtest_main.a : $(USER_ODIR)/gtest-all.o $(USER_ODIR)/gtest_main.o
	$(AR) $(ARFLAGS) -o $@ $^


##########################################################
#GTEST SECTIONS DUMMY_UNITTEST

$(USER_ODIR)/dummy_unittest.o : $(USER_DIR)/dummy_unittest.cc \
	$(GTEST_HEADERS) $(DEPS) 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I $(IDIR) -I$(DDIR) -I $(GTEST_DIR)/include/gtest/ \
	-I $(GTEST_DIR)/include/gtest/internal/ -c $(USER_DIR)/dummy_unittest.cc -o $@

dummy_unittest : $(LDIR)/$(LIB_DUMMY) $(USER_ODIR)/dummy_unittest.o $(LDIR)/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread -lm $^ -o $@ -I$(DDIR)


###########################################################
