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

package bip2.ujf.verimag.bip.component.atom.util;

import bip2.ujf.verimag.bip.component.atom.*;

import bip2.ujf.verimag.bip.data.util.DataValidator;
import bip2.ujf.verimag.bip.port.util.PortValidator;
import bip2.ujf.verimag.bip.types.PortType;

import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import org.eclipse.emf.common.util.Diagnostic;
import org.eclipse.emf.common.util.DiagnosticChain;
import org.eclipse.emf.common.util.ResourceLocator;

import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;

import org.eclipse.emf.ecore.util.EObjectValidator;

import ujf.verimag.bip.error.message.ErrorCodeEnum;

/**
 * <!-- begin-user-doc -->
 * The <b>Validator</b> for the model.
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.component.atom.AtomPackage
 * @generated
 */
public class AtomValidator extends EObjectValidator {
    /**
     * The cached model package
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static final AtomValidator INSTANCE = new AtomValidator();

    /**
     * A constant for the {@link org.eclipse.emf.common.util.Diagnostic#getSource() source} of diagnostic {@link org.eclipse.emf.common.util.Diagnostic#getCode() codes} from this package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.eclipse.emf.common.util.Diagnostic#getSource()
     * @see org.eclipse.emf.common.util.Diagnostic#getCode()
     * @generated
     */
    public static final String DIAGNOSTIC_SOURCE = "bip2.ujf.verimag.bip.component.atom";

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
     * The cached base package validator.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected DataValidator dataValidator;

    /**
     * Creates an instance of the switch.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomValidator() {
        super();
        portValidator = PortValidator.INSTANCE;
        dataValidator = DataValidator.INSTANCE;
    }

    /**
     * Returns the package of this validator switch.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EPackage getEPackage() {
        return AtomPackage.eINSTANCE;
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
        case AtomPackage.ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION:
            return validateAtomInternalExternalPortDeclaration(
                    (AtomInternalExternalPortDeclaration) value, diagnostics,
                    context);
        case AtomPackage.ATOM_INTERNAL_PORT_DECLARATION:
            return validateAtomInternalPortDeclaration(
                    (AtomInternalPortDeclaration) value, diagnostics, context);
        case AtomPackage.ATOM_EXTERNAL_PORT_DECLARATION:
            return validateAtomExternalPortDeclaration(
                    (AtomExternalPortDeclaration) value, diagnostics, context);
        case AtomPackage.ATOM_INTERNAL_DATA_DECLARATION:
            return validateAtomInternalDataDeclaration(
                    (AtomInternalDataDeclaration) value, diagnostics, context);
        case AtomPackage.ATOM_EXPORT_PORT_DECLARATION:
            return validateAtomExportPortDeclaration(
                    (AtomExportPortDeclaration) value, diagnostics, context);
        case AtomPackage.EVENT_CONSUMPTION_POLICY:
            return validateEventConsumptionPolicy(
                    (EventConsumptionPolicy) value, diagnostics, context);
        default:
            return true;
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateAtomInternalExternalPortDeclaration(
            AtomInternalExternalPortDeclaration atomInternalExternalPortDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment(
                (EObject) atomInternalExternalPortDeclaration, diagnostics,
                context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) atomInternalExternalPortDeclaration, diagnostics,
                context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) atomInternalExternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) atomInternalExternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) atomInternalExternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) atomInternalExternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_UniqueID(
                    (EObject) atomInternalExternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) atomInternalExternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) atomInternalExternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= portValidator
                    .validatePortDeclaration_hasCorrectNumberOfDataParameters(
                            atomInternalExternalPortDeclaration, diagnostics,
                            context);
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateAtomInternalPortDeclaration(
            AtomInternalPortDeclaration atomInternalPortDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment(
                (EObject) atomInternalPortDeclaration, diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) atomInternalPortDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) atomInternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) atomInternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) atomInternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) atomInternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) atomInternalPortDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) atomInternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) atomInternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= portValidator
                    .validatePortDeclaration_hasCorrectNumberOfDataParameters(
                            atomInternalPortDeclaration, diagnostics, context);
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateAtomExternalPortDeclaration(
            AtomExternalPortDeclaration atomExternalPortDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment(
                (EObject) atomExternalPortDeclaration, diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) atomExternalPortDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) atomExternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) atomExternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) atomExternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) atomExternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) atomExternalPortDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) atomExternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) atomExternalPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= portValidator
                    .validatePortDeclaration_hasCorrectNumberOfDataParameters(
                            atomExternalPortDeclaration, diagnostics, context);
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateAtomInternalDataDeclaration(
            AtomInternalDataDeclaration atomInternalDataDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment(
                (EObject) atomInternalDataDeclaration, diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) atomInternalDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) atomInternalDataDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) atomInternalDataDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) atomInternalDataDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) atomInternalDataDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) atomInternalDataDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) atomInternalDataDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) atomInternalDataDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= dataValidator
                    .validateExplicitDataDeclaration_hasInitializationIfConst(
                            atomInternalDataDeclaration, diagnostics, context);
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateAtomExportPortDeclaration(
            AtomExportPortDeclaration atomExportPortDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) atomExportPortDeclaration,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) atomExportPortDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) atomExportPortDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) atomExportPortDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) atomExportPortDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) atomExportPortDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) atomExportPortDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) atomExportPortDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) atomExportPortDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= portValidator
                    .validatePortDeclaration_hasCorrectNumberOfDataParameters(
                            atomExportPortDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateAtomExportPortDeclaration_referencedPortsHaveTheSameType(
                    atomExportPortDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateAtomExportPortDeclaration_noDuplicatedPortReference(
                    atomExportPortDeclaration, diagnostics, context);
        return result;
    }

    /**
     * Validates the referencedPortsHaveTheSameType constraint of '<em>Export Port Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateAtomExportPortDeclaration_referencedPortsHaveTheSameType(
            AtomExportPortDeclaration atomExportPortDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = true;
        PortType pt = atomExportPortDeclaration.getPortDeclarationReferences()
                .get(0).getPortType();

        for (AtomInternalPortDeclaration aipd : atomExportPortDeclaration
                .getPortDeclarationReferences()) {
            // here, we use a '==' as each port type should have a unique PortType object.
            // if this assumption changes, this check will break.
            if (aipd.getPortType() != pt) {
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
                                getObjectLabel(atomExportPortDeclaration,
                                        context) },
                        new Object[] { atomExportPortDeclaration,
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
    public boolean validateAtomExportPortDeclaration_noDuplicatedPortReference(
            AtomExportPortDeclaration atomExportPortDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = true;
        Set<AtomInternalPortDeclaration> s = new HashSet<AtomInternalPortDeclaration>(
                atomExportPortDeclaration.getPortDeclarationReferences());
        ok = s.size() == atomExportPortDeclaration
                .getPortDeclarationReferences().size();

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "noDuplicatedPortReference",
                                getObjectLabel(atomExportPortDeclaration,
                                        context) },
                        new Object[] { atomExportPortDeclaration,
                                ErrorCodeEnum.noDuplicatedPortReference },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateEventConsumptionPolicy(
            EventConsumptionPolicy eventConsumptionPolicy,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
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

} //AtomValidator
