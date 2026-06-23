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

import org.antlr.runtime.MismatchedTokenException;
import org.junit.Before;
import org.junit.Test;

import ujf.verimag.bip.error.message.ErrorCodeEnum;
import ujf.verimag.bip.parser.Bip2Parser;
import ujf.verimag.bip.parser.loader.LoadPackageException;



public class PackageLoaderWalkerTests  extends AbstractPackageLoaderTests {

    String rootDirectory = "src/tests/resources/walker";

    @Before
    public void setUp() throws Exception {
        setUp(rootDirectory);
    }

    @Test
    public void invalidConnectorDefine() {
        boolean ok = false;
        try {
            this.pl.getPackage("invalidConnectorDefine", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.invalidConnectorDefine;
        }

        if (!ok)
            fail("Did not catch invalid connector define");
    }

    @Test
    public void invalidConnectorDefineRefToUnknownPort() {
        boolean ok = false;
        try {
            this.pl.getPackage("invalidConnectorDefineRefToUnknownPort", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.UndefinedVariable;
        }

        if (!ok)
            fail("Did not catch invalid connector define");
    }

    @Test
    public void undefinedPortType() {
        boolean ok = false;
        try {
            this.pl.getPackage("undefinedPortType", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.UndefinedType;
        }

        if (!ok)
            fail("Did not catch undefined port type");
    }


    @Test
    public void duplicatedComponentDeclaration() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedComponentDeclaration", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedVariable;
        }

        if (!ok)
            fail("Did not catch duplicated component declaration");
    }


    @Test
    public void duplicatedAtomTypeDefinition() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedAtomTypeDefinition", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedType;
        }

