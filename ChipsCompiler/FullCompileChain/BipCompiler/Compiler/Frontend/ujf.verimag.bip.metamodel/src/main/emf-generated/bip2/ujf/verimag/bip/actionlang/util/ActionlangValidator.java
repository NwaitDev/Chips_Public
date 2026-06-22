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

package bip2.ujf.verimag.bip.actionlang.util;

import bip2.ujf.verimag.bip.actionlang.*;
import bip2.ujf.verimag.bip.component.ComponentDataParameterDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomInternalDataDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionAction;
import bip2.ujf.verimag.bip.connector.ConnectorPortParameterDeclaration;
import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataType;
import bip2.ujf.verimag.bip.packaging.BinaryOpPrototype;
import bip2.ujf.verimag.bip.packaging.FunctionCallPrototype;
import bip2.ujf.verimag.bip.packaging.UnaryOpPrototype;
import bip2.ujf.verimag.bip.port.PortDeclaration;
import bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration;
import bip2.ujf.verimag.bip.types.Type;

import java.util.Map;

import org.eclipse.emf.common.util.BasicEList;
import org.eclipse.emf.common.util.Diagnostic;
import org.eclipse.emf.common.util.DiagnosticChain;
import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.common.util.ResourceLocator;

import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;

import org.eclipse.emf.ecore.util.EObjectValidator;

import ujf.verimag.bip.error.message.ErrorCodeEnum;

/**
 * <!-- begin-user-doc -->
 * The <b>Validator</b> for the model.
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.actionlang.ActionlangPackage
 * @generated
 */
