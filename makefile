all: report

report: proba.o structs.o temp_functions.o
	gcc -o report proba.o structs.o temp_functions.o

proba.o: proba.c
	gcc -c -o proba.o proba.c

structs.o: structs.c
	gcc -c -o structs.o structs.c

temp_functions.o: temp_functions.c
	gcc -c -o temp_functions.o temp_functions.c
clean:
	rm proba.o
	rm structs.o
	rm temp_functions.o
	rm report
