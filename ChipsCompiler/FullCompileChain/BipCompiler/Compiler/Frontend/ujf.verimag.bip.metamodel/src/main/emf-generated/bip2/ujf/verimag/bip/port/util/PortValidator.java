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

package bip2.ujf.verimag.bip.port.util;

import bip2.ujf.verimag.bip.component.atom.AtomExportPortDeclaration;
import bip2.ujf.verimag.bip.component.compound.CompoundExportPortDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorPortParameterDeclaration;
import bip2.ujf.verimag.bip.data.DataDeclarationReferenceDataParameter;
import bip2.ujf.verimag.bip.data.DataType;
import bip2.ujf.verimag.bip.packaging.BipPackage;
import bip2.ujf.verimag.bip.port.*;

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
 * @see bip2.ujf.verimag.bip.port.PortPackage
 * @generated
 */
public class PortValidator extends EObjectValidator {
    /**
     * The cached model package
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static final PortValidator INSTANCE = new PortValidator();

    /**
     * A constant for the {@link org.eclipse.emf.common.util.Diagnostic#getSource() source} of diagnostic {@link org.eclipse.emf.common.util.Diagnostic#getCode() codes} from this package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.eclipse.emf.common.util.Diagnostic#getSource()
     * @see org.eclipse.emf.common.util.Diagnostic#getCode()
     * @generated
     */
    public static final String DIAGNOSTIC_SOURCE = "bip2.ujf.verimag.bip.port";

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
    public PortValidator() {
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
        return PortPackage.eINSTANCE;
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
        case PortPackage.PORT_DECLARATION:
            return validatePortDeclaration((PortDeclaration) value, diagnostics,
                    context);
        case PortPackage.SUB_PORT_DECLARATION_REFERENCE:
            return validateSubPortDeclarationReference(
                    (SubPortDeclarationReference) value, diagnostics, context);
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION:
            return validatePortDataParameterDeclaration(
                    (PortDataParameterDeclaration) value, diagnostics, context);
        case PortPackage.PORT_DECLARATION_REFERENCE_PARAMETER:
            return validatePortDeclarationReferenceParameter(
                    (PortDeclarationReferenceParameter) value, diagnostics,
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
    public boolean validatePortDeclaration(PortDeclaration portDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) portDeclaration,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) portDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms((EObject) portDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) portDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) portDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves((EObject) portDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) portDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) portDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique((EObject) portDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validatePortDeclaration_hasCorrectNumberOfDataParameters(
                    portDeclaration, diagnostics, context);
        return result;
    }

    /**
     * Validates the hasCorrectNumberOfDataParameters constraint of '<em>Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validatePortDeclaration_hasCorrectNumberOfDataParameters(
            PortDeclaration portDeclaration, DiagnosticChain diagnostics,
            Map<Object, Object> context) {
        boolean ok = true;
        if (portDeclaration instanceof ConnectorPortParameterDeclaration) {
            // this is ok to have the parameters list empty for port parameters.
        } else if (portDeclaration instanceof AtomExportPortDeclaration) {
            // same as above: exported port don't have params.
        } else if (portDeclaration instanceof CompoundExportPortDeclaration) {
            // again, as above
        } else {
            int decl_size = portDeclaration.getDataParameters().size();
            int type_size = portDeclaration.getPortType()
                    .getDataParameterDeclarations().size();
            ok = (decl_size == type_size);
        }

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "hasCorrectNumberOfDataParameters",
                                getObjectLabel(portDeclaration, context) },
                        new Object[] { portDeclaration,
                                ErrorCodeEnum.hasCorrectNumberOfDataParameters },
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
    public boolean validateSubPortDeclarationReference(
            SubPortDeclarationReference subPortDeclarationReference,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment(
                (EObject) subPortDeclarationReference, diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) subPortDeclarationReference, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) subPortDeclarationReference, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) subPortDeclarationReference, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) subPortDeclarationReference, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) subPortDeclarationReference, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) subPortDeclarationReference,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) subPortDeclarationReference, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) subPortDeclarationReference, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validateSubPortDeclarationReference_subPortDeclarationReferenceHasOneDeclaration(
                    subPortDeclarationReference, diagnostics, context);
        return result;
    }

    /**
     * Validates the subPortDeclarationReferenceHasOneDeclaration constraint of '<em>Sub Port Declaration Reference</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateSubPortDeclarationReference_subPortDeclarationReferenceHasOneDeclaration(
            SubPortDeclarationReference subPortDeclarationReference,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        int c = 0;
        c += subPortDeclarationReference.getComponentDeclaration() != null ? 1
                : 0;
        c += subPortDeclarationReference.getConnectorDeclaration() != null ? 1
                : 0;
        if (c != 1) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] {
                                "subPortDeclarationReferenceHasOneDeclaration",
                                getObjectLabel(subPortDeclarationReference,
                                        context) },
                        new Object[] { subPortDeclarationReference,
                                ErrorCodeEnum.subPortDeclarationReferenceHasOneDeclaration },
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
    public boolean validatePortDataParameterDeclaration(
            PortDataParameterDeclaration portDataParameterDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        return validate_EveryDefaultConstraint(
                (EObject) portDataParameterDeclaration, diagnostics, context);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean validatePortDeclarationReferenceParameter(
            PortDeclarationReferenceParameter portDeclarationReferenceParameter,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment(
                (EObject) portDeclarationReferenceParameter, diagnostics,
                context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) portDeclarationReferenceParameter, diagnostics,
                context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) portDeclarationReferenceParameter, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) portDeclarationReferenceParameter, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) portDeclarationReferenceParameter, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) portDeclarationReferenceParameter, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_UniqueID(
                    (EObject) portDeclarationReferenceParameter, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) portDeclarationReferenceParameter, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) portDeclarationReferenceParameter, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validatePortDeclarationReferenceParameter_portParameterHasCorrectPortType(
                    portDeclarationReferenceParameter, diagnostics, context);
        return result;
    }

    /**
     * Validates the portParameterHasCorrectPortType constraint of '<em>Declaration Reference Parameter</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validatePortDeclarationReferenceParameter_portParameterHasCorrectPortType(
            PortDeclarationReferenceParameter portDeclarationReferenceParameter,
            DiagnosticChain diagnostics, Map<Object, Object> context) {

        boolean ok = portDeclarationReferenceParameter.getParameterDeclaration()
                .getPortType()
                .equals(portDeclarationReferenceParameter
                        .getSubPortDeclarationReference()
                        .getForwardPortDeclaration().getPortType());

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "portParameterHasCorrectPortType",
                                getObjectLabel(
                                        portDeclarationReferenceParameter,
                                        context) },
                        new Object[] { portDeclarationReferenceParameter,
                                ErrorCodeEnum.portParameterHasCorrectPortType },
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

} //PortValidator
