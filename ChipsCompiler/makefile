SUBDIRS := BipXmiGenerator ChipsXmiGenerator CppGenerator

DIR := FullCompileChain

.PHONY: compile setup BipCompiler $(SUBDIRS) clean

all: compile

compile: BipCompiler $(SUBDIRS)

BipCompiler:
	cd $(DIR)/BipCompiler/distribution && ./wrap.sh

$(SUBDIRS):
	$(MAKE) -C $(DIR)/$@

setup:
	@echo "make cannot export environment variables to your shell."
	@echo "Please run this command yourself:"
	@echo "   cd FullCompileChain ; source ./setenv.sh"

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $(DIR)/$$dir clean; \
	done