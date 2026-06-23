.PHONY: all clean transform compile

all:emftvm.class

emftvm.class: emftvm.java 
	javac -cp "lib/*" emftvm.java

transform:
	./emftvm.sh metamodels/chips1.1.ecore metamodels/BIP.ecore examplemodels/TeaStoreVariation.chips.xmi transformations/chips2bip.atl examplemodels/TeaStoreVariation.bip.xmi

compile: 
	mkdir -p examplemodels/output/build
	bipc --xmi examplemodels/TeaStoreVariation.bip.xmi -d 'SYSTEM_COMPOUND' --genbip-output examplemodels/output


clean: 
	rm *.class transformations/*.emftvm
	rm examplemodels/TeaStoreVariation.bip.xmi
	rm -r examplemodels/output