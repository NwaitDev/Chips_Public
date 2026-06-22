/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
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

package bip2.ujf.verimag.bip.packaging.impl;

import bip2.ujf.verimag.bip.annotation.impl.AnnotatedElementImpl;

import bip2.ujf.verimag.bip.packaging.PackagingPackage;
import bip2.ujf.verimag.bip.packaging.Prototype;
import bip2.ujf.verimag.bip.packaging.PrototypeParameterDeclaration;

import bip2.ujf.verimag.bip.types.Type;

import java.util.Collection;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;

import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.InternalEList;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Prototype</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.impl.PrototypeImpl#getParameterDeclarations <em>Parameter Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.impl.PrototypeImpl#getReturnType <em>Return Type</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.impl.PrototypeImpl#isNative <em>Native</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.impl.PrototypeImpl#isConst <em>Const</em>}</li>
 * </ul>
 *
 * @generated
 */
public abstract class PrototypeImpl extends AnnotatedElementImpl
        implements Prototype {
    /**
     * The cached value of the '{@link #getParameterDeclarations() <em>Parameter Declarations</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getParameterDeclarations()
     * @generated
     * @ordered
     */
    protected EList<PrototypeParameterDeclaration> parameterDeclarations;

    /**
     * The cached value of the '{@link #getReturnType() <em>Return Type</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getReturnType()
     * @generated
     * @ordered
     */
    protected Type returnType;

    /**
     * The default value of the '{@link #isNative() <em>Native</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #isNative()
     * @generated
     * @ordered
     */
    protected static final boolean NATIVE_EDEFAULT = false;

    /**
     * The cached value of the '{@link #isNative() <em>Native</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #isNative()
     * @generated
     * @ordered
     */
    protected boolean native_ = NATIVE_EDEFAULT;

    /**
     * The default value of the '{@link #isConst() <em>Const</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #isConst()
     * @generated
     * @ordered
     */
    protected static final boolean CONST_EDEFAULT = false;

    /**
     * The cached value of the '{@link #isConst() <em>Const</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #isConst()
     * @generated
     * @ordered
     */
    protected boolean const_ = CONST_EDEFAULT;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected PrototypeImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return PackagingPackage.Literals.PROTOTYPE;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<PrototypeParameterDeclaration> getParameterDeclarations() {
        if (parameterDeclarations == null) {
            parameterDeclarations = new EObjectContainmentEList<PrototypeParameterDeclaration>(
                    PrototypeParameterDeclaration.class, this,
                    PackagingPackage.PROTOTYPE__PARAMETER_DECLARATIONS);
        }
        return parameterDeclarations;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public Type getReturnType() {
        if (returnType != null && ((EObject) returnType).eIsProxy()) {
            InternalEObject oldReturnType = (InternalEObject) returnType;
            returnType = (Type) eResolveProxy(oldReturnType);
            if (returnType != oldReturnType) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            PackagingPackage.PROTOTYPE__RETURN_TYPE,
                            oldReturnType, returnType));
            }
        }
        return returnType;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public Type basicGetReturnType() {
        return returnType;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setReturnType(Type newReturnType) {
        Type oldReturnType = returnType;
        returnType = newReturnType;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PackagingPackage.PROTOTYPE__RETURN_TYPE, oldReturnType,
                    returnType));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean isNative() {
        return native_;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setNative(boolean newNative) {
        boolean oldNative = native_;
        native_ = newNative;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PackagingPackage.PROTOTYPE__NATIVE, oldNative, native_));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean isConst() {
        return const_;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setConst(boolean newConst) {
        boolean oldConst = const_;
        const_ = newConst;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PackagingPackage.PROTOTYPE__CONST, oldConst, const_));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean isBetterMatchingThan(EList<Type> types,
            Prototype prototype) {
        boolean oneIsBetter = false;
        boolean allAreNotWorse = true;

        assert (getParameterDeclarations().size() == types.size());

        assert (getParameterDeclarations().size() == prototype
                .getParameterDeclarations().size());

        for (int i = 0; i < getParameterDeclarations().size(); i++) {
            Type paramType = types.get(i);
            Type protoType1 = getParameterDeclarations().get(i).getType();
            Type protoType2 = prototype.getParameterDeclarations().get(i)
                    .getType();

            assert (paramType.isKindOf(protoType1));
            assert (paramType.isKindOf(protoType2));

            if ((paramType == protoType1 && paramType != protoType2)
                    || protoType1.isSubTypeOf(protoType2)) {
                oneIsBetter = true;
            }

            if ((paramType == protoType2 && paramType != protoType1)
                    || protoType2.isSubTypeOf(protoType1)) {
                allAreNotWorse = false;
            }
        }

        return oneIsBetter && allAreNotWorse;
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
        case PackagingPackage.PROTOTYPE__PARAMETER_DECLARATIONS:
            return ((InternalEList<?>) getParameterDeclarations())
                    .basicRemove(otherEnd, msgs);
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
        case PackagingPackage.PROTOTYPE__PARAMETER_DECLARATIONS:
            return getParameterDeclarations();
        case PackagingPackage.PROTOTYPE__RETURN_TYPE:
            if (resolve)
                return getReturnType();
            return basicGetReturnType();
        case PackagingPackage.PROTOTYPE__NATIVE:
            return isNative();
        case PackagingPackage.PROTOTYPE__CONST:
            return isConst();
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
        case PackagingPackage.PROTOTYPE__PARAMETER_DECLARATIONS:
            getParameterDeclarations().clear();
            getParameterDeclarations().addAll(
                    (Collection<? extends PrototypeParameterDeclaration>) newValue);
            return;
        case PackagingPackage.PROTOTYPE__RETURN_TYPE:
            setReturnType((Type) newValue);
            return;
        case PackagingPackage.PROTOTYPE__NATIVE:
            setNative((Boolean) newValue);
            return;
        case PackagingPackage.PROTOTYPE__CONST:
            setConst((Boolean) newValue);
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
        case PackagingPackage.PROTOTYPE__PARAMETER_DECLARATIONS:
            getParameterDeclarations().clear();
            return;
        case PackagingPackage.PROTOTYPE__RETURN_TYPE:
            setReturnType((Type) null);
            return;
        case PackagingPackage.PROTOTYPE__NATIVE:
            setNative(NATIVE_EDEFAULT);
            return;
        case PackagingPackage.PROTOTYPE__CONST:
            setConst(CONST_EDEFAULT);
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
        case PackagingPackage.PROTOTYPE__PARAMETER_DECLARATIONS:
            return parameterDeclarations != null
                    && !parameterDeclarations.isEmpty();
        case PackagingPackage.PROTOTYPE__RETURN_TYPE:
            return returnType != null;
        case PackagingPackage.PROTOTYPE__NATIVE:
            return native_ != NATIVE_EDEFAULT;
        case PackagingPackage.PROTOTYPE__CONST:
            return const_ != CONST_EDEFAULT;
        }
        return super.eIsSet(featureID);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public String toString() {
        if (eIsProxy())
            return super.toString();

        StringBuffer result = new StringBuffer(super.toString());
        result.append(" (native: ");
        result.append(native_);
        result.append(", const: ");
        result.append(const_);
        result.append(')');
        return result.toString();
    }

} //PrototypeImpl
