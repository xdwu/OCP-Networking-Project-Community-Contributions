CXX=g++
CFLAGS = -I/usr/include/sai -I. -std=c++11
DEPS = switch_sai_constants.h  switch_sai_rpc.h  switch_sai_types.h
OBJS = switch_sai_constants.o  switch_sai_rpc.o  switch_sai_types.o

SAICLIENTDIR = ../saiclient
ODIR = ./src/obj
SAIDIR = ./include
SRC = ./src
THRIFT = /usr/local/bin/thrift
LIBS = -lthrift -lpthread
EXTRA_LIBS = -lJudy -lpcap
BUILT_SOURCES = \
				src/gen-cpp/switch_sai_constants.cpp \
				src/gen-cpp/switch_sai_constants.h \
				src/gen-cpp/switch_sai_rpc.cpp \
				src/gen-cpp/switch_sai_rpc.h \
				src/gen-cpp/switch_sai_types.cpp \
				src/gen-cpp/switch_sai_types.h

CLIENT_SOURCES = \
				src/gen-py/__init__.py \
				src/gen-py/switch_sai/constants.py \
				src/gen-py/switch_sai/__init__.py \
				src/gen-py/switch_sai/switch_sai_rpc.py \
				src/gen-py/switch_sai/switch_sai_rpc-remote \
				src/gen-py/switch_sai/ttypes.py

MKDIR_P = mkdir -p

all: directories $(ODIR)/librpcserver.a switch-server client

directories:
	$(MKDIR_P) $(ODIR)

$(BUILT_SOURCES): src/switch_sai.thrift
	$(THRIFT) -o $(SRC) --gen cpp -r $(SRC)/switch_sai.thrift

$(CLIENT_SOURCES): src/switch_sai.thrift
	$(THRIFT) -o $(SRC) --gen py -r $(SRC)/switch_sai.thrift 

client: $(CLIENT_SOURCES)
	cp -r ./src/gen-py/switch_sai/ ../saiclient/switch_sai_thrift

$(ODIR)/%.o: src/gen-cpp/%.cpp 
	$(CXX) $(CFLAGS) -c $^ -o $@

$(ODIR)/switch_sai_rpc_server.o: src/switch_sai_rpc_server.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@ $(CFLAGS) -I$(SRC)/gen-cpp

$(ODIR)/server.o: src/server.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@ $(CFLAGS) -I$(SRC)/gen-cpp -I$(SRC)

$(ODIR)/librpcserver.a: $(ODIR)/switch_sai_rpc.o $(ODIR)/switch_sai_types.o $(ODIR)/switch_sai_constants.o $(ODIR)/switch_sai_rpc_server.o
	ar rcs $(ODIR)/librpcserver.a $(ODIR)/switch_sai_rpc.o $(ODIR)/switch_sai_types.o $(ODIR)/switch_sai_constants.o $(ODIR)/switch_sai_rpc_server.o

switch-server: $(ODIR)/server.o  $(ODIR)/librpcserver.a 
	$(CXX) $(ODIR)/switch_sai_rpc_server.o $(ODIR)/server.o -o switch-server \
			$(ODIR)/librpcserver.a $(LIBS) -lsai

clean:
	rm -rf $(ODIR) $(SRC)/gen-cpp $(SRC)/gen-py switch-server $(SAICLIENTDIR)/switch_sai_thrift $(SAICLIENTDIR)/*.pyc
