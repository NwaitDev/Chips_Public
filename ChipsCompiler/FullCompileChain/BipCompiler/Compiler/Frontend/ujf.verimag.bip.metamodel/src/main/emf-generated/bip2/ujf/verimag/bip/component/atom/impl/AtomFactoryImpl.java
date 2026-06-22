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

package bip2.ujf.verimag.bip.component.atom.impl;

import bip2.ujf.verimag.bip.component.atom.*;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EDataType;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;

import org.eclipse.emf.ecore.impl.EFactoryImpl;

import org.eclipse.emf.ecore.plugin.EcorePlugin;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model <b>Factory</b>.
 * <!-- end-user-doc -->
 * @generated
 */
public class AtomFactoryImpl extends EFactoryImpl implements AtomFactory {
    /**
     * Creates the default factory implementation.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static AtomFactory init() {
        try {
            AtomFactory theAtomFactory = (AtomFactory) EPackage.Registry.INSTANCE
                    .getEFactory(AtomPackage.eNS_URI);
            if (theAtomFactory != null) {
                return theAtomFactory;
            }
        } catch (Exception exception) {
            EcorePlugin.INSTANCE.log(exception);
        }
        return new AtomFactoryImpl();
    }

    /**
     * Creates an instance of the factory.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomFactoryImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EObject create(EClass eClass) {
        switch (eClass.getClassifierID()) {
        case AtomPackage.ATOM_INTERNAL_PORT_DECLARATION:
            return (EObject) createAtomInternalPortDeclaration();
        case AtomPackage.ATOM_EXTERNAL_PORT_DECLARATION:
            return (EObject) createAtomExternalPortDeclaration();
        case AtomPackage.ATOM_INTERNAL_DATA_DECLARATION:
            return (EObject) createAtomInternalDataDeclaration();
        case AtomPackage.ATOM_EXPORT_PORT_DECLARATION:
            return (EObject) createAtomExportPortDeclaration();
        default:
            throw new IllegalArgumentException("The class '" + eClass.getName()
                    + "' is not a valid classifier");
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object createFromString(EDataType eDataType, String initialValue) {
        switch (eDataType.getClassifierID()) {
        case AtomPackage.EVENT_CONSUMPTION_POLICY:
            return createEventConsumptionPolicyFromString(eDataType,
                    initialValue);
        default:
            throw new IllegalArgumentException("The datatype '"
                    + eDataType.getName() + "' is not a valid classifier");
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public String convertToString(EDataType eDataType, Object instanceValue) {
        switch (eDataType.getClassifierID()) {
        case AtomPackage.EVENT_CONSUMPTION_POLICY:
            return convertEventConsumptionPolicyToString(eDataType,
                    instanceValue);
        default:
            throw new IllegalArgumentException("The datatype '"
                    + eDataType.getName() + "' is not a valid classifier");
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomInternalPortDeclaration createAtomInternalPortDeclaration() {
        AtomInternalPortDeclarationImpl atomInternalPortDeclaration = new AtomInternalPortDeclarationImpl();
        return atomInternalPortDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomExternalPortDeclaration createAtomExternalPortDeclaration() {
        AtomExternalPortDeclarationImpl atomExternalPortDeclaration = new AtomExternalPortDeclarationImpl();
        return atomExternalPortDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomInternalDataDeclaration createAtomInternalDataDeclaration() {
        AtomInternalDataDeclarationImpl atomInternalDataDeclaration = new AtomInternalDataDeclarationImpl();
        return atomInternalDataDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomExportPortDeclaration createAtomExportPortDeclaration() {
        AtomExportPortDeclarationImpl atomExportPortDeclaration = new AtomExportPortDeclarationImpl();
        return atomExportPortDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EventConsumptionPolicy createEventConsumptionPolicyFromString(
            EDataType eDataType, String initialValue) {
        EventConsumptionPolicy result = EventConsumptionPolicy
                .get(initialValue);
        if (result == null)
            throw new IllegalArgumentException("The value '" + initialValue
                    + "' is not a valid enumerator of '" + eDataType.getName()
                    + "'");
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public String convertEventConsumptionPolicyToString(EDataType eDataType,
            Object instanceValue) {
        return instanceValue == null ? null : instanceValue.toString();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomPackage getAtomPackage() {
        return (AtomPackage) getEPackage();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @deprecated
     * @generated
     */
    @Deprecated
    public static AtomPackage getPackage() {
        return AtomPackage.eINSTANCE;
    }

} //AtomFactoryImpl
