SUBDIRS := BipXmiGenerator ChipsXmiGenerator CppGenerator

DIR := FullCompileChain

CHIPS_SANDBOX := CHIPS_GENERATED
TESTS := testfiles

.PHONY: compile setup BipCompiler $(SUBDIRS) $(TESTS) $(CHIPS_SANDBOX) clean test clean_test

all: compile

compile: BipCompiler $(SUBDIRS)

BipCompiler:
	cd $(DIR)/BipCompiler/distribution && ./wrap.sh

$(SUBDIRS):
	$(MAKE) -C $(DIR)/$@

$(CHIPS_SANDBOX)/test.chips.xmi: $(TESTS)/TeaStoreVariation.chips $(DIR)/ChipsXmiGenerator
	./$(DIR)/ChipsXmiGenerator/chipsparser $< $@

$(CHIPS_SANDBOX)/test.bip.xmi: $(CHIPS_SANDBOX)/test.chips.xmi $(DIR)/BipXmiGenerator
	./$(DIR)/BipXmiGenerator/emftvm.sh \
	$(DIR)/metamodels/chips1.1.ecore \
	$(DIR)/metamodels/BIP.ecore \
	$< $(DIR)/BipXmiGenerator/transformations/chips2bip.atl $@ \
	2> $(CHIPS_SANDBOX)/debug.log

$(CHIPS_SANDBOX)/ChipsModel.bip: $(CHIPS_SANDBOX)/test.bip.xmi
	bipc --xmi $< -d "SYSTEM_COMPOUND" --genbip-output-dir $(CHIPS_SANDBOX) 2>$(CHIPS_SANDBOX)/debug.log
	sed -i 's/@0//g' $(CHIPS_SANDBOX)/ChipsModel.bip

$(CHIPS_SANDBOX)/bip_importable.o: testfiles/TeaStoreVariation.chips $(DIR)/CppGenerator 
	./$(DIR)/CppGenerator/build/Chips2Cpp $< -o $(CHIPS_SANDBOX)/bip_importable.cpp
	g++ -Wall -Wextra -std=c++17 $(CHIPS_SANDBOX)/bip_importable.cpp -c -o $@ 2>$(CHIPS_SANDBOX)/debug.log

# ABS_SANDBOX := $(abspath $(CHIPS_SANDBOX))

$(CHIPS_SANDBOX)/output/build/system: $(CHIPS_SANDBOX)/bip_importable.o  $(CHIPS_SANDBOX)/ChipsModel.bip
	mkdir -p $(CHIPS_SANDBOX)/output/build
	cd $(CHIPS_SANDBOX) && bipc -p ChipsModel \
	-d "SYSTEM_COMPOUND()" \
	--gencpp-cc-extra-src *.cpp \
	--gencpp-cc-I . \
	--gencpp-cc-extra-opt -std=c++17 \
	--gencpp-output output 2>debug.log
	cd $(CHIPS_SANDBOX)/output/build && cmake .. -Wno-dev
	$(MAKE) -C $(CHIPS_SANDBOX)/output/build 2> $(CHIPS_SANDBOX)/debug.log

test: $(CHIPS_SANDBOX)/output/build/system
	./$< 

clean_test:
	rm -r $(CHIPS_SANDBOX)/*

setup:
	@echo "make cannot export environment variables to your shell."
	@echo "Please run this command yourself:"
	@echo "   cd FullCompileChain ; source ./setenv.sh"

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $(DIR)/$$dir clean; \
	done