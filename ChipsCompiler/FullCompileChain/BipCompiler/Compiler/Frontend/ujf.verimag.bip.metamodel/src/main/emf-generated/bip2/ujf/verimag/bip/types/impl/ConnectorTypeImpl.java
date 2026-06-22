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

package bip2.ujf.verimag.bip.types.impl;

import bip2.ujf.verimag.bip.annotation.AnnotatedElement;
import bip2.ujf.verimag.bip.annotation.AnnotationPackage;
import bip2.ujf.verimag.bip.annotation.BipAnnotation;
import bip2.ujf.verimag.bip.annotation.impl.StringToAnnotationMapEntryImpl;
import bip2.ujf.verimag.bip.annotation.impl.AnnotatedElementImpl;
import bip2.ujf.verimag.bip.connector.ConnectorDataDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorExportedPortDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionAction;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionDefinition;
import bip2.ujf.verimag.bip.connector.ConnectorPortParameterDeclaration;
import bip2.ujf.verimag.bip.data.DataType;
import bip2.ujf.verimag.bip.port.PortDataParameterDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionDefinition;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionPortReference;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionNestedDefinition;
import bip2.ujf.verimag.bip.types.ConnectorType;
import bip2.ujf.verimag.bip.types.Type;
import bip2.ujf.verimag.bip.types.TypesFactory;
import bip2.ujf.verimag.bip.types.TypesPackage;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Queue;
import java.util.List;
import java.util.LinkedList;
import java.util.Set;

import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.common.notify.NotificationChain;
import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.common.util.EMap;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EStructuralFeature;
import org.eclipse.emf.common.util.BasicEList;

import org.eclipse.emf.ecore.InternalEObject;
import org.eclipse.emf.ecore.impl.ENotificationImpl;
import org.eclipse.emf.ecore.impl.EObjectImpl;
import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.EObjectResolvingEList;
import org.eclipse.emf.ecore.util.EcoreEMap;
import org.eclipse.emf.ecore.util.InternalEList;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Connector Type</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.ConnectorTypeImpl#getExportedPortDeclaration <em>Exported Port Declaration</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.ConnectorTypeImpl#getDataDeclarations <em>Data Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.ConnectorTypeImpl#getInteractions <em>Interactions</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.ConnectorTypeImpl#getInteractionDefinition <em>Interaction Definition</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.ConnectorTypeImpl#getPorts <em>Ports</em>}</li>
 * </ul>
 *
 * @generated
 */
public class ConnectorTypeImpl extends TypeImpl implements ConnectorType {

    /**
     * The cached value of the '{@link #getExportedPortDeclaration() <em>Exported Port Declaration</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getExportedPortDeclaration()
     * @generated
     * @ordered
     */
    protected ConnectorExportedPortDeclaration exportedPortDeclaration;
    /**
     * The cached value of the '{@link #getDataDeclarations() <em>Data Declarations</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getDataDeclarations()
     * @generated
     * @ordered
     */
    protected EList<ConnectorDataDeclaration> dataDeclarations;

    /**
     * The cached value of the '{@link #getInteractions() <em>Interactions</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getInteractions()
     * @generated
     * @ordered
     */
    protected EList<ConnectorInteractionAction> interactions;

    /**
     * The cached value of the '{@link #getInteractionDefinition() <em>Interaction Definition</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getInteractionDefinition()
     * @generated
     * @ordered
     */
    protected ConnectorInteractionDefinition interactionDefinition;

