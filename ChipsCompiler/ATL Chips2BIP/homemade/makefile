.PHONY: all clean run


all:EMFTVMLauncher.class

EMFTVMLauncher.class: EMFTVMLauncher.java 
	javac -cp "lib/*" EMFTVMLauncher.java

run:
	java -cp '.:lib/*' EMFTVMLauncher



clean: 
	rm *.class