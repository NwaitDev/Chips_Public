.PHONY: all clean transform compile

all:emftvm.class

emftvm.class: emftvm.java 
	javac -cp "lib/*" emftvm.java

run:
	./emftvm.sh metamodels/chips1.1.ecore metamodels/BIP.ecore examplemodels/TeaStoreVariationChips.xmi transformations/chips2bip.atl examplemodels/TeaStoreVariation.xmi

	bipc models/TeaStoreVariation.xmi -d 'SYSTEM_COMPOUND()' --gencpp-output models/output --genbip-output models/output

run-nofilter:
	./emftvm.sh metamodels/chips1.1.ecore metamodels/BIP.ecore models/TeaStoreVariationChips.xmi transformations/chips2bip.atl models/TeaStoreVariation.xmi
	# python3 filter_xmi.py models/TeaStoreVariation.xmi
	bipc models/TeaStoreVariation.xmi -d 'SYSTEM_COMPOUND' --gencpp-output models/output --genbip-output models/output
transform:
	./emftvm.sh metamodels/chips1.1.ecore metamodels/BIP.ecore examplemodels/TeaStoreVariation.chips.xmi transformations/chips2bip.atl examplemodels/TeaStoreVariation.bip.xmi 2>debug.log

compile: 
	mkdir -p examplemodels/output/build
	bipc --xmi examplemodels/TeaStoreVariation.bip.xmi -d 'SYSTEM_COMPOUND' --genbip-output examplemodels/output

clean: 
	rm *.class transformations/*.emftvm
	rm examplemodels/TeaStoreVariation.bip.xmi
	rm -r examplemodels/output