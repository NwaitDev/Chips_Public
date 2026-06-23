.PHONY: all clean run


all:emftvm.class

emftvm.class: emftvm.java 
	javac -cp "lib/*" emftvm.java

run:
	./emftvm.sh metamodels/chips1.1.ecore metamodels/BIP.ecore examplemodels/TeaStoreVariation.chips.xmi transformations/chips2bip.atl models/TeaStoreVariation.bip.xmi
	bipc models/TeaStoreVariation.xmi -d 'SYSTEM_COMPOUND' --gencpp-output examplemodels/output --genbip-output examplemodels/output


clean: 
	rm *.class transformations/*.emftvm
	rm examplemodels/TeaStoreVariation.bip.xmi