    /**
     * The cached value of the '{@link #getPorts() <em>Ports</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPorts()
     * @generated
     * @ordered
     */
    protected EList<ConnectorPortParameterDeclaration> ports;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected ConnectorTypeImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return TypesPackage.Literals.CONNECTOR_TYPE;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorExportedPortDeclaration getExportedPortDeclaration() {
        return exportedPortDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetExportedPortDeclaration(
            ConnectorExportedPortDeclaration newExportedPortDeclaration,
            NotificationChain msgs) {
        ConnectorExportedPortDeclaration oldExportedPortDeclaration = exportedPortDeclaration;
        exportedPortDeclaration = newExportedPortDeclaration;
        if (eNotificationRequired()) {
            ENotificationImpl notification = new ENotificationImpl(this,
                    Notification.SET,
                    TypesPackage.CONNECTOR_TYPE__EXPORTED_PORT_DECLARATION,
                    oldExportedPortDeclaration, newExportedPortDeclaration);
            if (msgs == null)
                msgs = notification;
            else
                msgs.add(notification);
        }
        return msgs;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setExportedPortDeclaration(
            ConnectorExportedPortDeclaration newExportedPortDeclaration) {
        if (newExportedPortDeclaration != exportedPortDeclaration) {
            NotificationChain msgs = null;
            if (exportedPortDeclaration != null)
                msgs = ((InternalEObject) exportedPortDeclaration)
                        .eInverseRemove(this, EOPPOSITE_FEATURE_BASE
                                - TypesPackage.CONNECTOR_TYPE__EXPORTED_PORT_DECLARATION,
                                null, msgs);
            if (newExportedPortDeclaration != null)
                msgs = ((InternalEObject) newExportedPortDeclaration)
                        .eInverseAdd(this, EOPPOSITE_FEATURE_BASE
                                - TypesPackage.CONNECTOR_TYPE__EXPORTED_PORT_DECLARATION,
                                null, msgs);
            msgs = basicSetExportedPortDeclaration(newExportedPortDeclaration,
                    msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    TypesPackage.CONNECTOR_TYPE__EXPORTED_PORT_DECLARATION,
                    newExportedPortDeclaration, newExportedPortDeclaration));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<ConnectorDataDeclaration> getDataDeclarations() {
        if (dataDeclarations == null) {
            dataDeclarations = new EObjectContainmentEList<ConnectorDataDeclaration>(
                    ConnectorDataDeclaration.class, this,
                    TypesPackage.CONNECTOR_TYPE__DATA_DECLARATIONS);
        }
        return dataDeclarations;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<ConnectorInteractionAction> getInteractions() {
        if (interactions == null) {
            interactions = new EObjectContainmentEList<ConnectorInteractionAction>(
                    ConnectorInteractionAction.class, this,
                    TypesPackage.CONNECTOR_TYPE__INTERACTIONS);
        }
        return interactions;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorInteractionDefinition getInteractionDefinition() {
        return interactionDefinition;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetInteractionDefinition(
            ConnectorInteractionDefinition newInteractionDefinition,
            NotificationChain msgs) {
        ConnectorInteractionDefinition oldInteractionDefinition = interactionDefinition;
        interactionDefinition = newInteractionDefinition;
        if (eNotificationRequired()) {
            ENotificationImpl notification = new ENotificationImpl(this,
                    Notification.SET,
                    TypesPackage.CONNECTOR_TYPE__INTERACTION_DEFINITION,
                    oldInteractionDefinition, newInteractionDefinition);
            if (msgs == null)
                msgs = notification;
            else
                msgs.add(notification);
        }
        return msgs;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setInteractionDefinition(
            ConnectorInteractionDefinition newInteractionDefinition) {
        if (newInteractionDefinition != interactionDefinition) {
            NotificationChain msgs = null;
            if (interactionDefinition != null)
                msgs = ((InternalEObject) interactionDefinition).eInverseRemove(
                        this,
                        EOPPOSITE_FEATURE_BASE
                                - TypesPackage.CONNECTOR_TYPE__INTERACTION_DEFINITION,
                        null, msgs);
            if (newInteractionDefinition != null)
                msgs = ((InternalEObject) newInteractionDefinition).eInverseAdd(
                        this,
                        EOPPOSITE_FEATURE_BASE
                                - TypesPackage.CONNECTOR_TYPE__INTERACTION_DEFINITION,
                        null, msgs);
            msgs = basicSetInteractionDefinition(newInteractionDefinition,
                    msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    TypesPackage.CONNECTOR_TYPE__INTERACTION_DEFINITION,
                    newInteractionDefinition, newInteractionDefinition));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<ConnectorPortParameterDeclaration> getPorts() {
        if (ports == null) {
            ports = new EObjectContainmentEList<ConnectorPortParameterDeclaration>(
                    ConnectorPortParameterDeclaration.class, this,
                    TypesPackage.CONNECTOR_TYPE__PORTS);
        }
        return ports;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public ConnectorPortParameterDeclaration getPortParameterDeclaration(
            String name) {
        for (ConnectorPortParameterDeclaration cpp : getPorts()) {
            if (cpp.getName().equals(name)) {
                return cpp;
            }
        }
        return null;
    }

    /**
     * Compute the support set of an interaction definition, i.e.
     * recursively the set of port parameters involved in the
     * corresponding tree of interaction definition.
     * @param definition the target interaction definition
     * @return the set of port parameters involved in definition
     * @generated NOT
     */
    private Set<ConnectorPortParameterDeclaration> support(
            ConnectorInteractionDefinition definition) {
        Set<ConnectorPortParameterDeclaration> ret = new HashSet<ConnectorPortParameterDeclaration>();

        if (definition instanceof ConnectorInteractionPortReference) {
            ConnectorInteractionPortReference portRef = (ConnectorInteractionPortReference) definition;

            ret.add(portRef.getPort());
        } else if (definition instanceof ConnectorInteractionNestedDefinition) {
            ConnectorInteractionNestedDefinition nestedDef = (ConnectorInteractionNestedDefinition) definition;

            for (ConnectorInteractionDefinition def : nestedDef
                    .getSubInteractions()) {
                ret.addAll(support(def));
            }
        } else {
            assert (false);
        }

        return ret;
    }

    /**
     * Returns true if (at least) a sub interaction definition of a nested
     * definition is quoted.
     * @param nested the target nested interaction definition
     * @return true if a sub interaction is quoted
     * @generated NOT
     */
    private boolean hasQuoted(ConnectorInteractionNestedDefinition nested) {
        boolean ret = false;

        for (ConnectorInteractionDefinition def : nested.getSubInteractions()) {
            if (def.isQuoted()) {
                ret = true;
                break;
            }
        }

        return ret;
    }

    /**
     * Returns true if a given set of port parameters do no intersect the
     * support of an interaction definition.
     * @param ports the target set of port parameters
     * @param definition the target interaction definition
     * @return true if ports do no intersect the support of definition
     * @generated NOT
     */
    private boolean isEmpty(Set<ConnectorPortParameterDeclaration> ports,
            ConnectorInteractionDefinition definition) {
        Set<ConnectorPortParameterDeclaration> portsOfSupport = support(
                definition);
        // intersect the support set of definition with the set of ports
        portsOfSupport.retainAll(ports);

        return portsOfSupport.isEmpty();
    }

    /**
     * Returns true if a given set of port parameters validate an interaction
     * definition, that is, if the subset of port parameters that belong to
     * the support of the interaction definition corresponds to a valid
     * interaction.
     * @param ports the target set of port parameters
     * @param definition the target interaction definition
     * @return true if ports intersected with support(definition) is a valid
     * interaction of definition
     * @generated NOT
     */
    private boolean isValid(Set<ConnectorPortParameterDeclaration> ports,
            ConnectorInteractionDefinition definition) {
        boolean ret = false;

        if (definition instanceof ConnectorInteractionPortReference) {
            // validity for a single port reference = should be in ports
            ret = ports.containsAll(support(definition));
        } else if (definition instanceof ConnectorInteractionNestedDefinition) {
            ConnectorInteractionNestedDefinition nestedDef = (ConnectorInteractionNestedDefinition) definition;
            if (!hasQuoted(nestedDef)) {
                ret = true;

                // synchron: all sub interactions should be valid
                for (ConnectorInteractionDefinition def : nestedDef
                        .getSubInteractions()) {
                    if (!isValid(ports, def)) {
                        ret = false;
                        break;
                    }
                }
            } else {
                // broadcast: sub interactions should be valid or empty,
                // and at least one trigger should be valid
                boolean allActiveOrEmpty = true;
                int activeTriggers = 0;

                for (ConnectorInteractionDefinition def : nestedDef
                        .getSubInteractions()) {
                    if (isValid(ports, def)) {
                        if (def.isQuoted()) {
                            activeTriggers++;
                        }
                    } else if (!isEmpty(ports, def)) {
                        allActiveOrEmpty = false;
                        break;
                    }
                }

                ret = allActiveOrEmpty && activeTriggers > 0;
            }
        } else {
            assert (false);
        }

        return ret;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean isDefined(EList<ConnectorPortParameterDeclaration> ports) {
        Set<ConnectorPortParameterDeclaration> setOfPorts = new HashSet<ConnectorPortParameterDeclaration>(
                ports);

        return isValid(setOfPorts, getInteractionDefinition())
                && support(getInteractionDefinition()).containsAll(setOfPorts);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public ConnectorDataDeclaration getDataDeclaration(String name) {
        for (ConnectorDataDeclaration cdd : getDataDeclarations()) {
            if (cdd.getName().equals(name)) {
                return cdd;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public NotificationChain eInverseRemove(InternalEObject otherEnd,
            int featureID, NotificationChain msgs) {
        switch (featureID) {
        case TypesPackage.CONNECTOR_TYPE__EXPORTED_PORT_DECLARATION:
            return basicSetExportedPortDeclaration(null, msgs);
        case TypesPackage.CONNECTOR_TYPE__DATA_DECLARATIONS:
            return ((InternalEList<?>) getDataDeclarations())
                    .basicRemove(otherEnd, msgs);
        case TypesPackage.CONNECTOR_TYPE__INTERACTIONS:
            return ((InternalEList<?>) getInteractions()).basicRemove(otherEnd,
                    msgs);
        case TypesPackage.CONNECTOR_TYPE__INTERACTION_DEFINITION:
            return basicSetInteractionDefinition(null, msgs);
        case TypesPackage.CONNECTOR_TYPE__PORTS:
            return ((InternalEList<?>) getPorts()).basicRemove(otherEnd, msgs);
        }
        return super.eInverseRemove(otherEnd, featureID, msgs);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eGet(int featureID, boolean resolve, boolean coreType) {
        switch (featureID) {
        case TypesPackage.CONNECTOR_TYPE__EXPORTED_PORT_DECLARATION:
            return getExportedPortDeclaration();
        case TypesPackage.CONNECTOR_TYPE__DATA_DECLARATIONS:
            return getDataDeclarations();
        case TypesPackage.CONNECTOR_TYPE__INTERACTIONS:
            return getInteractions();
        case TypesPackage.CONNECTOR_TYPE__INTERACTION_DEFINITION:
            return getInteractionDefinition();
        case TypesPackage.CONNECTOR_TYPE__PORTS:
            return getPorts();
        }
        return super.eGet(featureID, resolve, coreType);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @SuppressWarnings("unchecked")
    @Override
    public void eSet(int featureID, Object newValue) {
        switch (featureID) {
        case TypesPackage.CONNECTOR_TYPE__EXPORTED_PORT_DECLARATION:
            setExportedPortDeclaration(
                    (ConnectorExportedPortDeclaration) newValue);
            return;
        case TypesPackage.CONNECTOR_TYPE__DATA_DECLARATIONS:
            getDataDeclarations().clear();
            getDataDeclarations().addAll(
                    (Collection<? extends ConnectorDataDeclaration>) newValue);
            return;
        case TypesPackage.CONNECTOR_TYPE__INTERACTIONS:
            getInteractions().clear();
            getInteractions().addAll(
                    (Collection<? extends ConnectorInteractionAction>) newValue);
            return;
        case TypesPackage.CONNECTOR_TYPE__INTERACTION_DEFINITION:
            setInteractionDefinition((ConnectorInteractionDefinition) newValue);
            return;
        case TypesPackage.CONNECTOR_TYPE__PORTS:
            getPorts().clear();
            getPorts().addAll(
                    (Collection<? extends ConnectorPortParameterDeclaration>) newValue);
            return;
        }
        super.eSet(featureID, newValue);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public void eUnset(int featureID) {
        switch (featureID) {
        case TypesPackage.CONNECTOR_TYPE__EXPORTED_PORT_DECLARATION:
            setExportedPortDeclaration((ConnectorExportedPortDeclaration) null);
            return;
        case TypesPackage.CONNECTOR_TYPE__DATA_DECLARATIONS:
            getDataDeclarations().clear();
            return;
        case TypesPackage.CONNECTOR_TYPE__INTERACTIONS:
            getInteractions().clear();
            return;
        case TypesPackage.CONNECTOR_TYPE__INTERACTION_DEFINITION:
            setInteractionDefinition((ConnectorInteractionDefinition) null);
            return;
        case TypesPackage.CONNECTOR_TYPE__PORTS:
            getPorts().clear();
            return;
        }
        super.eUnset(featureID);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public boolean eIsSet(int featureID) {
        switch (featureID) {
        case TypesPackage.CONNECTOR_TYPE__EXPORTED_PORT_DECLARATION:
            return exportedPortDeclaration != null;
        case TypesPackage.CONNECTOR_TYPE__DATA_DECLARATIONS:
            return dataDeclarations != null && !dataDeclarations.isEmpty();
        case TypesPackage.CONNECTOR_TYPE__INTERACTIONS:
            return interactions != null && !interactions.isEmpty();
        case TypesPackage.CONNECTOR_TYPE__INTERACTION_DEFINITION:
            return interactionDefinition != null;
        case TypesPackage.CONNECTOR_TYPE__PORTS:
            return ports != null && !ports.isEmpty();
        }
        return super.eIsSet(featureID);
    }

} //ConnectorTypeImpl
