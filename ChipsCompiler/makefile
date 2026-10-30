SUBDIRS := ChipsModel2BipModel Chips2XmiParser Chips2Cpp

DIR := FullCompileChain

PREFIX ?= $(HOME)/.local
BINDIR := $(PREFIX)/bin

.PHONY: all BipCompiler $(SUBDIRS) clean install uninstall

BIPC := $(DIR)/BipCompiler/distribution/build/bipc-latest/bin/bipc
BIPC_SRCS := $(shell find $(DIR)/BipCompiler -path '$(DIR)/BipCompiler/distribution/build' -prune -o -type f -print)


all: $(BIPC) $(SUBDIRS)

$(BIPC): $(BIPC_SRCS)
	cd $(DIR)/BipCompiler/distribution && ./wrap.sh
	touch $@

$(SUBDIRS):
	$(MAKE) -C $(DIR)/$@

install: all
	mkdir -p $(BINDIR)
	chmod +x $(CURDIR)/chipsc
	printf '#!/bin/sh\nexec "%s" "$$@"\n' "$(CURDIR)/chipsc" > $(BINDIR)/chipsc
	chmod +x $(BINDIR)/chipsc
	@case ":$$PATH:" in \
		*":$(BINDIR):"*) echo "chipsc installed in $(BINDIR)" ;; \
		*) echo "chipsc installed in $(BINDIR), but $(BINDIR) is not in your PATH."; \
		   echo "Add this line to ~/.bashrc:  export PATH=\"$(BINDIR):\$$PATH\"" ;; \
	esac

uninstall:
	rm -f $(BINDIR)/chipsc

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $(DIR)/$$dir clean; \
	done