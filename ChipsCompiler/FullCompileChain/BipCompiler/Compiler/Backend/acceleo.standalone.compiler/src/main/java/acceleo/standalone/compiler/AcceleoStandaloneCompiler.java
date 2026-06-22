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

package acceleo.standalone.compiler;

import java.security.CodeSource;

import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.resource.URIConverter;

import org.eclipse.emf.common.util.URI;

import org.eclipse.emf.ecore.xmi.impl.EcoreResourceFactoryImpl;

import org.eclipse.acceleo.common.IAcceleoConstants;
import org.eclipse.acceleo.model.mtl.MtlPackage;
import org.eclipse.acceleo.model.mtl.resource.EMtlResourceFactoryImpl;
import org.eclipse.acceleo.parser.compiler.AcceleoCompiler;
import org.eclipse.emf.ecore.resource.Resource;

import org.apache.tools.ant.BuildException;

import bip2.Bip2Package;

/**
 * This class is used to compile acceleo template without the need of
 * running the full eclipse IDE. It is a custom Ant task, and thus needs
 * to be executed from ant. It is a direct rip from Acceleo FAQ.
 *
 */
public class AcceleoStandaloneCompiler extends AcceleoCompiler {
    public void execute() throws BuildException {
      registerResourceFactories();
      registerPackages();
      registerLibraries();
  
      super.execute();
    }
  
    public void registerResourceFactories() {
      Resource.Factory.Registry.INSTANCE.getExtensionToFactoryMap().put("ecore", new EcoreResourceFactoryImpl());
      Resource.Factory.Registry.INSTANCE.getExtensionToFactoryMap().put(IAcceleoConstants.EMTL_FILE_EXTENSION, new EMtlResourceFactoryImpl());
  
      // Uncomment the following if you need to use UML models
      // Resource.Factory.Registry.INSTANCE.getExtensionToFactoryMap().put(UMLResource.FILE_EXTENSION, UMLResource.Factory.INSTANCE);
    }
  
    public void registerPackages() {
      // Uncomment if you need to use UML models
      EPackage.Registry.INSTANCE.put(Bip2Package.eNS_URI, Bip2Package.eINSTANCE);
      // Uncomment if you need to use UML models saved with on old version of MDT/UML (you might need to change the URI's version number)
      // EPackage.Registry.INSTANCE.put("http://www.eclipse.org/uml2/2.1.0/UML", UMLPackage.eINSTANCE);
    }
  
    public void registerLibraries() {
      CodeSource acceleoModel = MtlPackage.class.getProtectionDomain().getCodeSource();
      if (acceleoModel != null) {
        String libraryLocation = acceleoModel.getLocation().toString();
        if (libraryLocation.endsWith(".jar")) {
          libraryLocation = "jar:" + libraryLocation + '!';
        }
  
        URIConverter.URI_MAP.put(URI.createURI("http://www.eclipse.org/acceleo/mtl/3.0/mtlstdlib.ecore"),
                                 URI.createURI(libraryLocation + "/model/mtlstdlib.ecore"));
        URIConverter.URI_MAP.put(URI.createURI("http://www.eclipse.org/acceleo/mtl/3.0/mtlnonstdlib.ecore"),
                                 URI.createURI(libraryLocation + "/model/mtlnonstdlib.ecore"));
      } else {
        System.err.println("Coudln't retrieve location of plugin 'org.eclipse.acceleo.model'.");
      }
    }
  }
