.PHONY: all clean transform compile

FILE:=Drone#TeaStoreVariation

all:emftvm.class

emftvm.class: emftvm.java 
	javac -cp "lib/*" emftvm.java

transform:
	./emftvm.sh metamodels/chips1.1.ecore metamodels/BIP.ecore examplemodels/$(FILE).chips.xmi transformations/chips2bip.atl examplemodels/$(FILE).bip.xmi 2>debug.log

compile: 
	mkdir -p examplemodels/output/build
	bipc --xmi examplemodels/$(FILE).bip.xmi -d 'SYSTEM_COMPOUND' --genbip-output examplemodels/output

clean: 
	rm *.class transformations/*.emftvm
	rm examplemodels/$(FILE).bip.xmi
	rm -r examplemodels/output