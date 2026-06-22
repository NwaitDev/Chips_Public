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
import bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.Expression;
import bip2.ujf.verimag.bip.actionlang.FunctionCallExpression;
import bip2.ujf.verimag.bip.actionlang.UnaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.ValuedExpression;

import bip2.ujf.verimag.bip.packaging.FunctionCallPrototype;
import bip2.ujf.verimag.bip.packaging.PrototypeParameterDeclaration;
import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataType;
import bip2.ujf.verimag.bip.packaging.BipPackage;
import bip2.ujf.verimag.bip.types.Type;

import java.util.ArrayList;
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
 * An implementation of the model object '<em><b>Function Call Expression</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.impl.FunctionCallExpressionImpl#getParameters <em>Parameters</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.impl.FunctionCallExpressionImpl#getFunctionName <em>Function Name</em>}</li>
 * </ul>
 *
 * @generated
 */
public class FunctionCallExpressionImpl extends ValuedExpressionImpl
        implements FunctionCallExpression {
    /**
     * The cached value of the '{@link #getParameters() <em>Parameters</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getParameters()
     * @generated
     * @ordered
     */
    protected EList<ValuedExpression> parameters;

    /**
     * The default value of the '{@link #getFunctionName() <em>Function Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getFunctionName()
     * @generated
     * @ordered
     */
    protected static final String FUNCTION_NAME_EDEFAULT = null;

    /**
     * The cached value of the '{@link #getFunctionName() <em>Function Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getFunctionName()
     * @generated
     * @ordered
     */
    protected String functionName = FUNCTION_NAME_EDEFAULT;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected FunctionCallExpressionImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return ActionlangPackage.Literals.FUNCTION_CALL_EXPRESSION;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<ValuedExpression> getParameters() {
        if (parameters == null) {
            parameters = new EObjectContainmentEList<ValuedExpression>(
                    ValuedExpression.class, this,
                    ActionlangPackage.FUNCTION_CALL_EXPRESSION__PARAMETERS);
        }
        return parameters;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public String getFunctionName() {
        return functionName;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setFunctionName(String newFunctionName) {
        String oldFunctionName = functionName;
        functionName = newFunctionName;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    ActionlangPackage.FUNCTION_CALL_EXPRESSION__FUNCTION_NAME,
                    oldFunctionName, functionName));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    private EList<FunctionCallPrototype> getPrototypesIn(BipPackage pack) {
        EList<FunctionCallPrototype> ret = new BasicEList<FunctionCallPrototype>();

        // compute types of parameters of the function call
        EList<Type> parametersTypes = new BasicEList<Type>();

        for (ValuedExpression expression : getParameters()) {
            Type type = expression.getType();
            parametersTypes.add(type);
        }

        // compute all prototypes matching function name and compatible parameters
        EList<FunctionCallPrototype> matching = pack
                .getFunctionCallPrototypes(getFunctionName(), parametersTypes);

        // keep only the maximal ones w.r.t. isRefiningParametersOf()
        for (FunctionCallPrototype prototype : matching) {
            boolean keepIt = true;

            for (FunctionCallPrototype testPrototype : matching) {
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
    private EList<FunctionCallPrototype> getPrototypesInAllUsedPackages(
            BipPackage pack) {
        Set<FunctionCallPrototype> ret = new HashSet<FunctionCallPrototype>();

        for (BipPackage usedPackage : pack.getUsed_packages()) {
            ret.addAll(getPrototypesIn(usedPackage));
            ret.addAll(getPrototypesInAllUsedPackages(usedPackage));
        }

        return new BasicEList<FunctionCallPrototype>(ret);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public EList<FunctionCallPrototype> getPrototypes() {
        Set<FunctionCallPrototype> ret = new HashSet<FunctionCallPrototype>();

        BipPackage currentPackage = getPackage();

        // look for prototypes in the current package
        ret.addAll(getPrototypesIn(currentPackage));

        if (ret.isEmpty()) {
            // look for prototypes in used packages
            ret.addAll(getPrototypesInAllUsedPackages(currentPackage));
        }

        return new BasicEList<FunctionCallPrototype>(ret);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public Type getType() {
        Type ret = null;

        EList<FunctionCallPrototype> prototypes = getPrototypes();

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

        EList<FunctionCallPrototype> prototypes = getPrototypes();

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

        EList<FunctionCallPrototype> prototypes = getPrototypes();

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
        case ActionlangPackage.FUNCTION_CALL_EXPRESSION__PARAMETERS:
            return ((InternalEList<?>) getParameters()).basicRemove(otherEnd,
                    msgs);
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
        case ActionlangPackage.FUNCTION_CALL_EXPRESSION__PARAMETERS:
            return getParameters();
        case ActionlangPackage.FUNCTION_CALL_EXPRESSION__FUNCTION_NAME:
            return getFunctionName();
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
        case ActionlangPackage.FUNCTION_CALL_EXPRESSION__PARAMETERS:
            getParameters().clear();
            getParameters()
                    .addAll((Collection<? extends ValuedExpression>) newValue);
            return;
        case ActionlangPackage.FUNCTION_CALL_EXPRESSION__FUNCTION_NAME:
            setFunctionName((String) newValue);
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
        case ActionlangPackage.FUNCTION_CALL_EXPRESSION__PARAMETERS:
            getParameters().clear();
            return;
        case ActionlangPackage.FUNCTION_CALL_EXPRESSION__FUNCTION_NAME:
            setFunctionName(FUNCTION_NAME_EDEFAULT);
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
        case ActionlangPackage.FUNCTION_CALL_EXPRESSION__PARAMETERS:
            return parameters != null && !parameters.isEmpty();
        case ActionlangPackage.FUNCTION_CALL_EXPRESSION__FUNCTION_NAME:
            return FUNCTION_NAME_EDEFAULT == null ? functionName != null
                    : !FUNCTION_NAME_EDEFAULT.equals(functionName);
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
        result.append(" (functionName: ");
        result.append(functionName);
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

        for (ValuedExpression expr : getParameters()) {
            ret.addAll(expr.getReadVariables());
        }

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

        for (ValuedExpression expr : getParameters()) {
            ret.addAll(expr.getMayReadVariables());
        }

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

        for (ValuedExpression expr : getParameters()) {
            ret.addAll(expr.getWriteVariables());
        }

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
        EList<FunctionCallPrototype> prototypes = getPrototypes();

        assert (prototypes.size() == 1);

        FunctionCallPrototype prototype = prototypes.get(0);

        assert (getParameters().size() == prototype.getParameterDeclarations()
                .size());

        for (int i = 0; i < getParameters().size(); i++) {
            ValuedExpression expr = getParameters().get(i);
            PrototypeParameterDeclaration decl = prototype
                    .getParameterDeclarations().get(i);

            if (decl.isConst()) {
                ret.addAll(expr.getMayWriteVariables());
            } else {
                ret.addAll(expr.getMayReadVariables());
            }
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

        // variables initialized after the evaluation of all parameters
        EList<DataDeclaration> returnedInitializedVariables = new BasicEList<DataDeclaration>(
                uninitialized);

        for (ValuedExpression expr : getParameters()) {
            // /!\ no assumption is made on the execution order of parameters
            // => copy initialized variables
            EList<DataDeclaration> exprUninitializedVariables = new BasicEList<DataDeclaration>(
                    uninitialized);

            ret.addAll(expr.getMayReadUninitializedVariables(
                    exprUninitializedVariables));

            // update returned uninitialized variables
            returnedInitializedVariables.retainAll(exprUninitializedVariables);
        }

        // update returned uninitialized variables
        uninitialized.retainAll(returnedInitializedVariables);

        return ret;
    }

} //FunctionCallExpressionImpl
