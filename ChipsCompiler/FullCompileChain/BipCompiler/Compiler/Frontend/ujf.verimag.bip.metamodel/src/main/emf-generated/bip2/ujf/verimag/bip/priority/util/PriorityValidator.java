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

package bip2.ujf.verimag.bip.priority.util;

import bip2.ujf.verimag.bip.actionlang.ValuedExpression;
import bip2.ujf.verimag.bip.connector.ConnectorFactory;
import bip2.ujf.verimag.bip.connector.ConnectorDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorPortParameterDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionDefinition;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionNestedDefinition;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionPortReference;
import bip2.ujf.verimag.bip.connector.util.ConnectorValidator;

import bip2.ujf.verimag.bip.port.PortDeclaration;
import bip2.ujf.verimag.bip.port.PortDeclarationReferenceParameter;
import bip2.ujf.verimag.bip.port.SubPortDeclarationReference;
import bip2.ujf.verimag.bip.priority.*;
import bip2.ujf.verimag.bip.types.CompoundType;
import bip2.ujf.verimag.bip.types.ConnectorType;

import java.util.HashSet;
import java.util.Map;
import java.util.Queue;
import java.util.LinkedList;
import java.util.List;
import java.util.ArrayList;
import java.util.Set;

import org.eclipse.emf.common.util.BasicEList;
import org.eclipse.emf.common.util.Diagnostic;
import org.eclipse.emf.common.util.DiagnosticChain;
import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.common.util.ResourceLocator;

import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;

import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.EObjectValidator;
import org.eclipse.emf.ecore.util.EcoreEList;
import org.eclipse.emf.ecore.util.EcoreUtil;

import ujf.verimag.bip.error.message.ErrorCodeEnum;

/**
 * <!-- begin-user-doc -->
 * The <b>Validator</b> for the model.
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.priority.PriorityPackage
 * @generated
 */
