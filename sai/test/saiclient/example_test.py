"""
Thrift SAI interface basic tests
"""

import sys
sys.path.append('./')
import switch_sai_thrift

import time
import logging

import unittest
import random

import sai_base_test

import os

from switch_sai_thrift.ttypes import  *
from utils import *

this_dir = os.path.dirname(os.path.abspath(__file__))

port_list = []
table_attr_list = []


class L2AccessToAccessVlanTest(sai_base_test.ThriftInterface):
    def runTest(self):
        print
        #print "Sending L2 packet port 1 -> port 2 [access vlan=10])"
        print "Example Test Case for SAI API Test"
        switch_init(self.client)
        vlan_id = 10
        port1 = port_list[1]
        port2 = port_list[2]
        mac1 = '00:11:11:11:11:11'
        mac2 = '00:22:22:22:22:22'
        mac_action = 1

        self.client.sai_thrift_create_vlan(vlan_id)
        vlan_port1 = sai_thrift_vlan_port_t(port_id=port1, tagging_mode=0)
        vlan_port2 = sai_thrift_vlan_port_t(port_id=port2, tagging_mode=0)
        self.client.sai_thrift_add_ports_to_vlan(vlan_id, [vlan_port1, vlan_port2])

        sai_thrift_create_fdb(self.client, vlan_id, mac1, port1, mac_action)
        sai_thrift_create_fdb(self.client, vlan_id, mac2, port2, mac_action)


        sai_thrift_delete_fdb(self.client, vlan_id, mac1, port1)
        sai_thrift_delete_fdb(self.client, vlan_id, mac2, port2)

        self.client.sai_thrift_remove_ports_from_vlan(vlan_id, [vlan_port1, vlan_port2])
        self.client.sai_thrift_delete_vlan(vlan_id)

if __name__ == '__main__':
        unittest.main()
