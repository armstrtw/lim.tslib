XMIM_DIR     = /opt/lim/xmim

XMIM_LIBDIR  = $(XMIM_DIR)/lib
XMIM_INCDIR  = $(XMIM_DIR)/include

XMIM_LIB     = xmim

LIBS     = -L$(XMIM_LIBDIR) -l$(XMIM_LIB) -lm -lnsl -lform

CFLAGS = -Wall -O0 -g -fpic -I.. -I$(XMIM_INCDIR)
CXXFLAGS = $(CFLAGS)
LDFLAGS = $(LIBS)
CXX      = g++

.PHONY: test

test:
	$(CXX) $(CXXFLAGS) test.cpp -o $@ $(LDFLAGS)
	./test

clean:
	rm -f ./test
