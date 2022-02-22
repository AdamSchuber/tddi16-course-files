#
# Makefile
#

CCC      = g++	
CCFLAGS += -std=c++17 -pedantic -Wall -g

avl_tree-test: avl_tree-test.o
	$(CCC) $(CCFLAGS) -o avl_tree-test avl_tree-test.o

avl_tree-test.o: avl_tree-test.cpp avl_tree.cpp
	$(CCC) $(CCFLAGS) -c avl_tree-test.cpp

clean:
	@ \rm -f *.o

zap: clean
	@ \rm -rf avl_tree-test *.o *~ 
