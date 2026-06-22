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

package bip2.ujf.verimag.bip.instance.impl;

import bip2.ujf.verimag.bip.data.DataDeclaration;

import bip2.ujf.verimag.bip.instance.DataInstance;
import bip2.ujf.verimag.bip.instance.InstancePackage;

import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

import org.eclipse.emf.ecore.impl.EObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Data Instance</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.DataInstanceImpl#getDeclaration <em>Declaration</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.DataInstanceImpl#getProxyLink <em>Proxy Link</em>}</li>
 * </ul>
 *
 * @generated
 */
public class DataInstanceImpl extends AnnotatedEObjectImpl
        implements DataInstance {
    /**
     * The cached value of the '{@link #getDeclaration() <em>Declaration</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getDeclaration()
     * @generated
     * @ordered
     */
    protected DataDeclaration declaration;

    /**
     * The cached value of the '{@link #getProxyLink() <em>Proxy Link</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getProxyLink()
     * @generated
     * @ordered
     */
    protected DataInstance proxyLink;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected DataInstanceImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return InstancePackage.Literals.DATA_INSTANCE;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataDeclaration getDeclaration() {
        if (declaration != null && ((EObject) declaration).eIsProxy()) {
            InternalEObject oldDeclaration = (InternalEObject) declaration;
            declaration = (DataDeclaration) eResolveProxy(oldDeclaration);
            if (declaration != oldDeclaration) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            InstancePackage.DATA_INSTANCE__DECLARATION,
                            oldDeclaration, declaration));
            }
        }
        return declaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataDeclaration basicGetDeclaration() {
        return declaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setDeclaration(DataDeclaration newDeclaration) {
        DataDeclaration oldDeclaration = declaration;
        declaration = newDeclaration;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    InstancePackage.DATA_INSTANCE__DECLARATION, oldDeclaration,
                    declaration));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataInstance getProxyLink() {
        if (proxyLink != null && ((EObject) proxyLink).eIsProxy()) {
            InternalEObject oldProxyLink = (InternalEObject) proxyLink;
            proxyLink = (DataInstance) eResolveProxy(oldProxyLink);
            if (proxyLink != oldProxyLink) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            InstancePackage.DATA_INSTANCE__PROXY_LINK,
                            oldProxyLink, proxyLink));
            }
        }
        return proxyLink;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataInstance basicGetProxyLink() {
        return proxyLink;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setProxyLink(DataInstance newProxyLink) {
        DataInstance oldProxyLink = proxyLink;
        proxyLink = newProxyLink;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    InstancePackage.DATA_INSTANCE__PROXY_LINK, oldProxyLink,
                    proxyLink));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eGet(int featureID, boolean resolve, boolean coreType) {
        switch (featureID) {
        case InstancePackage.DATA_INSTANCE__DECLARATION:
            if (resolve)
                return getDeclaration();
            return basicGetDeclaration();
        case InstancePackage.DATA_INSTANCE__PROXY_LINK:
            if (resolve)
                return getProxyLink();
            return basicGetProxyLink();
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
        case InstancePackage.DATA_INSTANCE__DECLARATION:
            setDeclaration((DataDeclaration) newValue);
            return;
        case InstancePackage.DATA_INSTANCE__PROXY_LINK:
            setProxyLink((DataInstance) newValue);
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
        case InstancePackage.DATA_INSTANCE__DECLARATION:
            setDeclaration((DataDeclaration) null);
            return;
        case InstancePackage.DATA_INSTANCE__PROXY_LINK:
            setProxyLink((DataInstance) null);
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
        case InstancePackage.DATA_INSTANCE__DECLARATION:
            return declaration != null;
        case InstancePackage.DATA_INSTANCE__PROXY_LINK:
            return proxyLink != null;
        }
        return super.eIsSet(featureID);
    }

} //DataInstanceImpl
