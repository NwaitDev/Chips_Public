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

package bip2.ujf.verimag.bip.actionlang.impl;

import bip2.ujf.verimag.bip.actionlang.ActionlangPackage;
import bip2.ujf.verimag.bip.actionlang.BinaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.BinaryOperators;
import bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.Expression;
import bip2.ujf.verimag.bip.actionlang.ValuedExpression;

import bip2.ujf.verimag.bip.packaging.BinaryOpPrototype;
import bip2.ujf.verimag.bip.packaging.PrototypeParameterDeclaration;
import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataType;
import bip2.ujf.verimag.bip.packaging.BipPackage;
import bip2.ujf.verimag.bip.types.Type;

import java.util.Collection;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.BasicEList;
import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import org.eclipse.emf.ecore.impl.EObjectImpl;

import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.InternalEList;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Binary Op Expression</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.impl.BinaryOpExpressionImpl#getOperator <em>Operator</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.impl.BinaryOpExpressionImpl#getLeft <em>Left</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.impl.BinaryOpExpressionImpl#getRight <em>Right</em>}</li>
 * </ul>
 *
 * @generated
 */
public class BinaryOpExpressionImpl extends ValuedExpressionImpl
        implements BinaryOpExpression {
    /**
     * The default value of the '{@link #getOperator() <em>Operator</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getOperator()
     * @generated
     * @ordered
     */
    protected static final BinaryOperators OPERATOR_EDEFAULT = BinaryOperators.ADDITION;

    /**
     * The cached value of the '{@link #getOperator() <em>Operator</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getOperator()
     * @generated
     * @ordered
     */
    protected BinaryOperators operator = OPERATOR_EDEFAULT;

    /**
     * The cached value of the '{@link #getLeft() <em>Left</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getLeft()
     * @generated
     * @ordered
     */
    protected ValuedExpression left;

    /**
     * The cached value of the '{@link #getRight() <em>Right</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getRight()
     * @generated
     * @ordered
     */
    protected ValuedExpression right;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected BinaryOpExpressionImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return ActionlangPackage.Literals.BINARY_OP_EXPRESSION;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public BinaryOperators getOperator() {
        return operator;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setOperator(BinaryOperators newOperator) {
        BinaryOperators oldOperator = operator;
        operator = newOperator == null ? OPERATOR_EDEFAULT : newOperator;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    ActionlangPackage.BINARY_OP_EXPRESSION__OPERATOR,
                    oldOperator, operator));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ValuedExpression getLeft() {
        return left;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetLeft(ValuedExpression newLeft,
            NotificationChain msgs) {
        ValuedExpression oldLeft = left;
        left = newLeft;
        if (eNotificationRequired()) {
            ENotificationImpl notification = new ENotificationImpl(this,
                    Notification.SET,
                    ActionlangPackage.BINARY_OP_EXPRESSION__LEFT, oldLeft,
                    newLeft);
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
     * @generated NOT
     */
    public void setLeft(ValuedExpression newLeft) {
        assert (this != newLeft);
        if (newLeft != left) {
            NotificationChain msgs = null;
            if (left != null)
                msgs = ((InternalEObject) left).eInverseRemove(this,
                        EOPPOSITE_FEATURE_BASE
                                - ActionlangPackage.BINARY_OP_EXPRESSION__LEFT,
                        null, msgs);
            if (newLeft != null)
                msgs = ((InternalEObject) newLeft).eInverseAdd(this,
                        EOPPOSITE_FEATURE_BASE
                                - ActionlangPackage.BINARY_OP_EXPRESSION__LEFT,
                        null, msgs);
            msgs = basicSetLeft(newLeft, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    ActionlangPackage.BINARY_OP_EXPRESSION__LEFT, newLeft,
                    newLeft));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ValuedExpression getRight() {
        return right;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetRight(ValuedExpression newRight,
            NotificationChain msgs) {
        ValuedExpression oldRight = right;
        right = newRight;
        if (eNotificationRequired()) {
            ENotificationImpl notification = new ENotificationImpl(this,
                    Notification.SET,
                    ActionlangPackage.BINARY_OP_EXPRESSION__RIGHT, oldRight,
                    newRight);
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
     * @generated NOT
     */
    public void setRight(ValuedExpression newRight) {
        assert (this != newRight);
        if (newRight != right) {
            NotificationChain msgs = null;
            if (right != null)
                msgs = ((InternalEObject) right).eInverseRemove(this,
                        EOPPOSITE_FEATURE_BASE
                                - ActionlangPackage.BINARY_OP_EXPRESSION__RIGHT,
                        null, msgs);
            if (newRight != null)
                msgs = ((InternalEObject) newRight).eInverseAdd(this,
                        EOPPOSITE_FEATURE_BASE
                                - ActionlangPackage.BINARY_OP_EXPRESSION__RIGHT,
                        null, msgs);
            msgs = basicSetRight(newRight, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    ActionlangPackage.BINARY_OP_EXPRESSION__RIGHT, newRight,
                    newRight));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    private EList<BinaryOpPrototype> getPrototypesIn(BipPackage pack) {
        EList<BinaryOpPrototype> ret = new BasicEList<BinaryOpPrototype>();

        // compute types of parameters of the function call
        EList<Type> parametersTypes = new BasicEList<Type>();

        parametersTypes.add(getLeft().getType());
        parametersTypes.add(getRight().getType());

        // compute all prototypes matching function name and compatible parameters
        EList<BinaryOpPrototype> matching = pack
                .getBinaryOpPrototypes(getOperator(), parametersTypes);

        // keep only the maximal ones w.r.t. isRefiningParametersOf()
        for (BinaryOpPrototype prototype : matching) {
            boolean keepIt = true;

            for (BinaryOpPrototype testPrototype : matching) {
                if (prototype != testPrototype && testPrototype
                        .isBetterMatchingThan(parametersTypes, prototype)) {
                    keepIt = false;
                    break;
                }
            }

            if (keepIt) {
                ret.add(prototype);
            }
        }

        return ret;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    private EList<BinaryOpPrototype> getPrototypesInAllUsedPackages(
            BipPackage pack) {
        Set<BinaryOpPrototype> ret = new HashSet<BinaryOpPrototype>();

        for (BipPackage usedPackage : pack.getUsed_packages()) {
            ret.addAll(getPrototypesIn(usedPackage));
            ret.addAll(getPrototypesInAllUsedPackages(usedPackage));
        }

        return new BasicEList<BinaryOpPrototype>(ret);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public EList<BinaryOpPrototype> getPrototypes() {
        Set<BinaryOpPrototype> ret = new HashSet<BinaryOpPrototype>();

        BipPackage currentPackage = getPackage();

        // look for prototypes in the current package
        ret.addAll(getPrototypesIn(currentPackage));

        if (ret.isEmpty()) {
            // look for prototypes in used packages
            ret.addAll(getPrototypesInAllUsedPackages(currentPackage));
        }

        return new BasicEList<BinaryOpPrototype>(ret);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public Type getType() {
        Type ret = null;

        EList<BinaryOpPrototype> prototypes = getPrototypes();

        if (prototypes.size() == 1) {
            ret = prototypes.get(0).getReturnType();
        }

        return ret;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean isConst() {
        boolean ret = false;

        EList<BinaryOpPrototype> prototypes = getPrototypes();

        if (prototypes.size() == 1) {
            ret = prototypes.get(0).isConst();
        }

        return ret;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean hasSideEffect() {
        boolean ret = false;

        EList<BinaryOpPrototype> prototypes = getPrototypes();

        if (prototypes.size() == 1) {
            for (PrototypeParameterDeclaration dataDeclaration : prototypes
                    .get(0).getParameterDeclarations()) {
                if (!dataDeclaration.isConst()) {
                    ret = true;
                    break;
                }
            }
        }

        return ret;
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
        case ActionlangPackage.BINARY_OP_EXPRESSION__LEFT:
            return basicSetLeft(null, msgs);
        case ActionlangPackage.BINARY_OP_EXPRESSION__RIGHT:
            return basicSetRight(null, msgs);
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
        case ActionlangPackage.BINARY_OP_EXPRESSION__OPERATOR:
            return getOperator();
        case ActionlangPackage.BINARY_OP_EXPRESSION__LEFT:
            return getLeft();
        case ActionlangPackage.BINARY_OP_EXPRESSION__RIGHT:
            return getRight();
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
        case ActionlangPackage.BINARY_OP_EXPRESSION__OPERATOR:
            setOperator((BinaryOperators) newValue);
            return;
        case ActionlangPackage.BINARY_OP_EXPRESSION__LEFT:
            setLeft((ValuedExpression) newValue);
            return;
        case ActionlangPackage.BINARY_OP_EXPRESSION__RIGHT:
            setRight((ValuedExpression) newValue);
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
        case ActionlangPackage.BINARY_OP_EXPRESSION__OPERATOR:
            setOperator(OPERATOR_EDEFAULT);
            return;
        case ActionlangPackage.BINARY_OP_EXPRESSION__LEFT:
            setLeft((ValuedExpression) null);
            return;
        case ActionlangPackage.BINARY_OP_EXPRESSION__RIGHT:
            setRight((ValuedExpression) null);
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
        case ActionlangPackage.BINARY_OP_EXPRESSION__OPERATOR:
            return operator != OPERATOR_EDEFAULT;
        case ActionlangPackage.BINARY_OP_EXPRESSION__LEFT:
            return left != null;
        case ActionlangPackage.BINARY_OP_EXPRESSION__RIGHT:
            return right != null;
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
        result.append(" (operator: ");
        result.append(operator);
        result.append(')');
        return result.toString();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> geReadVariables() {
        Set<DataDeclaration> ret = new HashSet<DataDeclaration>();

        ret.addAll(getLeft().getReadVariables());
        ret.addAll(getRight().getReadVariables());

        return new BasicEList<DataDeclaration>(ret);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getMayReadVariables() {
        Set<DataDeclaration> ret = new HashSet<DataDeclaration>();

        ret.addAll(getLeft().getMayReadVariables());
        ret.addAll(getRight().getMayReadVariables());

        return new BasicEList<DataDeclaration>(ret);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getWriteVariables() {
        Set<DataDeclaration> ret = new HashSet<DataDeclaration>();

        ret.addAll(getLeft().getWriteVariables());
        ret.addAll(getRight().getWriteVariables());

        return new BasicEList<DataDeclaration>(ret);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getMayWriteVariables() {
        Set<DataDeclaration> ret = new HashSet<DataDeclaration>();
        EList<BinaryOpPrototype> prototypes = getPrototypes();

        assert (prototypes.size() == 1);

        BinaryOpPrototype prototype = prototypes.get(0);

        assert (prototype.getParameterDeclarations().size() == 2);

        if (prototype.getParameterDeclarations().get(0).isConst()) {
            ret.addAll(getLeft().getMayWriteVariables());
        } else {
            ret.addAll(getLeft().getMayReadVariables());
        }

        if (prototype.getParameterDeclarations().get(1).isConst()) {
            ret.addAll(getRight().getMayWriteVariables());
        } else {
            ret.addAll(getRight().getMayReadVariables());
        }

        return new BasicEList<DataDeclaration>(ret);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<Expression> getMayReadUninitializedVariables(
            EList<DataDeclaration> uninitialized) {
        EList<Expression> ret = new BasicEList<Expression>();

        // /!\ no assumption is made on the execution order of binary expressions
        // => copy initialized variables

        // left hand side
        EList<DataDeclaration> leftUninitializedVariables = new BasicEList<DataDeclaration>(
                uninitialized);

        ret.addAll(getLeft()
                .getMayReadUninitializedVariables(leftUninitializedVariables));

        // right hand side
        EList<DataDeclaration> rightUninitializedVariables = new BasicEList<DataDeclaration>(
                uninitialized);

        ret.addAll(getRight()
                .getMayReadUninitializedVariables(rightUninitializedVariables));

        // update uninitialized variables
        uninitialized.retainAll(leftUninitializedVariables);
        uninitialized.retainAll(rightUninitializedVariables);

        return ret;
    }

} //BinaryOpExpressionImpl
