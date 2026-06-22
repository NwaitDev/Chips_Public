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

package ujf.verimag.bip.backend.tests.cpp;

import static org.junit.Assert.*;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

import org.junit.Before;
import org.junit.Test;

import ujf.verimag.bip.backend.tests.AbstractBackendTests;

public class CppBackendTests  extends AbstractBackendTests {
    String rootdir = "src/tests/resources/cpp/";
    String outputdir = "build/cpp/";

    private static void delete(File f) throws IOException {
        if (f.isDirectory()) {
            for (File c : f.listFiles())
                delete(c);
        }
        if (!f.delete())
            throw new FileNotFoundException("Failed to delete file: " + f);
    }

    @Before
    public void resetOutputDir() throws IOException {
        File f = new File(outputdir);
        if (f.exists())
            delete(f);
        f.mkdirs();
      }

    @Before
    public void setProperty(){
        System.setProperty("bip.compiler.backends", "ujf.verimag.bip.backend.cpp.CppBackend");
    }

    @Before
    public void setUpOutputDirectory(){
        
    }

    private boolean runCompilerOn(String packagename, String rootDef){
        boolean ok = false;
        try {
            String [] args = new String[]{"-I", rootdir,
                    "-p", packagename,
                    "-d", rootDef,
                    "--gencpp-output-dir", outputdir};
            setUpCompiler(args);
            if (this.compiler.run() == 0)
                ok = true;
        } catch (Exception e) {
            fail("Can't setup Compiler.");
        }
        return ok;
    }

    @Test
    public void internal_port() {
        if (!runCompilerOn("internal_port", "MyCompound()"))
            fail("code generation failed");
    }

    @Test
    public void periodic_tick() {
        if (!runCompilerOn("periodic_tick", "MyCompound()"))
            fail("code generation failed");
    }

    @Test
    public void priorities_atom() {
        if (!runCompilerOn("priorities_atom", "MyCompound()"))
            fail("code generation failed");
    }

    @Test
    public void priorities_wildcard() {
        if (!runCompilerOn("priorities_wildcard", "MyCompound()"))
            fail("code generation failed");
    }

    @Test
    public void hierarchy() {
        if (!runCompilerOn("hierarchy", "MyCompound()"))
            fail("code generation failed");
    }

    @Test
    public void ifthenelse() {
        if (!runCompilerOn("ifthenelse", "CT()"))
            fail("code generation failed");
    }

    @Test
    public void const_data() {
        if (!runCompilerOn("const_data", "CT()"))
            fail("code generation failed");
    }
}
