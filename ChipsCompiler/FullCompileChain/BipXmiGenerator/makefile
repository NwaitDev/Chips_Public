.PHONY: all clean transform compile


all:transformations/chips2bip.emftvm

emftvm.class: emftvm.java 
	javac -cp "lib/*" emftvm.java

transformations/chips2bip.emftvm: emftvm.class
	./emftvm.sh -c transformations/chips2bip.atl

clean: 
	rm *.class transformations/*.emftvm