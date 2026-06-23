/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Anakreontas Mentis
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
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

package ujf.verimag.bip.frontend.tests.parser;

import static org.junit.Assert.*;

import java.io.FileInputStream;

import org.antlr.runtime.ANTLRInputStream;
import org.antlr.runtime.CommonTokenStream;
import org.antlr.runtime.MismatchedTokenException;
import org.antlr.runtime.MissingTokenException;
import org.antlr.runtime.NoViableAltException;
import org.antlr.runtime.UnwantedTokenException;
import org.junit.Test;
import ujf.verimag.bip.parser.Bip2Lexer;
import ujf.verimag.bip.parser.Bip2Parser;

public class ParserTests {
    Bip2Lexer lexer ;
    Bip2Parser parser;
    
    public void setUp(String filename) throws Exception {
        FileInputStream filestream = new FileInputStream(filename);
        ANTLRInputStream input = new ANTLRInputStream(filestream);
        lexer = new Bip2Lexer(input);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        parser = new Bip2Parser(tokens);
    }

    @Test(expected = MismatchedTokenException.class)
    public void missingPackageName_01() throws Exception {
        setUp("src/tests/resources/syntax/01_missing_package_name.bip");
        try {
            parser.bip_package();
        } catch (MismatchedTokenException mte) {
            String expected = Bip2Parser.tokenNames[mte.expecting];
            if (expected.equalsIgnoreCase("package"))
                throw mte;
            else
                fail("MismatchedToken was not expecting PACKAGE token");
        }
        fail("No error found");
    }

    @Test(expected = MismatchedTokenException.class)
    public void emptyPackage_02() throws Exception {
        setUp("src/tests/resources/syntax/02_empty_package.bip");
        parser.bip_package();
    }
    
    @Test(expected = MismatchedTokenException.class)
    public void missingLparenTokenInPortTypeDefinition_03() throws Exception {
        setUp("src/tests/resources/syntax/03_missingLparenTokenInPortTypeDefinition.bip");
        try {
            parser.bip_package();
        } catch (MismatchedTokenException mte) {
            String expected = Bip2Parser.tokenNames[mte.expecting];
            if (expected.equalsIgnoreCase("LPAREN"))
                throw mte;
            else
                fail("MismatchedToken was not expecting LPAREN token");
        }
        fail("No error found");
    }
    
    @Test
    public void missingTypeTokenInPortTypeDefinition_04() throws Exception {
        setUp("src/tests/resources/syntax/04_missingTypeTokenInPortTypeDefinition.bip");
        parser.bip_package();
        
        boolean ok = (!parser.errors.isEmpty()) && (parser.errors.get(0).getAntlrException() instanceof MismatchedTokenException) &&
                Bip2Parser.tokenNames[((MismatchedTokenException)(parser.errors.get(0).getAntlrException())).expecting].equalsIgnoreCase("TYPE");

        if (!ok)
            fail("Did not catch missing 'type' in port type definition");
    }
    
    @Test
    public void badPackageNameStartsWithDigit_05() throws Exception {
        setUp("src/tests/resources/syntax/05_badPackageNameStartsWithDigit.bip");
        parser.bip_package();
        
        boolean ok = (!parser.errors.isEmpty()) && (parser.errors.get(0).getAntlrException() instanceof UnwantedTokenException) &&
                ((UnwantedTokenException)(parser.errors.get(0).getAntlrException())).token.getText().equalsIgnoreCase("01");
        if (!ok)
            fail("Did not catch package name starting with digit");
    }
    
    @Test
    public void noDoubleDotInPackageName_01_2() throws Exception {
        setUp("src/tests/resources/syntax/01_2_noDoubleDotInPackageName.bip");
        parser.bip_package();
        
        boolean ok = (!parser.errors.isEmpty()) && (parser.errors.get(0).getAntlrException() instanceof UnwantedTokenException) &&
                ((UnwantedTokenException)(parser.errors.get(0).getAntlrException())).token.getText().equalsIgnoreCase(".");
        if (!ok)
        	fail("Did not catch double '.' in package name");
    }
    
    @Test
    public void missingClosingEndTokenPackage_06() throws Exception {
        setUp("src/tests/resources/syntax/06_missingClosingEndTokenPackage.bip");
        parser.bip_package();
        
        boolean ok = (!parser.errors.isEmpty()) && (parser.errors.get(0).getAntlrException() instanceof MissingTokenException) &&
                (Bip2Parser.tokenNames[((MissingTokenException)(parser.errors.get(0).getAntlrException())).expecting].equalsIgnoreCase("END"));
        if (!ok)
            fail("Did not catch missing 'end' for ending package definition");
    }
    
    @Test
    public void noGarbageAfterClosingEnd() throws Exception {
        setUp("src/tests/resources/syntax/noGarbageAfterClosingEnd.bip");
        parser.bip_package();
    }
    

    @Test
    public void duplicatedExportPortInConnector() throws Exception {
        setUp("src/tests/resources/syntax/duplicatedExportPortInConnector.bip");
        boolean ok = false;
        try {
            parser.bip_package();
        } catch (MismatchedTokenException mte){
            ok = mte.token.getText().equalsIgnoreCase("export") && Bip2Parser.tokenNames[mte.expecting].equalsIgnoreCase("define");
        }
        
        if (!ok){
            fail("Did not catch garbage after closing end");
        }
    }
    
    @Test
    public void hierarchical_pack_hierarchicalPack() throws Exception {
        setUp("src/tests/resources/syntax/hierarchical/pack/hierarchicalPack.bip");
        boolean ok = true;
        parser.bip_package();
        ok = parser.errors.isEmpty() && lexer.errors.isEmpty();
        if (!ok){
            fail("Simple hierarchical package name not ok");
        }
       
    }

    @Test
    public void ifthenelse() throws Exception {
        setUp("src/tests/resources/syntax/10_ifthenelse.bip");
        parser.bip_package();
    }

    @Test
    public void nestedPortFlat() throws Exception {
        setUp("src/tests/resources/syntax/nested/flat.bip");
        parser.bip_package();
    }


    @Test
    public void nestedPortFlatQuoted() throws Exception {
        setUp("src/tests/resources/syntax/nested/flatquoted.bip");
        parser.bip_package();
    }

    @Test
    public void nestedPorts() throws Exception {
        setUp("src/tests/resources/syntax/nested/nested.bip");
        parser.bip_package();
    }
    
    @Test
    public void badFunctionCallExpression() throws Exception {
        setUp("src/tests/resources/syntax/badFunctionCallExpression.bip");
        parser.bip_package();
        
        boolean ok = (!parser.errors.isEmpty()) && (parser.errors.get(0).getAntlrException() instanceof MissingTokenException) &&
                (Bip2Parser.tokenNames[((MissingTokenException)(parser.errors.get(0).getAntlrException())).expecting].equalsIgnoreCase("SEMICOL"));
        if (!ok){
            fail("Did not catch incorrect function call expression");
        }
    }
    
    @Test(expected = MismatchedTokenException.class)
    public void badFieldAccessExpression() throws Exception {
        setUp("src/tests/resources/syntax/badFieldAccessExpression.bip");
        
        try {
            parser.bip_package();
        }
        catch (MismatchedTokenException mte) {
            String expected = Bip2Parser.tokenNames[mte.expecting];
            if (expected.equalsIgnoreCase("SEMICOL"))
                throw mte;
            else
                fail("Catch incorrect field access expression but with wrong expected token");
        }
        
        fail("Did not catch incorrect field access expression");
    }
}
