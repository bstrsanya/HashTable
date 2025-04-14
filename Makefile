DEBUG_FLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
		-Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts \
		-Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal \
		-Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op \
		-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self \
		-Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel \
		-Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types \
		-Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code \
		-Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers \
		-Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new \
		-fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging \
		-fno-omit-frame-pointer -fPIE -Werror=vla \
		-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

## CC ?= g++ не работает, потому что берется default value CC := cc
ifeq ($(origin CC),default)
	CC = g++
endif 

LDFLAGS = -L./lib -lfileproces
# INTRINSIC = -msse4.1 -msse4.2 -mavx2 -mavx

CFLAGS ?= -O0 -g
OUT_O_DIR ?= build
COMMONINC = -I./lib -I./include
INSTALL_DIR = /usr/local/bin

override CFLAGS += $(COMMONINC)
override CFLAGS += $(INTRINSIC)

ifeq ($(debug), true)
    override CFLAGS += $(DEBUG_FLAGS) 
    override LDFLAGS += $(DEBUG_FLAGS)        
endif

CSRC = src/main.cpp src/func.cpp lib/List.cpp
COBJ = $(addprefix $(OUT_O_DIR)/,$(CSRC:.cpp=.o))
DEPS = $(COBJ:.o=.d)

.PHONY: all
all: hash_table

hash_table: $(COBJ)
	@$(CC) $^ -o $@ $(LDFLAGS)
	@echo 'project is created'

$(COBJ) : $(OUT_O_DIR)/%.o : %.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo 'compile $<'

$(DEPS) : $(OUT_O_DIR)/%.d : %.cpp
	@mkdir -p $(@D)
	@$(CC) -E $(CFLAGS) $< -MM -MT $(@:.d=.o) > $@

.PHONY: compile_commands
compile_commands:
	@bear -- make

.PHONY: install 
install: 
	@sudo install -m 755 hash_table $(INSTALL_DIR)

.PHONY: clean
clean:
	@rm -rf ./build hash_table compile_commands.json

# если вызванная цель НЕ clean то проверить изменения в хедэрах
NODEPS = clean
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
include $(DEPS)
endif