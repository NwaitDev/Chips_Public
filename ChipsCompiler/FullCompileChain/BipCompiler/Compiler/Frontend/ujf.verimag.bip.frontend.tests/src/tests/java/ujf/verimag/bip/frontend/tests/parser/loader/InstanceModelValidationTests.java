/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
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

package ujf.verimag.bip.frontend.tests.parser.loader;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import bip2.ujf.verimag.bip.component.ComponentDeclaration;
import bip2.ujf.verimag.bip.component.ComponentFactory;
import bip2.ujf.verimag.bip.types.ComponentType;

import ujf.verimag.bip.error.message.ErrorCodeEnum;
import ujf.verimag.bip.instantiator.Instantiator;
import ujf.verimag.bip.instantiator.InstantiatorException;
import ujf.verimag.bip.parser.loader.LoadPackageException;

public class InstanceModelValidationTests extends AbstractPackageLoaderTests {

    String rootDirectory = "src/tests/resources/instancemodelvalidation";

    public ComponentDeclaration createRootDeclaration(){
        ComponentType ct = this.pl.getComponentType("CT").get(0);
        
        StringBuffer fake_context = new StringBuffer(ct.getName() + " ROOT()");//
        
        ComponentDeclaration cd = ComponentFactory.eINSTANCE.createComponentDeclaration();
        cd.setLocationInfo(1, 0);
        cd.setType(ct);
        cd.setName("ROOT");
        cd.setSourceStringBuffer(fake_context);
        
        return cd;
    }
    
    @Before
    public void setUp() throws Exception {
        setUp(rootDirectory);
    }
    
    @Test
    public void connectorDoesNotBindTheSameComponentMoreThanOnce() throws LoadPackageException {
        boolean ok = false;
        
        this.pl.getPackage("connectorDoesNotBindTheSameComponentMoreThanOnce", true);
        ComponentDeclaration cd = createRootDeclaration();
        Instantiator instantiator = new Instantiator(this.pl);
        try {
            instantiator.instantiateTopLevel(cd);
        } catch (InstantiatorException e){
            ok = e.getErrors().length == 1 && e.getErrors()[0].errorcode == ErrorCodeEnum.connectorDoesNotBindTheSameComponentMoreThanOnce;
        }

        if (!ok)
            fail("Did not catch connectors connecting more than once the same component");
    }
}
