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

package bip2.ujf.verimag.bip.actionlang.impl;

import java.util.List;

import bip2.ujf.verimag.bip.actionlang.ActionlangPackage;
import bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.AssignmentExpression;
import bip2.ujf.verimag.bip.actionlang.BinaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.Expression;
import bip2.ujf.verimag.bip.actionlang.FunctionCallExpression;
import bip2.ujf.verimag.bip.actionlang.IfThenElseExpression;
import bip2.ujf.verimag.bip.actionlang.UnaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.ValuedExpression;
import bip2.ujf.verimag.bip.types.Type;

import org.eclipse.emf.common.util.BasicEList;
import org.eclipse.emf.common.util.EList;
import bip2.ujf.verimag.bip.behavior.PetriNet;
import bip2.ujf.verimag.bip.behavior.Transition;
import bip2.ujf.verimag.bip.component.ComponentDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionAction;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionDefinition;

import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataFactory;
import bip2.ujf.verimag.bip.data.DataType;
import bip2.ujf.verimag.bip.invariant.Invariant;
import bip2.ujf.verimag.bip.packaging.BinaryOpPrototype;
import bip2.ujf.verimag.bip.packaging.BipPackage;
import bip2.ujf.verimag.bip.packaging.ConstDataDeclaration;
import bip2.ujf.verimag.bip.packaging.FunctionCallPrototype;
import bip2.ujf.verimag.bip.packaging.Prototype;
import bip2.ujf.verimag.bip.packaging.UnaryOpPrototype;
import bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration;
import bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EStructuralFeature;

import ujf.verimag.bip.metamodel.AnnotatedEObject;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Valued Expression</b></em>'.
 * <!-- end-user-doc -->
 *
 * @generated
 */
