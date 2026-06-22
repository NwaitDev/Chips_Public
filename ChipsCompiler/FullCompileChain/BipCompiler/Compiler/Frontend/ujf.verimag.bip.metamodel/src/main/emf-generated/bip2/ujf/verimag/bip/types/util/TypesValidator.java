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

package bip2.ujf.verimag.bip.types.util;

import bip2.ujf.verimag.bip.actionlang.BinaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.FunctionCallExpression;
import bip2.ujf.verimag.bip.actionlang.UnaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.ValuedExpression;
import bip2.ujf.verimag.bip.component.atom.AtomInternalPortDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomInternalDataDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorDataDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionAction;
import bip2.ujf.verimag.bip.connector.ConnectorPortParameterDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionPortReference;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionDefinition;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionNestedDefinition;
import bip2.ujf.verimag.bip.connector.util.ConnectorAdapterFactory;
import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.port.PortDeclaration;
import bip2.ujf.verimag.bip.port.PortDeclarationReferenceParameter;
import bip2.ujf.verimag.bip.port.SubPortDeclarationReference;
import bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration;
import bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration;
import bip2.ujf.verimag.bip.priority.ConnectorInteraction;
import bip2.ujf.verimag.bip.types.*;
import ujf.verimag.bip.metamodel.AnnotatedEObject;

import java.util.ArrayList;
import java.util.HashMap;
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
 * @see bip2.ujf.verimag.bip.types.TypesPackage
 * @generated
 */