        if (!ok)
            fail("Did not catch duplicated atom type definition");
    }


    @Test
    public void duplicatedCompoundTypeDefinition() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedCompoundTypeDefinition", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedType;
        }

        if (!ok)
            fail("Did not catch duplicated compound type definition");
    }


    @Test
    public void duplicatedPortTypeDefinition() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedPortTypeDefinition", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedType;
        }

        if (!ok)
            fail("Did not catch duplicated port type definition");
    }

    @Test
    public void duplicatedComponentTypeParameter() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedComponentTypeParameter", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedVariable;
        }

        if (!ok)
            fail("Did not catch duplicated component type parameter declaration");
    }

    @Test
    public void duplicatedConnectorDeclaration() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedConnectorDeclaration", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedVariable;
        }

        if (!ok)
            fail("Did not catch duplicated connector declaration");
    }

    @Test
    public void duplicatedConnectorTypeDefinition() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedConnectorTypeDefinition", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedType;
        }

        if (!ok)
            fail("Did not catch duplicated connector type definition");
    }

    @Test
    public void duplicatedDataDeclarationInAtom() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedDataDeclarationInAtom", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedVariable;
        }

        if (!ok)
            fail("Did not catch duplicated data declaration in atom");
    }

    @Test
    public void duplicatedDataParamInPortType() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedDataParamInPortType", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedVariable;
        }

        if (!ok)
            fail("Did not catch duplicated data param in port type");
    }

    @Test
    public void duplicatedExportPortInCompound() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedExportPortInCompound", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedVariable;
        }

        if (!ok)
            fail("Did not catch duplicated export port in compound");
    }
    
    @Test
    public void duplicatedExportPortInAtom1() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedExportPortInAtom1", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedVariable;
        }

        if (!ok)
            fail("Did not catch duplicated export port in atom");
    }
    
    @Test
    public void duplicatedExportPortInAtom2() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedExportPortInAtom2", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedVariable;
        }

        if (!ok)
            fail("Did not catch duplicated export port in atom");
    }
    

    @Test
    public void duplicatedExportDataInCompound() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedExportDataInCompound", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedVariable;
        }

        if (!ok)
            fail("Did not catch duplicated export data in compound");
    }


    @Test
    public void duplicatedPortDeclInAtom() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedPortDeclInAtom", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedVariable;
        }

        if (!ok)
            fail("Did not catch duplicated port decl in atom");
    }

    @Test
    public void duplicatedPortDeclInAtom2() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedPortDeclInAtom2", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedVariable;
        }

        if (!ok)
            fail("Did not catch duplicated port decl in atom");
    }

    @Test
    public void duplicatedPortDeclInAtom3() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedPortDeclInAtom3", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedVariable;
        }

        if (!ok)
            fail("Did not catch duplicated port decl in atom");
    }

    @Test
    public void duplicatedCompoundPriorityDeclaration() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedCompoundPriorityDeclaration", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedVariable;
        }

        if (!ok)
            fail("Did not catch duplicated compound priority decl");
    }

    @Test
    public void redefinedAnnotation() {
        boolean ok = false;
        try {
            this.pl.getPackage("redefinedAnnotation", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedAnnotation;
        }

        if (!ok)
            fail("Did not catch duplicated annotation");
    }

    @Test
    public void redefinedAnnotationParameter() {
        boolean ok = false;
        try {
            this.pl.getPackage("redefinedAnnotationParameter", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedAnnotationParameter;
        }

        if (!ok)
            fail("Did not catch duplicated annotation parameter");
    }

    @Test
    public void transitionOnUndeclaredPort() {
        boolean ok = false;
        try {
            this.pl.getPackage("transitionOnUndeclaredPort", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.UndefinedVariable;
        }

        if (!ok)
            fail("Did not catch transition on undeclared port");
    }
    
    @Test
    public void transitionToUndeclaredState() {
        boolean ok = false;
        try {
            this.pl.getPackage("transitionToUndeclaredState", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.UndefinedVariable;
        }

        if (!ok)
            fail("Did not catch transition to undeclared state");
    }
    
    @Test
    public void transitionFromUndeclaredState() {
        boolean ok = false;
        try {
            this.pl.getPackage("transitionFromUndeclaredState", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.UndefinedVariable;
        }

        if (!ok)
            fail("Did not catch transition from undeclared state");
    }
    
    @Test
    public void undefinedConnectorType() {
        boolean ok = false;
        try {
            this.pl.getPackage("undefinedConnectorType", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.UndefinedType;
        }

        if (!ok)
            fail("Did not catch reference to undefined connector type");
    }

    @Test
    public void undefinedComponentType() {
        boolean ok = false;
        try {
            this.pl.getPackage("undefinedComponentType", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.UndefinedType;
        }

        if (!ok)
            fail("Did not catch reference to undefined component type");
    }

    @Test
    public void duplicatedPlaceDeclaration() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedPlaceDeclaration", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.RedefinedVariable;
        }

        if (!ok)
            fail("Did not catch duplicated place declaration in petrinet");
    }

    @Test
    public void hierarchical_pack_hierarchicalPack() throws Exception {
        this.pl.getPackage("hierarchical.pack.hierarchicalPack", true);
    }
    
    @Test
    public void big_use__creation() throws Exception {
        this.pl.getPackage("big.use_creation", true);
    }

    @Test
    public void ifthenelse() throws Exception {
        this.pl.getPackage("ifthenelse", true);
    }

    @Test
    public void constDataCompDecl() throws Exception {
        this.pl.getPackage("constDataCompDecl", true);
    }

    @Test
    public void constDataTransitions() throws Exception {
        this.pl.getPackage("constDataTransitions", true);
    }

    @Test
    public void constDataAtomPrio() throws Exception {
        this.pl.getPackage("constDataAtomPrio", true);
    }

    @Test
    public void constDataCompoundPrio() throws Exception {
        this.pl.getPackage("constDataCompoundPrio", true);
    }

    @Test
    public void constDataConnector() throws Exception {
        this.pl.getPackage("constDataConnector", true);
    }

    @Test
    public void nestedError() {
        boolean ok = false;

        try {
            this.pl.getPackage("nestedError", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1)
                    && (e.getErrors()[0].isNested() && e.getErrors()[0]
                            .getNestedErrors().length == 1)
                    && (e.getErrors()[0].getNestedErrors()[0].isNested() && e
                            .getErrors()[0].getNestedErrors()[0]
                            .getNestedErrors().length == 2)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.LoadPackage
                    && e.getErrors()[0].getNestedErrors()[0].errorcode == ErrorCodeEnum.LoadPackage
                    && e.getErrors()[0].getNestedErrors()[0].getNestedErrors()[0].errorcode == ErrorCodeEnum.hasCorrectNumberOfDataParameters
                    && e.getErrors()[0].getNestedErrors()[0].getNestedErrors()[1].errorcode == ErrorCodeEnum.checkDuplicatedTriggerPortFromSameState;
        }

        if (!ok)
            fail("Did not handle correctly nested errors.");
    }
    
    @Test
    public void atomPriorityInvolvingUndeclaredPort1() {
        boolean ok = false;
        try {
            this.pl.getPackage("atomPriorityInvolvingUndeclaredPort1", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.UndefinedVariable;
        }

        if (!ok)
            fail("Did not catch priority involving undeclared port");
    }
    
    @Test
    public void atomPriorityInvolvingUndeclaredPort2() {
        boolean ok = false;
        try {
            this.pl.getPackage("atomPriorityInvolvingUndeclaredPort2", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.UndefinedVariable;
        }

        if (!ok)
            fail("Did not catch priority involving undeclared port");
    }
    
    @Test
    public void exportOfAtomParameters() throws Exception {
        boolean ok = false;
        try {
            this.pl.getPackage("exportOfAtomParameters", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.IncorrectBipType && e.getErrors()[0].getLine() == 8;
        }

        if (!ok)
            fail("Did not catch incorrect export of atom parameters through a port");
    	
    }
        
    @Test
    public void exportOfConstData() throws Exception {
        boolean ok = false;
        try {
            this.pl.getPackage("exportOfConstData", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.IncorrectBipType && e.getErrors()[0].getLine() == 8;
        }

        if (!ok)
            fail("Did not catch incorrect export of const data through a port");
    	
    }

    
    @Test
    public void exportOfConstData2() throws Exception {
        boolean ok = false;
        try {
            this.pl.getPackage("exportOfConstData2", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1) && e.getErrors()[0].errorcode == ErrorCodeEnum.IncorrectBipType && e.getErrors()[0].getLine() == 9;
        }

        if (!ok)
            fail("Did not catch incorrect export of const data through a port");
    	
    }
}