public abstract class ValuedExpressionImpl extends AnnotatedEObjectImpl
        implements ValuedExpression {
    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected ValuedExpressionImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return ActionlangPackage.Literals.VALUED_EXPRESSION;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public Type getType() {
        assert (false);
        return null;
    }

    /**
     * .
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public BipPackage getPackage() {
        return getPackage(this);
    }

    /**
     * .
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    private BipPackage getPackage(EObject object) {
        EObject container = object;

        while (container.eContainer() != null) {
            container = container.eContainer();
        }

        assert (container != null);

        if (container instanceof BipPackage) {
            return (BipPackage) container;
        } else if (container instanceof ComponentDeclaration) {
            ComponentDeclaration mainDeclaration = (ComponentDeclaration) container;

            return getPackage(mainDeclaration.getType());
        }

        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public Type getExpectedType() {
        Type ret = null;

        EObject container = this.eContainer();

        if (container != null) {
            if (container instanceof Transition) {
                Transition transition = (Transition) container;

                if (this == transition.getGuard()) {
                    ret = getPackage().getBoolDataType();
                } else if (!transition.getActions().contains(this)) {
                    assert false;
                }
            } else if (container instanceof Invariant) {
                Invariant invariant = (Invariant) container;

                if (this == invariant.getGuard()) {
                    ret = getPackage().getBoolDataType();
                } else {
                    assert (false);
                }
            } else if (container instanceof ConnectorInteractionAction) {
                ConnectorInteractionAction interaction = (ConnectorInteractionAction) container;

                if (this == interaction.getGuard()) {
                    ret = getPackage().getBoolDataType();
                } else if (!interaction.getDown().contains(this)
                        && !interaction.getUp().contains(this)) {
                    assert (false);
                }
            } else if (container instanceof AtomPriorityDeclaration) {
                AtomPriorityDeclaration priority = (AtomPriorityDeclaration) container;

                if (this == priority.getGuard()) {
                    ret = getPackage().getBoolDataType();
                } else
                    assert false;
            } else if (container instanceof CompoundPriorityDeclaration) {
                CompoundPriorityDeclaration priority = (CompoundPriorityDeclaration) container;

                if (this == priority.getGuard()) {
                    ret = getPackage().getBoolDataType();
                } else
                    assert false;

            } else if (container instanceof UnaryOpExpression) {
                UnaryOpExpression unaryExpr = (UnaryOpExpression) container;

                List<UnaryOpPrototype> prototypes = unaryExpr.getPrototypes();

                if (prototypes.size() == 1) {
                    Prototype prototype = prototypes.get(0);
                    assert (prototype.getParameterDeclarations().size() == 1);

                    if (this == unaryExpr.getOperand()) {
                        ret = prototype.getParameterDeclarations().get(0)
                                .getType();
                    } else
                        assert (false);
                }
            } else if (container instanceof BinaryOpExpression) {
                BinaryOpExpression binaryExpr = (BinaryOpExpression) container;

                List<BinaryOpPrototype> prototypes = binaryExpr.getPrototypes();

                if (prototypes.size() == 1) {
                    Prototype prototype = prototypes.get(0);
                    assert (prototype.getParameterDeclarations().size() == 2);

                    if (this == binaryExpr.getLeft()) {
                        ret = prototype.getParameterDeclarations().get(0)
                                .getType();
                    } else if (this == binaryExpr.getRight()) {
                        ret = prototype.getParameterDeclarations().get(1)
                                .getType();
                    } else
                        assert (false);
                }
            } else if (container instanceof FunctionCallExpression) {
                FunctionCallExpression functionCall = (FunctionCallExpression) container;

                List<FunctionCallPrototype> prototypes = functionCall
                        .getPrototypes();

                if (prototypes.size() == 1) {
                    Prototype prototype = prototypes.get(0);
                    assert (functionCall.getParameters().size() == prototype
                            .getParameterDeclarations().size());

                    for (int i = 0; i < functionCall.getParameters()
                            .size(); i++) {
                        if (this == functionCall.getParameters().get(i)) {
                            ret = prototype.getParameterDeclarations().get(i)
                                    .getType();
                            break;
                        } else if (i == functionCall.getParameters().size()
                                - 1) {
                            assert (false);
                        }
                    }
                }
            } else if (container instanceof DataDeclaration) {
                DataDeclaration dataDeclaration = (DataDeclaration) container;
                ret = dataDeclaration.getDataType();
            } else if (container instanceof AssignmentExpression) {
                AssignmentExpression assignment = (AssignmentExpression) container;

                if (this == assignment.getLhs()
                        || this == assignment.getRhs()) {
                    ret = assignment.getLhs().getType();
                } else
                    assert (false);
            } else if (container instanceof IfThenElseExpression) {
                IfThenElseExpression ifThenElse = (IfThenElseExpression) container;

                if (this == ifThenElse.getCondition()) {
                    ret = getPackage().getBoolDataType();
                } else if (!ifThenElse.getThen().contains(this)
                        && !ifThenElse.getElse().contains(this)) {
                    assert (false);
                }
            } else if (container instanceof ComponentDeclaration) {
                ComponentDeclaration declaration = (ComponentDeclaration) container;

                for (int i = 0; i < declaration.getParameters().size(); i++) {
                    if (this == declaration.getParameters().get(i)) {
                        if (i < declaration.getType()
                                .getDataParameterDeclarations().size()) {
                            ret = declaration.getType()
                                    .getDataParameterDeclarations().get(i)
                                    .getDataType();
                        }

                        break;
                    } else if (i == declaration.getParameters().size() - 1) {
                        assert (false);
                    }
                }
            } else if (container instanceof PetriNet) {
                PetriNet pn = (PetriNet) container;

                if (!pn.getInitialActions().contains(this))
                    assert (false);
            } else {
                System.out.println(container);
                assert (false);
            }
        }
        return ret;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean isConst() {
        assert (false);
        return false;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean expectedIsConst() {
        // /!\ Only calls to operators and function may modify
        // variables which are passed as reference
        // in all other cases variables are passed by value
        boolean ret = true;

        EObject container = this.eContainer();

        if (container != null) {
            if (container instanceof UnaryOpExpression) {
                UnaryOpExpression unaryExpr = (UnaryOpExpression) container;

                List<UnaryOpPrototype> prototypes = unaryExpr.getPrototypes();

                if (prototypes.size() == 1) {
                    Prototype prototype = prototypes.get(0);
                    assert (prototype.getParameterDeclarations().size() == 1);

                    if (this == unaryExpr.getOperand()) {
                        ret = prototype.getParameterDeclarations().get(0)
                                .isConst();
                    } else
                        assert (false);
                }
            } else if (container instanceof BinaryOpExpression) {
                BinaryOpExpression binaryExpr = (BinaryOpExpression) container;

                List<BinaryOpPrototype> prototypes = binaryExpr.getPrototypes();

                if (prototypes.size() == 1) {
                    Prototype prototype = prototypes.get(0);
                    assert (prototype.getParameterDeclarations().size() == 2);

                    if (this == binaryExpr.getLeft()) {
                        ret = prototype.getParameterDeclarations().get(0)
                                .isConst();
                    } else if (this == binaryExpr.getRight()) {
                        ret = prototype.getParameterDeclarations().get(1)
                                .isConst();
                    } else
                        assert (false);
                }
            } else if (container instanceof FunctionCallExpression) {
                FunctionCallExpression functionCall = (FunctionCallExpression) container;

                List<FunctionCallPrototype> prototypes = functionCall
                        .getPrototypes();

                if (prototypes.size() == 1) {
                    Prototype prototype = prototypes.get(0);
                    assert (functionCall.getParameters().size() == prototype
                            .getParameterDeclarations().size());

                    for (int i = 0; i < functionCall.getParameters()
                            .size(); i++) {
                        if (this == functionCall.getParameters().get(i)) {
                            ret = prototype.getParameterDeclarations().get(i)
                                    .isConst();
                            break;
                        } else if (i == functionCall.getParameters().size()
                                - 1) {
                            assert (false);
                        }
                    }
                }
            }
        }
        return ret;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean isInConstantContext() {
        return isInConstantContext(this);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    private boolean isInConstantContext(EObject object) {
        boolean ret = false;

        EObject container = object.eContainer();

        if (container != null) {
            if (container instanceof IfThenElseExpression) {
                IfThenElseExpression expression = (IfThenElseExpression) container;

                if (object == expression.getCondition()) {
                    ret = true;
                }
            } else if (container instanceof Transition) {
                Transition transition = (Transition) container;

                if (object == transition.getGuard()) {
                    ret = true;
                }
            } else if (container instanceof ConnectorInteractionAction) {
                ConnectorInteractionAction interaction = (ConnectorInteractionAction) container;

                if (object == interaction.getGuard()) {
                    ret = true;
                }
            } else if (container instanceof AtomPriorityDeclaration) {
                AtomPriorityDeclaration priority = (AtomPriorityDeclaration) container;

                if (object == priority.getGuard()) {
                    ret = true;
                }
            } else if (container instanceof CompoundPriorityDeclaration) {
                CompoundPriorityDeclaration priority = (CompoundPriorityDeclaration) container;

                if (object == priority.getGuard()) {
                    ret = true;
                }
            }

            if (!ret) {
                ret = isInConstantContext(container);
            }
        }

        return ret;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean hasSideEffect() {
        return false;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public EList<DataDeclaration> getReadVariables() {
        assert (false);

        return new BasicEList<DataDeclaration>();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public EList<DataDeclaration> getMayReadVariables() {
        assert (false);

        return new BasicEList<DataDeclaration>();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public EList<DataDeclaration> getWriteVariables() {
        assert (false);

        return new BasicEList<DataDeclaration>();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public EList<DataDeclaration> getMayWriteVariables() {
        assert (false);

        return new BasicEList<DataDeclaration>();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public EList<Expression> getMayReadUninitializedVariables(
            EList<DataDeclaration> uninitialized) {
        assert (false);

        return new BasicEList<Expression>();
    }

} //ValuedExpressionImpl
