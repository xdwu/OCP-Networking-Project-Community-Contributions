"""
Base classes for test cases

Tests will usually inherit from one of these classes to have the controller
and/or dataplane automatically set up.
"""

import os
import logging
import unittest
import sys

################################################################
#
# Thrift interface base tests
#
################################################################

sys.path.append('./')
import switch_sai_thrift
import switch_sai_thrift.switch_sai_rpc as switch_sai_rpc


from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

class ThriftBaseTest(unittest.TestCase):
    def __str__(self):
        return self.id().replace('.runTest', '')

    def setUp(self):
        logging.info("** START TEST CASE " + str(self))

    def tearDown(self):
        logging.info("** END TEST CASE " + str(self))

class ThriftInterface(ThriftBaseTest):

    def setUp(self):
        ThriftBaseTest.setUp(self)

        # Set up thrift client and contact server
        self.transport = TSocket.TSocket('localhost', 9092)
        self.transport = TTransport.TBufferedTransport(self.transport)
        self.protocol = TBinaryProtocol.TBinaryProtocol(self.transport)

        self.client = switch_sai_rpc.Client(self.protocol)
        self.transport.open()

    def tearDown(self):
        ThriftBaseTest.tearDown(self)
        self.transport.close()
