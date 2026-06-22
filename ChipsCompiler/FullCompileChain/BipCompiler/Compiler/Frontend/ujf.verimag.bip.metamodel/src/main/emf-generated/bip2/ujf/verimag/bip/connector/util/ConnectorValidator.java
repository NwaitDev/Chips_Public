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

package bip2.ujf.verimag.bip.connector.util;

import bip2.ujf.verimag.bip.actionlang.AssignmentExpression;
import bip2.ujf.verimag.bip.actionlang.BinaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.Expression;
import bip2.ujf.verimag.bip.actionlang.FunctionCallExpression;
import bip2.ujf.verimag.bip.actionlang.IfThenElseExpression;
import bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.UnaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.ValuedExpression;
import bip2.ujf.verimag.bip.component.compound.CompoundExportPortDeclaration;
import bip2.ujf.verimag.bip.connector.*;
import bip2.ujf.verimag.bip.data.util.DataValidator;
import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataDeclarationReferenceDataParameter;

import bip2.ujf.verimag.bip.port.PortDeclaration;
import bip2.ujf.verimag.bip.port.PortDeclarationReferenceParameter;
import bip2.ujf.verimag.bip.port.SubPortDeclarationReference;
import bip2.ujf.verimag.bip.port.util.PortValidator;
import bip2.ujf.verimag.bip.types.AtomType;
import bip2.ujf.verimag.bip.types.CompoundType;
import bip2.ujf.verimag.bip.types.ConnectorType;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.HashSet;
import java.util.List;
import java.util.ArrayList;

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
 * @see bip2.ujf.verimag.bip.connector.ConnectorPackage
 * @generated
 */
