assembler_objs := \
	obj/assembler.o\
	obj/assembler_functions.o\
	obj/stack_functions.o\
	obj/string_funcs.o\

processor_objs := \
	obj/stack_functions.o\
	obj/string_funcs.o\
	obj/processor.o\

all: init assembler processor

obj/%.o: src/%.c
	cc $(args) -std=c99 -O3 -MMD -MP -c $< -o $@
DEPS = $(objs:.o=.d)
-include $(DEPS)

assembler: $(assembler_objs)
	g++ -o assembler $(assembler_objs) -O3 -std=c99
processor: $(processor_objs)
	g++ -o processor $(processor_objs) -O3 -std=c99

clean:
ifeq ($(OS),Windows_NT)
	del "obj\*.o"
else
	rm -R obj/*.o
endif

init: obj
obj:
ifeq ($(OS),Windows_NT)
	mkdir "obj"
else
	mkdir -p obj
endif
