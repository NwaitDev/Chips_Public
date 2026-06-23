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

package ujf.verimag.bip.metamodel.tool;

import java.util.Stack;

import org.eclipse.emf.ecore.EAnnotation;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EClassifier;
import org.eclipse.emf.ecore.EPackage;

import bip2.Bip2Package;
import bip2.impl.Bip2PackageImpl;

/**
 * Simple tool to gather all constraints found in the metamodel.
 * This is more a hack than a real tool, and should not be considered reliable
 * nor trustworthy.
 */
public class ConstraintsLister {

    private static Stack<EPackage> stack = new Stack<EPackage>();
    
    private static String getFullPackageName(){
        String s = "";
        
        for (EPackage ep : stack){
            s = s + "." + ep.getName();
        }
        return s.substring(1);
    }
    
    private static void visitPackage(EPackage pack){
        stack.push(pack);
        
        boolean first_pack = true;
        
        for (EClassifier ecl : pack.getEClassifiers()){
            if (ecl instanceof EClass){
                EAnnotation annot = ecl.getEAnnotation("http://www.eclipse.org/emf/2002/Ecore");
                if (annot == null) continue;
                
                String constraints = annot.getDetails().get("constraints");
                if (constraints == null) continue;
                boolean first = true;
                for(String c : constraints.split("\\s+")){
                    if (first_pack) {
                        System.out.println("==== " + getFullPackageName() + " ====");
                        first_pack = false;
                    }
                    if (first) {
                        System.out.println("=== " + ecl.getName() + " ===");
                        first = false;
                    }
                    System.out.println("  * " + c);
                }
            }
        }
        
        for (EPackage epack : pack.getESubpackages()){
            visitPackage(epack);
        }
        
        stack.pop();
    }
    
    /**
     * Displays all constraints found in the bip2 metamodel on standard output
     * @param args ignored
     */
    public static void main(String[] args) {
        Bip2PackageImpl.init();

        EPackage bp = EPackage.Registry.INSTANCE
        .getEPackage(Bip2Package.eNS_URI);

        visitPackage(bp);
    }
}
