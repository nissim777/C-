
STYLE_TESTER=~plabc/www/codingStyleCheck
PRESUBMIT_TESTER=~plabcpp/www/ex2/presubmit_ex2

EXE=ex2
TARFILE=$(EXE).tar

DEPS=Item.h Item.cpp DiscretItem.h DiscretItem.cpp ContinuousItem.h ContinuousItem.cpp Parser.h Parser.cpp ikea.cpp

all: $(EXE)

$(EXE): $(DEPS)
	g++ -Wall -Wextra -Wvla -std=c++14 -g $(DEPS) -o $(EXE)

tar: $(TARFILE)

$(TARFILE): $(DEPS)
	tar -cvf $(TARFILE) Makefile *.h *.cpp

clean:
	rm -rf $(TARFILE)
	rm -rf $(EXE)

style: $(EXE)
	$(STYLE_TESTER) .

presubmit: tar
	$(PRESUBMIT_TESTER) $(TARFILE)

valgrind: $(EXE)
	valgrind --leak-check=full --show-possibly-lost=yes $(EXE) --show-reachable=yes ./$(EXE) 

