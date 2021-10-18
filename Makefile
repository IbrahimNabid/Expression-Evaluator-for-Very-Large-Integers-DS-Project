%.out: %.cpp
	g++ -O0 -g -Wall -std=c++11 -Werror=return-type $^ -o $@

test: main.out
	valgrind --leak-check=full ./main.out

clean:
	rm -f *.out
