.PHONY: all clean run


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


clean: 
	rm *.class transformations/*.emftvm
	rm models/TeaStoreVariation.xmi