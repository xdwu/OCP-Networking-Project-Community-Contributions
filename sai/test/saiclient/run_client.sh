#!/bin/bash
echo "*** Run the sai API Test Client example_test.pyi ***"
if [ ! -d "./switch_sai_thrift" ]; then
  cd ../saiserver
  make client
  cd ../saiclient
fi

python example_test.py
