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

package bip2.ujf.verimag.bip.behavior.util;

import bip2.ujf.verimag.bip.actionlang.AssignmentExpression;
import bip2.ujf.verimag.bip.actionlang.BinaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.Expression;
import bip2.ujf.verimag.bip.actionlang.FunctionCallExpression;
import bip2.ujf.verimag.bip.actionlang.IfThenElseExpression;
import bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.UnaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.ValuedExpression;
import bip2.ujf.verimag.bip.behavior.*;
import bip2.ujf.verimag.bip.component.atom.AtomInternalDataDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomInternalExternalPortDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomInternalPortDeclaration;
import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataDeclarationReferenceDataParameter;
import bip2.ujf.verimag.bip.types.AtomType;
import bip2.ujf.verimag.bip.types.ConnectorType;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

import org.eclipse.emf.common.util.BasicEList;
import org.eclipse.emf.common.util.Diagnostic;
import org.eclipse.emf.common.util.DiagnosticChain;
import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.common.util.ResourceLocator;

import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;

import org.eclipse.emf.ecore.util.EObjectValidator;

import ujf.verimag.bip.error.message.ErrorCodeEnum;

import lpsolve.LpSolve;
import lpsolve.LpSolveException;

/**
 * <!-- begin-user-doc -->
 * The <b>Validator</b> for the model.
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.behavior.BehaviorPackage
 * @generated
 */
