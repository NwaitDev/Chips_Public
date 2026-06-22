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

import java.util.List;

import bip2.ujf.verimag.bip.actionlang.ActionlangPackage;
import bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.Expression;
import bip2.ujf.verimag.bip.actionlang.UnaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.UnaryOperators;
import bip2.ujf.verimag.bip.actionlang.ValuedExpression;

import bip2.ujf.verimag.bip.packaging.PrototypeParameterDeclaration;
import bip2.ujf.verimag.bip.packaging.UnaryOpPrototype;
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
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

import org.eclipse.emf.ecore.impl.EObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Unary Op Expression</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.impl.UnaryOpExpressionImpl#getOperator <em>Operator</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.impl.UnaryOpExpressionImpl#getOperand <em>Operand</em>}</li>
 * </ul>
 *
 * @generated
 */
public class UnaryOpExpressionImpl extends ValuedExpressionImpl
        implements UnaryOpExpression {
    /**
     * The default value of the '{@link #getOperator() <em>Operator</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getOperator()
     * @generated
     * @ordered
     */
    protected static final UnaryOperators OPERATOR_EDEFAULT = UnaryOperators.PLUS;

    /**
     * The cached value of the '{@link #getOperator() <em>Operator</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getOperator()
     * @generated
     * @ordered
     */
    protected UnaryOperators operator = OPERATOR_EDEFAULT;

    /**
     * The cached value of the '{@link #getOperand() <em>Operand</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getOperand()
     * @generated
     * @ordered
     */
    protected ValuedExpression operand;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected UnaryOpExpressionImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return ActionlangPackage.Literals.UNARY_OP_EXPRESSION;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public UnaryOperators getOperator() {
        return operator;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setOperator(UnaryOperators newOperator) {
        UnaryOperators oldOperator = operator;
        operator = newOperator == null ? OPERATOR_EDEFAULT : newOperator;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    ActionlangPackage.UNARY_OP_EXPRESSION__OPERATOR,
                    oldOperator, operator));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ValuedExpression getOperand() {
        return operand;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetOperand(ValuedExpression newOperand,
            NotificationChain msgs) {
        ValuedExpression oldOperand = operand;
        operand = newOperand;
        if (eNotificationRequired()) {
            ENotificationImpl notification = new ENotificationImpl(this,
                    Notification.SET,
                    ActionlangPackage.UNARY_OP_EXPRESSION__OPERAND, oldOperand,
                    newOperand);
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
    public void setOperand(ValuedExpression newOperand) {
        assert (this != newOperand);
        if (newOperand != operand) {
            NotificationChain msgs = null;
            if (operand != null)
                msgs = ((InternalEObject) operand).eInverseRemove(this,
                        EOPPOSITE_FEATURE_BASE
                                - ActionlangPackage.UNARY_OP_EXPRESSION__OPERAND,
                        null, msgs);
            if (newOperand != null)
                msgs = ((InternalEObject) newOperand).eInverseAdd(this,
                        EOPPOSITE_FEATURE_BASE
                                - ActionlangPackage.UNARY_OP_EXPRESSION__OPERAND,
                        null, msgs);
            msgs = basicSetOperand(newOperand, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    ActionlangPackage.UNARY_OP_EXPRESSION__OPERAND, newOperand,
                    newOperand));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    private EList<UnaryOpPrototype> getPrototypesIn(BipPackage pack) {
        EList<UnaryOpPrototype> ret = new BasicEList<UnaryOpPrototype>();

        // compute types of parameters of the function call
        EList<Type> parametersTypes = new BasicEList<Type>();
        Type type = getOperand().getType();
        parametersTypes.add(type);

        // compute all prototypes matching function name and compatible parameters
        EList<UnaryOpPrototype> matching = pack
                .getUnaryOpPrototypes(getOperator(), parametersTypes);

        // keep only the maximal ones w.r.t. isRefiningParametersOf()
        for (UnaryOpPrototype prototype : matching) {
            boolean keepIt = true;

            for (UnaryOpPrototype testPrototype : matching) {
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
    private EList<UnaryOpPrototype> getPrototypesInAllUsedPackages(
            BipPackage pack) {
        Set<UnaryOpPrototype> ret = new HashSet<UnaryOpPrototype>();

        for (BipPackage usedPackage : pack.getUsed_packages()) {
            ret.addAll(getPrototypesIn(usedPackage));
            ret.addAll(getPrototypesInAllUsedPackages(usedPackage));
        }

        return new BasicEList<UnaryOpPrototype>(ret);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public EList<UnaryOpPrototype> getPrototypes() {
        Set<UnaryOpPrototype> ret = new HashSet<UnaryOpPrototype>();

        BipPackage currentPackage = getPackage();

        // look for prototypes in the current package
        ret.addAll(getPrototypesIn(currentPackage));

        if (ret.isEmpty()) {
            // look for prototypes in used packages
            ret.addAll(getPrototypesInAllUsedPackages(currentPackage));
        }

        return new BasicEList<UnaryOpPrototype>(ret);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public Type getType() {
        Type ret = null;

        EList<UnaryOpPrototype> prototypes = getPrototypes();

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

        EList<UnaryOpPrototype> prototypes = getPrototypes();

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

        EList<UnaryOpPrototype> prototypes = getPrototypes();

        if (prototypes.size() == 1) {
            for (PrototypeParameterDeclaration declaration : prototypes.get(0)
                    .getParameterDeclarations()) {
                if (!declaration.isConst()) {
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
        case ActionlangPackage.UNARY_OP_EXPRESSION__OPERAND:
            return basicSetOperand(null, msgs);
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
        case ActionlangPackage.UNARY_OP_EXPRESSION__OPERATOR:
            return getOperator();
        case ActionlangPackage.UNARY_OP_EXPRESSION__OPERAND:
            return getOperand();
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
        case ActionlangPackage.UNARY_OP_EXPRESSION__OPERATOR:
            setOperator((UnaryOperators) newValue);
            return;
        case ActionlangPackage.UNARY_OP_EXPRESSION__OPERAND:
            setOperand((ValuedExpression) newValue);
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
        case ActionlangPackage.UNARY_OP_EXPRESSION__OPERATOR:
            setOperator(OPERATOR_EDEFAULT);
            return;
        case ActionlangPackage.UNARY_OP_EXPRESSION__OPERAND:
            setOperand((ValuedExpression) null);
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
        case ActionlangPackage.UNARY_OP_EXPRESSION__OPERATOR:
            return operator != OPERATOR_EDEFAULT;
        case ActionlangPackage.UNARY_OP_EXPRESSION__OPERAND:
            return operand != null;
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
     * @generated NOT
     */
    public EList<DataDeclaration> getReadVariables() {
        return getOperand().getReadVariables();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public EList<DataDeclaration> getMayReadVariables() {
        return getOperand().getMayReadVariables();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public EList<DataDeclaration> getWriteVariables() {
        return getOperand().getWriteVariables();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public EList<DataDeclaration> getMayWriteVariables() {
        EList<UnaryOpPrototype> prototypes = getPrototypes();

        assert (prototypes.size() == 1);

        UnaryOpPrototype prototype = prototypes.get(0);

        assert (prototype.getParameterDeclarations().size() == 1);

        if (prototype.getParameterDeclarations().get(0).isConst()) {
            return getOperand().getMayReadVariables();
        } else {
            return getOperand().getMayWriteVariables();
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public EList<Expression> getMayReadUninitializedVariables(
            EList<DataDeclaration> uninitialized) {
        return getOperand().getMayReadUninitializedVariables(uninitialized);
    }

} //UnaryOpExpressionImpl
