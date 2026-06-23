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

package bip2.ujf.verimag.bip.component.compound.util;

import bip2.ujf.verimag.bip.component.atom.AtomInternalPortDeclaration;
import bip2.ujf.verimag.bip.component.compound.*;

import bip2.ujf.verimag.bip.port.PortDeclaration;
import bip2.ujf.verimag.bip.port.SubPortDeclarationReference;
import bip2.ujf.verimag.bip.port.util.PortValidator;
import bip2.ujf.verimag.bip.types.CompoundType;
import bip2.ujf.verimag.bip.types.PortType;

import java.util.HashSet;
import java.util.Map;

import org.eclipse.emf.common.util.Diagnostic;
import org.eclipse.emf.common.util.DiagnosticChain;
import org.eclipse.emf.common.util.ResourceLocator;

import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;

import org.eclipse.emf.ecore.util.EObjectValidator;
import org.eclipse.emf.ecore.util.EcoreUtil;

import ujf.verimag.bip.error.message.ErrorCodeEnum;

/**
 * <!-- begin-user-doc -->
 * The <b>Validator</b> for the model.
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.component.compound.CompoundPackage
 * @generated
 */
public class CompoundValidator extends EObjectValidator {
    /**
     * The cached model package
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static final CompoundValidator INSTANCE = new CompoundValidator();

    /**
     * A constant for the {@link org.eclipse.emf.common.util.Diagnostic#getSource() source} of diagnostic {@link org.eclipse.emf.common.util.Diagnostic#getCode() codes} from this package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.eclipse.emf.common.util.Diagnostic#getSource()
     * @see org.eclipse.emf.common.util.Diagnostic#getCode()
     * @generated
     */
    public static final String DIAGNOSTIC_SOURCE = "bip2.ujf.verimag.bip.component.compound";

