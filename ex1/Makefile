all:
	g++ -Wall -Wextra -Wvla -std=c++14 -g big_integer.h big_integer.cpp big_int_tester.cpp -o testint
	g++ -Wall -Wextra -Wvla -std=c++14 -g big_integer.h big_integer.cpp my_set.h my_set.cpp my_set_tester.cpp -o testset
	
testint:
	g++ -Wall -Wextra -Wvla -std=c++14 -g big_integer.h big_integer.cpp big_int_tester.cpp -o testint
	./testint

testset:
	g++ -Wall -Wextra -Wvla -std=c++14 -g big_integer.h big_integer.cpp my_set.h my_set.cpp my_set_tester.cpp -o testset
	./testset

tar:
	tar -cvf ex1.tar Makefile big_integer.h big_integer.cpp my_set.h my_set.cpp

clean:
	rm -rf *.o
	rm -rf testint
	rm -rf testset
	rm -rf ex1.tar

valgrindset: testset
	valgrind --leak-check=full --show-possibly-lost=yes --show-reachable=yes ./testset

valgrindint: testint
	valgrind --leak-check=full --show-possibly-lost=yes --show-reachable=yes ./testint

style:
	~plabc/www/codingStyleCheck big_integer.h
	~plabc/www/codingStyleCheck big_integer.cpp
	~plabc/www/codingStyleCheck my_set.h
	~plabc/www/codingStyleCheck my_set.cpp
presubmit:
	~plabcpp/www/ex1/presubmit_ex1 ex1.tar
