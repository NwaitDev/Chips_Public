.PHONY: all clean run


all:emftvm.class

emftvm.class: emftvm.java 
	javac -cp "lib/*" emftvm.java

run:
	./emftvm.sh metamodels/chips1.1.ecore metamodels/BIP.ecore TeaStoreVariation.xmi transformations/chips2bip.atl models/output.xmi

clean: 
	rm *.class