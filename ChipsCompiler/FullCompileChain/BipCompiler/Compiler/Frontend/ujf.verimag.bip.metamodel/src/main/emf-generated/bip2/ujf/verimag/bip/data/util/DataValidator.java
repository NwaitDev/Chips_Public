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

package bip2.ujf.verimag.bip.data.util;

import bip2.ujf.verimag.bip.data.*;

import java.util.Map;

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
 * @see bip2.ujf.verimag.bip.data.DataPackage
 * @generated
 */
public class DataValidator extends EObjectValidator {
    /**
     * The cached model package
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static final DataValidator INSTANCE = new DataValidator();

    /**
     * A constant for the {@link org.eclipse.emf.common.util.Diagnostic#getSource() source} of diagnostic {@link org.eclipse.emf.common.util.Diagnostic#getCode() codes} from this package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.eclipse.emf.common.util.Diagnostic#getSource()
     * @see org.eclipse.emf.common.util.Diagnostic#getCode()
     * @generated
     */
    public static final String DIAGNOSTIC_SOURCE = "bip2.ujf.verimag.bip.data";

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
     * Creates an instance of the switch.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataValidator() {
        super();
    }

    /**
     * Returns the package of this validator switch.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EPackage getEPackage() {
        return DataPackage.eINSTANCE;
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
        case DataPackage.DATA_TYPE:
            return validateDataType((DataType) value, diagnostics, context);
        case DataPackage.DATA_DECLARATION:
            return validateDataDeclaration((DataDeclaration) value, diagnostics,
                    context);
        case DataPackage.EXPLICIT_DATA_DECLARATION:
            return validateExplicitDataDeclaration(
                    (ExplicitDataDeclaration) value, diagnostics, context);
        case DataPackage.SUB_DATA_DECLARATION_REFERENCE:
            return validateSubDataDeclarationReference(
                    (SubDataDeclarationReference) value, diagnostics, context);
        case DataPackage.DATA_PARAMETER:
            return validateDataParameter((DataParameter) value, diagnostics,
                    context);
        case DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER:
            return validateDataDeclarationReferenceDataParameter(
                    (DataDeclarationReferenceDataParameter) value, diagnostics,
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
    public boolean validateDataType(DataType dataType,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) dataType, diagnostics,
                context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateDataDeclaration(DataDeclaration dataDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) dataDeclaration,
                diagnostics, context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateExplicitDataDeclaration(
            ExplicitDataDeclaration explicitDataDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) explicitDataDeclaration,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) explicitDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) explicitDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) explicitDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) explicitDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) explicitDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) explicitDataDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) explicitDataDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) explicitDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateExplicitDataDeclaration_hasInitializationIfConst(
                    explicitDataDeclaration, diagnostics, context);
        return result;
    }

    /**
     * Validates the hasInitializationIfConst constraint of '<em>Explicit Data Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateExplicitDataDeclaration_hasInitializationIfConst(
            ExplicitDataDeclaration explicitDataDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (explicitDataDeclaration.isConst()
                && explicitDataDeclaration.getValue() == null) {
            if (diagnostics != null) {
                diagnostics.add(
                        createDiagnostic(Diagnostic.ERROR, DIAGNOSTIC_SOURCE, 0,
                                "_UI_GenericConstraint_diagnostic",
                                new Object[] { "uninitializedConstData",
                                        getObjectLabel(explicitDataDeclaration,
                                                context) },
                                new Object[] { explicitDataDeclaration,
                                        ErrorCodeEnum.uninitializedConstData },
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
    public boolean validateSubDataDeclarationReference(
            SubDataDeclarationReference subDataDeclarationReference,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment(
                (EObject) subDataDeclarationReference, diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) subDataDeclarationReference, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) subDataDeclarationReference, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) subDataDeclarationReference, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) subDataDeclarationReference, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) subDataDeclarationReference, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) subDataDeclarationReference,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) subDataDeclarationReference, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) subDataDeclarationReference, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validateSubDataDeclarationReference_hasOneDeclaration(
                    subDataDeclarationReference, diagnostics, context);
        return result;
    }

    /**
     * Validates the hasOneDeclaration constraint of '<em>Sub Data Declaration Reference</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateSubDataDeclarationReference_hasOneDeclaration(
            SubDataDeclarationReference subDataDeclarationReference,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        int c = 0;

        c += subDataDeclarationReference.getComponentDeclaration() != null ? 1
                : 0;
        c += subDataDeclarationReference.getPortDeclaration() != null ? 1 : 0;
        if (c != 1) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "hasOneDeclaration",
                                getObjectLabel(subDataDeclarationReference,
                                        context) },
                        new Object[] { subDataDeclarationReference,
                                ErrorCodeEnum.hasOneDeclaration },
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
    public boolean validateDataParameter(DataParameter dataParameter,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) dataParameter,
                diagnostics, context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateDataDeclarationReferenceDataParameter(
            DataDeclarationReferenceDataParameter dataDeclarationReferenceDataParameter,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment(
                (EObject) dataDeclarationReferenceDataParameter, diagnostics,
                context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) dataDeclarationReferenceDataParameter, diagnostics,
                context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) dataDeclarationReferenceDataParameter,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) dataDeclarationReferenceDataParameter,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) dataDeclarationReferenceDataParameter,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) dataDeclarationReferenceDataParameter,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID(
                    (EObject) dataDeclarationReferenceDataParameter,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) dataDeclarationReferenceDataParameter,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) dataDeclarationReferenceDataParameter,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validateDataDeclarationReferenceDataParameter_hasCorrectType(
                    dataDeclarationReferenceDataParameter, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validateDataDeclarationReferenceDataParameter_hasCorrectConst(
                    dataDeclarationReferenceDataParameter, diagnostics,
                    context);
        return result;
    }

    /**
     * Validates the hasCorrectType constraint of '<em>Declaration Reference Data Parameter</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateDataDeclarationReferenceDataParameter_hasCorrectType(
            DataDeclarationReferenceDataParameter dataDeclarationReferenceDataParameter,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        DataType referenceDataType = dataDeclarationReferenceDataParameter
                .getDataDeclarationReference().getDataType();
        DataType parameterDataType = dataDeclarationReferenceDataParameter
                .getParameterDeclaration().getDataType();

        assert (referenceDataType == dataDeclarationReferenceDataParameter
                .getType());

        if (!(referenceDataType.isKindOf(parameterDataType)
                && parameterDataType.isKindOf(referenceDataType))) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "hasCorrectType",
                                getObjectLabel(
                                        dataDeclarationReferenceDataParameter,
                                        context) },
                        new Object[] { dataDeclarationReferenceDataParameter,
                                ErrorCodeEnum.hasIncorrectType,
                                parameterDataType, referenceDataType },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the hasCorrectConst constraint of '<em>Declaration Reference Data Parameter</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateDataDeclarationReferenceDataParameter_hasCorrectConst(
            DataDeclarationReferenceDataParameter dataDeclarationReferenceDataParameter,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean referenceIsConst = dataDeclarationReferenceDataParameter
                .getDataDeclarationReference().isConst();
        boolean parameterIsConst = dataDeclarationReferenceDataParameter
                .getParameterDeclaration().isConst();

        if (!parameterIsConst && referenceIsConst) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "hasIncorrectConst",
                                getObjectLabel(
                                        dataDeclarationReferenceDataParameter,
                                        context) },
                        new Object[] { dataDeclarationReferenceDataParameter,
                                ErrorCodeEnum.hasIncorrectConst },
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

} //DataValidator
