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

package bip2.ujf.verimag.bip.component.util;

import bip2.ujf.verimag.bip.component.*;
import bip2.ujf.verimag.bip.component.compound.CompoundExportPortDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorDeclaration;
import bip2.ujf.verimag.bip.port.PortDeclaration;
import bip2.ujf.verimag.bip.port.PortDeclarationReferenceParameter;
import bip2.ujf.verimag.bip.port.SubPortDeclarationReference;
import bip2.ujf.verimag.bip.types.ComponentType;
import bip2.ujf.verimag.bip.types.CompoundType;

import java.util.HashSet;
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
 * @see bip2.ujf.verimag.bip.component.ComponentPackage
 * @generated
 */
public class ComponentValidator extends EObjectValidator {
    /**
     * The cached model package
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static final ComponentValidator INSTANCE = new ComponentValidator();

    /**
     * A constant for the {@link org.eclipse.emf.common.util.Diagnostic#getSource() source} of diagnostic {@link org.eclipse.emf.common.util.Diagnostic#getCode() codes} from this package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.eclipse.emf.common.util.Diagnostic#getSource()
     * @see org.eclipse.emf.common.util.Diagnostic#getCode()
     * @generated
     */
    public static final String DIAGNOSTIC_SOURCE = "bip2.ujf.verimag.bip.component";

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
    public ComponentValidator() {
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
        return ComponentPackage.eINSTANCE;
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
        case ComponentPackage.COMPONENT_DECLARATION:
            return validateComponentDeclaration((ComponentDeclaration) value,
                    diagnostics, context);
        case ComponentPackage.COMPONENT_DATA_PARAMETER_DECLARATION:
            return validateComponentDataParameterDeclaration(
                    (ComponentDataParameterDeclaration) value, diagnostics,
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
    public boolean validateComponentDeclaration(
            ComponentDeclaration componentDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment((EObject) componentDeclaration,
                diagnostics, context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) componentDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) componentDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) componentDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) componentDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) componentDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_UniqueID((EObject) componentDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique((EObject) componentDeclaration,
                    diagnostics, context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) componentDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateComponentDeclaration_componentDeclarationHasCorrectNumberOfParam(
                    componentDeclaration, diagnostics, context);
        if (result || diagnostics != null)
            result &= validateComponentDeclaration_componentDeclarationHasNoUnconnectedPort(
                    componentDeclaration, diagnostics, context);
        return result;
    }

    /**
     * Validates the componentDeclarationHasCorrectNumberOfParam constraint of '<em>Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateComponentDeclaration_componentDeclarationHasCorrectNumberOfParam(
            ComponentDeclaration componentDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok;

        int ct_size = componentDeclaration.getType()
                .getDataParameterDeclarations().size();
        int decl_size = componentDeclaration.getParameters().size();

        ok = (ct_size == decl_size);

        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] {
                                "componentDeclarationHasCorrectNumberOfParam",
                                getObjectLabel(componentDeclaration, context) },
                        new Object[] { componentDeclaration,
                                ErrorCodeEnum.componentDeclarationHasCorrectNumberOfParam },
                        context));
            }
            return false;
        }
        return true;
    }

    /**
     * Validates the componentDeclarationHasNoUnconnectedPort constraint of '<em>Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateComponentDeclaration_componentDeclarationHasNoUnconnectedPort(
            ComponentDeclaration componentDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        boolean ok = true;

        HashSet<String> epd_names = new HashSet<String>();
        for (PortDeclaration pd : componentDeclaration.getType()
                .getExportedPortDeclarations()) {
            epd_names.add(pd.getName());
        }

        // what is happening for Root component ?
        CompoundType ct = (CompoundType) componentDeclaration.eContainer();
        String comp_name = componentDeclaration.getName();

        if (epd_names.isEmpty() || (ct == null)) {
            // We are either:
            //  - looking at the top component. Port is dangling for sure!
            //  - looking at a component without exported port.
        } else {
            /*
             * Get the parent, which must be a compound type:
             * 
             * - list all connector and see if one of them is connecting us 
             * - list all exported port and see if we are getting exported
             * 
             * if nothing is found, we are not bound. This is not the end of the
             * world but everything depending on this port can be
             * considered 'dead code'
             */

            for (ConnectorDeclaration cd : ct.getConnectorDeclarations()) {
                for (PortDeclarationReferenceParameter cdrp : cd
                        .getPortParameters()) {
                    if (cdrp.getSubPortDeclarationReference()
                            .getComponentDeclaration() != null) {
                        String b_c_name = cdrp.getSubPortDeclarationReference()
                                .getComponentDeclaration().getName();
                        String b_epd_name = cdrp
                                .getSubPortDeclarationReference()
                                .getForwardPortDeclaration().getName();
                        if (b_c_name.equals(comp_name)) {
                            epd_names.remove(b_epd_name);
                        }
                        if (epd_names.isEmpty())
                            break;
                    }
                    if (epd_names.isEmpty())
                        break;
                }
                if (epd_names.isEmpty())
                    break;
            }

            // no luck with connector, check exported ports
            if (!epd_names.isEmpty()) {
                for (CompoundExportPortDeclaration cepd : ct
                        .getExportPortDeclarations()) {
                    for (SubPortDeclarationReference spdr : cepd
                            .getPortDeclarationReferences()) {
                        if (spdr.getComponentDeclaration() != null) {
                            String b_c_name = spdr.getComponentDeclaration()
                                    .getName();
                            String b_epd_name = spdr.getForwardPortDeclaration()
                                    .getName();
                            if (b_c_name.equals(comp_name)) {
                                epd_names.remove(b_epd_name);
                            }
                        }
                    }
                }
            }
        }

        ok = epd_names.isEmpty();
        if (!ok) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.WARNING,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] {
                                "componentDeclarationHasNoUnconnectedPort",
                                getObjectLabel(componentDeclaration, context) },
                        new Object[] { componentDeclaration,
                                ErrorCodeEnum.componentDeclarationHasNoUnconnectedPort },
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
    public boolean validateComponentDataParameterDeclaration(
            ComponentDataParameterDeclaration componentDataParameterDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {
        if (!validate_NoCircularContainment(
                (EObject) componentDataParameterDeclaration, diagnostics,
                context))
            return false;
        boolean result = validate_EveryMultiplicityConforms(
                (EObject) componentDataParameterDeclaration, diagnostics,
                context);
        if (result || diagnostics != null)
            result &= validate_EveryDataValueConforms(
                    (EObject) componentDataParameterDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryReferenceIsContained(
                    (EObject) componentDataParameterDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryBidirectionalReferenceIsPaired(
                    (EObject) componentDataParameterDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryProxyResolves(
                    (EObject) componentDataParameterDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_UniqueID(
                    (EObject) componentDataParameterDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryKeyUnique(
                    (EObject) componentDataParameterDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validate_EveryMapEntryUnique(
                    (EObject) componentDataParameterDeclaration, diagnostics,
                    context);
        if (result || diagnostics != null)
            result &= validateComponentDataParameterDeclaration_dataTypeIsBasic(
                    componentDataParameterDeclaration, diagnostics, context);
        return result;
    }

    /**
     * Validates the dataTypeIsBasic constraint of '<em>Data Parameter Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean validateComponentDataParameterDeclaration_dataTypeIsBasic(
            ComponentDataParameterDeclaration componentDataParameterDeclaration,
            DiagnosticChain diagnostics, Map<Object, Object> context) {

        boolean b = componentDataParameterDeclaration.getDataType().isNative();
        if (!b) {
            if (diagnostics != null) {
                diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                        DIAGNOSTIC_SOURCE, 0,
                        "_UI_GenericConstraint_diagnostic",
                        new Object[] { "dataTypeIsBasic", getObjectLabel(
                                componentDataParameterDeclaration, context) },
                        new Object[] { componentDataParameterDeclaration,
                                ErrorCodeEnum.dataTypeIsBasic },
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

} //ComponentValidator