public class TypesValidator extends EObjectValidator {
    /**
     * The cached model package
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static final TypesValidator INSTANCE = new TypesValidator();

    /**
     * A constant for the {@link org.eclipse.emf.common.util.Diagnostic#getSource() source} of diagnostic {@link org.eclipse.emf.common.util.Diagnostic#getCode() codes} from this package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.eclipse.emf.common.util.Diagnostic#getSource()
     * @see org.eclipse.emf.common.util.Diagnostic#getCode()
     * @generated
     */
    public static final String DIAGNOSTIC_SOURCE = "bip2.ujf.verimag.bip.types";

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
    public TypesValidator() {
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
        return TypesPackage.eINSTANCE;
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
        case TypesPackage.TYPE:
            return validateType((Type) value, diagnostics, context);
        case TypesPackage.BIP_TYPE:
            return validateBipType((BipType) value, diagnostics, context);
        case TypesPackage.COMPONENT_TYPE:
            return validateComponentType((ComponentType) value, diagnostics,
                    context);
        case TypesPackage.ATOM_TYPE:
            return validateAtomType((AtomType) value, diagnostics, context);
        case TypesPackage.COMPOUND_TYPE:
            return validateCompoundType((CompoundType) value, diagnostics,
                    context);
        case TypesPackage.CONNECTOR_TYPE:
            return validateConnectorType((ConnectorType) value, diagnostics,
                    context);
        case TypesPackage.PORT_TYPE:
            return validatePortType((PortType) value, diagnostics, context);
        default:
            return true;
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateType(Type type, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) type, diagnostics,
                context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateAtomType(AtomType atomType,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) atomType, diagnostics,
                context))
            return false;
        boolean result = validate_EveryMultiplicityConforms((EObject) atomType,
                diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms((EObject) atomType,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained((EObject) atomType,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) atomType, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves((EObject) atomType,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) atomType, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) atomType, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique((EObject) atomType,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validateAtomType_InternalDataSynchronizedWithExportedData(
                    atomType, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateAtomType_checkForCyclesInPrioritiesInAtom(
                    atomType, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateAtomType_checkUninitializedVariablesInAtomInternalDataDeclaration(
                    atomType, diagnostics, context);
        return result;
    }

    /**
     * Validates the InternalDataSynchronizedWithExportedData constraint of '<em>Atom Type</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateAtomType_InternalDataSynchronizedWithExportedData(
            AtomType atomType, DiagnosticChain diagnostics,
            Map<Object, Object> context) {

        boolean ok = true;

        // checks internal list is a superset of exported list
        ok = atomType.getInternalDataDeclarations()
                .containsAll(atomType.getExportedDataDeclarations());

        // checks that all internal ports marked as exported are in the exported list
        if (ok) {
            for (AtomInternalDataDeclaration aidd : atomType
                    .getInternalDataDeclarations()) {
                boolean exp = aidd.isExported();
                boolean isinexplist = atomType.getExportedDataDeclarations()
                        .contains(aidd);
                ok = ((exp && isinexplist) || (!exp && !isinexplist));
                if (!ok)
                    break;
            }
        }
        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] {
                                "InternalDataSynchronizedWithExportedData",
                                getObjectLabel(atomType, context) },
                        new Object[] { atomType,
                                ErrorCodeEnum.InternalDataSynchronizedWithExportedData },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the checkForCyclesInPrioritiesInAtom constraint of '<em>Atom Type</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateAtomType_checkForCyclesInPrioritiesInAtom(
            AtomType atomType, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        PriorityGraph atomPriorityGraph = new AtomPriorityGraph(atomType);
        Set<List<AnnotatedEObject>> allCycles = getAllCycles(atomPriorityGraph);

        Map<AtomPriorityDeclaration, List<AnnotatedEObject>> errors = new HashMap<AtomPriorityDeclaration, List<AnnotatedEObject>>();

        for (List<AnnotatedEObject> cycle : allCycles) {
            AnnotatedEObject object = getFirst(cycle);
            assert (object instanceof AtomPriorityDeclaration);
            AtomPriorityDeclaration priority = (AtomPriorityDeclaration) object;

            List<AnnotatedEObject> previousCycle = errors.get(priority);

            if (previousCycle == null) {
                errors.put(priority, cycle);
            } else {
                errors.put(priority, keep(previousCycle, cycle));
            }
        }

        if (!errors.isEmpty()) {
            if (diagnostics != null) {
                for (Map.Entry<AtomPriorityDeclaration, List<AnnotatedEObject>> entry : errors
                        .entrySet()) {
                    List<AnnotatedEObject> cycle = entry.getValue();

                    int level;

                    if (numberOfGuards(cycle) > 1)
                        level = Diagnostic.WARNING;
                    else
                        level = Diagnostic.ERROR;

                    diagnostics.add(createDiagnostic(level, DIAGNOSTIC_SOURCE,
                            0, "_UI_GenericConstraint_diagnostic",
                            new Object[] { "checkForCyclesInPrioritiesInAtom",
                                    getObjectLabel(atomType, context) },
                            new Object[] { entry.getKey(),
                                    ErrorCodeEnum.checkForCyclesInPrioritiesInAtom,
                                    cycle },
                            context));
                }
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the checkUninitializedVariables constraint of '<em>Atom Type</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateAtomType_checkUninitializedVariablesInAtomInternalDataDeclaration(
            AtomType atomType, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        // start with an empty list of erroneous expressions
        List<DirectDataDeclarationReferenceExpression> errors = new ArrayList<DirectDataDeclarationReferenceExpression>();

        // compute the initial set of uninitialized variables, i.e.
        // atom parameters as well as constant data of the package
        // are considered initialized
        Set<DataDeclaration> uninitialized = new HashSet<DataDeclaration>();
        uninitialized.addAll(atomType.getInternalDataDeclarations());

        // /!\ WARNING: order is critical since uninitialized is updated
        for (AtomInternalDataDeclaration dataDecl : atomType
                .getInternalDataDeclarations()) {
            if (dataDecl.getValue() != null) {
                // first, check uninitialized variables
                checkUninitializedVariables(dataDecl.getValue(), uninitialized,
                        errors);

                // then remove dataDecl from the uninitialized variables
                uninitialized.remove(dataDecl);
            }
        }

        if (!errors.isEmpty()) {
            if (diagnostics != null) {
                for (DirectDataDeclarationReferenceExpression ref : errors) {
                    diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                            DIAGNOSTIC_SOURCE, 0,
                            "_UI_GenericConstraint_diagnostic",
                            new Object[] { "", getObjectLabel(ref, context) },
                            new Object[] { ref,
                                    ErrorCodeEnum.uninitializedVariableInAtomInternalDataDeclaration,
                                    ref },
                            context));
                }
            }
            return false;
        }
        return true;
    }

    /**
     * 
     * @generated NOT
     */
    private void checkUninitializedVariables(ValuedExpression expression,
            Set<DataDeclaration> uninitialized,
            List<DirectDataDeclarationReferenceExpression> errors) {
        if (expression instanceof BinaryOpExpression) {
            BinaryOpExpression binaryOpExpression = (BinaryOpExpression) expression;

            checkUninitializedVariables(binaryOpExpression.getLeft(),
                    uninitialized, errors);
            checkUninitializedVariables(binaryOpExpression.getRight(),
                    uninitialized, errors);
        } else if (expression instanceof UnaryOpExpression) {
            UnaryOpExpression unaryOpExpression = (UnaryOpExpression) expression;

            checkUninitializedVariables(unaryOpExpression.getOperand(),
                    uninitialized, errors);
        } else if (expression instanceof FunctionCallExpression) {
            FunctionCallExpression functionCallExpression = (FunctionCallExpression) expression;

            for (ValuedExpression subExpression : functionCallExpression
                    .getParameters()) {
                checkUninitializedVariables(subExpression, uninitialized,
                        errors);
            }
        } else if (expression instanceof DirectDataDeclarationReferenceExpression) {
            DirectDataDeclarationReferenceExpression directData = (DirectDataDeclarationReferenceExpression) expression;

            if (uninitialized.contains(directData.getDataDeclaration())) {
                // found a reference to a variable that may be uninitialized
                if (errors != null)
                    errors.add(directData);
            }
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateComponentType(ComponentType componentType,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) componentType,
                diagnostics, context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateCompoundType(CompoundType compoundType,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) compoundType, diagnostics,
                context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) compoundType, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms((EObject) compoundType,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained((EObject) compoundType,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) compoundType, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves((EObject) compoundType,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) compoundType, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) compoundType,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique((EObject) compoundType,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validateCompoundType_exportedPortsListsSynchronized(
                    compoundType, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateCompoundType_exportedDataListsSynchronized(
                    compoundType, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateCompoundType_checkForCyclesInPrioritiesInCompound(
                    compoundType, diagnostics, context);
        return result;
    }

    /**
     * Validates the exportedPortsListsSynchronized constraint of '<em>Compound Type</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateCompoundType_exportedPortsListsSynchronized(
            CompoundType compoundType, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        boolean ok = true;

        // check inclusion in both ways
        ok = compoundType.getExportedPortDeclarations()
                .containsAll(compoundType.getExportPortDeclarations());
        ok = ok && compoundType.getExportPortDeclarations()
                .containsAll(compoundType.getExportedPortDeclarations());

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "exportedPortsListsSynchronized",
                                getObjectLabel(compoundType, context) },
                        new Object[] { compoundType,
                                ErrorCodeEnum.exportedPortsListsSynchronized },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the exportedDataListsSynchronized constraint of '<em>Compound Type</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateCompoundType_exportedDataListsSynchronized(
            CompoundType compoundType, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        boolean ok = true;

        // check inclusion in both ways
        ok = compoundType.getExportedDataDeclarations()
                .containsAll(compoundType.getExportDataDeclarations());
        ok = ok && compoundType.getExportDataDeclarations()
                .containsAll(compoundType.getExportedDataDeclarations());

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "exportedDataListsSynchronized",
                                getObjectLabel(compoundType, context) },
                        new Object[] { compoundType,
                                ErrorCodeEnum.exportedDataListsSynchronized },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Check inclusion of interactions.
     * @param inter1 the first interaction
     * @param inter2 the second interaction
     * @return true if inter1 is included in inter2
     * @generated NOT
     */
    private boolean isIncludedIn(ConnectorInteraction inter1,
            ConnectorInteraction inter2) {
        boolean ret = false;

        if (inter1.getConnectorDeclaration() == inter2
                .getConnectorDeclaration()) {
            ret = true;

            if (!inter1.getPortDeclarationReferences().isEmpty()
                    && !inter2.getPortDeclarationReferences().isEmpty()) {
                for (SubPortDeclarationReference portRef : inter1
                        .getPortDeclarationReferences()) {
                    boolean found = false;

                    for (SubPortDeclarationReference targetPortRef : inter2
                            .getPortDeclarationReferences()) {
                        if (portRef.getComponentDeclaration() == targetPortRef
                                .getComponentDeclaration()
                                && portRef
                                        .getConnectorDeclaration() == targetPortRef
                                                .getConnectorDeclaration()
                                && portRef
                                        .getForwardPortDeclaration() == targetPortRef
                                                .getForwardPortDeclaration()) {
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        ret = false;
                        break;
                    }
                }
            }
        }

        return ret;
    }

    /** 
     * Determine whether an instance of connector is top-level or not.
     * @param connector the target instance of connector
     * @return true if connector is a top-level connector
     * @generated NOT
     */
    private boolean isTopLevel(ConnectorDeclaration connector) {
        boolean ret = true;

        // compound type holding delc
        CompoundType holder = (CompoundType) connector.eContainer();

        // check all connectors involved in parameters of connector declarations
        for (ConnectorDeclaration decl : holder.getConnectorDeclarations()) {
            for (PortDeclarationReferenceParameter portRef : decl
                    .getPortParameters()) {
                SubPortDeclarationReference subPortRef = portRef
                        .getSubPortDeclarationReference();
                ConnectorDeclaration subPortRefConnector = subPortRef
                        .getConnectorDeclaration();

                if (subPortRefConnector != null) {
                    // subPortRefConnector is connected to a connector, check if equals to connector
                    if (connector == subPortRefConnector) {
                        ret = false;
                        break;
                    }
                }
            }
        }

        return ret;
    }

    /** 
     * Determine if there is a edge between two priorities in
     * the compound priority graph
     * @param fromDecl the source of the potential edge
     * @param toDecl the destination of the potential edge
     * @return true if there is an edge from fromDecl to toDecl
     * @generated NOT
     */
    private boolean areConnected(CompoundPriorityDeclaration fromDecl,
            CompoundPriorityDeclaration toDecl) {
        boolean ret = false;

        CompoundType holder = (CompoundType) fromDecl.eContainer();

        assert (holder == (CompoundType) toDecl.eContainer());

        /* WARNING:
         * Disallowed priorities of the form *:* < *:* are checked by
         * constraint compoundPriorityHasAtMostOneWildcard of priorities.
         */
        if ((fromDecl.getLow() != null || fromDecl.getHigh() != null)
                && (toDecl.getLow() != null || toDecl.getHigh() != null)) {
            if (fromDecl.getHigh() == null) {
                if (toDecl.getLow() == null) {
                    for (ConnectorDeclaration decl : holder
                            .getConnectorDeclarations()) {
                        // check if exists a connector matching both wildcards
                        if (isTopLevel(decl)
                                && decl != fromDecl.getLow()
                                        .getConnectorDeclaration()
                                && decl != toDecl.getHigh()
                                        .getConnectorDeclaration()) {
                            ret = true;
                            break;
                        }

                    }
                } else {
                    if (fromDecl.getLow().getConnectorDeclaration() != toDecl
                            .getLow().getConnectorDeclaration()) {
                        ret = true;
                    }
                }
            } else {
                if (toDecl.getLow() == null) {
                    if (toDecl.getHigh().getConnectorDeclaration() != fromDecl
                            .getHigh().getConnectorDeclaration()) {
                        ret = true;
                    }
                } else {
                    ret = isIncludedIn(fromDecl.getHigh(), toDecl.getLow());
                }
            }
        }

        return ret;
    }

    /** 
     * Determine if there is a edge between two priorities in
     * the atom priority graph
     * @param fromDecl the source of the potential edge
     * @param toDecl the destination of the potential edge
     * @return true if there is an edge from fromDecl to toDecl
     * @generated NOT
     */
    private boolean areConnected(AtomPriorityDeclaration fromDecl,
            AtomPriorityDeclaration toDecl) {
        boolean ret = false;

        AtomType holder = (AtomType) fromDecl.eContainer();

        assert (holder == (AtomType) toDecl.eContainer());

        /* WARNING:
         * Disallowed priorities of the form *:* < *:* are checked by
         * constraint atomPriorityHasAtMostOneWildcard of priorities.
         */
        if ((fromDecl.getLow() != null || fromDecl.getHigh() != null)
                && (toDecl.getLow() != null || toDecl.getHigh() != null)) {
            if (fromDecl.getHigh() == null) {
                if (toDecl.getLow() == null) {
                    for (PortDeclaration decl : holder
                            .getInternalPortDeclarations()) {
                        // check if exists a port matching both wildcards
                        if (decl != fromDecl.getLow()
                                && decl != toDecl.getHigh()) {
                            ret = true;
                            break;
                        }
                    }
                } else if (fromDecl.getLow() != toDecl.getLow()) {
                    ret = true;
                }
            } else {
                if (fromDecl.getHigh() == toDecl.getLow()) {
                    ret = true;
                } else if (toDecl.getLow() == null
                        && fromDecl.getHigh() != toDecl.getHigh()) {
                    ret = true;
                }
            }
        }

        return ret;
    }

    /**
     * Interface for graphs
     * @generated NOT
     */
    private interface PriorityGraph {
        public Set<AnnotatedEObject> getNodes();

        public Set<AnnotatedEObject> getSuccessors(AnnotatedEObject object);
    }

    /**
     * Implementation for graph of atom priorities
     * @generated NOT
     */
    class CompoundPriorityGraph implements PriorityGraph {
        CompoundPriorityGraph(CompoundType ct) {
            this.ct = ct;
        }

        public Set<AnnotatedEObject> getNodes() {
            Set<AnnotatedEObject> ret = new HashSet<AnnotatedEObject>();
            ret.addAll(ct.getPriorities());

            return ret;
        }

        public Set<AnnotatedEObject> getSuccessors(AnnotatedEObject object) {
            assert (getNodes().contains(object));
            assert (object instanceof CompoundPriorityDeclaration);

            Set<AnnotatedEObject> ret = new HashSet<AnnotatedEObject>();

            CompoundPriorityDeclaration priority = (CompoundPriorityDeclaration) object;
            CompoundType ct = (CompoundType) priority.eContainer();

            for (CompoundPriorityDeclaration p : ct.getPriorities()) {
                if (areConnected(priority, p)) {
                    ret.add(p);
                }
            }

            return ret;
        }

        private CompoundType ct;
    }

    /**
     * Implementation for graph of atom priorities
     * @generated NOT
     */
    class AtomPriorityGraph implements PriorityGraph {
        AtomPriorityGraph(AtomType at) {
            this.at = at;
        }

        public Set<AnnotatedEObject> getNodes() {
            Set<AnnotatedEObject> ret = new HashSet<AnnotatedEObject>();
            ret.addAll(at.getPriorities());

            return ret;
        }

        public Set<AnnotatedEObject> getSuccessors(AnnotatedEObject object) {
            assert (getNodes().contains(object));
            assert (object instanceof AtomPriorityDeclaration);

            Set<AnnotatedEObject> ret = new HashSet<AnnotatedEObject>();

            AtomPriorityDeclaration priority = (AtomPriorityDeclaration) object;

            for (AtomPriorityDeclaration p : at.getPriorities()) {
                if (areConnected(priority, p)) {
                    ret.add(p);
                }
            }

            return ret;
        }

        private AtomType at;
    }

    /**
     * Compute recursively all the cycles reachable from a given node in a graph
     * @param object the starting point of the research
     * @param graph the target graph
     * @param path the current searching path in the graph for the recursion
     * @return the set of cycles reachable from object
     * @generated NOT
     */
    private Set<List<AnnotatedEObject>> getAllCyclesFrom(
            AnnotatedEObject object, PriorityGraph graph,
            List<AnnotatedEObject> path) {
        Set<List<AnnotatedEObject>> ret = new HashSet<List<AnnotatedEObject>>();
        Set<AnnotatedEObject> successors = graph.getSuccessors(object);

        if (!successors.isEmpty()) {
            for (AnnotatedEObject successor : successors) {
                if (path.contains(successor)) {
                    // new cycle found
                    List<AnnotatedEObject> cycle = path
                            .subList(path.indexOf(successor), path.size());
                    ret.add(cycle);
                } else {
                    List<AnnotatedEObject> updatedPath = new ArrayList<AnnotatedEObject>();
                    updatedPath.addAll(path);
                    updatedPath.add(successor);

                    // recursive call from successor
                    ret.addAll(getAllCyclesFrom(successor, graph, updatedPath));
                }
            }
        }

        return ret;
    }

    /**
     * Compute all cycles in an DAG.
     * @param graph the target graph
     * @return the set of cycles
     * @generated NOT
     */
    private Set<List<AnnotatedEObject>> getAllCycles(PriorityGraph graph) {
        Set<List<AnnotatedEObject>> ret = new HashSet<List<AnnotatedEObject>>();

        for (AnnotatedEObject node : graph.getNodes()) {
            Set<List<AnnotatedEObject>> cyclesFromNode = getAllCyclesFrom(node,
                    graph, new ArrayList<AnnotatedEObject>());

            for (List<AnnotatedEObject> newCycle : cyclesFromNode) {
                boolean found = false;

                for (List<AnnotatedEObject> cycle : ret) {
                    if (cycle.containsAll(newCycle)
                            && newCycle.containsAll(cycle)) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    ret.add(newCycle);
                }
            }
        }

        return ret;
    }

    /**
     * Compute the annotated object minimizing its line start number
     * @param objects the target collection
     * @return an/the object of objects minimizing its line start number
     * @generated NOT
     */
    private AnnotatedEObject getFirst(List<AnnotatedEObject> objects) {
        AnnotatedEObject ret = null;
        int lineNumber = -1;

        for (AnnotatedEObject object : objects) {
            if (ret == null || object.getLineStart() < lineNumber) {
                ret = object;
                lineNumber = object.getLineStart();
            }
        }

        return ret;
    }

    /**
     * Return the number of guards involved in a given cycle
     * @param cycle the target cycle of priorities
     * @return the number of guards involved in the cycle
     * @generated NOT
     */
    private int numberOfGuards(List<AnnotatedEObject> cycle) {
        int ret = 0;

        for (AnnotatedEObject object : cycle) {
            if (object instanceof AtomPriorityDeclaration) {
                AtomPriorityDeclaration priority = (AtomPriorityDeclaration) object;

                if (priority.getGuard() != null) {
                    ret++;
                }
            } else if (object instanceof CompoundPriorityDeclaration) {
                CompoundPriorityDeclaration priority = (CompoundPriorityDeclaration) object;

                if (priority.getGuard() != null) {
                    ret++;
                }
            }
        }

        return ret;
    }

    /**
     * Determine whether a cycle should trigger a warning or an error.
     * We produce warning if the cycle has at least two guards.
     * @param cycle the target cycle of priorities
     * @return true if the cycle corresponds to warning only
     * @generated NOT
     */
    private boolean isWarning(List<AnnotatedEObject> cycle) {
        return numberOfGuards(cycle) > 1;
    }

    /**
     * Determine whether a cycle should trigger a warning or an error.
     * We produce warning if the cycle has at least two guards.
     * @param cycle1 the target cycle of priorities
     * @param cycle2 the 
     * @return true
     * @generated NOT
     */
    private List<AnnotatedEObject> keep(List<AnnotatedEObject> cycle1,
            List<AnnotatedEObject> cycle2) {
        List<AnnotatedEObject> ret = null;

        if (isWarning(cycle1) != isWarning(cycle2)) {
            if (!isWarning(cycle1)) {
                ret = cycle1;
            }
            if (!isWarning(cycle2)) {
                ret = cycle2;
            }
        } else {
            if (cycle1.size() <= cycle2.size()) {
                ret = cycle1;
            } else {
                ret = cycle2;
            }
        }

        assert (ret != null);

        return ret;
    }

    /**
     * Validates the checkForCyclesInPrioritiesInCompound constraint of '<em>Compound Type</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateCompoundType_checkForCyclesInPrioritiesInCompound(
            CompoundType compoundType, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        PriorityGraph compoundPriorityGraph = new CompoundPriorityGraph(
                compoundType);
        Set<List<AnnotatedEObject>> allCycles = getAllCycles(
                compoundPriorityGraph);

        Map<CompoundPriorityDeclaration, List<AnnotatedEObject>> errors = new HashMap<CompoundPriorityDeclaration, List<AnnotatedEObject>>();

        for (List<AnnotatedEObject> cycle : allCycles) {
            AnnotatedEObject object = getFirst(cycle);
            assert (object instanceof CompoundPriorityDeclaration);
            CompoundPriorityDeclaration priority = (CompoundPriorityDeclaration) object;

            List<AnnotatedEObject> previousCycle = errors.get(priority);

            if (previousCycle == null) {
                errors.put(priority, cycle);
            } else {
                errors.put(priority, keep(previousCycle, cycle));
            }
        }

        if (!errors.isEmpty()) {
            if (diagnostics != null) {
                for (Map.Entry<CompoundPriorityDeclaration, List<AnnotatedEObject>> entry : errors
                        .entrySet()) {
                    CompoundPriorityDeclaration priority = entry.getKey();
                    List<AnnotatedEObject> cycle = entry.getValue();

                    int level;

                    if (isWarning(cycle))
                        level = Diagnostic.WARNING;
                    else
                        level = Diagnostic.ERROR;

                    boolean priorityContradictMaximalProgress = false;

                    if (priority.getLow() != null
                            && priority.getHigh() != null) {
                        if (isIncludedIn(priority.getHigh(),
                                priority.getLow())) {
                            if (priority.getLow().getPortDeclarationReferences()
                                    .size() > priority.getHigh()
                                            .getPortDeclarationReferences()
                                            .size()) {
                                priorityContradictMaximalProgress = true;

                                // since we keep cycles of minimal size (according to keep())
                                // in this case the cycle  should be of size one
                                assert (cycle.size() == 1);
                                assert (priority == getFirst(cycle));
                            }
                        }
                    }

                    if (priorityContradictMaximalProgress) {
                        diagnostics.add(createDiagnostic(level,
                                DIAGNOSTIC_SOURCE, 0,
                                "_UI_GenericConstraint_diagnostic",
                                new Object[] {
                                        "priorityContradictMaximalProgress",
                                        getObjectLabel(compoundType, context) },
                                new Object[] { priority,
                                        ErrorCodeEnum.priorityContradictMaximalProgress },
                                context));
                    } else {
                        diagnostics.add(createDiagnostic(level,
                                DIAGNOSTIC_SOURCE, 0,
                                "_UI_GenericConstraint_diagnostic",
                                new Object[] {
                                        "checkForCyclesInPrioritiesInCompound",
                                        getObjectLabel(compoundType, context) },
                                new Object[] { priority,
                                        ErrorCodeEnum.checkForCyclesInPrioritiesInCompound,
                                        cycle },
                                context));
                    }
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
    public boolean validateConnectorType(ConnectorType connectorType,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) connectorType,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) connectorType, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms((EObject) connectorType,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) connectorType, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) connectorType, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves((EObject) connectorType,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) connectorType, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) connectorType,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique((EObject) connectorType,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorType_interactionDefinedIfExportPortWithData(
                    connectorType, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorType_noDuplicatedInteractionAction(
                    connectorType, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorType_checkDownWhenNoDataInConnectorPort(
                    connectorType, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorType_missingInteractionIfExportPortWithData(
                    connectorType, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorType_checkUninitializedVariablesInConnectorDataDeclaration(
                    connectorType, diagnostics, context);
        return result;
    }

    /**
     * Validates the interactionDefinedIfExportPortWithData constraint of '<em>Connector Type</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorType_interactionDefinedIfExportPortWithData(
            ConnectorType connectorType, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        boolean ok = true;

        boolean hasExportPortWithData = false;

        if (connectorType.getExportedPortDeclaration() != null) {
            hasExportPortWithData = !connectorType.getExportedPortDeclaration()
                    .getDataParameters().isEmpty();
        }

        boolean hasAtLeastOneInteractionAction = !connectorType
                .getInteractions().isEmpty();

        ok = !(hasExportPortWithData && !hasAtLeastOneInteractionAction);

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "interactionDefinedIfExportPortWithData",
                                getObjectLabel(connectorType, context) },
                        new Object[] { connectorType,
                                ErrorCodeEnum.interactionDefinedIfExportPortWithData },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the noDuplicatedInteractionAction constraint of '<em>Connector Type</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorType_noDuplicatedInteractionAction(
            ConnectorType connectorType, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        boolean ok = true;
        HashSet<Set<ConnectorPortParameterDeclaration>> all = new HashSet<Set<ConnectorPortParameterDeclaration>>();

        ConnectorInteractionAction faulty_action = null;

        for (ConnectorInteractionAction ci : connectorType.getInteractions()) {
            HashSet<ConnectorPortParameterDeclaration> s = new HashSet<ConnectorPortParameterDeclaration>(
                    ci.getOnPorts());
            if (!all.add(s)) {
                ok = false;
                faulty_action = ci;
                break;
            }
        }
        if (!ok && diagnostics != null) {
            diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                    DIAGNOSTIC_SOURCE, 0, "_UI_GenericConstraint_diagnostic",
                    new Object[] { "noDuplicatedInteractionAction",
                            getObjectLabel(connectorType, context) },
                    new Object[] { faulty_action,
                            ErrorCodeEnum.noDuplicatedInteractionAction },
                    context));
        }
        return ok;
    }

    /**
     * Validates the checkDownWhenNoDataInConnectorPort constraint of '<em>Connector Type</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorType_checkDownWhenNoDataInConnectorPort(
            ConnectorType connectorType, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        boolean noPortParameters = true;
        List<ConnectorInteractionAction> faulty_down = new ArrayList<ConnectorInteractionAction>();

        for (ConnectorPortParameterDeclaration pt : connectorType.getPorts()) {

            if (!pt.getPortType().getDataParameterDeclarations().isEmpty()) {
                noPortParameters = false;
                break;
            }
        }
        boolean empty = false;
        if (noPortParameters) {
            for (ConnectorInteractionAction ci : connectorType
                    .getInteractions()) {
                if (!ci.getDown().isEmpty()) {
                    faulty_down.add(ci);
                    empty = true;
                }
            }
        }
        boolean ok = !empty;
        if (!ok && diagnostics != null) {
            for (ConnectorInteractionAction cia : faulty_down) {
                diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "checkDownWhenNoDataInConnectorPort",
                                getObjectLabel(connectorType, context) },
                        new Object[] { cia,
                                ErrorCodeEnum.checkDownWhenNoDataInConnectorPort },
                        context));
            }
        }
        return ok;
    }

    /**
     * Determine whether a nested definition has trigger(s) or not.
     * @generated NOT
     */
    private boolean hasTrigger(
            ConnectorInteractionNestedDefinition nestedDefinition) {
        boolean ret = false;

        for (ConnectorInteractionDefinition subDef : nestedDefinition
                .getSubInteractions()) {
            if (subDef.isQuoted()) {
                ret = true;
                break;
            }
        }

        return ret;
    }

    /**
     * Count the number of interactions meeting the defined expression.
     * @generated NOT
     */
    public int countDefinedInteractions(
            ConnectorInteractionDefinition definition) {
        int ret = 1;

        if (definition instanceof ConnectorInteractionNestedDefinition) {
            ConnectorInteractionNestedDefinition nestedDefinition = (ConnectorInteractionNestedDefinition) definition;

            if (hasTrigger(nestedDefinition)) {
                // count all interactions, including interactions without any trigger, empty interaction, etc.
                for (ConnectorInteractionDefinition subDef : nestedDefinition
                        .getSubInteractions()) {
                    ret = ret * (1 + countDefinedInteractions(subDef));
                }

                // subtract all interactions without a trigger
                int noTrigger = 1;

                for (ConnectorInteractionDefinition subDef : nestedDefinition
                        .getSubInteractions()) {
                    if (!subDef.isQuoted()) {
                        noTrigger = noTrigger
                                * (1 + countDefinedInteractions(subDef));
                    }
                }

                ret = ret - noTrigger;
            } else {
                for (ConnectorInteractionDefinition subDef : nestedDefinition
                        .getSubInteractions()) {
                    ret = ret * countDefinedInteractions(subDef);
                }
            }
        } else {
            assert definition instanceof ConnectorInteractionPortReference;
        }

        return ret;
    }

    /**
     * Validates the missingInteractionIfExportPortWithData constraint of '<em>Connector Type</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorType_missingInteractionIfExportPortWithData(
            ConnectorType connectorType, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        int interactions = countDefinedInteractions(
                connectorType.getInteractionDefinition());
        boolean ok = true;

        boolean hasExportPortWithData = false;

        if (connectorType.getExportedPortDeclaration() != null) {
            hasExportPortWithData = !connectorType.getExportedPortDeclaration()
                    .getDataParameters().isEmpty();
        }

        boolean hasAllInteractionsOrNoInteraction = interactions == connectorType
                .getInteractions().size()
                || connectorType.getInteractions().isEmpty();

        ok = !(hasExportPortWithData && !hasAllInteractionsOrNoInteraction);

        if (!ok && diagnostics != null) {
            diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                    DIAGNOSTIC_SOURCE, 0, "_UI_GenericConstraint_diagnostic",
                    new Object[] { "missingInteractionIfExportPortWithData",
                            getObjectLabel(connectorType, context) },
                    new Object[] { connectorType,
                            ErrorCodeEnum.missingInteractionIfExportPortWithData },
                    context));
        }
        return ok;
    }

    /**
     * Validates the checkUninitializedVariables constraint of '<em>Connector Type</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorType_checkUninitializedVariablesInConnectorDataDeclaration(
            ConnectorType connectorType, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        // start with an empty list of erroneous expressions
        List<DirectDataDeclarationReferenceExpression> errors = new ArrayList<DirectDataDeclarationReferenceExpression>();

        // compute the initial set of uninitialized variables, i.e.
        // atom parameters as well as constant data of the package
        // are considered initialized
        Set<DataDeclaration> uninitialized = new HashSet<DataDeclaration>();
        uninitialized.addAll(connectorType.getDataDeclarations());

        // /!\ WARNING: order is critical since uninitialized is updated
        for (ConnectorDataDeclaration dataDecl : connectorType
                .getDataDeclarations()) {
            if (dataDecl.getValue() != null) {
                // first, check uninitialized variables
                checkUninitializedVariables(dataDecl.getValue(), uninitialized,
                        errors);

                // then remove dataDecl from the uninitialized variables
                uninitialized.remove(dataDecl);
            }
        }

        if (!errors.isEmpty()) {
            if (diagnostics != null) {
                for (DirectDataDeclarationReferenceExpression ref : errors) {
                    diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                            DIAGNOSTIC_SOURCE, 0,
                            "_UI_GenericConstraint_diagnostic",
                            new Object[] { "", getObjectLabel(ref, context) },
                            new Object[] { ref,
                                    ErrorCodeEnum.uninitializedVariableInConnectorDataDeclaration,
                                    ref },
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
    public boolean validatePortType(PortType portType,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) portType, diagnostics,
                context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateBipType(BipType bipType, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) bipType, diagnostics,
                context);
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

} //TypesValidator
