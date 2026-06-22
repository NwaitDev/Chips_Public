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

package bip2.ujf.verimag.bip.instance.impl;

import bip2.ujf.verimag.bip.instance.*;

import org.eclipse.emf.ecore.EClass;
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
public class InstanceFactoryImpl extends EFactoryImpl
        implements InstanceFactory {
    /**
     * Creates the default factory implementation.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static InstanceFactory init() {
        try {
            InstanceFactory theInstanceFactory = (InstanceFactory) EPackage.Registry.INSTANCE
                    .getEFactory(InstancePackage.eNS_URI);
            if (theInstanceFactory != null) {
                return theInstanceFactory;
            }
        } catch (Exception exception) {
            EcorePlugin.INSTANCE.log(exception);
        }
        return new InstanceFactoryImpl();
    }

    /**
     * Creates an instance of the factory.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public InstanceFactoryImpl() {
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
        case InstancePackage.CONNECTOR_INSTANCE:
            return (EObject) createConnectorInstance();
        case InstancePackage.DATA_INSTANCE:
            return (EObject) createDataInstance();
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE:
            return (EObject) createCompoundPriorityInstance();
        case InstancePackage.ATOM_INSTANCE:
            return (EObject) createAtomInstance();
        case InstancePackage.COMPOUND_INSTANCE:
            return (EObject) createCompoundInstance();
        case InstancePackage.EXPORTED_PORT_INSTANCE:
            return (EObject) createExportedPortInstance();
        case InstancePackage.ATOM_INTERNAL_PORT_INSTANCE:
            return (EObject) createAtomInternalPortInstance();
        case InstancePackage.ATOM_EXTERNAL_PORT_INSTANCE:
            return (EObject) createAtomExternalPortInstance();
        case InstancePackage.CONNECTOR_PORT_INSTANCE:
            return (EObject) createConnectorPortInstance();
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
    public ConnectorInstance createConnectorInstance() {
        ConnectorInstanceImpl connectorInstance = new ConnectorInstanceImpl();
        return connectorInstance;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ExportedPortInstance createExportedPortInstance() {
        ExportedPortInstanceImpl exportedPortInstance = new ExportedPortInstanceImpl();
        return exportedPortInstance;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomInternalPortInstance createAtomInternalPortInstance() {
        AtomInternalPortInstanceImpl atomInternalPortInstance = new AtomInternalPortInstanceImpl();
        return atomInternalPortInstance;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomExternalPortInstance createAtomExternalPortInstance() {
        AtomExternalPortInstanceImpl atomExternalPortInstance = new AtomExternalPortInstanceImpl();
        return atomExternalPortInstance;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorPortInstance createConnectorPortInstance() {
        ConnectorPortInstanceImpl connectorPortInstance = new ConnectorPortInstanceImpl();
        return connectorPortInstance;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataInstance createDataInstance() {
        DataInstanceImpl dataInstance = new DataInstanceImpl();
        return dataInstance;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public CompoundPriorityInstance createCompoundPriorityInstance() {
        CompoundPriorityInstanceImpl compoundPriorityInstance = new CompoundPriorityInstanceImpl();
        return compoundPriorityInstance;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomInstance createAtomInstance() {
        AtomInstanceImpl atomInstance = new AtomInstanceImpl();
        return atomInstance;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public CompoundInstance createCompoundInstance() {
        CompoundInstanceImpl compoundInstance = new CompoundInstanceImpl();
        return compoundInstance;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public InstancePackage getInstancePackage() {
        return (InstancePackage) getEPackage();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @deprecated
     * @generated
     */
    @Deprecated
    public static InstancePackage getPackage() {
        return InstancePackage.eINSTANCE;
    }

} //InstanceFactoryImpl
