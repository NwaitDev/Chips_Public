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

package bip2.ujf.verimag.bip.instance.util;

import bip2.ujf.verimag.bip.instance.*;

import java.util.ArrayDeque;
import java.util.Deque;
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
 * @see bip2.ujf.verimag.bip.instance.InstancePackage
 * @generated
 */
public class InstanceValidator extends EObjectValidator {
    /**
     * The cached model package
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static final InstanceValidator INSTANCE = new InstanceValidator();

    /**
     * A constant for the {@link org.eclipse.emf.common.util.Diagnostic#getSource() source} of diagnostic {@link org.eclipse.emf.common.util.Diagnostic#getCode() codes} from this package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.eclipse.emf.common.util.Diagnostic#getSource()
     * @see org.eclipse.emf.common.util.Diagnostic#getCode()
     * @generated
     */
    public static final String DIAGNOSTIC_SOURCE = "bip2.ujf.verimag.bip.instance";

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
    public InstanceValidator() {
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
        return InstancePackage.eINSTANCE;
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
        case InstancePackage.CONNECTOR_INSTANCE:
            return validateConnectorInstance((ConnectorInstance) value,
                    diagnostics, context);
        case InstancePackage.DATA_INSTANCE:
            return validateDataInstance((DataInstance) value, diagnostics,
                    context);
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE:
            return validateCompoundPriorityInstance(
                    (CompoundPriorityInstance) value, diagnostics, context);
        case InstancePackage.ATOM_INSTANCE:
            return validateAtomInstance((AtomInstance) value, diagnostics,
                    context);
        case InstancePackage.COMPOUND_INSTANCE:
            return validateCompoundInstance((CompoundInstance) value,
                    diagnostics, context);
        case InstancePackage.COMPONENT_INSTANCE:
            return validateComponentInstance((ComponentInstance) value,
                    diagnostics, context);
        case InstancePackage.PORT_INSTANCE:
            return validatePortInstance((PortInstance) value, diagnostics,
                    context);
        case InstancePackage.EXPORTED_PORT_INSTANCE:
            return validateExportedPortInstance((ExportedPortInstance) value,
                    diagnostics, context);
        case InstancePackage.ATOM_INTERNAL_PORT_INSTANCE:
            return validateAtomInternalPortInstance(
                    (AtomInternalPortInstance) value, diagnostics, context);
        case InstancePackage.ATOM_EXTERNAL_PORT_INSTANCE:
            return validateAtomExternalPortInstance(
                    (AtomExternalPortInstance) value, diagnostics, context);
        case InstancePackage.CONNECTOR_PORT_INSTANCE:
            return validateConnectorPortInstance((ConnectorPortInstance) value,
                    diagnostics, context);
        default:
            return true;
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateConnectorInstance(
            ConnectorInstance connectorInstance, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) connectorInstance,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) connectorInstance, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) connectorInstance, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) connectorInstance, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) connectorInstance, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves((EObject) connectorInstance,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) connectorInstance,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) connectorInstance,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique((EObject) connectorInstance,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validateConnectorInstance_connectorDoesNotBindTheSameComponentMoreThanOnce(
                    connectorInstance, diagnostics, context);
        return result;
    }

    /**
     * Validates the connectorDoesNotBindTheSameComponentMoreThanOnce constraint of '<em>Connector Instance</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateConnectorInstance_connectorDoesNotBindTheSameComponentMoreThanOnce(
            ConnectorInstance connectorInstance, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        boolean ok = true;

        // only consider "root" connector (ie. the one without exported port)
        if (connectorInstance.getExportedPort() == null) {
            Set<ComponentInstance> connectedComps = new HashSet<ComponentInstance>();
            Deque<ConnectorInstance> connectorToVisit = new ArrayDeque<ConnectorInstance>();
            connectorToVisit.push(connectorInstance);

            while (!connectorToVisit.isEmpty()) {
                ConnectorInstance conni = connectorToVisit.pop();
                for (PortInstance pi : conni.getPortParamInstances()) {
                    if (pi instanceof ConnectorPortInstance) {
                        // visit the subconnector
                        connectorToVisit.push(
                                (ConnectorInstance) (((ConnectorPortInstance) pi)
                                        .eContainer()));
                    } else if (pi instanceof ExportedPortInstance) {
                        if (!connectedComps
                                .add((ComponentInstance) pi.eContainer())) {
                            ok = false;
                        }
                    } else if (pi instanceof AtomInternalPortInstance) {
                        // this is an error, I guess. See #172
                    }
                }
            }
        }
        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] {
                                "connectorDoesNotBindTheSameComponentMoreThanOnce",
                                getObjectLabel(connectorInstance, context) },
                        new Object[] { connectorInstance,
                                ErrorCodeEnum.connectorDoesNotBindTheSameComponentMoreThanOnce },
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
    public boolean validatePortInstance(PortInstance portInstance,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) portInstance,
                diagnostics, context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateExportedPortInstance(
            ExportedPortInstance exportedPortInstance,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) exportedPortInstance,
                diagnostics, context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateAtomInternalPortInstance(
            AtomInternalPortInstance atomInternalPortInstance,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint(
                (EObject) atomInternalPortInstance, diagnostics, context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateAtomExternalPortInstance(
            AtomExternalPortInstance atomExternalPortInstance,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint(
                (EObject) atomExternalPortInstance, diagnostics, context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateConnectorPortInstance(
            ConnectorPortInstance connectorPortInstance,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) connectorPortInstance,
                diagnostics, context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateDataInstance(DataInstance dataInstance,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) dataInstance,
                diagnostics, context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateCompoundPriorityInstance(
            CompoundPriorityInstance compoundPriorityInstance,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint(
                (EObject) compoundPriorityInstance, diagnostics, context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateAtomInstance(AtomInstance atomInstance,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) atomInstance,
                diagnostics, context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateCompoundInstance(CompoundInstance compoundInstance,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) compoundInstance,
                diagnostics, context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validateComponentInstance(
            ComponentInstance componentInstance, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        return validate_EveryDefaultConstraint((EObject) componentInstance,
                diagnostics, context);
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

} //InstanceValidator
