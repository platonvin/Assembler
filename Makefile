CC ?= cc
CXX ?= g++

assembler_objs := \
	obj/assembler.o\
	obj/assembler_functions.o\
	obj/stack_functions.o\
	obj/string_funcs.o\

processor_objs := \
	obj/stack_functions.o\
	obj/string_funcs.o\
	obj/processor.o\

ifeq ($(OS),Windows_NT)
    ASM_TARGET := assembler.exe
    PROC_TARGET := processor.exe
# getopt impl for Windows
	assembler_objs += obj/getopt.o
	processor_objs += obj/getopt.o
else
    ASM_TARGET := assembler
    PROC_TARGET := processor
endif


all: init $(ASM_TARGET) $(PROC_TARGET)

flags = -O3 -Wno-deprecated-declarations -Wno-format
# flags = -O0 -g

obj/%.o: src/%.c
	$(CC) $(args) -std=c99 $(flags) -MMD -MP -c $< -o $@
DEPS = $(assembler_objs:.o=.d) $(processor_objs:.o=.d)
-include $(DEPS)

$(ASM_TARGET): $(assembler_objs)
	$(CXX) -o $@ $(assembler_objs) $(flags)  -std=c99
$(PROC_TARGET): $(processor_objs)
	$(CXX) -o $@ $(processor_objs) $(flags)  -std=c99

clean:
ifeq ($(OS),Windows_NT)
	del /Q obj\*.o obj\*.d
else
	rm -rf obj/*.o obj/*.d
endif

init: obj
obj:
ifeq ($(OS),Windows_NT)
	mkdir "obj"
else
	mkdir -p obj
endif
