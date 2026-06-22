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

package bip2.ujf.verimag.bip.types.impl;

import bip2.ujf.verimag.bip.annotation.impl.AnnotatedElementImpl;

import bip2.ujf.verimag.bip.types.Type;
import bip2.ujf.verimag.bip.types.TypesPackage;

import java.util.Collection;

import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;

import org.eclipse.emf.ecore.impl.ENotificationImpl;

import org.eclipse.emf.ecore.util.EObjectResolvingEList;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Type</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.TypeImpl#getName <em>Name</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.TypeImpl#isNative <em>Native</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.TypeImpl#getSuperTypes <em>Super Types</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.TypeImpl#getCastableTypes <em>Castable Types</em>}</li>
 * </ul>
 *
 * @generated
 */
public abstract class TypeImpl extends AnnotatedElementImpl implements Type {
    /**
     * The default value of the '{@link #getName() <em>Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getName()
     * @generated
     * @ordered
     */
    protected static final String NAME_EDEFAULT = null;

    /**
     * The cached value of the '{@link #getName() <em>Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getName()
     * @generated
     * @ordered
     */
    protected String name = NAME_EDEFAULT;

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
     * The cached value of the '{@link #getSuperTypes() <em>Super Types</em>}' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getSuperTypes()
     * @generated
     * @ordered
     */
    protected EList<Type> superTypes;

    /**
     * The cached value of the '{@link #getCastableTypes() <em>Castable Types</em>}' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getCastableTypes()
     * @generated
     * @ordered
     */
    protected EList<Type> castableTypes;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected TypeImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return TypesPackage.Literals.TYPE;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public String getName() {
        return name;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setName(String newName) {
        String oldName = name;
        name = newName;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    TypesPackage.TYPE__NAME, oldName, name));
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
                    TypesPackage.TYPE__NATIVE, oldNative, native_));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<Type> getSuperTypes() {
        if (superTypes == null) {
            superTypes = new EObjectResolvingEList<Type>(Type.class, this,
                    TypesPackage.TYPE__SUPER_TYPES);
        }
        return superTypes;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<Type> getCastableTypes() {
        if (castableTypes == null) {
            castableTypes = new EObjectResolvingEList<Type>(Type.class, this,
                    TypesPackage.TYPE__CASTABLE_TYPES);
        }
        return castableTypes;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean isKindOf(Type type) {
        boolean ret = false;

        if (this == type) {
            ret = true;
        } else if (this.isNative() && type.isNative()
                && this.getName().equals(type.getName())) {
            ret = true;
        } else if (type.hasCastFor(this)) {
            ret = true;
        } else {
            ret = isSubTypeOf(type);
        }

        return ret;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean isSubTypeOf(Type type) {
        boolean ret = false;

        for (Type superType : getSuperTypes()) {
            if (superType.isKindOf(type)) {
                ret = true;
                break;
            }
        }

        return ret;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean hasCastFor(Type type) {
        return getCastableTypes().contains(type);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eGet(int featureID, boolean resolve, boolean coreType) {
        switch (featureID) {
        case TypesPackage.TYPE__NAME:
            return getName();
        case TypesPackage.TYPE__NATIVE:
            return isNative();
        case TypesPackage.TYPE__SUPER_TYPES:
            return getSuperTypes();
        case TypesPackage.TYPE__CASTABLE_TYPES:
            return getCastableTypes();
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
        case TypesPackage.TYPE__NAME:
            setName((String) newValue);
            return;
        case TypesPackage.TYPE__NATIVE:
            setNative((Boolean) newValue);
            return;
        case TypesPackage.TYPE__SUPER_TYPES:
            getSuperTypes().clear();
            getSuperTypes().addAll((Collection<? extends Type>) newValue);
            return;
        case TypesPackage.TYPE__CASTABLE_TYPES:
            getCastableTypes().clear();
            getCastableTypes().addAll((Collection<? extends Type>) newValue);
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
        case TypesPackage.TYPE__NAME:
            setName(NAME_EDEFAULT);
            return;
        case TypesPackage.TYPE__NATIVE:
            setNative(NATIVE_EDEFAULT);
            return;
        case TypesPackage.TYPE__SUPER_TYPES:
            getSuperTypes().clear();
            return;
        case TypesPackage.TYPE__CASTABLE_TYPES:
            getCastableTypes().clear();
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
        case TypesPackage.TYPE__NAME:
            return NAME_EDEFAULT == null ? name != null
                    : !NAME_EDEFAULT.equals(name);
        case TypesPackage.TYPE__NATIVE:
            return native_ != NATIVE_EDEFAULT;
        case TypesPackage.TYPE__SUPER_TYPES:
            return superTypes != null && !superTypes.isEmpty();
        case TypesPackage.TYPE__CASTABLE_TYPES:
            return castableTypes != null && !castableTypes.isEmpty();
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
        result.append(" (name: ");
        result.append(name);
        result.append(", native: ");
        result.append(native_);
        result.append(')');
        return result.toString();
    }

} //TypeImpl
