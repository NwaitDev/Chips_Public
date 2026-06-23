/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
 *  Anakreontas Mentis
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

import static org.junit.Assert.fail;

import org.junit.Before;
import org.junit.Test;

import ujf.verimag.bip.error.message.ErrorCodeEnum;
import ujf.verimag.bip.parser.loader.LoadPackageException;

public class PackageLoaderModelValidationTests extends
        AbstractPackageLoaderTests {

    String rootDirectory = "src/tests/resources/modelvalidation";

    @Before
    public void setUp() throws Exception {
        setUp(rootDirectory);
    }

    @Test
    public void invalidModificationsOfConstData() throws Exception {
        boolean ok = false;
        try {
            this.pl.getPackage("invalidModificationsOfConstData", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 5) &&
            		e.getErrors()[0].errorcode == ErrorCodeEnum.hasIncorrectConst && e.getErrors()[0].getLine() == 24 &&
            		e.getErrors()[1].errorcode == ErrorCodeEnum.hasIncorrectConst && e.getErrors()[1].getLine() == 26 &&
            		e.getErrors()[2].errorcode == ErrorCodeEnum.hasIncorrectConst && e.getErrors()[2].getLine() == 27 &&
    				e.getErrors()[3].errorcode == ErrorCodeEnum.hasIncorrectConst && e.getErrors()[3].getLine() == 36 &&
    	            e.getErrors()[4].errorcode == ErrorCodeEnum.hasIncorrectConst && e.getErrors()[4].getLine() == 38;
        }

        if (!ok)
            fail("Did not catch invalid assignment of const data");
    }

    @Test
    public void duplicatedPortRefInCompoundMergedPort() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedPortRefInCompoundMergedPort", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.noDuplicatedPortReference;
        }
        if (!ok)
            fail("Did not catch duplicated port ref in compound merged export port");
    }

    @Test
    public void duplicatedPortRefInConnectorDefine() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedPortRefInConnectorDefine", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.invalidConnectorDefine;
        }
        if (!ok)
            fail("Did not catch duplicated port ref in connector define");
    }

    @Test
    public void duplicatedPortRefInConnectorAction() {
        boolean ok = false;
        try {
            this.pl.getPackage("duplicatedPortRefInConnectorAction", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.noDuplicatedPortReference;
        }
        if (!ok)
            fail("Did not catch duplicated port ref in connector action");
    }

    @Test
    public void badTypeInCompoundMergedPort() {
        boolean ok = false;
        try {
            this.pl.getPackage("badTypeInCompoundMergedPort", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.referencedPortsHaveTheSameType;
        }
        if (!ok)
            fail("Did not catch that exported ports do not have the same type");
    }

    @Test
    public void invalidConnectorActionMissingBody() {
        boolean ok = false;
        try {
            this.pl.getPackage("invalidConnectorActionMissingBody", true);
            ok = (this.pl.getErrors().size() == 1)
                    && this.pl.getErrors().get(0).errorcode == ErrorCodeEnum.connectorActionNotEmpty;
        } catch (LoadPackageException e) {
            ok = false;
        }
        if (!ok)
            fail("Did not catch bogus connector action missing a body");
    }

    @Test
    public void invalidConnectorActionMissingBodyForUpDown() {
        boolean ok = false;
        try {
            this.pl.getPackage("invalidConnectorActionMissingBodyForUpDown",
                    true);
            ok = (this.pl.getErrors().size() == 1)
                    && this.pl.getErrors().get(0).errorcode == ErrorCodeEnum.connectorActionNotEmpty;
        } catch (LoadPackageException e) {
            ok = false;
        }
        if (!ok)
            fail("Did not catch bogus connector action missing a body for up/down");
    }

    // These are commented out as they are "hard" to test. It is not possible to
    // write a BIP file that will trigger an error with these constraints
    // @Test
    // public void InternalDataSynchronizedWithExportedData () {
    // }
    //
    //
    // @Test
    // public void exportedPortsListsSynchronized () {
    // }
    //
    // @Test
    // public void exportedDataListsSynchronized () {
    // }
    //
    // @Test
    // public void hasOneDeclaration () {
    // }

    // @Test
    // public void hasCorrectNumberOfDataParameters () {
    // }
    //
    // @Test
    // public void subPortDeclarationReferenceHasOneDeclaration () {
    // }
    //
    // @Test
    // public void hasCorrectNumberOfPortParameters () {
    // fail("not yet");
    // }
    //
    // @Test
    // public void onPortInConnectorParameters () {
    // fail("not yet");
    // }
    //
    // @Test
    // public void componentDeclarationHasCorrectNumberOfParam () {
    // fail("not yet");
    // }
    // @Test
    // public void dataTypeIsBasic () {
    // boolean ok = false;
    // try {
    // this.pl.getPackage("dataTypeIsBasic", true);
    // } catch (LoadPackageException e) {
    // ok = (e.getErrors().length == 2) && e.getErrors()[0].errorcode ==
    // ErrorCodeEnum.dataTypeIsBasic &&
    // e.getErrors()[1].errorcode == ErrorCodeEnum.dataTypeIsBasic;
    // }
    // if (!ok)
    // fail("Did not catch not basic type in component type parameters");
    // }

    // @Test
    // public void AtomExportPortDeclaration_referencedPortsHaveTheSameType () {
    // fail("not yet");
    // }
    //
    // @Test
    // public void AtomExportPortDeclaration_noDuplicatedPortReference () {
    // fail("not yet");
    // }
    //
    // @Test
    // public void sameDataTypeAsPointedDeclaration () {
    // fail("not yet");
    // }
    //
    // @Test
    // public void dataIsExportedInComponent () {
    // fail("not yet");
    // // }
    //
    // @Test
    // public void hasOneLHS () {
    // fail("not yet");
    // }
    // @Test
    // public void instanceHasCorrectNumberOfParams () {
    // fail("not yet");
    // }

    @Test
    public void interactionDefinedIfExportPortWithData() throws LoadPackageException {
        boolean ok = false;
        this.pl.getPackage("interactionDefinedIfExportPortWithData", true);
        ok = (pl.getErrors().size() == 1)
                    && pl.getErrors().get(0).errorcode == ErrorCodeEnum.interactionDefinedIfExportPortWithData;
        if (!ok)
            fail("Did not catch missing interaction when export port in connector has data");
    }

    @Test
    public void noDuplicatedInteractionAction() {
        boolean ok = false;
        try {
            this.pl.getPackage("noDuplicatedInteractionAction", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 2)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.noDuplicatedInteractionAction
                    && e.getErrors()[1].errorcode == ErrorCodeEnum.noDuplicatedInteractionAction;
        }
        if (!ok)
            fail("Did not catch missing interaction when export port in connector has data");
    }

    @Test
    public void hasCorrectTypeForDataParameters() {
        boolean ok = false;
        try {
            this.pl.getPackage("hasCorrectTypeForDataParameters", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.hasIncorrectType;
        }
        if (!ok)
            fail("Did not catch bad data type in port declaration");
    }
    
    @Test
    public void compoundPriorityDuplicateMaximalProgress() {
        boolean ok = true;
        try {
            this.pl.getPackage("compoundPriorityDuplicateMaximalProgress", true);
        } catch (LoadPackageException e) {
        	ok = false;
        }
        
        if (!ok) {
            fail("Found an unexpected error instead of warnings for priorities duplicating maximal progress");
        }
        else {
        	ok = ok && (pl.getErrors().size() == 6)
        			&& pl.getErrors().get(0).errorcode == ErrorCodeEnum.priorityDuplicateMaximalProgress
        			&& pl.getErrors().get(1).errorcode == ErrorCodeEnum.priorityDuplicateMaximalProgress
        			&& pl.getErrors().get(2).errorcode == ErrorCodeEnum.priorityDuplicateMaximalProgress
        			&& pl.getErrors().get(3).errorcode == ErrorCodeEnum.priorityDuplicateMaximalProgress
        			&& pl.getErrors().get(4).errorcode == ErrorCodeEnum.priorityDuplicateMaximalProgress
        			&& pl.getErrors().get(5).errorcode == ErrorCodeEnum.priorityDuplicateMaximalProgress;
        
        	if (!ok)
        		fail("Did not catch priorities duplicating maximal progress");
        }
    }
    
    @Test
    public void compoundPriorityContradictMaximalProgress() {
        boolean ok = false;
        try {
            this.pl.getPackage("compoundPriorityContradictMaximalProgress", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 6)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.priorityContradictMaximalProgress
                    && e.getErrors()[1].errorcode == ErrorCodeEnum.priorityContradictMaximalProgress
                    && e.getErrors()[2].errorcode == ErrorCodeEnum.priorityContradictMaximalProgress
                    && e.getErrors()[3].errorcode == ErrorCodeEnum.priorityContradictMaximalProgress
                    && e.getErrors()[4].errorcode == ErrorCodeEnum.priorityContradictMaximalProgress
                    && e.getErrors()[5].errorcode == ErrorCodeEnum.priorityContradictMaximalProgress;
        }
        if (!ok)
            fail("Did not catch priorities contradicting maximal progress");
    }

    @Test
    public void compoundPriorityHasAtMostOneWildcard() {
        boolean ok = false;
        try {
            this.pl.getPackage("compoundPriorityHasAtMostOneWildcard", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 2)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.compoundPriorityHasAtMostOneWildcard
                    && e.getErrors()[1].errorcode == ErrorCodeEnum.compoundPriorityHasAtMostOneWildcard;
        }
        if (!ok)
            fail("Did not catch priority of the form '* < *' in compound type");
    }
    
    @Test
    public void compoundPriorityInvolvesTopLevelConnectors() {
        boolean ok = false;
        try {
            this.pl.getPackage("compoundPriorityInvolvesTopLevelConnectors", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 2)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.compoundPriorityInvolvesOnlyTopLevelConnectors
                    && e.getErrors()[1].errorcode == ErrorCodeEnum.compoundPriorityInvolvesOnlyTopLevelConnectors;
        }
        if (!ok)
            fail("Did not catch priority between non top level connectors in compound type");
    }
    
    @Test
    public void compoundPriorityInvolvesTopLevelConnectors2() {
        boolean ok = false;
        try {
            this.pl.getPackage("compoundPriorityInvolvesTopLevelConnectors2", true);
        } catch (LoadPackageException e) {
            int prioritiesOnlyTopLevelConnectorsErrors = 0;
            
            for (int i = 0 ; i < e.getErrors().length ; i++) {
                if (e.getErrors()[i].errorcode == ErrorCodeEnum.compoundPriorityInvolvesOnlyTopLevelConnectors) {
                    prioritiesOnlyTopLevelConnectorsErrors++;
                }
                else if (e.getErrors()[i].errorcode != ErrorCodeEnum.variableModifiedBetweenUpAndDown) {
                    continue;
                }
            }
        
            ok = (prioritiesOnlyTopLevelConnectorsErrors == 3);
        }
        if (!ok)
            fail("Did not catch priority between non top level connectors in compound type");
    }

    @Test
    public void portReferencesOnCorrectConnectorDeclaration() {
        boolean ok = false;
        try {
            this.pl.getPackage("portReferencesOnCorrectConnectorDeclaration",
                    true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 2)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.portReferencesOnCorrectConnectorDeclaration
                    && e.getErrors()[1].errorcode == ErrorCodeEnum.portReferencesOnCorrectConnectorDeclaration;
        }
        if (!ok)
            fail("Did not catch bogus port references (port not on correct connector) in compound priority");
    }

    @Test
    public void noDuplicatedPortReferenceInConnectorInteraction() {
        boolean ok = false;
        try {
            this.pl.getPackage(
                    "noDuplicatedPortReferenceInConnectorInteraction", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 2)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.noDuplicatedPortReferenceInConnectorInteraction
                    && e.getErrors()[1].errorcode == ErrorCodeEnum.noDuplicatedPortReferenceInConnectorInteraction;
        }
        if (!ok)
            fail("Did not catch duplicated port references in compound priority");
    }

    @Test
    public void atomPriorityHasAtMostOneWildcard() {
        boolean ok = false;
        try {
            this.pl.getPackage("atomPriorityHasAtMostOneWildcard", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.atomPriorityHasAtMostOneWildcard;
        }
        if (!ok)
            fail("Did not catch bogus priority of the form '* < *' in atom");
    }

    @Test
    public void portParameterHasCorrectPortType() {
        boolean ok = false;
        try {
            this.pl.getPackage("portParameterHasCorrectPortType", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.portParameterHasCorrectPortType;
        }
        if (!ok)
            fail("Did not catch bad port type for a port parameter");
    }

    @Test
    public void upDoesNotContainExternalSubDataRefOnLHSAssignements() {
        boolean ok = false;
        try {
            this.pl.getPackage(
                    "upDoesNotContainExternalSubDataRefOnLHSAssignements", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.upDoesNotContainExternalSubDataRefOnLHSAssignments;
        }
        if (!ok)
            fail("Did not catch bad assignment in 'up' in connector");
    }

    @Test
    public void connectorActionNotEmpty() {
        boolean ok = false;
        try {
            this.pl.getPackage("connectorActionNotEmpty", true);
            ok = (this.pl.getErrors().size() == 3)
                    && this.pl.getErrors().get(0).errorcode == ErrorCodeEnum.connectorActionNotEmpty
                    && this.pl.getErrors().get(1).errorcode == ErrorCodeEnum.connectorActionNotEmpty
                    && this.pl.getErrors().get(2).errorcode == ErrorCodeEnum.connectorActionNotEmpty;
        } catch (LoadPackageException e) {
            ok = false;
        }
        if (!ok)
            fail("Did not catch empty action in connector");
    }

    @Test
    public void noUpIfNoExportedPort() {
        boolean ok = false;
        try {
            this.pl.getPackage("noUpIfNoExportedPort", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.noUpIfNoExportedPort;
        }
        if (!ok)
            fail("Did not catch extra 'up' in connector with no exported port");
    }

    @Test
    public void missingUpForExportedPort() {
        boolean ok = false;
        try {
            this.pl.getPackage("missingUpForExportedPort", true);
            ok =  (this.pl.getErrors().size() == 2) && 
                    this.pl.getErrors().get(0).errorcode == ErrorCodeEnum.missingUpForExportedPort &&
                    this.pl.getErrors().get(1).errorcode == ErrorCodeEnum.uninitializedVariableExportedByPortOfConnector;
        } catch (LoadPackageException e) {
           ok = false;
        }
        
        if (!ok)
            fail("Did not catch missing'up' in connector with exported port+data");
    }
    
    @Test
    public void triggerPortsValidWrtDefine() {
        boolean ok = false;
        try {
            this.pl.getPackage("triggerPortsValidWrtDefine", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 2)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.triggerPortsValidWrtDefine
                    && e.getErrors()[1].errorcode == ErrorCodeEnum.triggerPortsValidWrtDefine;
        }
        if (!ok)
            fail("Did not catch invalid trigger port wrt define in connector");
    }

    @Test
    public void dataRefInConnectorActionToInvolvedPort() {
        boolean ok = false;
        try {
            this.pl.getPackage("dataRefInConnectorActionToInvolvedPort", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 2)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.dataRefInConnectorActionToInvolvedPort
                    && e.getErrors()[1].errorcode == ErrorCodeEnum.dataRefInConnectorActionToInvolvedPort;
        }
        if (!ok)
            fail("Did not catch invalid use of uninvolved port in connector action");
    }

    @Test
    public void CompoundExportPortDeclaration_referencedPortsHaveTheSameType() {
        boolean ok = false;
        try {
            this.pl.getPackage(
                    "CompoundExportPortDeclaration_referencedPortsHaveTheSameType",
                    true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.referencedPortsHaveTheSameType;
        }
        if (!ok)
            fail("Did not catch not matching type in exported port in compound");
    }

    @Test
    public void CompoundExportPortDeclaration_noDuplicatedPortReference() {
        boolean ok = false;
        try {
            this.pl.getPackage(
                    "CompoundExportPortDeclaration_noDuplicatedPortReference",
                    true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 1)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.noDuplicatedPortReference;
        }
        if (!ok)
            fail("Did not catch duplicate reference in exported port in compound");
    }

    @Test
    public void noRefToLocalDataInConnectorGuard() {
        boolean ok = false;
        try {
            this.pl.getPackage("noRefToLocalDataInConnectorGuard", true);
        } catch (LoadPackageException e) {
        	// nothing to do since it is a warning in this test case
        }
        
        ok = (this.pl.getErrors().size() == 1)
        		&& this.pl.getErrors().get(0).errorcode == ErrorCodeEnum.uninitializedVariableOfConnectorInteractionAction;
        
        if (!ok)
            fail("Did not catch use of local data in connector guard");
    }

    @Test
    public void checkDuplicatedTriggerPortFromSameState() {
        boolean ok = false;
        try {
            this.pl.getPackage("checkDuplicatedTriggerPortFromSameState", true);
        } catch (LoadPackageException e) {
            ok = (e.getErrors().length == 7)
                    && e.getErrors()[0].errorcode == ErrorCodeEnum.checkDuplicatedTriggerPortFromSameState && e.getErrors()[0].getLine() == 11 &&
                       e.getErrors()[1].errorcode == ErrorCodeEnum.checkDuplicatedTriggerPortFromSameState && e.getErrors()[1].getLine() == 21 &&
                       e.getErrors()[2].errorcode == ErrorCodeEnum.checkDuplicatedTriggerPortFromSameState && e.getErrors()[2].getLine() == 31 &&
                       e.getErrors()[3].errorcode == ErrorCodeEnum.checkDuplicatedTriggerPortFromSameState && e.getErrors()[3].getLine() == 43 &&
                       e.getErrors()[4].errorcode == ErrorCodeEnum.deadCode && e.getErrors()[4].getLine() == 52 &&
                       e.getErrors()[5].errorcode == ErrorCodeEnum.deadCode && e.getErrors()[5].getLine() == 53 &&
                       e.getErrors()[6].errorcode == ErrorCodeEnum.checkDuplicatedTriggerPortFromSameState && e.getErrors()[6].getLine() == 64;
        }
        if (!ok)
            fail("Did not catch non determinism in petrinet (2 or more transition triggered by same port from same state).");
    }
    
    @Test
    public void checkDownWhenNoDataInConnectorPort() {
        boolean ok = false;
        try {
            this.pl.getPackage("checkDownWhenNoDataInConnectorPort", true);
        } catch (LoadPackageException e) {
            fail("Package loader raised an unexpected exception");
        }

        ok = (pl.getErrors().size() == 4)
                && pl.getErrors().get(0).errorcode == ErrorCodeEnum.checkDownWhenNoDataInConnectorPort && pl.getErrors().get(0).getLine() == 10 &&
                pl.getErrors().get(1).errorcode == ErrorCodeEnum.checkDownWhenNoDataInConnectorPort && pl.getErrors().get(1).getLine() == 29 &&
                pl.getErrors().get(2).errorcode == ErrorCodeEnum.checkDownWhenNoDataInConnectorPort && pl.getErrors().get(2).getLine() == 30 &&
                pl.getErrors().get(3).errorcode == ErrorCodeEnum.checkDownWhenNoDataInConnectorPort && pl.getErrors().get(3).getLine() == 31;

        if (!ok)
            fail("Did not catch 'down' on connector connecting port without data.");
    }
    
    @Test
    public void checkForCyclesInPrioritiesInAtom() {
        boolean ok = false;
        
        try {
            this.pl.getPackage("checkForCyclesInPrioritiesInAtom", true);
        } catch (LoadPackageException e) {
            ok = e.getErrors().length == 6 &&
                    e.getErrors()[0].errorcode == ErrorCodeEnum.checkForCyclesInPrioritiesInAtom && e.getErrors()[0].getLine() == 11 &&
                    e.getErrors()[1].errorcode == ErrorCodeEnum.checkForCyclesInPrioritiesInAtom && e.getErrors()[1].getLine() == 22 &&
                    e.getErrors()[2].errorcode == ErrorCodeEnum.checkForCyclesInPrioritiesInAtom && (e.getErrors()[2].getLine() == 35 || e.getErrors()[2].getLine() == 34) &&
                    e.getErrors()[3].errorcode == ErrorCodeEnum.checkForCyclesInPrioritiesInAtom && (e.getErrors()[3].getLine() == 34 || e.getErrors()[3].getLine() == 35) &&
                    e.getErrors()[4].errorcode == ErrorCodeEnum.checkForCyclesInPrioritiesInAtom && e.getErrors()[4].getLine() == 47 &&
                    e.getErrors()[5].errorcode == ErrorCodeEnum.checkForCyclesInPrioritiesInAtom && e.getErrors()[5].getLine() == 80;

        }

        if (!ok)
            fail("Did not catch cycles in atom priorities");
    }

    @Test
    public void interactionIsDefinedInConnector() {
        boolean ok = false;

        try {
            this.pl.getPackage("interactionIsDefinedInConnector", true);
        } catch (LoadPackageException e) {
            ok = e.getErrors().length == 2 &&
                    e.getErrors()[0].errorcode == ErrorCodeEnum.interactionIsDefinedInConnector && e.getErrors()[0].getLine() == 24 &&
                    e.getErrors()[1].errorcode == ErrorCodeEnum.interactionIsDefinedInConnector && e.getErrors()[1].getLine() == 27 ;
        }

        if (!ok)
            fail("Did not catch priorities with interactions not defined in connector");
    }
    
    @Test
    public void connectorDeclarationHasnoDuplicatedPortReferenceParameter() {
        boolean ok = false;

        try {
            this.pl.getPackage("connectorDeclarationHasnoDuplicatedPortReferenceParameter", true);
        } catch (LoadPackageException e) {
            ok = e.getErrors().length == 1 &&
                    e.getErrors()[0].errorcode == ErrorCodeEnum.connectorDeclarationHasnoDuplicatedPortReferenceParameter && e.getErrors()[0].getLine() == 21;
        }

        if (!ok)
            fail("Did not catch duplicated port ref in connector decl");
    }

    @Test
    public void connectorHasExportPortBound() throws LoadPackageException {
        boolean ok = false;
        this.pl.getPackage("connectorHasExportPortBound", true);
        ok = (pl.getErrors().size() == 1)
                && pl.getErrors().get(0).errorcode == ErrorCodeEnum.connectorHasExportPortBound && pl.getErrors().get(0).getLine() == 28;

        if (!ok)
            fail("Did not catch unbound exported port for a connector declaration");
    }

    @Test
    public void componentDeclarationHasNoUnconnectedPort() throws LoadPackageException {
        boolean ok = false;
        this.pl.getPackage("componentDeclarationHasNoUnconnectedPort", true);
        ok = (pl.getErrors().size() == 1)
                && pl.getErrors().get(0).errorcode == ErrorCodeEnum.componentDeclarationHasNoUnconnectedPort&& pl.getErrors().get(0).getLine() == 17;

        if (!ok)
            fail("Did not catch unbound exported port for a component declaration");
    }

    @Test
    public void missingInteractionIfExportPortWithData() throws LoadPackageException {
        boolean ok = false;
        this.pl.getPackage("missingInteractionIfExportPortWithData", true);
        ok = (pl.getErrors().size() == 1)
                && pl.getErrors().get(0).errorcode == ErrorCodeEnum.missingInteractionIfExportPortWithData && pl.getErrors().get(0).getLine() == 25;

        if (!ok)
            fail("Did not catch missing interaction on connector type with exported data");
    }

    @Test
    public void variableInitialization() {
        boolean ok = false;

        try {
            this.pl.getPackage("variableInitialization", true);
        } catch (LoadPackageException e) {
            ok = e.getErrors().length == 12 && // the last error is a warning!
                    e.getErrors()[0].errorcode == ErrorCodeEnum.uninitializedConstData && e.getErrors()[0].getLine() == 3 &&
                    e.getErrors()[1].errorcode == ErrorCodeEnum.uninitializedConstData && e.getErrors()[1].getLine() == 4 &&
                    e.getErrors()[2].errorcode == ErrorCodeEnum.uninitializedConstData && e.getErrors()[2].getLine() == 5 &&
                    e.getErrors()[3].errorcode == ErrorCodeEnum.uninitializedVariableInAtomInternalDataDeclaration && e.getErrors()[3].getLine() == 11 &&
                    e.getErrors()[4].errorcode == ErrorCodeEnum.uninitializedConstData && e.getErrors()[4].getLine() == 13 &&
                    e.getErrors()[5].errorcode == ErrorCodeEnum.uninitializedConstData && e.getErrors()[5].getLine() == 14 &&
                    e.getErrors()[6].errorcode == ErrorCodeEnum.uninitializedConstData && e.getErrors()[6].getLine() == 15 &&
                    e.getErrors()[7].errorcode == ErrorCodeEnum.uninitializedVariableInConnectorDataDeclaration && e.getErrors()[7].getLine() == 24 &&
                    e.getErrors()[8].errorcode == ErrorCodeEnum.uninitializedConstData && e.getErrors()[8].getLine() == 26 &&
                    e.getErrors()[9].errorcode == ErrorCodeEnum.uninitializedConstData && e.getErrors()[9].getLine() == 27 &&
                    e.getErrors()[10].errorcode == ErrorCodeEnum.uninitializedConstData && e.getErrors()[10].getLine() == 28;

        }
        if (!ok)
            fail("Did not catch correctly incorrect variable initialization");
    }
    
    @Test
    public void typeCheckAssignments() {
        boolean ok = false;

        try {
            this.pl.getPackage("typeCheckAssignments", true);
        } catch (LoadPackageException e) {
            ok = e.getErrors().length == 20;
            
            ok = ok && e.getErrors()[0].errorcode == ErrorCodeEnum.hasIncorrectType && e.getErrors()[0].getLine() == 5;
            
            for (int i = 0 ; i < 19 ; i++) {
              ok = ok && e.getErrors()[i+1].errorcode == ErrorCodeEnum.hasIncorrectType && e.getErrors()[i+1].getLine() == i + 33;
            }
        }
        if (!ok) {
            fail("Did not catch incorrectly typed assignments");
        }
    }    
    
    @Test
    public void typeCheckFunctionCalls() {
        boolean ok = false;

        try {
            this.pl.getPackage("typeCheckFunctionCalls", true);
        } catch (LoadPackageException e) {
            // 4th error is a warning for internal transitions from a single state
            ok = e.getErrors().length == 6 &&
                    e.getErrors()[0].errorcode == ErrorCodeEnum.noMatchBinaryOp && e.getErrors()[0].getLine() == 76 &&
                    e.getErrors()[1].errorcode == ErrorCodeEnum.hasIncorrectType && e.getErrors()[1].getLine() == 79 &&
                    e.getErrors()[2].errorcode == ErrorCodeEnum.matchingFunctionCallWithoutReturnValue && e.getErrors()[2].getLine() == 80 &&
                    e.getErrors()[3].errorcode == ErrorCodeEnum.checkDuplicatedTriggerPortFromSameState && e.getErrors()[3].getLine() == 90 &&
                    e.getErrors()[4].errorcode == ErrorCodeEnum.noMatchFunctionCall && e.getErrors()[4].getLine() == 95 &&
                    e.getErrors()[5].errorcode == ErrorCodeEnum.ambiguousFunctionCall && e.getErrors()[5].getLine() == 103;
            }
        if (!ok) {
            fail("Did not catch incorrectly typed function calls");
        }
    }
     
    @Test
    public void typeCheckGuards() {
        boolean ok = false;

        try {
            this.pl.getPackage("typeCheckGuards", true);
        } catch (LoadPackageException e) {
            // 4th error is a warning for internal transitions from a single state
            ok = e.getErrors().length == 10 &&
                    e.getErrors()[0].errorcode == ErrorCodeEnum.hasIncorrectType && e.getErrors()[0].getLine() == 51 &&
                    e.getErrors()[1].errorcode == ErrorCodeEnum.hasIncorrectType && e.getErrors()[1].getLine() == 52 &&
                    e.getErrors()[2].errorcode == ErrorCodeEnum.hasIncorrectType && e.getErrors()[2].getLine() == 55 &&
                    e.getErrors()[3].errorcode == ErrorCodeEnum.checkDuplicatedTriggerPortFromSameState && e.getErrors()[3].getLine() == 89 &&
                    e.getErrors()[4].errorcode == ErrorCodeEnum.hasIncorrectType && e.getErrors()[4].getLine() == 90 &&
                    e.getErrors()[5].errorcode == ErrorCodeEnum.checkDuplicatedTriggerPortFromSameState && e.getErrors()[5].getLine() == 92 &&
                    e.getErrors()[6].errorcode == ErrorCodeEnum.hasIncorrectType && e.getErrors()[6].getLine() == 93 &&
                    e.getErrors()[7].errorcode == ErrorCodeEnum.hasIncorrectType && e.getErrors()[7].getLine() == 110 &&
                    e.getErrors()[8].errorcode == ErrorCodeEnum.hasIncorrectType && e.getErrors()[8].getLine() == 119 &&
                    e.getErrors()[9].errorcode == ErrorCodeEnum.hasIncorrectType && e.getErrors()[9].getLine() == 120;
            }
        if (!ok) {
            fail("Did not catch incorrectly typed function calls");
        }
    }
    
    @Test
    public void typeCheckConstDataInUsePackage() {
        boolean ok = false;
        try {
            this.pl.getPackage("typeCheckConstDataInUsePackage", true);
            ok = (this.pl.getErrors().size() == 0);
        } catch (LoadPackageException e) {
            ok = false;
        }
        if (!ok)
            fail("Found an error in a correct use of const data in use package");
    }
    
    @Test
    public void typeCheckComponentDeclarations() {
        boolean ok = false;
        try {
            this.pl.getPackage("typeCheckComponentDeclarations", true);
        } catch (LoadPackageException e) {
            ok = e.getErrors().length == 3 &&
            		e.getErrors()[0].errorcode == ErrorCodeEnum.hasIncorrectType && e.getErrors()[0].getLine() == 22 &&
            		e.getErrors()[1].errorcode == ErrorCodeEnum.hasIncorrectType && e.getErrors()[1].getLine() == 23 &&
            		e.getErrors()[2].errorcode == ErrorCodeEnum.hasIncorrectType && e.getErrors()[2].getLine() == 28;
        }
        if (!ok)
            fail("Found an error in a correct use of const data in use package");
    }
    

    @Test
    public void checkComponentParameters() {
        boolean ok = false;
        try {
            this.pl.getPackage("checkComponentParameters", true);
        } catch (LoadPackageException e) {
            ok = e.getErrors().length == 3 &&
            		e.getErrors()[0].errorcode == ErrorCodeEnum.hasIncorrectType && e.getErrors()[0].getLine() == 16 &&
            		e.getErrors()[1].errorcode == ErrorCodeEnum.componentDeclarationHasCorrectNumberOfParam && e.getErrors()[1].getLine() == 17 &&
            		e.getErrors()[2].errorcode == ErrorCodeEnum.componentDeclarationHasCorrectNumberOfParam && e.getErrors()[2].getLine() == 18;
        }
        if (!ok)
            fail("Found an error in a correct use of const data in use package");
    }
}
