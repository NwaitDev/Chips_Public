/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
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

package bip2.ujf.verimag.bip.packaging.util;

import bip2.ujf.verimag.bip.data.util.DataValidator;
import bip2.ujf.verimag.bip.data.DataType;
import bip2.ujf.verimag.bip.packaging.*;
import bip2.ujf.verimag.bip.types.Type;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
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
 * @see bip2.ujf.verimag.bip.packaging.PackagingPackage
 * @generated
 */
public class PackagingValidator extends EObjectValidator {
    /**
     * The cached model package
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static final PackagingValidator INSTANCE = new PackagingValidator();

    /**
     * A constant for the {@link org.eclipse.emf.common.util.Diagnostic#getSource() source} of diagnostic {@link org.eclipse.emf.common.util.Diagnostic#getCode() codes} from this package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.eclipse.emf.common.util.Diagnostic#getSource()
     * @see org.eclipse.emf.common.util.Diagnostic#getCode()
     * @generated
     */
    public static final String DIAGNOSTIC_SOURCE = "bip2.ujf.verimag.bip.packaging";

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
    protected DataValidator dataValidator;

    /**
     * Creates an instance of the switch.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public PackagingValidator() {
        super();
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
        return PackagingPackage.eINSTANCE;
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
        case PackagingPackage.BIP_PACKAGE:
            return validateBipPackage((BipPackage) value, diagnostics, context);
        case PackagingPackage.BIP_PACKAGE_SET:
            return validateBipPackageSet((BipPackageSet) value, diagnostics,
                    context);
        case PackagingPackage.CONST_DATA_DECLARATION:
            return validateConstDataDeclaration((ConstDataDeclaration) value,
                    diagnostics, context);
        case PackagingPackage.PROTOTYPE:
            return validatePrototype((Prototype) value, diagnostics, context);
        case PackagingPackage.FUNCTION_CALL_PROTOTYPE:
            return validateFunctionCallPrototype((FunctionCallPrototype) value,
                    diagnostics, context);
        case PackagingPackage.BINARY_OP_PROTOTYPE:
            return validateBinaryOpPrototype((BinaryOpPrototype) value,
                    diagnostics, context);
        case PackagingPackage.UNARY_OP_PROTOTYPE:
            return validateUnaryOpPrototype((UnaryOpPrototype) value,
                    diagnostics, context);
        case PackagingPackage.PROTOTYPE_PARAMETER_DECLARATION:
            return validatePrototypeParameterDeclaration(
                    (PrototypeParameterDeclaration) value, diagnostics,
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
    public boolean validateBipPackage(BipPackage bipPackage,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) bipPackage, diagnostics,
                context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) bipPackage, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms((EObject) bipPackage,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained((EObject) bipPackage,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) bipPackage, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves((EObject) bipPackage,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) bipPackage, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) bipPackage, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique((EObject) bipPackage,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validateBipPackage_checkForCyclesInSubTyping(bipPackage,
                    diagnostics, context);
        return result;
    }

    /**
     * Recursive check for cycles in the refinement relationship of data types,
     * coming from a specific path in this relationship
     * @param dataType the target data type to be added to the path and from
     * which cycles should be checked
     * @param pathInDataTypes the already computed path
     * @return true if there exist a cycle from pathInDataTypes,dataType
     * @generated NOT
     */
    private boolean checkForCyclesInSubTypingFrom(Type type,
            List<Type> pathInDataTypes) {
        boolean ret = pathInDataTypes.contains(type);

        pathInDataTypes.add(type);

        if (!ret) {
            for (Type superType : type.getSuperTypes()) {
                ret |= checkForCyclesInSubTypingFrom(superType,
                        pathInDataTypes);

                if (ret)
                    break;
            }
        }

        return ret;
    }

