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

package ujf.verimag.bip.backend.tests.bip;

import static org.junit.Assert.*;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Arrays;

import org.eclipse.emf.ecore.util.EcoreUtil;
import org.eclipse.emf.ecore.*;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import bip2.ujf.verimag.bip.packaging.BipPackage;

import ujf.verimag.bip.backend.tests.AbstractBackendTests;

import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.emf.ecore.xmi.impl.XMLResourceFactoryImpl;
import org.eclipse.emf.common.util.URI;

public class BipBackendTests  extends AbstractBackendTests {
    final static String rootdir = "src/tests/resources/bip/";
    final static String outputdir = "build/bip/";
    final static String trashdir = "build/bip/trash";
	final static String serializeDir = "build/bip/serialized";

    private static void delete(File f) throws IOException {
        if (f.isDirectory()) {
            for (File c : f.listFiles())
                delete(c);
        }
        if (!f.delete())
            throw new FileNotFoundException("Failed to delete file: " + f);
    }

    private BipPackage runCompilerOn(String packagename){
        return runCompilerOn(packagename, rootdir, outputdir);
    }

    private BipPackage runCompilerOn(String packagename, String rootdir, String outputdir){
        try {
            String [] args = new String[]{"-I", rootdir,
                    "-p", packagename,
                    "--genbip-follow-used-packages",
                    "--genbip-output-dir", outputdir};
            setUpCompiler(args);
            if (this.compiler.run() == 0)
                return this.compiler.getRootPackage();
        } catch (Exception e) {
            fail("Can't setup Compiler.");
        }
        return null;
    }

	private void storeModel(BipPackage pack, String fileName) {
		//copied from PackageLoader
        // create resource set and resource 
        ResourceSet resourceSet = new ResourceSetImpl();

        // Register XML resource factory
        resourceSet.getResourceFactoryRegistry()
			.getExtensionToFactoryMap().put("xml", 
											new XMLResourceFactoryImpl());
        
        
        Resource resource = resourceSet.createResource(URI.createFileURI(serializeDir
																		 + "/" + fileName + ".xml"));
        // add the root object to the resource
        resource.getContents().add(pack);
        // serialize resource you can specify also serialization
        // options which defined on org.eclipse.emf.ecore.xmi.XMIResource
        try {
          resource.save(null);
        } catch (IOException e) {}
	}

    private boolean backAndForth(String packagename) {
        BipPackage orig = runCompilerOn(packagename);
        BipPackage refurb = runCompilerOn(packagename, outputdir, trashdir);
		if (orig != null && refurb != null) {
			boolean result =  EcoreUtil.equals(orig, refurb);
			if (!result) {
				storeModel(orig, packagename + "_original");
				storeModel(refurb, packagename + "_modified");
			}
			return result;
		}
		return false;
    }
    
	@BeforeClass
    public static void resetOutputDir() throws IOException {
		for (String file : Arrays.asList(outputdir, trashdir, serializeDir)) {
			File f = new File(file);
			if (f.exists()) {
				delete(f);
			}
			f.mkdirs();
		}
	}

    @Before
    public void setProperty(){
        System.setProperty("bip.compiler.backends", "ujf.verimag.bip.backend.bip.BipBackend");
    }

    @Test
    public void simple() {
        boolean ret = backAndForth("simple");
        if ( !ret )
            fail("BIP backend failed");
    }

    @Test
    public void hierarchy() {
        boolean ret = backAndForth("hierarchy");
        if ( !ret )
            fail("BIP backend failed");
    }

    @Test
    public void hierarchy_annotated() {
        boolean ret = backAndForth("hierarchy_annotated");
        if ( !ret )
            fail("BIP backend failed");
    }

    @Test
    public void tempcontrol() {
        boolean ret = backAndForth("tempcontrol");
        if ( !ret )
            fail("BIP backend failed");
    }

    @Test
    public void internal_port() {
        boolean ret = backAndForth("internal_port");
        if ( !ret )
            fail("BIP backend failed");
    }

    @Test
    public void modulo8() {
        boolean ret = backAndForth("modulo8");
        if ( !ret )
            fail("BIP backend failed");
    }

    @Test
    public void periodic_tick() {
        boolean ret = backAndForth("periodic_tick");
        if ( !ret )
            fail("BIP backend failed");
    }

    @Test
    public void priorities_atom() {
        boolean ret = backAndForth("priorities_atom");
        if ( !ret )
            fail("BIP backend failed");
    }

    @Test
    public void priorities_wildcard() {
        boolean ret = backAndForth("priorities_wildcard");
        if ( !ret )
            fail("BIP backend failed");
    }

    @Test
    public void use_create() {
        boolean ret = backAndForth("big.use_creation");
        if ( !ret )
            fail("BIP backend failed");
    }

    @Test
    public void const_data() {
        boolean ret = backAndForth("const_data");
        if ( !ret )
            fail("BIP backend failed");
    }
}
