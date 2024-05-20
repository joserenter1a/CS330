cc = gcc

sources = main.c mmio.c
objects = $(addsuffix .o, $(basename $(sources)))

flags = -g -std=c11 

target = spmv

test : all
	./spmv test1/A.mtx test1/x.mtx result
	diff -q result test1/ans.mtx

	./spmv test2/A.mtx test2/x.mtx result2
	diff -q result2 test2/ans.mtx

all: $(target) 

$(target) : $(objects)
	$(cc) $(flags) -o $(target) $(objects)

%.o : %.c
	$(cc) -c $(flags) $< -o $@

clean:
	rm -rf $(target) $(objects) 
