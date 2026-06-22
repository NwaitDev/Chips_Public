/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
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

package bip2.ujf.verimag.bip.port.impl;

import bip2.ujf.verimag.bip.port.PortDeclaration;
import bip2.ujf.verimag.bip.port.PortDeclarationReferenceParameter;
import bip2.ujf.verimag.bip.port.PortPackage;
import bip2.ujf.verimag.bip.port.SubPortDeclarationReference;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

import org.eclipse.emf.ecore.impl.EObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Declaration Reference Parameter</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.port.impl.PortDeclarationReferenceParameterImpl#getParameterDeclaration <em>Parameter Declaration</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.port.impl.PortDeclarationReferenceParameterImpl#getSubPortDeclarationReference <em>Sub Port Declaration Reference</em>}</li>
 * </ul>
 *
 * @generated
 */
public class PortDeclarationReferenceParameterImpl extends AnnotatedEObjectImpl
        implements PortDeclarationReferenceParameter {
    /**
     * The cached value of the '{@link #getParameterDeclaration() <em>Parameter Declaration</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getParameterDeclaration()
     * @generated
     * @ordered
     */
    protected PortDeclaration parameterDeclaration;

    /**
     * The cached value of the '{@link #getSubPortDeclarationReference() <em>Sub Port Declaration Reference</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getSubPortDeclarationReference()
     * @generated
     * @ordered
     */
    protected SubPortDeclarationReference subPortDeclarationReference;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected PortDeclarationReferenceParameterImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return PortPackage.Literals.PORT_DECLARATION_REFERENCE_PARAMETER;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public PortDeclaration getParameterDeclaration() {
        if (parameterDeclaration != null
                && ((EObject) parameterDeclaration).eIsProxy()) {
            InternalEObject oldParameterDeclaration = (InternalEObject) parameterDeclaration;
            parameterDeclaration = (PortDeclaration) eResolveProxy(
                    oldParameterDeclaration);
            if (parameterDeclaration != oldParameterDeclaration) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            PortPackage.PORT_DECLARATION_REFERENCE_PARAMETER__PARAMETER_DECLARATION,
                            oldParameterDeclaration, parameterDeclaration));
            }
        }
        return parameterDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public PortDeclaration basicGetParameterDeclaration() {
        return parameterDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setParameterDeclaration(
            PortDeclaration newParameterDeclaration) {
        PortDeclaration oldParameterDeclaration = parameterDeclaration;
        parameterDeclaration = newParameterDeclaration;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PortPackage.PORT_DECLARATION_REFERENCE_PARAMETER__PARAMETER_DECLARATION,
                    oldParameterDeclaration, parameterDeclaration));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public SubPortDeclarationReference getSubPortDeclarationReference() {
        return subPortDeclarationReference;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetSubPortDeclarationReference(
            SubPortDeclarationReference newSubPortDeclarationReference,
            NotificationChain msgs) {
        SubPortDeclarationReference oldSubPortDeclarationReference = subPortDeclarationReference;
        subPortDeclarationReference = newSubPortDeclarationReference;
        if (eNotificationRequired()) {
            ENotificationImpl notification = new ENotificationImpl(this,
                    Notification.SET,
                    PortPackage.PORT_DECLARATION_REFERENCE_PARAMETER__SUB_PORT_DECLARATION_REFERENCE,
                    oldSubPortDeclarationReference,
                    newSubPortDeclarationReference);
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
    public void setSubPortDeclarationReference(
            SubPortDeclarationReference newSubPortDeclarationReference) {
        if (newSubPortDeclarationReference != subPortDeclarationReference) {
            NotificationChain msgs = null;
            if (subPortDeclarationReference != null)
                msgs = ((InternalEObject) subPortDeclarationReference)
                        .eInverseRemove(this, EOPPOSITE_FEATURE_BASE
                                - PortPackage.PORT_DECLARATION_REFERENCE_PARAMETER__SUB_PORT_DECLARATION_REFERENCE,
                                null, msgs);
            if (newSubPortDeclarationReference != null)
                msgs = ((InternalEObject) newSubPortDeclarationReference)
                        .eInverseAdd(this, EOPPOSITE_FEATURE_BASE
                                - PortPackage.PORT_DECLARATION_REFERENCE_PARAMETER__SUB_PORT_DECLARATION_REFERENCE,
                                null, msgs);
            msgs = basicSetSubPortDeclarationReference(
                    newSubPortDeclarationReference, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PortPackage.PORT_DECLARATION_REFERENCE_PARAMETER__SUB_PORT_DECLARATION_REFERENCE,
                    newSubPortDeclarationReference,
                    newSubPortDeclarationReference));
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
        case PortPackage.PORT_DECLARATION_REFERENCE_PARAMETER__SUB_PORT_DECLARATION_REFERENCE:
            return basicSetSubPortDeclarationReference(null, msgs);
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
        case PortPackage.PORT_DECLARATION_REFERENCE_PARAMETER__PARAMETER_DECLARATION:
            if (resolve)
                return getParameterDeclaration();
            return basicGetParameterDeclaration();
        case PortPackage.PORT_DECLARATION_REFERENCE_PARAMETER__SUB_PORT_DECLARATION_REFERENCE:
            return getSubPortDeclarationReference();
        }
        return super.eGet(featureID, resolve, coreType);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public void eSet(int featureID, Object newValue) {
        switch (featureID) {
        case PortPackage.PORT_DECLARATION_REFERENCE_PARAMETER__PARAMETER_DECLARATION:
            setParameterDeclaration((PortDeclaration) newValue);
            return;
        case PortPackage.PORT_DECLARATION_REFERENCE_PARAMETER__SUB_PORT_DECLARATION_REFERENCE:
            setSubPortDeclarationReference(
                    (SubPortDeclarationReference) newValue);
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
        case PortPackage.PORT_DECLARATION_REFERENCE_PARAMETER__PARAMETER_DECLARATION:
            setParameterDeclaration((PortDeclaration) null);
            return;
        case PortPackage.PORT_DECLARATION_REFERENCE_PARAMETER__SUB_PORT_DECLARATION_REFERENCE:
            setSubPortDeclarationReference((SubPortDeclarationReference) null);
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
        case PortPackage.PORT_DECLARATION_REFERENCE_PARAMETER__PARAMETER_DECLARATION:
            return parameterDeclaration != null;
        case PortPackage.PORT_DECLARATION_REFERENCE_PARAMETER__SUB_PORT_DECLARATION_REFERENCE:
            return subPortDeclarationReference != null;
        }
        return super.eIsSet(featureID);
    }

} //PortDeclarationReferenceParameterImpl
