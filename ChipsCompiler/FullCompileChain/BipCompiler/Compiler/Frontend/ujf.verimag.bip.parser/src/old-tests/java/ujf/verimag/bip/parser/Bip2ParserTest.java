/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 * 
 * This software is a computer program whose purpose is to generate
 * executable code from BIP models.
 * 
 * This software is governed by the CeCILL-B license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-B
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 * 
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security.
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-B license and that you accept its terms.
 */

package ujf.verimag.bip.parser;

import static org.junit.Assert.*;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;


import org.antlr.runtime.ANTLRFileStream;
import org.antlr.runtime.CharStream;
import org.antlr.runtime.CommonTokenStream;
import org.antlr.runtime.RecognitionException;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

@RunWith(Parameterized.class)
public class Bip2ParserTest {

	private String filename;

    public Bip2ParserTest(String filename) {
        this.filename = filename;
    }
	
    @Parameters
    public static Collection<Object[]> data() {
    	URL testDir = Bip2ParserTest.class.getResource("/syntax-tests");
    	    	
    	File f = new File(testDir.getPath());
    	File[] children = f.listFiles();
    	if (children == null)
    		fail("Root directory is not a directory ?!");
    	
    	List<File> directory_to_walk = new ArrayList<File>();
    	directory_to_walk.add(f);
    	
		Collection<Object[]> data = new ArrayList<Object[]>();

    	while (!directory_to_walk.isEmpty()){
    		File cur_file = directory_to_walk.get(0);
    		directory_to_walk.remove(0);
    		
    		if (cur_file.isDirectory()){
    			for (File child: cur_file.listFiles()){
    				directory_to_walk.add(child);
    			}
    		} else {
    			data.add(new Object[]{cur_file.getPath()});
    		}
    	}
    	return data;
    }


	@Test
	public void testBip_file() throws Exception {
		CharStream input = null;
		try {
			input = new ANTLRFileStream(this.filename);
		} catch (IOException e) {
			fail("Error opening test file:" + this.filename);
		}

		Bip2Lexer lexer = new Bip2Lexer(input);
		CommonTokenStream tokens = new CommonTokenStream(lexer);
		Bip2Parser parser = new Bip2Parser(tokens);
		
		try {
			Bip2Parser.bip_package_return bfr = parser.bip_package();
		} catch (RecognitionException e) {
			fail("Error parsing file:" + this.filename);
		} catch (Exception e){
			System.err.println("Exception with file:" + this.filename);
			throw e;
		}
		int errors = parser.getNumberOfSyntaxErrors();
		if (errors > 0 && this.filename.contains("good")){
			fail("["+ this.filename  + "]" + errors + " errors during parsing [unexpected errors]");
		} else if (errors == 0 && this.filename.contains("bad")){
			fail ("["+ this.filename  + "]" + ": bad file compiled unexpectedly");
		}
	}

}
