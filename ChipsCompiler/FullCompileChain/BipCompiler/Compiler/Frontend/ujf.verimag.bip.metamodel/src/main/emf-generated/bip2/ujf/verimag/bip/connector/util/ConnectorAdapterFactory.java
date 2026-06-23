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

import bip2.ujf.verimag.bip.annotation.AnnotatedElement;
import bip2.ujf.verimag.bip.connector.*;

import bip2.ujf.verimag.bip.data.DataDeclaration;

import bip2.ujf.verimag.bip.data.ExplicitDataDeclaration;
import bip2.ujf.verimag.bip.port.PortDeclaration;

import org.eclipse.emf.common.notify.Adapter;
import org.eclipse.emf.common.notify.Notifier;

import org.eclipse.emf.common.notify.impl.AdapterFactoryImpl;

import org.eclipse.emf.ecore.EObject;

/**
 * <!-- begin-user-doc -->
 * The <b>Adapter Factory</b> for the model.
 * It provides an adapter <code>createXXX</code> method for each class of the model.
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.connector.ConnectorPackage
 * @generated
 */
public class ConnectorAdapterFactory extends AdapterFactoryImpl {
    /**
     * The cached model package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected static ConnectorPackage modelPackage;

    /**
     * Creates an instance of the adapter factory.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorAdapterFactory() {
        if (modelPackage == null) {
            modelPackage = ConnectorPackage.eINSTANCE;
        }
    }

    /**
     * Returns whether this factory is applicable for the type of the object.
     * <!-- begin-user-doc -->
     * This implementation returns <code>true</code> if the object is either the model's package or is an instance object of the model.
     * <!-- end-user-doc -->
     * @return whether this factory is applicable for the type of the object.
     * @generated
     */
    @Override
    public boolean isFactoryForType(Object object) {
        if (object == modelPackage) {
            return true;
        }
        if (object instanceof EObject) {
            return ((EObject) object).eClass().getEPackage() == modelPackage;
        }
        return false;
    }

    /**
     * The switch that delegates to the <code>createXXX</code> methods.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected ConnectorSwitch<Adapter> modelSwitch = new ConnectorSwitch<Adapter>() {
        @Override
        public Adapter caseConnectorDeclaration(ConnectorDeclaration object) {
            return createConnectorDeclarationAdapter();
        }

        @Override
        public Adapter caseConnectorPortParameterDeclaration(
                ConnectorPortParameterDeclaration object) {
            return createConnectorPortParameterDeclarationAdapter();
        }

        @Override
        public Adapter caseConnectorExportedPortDeclaration(
                ConnectorExportedPortDeclaration object) {
            return createConnectorExportedPortDeclarationAdapter();
        }

        @Override
        public Adapter caseConnectorDataDeclaration(
                ConnectorDataDeclaration object) {
            return createConnectorDataDeclarationAdapter();
        }

        @Override
        public Adapter caseConnectorInteractionAction(
                ConnectorInteractionAction object) {
            return createConnectorInteractionActionAdapter();
        }

        @Override
        public Adapter caseConnectorInteractionDefinition(
                ConnectorInteractionDefinition object) {
            return createConnectorInteractionDefinitionAdapter();
        }

        @Override
        public Adapter caseConnectorInteractionPortReference(
                ConnectorInteractionPortReference object) {
            return createConnectorInteractionPortReferenceAdapter();
        }

        @Override
        public Adapter caseConnectorInteractionNestedDefinition(
                ConnectorInteractionNestedDefinition object) {
            return createConnectorInteractionNestedDefinitionAdapter();
        }

        @Override
        public Adapter caseAnnotatedElement(AnnotatedElement object) {
            return createAnnotatedElementAdapter();
        }

        @Override
        public Adapter casePortDeclaration(PortDeclaration object) {
            return createPortDeclarationAdapter();
        }

        @Override
        public Adapter caseDataDeclaration(DataDeclaration object) {
            return createDataDeclarationAdapter();
        }

        @Override
        public Adapter caseExplicitDataDeclaration(
                ExplicitDataDeclaration object) {
            return createExplicitDataDeclarationAdapter();
        }

        @Override
        public Adapter defaultCase(EObject object) {
            return createEObjectAdapter();
        }
    };

    /**
     * Creates an adapter for the <code>target</code>.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param target the object to adapt.
     * @return the adapter for the <code>target</code>.
     * @generated
     */
    @Override
    public Adapter createAdapter(Notifier target) {
        return modelSwitch.doSwitch((EObject) target);
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.connector.ConnectorDeclaration <em>Declaration</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.connector.ConnectorDeclaration
     * @generated
     */
    public Adapter createConnectorDeclarationAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.connector.ConnectorPortParameterDeclaration <em>Port Parameter Declaration</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.connector.ConnectorPortParameterDeclaration
     * @generated
     */
    public Adapter createConnectorPortParameterDeclarationAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.connector.ConnectorExportedPortDeclaration <em>Exported Port Declaration</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.connector.ConnectorExportedPortDeclaration
     * @generated
     */
    public Adapter createConnectorExportedPortDeclarationAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.connector.ConnectorDataDeclaration <em>Data Declaration</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.connector.ConnectorDataDeclaration
     * @generated
     */
    public Adapter createConnectorDataDeclarationAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.connector.ConnectorInteractionAction <em>Interaction Action</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.connector.ConnectorInteractionAction
     * @generated
     */
    public Adapter createConnectorInteractionActionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.connector.ConnectorInteractionDefinition <em>Interaction Definition</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.connector.ConnectorInteractionDefinition
     * @generated
     */
    public Adapter createConnectorInteractionDefinitionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.connector.ConnectorInteractionPortReference <em>Interaction Port Reference</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.connector.ConnectorInteractionPortReference
     * @generated
     */
    public Adapter createConnectorInteractionPortReferenceAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.connector.ConnectorInteractionNestedDefinition <em>Interaction Nested Definition</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.connector.ConnectorInteractionNestedDefinition
     * @generated
     */
    public Adapter createConnectorInteractionNestedDefinitionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.port.PortDeclaration <em>Declaration</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.port.PortDeclaration
     * @generated
     */
    public Adapter createPortDeclarationAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.data.DataDeclaration <em>Declaration</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.data.DataDeclaration
     * @generated
     */
    public Adapter createDataDeclarationAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.data.ExplicitDataDeclaration <em>Explicit Data Declaration</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.data.ExplicitDataDeclaration
     * @generated
     */
    public Adapter createExplicitDataDeclarationAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.annotation.AnnotatedElement <em>Annotated Element</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.annotation.AnnotatedElement
     * @generated
     */
    public Adapter createAnnotatedElementAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for the default case.
     * <!-- begin-user-doc -->
     * This default implementation returns null.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @generated
     */
    public Adapter createEObjectAdapter() {
        return null;
    }

} //ConnectorAdapterFactory
