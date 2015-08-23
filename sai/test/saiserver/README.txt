* Prerequisite
    Vender specific SAI library is loaded
    libsai.so.0 => /usr/lib/libsai.so.0

    The sai headers are installed at
    /usr/include/sai/

* SAI Client and SAI Server Directories are as following
    saiclient
    saiserver

* build the saiserver and client sources required by the saiclient
    cd saiserver
    make

* start server binary
    switch-server

* Example of Client Side test case
    running the saiserver: sudo ./switch-server

    ./run_client

    More test cases can be extended at example_test.py
    Utility functions can be extended at utils.py