public class BehaviorValidator extends EObjectValidator {
    /**
     * The cached model package
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static final BehaviorValidator INSTANCE = new BehaviorValidator();

    /**
     * A constant for the {@link org.eclipse.emf.common.util.Diagnostic#getSource() source} of diagnostic {@link org.eclipse.emf.common.util.Diagnostic#getCode() codes} from this package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.eclipse.emf.common.util.Diagnostic#getSource()
     * @see org.eclipse.emf.common.util.Diagnostic#getCode()
     * @generated
     */
    public static final String DIAGNOSTIC_SOURCE = "bip2.ujf.verimag.bip.behavior";

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
    public BehaviorValidator() {
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
        return BehaviorPackage.eINSTANCE;
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
        case BehaviorPackage.PETRI_NET:
            return validatePetriNet((PetriNet) value, diagnostics, context);
        case BehaviorPackage.STATE:
            return validateState((State) value, diagnostics, context);
        case BehaviorPackage.TRANSITION:
            return validateTransition((Transition) value, diagnostics, context);
        default:
            return true;
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validatePetriNet(PetriNet petriNet,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) petriNet, diagnostics,
                context))
            return false;
        boolean result = validate_EveryMultiplicityConforms((EObject) petriNet,
                diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms((EObject) petriNet,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained((EObject) petriNet,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) petriNet, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves((EObject) petriNet,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) petriNet, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) petriNet, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique((EObject) petriNet,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validatePetriNet_checkIllFormed(petriNet, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validatePetriNet_checkUninitializedVariablesOfPetriNet(
                    petriNet, diagnostics, context);
        if (result || diagnostics != null)
            result &= validatePetriNet_checkUninitializedVariablesExportedByPortOfAtom(
                    petriNet, diagnostics, context);
        if (result || diagnostics != null)
            result &= validatePetriNet_checkUninitializedVariablesExportedAtom(
                    petriNet, diagnostics, context);
        return result;
    }

    /**
     * Validates the checkIllFormed constraint of '<em>Petri Net</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validatePetriNet_checkIllFormed(PetriNet petriNet,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean noDuplicated = checkDuplicatedTriggerPortFromSameState(petriNet,
                diagnostics, context);
        boolean oneSafe = checkOneSafety(petriNet, diagnostics, context);
        boolean noDeadTransition = checkDeadTransitions(petriNet, diagnostics,
                context);

        return noDuplicated && oneSafe && noDeadTransition;
    }

    /**
     * Validates the checkDuplicatedTriggerPortFromSameState constraint of '
     * <em>Petri Net</em>'. <!-- begin-user-doc --> <!-- end-user-doc -->
     * 
     * @generated NOT
     */
    public boolean checkDuplicatedTriggerPortFromSameState(PetriNet petriNet,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = true;

        Map<Transition, Integer> errorLevels = new HashMap<Transition, Integer>();
        Map<Transition, Transition> faultyTransitions = new HashMap<Transition, Transition>();

        for (Transition t1 : petriNet.getTransitions()) {
            for (Transition t2 : petriNet.getTransitions()) {
                if (t1 == t2 || t1.getLineStart() < t2.getLineStart())
                    continue;

                AtomInternalExternalPortDeclaration p1 = t1.getTriggerPort();
                AtomInternalExternalPortDeclaration p2 = t2.getTriggerPort();

                if (p1 == p2) {
                    if (t1.getSources().containsAll(t2.getSources())
                            || t2.getSources().containsAll(t1.getSources())) {
                        ok = false;

                        if (t1.getGuard() == null && t2.getGuard() == null) {
                            errorLevels.put(t1, Diagnostic.ERROR);
                            faultyTransitions.put(t1, t2);
                            break;
                        } else if (!errorLevels.containsKey(t1)) {
                            errorLevels.put(t1, Diagnostic.WARNING);
                            faultyTransitions.put(t1, t2);
                        }
                    } else {
                        Set<State> states = new HashSet<State>();

                        states.addAll(t1.getSources());
                        states.addAll(t2.getSources());

                        EList<State> statesList = new BasicEList<State>(states);

                        if (petriNet.mayBeCoverable(statesList)) {
                            ok = false;

                            if (t1.getGuard() == null && t2.getGuard() == null
                                    && petriNet.isCoverable(statesList)) {
                                errorLevels.put(t1, Diagnostic.ERROR);
                                faultyTransitions.put(t1, t2);
                                break;
                            } else if (!errorLevels.containsKey(t1)) {
                                errorLevels.put(t1, Diagnostic.WARNING);
                                faultyTransitions.put(t1, t2);
                            }
                        }
                    }
                }
            }
        }

        if (!ok) {
            if (diagnostics != null) {
                for (Entry<Transition, Transition> e : faultyTransitions
                        .entrySet()) {
                    // retrieve faulty pair of transitions
                    Transition t1 = e.getKey();
                    Transition t2 = e.getValue();

                    // retrieve error level
                    assert (errorLevels.containsKey(t1));
                    int level = errorLevels.get(t1);

                    diagnostics.add(createDiagnostic(level, DIAGNOSTIC_SOURCE,
                            0, "_UI_GenericConstraint_diagnostic",
                            new Object[] {
                                    "checkDuplicatedTriggerPortFromSameState",
                                    getObjectLabel(petriNet, context) },
                            new Object[] { t1,
                                    ErrorCodeEnum.checkDuplicatedTriggerPortFromSameState,
                                    t2 },
                            context));
                }
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the checkUninitializedVariablesOfPetriNet constraint of '<em>Petri Net</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validatePetriNet_checkUninitializedVariablesOfPetriNet(
            PetriNet petriNet, DiagnosticChain diagnostics,
            Map<Object, Object> context) {

        EList<Expression> errors = petriNet.getUninitializedVariables();

        if (!errors.isEmpty()) {
            if (diagnostics != null) {
                // getErrors() = all expressions involving an uninitialized variable
                for (Expression ref : errors) {
                    diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                            DIAGNOSTIC_SOURCE, 0,
                            "_UI_GenericConstraint_diagnostic",
                            new Object[] { "uninitializedVariableOfPetriNet",
                                    getObjectLabel(ref, context) },
                            new Object[] { ref,
                                    ErrorCodeEnum.uninitializedVariableOfPetriNet,
                                    ref },
                            context));
                }
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the checkUninitializedVariablesExportedByPortOfAtom constraint of '<em>Petri Net</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validatePetriNet_checkUninitializedVariablesExportedByPortOfAtom(
            PetriNet petriNet, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        boolean ret = true;

        for (Transition t : petriNet.getTransitions()) {
            if (t.getTriggerPort() != null) {
                EList<DataDeclaration> uninitializedVariables = petriNet
                        .getUninitializedExportedVariables(t);

                if (!uninitializedVariables.isEmpty()) {
                    ret = false;

                    if (diagnostics != null) {
                        diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                                DIAGNOSTIC_SOURCE, 0,
                                "_UI_GenericConstraint_diagnostic",
                                new Object[] {
                                        "uninitializedVariableExportedByPortOfAtom",
                                        getObjectLabel(t, context) },
                                new Object[] { t,
                                        ErrorCodeEnum.uninitializedVariableExportedByPortOfAtom,
                                        t.getTriggerPort(),
                                        new HashSet<DataDeclaration>(
                                                uninitializedVariables) },
                                context));
                    }
                }
            }
        }

        return ret;
    }

    /**
     * Validates the checkUninitializedVariablesExportedAtom constraint of '<em>Petri Net</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validatePetriNet_checkUninitializedVariablesExportedAtom(
            PetriNet petriNet, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        EList<DataDeclaration> uninitialized = petriNet
                .getUninitializedExportedVariables();

        if (!uninitialized.isEmpty()) {
            if (diagnostics != null) {
                for (DataDeclaration decl : uninitialized) {
                    diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                            DIAGNOSTIC_SOURCE, 0,
                            "_UI_GenericConstraint_diagnostic",
                            new Object[] {
                                    "uninitializedVariableExportedByAtom",
                                    getObjectLabel(decl, context) },
                            new Object[] { decl,
                                    ErrorCodeEnum.uninitializedVariableExportedByAtom },
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
    public boolean validateState(State state, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) state, diagnostics,
                context);
    }

    /**
     * Validates the checkOneSafety constraint of '<em>State</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean checkOneSafety(PetriNet petriNet,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = true;

        for (State state : petriNet.getStates()) {
            if (!petriNet.isOneSafe(state)) {
                ok = false;

                // for acyclic Petri net the 1-safety analysis is sound and complete
                int level = (petriNet.mayBeOneSafe(state)) ? Diagnostic.WARNING
                        : Diagnostic.ERROR;

                if (diagnostics != null) {
                    diagnostics.add(createDiagnostic(level, DIAGNOSTIC_SOURCE,
                            0, "_UI_GenericConstraint_diagnostic",
                            new Object[] { "checkOneSafety",
                                    getObjectLabel(state, context) },
                            new Object[] { state, ErrorCodeEnum.isNotOneSafe },
                            context));
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
    public boolean validateTransition(Transition transition,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) transition, diagnostics,
                context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) transition, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms((EObject) transition,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained((EObject) transition,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) transition, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves((EObject) transition,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) transition, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) transition, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique((EObject) transition,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validateTransition_hasNoVariableModifiedBetweenProvidedAndDo(
                    transition, diagnostics, context);
        return result;
    }

    /**
     * Validates the hasNoVariableModifiedBetweenProvidedAndDo constraint of '<em>Transition</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateTransition_hasNoVariableModifiedBetweenProvidedAndDo(
            Transition transition, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        List<Expression> errors = new ArrayList<Expression>();

        if (transition.getTriggerPort() != null) {
            // observe all variables that exported through the trigger port and read in the guard
            EList<DataDeclaration> observedVariables = new BasicEList<DataDeclaration>();

            for (DataDeclarationReferenceDataParameter p : transition
                    .getTriggerPort().getDataParameters()) {
                DataDeclaration dataDecl = p.getDataDeclarationReference();

                if (transition.getGuard() != null) {
                    if (transition.getGuard().getMayReadVariables()
                            .contains(dataDecl)) {
                        observedVariables.add(dataDecl);
                    }
                }
            }

            // check if observedVariables can be read by the code before being assigned
            for (Expression expr : transition.getActions()) {
                errors.addAll(expr
                        .getMayReadUninitializedVariables(observedVariables));
            }
        }

        if (!errors.isEmpty()) {
            if (diagnostics != null) {
                for (Expression ref : errors) {
                    diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                            DIAGNOSTIC_SOURCE, 0,
                            "_UI_GenericConstraint_diagnostic",
                            new Object[] {
                                    "variableModifiedBetweenProvidedAndDo",
                                    getObjectLabel(ref, context) },
                            new Object[] { ref,
                                    ErrorCodeEnum.variableModifiedBetweenProvidedAndDo,
                                    transition.getTriggerPort() },
                            context));
                }
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the checkDeadcode constraint of '<em>Transition</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean checkDeadTransitions(PetriNet petriNet,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = true;

        for (Transition transition : petriNet.getTransitions()) {
            if (!petriNet.mayBeCoverable(transition.getSources())) {
                ok = false;
                if (diagnostics != null) {
                    diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                            DIAGNOSTIC_SOURCE, 0,
                            "_UI_GenericConstraint_diagnostic",
                            new Object[] { "deadCode",
                                    getObjectLabel(transition, context) },
                            new Object[] { transition, ErrorCodeEnum.deadCode },
                            context));
                }
            }
        }

        return ok;
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

} //BehaviorValidator