public class ConnectorValidator extends EObjectValidator {
    /**
     * The cached model package
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static final ConnectorValidator INSTANCE = new ConnectorValidator();

    /**
     * A constant for the {@link org.eclipse.emf.common.util.Diagnostic#getSource() source} of diagnostic {@link org.eclipse.emf.common.util.Diagnostic#getCode() codes} from this package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.eclipse.emf.common.util.Diagnostic#getSource()
     * @see org.eclipse.emf.common.util.Diagnostic#getCode()
     * @generated
     */
    public static final String DIAGNOSTIC_SOURCE = "bip2.ujf.verimag.bip.connector";

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
    public ConnectorValidator() {
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
        return ConnectorPackage.eINSTANCE;
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
        case ConnectorPackage.CONNECTOR_DECLARATION:
            return validateConnectorDeclaration((ConnectorDeclaration) value,
                    diagnostics, context);
        case ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION:
            return validateConnectorPortParameterDeclaration(
                    (ConnectorPortParameterDeclaration) value, diagnostics,
                    context);
        case ConnectorPackage.CONNECTOR_EXPORTED_PORT_DECLARATION:
            return validateConnectorExportedPortDeclaration(
                    (ConnectorExportedPortDeclaration) value, diagnostics,
                    context);
        case ConnectorPackage.CONNECTOR_DATA_DECLARATION:
            return validateConnectorDataDeclaration(
                    (ConnectorDataDeclaration) value, diagnostics, context);
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION:
            return validateConnectorInteractionAction(
                    (ConnectorInteractionAction) value, diagnostics, context);
        case ConnectorPackage.CONNECTOR_INTERACTION_DEFINITION:
            return validateConnectorInteractionDefinition(
                    (ConnectorInteractionDefinition) value, diagnostics,
                    context);
        case ConnectorPackage.CONNECTOR_INTERACTION_PORT_REFERENCE:
            return validateConnectorInteractionPortReference(
                    (ConnectorInteractionPortReference) value, diagnostics,
                    context);
        case ConnectorPackage.CONNECTOR_INTERACTION_NESTED_DEFINITION:
            return validateConnectorInteractionNestedDefinition(
                    (ConnectorInteractionNestedDefinition) value, diagnostics,
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
    public boolean validateConnectorDeclaration(
            ConnectorDeclaration connectorDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) connectorDeclaration,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) connectorDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) connectorDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) connectorDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) connectorDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) connectorDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) connectorDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) connectorDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) connectorDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorDeclaration_hasCorrectNumberOfPortParameters(
                    connectorDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorDeclaration_connectorDeclarationHasnoDuplicatedPortReferenceParameter(
                    connectorDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorDeclaration_connectorHasExportPortBound(
                    connectorDeclaration, diagnostics, context);
        return result;
    }

    /**
     * Validates the hasCorrectNumberOfPortParameters constraint of '<em>Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorDeclaration_hasCorrectNumberOfPortParameters(
            ConnectorDeclaration connectorDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {

        int decl_size = connectorDeclaration.getPortParameters().size();
        int type_size = connectorDeclaration.getType().getPorts().size();

        boolean ok = decl_size == type_size;

        if (!ok && diagnostics != null) {
            diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                    DIAGNOSTIC_SOURCE, 0, "_UI_GenericConstraint_diagnostic",
                    new Object[] { "hasCorrectNumberOfPortParameters",
                            getObjectLabel(connectorDeclaration, context) },
                    new Object[] { connectorDeclaration,
                            ErrorCodeEnum.hasCorrectNumberOfPortParameters },
                    context));
        }
        return ok;
    }

    /**
     * Validates the connectorDeclarationHasnoDuplicatedPortReferenceParameter constraint of '<em>Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorDeclaration_connectorDeclarationHasnoDuplicatedPortReferenceParameter(
            ConnectorDeclaration connectorDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = true;
        HashMap<String, String> map = new HashMap<String, String>();
        for (PortDeclarationReferenceParameter p : connectorDeclaration
                .getPortParameters()) {
            SubPortDeclarationReference spdr = p
                    .getSubPortDeclarationReference();
            String n = spdr.getConnectorDeclaration() != null
                    ? spdr.getConnectorDeclaration().getName()
                    : spdr.getComponentDeclaration().getName(),
                    frwd = spdr.getForwardPortDeclaration().getName();
            ok = !map.containsKey(n) || !map.get(n).equals(frwd);
            if (!ok) {
                break;
            } else {
                /*
                 *  BIG FAT WARNING
                 *  THIS WILL **NOT** DETECT THAT THE SAME COMPONENT IS CONNECTED
                 *  TWICE !!
                 *
                 *  I REPEAT: IT WON'T DETECT SAME COMPONENT CONNECTED TWICE!
                 */
                map.put(n, frwd);
            }
        }

        if (!ok && diagnostics != null) {
            diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                    DIAGNOSTIC_SOURCE, 0, "_UI_GenericConstraint_diagnostic",
                    new Object[] {
                            "connectorDeclarationHasnoDuplicatedPortReferenceParameter",
                            getObjectLabel(connectorDeclaration, context) },
                    new Object[] { connectorDeclaration,
                            ErrorCodeEnum.connectorDeclarationHasnoDuplicatedPortReferenceParameter },
                    context));
        }
        return ok;
    }

    /**
     * Validates the connectorHasExportPortBound constraint of '<em>Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorDeclaration_connectorHasExportPortBound(
            ConnectorDeclaration connectorDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = false;

        PortDeclaration epd = connectorDeclaration.getType()
                .getExportedPortDeclaration();

        if (epd == null) {
            // nothing to check here
            ok = true;
        } else {
            /*
             * Get the parent, which must be a compound type:
             *  - list all connector and see if one of them is connecting us 
             *  - list all exported port and see if we are getting exported
             * 
             * if nothing is found, we are not bound. This is not the end of the
             * world but everything depending on this connector can be
             * considered 'dead code'
             */
            String epd_name = epd.getName();
            String conn_name = connectorDeclaration.getName();

            CompoundType ct = (CompoundType) connectorDeclaration.eContainer();

            for (ConnectorDeclaration cd : ct.getConnectorDeclarations()) {
                for (PortDeclarationReferenceParameter cdrp : cd
                        .getPortParameters()) {
                    if (cdrp.getSubPortDeclarationReference()
                            .getConnectorDeclaration() != null) {
                        String b_c_name = cdrp.getSubPortDeclarationReference()
                                .getConnectorDeclaration().getName();
                        String b_epd_name = cdrp
                                .getSubPortDeclarationReference()
                                .getForwardPortDeclaration().getName();
                        ok = b_c_name.equals(conn_name)
                                && b_epd_name.equals(epd_name);

                        if (ok)
                            break;
                    }
                    if (ok)
                        break;
                }
                if (ok)
                    break;
            }

            // no luck with connector, check exported ports
            if (!ok) {
                for (CompoundExportPortDeclaration cepd : ct
                        .getExportPortDeclarations()) {
                    for (SubPortDeclarationReference spdr : cepd
                            .getPortDeclarationReferences()) {
                        if (spdr.getConnectorDeclaration() != null) {
                            String b_c_name = spdr.getConnectorDeclaration()
                                    .getName();
                            String b_epd_name = spdr.getForwardPortDeclaration()
                                    .getName();
                            ok = b_c_name.equals(conn_name)
                                    && b_epd_name.equals(epd_name);
                            break;
                        }
                    }
                    if (ok)
                        break;
                }
            }
        }

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "connectorHasExportPortBound",
                                getObjectLabel(connectorDeclaration, context) },
                        new Object[] { connectorDeclaration,
                                ErrorCodeEnum.connectorHasExportPortBound },
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
    public boolean validateConnectorPortParameterDeclaration(
            ConnectorPortParameterDeclaration connectorPortParameterDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment(
                (EObject) connectorPortParameterDeclaration, diagnostics,
                context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) connectorPortParameterDeclaration, diagnostics,
                context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) connectorPortParameterDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) connectorPortParameterDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) connectorPortParameterDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) connectorPortParameterDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_UniqueID(
                    (EObject) connectorPortParameterDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) connectorPortParameterDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) connectorPortParameterDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= portValidator
                    .validatePortDeclaration_hasCorrectNumberOfDataParameters(
                            connectorPortParameterDeclaration, diagnostics,
                            context);
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateConnectorExportedPortDeclaration(
            ConnectorExportedPortDeclaration connectorExportedPortDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment(
                (EObject) connectorExportedPortDeclaration, diagnostics,
                context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) connectorExportedPortDeclaration, diagnostics,
                context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) connectorExportedPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) connectorExportedPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) connectorExportedPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) connectorExportedPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_UniqueID(
                    (EObject) connectorExportedPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) connectorExportedPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) connectorExportedPortDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= portValidator
                    .validatePortDeclaration_hasCorrectNumberOfDataParameters(
                            connectorExportedPortDeclaration, diagnostics,
                            context);
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateConnectorDataDeclaration(
            ConnectorDataDeclaration connectorDataDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) connectorDataDeclaration,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) connectorDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) connectorDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) connectorDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) connectorDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) connectorDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) connectorDataDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) connectorDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) connectorDataDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= dataValidator
                    .validateExplicitDataDeclaration_hasInitializationIfConst(
                            connectorDataDeclaration, diagnostics, context);
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateConnectorInteractionAction(
            ConnectorInteractionAction connectorInteractionAction,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment(
                (EObject) connectorInteractionAction, diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) connectorInteractionAction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) connectorInteractionAction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) connectorInteractionAction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) connectorInteractionAction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) connectorInteractionAction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) connectorInteractionAction,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) connectorInteractionAction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) connectorInteractionAction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorInteractionAction_onPortInConnectorParameters(
                    connectorInteractionAction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorInteractionAction_upDoesNotContainExternalSubDataRefOnLHSAssignments(
                    connectorInteractionAction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorInteractionAction_connectorActionNotEmpty(
                    connectorInteractionAction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorInteractionAction_noUpIfNoExportedPort(
                    connectorInteractionAction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorInteractionAction_triggerPortsValidWrtDefine(
                    connectorInteractionAction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorInteractionAction_missingUpForExportedPort(
                    connectorInteractionAction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorInteractionAction_hasNoVariableModifiedBetweenUpAndDown(
                    connectorInteractionAction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorInteractionAction_checkUninitializedVariablesOfConnectorInteractionAction(
                    connectorInteractionAction, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorInteractionAction_checkUninitializedVariablesExportedByPortOfConnector(
                    connectorInteractionAction, diagnostics, context);
        return result;
    }

    /**
     * Validates the onPortInConnectorParameters constraint of '<em>Interaction Action</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorInteractionAction_onPortInConnectorParameters(
            ConnectorInteractionAction connectorInteractionAction,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        // check that both container are the same.
        boolean ok = true;

        // for (ConnectorPortParameterDeclaration cppd : connectorInteractionAction
        //         .getOnPorts()) {
        //     ok &= cppd.eContainer().equals(
        //             connectorInteractionAction.eContainer());
        // }

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "onPortInConnectorParameters",
                                getObjectLabel(connectorInteractionAction,
                                        context) },
                        new Object[] { connectorInteractionAction,
                                ErrorCodeEnum.onPortInConnectorParameters },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Used for by validation of the upDoesNotContainExternalSubDataRefOnLHSAssignments
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    private boolean validateConnectorInteractionAction_upDoesNotContainExternalSubDataRefOnLHSAssignments(
            ConnectorType ct, Expression expression) {
        boolean ok = true;

        Set<PortDeclaration> ports = new HashSet<PortDeclaration>(
                ct.getPorts());

        if (expression instanceof AssignmentExpression) {
            AssignmentExpression ae = (AssignmentExpression) expression;

            if (ae.getLhs() instanceof SubDataDeclarationReferenceExpression) {
                SubDataDeclarationReferenceExpression sddr = (SubDataDeclarationReferenceExpression) ae
                        .getLhs();

                PortDeclaration pd = sddr.getSubDataDeclarationRef()
                        .getPortDeclaration();

                if (ports.contains(pd)) {
                    ok = false;
                }
            }
        } else if (expression instanceof IfThenElseExpression) {
            IfThenElseExpression ite = (IfThenElseExpression) expression;

            Expression condition = ite.getCondition();

            if (!validateConnectorInteractionAction_upDoesNotContainExternalSubDataRefOnLHSAssignments(
                    ct, condition)) {
                ok = false;
            }

            for (Expression e : ite.getThen()) {
                if (!validateConnectorInteractionAction_upDoesNotContainExternalSubDataRefOnLHSAssignments(
                        ct, e)) {
                    ok = false;
                    break;
                }
            }

            for (Expression e : ite.getElse()) {
                if (!validateConnectorInteractionAction_upDoesNotContainExternalSubDataRefOnLHSAssignments(
                        ct, e)) {
                    ok = false;
                    break;
                }
            }
        }

        return ok;
    }

    /**
     * Validates the upDoesNotContainExternalSubDataRefOnLHSAssignments constraint of '<em>Interaction Action</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorInteractionAction_upDoesNotContainExternalSubDataRefOnLHSAssignments(
            ConnectorInteractionAction connectorInteractionAction,
            DiagnosticChain diagnostics, Map<Object, Object> context) {

        boolean ok = true;

        ConnectorType ct = (ConnectorType) connectorInteractionAction
                .eContainer();

        for (Expression e : connectorInteractionAction.getUp()) {
            if (!validateConnectorInteractionAction_upDoesNotContainExternalSubDataRefOnLHSAssignments(
                    ct, e)) {
                ok = false;
            }
        }

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] {
                                "upDoesNotContainExternalSubDataRefOnLHSAssignments",
                                getObjectLabel(connectorInteractionAction,
                                        context) },
                        new Object[] { connectorInteractionAction,
                                ErrorCodeEnum.upDoesNotContainExternalSubDataRefOnLHSAssignments },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the connectorActionNotEmpty constraint of '<em>Interaction Action</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorInteractionAction_connectorActionNotEmpty(
            ConnectorInteractionAction connectorInteractionAction,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = connectorInteractionAction.getGuard() != null
                || !connectorInteractionAction.getUp().isEmpty()
                || !connectorInteractionAction.getDown().isEmpty();

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "connectorActionNotEmpty",
                                getObjectLabel(connectorInteractionAction,
                                        context) },
                        new Object[] { connectorInteractionAction,
                                ErrorCodeEnum.connectorActionNotEmpty },
                        context));
            }
        }
        return ok;
    }

    /**
     * Validates the noUpIfNoExportedPort constraint of '<em>Interaction Action</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorInteractionAction_noUpIfNoExportedPort(
            ConnectorInteractionAction connectorInteractionAction,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean bad = false;

        ConnectorType ct = (ConnectorType) connectorInteractionAction
                .eContainer();
        boolean hasExpPort = ct.getExportedPortDeclaration() != null;
        boolean hasUp = !connectorInteractionAction.getUp().isEmpty();

        // has no export port but has an up
        bad = (!hasExpPort && hasUp);

        //        if (!ok) {
        //            if (!hasUp
        //                    && ct.getExportedPortDeclaration().getPortType()
        //                            .getDataParameterDeclarations().isEmpty()) {
        //                ok = true;
        //            }
        //        }

        if (bad && diagnostics != null) {
            diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                    DIAGNOSTIC_SOURCE, 0, "_UI_GenericConstraint_diagnostic",
                    new Object[] { "noUpIfNoExportedPort",
                            getObjectLabel(connectorInteractionAction,
                                    context) },
                    new Object[] { connectorInteractionAction,
                            ErrorCodeEnum.noUpIfNoExportedPort },
                    context));
        }
        return !bad;
    }

    /**
     * Validates the triggerPortsValidWrtDefine constraint of '<em>Interaction Action</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorInteractionAction_triggerPortsValidWrtDefine(
            ConnectorInteractionAction connectorInteractionAction,
            DiagnosticChain diagnostics, Map<Object, Object> context) {

        ConnectorType ct = (ConnectorType) connectorInteractionAction
                .eContainer();

        boolean ok = ct.isDefined(connectorInteractionAction.getOnPorts());

        if (!ok && diagnostics != null) {
            diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                    DIAGNOSTIC_SOURCE, 0, "_UI_GenericConstraint_diagnostic",
                    new Object[] { "triggerPortsValidWrtDefine",
                            getObjectLabel(connectorInteractionAction,
                                    context) },
                    new Object[] { connectorInteractionAction,
                            ErrorCodeEnum.triggerPortsValidWrtDefine },
                    context));
        }
        return ok;
    }

    /**
     * Validates the missingUpForExportedPort constraint of '<em>Interaction Action</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorInteractionAction_missingUpForExportedPort(
            ConnectorInteractionAction connectorInteractionAction,
            DiagnosticChain diagnostics, Map<Object, Object> context) {

        boolean maybe_missing = false;

        ConnectorType ct = (ConnectorType) connectorInteractionAction
                .eContainer();
        boolean hasExpPort = ct.getExportedPortDeclaration() != null;
        boolean hasUp = !connectorInteractionAction.getUp().isEmpty();

        // there is an exported port with data, but no Up.
        // this maybe valid, depending on how the exported port is used.
        maybe_missing = (hasExpPort && !ct.getExportedPortDeclaration()
                .getPortType().getDataParameterDeclarations().isEmpty()
                && !hasUp);

        if (maybe_missing && diagnostics != null) {
            diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                    DIAGNOSTIC_SOURCE, 0, "_UI_GenericConstraint_diagnostic",
                    new Object[] { "missingUpForExportedPort",
                            getObjectLabel(connectorInteractionAction,
                                    context) },
                    new Object[] { connectorInteractionAction,
                            ErrorCodeEnum.missingUpForExportedPort },
                    context));
        }
        return !maybe_missing;
    }

    /**
     * Validates the hasNoVariableModifiedBetweenUpAndDown constraint of '<em>Interaction Action</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorInteractionAction_hasNoVariableModifiedBetweenUpAndDown(
            ConnectorInteractionAction connectorInteractionAction,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        ConnectorType connector = (ConnectorType) connectorInteractionAction
                .eContainer();
        EList<Expression> errors = new BasicEList<Expression>();

        if (connector.getExportedPortDeclaration() != null) {
            // observe all variables that exported through the trigger port and read in the guard
            EList<DataDeclaration> observedVariables = new BasicEList<DataDeclaration>();

            for (DataDeclarationReferenceDataParameter p : connector
                    .getExportedPortDeclaration().getDataParameters()) {
                DataDeclaration dataDecl = p.getDataDeclarationReference();

                // keep only variables involved in the up
                for (Expression expr : connectorInteractionAction.getUp()) {
                    if (expr.getMayReadVariables().contains(dataDecl)) {
                        observedVariables.add(dataDecl);
                    }
                }
            }

            // check if observedVariables can be read by the code before being assigned
            for (Expression expr : connectorInteractionAction.getDown()) {
                EList<Expression> exprErrors = expr
                        .getMayReadUninitializedVariables(observedVariables);

                errors.addAll(exprErrors);
            }
        }

        if (!errors.isEmpty()) {
            if (diagnostics != null) {
                for (Expression ref : errors) {
                    diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                            DIAGNOSTIC_SOURCE, 0,
                            "_UI_GenericConstraint_diagnostic",
                            new Object[] { "variableModifiedBetweenUpAndDown",
                                    getObjectLabel(ref, context) },
                            new Object[] { ref,
                                    ErrorCodeEnum.variableModifiedBetweenUpAndDown,
                                    connector.getExportedPortDeclaration() },
                            context));
                }
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the checkUninitializedVariablesOfConnectorInteractionAction constraint of '<em>Interaction Action</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    private EList<DataDeclaration> getAllDataDeclarationsWithoutValue(
            ConnectorType connector) {
        EList<DataDeclaration> ret = new BasicEList<DataDeclaration>();

        for (ConnectorDataDeclaration data : connector.getDataDeclarations()) {
            if (data.getValue() == null) {
                ret.add(data);
            }
        }

        return ret;
    }

    /**
     * Validates the checkUninitializedVariablesOfConnectorInteractionAction constraint of '<em>Interaction Action</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorInteractionAction_checkUninitializedVariablesOfConnectorInteractionAction(
            ConnectorInteractionAction connectorInteractionAction,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        assert (connectorInteractionAction
                .eContainer() instanceof ConnectorType);
        ConnectorType connector = (ConnectorType) connectorInteractionAction
                .eContainer();
        // check uninitialized variables of guard
        EList<Expression> errors = new BasicEList<Expression>();

        // check uninitialized variables of guard
        if (connectorInteractionAction.getGuard() != null) {
            EList<Expression> guardErrors = connectorInteractionAction
                    .getGuard().getMayReadUninitializedVariables(
                            getAllDataDeclarationsWithoutValue(connector));

            errors.addAll(guardErrors);
        }

        // check up and down
        EList<DataDeclaration> uninitialized = getAllDataDeclarationsWithoutValue(
                connector);

        // /!\ WARNING: order is critical here since uninitialized is modified

        // check up
        for (Expression expr : connectorInteractionAction.getUp()) {
            EList<Expression> exprErrors = expr
                    .getMayReadUninitializedVariables(uninitialized);

            errors.addAll(exprErrors);
        }

        // check down
        for (Expression expr : connectorInteractionAction.getDown()) {
            EList<Expression> exprErrors = expr
                    .getMayReadUninitializedVariables(uninitialized);

            errors.addAll(exprErrors);
        }

        if (!errors.isEmpty()) {
            if (diagnostics != null) {
                for (Expression ref : errors) {
                    diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                            DIAGNOSTIC_SOURCE, 0,
                            "_UI_GenericConstraint_diagnostic",
                            new Object[] {
                                    "uninitializedVariableOfConnectorInteractionAction",
                                    getObjectLabel(ref, context) },
                            new Object[] { ref,
                                    ErrorCodeEnum.uninitializedVariableOfConnectorInteractionAction,
                                    ref },
                            context));
                }
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the checkUninitializedVariablesExportedByPortOfConnector constraint of '<em>Interaction Action</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorInteractionAction_checkUninitializedVariablesExportedByPortOfConnector(
            ConnectorInteractionAction connectorInteractionAction,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        assert (connectorInteractionAction
                .eContainer() instanceof ConnectorType);
        ConnectorType connector = (ConnectorType) connectorInteractionAction
                .eContainer();

        EList<DataDeclaration> uninitializedVariables = new BasicEList<DataDeclaration>();

        if (connector.getExportedPortDeclaration() != null) {
            for (DataDeclarationReferenceDataParameter p : connector
                    .getExportedPortDeclaration().getDataParameters()) {
                uninitializedVariables.add(p.getDataDeclarationReference());
            }

            for (Expression expr : connectorInteractionAction.getUp()) {
                expr.getMayReadUninitializedVariables(uninitializedVariables);
            }
        }

        if (!uninitializedVariables.isEmpty()) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] {
                                "uninitializedVariableExportedByPortOfConnector",
                                getObjectLabel(connectorInteractionAction,
                                        context) },
                        new Object[] { connectorInteractionAction,
                                ErrorCodeEnum.uninitializedVariableExportedByPortOfConnector,
                                connector.getExportedPortDeclaration(),
                                new HashSet<DataDeclaration>(
                                        uninitializedVariables) },
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
    public boolean validateConnectorInteractionDefinition(
            ConnectorInteractionDefinition connectorInteractionDefinition,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint(
                (EObject) connectorInteractionDefinition, diagnostics, context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateConnectorInteractionPortReference(
            ConnectorInteractionPortReference connectorInteractionPortReference,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint(
                (EObject) connectorInteractionPortReference, diagnostics,
                context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateConnectorInteractionNestedDefinition(
            ConnectorInteractionNestedDefinition connectorInteractionNestedDefinition,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint(
                (EObject) connectorInteractionNestedDefinition, diagnostics,
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

} //ConnectorValidator