    /**
     * A constant with a fixed name that can be used as the base value for additional hand written constants.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private static final int GENERATED_DIAGNOSTIC_CODE_COUNT = 0;

    /**
     * A constant with a fixed name that can be used as the base value for additional hand written constants in a derived class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected static final int DIAGNOSTIC_CODE_COUNT = GENERATED_DIAGNOSTIC_CODE_COUNT;

    /**
     * The cached base package validator.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected PortValidator portValidator;

    /**
     * Creates an instance of the switch.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public CompoundValidator() {
        super();
        portValidator = PortValidator.INSTANCE;
    }

    /**
     * Returns the package of this validator switch.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EPackage getEPackage() {
        return CompoundPackage.eINSTANCE;
    }

    /**
     * Calls <code>validateXXX</code> for the corresponding classifier of the model.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected boolean validate(int classifierID, Object value,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        switch (classifierID) {
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION:
            return validateCompoundExportPortDeclaration(
                    (CompoundExportPortDeclaration) value, diagnostics,
                    context);
        case CompoundPackage.COMPOUND_EXPORT_DATA_DECLARATION:
            return validateCompoundExportDataDeclaration(
                    (CompoundExportDataDeclaration) value, diagnostics,
                    context);
        default:
            return true;
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateCompoundExportPortDeclaration(
            CompoundExportPortDeclaration compoundExportPortDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment(
                (EObject) compoundExportPortDeclaration, diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) compoundExportPortDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) compoundExportPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) compoundExportPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) compoundExportPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) compoundExportPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) compoundExportPortDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) compoundExportPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) compoundExportPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= portValidator
                    .validatePortDeclaration_hasCorrectNumberOfDataParameters(
                            compoundExportPortDeclaration, diagnostics,
                            context);
        if (result || diagnostics != null)
            result &= validateCompoundExportPortDeclaration_referencedPortsHaveTheSameType(
                    compoundExportPortDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateCompoundExportPortDeclaration_noDuplicatedPortReference(
                    compoundExportPortDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateCompoundExportPortDeclaration_noDuplicatedExport(
                    compoundExportPortDeclaration, diagnostics, context);
        return result;
    }

    /**
     * Validates the referencedPortsHaveTheSameType constraint of '<em>Export Port Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateCompoundExportPortDeclaration_referencedPortsHaveTheSameType(
            CompoundExportPortDeclaration compoundExportPortDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        PortType pt = compoundExportPortDeclaration
                .getPortDeclarationReferences().get(0)
                .getForwardPortDeclaration().getPortType();
        boolean ok = true;

        for (SubPortDeclarationReference spdr : compoundExportPortDeclaration
                .getPortDeclarationReferences()) {
            // here, we use a '==' as each port type should have a unique PortType object.
            // if this assumption changes, this check will break.
            if (spdr.getForwardPortDeclaration().getPortType() != pt) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "referencedPortsHaveTheSameType",
                                getObjectLabel(compoundExportPortDeclaration,
                                        context) },
                        new Object[] { compoundExportPortDeclaration,
                                ErrorCodeEnum.referencedPortsHaveTheSameType },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the noDuplicatedPortReference constraint of '<em>Export Port Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateCompoundExportPortDeclaration_noDuplicatedPortReference(
            CompoundExportPortDeclaration compoundExportPortDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = true;

        for (SubPortDeclarationReference spdr : compoundExportPortDeclaration
                .getPortDeclarationReferences()) {
            int c = 0;
            for (SubPortDeclarationReference spdr2 : compoundExportPortDeclaration
                    .getPortDeclarationReferences()) {
                if (EcoreUtil.equals(spdr, spdr2)) {
                    c++;
                }
            }
            if (c != 1) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "noDuplicatedPortReference",
                                getObjectLabel(compoundExportPortDeclaration,
                                        context) },
                        new Object[] { compoundExportPortDeclaration,
                                ErrorCodeEnum.noDuplicatedPortReference },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the noDuplicatedExport constraint of '<em>Export Port Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateCompoundExportPortDeclaration_noDuplicatedExport(
            CompoundExportPortDeclaration compoundExportPortDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = true;
        
        // check all port references
        for (SubPortDeclarationReference portRef :
            compoundExportPortDeclaration.getPortDeclarationReferences()) {
            
            assert(compoundExportPortDeclaration.eContainer() instanceof CompoundType);
            
            CompoundType compound =
                    (CompoundType) compoundExportPortDeclaration.eContainer();
            
            // check if the port reference has been already exported
            for (CompoundExportPortDeclaration exportPort :
                compound.getExportPortDeclarations()) {
                if (exportPort != compoundExportPortDeclaration) {
                    for (SubPortDeclarationReference alreadyPortRef :
                        exportPort.getPortDeclarationReferences()) {
                        if (EcoreUtil.equals(portRef, alreadyPortRef)) {
                            if (diagnostics != null) {
                                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                                        DIAGNOSTIC_SOURCE, 0,
                                        "_UI_GenericConstraint_diagnostic",
                                        new Object[] { "noDuplicatedPortReference",
                                                getObjectLabel(compoundExportPortDeclaration,
                                                        context) },
                                        new Object[] { compoundExportPortDeclaration,
                                                ErrorCodeEnum.noDuplicatedExport },
                                        context));
                            }
                            
                            ok = false;
                        }
                    }
                }
            }
        }
        
        return ok;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateCompoundExportDataDeclaration(
            CompoundExportDataDeclaration compoundExportDataDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment(
                (EObject) compoundExportDataDeclaration, diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) compoundExportDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) compoundExportDataDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) compoundExportDataDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) compoundExportDataDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) compoundExportDataDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) compoundExportDataDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) compoundExportDataDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) compoundExportDataDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validateCompoundExportDataDeclaration_sameDataTypeAsPointedDeclaration(
                    compoundExportDataDeclaration, diagnostics, context);
        return result;
    }

    /**
     * Validates the sameDataTypeAsPointedDeclaration constraint of '<em>Export Data Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateCompoundExportDataDeclaration_sameDataTypeAsPointedDeclaration(
            CompoundExportDataDeclaration compoundExportDataDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {

        if (compoundExportDataDeclaration
                .getDataType() != compoundExportDataDeclaration
                        .getDataDeclarationReference()
                        .getForwardDataDeclaration().getDataType()) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "sameDataTypeAsPointedDeclaration",
                                getObjectLabel(compoundExportDataDeclaration,
                                        context) },
                        new Object[] { compoundExportDataDeclaration,
                                ErrorCodeEnum.sameDataTypeAsPointedDeclaration },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Returns the resource locator that will be used to fetch messages for this validator's diagnostics.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public ResourceLocator getResourceLocator() {
        // TODO
        // Specialize this to return a resource locator for messages specific to this validator.
        // Ensure that you remove @generated or mark it @generated NOT
        return super.getResourceLocator();
    }

} //CompoundValidator