    /**
     * Validates the checkForCyclesInSubTyping constraint of '<em>Bip Package</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateBipPackage_checkForCyclesInSubTyping(
            BipPackage bipPackage, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        boolean ok = true;

        DataType faultyDataType = null;
        List<Type> cycle = null;

        for (DataType dataType : bipPackage.getDataTypes()) {
            List<Type> path = new ArrayList<Type>();

            if (checkForCyclesInSubTypingFrom(dataType, path)) {
                faultyDataType = dataType;
                cycle = path;
                ok = false;
                break;
            }
        }

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "checkForCyclesInSubTyping",
                                getObjectLabel(bipPackage, context) },
                        new Object[] { faultyDataType,
                                // cycle, FIXME: add the path in the error message
                                ErrorCodeEnum.checkForCyclesInSubTyping },
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
    public boolean validateBipPackageSet(BipPackageSet bipPackageSet,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) bipPackageSet,
                diagnostics, context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateConstDataDeclaration(
            ConstDataDeclaration constDataDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) constDataDeclaration,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) constDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) constDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) constDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) constDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) constDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) constDataDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) constDataDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) constDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= dataValidator
                    .validateExplicitDataDeclaration_hasInitializationIfConst(
                            constDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConstDataDeclaration_hasCorrectConst(
                    constDataDeclaration, diagnostics, context);
        return result;
    }

    /**
     * Validates the hasCorrectConst constraint of '<em>Const Data Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConstDataDeclaration_hasCorrectConst(
            ConstDataDeclaration constDataDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!constDataDeclaration.isConst()) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "incorrectConstForConstDataDeclaration",
                                getObjectLabel(constDataDeclaration, context) },
                        new Object[] { constDataDeclaration,
                                ErrorCodeEnum.incorrectConstForConstDataDeclaration },
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
    public boolean validatePrototype(Prototype prototype,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) prototype, diagnostics,
                context))
            return false;
        boolean result = validate_EveryMultiplicityConforms((EObject) prototype,
                diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms((EObject) prototype,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained((EObject) prototype,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) prototype, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves((EObject) prototype,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) prototype, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) prototype, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique((EObject) prototype,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validatePrototype_involveOnlyDataTypeIfNotNative(
                    prototype, diagnostics, context);
        return result;
    }

    /**
     * Validates the involveOnlyDataTypeIfNotNative constraint of '<em>Prototype</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validatePrototype_involveOnlyDataTypeIfNotNative(
            Prototype prototype, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        boolean ok = true;

        if (!prototype.isNative()) {
            for (PrototypeParameterDeclaration param : prototype
                    .getParameterDeclarations()) {
                if (!(param.getType() instanceof DataType)) {
                    ok = false;
                    break;
                }
            }

            if (prototype.getReturnType() != null) {
                if (!(prototype.getReturnType() instanceof DataType)) {
                    ok = false;
                }
            }
        }

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(
                        createDiagnostic(Diagnostic.ERROR, DIAGNOSTIC_SOURCE, 0,
                                "_UI_GenericConstraint_diagnostic",
                                new Object[] { "involveOnlyDataTypeIfNotNative",
                                        getObjectLabel(prototype, context) },
                                new Object[] { prototype }, context));
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
    public boolean validateFunctionCallPrototype(
            FunctionCallPrototype functionCallPrototype,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) functionCallPrototype,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) functionCallPrototype, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) functionCallPrototype, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) functionCallPrototype, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) functionCallPrototype, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) functionCallPrototype, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) functionCallPrototype,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) functionCallPrototype,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) functionCallPrototype, diagnostics, context);
        if (result || diagnostics != null)
            result &= validatePrototype_involveOnlyDataTypeIfNotNative(
                    functionCallPrototype, diagnostics, context);
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateBinaryOpPrototype(
            BinaryOpPrototype binaryOpPrototype, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) binaryOpPrototype,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) binaryOpPrototype, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) binaryOpPrototype, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) binaryOpPrototype, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) binaryOpPrototype, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves((EObject) binaryOpPrototype,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) binaryOpPrototype,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) binaryOpPrototype,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique((EObject) binaryOpPrototype,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validatePrototype_involveOnlyDataTypeIfNotNative(
                    binaryOpPrototype, diagnostics, context);
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateUnaryOpPrototype(UnaryOpPrototype unaryOpPrototype,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) unaryOpPrototype,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) unaryOpPrototype, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) unaryOpPrototype, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) unaryOpPrototype, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) unaryOpPrototype, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves((EObject) unaryOpPrototype,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) unaryOpPrototype, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) unaryOpPrototype,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique((EObject) unaryOpPrototype,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validatePrototype_involveOnlyDataTypeIfNotNative(
                    unaryOpPrototype, diagnostics, context);
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validatePrototypeParameterDeclaration(
            PrototypeParameterDeclaration prototypeParameterDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint(
                (EObject) prototypeParameterDeclaration, diagnostics, context);
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

} //PackagingValidator