public class ActionlangValidator extends EObjectValidator {
    /**
     * The cached model package
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static final ActionlangValidator INSTANCE = new ActionlangValidator();

    /**
     * A constant for the {@link org.eclipse.emf.common.util.Diagnostic#getSource() source} of diagnostic {@link org.eclipse.emf.common.util.Diagnostic#getCode() codes} from this package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.eclipse.emf.common.util.Diagnostic#getSource()
     * @see org.eclipse.emf.common.util.Diagnostic#getCode()
     * @generated
     */
    public static final String DIAGNOSTIC_SOURCE = "bip2.ujf.verimag.bip.actionlang";

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
    public ActionlangValidator() {
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
        return ActionlangPackage.eINSTANCE;
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
        case ActionlangPackage.BINARY_OP_EXPRESSION:
            return validateBinaryOpExpression((BinaryOpExpression) value,
                    diagnostics, context);
        case ActionlangPackage.UNARY_OP_EXPRESSION:
            return validateUnaryOpExpression((UnaryOpExpression) value,
                    diagnostics, context);
        case ActionlangPackage.VALUED_EXPRESSION:
            return validateValuedExpression((ValuedExpression) value,
                    diagnostics, context);
        case ActionlangPackage.SUB_DATA_DECLARATION_REFERENCE_EXPRESSION:
            return validateSubDataDeclarationReferenceExpression(
                    (SubDataDeclarationReferenceExpression) value, diagnostics,
                    context);
        case ActionlangPackage.DIRECT_DATA_DECLARATION_REFERENCE_EXPRESSION:
            return validateDirectDataDeclarationReferenceExpression(
                    (DirectDataDeclarationReferenceExpression) value,
                    diagnostics, context);
        case ActionlangPackage.ASSIGNMENT_EXPRESSION:
            return validateAssignmentExpression((AssignmentExpression) value,
                    diagnostics, context);
        case ActionlangPackage.FUNCTION_CALL_EXPRESSION:
            return validateFunctionCallExpression(
                    (FunctionCallExpression) value, diagnostics, context);
        case ActionlangPackage.EXPRESSION:
            return validateExpression((Expression) value, diagnostics, context);
        case ActionlangPackage.VALUED_REFERENCE_EXPRESSION:
            return validateValuedReferenceExpression(
                    (ValuedReferenceExpression) value, diagnostics, context);
        case ActionlangPackage.DIRECT_BOOLEAN_EXPRESSION:
            return validateDirectBooleanExpression(
                    (DirectBooleanExpression) value, diagnostics, context);
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION:
            return validateIfThenElseExpression((IfThenElseExpression) value,
                    diagnostics, context);
        case ActionlangPackage.DIRECT_INTEGER_EXPRESSION:
            return validateDirectIntegerExpression(
                    (DirectIntegerExpression) value, diagnostics, context);
        case ActionlangPackage.DIRECT_FLOAT_EXPRESSION:
            return validateDirectFloatExpression((DirectFloatExpression) value,
                    diagnostics, context);
        case ActionlangPackage.DIRECT_STRING_EXPRESSION:
            return validateDirectStringExpression(
                    (DirectStringExpression) value, diagnostics, context);
        case ActionlangPackage.BINARY_OPERATORS:
            return validateBinaryOperators((BinaryOperators) value, diagnostics,
                    context);
        case ActionlangPackage.UNARY_OPERATORS:
            return validateUnaryOperators((UnaryOperators) value, diagnostics,
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
    public boolean validateBinaryOpExpression(
            BinaryOpExpression binaryOpExpression, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) binaryOpExpression,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) binaryOpExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) binaryOpExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) binaryOpExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) binaryOpExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves((EObject) binaryOpExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) binaryOpExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) binaryOpExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique((EObject) binaryOpExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectType(
                    binaryOpExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectConst(
                    binaryOpExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_noSideEffectInGuards(
                    binaryOpExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateBinaryOpExpression_hasOneMatchingPrototype(
                    binaryOpExpression, diagnostics, context);
        return result;
    }

    /**
     * Validates the hasCorrectType constraint of '<em>Binary Op Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateBinaryOpExpression_hasOneMatchingPrototype(
            BinaryOpExpression binaryOpExpression, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        // skip if (at lease) one the the operands is already ill-typed
        if (binaryOpExpression.getLeft().getType() == null
                || binaryOpExpression.getRight().getType() == null)
            return true;

        EList<BinaryOpPrototype> prototypes = binaryOpExpression
                .getPrototypes();

        boolean ok = prototypes.size() == 1;

        if (!ok) {
            if (diagnostics != null) {
                Type leftDataType = binaryOpExpression.getLeft().getType();
                Type rightDataType = binaryOpExpression.getRight().getType();

                if (binaryOpExpression.getPrototypes().size() == 0) {
                    diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                            DIAGNOSTIC_SOURCE, 0,
                            "_UI_GenericConstraint_diagnostic",
                            new Object[] { "noMatchBinaryOp",
                                    getObjectLabel(binaryOpExpression,
                                            context) },
                            new Object[] { binaryOpExpression,
                                    ErrorCodeEnum.noMatchBinaryOp, leftDataType,
                                    rightDataType },
                            context));
                }

                if (binaryOpExpression.getPrototypes().size() > 1) {
                    diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                            DIAGNOSTIC_SOURCE, 0,
                            "_UI_GenericConstraint_diagnostic",
                            new Object[] { "ambiguousBinaryOp",
                                    getObjectLabel(binaryOpExpression,
                                            context) },
                            new Object[] { binaryOpExpression,
                                    ErrorCodeEnum.ambiguousBinaryOp,
                                    leftDataType, rightDataType, prototypes },
                            context));
                }
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
    public boolean validateUnaryOpExpression(
            UnaryOpExpression unaryOpExpression, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) unaryOpExpression,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) unaryOpExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) unaryOpExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) unaryOpExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) unaryOpExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves((EObject) unaryOpExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) unaryOpExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) unaryOpExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique((EObject) unaryOpExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectType(unaryOpExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectConst(
                    unaryOpExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_noSideEffectInGuards(
                    unaryOpExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateUnaryOpExpression_hasOneMatchingPrototype(
                    unaryOpExpression, diagnostics, context);
        return result;
    }

    /**
     * Validates the hasCorrectType constraint of '<em>Unary Op Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateUnaryOpExpression_hasOneMatchingPrototype(
            UnaryOpExpression unaryOpExpression, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        // skip if the operand is already ill-typed
        if (unaryOpExpression.getOperand().getType() == null)
            return true;

        EList<UnaryOpPrototype> prototypes = unaryOpExpression.getPrototypes();

        boolean ok = prototypes.size() == 1;

        if (!ok) {
            if (diagnostics != null) {
                Type operandDataType = unaryOpExpression.getOperand().getType();

                if (unaryOpExpression.getPrototypes().size() == 0) {
                    diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                            DIAGNOSTIC_SOURCE, 0,
                            "_UI_GenericConstraint_diagnostic",
                            new Object[] { "noMatchUnaryOp",
                                    getObjectLabel(unaryOpExpression,
                                            context) },
                            new Object[] { unaryOpExpression,
                                    ErrorCodeEnum.noMatchUnaryOp,
                                    operandDataType },
                            context));
                }

                if (unaryOpExpression.getPrototypes().size() > 1) {
                    diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                            DIAGNOSTIC_SOURCE, 0,
                            "_UI_GenericConstraint_diagnostic",
                            new Object[] { "ambiguousUnaryOp",
                                    getObjectLabel(unaryOpExpression,
                                            context) },
                            new Object[] { unaryOpExpression,
                                    ErrorCodeEnum.ambiguousUnaryOp,
                                    operandDataType, prototypes },
                            context));
                }
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
    public boolean validateValuedExpression(ValuedExpression valuedExpression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) valuedExpression,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) valuedExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) valuedExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) valuedExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) valuedExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves((EObject) valuedExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) valuedExpression, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) valuedExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique((EObject) valuedExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectType(valuedExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectConst(valuedExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_noSideEffectInGuards(
                    valuedExpression, diagnostics, context);
        return result;
    }

    /**
     * Validates the hasCorrectType constraint of '<em>Valued Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateValuedExpression_hasCorrectType(
            ValuedExpression valuedExpression, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        boolean ok = true;

        Type dataType = valuedExpression.getType();
        Type expectedDataType = valuedExpression.getExpectedType();

        if (dataType != null && expectedDataType != null) {
            if (!dataType.isKindOf(expectedDataType)) {
                ok = false;
            }
        }
        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "hasIncorrectType",
                                getObjectLabel(valuedExpression, context) },
                        new Object[] { valuedExpression,
                                ErrorCodeEnum.hasIncorrectType,
                                expectedDataType, dataType },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the hasCorrectConst constraint of '<em>Valued Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateValuedExpression_hasCorrectConst(
            ValuedExpression valuedExpression, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        if (!valuedExpression.expectedIsConst() && valuedExpression.isConst()) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "hasIncorrectConst",
                                getObjectLabel(valuedExpression, context) },
                        new Object[] { valuedExpression,
                                ErrorCodeEnum.hasIncorrectConst },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the noSideEffectInGuards constraint of '<em>Valued Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateValuedExpression_noSideEffectInGuards(
            ValuedExpression valuedExpression, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        if (valuedExpression.isInConstantContext()
                && valuedExpression.hasSideEffect()) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "noSideEffectInGuards",
                                getObjectLabel(valuedExpression, context) },
                        new Object[] { valuedExpression,
                                ErrorCodeEnum.noSideEffectInGuards },
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
    public boolean validateSubDataDeclarationReferenceExpression(
            SubDataDeclarationReferenceExpression subDataDeclarationReferenceExpression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment(
                (EObject) subDataDeclarationReferenceExpression, diagnostics,
                context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) subDataDeclarationReferenceExpression, diagnostics,
                context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) subDataDeclarationReferenceExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) subDataDeclarationReferenceExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) subDataDeclarationReferenceExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) subDataDeclarationReferenceExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID(
                    (EObject) subDataDeclarationReferenceExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) subDataDeclarationReferenceExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) subDataDeclarationReferenceExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectType(
                    subDataDeclarationReferenceExpression, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectConst(
                    subDataDeclarationReferenceExpression, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_noSideEffectInGuards(
                    subDataDeclarationReferenceExpression, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validateSubDataDeclarationReferenceExpression_dataIsExportedInComponent(
                    subDataDeclarationReferenceExpression, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validateSubDataDeclarationReferenceExpression_dataRefInConnectorActionToInvolvedPort(
                    subDataDeclarationReferenceExpression, diagnostics,
                    context);
        return result;
    }

    /**
     * Validates the dataIsExportedInComponent constraint of '<em>Sub Data Declaration Reference Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateSubDataDeclarationReferenceExpression_dataIsExportedInComponent(
            SubDataDeclarationReferenceExpression subDataDeclarationReferenceExpression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = true;
        //  A priority can only access data that is exported by the component

        DataDeclaration dd = subDataDeclarationReferenceExpression
                .getSubDataDeclarationRef().getForwardDataDeclaration();

        if (dd instanceof AtomInternalDataDeclaration
                && !((AtomInternalDataDeclaration) dd).isExported()) {
            EObject e = subDataDeclarationReferenceExpression;
            while (e instanceof Expression) {
                e = e.eContainer();
            }
            if (e instanceof CompoundPriorityDeclaration) {
                ok = false;
            }
        }
        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "dataIsExportedInComponent",
                                getObjectLabel(
                                        subDataDeclarationReferenceExpression,
                                        context) },
                        new Object[] { subDataDeclarationReferenceExpression },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the dataRefInConnectorActionToInvolvedPort constraint of '<em>Sub Data Declaration Reference Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateSubDataDeclarationReferenceExpression_dataRefInConnectorActionToInvolvedPort(
            SubDataDeclarationReferenceExpression subDataDeclarationReferenceExpression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = true;

        PortDeclaration pd = subDataDeclarationReferenceExpression
                .getSubDataDeclarationRef().getPortDeclaration();

        // if this is something inside a connector (guard/up/down)
        if (pd != null && pd instanceof ConnectorPortParameterDeclaration) {
            EObject e = subDataDeclarationReferenceExpression;
            while (e instanceof Expression) {
                e = e.eContainer();
            }
            // can't be something else
            ConnectorInteractionAction cia = (ConnectorInteractionAction) e;

            ok = cia.getOnPorts().contains(pd);
        }

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "dataRefInConnectorActionToInvolvedPort",
                                getObjectLabel(
                                        subDataDeclarationReferenceExpression,
                                        context) },
                        new Object[] { subDataDeclarationReferenceExpression,
                                ErrorCodeEnum.dataRefInConnectorActionToInvolvedPort },
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
    public boolean validateDirectDataDeclarationReferenceExpression(
            DirectDataDeclarationReferenceExpression directDataDeclarationReferenceExpression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment(
                (EObject) directDataDeclarationReferenceExpression, diagnostics,
                context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) directDataDeclarationReferenceExpression, diagnostics,
                context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) directDataDeclarationReferenceExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) directDataDeclarationReferenceExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) directDataDeclarationReferenceExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) directDataDeclarationReferenceExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID(
                    (EObject) directDataDeclarationReferenceExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) directDataDeclarationReferenceExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) directDataDeclarationReferenceExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectType(
                    directDataDeclarationReferenceExpression, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectConst(
                    directDataDeclarationReferenceExpression, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_noSideEffectInGuards(
                    directDataDeclarationReferenceExpression, diagnostics,
                    context);
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateAssignmentExpression(
            AssignmentExpression assignmentExpression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) assignmentExpression,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) assignmentExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) assignmentExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) assignmentExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) assignmentExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) assignmentExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) assignmentExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) assignmentExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) assignmentExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateAssignmentExpression_rhsIsADataDeclarationReference(
                    assignmentExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateAssignmentExpression_hasCorrectConst(
                    assignmentExpression, diagnostics, context);
        return result;
    }

    /**
     * Validates the rhsIsADataDeclarationReference constraint of '<em>Assignment Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateAssignmentExpression_rhsIsADataDeclarationReference(
            AssignmentExpression assignmentExpression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = (assignmentExpression
                .getLhs() instanceof DirectDataDeclarationReferenceExpression)
                || (assignmentExpression
                        .getLhs() instanceof SubDataDeclarationReferenceExpression);

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "rhsIsADataDeclarationReference",
                                getObjectLabel(assignmentExpression, context) },
                        new Object[] { assignmentExpression,
                                ErrorCodeEnum.invalidLHSOfAssignment },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the hasCorrectConst constraint of '<em>Assignment Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateAssignmentExpression_hasCorrectConst(
            AssignmentExpression assignmentExpression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = true;

        if (assignmentExpression.getLhs().isConst()) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "hasCorrectConst",
                                getObjectLabel(assignmentExpression, context) },
                        new Object[] { assignmentExpression.getLhs(),
                                ErrorCodeEnum.hasIncorrectConst },
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
    public boolean validateFunctionCallExpression(
            FunctionCallExpression functionCallExpression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) functionCallExpression,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) functionCallExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) functionCallExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) functionCallExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) functionCallExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) functionCallExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) functionCallExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) functionCallExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) functionCallExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectType(
                    functionCallExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectConst(
                    functionCallExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_noSideEffectInGuards(
                    functionCallExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateFunctionCallExpression_hasOneMatchingPrototype(
                    functionCallExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateFunctionCallExpression_hasValueInValuedContext(
                    functionCallExpression, diagnostics, context);
        return result;
    }

    /**
     * Validates the hasCorrectType constraint of '<em>Function Call Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateFunctionCallExpression_hasOneMatchingPrototype(
            FunctionCallExpression functionCallExpression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        // skip if (at least) one of the parameters is already ill-typed
        for (ValuedExpression expression : functionCallExpression
                .getParameters()) {
            if (expression.getType() == null)
                return true;
        }

        EList<FunctionCallPrototype> prototypes = functionCallExpression
                .getPrototypes();

        boolean ok = prototypes.size() == 1;

        if (!ok) {
            if (diagnostics != null) {
                EList<Type> parametersTypes = new BasicEList<Type>();

                for (ValuedExpression parameter : functionCallExpression
                        .getParameters()) {
                    parametersTypes.add(parameter.getType());
                }

                if (functionCallExpression.getPrototypes().size() == 0) {
                    diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                            DIAGNOSTIC_SOURCE, 0,
                            "_UI_GenericConstraint_diagnostic",
                            new Object[] { "noMatchFunctionCall",
                                    getObjectLabel(functionCallExpression,
                                            context) },
                            new Object[] { functionCallExpression,
                                    ErrorCodeEnum.noMatchFunctionCall,
                                    parametersTypes },
                            context));
                }

                if (functionCallExpression.getPrototypes().size() > 1) {
                    diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                            DIAGNOSTIC_SOURCE, 0,
                            "_UI_GenericConstraint_diagnostic",
                            new Object[] { "ambiguousFunctionCall",
                                    getObjectLabel(functionCallExpression,
                                            context) },
                            new Object[] { functionCallExpression,
                                    ErrorCodeEnum.ambiguousFunctionCall,
                                    parametersTypes, prototypes },
                            context));
                }

            }
            return false;
        }
        return true;
    }

    /**
     * .
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    private boolean isInValuedContext(
            FunctionCallExpression functionCallExpression) {
        boolean ret = false;

        EObject container = functionCallExpression.eContainer();

        if (container instanceof IfThenElseExpression) {
            if (functionCallExpression.eContainmentFeature()
                    .getName() == "condition") {
                ret = true;
            }
        } else if (container instanceof BinaryOpExpression) {
            ret = true;
        } else if (container instanceof UnaryOpExpression) {
            ret = true;
        } else if (container instanceof FunctionCallExpression) {
            ret = true;
        } else if (container instanceof AssignmentExpression) {
            ret = true;
        }

        return ret;
    }

    /**
     * Validates the hasValueInValuedContext constraint of '<em>Function Call Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateFunctionCallExpression_hasValueInValuedContext(
            FunctionCallExpression functionCallExpression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = true;

        FunctionCallPrototype matchingPrototype = null;

        if (isInValuedContext(functionCallExpression)) {
            EList<FunctionCallPrototype> prototypes = functionCallExpression
                    .getPrototypes();

            if (prototypes.size() == 1) {
                matchingPrototype = prototypes.get(0);
                if (matchingPrototype.getReturnType() == null) {
                    ok = false;
                }
            }
        }

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "matchingFunctionCallWithoutReturnValue",
                                getObjectLabel(functionCallExpression,
                                        context) },
                        new Object[] { functionCallExpression,
                                ErrorCodeEnum.matchingFunctionCallWithoutReturnValue,
                                matchingPrototype },
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
    public boolean validateExpression(Expression expression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) expression,
                diagnostics, context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateValuedReferenceExpression(
            ValuedReferenceExpression valuedReferenceExpression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) valuedReferenceExpression,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) valuedReferenceExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) valuedReferenceExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) valuedReferenceExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) valuedReferenceExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) valuedReferenceExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) valuedReferenceExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) valuedReferenceExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) valuedReferenceExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectType(
                    valuedReferenceExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectConst(
                    valuedReferenceExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_noSideEffectInGuards(
                    valuedReferenceExpression, diagnostics, context);
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateDirectBooleanExpression(
            DirectBooleanExpression directBooleanExpression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) directBooleanExpression,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) directBooleanExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) directBooleanExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) directBooleanExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) directBooleanExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) directBooleanExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) directBooleanExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) directBooleanExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) directBooleanExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectType(
                    directBooleanExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectConst(
                    directBooleanExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_noSideEffectInGuards(
                    directBooleanExpression, diagnostics, context);
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateIfThenElseExpression(
            IfThenElseExpression ifThenElseExpression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) ifThenElseExpression,
                diagnostics, context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateDirectIntegerExpression(
            DirectIntegerExpression directIntegerExpression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) directIntegerExpression,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) directIntegerExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) directIntegerExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) directIntegerExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) directIntegerExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) directIntegerExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) directIntegerExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) directIntegerExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) directIntegerExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectType(
                    directIntegerExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectConst(
                    directIntegerExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_noSideEffectInGuards(
                    directIntegerExpression, diagnostics, context);
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateDirectFloatExpression(
            DirectFloatExpression directFloatExpression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) directFloatExpression,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) directFloatExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) directFloatExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) directFloatExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) directFloatExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) directFloatExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) directFloatExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) directFloatExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) directFloatExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectType(
                    directFloatExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectConst(
                    directFloatExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_noSideEffectInGuards(
                    directFloatExpression, diagnostics, context);
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateDirectStringExpression(
            DirectStringExpression directStringExpression,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) directStringExpression,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) directStringExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) directStringExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) directStringExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) directStringExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) directStringExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) directStringExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) directStringExpression,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) directStringExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectType(
                    directStringExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_hasCorrectConst(
                    directStringExpression, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateValuedExpression_noSideEffectInGuards(
                    directStringExpression, diagnostics, context);
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateBinaryOperators(BinaryOperators binaryOperators,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return true;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateUnaryOperators(UnaryOperators unaryOperators,
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

} //ActionlangValidator