public class PriorityValidator extends EObjectValidator {
    /**
     * The cached model package
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static final PriorityValidator INSTANCE = new PriorityValidator();

    /**
     * A constant for the {@link org.eclipse.emf.common.util.Diagnostic#getSource() source} of diagnostic {@link org.eclipse.emf.common.util.Diagnostic#getCode() codes} from this package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.eclipse.emf.common.util.Diagnostic#getSource()
     * @see org.eclipse.emf.common.util.Diagnostic#getCode()
     * @generated
     */
    public static final String DIAGNOSTIC_SOURCE = "bip2.ujf.verimag.bip.priority";

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
    public PriorityValidator() {
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
        return PriorityPackage.eINSTANCE;
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
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION:
            return validateCompoundPriorityDeclaration(
                    (CompoundPriorityDeclaration) value, diagnostics, context);
        case PriorityPackage.CONNECTOR_INTERACTION:
            return validateConnectorInteraction((ConnectorInteraction) value,
                    diagnostics, context);
        case PriorityPackage.ATOM_PRIORITY_DECLARATION:
            return validateAtomPriorityDeclaration(
                    (AtomPriorityDeclaration) value, diagnostics, context);
        default:
            return true;
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateCompoundPriorityDeclaration(
            CompoundPriorityDeclaration compoundPriorityDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment(
                (EObject) compoundPriorityDeclaration, diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) compoundPriorityDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) compoundPriorityDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) compoundPriorityDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) compoundPriorityDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) compoundPriorityDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) compoundPriorityDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) compoundPriorityDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) compoundPriorityDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validateCompoundPriorityDeclaration_compoundPriorityHasAtMostOneWildcard(
                    compoundPriorityDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateCompoundPriorityDeclaration_compoundPriorityInvolvesOnlyTopLevelConnectors(
                    compoundPriorityDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateCompoundPriorityDeclaration_priorityDuplicateMaximalProgress(
                    compoundPriorityDeclaration, diagnostics, context);
        return result;
    }

    /**
     * Validates the compoundPriorityHasAtMostOneWildcard constraint of '<em>Compound Priority Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateCompoundPriorityDeclaration_compoundPriorityHasAtMostOneWildcard(
            CompoundPriorityDeclaration compoundPriorityDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = !((compoundPriorityDeclaration.getHigh() == null)
                && (compoundPriorityDeclaration.getLow() == null));

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "compoundPriorityHasAtMostOneWildcard",
                                getObjectLabel(compoundPriorityDeclaration,
                                        context) },
                        new Object[] { compoundPriorityDeclaration,
                                ErrorCodeEnum.compoundPriorityHasAtMostOneWildcard },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Useful for compoundPriorityInvolvesOnlyTopLevelConnectors constraint of '<em>Compound Priority Declaration</em>'.
     * It checks if an interaction belongs to a top level connector or not
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean isTopLevel(ConnectorInteraction interaction) {
        boolean ret = true;

        // for interactions of the form *:*, interaction is 'null'
        if (interaction != null) {
            // the connector to be check for being top level of not (i.e. connected
            // to other connectors or not)
            ConnectorDeclaration connector = interaction
                    .getConnectorDeclaration();
            CompoundType holder = (CompoundType) connector.eContainer();

            // check all connectors involved in parameters of connector declarations
            for (ConnectorDeclaration decl : holder
                    .getConnectorDeclarations()) {
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
        }

        return ret;
    }

    /**
     * Validates the compoundPriorityInvolvesOnlyTopLevelConnectors constraint of '<em>Compound Priority Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateCompoundPriorityDeclaration_compoundPriorityInvolvesOnlyTopLevelConnectors(
            CompoundPriorityDeclaration compoundPriorityDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        // both interactions should be from top level connectors (or *:*)
        boolean ok = isTopLevel(compoundPriorityDeclaration.getLow())
                && isTopLevel(compoundPriorityDeclaration.getHigh());

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] {
                                "compoundPriorityInvolvesOnlyTopLevelConnectors",
                                getObjectLabel(compoundPriorityDeclaration,
                                        context) },
                        new Object[] { compoundPriorityDeclaration,
                                ErrorCodeEnum.compoundPriorityInvolvesOnlyTopLevelConnectors },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the priorityDuplicateMaximalProgress constraint of '<em>Compound Priority Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateCompoundPriorityDeclaration_priorityDuplicateMaximalProgress(
            CompoundPriorityDeclaration compoundPriorityDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = true;

        if (compoundPriorityDeclaration.getLow() != null
                && compoundPriorityDeclaration.getHigh() != null) {
            if (compoundPriorityDeclaration.getLow()
                    .getConnectorDeclaration() == compoundPriorityDeclaration
                            .getHigh().getConnectorDeclaration()) {
                boolean inclusion = true;

                for (SubPortDeclarationReference portRef : compoundPriorityDeclaration
                        .getLow().getPortDeclarationReferences()) {
                    boolean found = false;

                    for (SubPortDeclarationReference targetPortRef : compoundPriorityDeclaration
                            .getHigh().getPortDeclarationReferences()) {
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
                        inclusion = false;
                        break;
                    }
                }

                // if low interaction is strictly included in high interaction, max progress is duplicated
                if (inclusion && compoundPriorityDeclaration.getLow()
                        .getPortDeclarationReferences()
                        .size() < compoundPriorityDeclaration.getHigh()
                                .getPortDeclarationReferences().size()) {
                    ok = false;
                }
            }
        }

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "priorityDuplicateMaximalProgress",
                                getObjectLabel(compoundPriorityDeclaration,
                                        context) },
                        new Object[] { compoundPriorityDeclaration,
                                ErrorCodeEnum.priorityDuplicateMaximalProgress },
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
    public boolean validateConnectorInteraction(
            ConnectorInteraction connectorInteraction,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) connectorInteraction,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) connectorInteraction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) connectorInteraction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) connectorInteraction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) connectorInteraction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) connectorInteraction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) connectorInteraction,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) connectorInteraction,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) connectorInteraction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorInteraction_portReferencesOnCorrectConnectorDeclaration(
                    connectorInteraction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorInteraction_noDuplicatedPortReferenceInConnectorInteraction(
                    connectorInteraction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorInteraction_interactionIsDefinedInConnector(
                    connectorInteraction, diagnostics, context);
        return result;
    }

    /**
     * Validates the portReferencesOnCorrectConnectorDeclaration constraint of '<em>Connector Interaction</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorInteraction_portReferencesOnCorrectConnectorDeclaration(
            ConnectorInteraction connectorInteraction,
            DiagnosticChain diagnostics, Map<Object, Object> context) {

        boolean ok = true;

        ConnectorDeclaration cd = connectorInteraction
                .getConnectorDeclaration();

        for (SubPortDeclarationReference spdr : connectorInteraction
                .getPortDeclarationReferences()) {
            boolean found = false;

            for (PortDeclarationReferenceParameter pdrp : cd
                    .getPortParameters()) {
                SubPortDeclarationReference spdr_other = pdrp
                        .getSubPortDeclarationReference();

                if (spdr.getComponentDeclaration() != null) {
                    if (spdr_other.getComponentDeclaration() != null) {
                        if (spdr_other.getComponentDeclaration()
                                .equals(spdr.getComponentDeclaration())
                                && spdr_other.getForwardPortDeclaration()
                                        .equals(spdr
                                                .getForwardPortDeclaration())) {
                            found = true;
                            break;
                        }
                    }
                } else if (spdr.getConnectorDeclaration() != null) {
                    if (spdr_other.getConnectorDeclaration() != null) {
                        if (spdr_other.getConnectorDeclaration()
                                .equals(spdr.getConnectorDeclaration())
                                && spdr_other.getForwardPortDeclaration()
                                        .equals(spdr
                                                .getForwardPortDeclaration())) {
                            found = true;
                            break;
                        }
                    }
                } else {
                    ok = false;
                    break;
                }
            }

            if (!found) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] {
                                "portReferencesOnCorrectConnectorDeclaration",
                                getObjectLabel(connectorInteraction, context) },
                        new Object[] { connectorInteraction,
                                ErrorCodeEnum.portReferencesOnCorrectConnectorDeclaration },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the noDuplicatedPortReferenceInConnectorInteraction constraint of '<em>Connector Interaction</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorInteraction_noDuplicatedPortReferenceInConnectorInteraction(
            ConnectorInteraction connectorInteraction,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = true;

        for (SubPortDeclarationReference spdr : connectorInteraction
                .getPortDeclarationReferences()) {
            int c = 0;
            for (SubPortDeclarationReference spdr2 : connectorInteraction
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
                        new Object[] {
                                "noDuplicatedPortReferenceInConnectorInteraction",
                                getObjectLabel(connectorInteraction, context) },
                        new Object[] { connectorInteraction,
                                ErrorCodeEnum.noDuplicatedPortReferenceInConnectorInteraction },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the interactionIsDefinedInConnector constraint of '<em>Connector Interaction</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorInteraction_interactionIsDefinedInConnector(
            ConnectorInteraction connectorInteraction,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = true;

        ConnectorDeclaration cd = connectorInteraction
                .getConnectorDeclaration();
        ConnectorType ct = cd.getType();

        int interaction_size = connectorInteraction
                .getPortDeclarationReferences().size();
        int connector_param_size = ct.getPorts().size();
        EList<ConnectorPortParameterDeclaration> ports = new BasicEList<ConnectorPortParameterDeclaration>();
        // if interaction not maximal
        // unicity of port may not be OK, but if so,
        // the other constraint will be triggered.
        if (interaction_size != connector_param_size && interaction_size != 0) {
            for (SubPortDeclarationReference spdr : connectorInteraction
                    .getPortDeclarationReferences()) {
                boolean b = false;
                int idx;
                for (idx = 0; idx < cd.getPortParameters().size(); idx++) {
                    SubPortDeclarationReference spdr_decl = cd
                            .getPortParameters().get(idx)
                            .getSubPortDeclarationReference();
                    b = spdr.getComponentDeclaration() == spdr_decl
                            .getComponentDeclaration()
                            && spdr.getConnectorDeclaration() == spdr_decl
                                    .getConnectorDeclaration()
                            && spdr.getForwardPortDeclaration() == spdr_decl
                                    .getForwardPortDeclaration();
                    if (b)
                        break;
                }
                if (!b || idx >= ct.getPorts().size()) {
                    // we reached a faulty state where port ref can't be found.
                    // Most probably, another contraint should take care of that.
                    return true;
                }
                ConnectorPortParameterDeclaration cppd = ct.getPorts().get(idx);
                ports.add(cppd);
            }
            ok = ct.isDefined(ports);
        }
        if (!ok && diagnostics != null) {
            diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                    DIAGNOSTIC_SOURCE, 0, "_UI_GenericConstraint_diagnostic",
                    new Object[] { "interactionIsDefinedInConnector",
                            getObjectLabel(connectorInteraction, context) },
                    new Object[] { connectorInteraction,
                            ErrorCodeEnum.interactionIsDefinedInConnector },
                    context));
        }
        return ok;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateAtomPriorityDeclaration(
            AtomPriorityDeclaration atomPriorityDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) atomPriorityDeclaration,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) atomPriorityDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) atomPriorityDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) atomPriorityDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) atomPriorityDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) atomPriorityDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) atomPriorityDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) atomPriorityDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) atomPriorityDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateAtomPriorityDeclaration_atomPriorityHasAtMostOneWildcard(
                    atomPriorityDeclaration, diagnostics, context);
        return result;
    }

    /**
     * Validates the atomPriorityHasAtMostOneWildcard constraint of '<em>Atom Priority Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateAtomPriorityDeclaration_atomPriorityHasAtMostOneWildcard(
            AtomPriorityDeclaration atomPriorityDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = !(atomPriorityDeclaration.getLow() == null
                && atomPriorityDeclaration.getHigh() == null);

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "atomPriorityHasAtMostOneWildcard",
                                getObjectLabel(atomPriorityDeclaration,
                                        context) },
                        new Object[] { atomPriorityDeclaration,
                                ErrorCodeEnum.atomPriorityHasAtMostOneWildcard },
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

} //PriorityValidator
