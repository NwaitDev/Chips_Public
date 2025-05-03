.PHONY: all clean run runverb view version


PGM := main
COMPOUND := $(PGM)Compound
COMPILER_DISTRIB_PATH := /home/ngallone/Documents/compiler/distribution/build/bipc-latest/bin

# Packages path
PPATH := ../Packages

# Packages names
PNAMES := Constants FileStuff Printers Utils Base PhysicalFunctions VirtualFunctions

BIPSOURCES := $(shell find $(PPATH) -name '*.bip')
CPPSOURCES := $(shell find $(PPATH) -name '*.cpp')
CPPOBJ := $(shell find $(PPATH) -name '*.o')
HPPSOURCES := $(shell find $(PPATH) -name '*.hpp')
PDIRS := $(foreach n, $(PNAMES),$(PPATH)/$n)

INCLUDE_BIP_PACKAGES := $(foreach n, $(PDIRS), -I $n)
INCLUDE_CPP_PACKAGES := $(foreach d, $(PDIRS), --gencpp-cc-I $d)
CPP_EXTRA_OBJ := $(foreach o, $(CPPOBJ), --gencpp-ld-extra-obj $o)


COLOR_RESET := \033[0m
COLOR_RED := \033[31m
COLOR_GREEN := \033[32m
COLOR_GOLDEN := \033[33m
COLOR_BLUE := \033[34m

# Compilation
all: output/build/system

version:
	$(COMPILER_DISTRIB_PATH)/bipc.sh --version

# Compile $(PGM)
output/build/system: $(PGM).bip $(BIPSOURCES) $(CPPSOURCES)
	mkdir -p output/build

	$(COMPILER_DISTRIB_PATH)/bipc.sh -p $(PGM) -d "$(COMPOUND)()" $(INCLUDE_BIP_PACKAGES) $(INCLUDE_CPP_PACKAGES) \
		--genbip-follow-used-packages \
		--gencpp-follow-used-packages \
		$(CPP_EXTRA_OBJ)\
		--gencpp-output output

	cd output/build && cmake .. -Wno-dev

	$(MAKE) -C output/build 2>errout.log

clean:
	@echo "$(COLOR_RED)rm -rf output$(COLOR_RESET)"
	@rm -rf output


run: output/build/system
	@rm -f output/*.csv
	@echo "$(COLOR_BLUE)Running program...$(COLOR_RESET)"
	@./output/build/system --silent 1> output/stdout.log 2>output/stderr.log
	@echo "$(COLOR_BLUE)Running complete!$(COLOR_RESET)"

runverb:
	@rm -f output/*.csv
	@echo "$(COLOR_BLUE)Running program...$(COLOR_RESET)"
	@./output/build/system  1> output/stdout.log 2>output/stderr.log
	@echo "$(COLOR_BLUE)Running complete! trace written to output/std{out,err}.log$(COLOR_RESET)"

view: view.gp output/DataTreatmentBlock.csv
	@echo "$(COLOR_BLUE)gnuplot view.gp$(COLOR_RESET)"
	@gnuplot view.gp
