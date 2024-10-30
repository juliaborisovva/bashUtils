CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
NAME = my_cat
COMMON = ../common/my_common
STRING = ../common/my_string

.PHONY: all
all: my_cat

.PHONY: my_string.a
my_string.a: $(STRING).c $(STRING).h
	${CC} $(CFLAGS) -c $(STRING).c -o $(STRING).o
	ar rc $(STRING).a $(STRING).o

.PHONY: my_cat
my_cat: my_string.a $(NAME).c $(NAME).h $(COMMON).*
	${CC} $(CFLAGS) $(NAME).c $(COMMON).c -L. $(STRING).a -o $(NAME)

.PHONY: test
test: my_cat
	bash cat_test.sh

.PHONY: checks
checks:
	cp ../../materials/linters/.clang-format .
	cp ../../materials/linters/.clang-format ../common/
	clang-format --style=file *.c *.h $(COMMON).* $(STRING).c $(STRING).h -i
	clang-format --style=file *.c *.h $(COMMON).* $(STRING).c $(STRING).h -n
	cppcheck --enable=all --suppress=missingIncludeSystem --check-config *.c *.h $(COMMON).* $(STRING).c $(STRING).h
	rm .clang-format
	rm ../common/.clang-format

.PHONY: clean
clean: 
	rm -f *.o *.a *.out $(STRING).a $(STRING).o my_cat orig.txt my.txt

