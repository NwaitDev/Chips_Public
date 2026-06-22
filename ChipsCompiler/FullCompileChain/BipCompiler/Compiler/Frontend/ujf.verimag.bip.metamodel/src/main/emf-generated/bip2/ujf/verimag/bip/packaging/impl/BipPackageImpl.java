/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
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

import bip2.ujf.verimag.bip.actionlang.BinaryOperators;
import bip2.ujf.verimag.bip.actionlang.UnaryOperators;
import bip2.ujf.verimag.bip.annotation.impl.AnnotatedElementImpl;
import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataFactory;
import bip2.ujf.verimag.bip.data.DataType;
import bip2.ujf.verimag.bip.packaging.BinaryOpPrototype;
import bip2.ujf.verimag.bip.packaging.BipPackage;
import bip2.ujf.verimag.bip.packaging.ConstDataDeclaration;
import bip2.ujf.verimag.bip.packaging.FunctionCallPrototype;
import bip2.ujf.verimag.bip.packaging.PackagingFactory;
import bip2.ujf.verimag.bip.packaging.PackagingPackage;
import bip2.ujf.verimag.bip.packaging.PrototypeParameterDeclaration;

import bip2.ujf.verimag.bip.packaging.Prototype;
import bip2.ujf.verimag.bip.packaging.UnaryOpPrototype;
import bip2.ujf.verimag.bip.types.AtomType;
import bip2.ujf.verimag.bip.types.CompoundType;
import bip2.ujf.verimag.bip.types.ConnectorType;
import bip2.ujf.verimag.bip.types.PortType;

import bip2.ujf.verimag.bip.types.Type;
import java.util.Collection;
import java.util.List;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.BasicEList;
import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import org.eclipse.emf.ecore.impl.EObjectImpl;

import org.eclipse.emf.ecore.util.EDataTypeUniqueEList;
import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.EObjectResolvingEList;
import org.eclipse.emf.ecore.util.InternalEList;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Bip Package</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.impl.BipPackageImpl#getName <em>Name</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.impl.BipPackageImpl#getAtomTypes <em>Atom Types</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.impl.BipPackageImpl#getCompoundTypes <em>Compound Types</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.impl.BipPackageImpl#getConnectorTypes <em>Connector Types</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.impl.BipPackageImpl#getPortTypes <em>Port Types</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.impl.BipPackageImpl#getDataTypes <em>Data Types</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.impl.BipPackageImpl#getUsed_packages <em>Used packages</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.impl.BipPackageImpl#getConstData <em>Const Data</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.impl.BipPackageImpl#getPrototypes <em>Prototypes</em>}</li>
 * </ul>
 *
 * @generated
 */
public class BipPackageImpl extends AnnotatedElementImpl implements BipPackage {

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
     * The cached value of the '{@link #getAtomTypes() <em>Atom Types</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getAtomTypes()
     * @generated
     * @ordered
     */
    protected EList<AtomType> atomTypes;
    /**
     * The cached value of the '{@link #getCompoundTypes() <em>Compound Types</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getCompoundTypes()
     * @generated
     * @ordered
     */
    protected EList<CompoundType> compoundTypes;
    /**
     * The cached value of the '{@link #getConnectorTypes() <em>Connector Types</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getConnectorTypes()
     * @generated
     * @ordered
     */
    protected EList<ConnectorType> connectorTypes;
    /**
     * The cached value of the '{@link #getPortTypes() <em>Port Types</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPortTypes()
     * @generated
     * @ordered
     */
    protected EList<PortType> portTypes;
    /**
     * The cached value of the '{@link #getDataTypes() <em>Data Types</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getDataTypes()
     * @generated
     * @ordered
     */
    protected EList<DataType> dataTypes;
    /**
     * The cached value of the '{@link #getUsed_packages() <em>Used packages</em>}' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getUsed_packages()
     * @generated
     * @ordered
     */
    protected EList<BipPackage> used_packages;

    /**
     * The cached value of the '{@link #getConstData() <em>Const Data</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getConstData()
     * @generated
     * @ordered
     */
    protected EList<ConstDataDeclaration> constData;

    /**
     * The cached value of the '{@link #getPrototypes() <em>Prototypes</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPrototypes()
     * @generated
     * @ordered
     */
    protected EList<Prototype> prototypes;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    protected BipPackageImpl() {
        super();

        // set native data types
        boolDataType.setName("bool");
        boolDataType.setNative(true);
        getDataTypes().add(boolDataType);

        intDataType.setName("int");
        intDataType.setNative(true);
        getDataTypes().add(intDataType);

        floatDataType.setName("float");
        floatDataType.setNative(true);
        getDataTypes().add(floatDataType);

        stringDataType.setName("string");
        stringDataType.setNative(true);
        getDataTypes().add(stringDataType);

        // set sub-typing of native data types
        floatDataType.getCastableTypes().add(intDataType);

        // set native comparison prototypes
        for (BinaryOperators op : comparison_operators) {
            addNativeBinaryPrototype(op, getIntDataType(), getIntDataType(),
                    getBoolDataType());
            addNativeBinaryPrototype(op, getFloatDataType(), getIntDataType(),
                    getBoolDataType());
            addNativeBinaryPrototype(op, getIntDataType(), getFloatDataType(),
                    getBoolDataType());
            addNativeBinaryPrototype(op, getFloatDataType(), getFloatDataType(),
                    getBoolDataType());
            addNativeBinaryPrototype(op, getBoolDataType(), getBoolDataType(),
                    getBoolDataType());
            addNativeBinaryPrototype(op, getStringDataType(),
                    getStringDataType(), getBoolDataType());
        }

        // set native arithmetic binary prototypes        
        for (BinaryOperators op : arithmetic_binary_operators) {
            addNativeBinaryPrototype(op, getIntDataType(), getIntDataType(),
                    getIntDataType());
            addNativeBinaryPrototype(op, getFloatDataType(), getIntDataType(),
                    getFloatDataType());
            addNativeBinaryPrototype(op, getIntDataType(), getFloatDataType(),
                    getFloatDataType());
            addNativeBinaryPrototype(op, getFloatDataType(), getFloatDataType(),
                    getFloatDataType());
        }

        // set native arithmetic unary prototypes
        for (UnaryOperators op : arithmetic_unary_operators) {
            addNativeUnaryPrototype(op, getIntDataType(), getIntDataType());
            addNativeUnaryPrototype(op, getFloatDataType(), getFloatDataType());
        }

        // set native bitwise binary prototypes
        for (BinaryOperators op : bwise_binary_operators) {
            addNativeBinaryPrototype(op, getIntDataType(), getIntDataType(),
                    getIntDataType());
        }

        // set native bitwise unary prototypes
        for (UnaryOperators op : bwise_unary_operators) {
            addNativeUnaryPrototype(op, getIntDataType(), getIntDataType());
        }

        // set native logical binary prototypes
        for (BinaryOperators op : logical_binary_operators) {
            addNativeBinaryPrototype(op, getBoolDataType(), getBoolDataType(),
                    getBoolDataType());
        }

        // set native logical unary prototypes
        for (UnaryOperators op : logical_unary_operators) {
            addNativeUnaryPrototype(op, getBoolDataType(), getBoolDataType());
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    protected final DataType boolDataType = DataFactory.eINSTANCE
            .createDataType();

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    protected final DataType intDataType = DataFactory.eINSTANCE
            .createDataType();

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    protected final DataType floatDataType = DataFactory.eINSTANCE
            .createDataType();

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    protected final DataType stringDataType = DataFactory.eINSTANCE
            .createDataType();

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    protected static final BinaryOperators[] comparison_operators = {
            BinaryOperators.EQUAL, BinaryOperators.NOT_EQUAL,
            BinaryOperators.GREATER_THAN, BinaryOperators.GREATER_THAN_OR_EQUAL,
            BinaryOperators.LESS_THAN, BinaryOperators.LESS_THAN_OR_EQUAL };

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    protected static final BinaryOperators[] arithmetic_binary_operators = {
            BinaryOperators.ADDITION, BinaryOperators.SUBTRACTION,
            BinaryOperators.MULTIPLICATION, BinaryOperators.DIVISION,
            BinaryOperators.MODULO };

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    protected static final UnaryOperators[] arithmetic_unary_operators = {
            UnaryOperators.PLUS, UnaryOperators.MINUS };

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    private static final BinaryOperators[] bwise_binary_operators = {
            BinaryOperators.BWISE_AND, BinaryOperators.BWISE_XOR,
            BinaryOperators.BWISE_OR };

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    protected static final UnaryOperators[] bwise_unary_operators = {
            UnaryOperators.BWISE_NOT };

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    protected static final BinaryOperators[] logical_binary_operators = {
            BinaryOperators.LOGICAL_OR, BinaryOperators.LOGICAL_AND };

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    protected static final UnaryOperators[] logical_unary_operators = {
            UnaryOperators.LOGICAL_NOT };

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    protected void addNativeUnaryPrototype(UnaryOperators op, Type operandType,
            Type retType) {
        UnaryOpPrototype proto = PackagingFactory.eINSTANCE
                .createUnaryOpPrototype();

        proto.setOperator(op);
        proto.setNative(true);

        PrototypeParameterDeclaration operand = PackagingFactory.eINSTANCE
                .createPrototypeParameterDeclaration();
        operand.setName("");
        operand.setType(operandType);
        operand.setConst(true);
        proto.getParameterDeclarations().add(operand);

        proto.setReturnType(retType);

        getPrototypes().add(proto);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    private void addNativeBinaryPrototype(BinaryOperators op, Type leftType,
            Type rightType, Type retType) {
        BinaryOpPrototype proto = PackagingFactory.eINSTANCE
                .createBinaryOpPrototype();

        proto.setOperator(op);
        proto.setNative(true);

        PrototypeParameterDeclaration leftParam = PackagingFactory.eINSTANCE
                .createPrototypeParameterDeclaration();
        PrototypeParameterDeclaration rightParam = PackagingFactory.eINSTANCE
                .createPrototypeParameterDeclaration();

        leftParam.setName("");
        leftParam.setType(rightType);
        leftParam.setConst(true);
        proto.getParameterDeclarations().add(rightParam);

        rightParam.setName("");
        rightParam.setType(leftType);
        rightParam.setConst(true);
        proto.getParameterDeclarations().add(leftParam);

        proto.setReturnType(retType);

        getPrototypes().add(proto);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return PackagingPackage.Literals.BIP_PACKAGE;
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
                    PackagingPackage.BIP_PACKAGE__NAME, oldName, name));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<BipPackage> getUsed_packages() {
        if (used_packages == null) {
            used_packages = new EObjectResolvingEList<BipPackage>(
                    BipPackage.class, this,
                    PackagingPackage.BIP_PACKAGE__USED_PACKAGES);
        }
        return used_packages;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<ConstDataDeclaration> getConstData() {
        if (constData == null) {
            constData = new EObjectContainmentEList<ConstDataDeclaration>(
                    ConstDataDeclaration.class, this,
                    PackagingPackage.BIP_PACKAGE__CONST_DATA);
        }
        return constData;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<Prototype> getPrototypes() {
        if (prototypes == null) {
            prototypes = new EObjectContainmentEList<Prototype>(Prototype.class,
                    this, PackagingPackage.BIP_PACKAGE__PROTOTYPES);
        }
        return prototypes;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<AtomType> getAtomTypes() {
        if (atomTypes == null) {
            atomTypes = new EObjectContainmentEList<AtomType>(AtomType.class,
                    this, PackagingPackage.BIP_PACKAGE__ATOM_TYPES);
        }
        return atomTypes;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<CompoundType> getCompoundTypes() {
        if (compoundTypes == null) {
            compoundTypes = new EObjectContainmentEList<CompoundType>(
                    CompoundType.class, this,
                    PackagingPackage.BIP_PACKAGE__COMPOUND_TYPES);
        }
        return compoundTypes;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<ConnectorType> getConnectorTypes() {
        if (connectorTypes == null) {
            connectorTypes = new EObjectContainmentEList<ConnectorType>(
                    ConnectorType.class, this,
                    PackagingPackage.BIP_PACKAGE__CONNECTOR_TYPES);
        }
        return connectorTypes;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<PortType> getPortTypes() {
        if (portTypes == null) {
            portTypes = new EObjectContainmentEList<PortType>(PortType.class,
                    this, PackagingPackage.BIP_PACKAGE__PORT_TYPES);
        }
        return portTypes;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<DataType> getDataTypes() {
        if (dataTypes == null) {
            dataTypes = new EObjectContainmentEList<DataType>(DataType.class,
                    this, PackagingPackage.BIP_PACKAGE__DATA_TYPES);
        }
        return dataTypes;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public AtomType getAtomType(String name) {
        for (AtomType at : getAtomTypes()) {
            if (at.getName().equals(name)) {
                return at;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public CompoundType getCompoundType(String name) {
        for (CompoundType ct : getCompoundTypes()) {
            if (ct.getName().equals(name)) {
                return ct;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public ConnectorType getConnectorType(String name) {
        for (ConnectorType ct : getConnectorTypes()) {
            if (ct.getName().equals(name)) {
                return ct;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public PortType getPortType(String name) {
        for (PortType pt : getPortTypes()) {
            if (pt.getName().equals(name)) {
                return pt;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public DataType getDataType(String name) {
        for (DataType dt : getDataTypes()) {
            if (dt.getName().equals(name)) {
                return dt;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public ConstDataDeclaration getConstDataDeclaration(String name) {
        for (ConstDataDeclaration cdd : getConstData()) {
            if (cdd.getName().equals(name))
                return cdd;
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    private boolean isKindOf(EList<Type> types1,
            EList<PrototypeParameterDeclaration> types2) {
        boolean ret = false;

        if (types1.size() == types2.size()) {
            ret = true;

            for (int i = 0; i < types1.size(); i++) {
                Type dt1 = types1.get(i);
                Type dt2 = types2.get(i).getType();

                if (dt1 != null) {
                    if (!dt1.isKindOf(dt2)) {
                        ret = false;
                        break;
                    }
                } else {
                    ret = false;
                    break;
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
    public EList<FunctionCallPrototype> getFunctionCallPrototypes(
            String functionName) {
        EList<FunctionCallPrototype> ret = new BasicEList<FunctionCallPrototype>();

        for (Prototype prototype : getPrototypes()) {
            if (prototype instanceof FunctionCallPrototype) {
                FunctionCallPrototype functionCallPrototype = (FunctionCallPrototype) prototype;

                if (functionName.equals(functionCallPrototype.getFunctionName())
                        || functionName.equals(getName() + "."
                                + functionCallPrototype.getFunctionName())) {
                    ret.add(functionCallPrototype);
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
    public EList<FunctionCallPrototype> getFunctionCallPrototypes(
            String functionName, EList<Type> parametersTypes) {
        EList<FunctionCallPrototype> ret = new BasicEList<FunctionCallPrototype>();

        for (FunctionCallPrototype prototype : getFunctionCallPrototypes(
                functionName)) {
            if (isKindOf(parametersTypes,
                    prototype.getParameterDeclarations())) {
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
    public EList<BinaryOpPrototype> getBinaryOpPrototypes(
            BinaryOperators operator) {
        EList<BinaryOpPrototype> ret = new BasicEList<BinaryOpPrototype>();

        for (Prototype prototype : getPrototypes()) {
            if (prototype instanceof BinaryOpPrototype) {
                BinaryOpPrototype binaryOpPrototype = (BinaryOpPrototype) prototype;

                if (operator == binaryOpPrototype.getOperator()) {
                    ret.add(binaryOpPrototype);
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
    public EList<BinaryOpPrototype> getBinaryOpPrototypes(
            BinaryOperators operator, EList<Type> parametersTypes) {
        EList<BinaryOpPrototype> ret = new BasicEList<BinaryOpPrototype>();

        for (BinaryOpPrototype prototype : getBinaryOpPrototypes(operator)) {
            if (isKindOf(parametersTypes,
                    prototype.getParameterDeclarations())) {
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
    public EList<UnaryOpPrototype> getUnaryOpPrototypes(
            UnaryOperators operator) {
        EList<UnaryOpPrototype> ret = new BasicEList<UnaryOpPrototype>();

        for (Prototype prototype : getPrototypes()) {
            if (prototype instanceof UnaryOpPrototype) {
                UnaryOpPrototype unaryOpPrototype = (UnaryOpPrototype) prototype;

                if (operator == unaryOpPrototype.getOperator()) {
                    ret.add(unaryOpPrototype);
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
    public EList<UnaryOpPrototype> getUnaryOpPrototypes(UnaryOperators operator,
            EList<Type> parametersTypes) {
        EList<UnaryOpPrototype> ret = new BasicEList<UnaryOpPrototype>();

        for (UnaryOpPrototype prototype : getUnaryOpPrototypes(operator)) {
            if (isKindOf(parametersTypes,
                    prototype.getParameterDeclarations())) {
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
    public DataType getBoolDataType() {
        return boolDataType;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public DataType getIntDataType() {
        return intDataType;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public DataType getFloatDataType() {
        return floatDataType;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public DataType getStringDataType() {
        return stringDataType;
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
        case PackagingPackage.BIP_PACKAGE__ATOM_TYPES:
            return ((InternalEList<?>) getAtomTypes()).basicRemove(otherEnd,
                    msgs);
        case PackagingPackage.BIP_PACKAGE__COMPOUND_TYPES:
            return ((InternalEList<?>) getCompoundTypes()).basicRemove(otherEnd,
                    msgs);
        case PackagingPackage.BIP_PACKAGE__CONNECTOR_TYPES:
            return ((InternalEList<?>) getConnectorTypes())
                    .basicRemove(otherEnd, msgs);
        case PackagingPackage.BIP_PACKAGE__PORT_TYPES:
            return ((InternalEList<?>) getPortTypes()).basicRemove(otherEnd,
                    msgs);
        case PackagingPackage.BIP_PACKAGE__DATA_TYPES:
            return ((InternalEList<?>) getDataTypes()).basicRemove(otherEnd,
                    msgs);
        case PackagingPackage.BIP_PACKAGE__CONST_DATA:
            return ((InternalEList<?>) getConstData()).basicRemove(otherEnd,
                    msgs);
        case PackagingPackage.BIP_PACKAGE__PROTOTYPES:
            return ((InternalEList<?>) getPrototypes()).basicRemove(otherEnd,
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
        case PackagingPackage.BIP_PACKAGE__NAME:
            return getName();
        case PackagingPackage.BIP_PACKAGE__ATOM_TYPES:
            return getAtomTypes();
        case PackagingPackage.BIP_PACKAGE__COMPOUND_TYPES:
            return getCompoundTypes();
        case PackagingPackage.BIP_PACKAGE__CONNECTOR_TYPES:
            return getConnectorTypes();
        case PackagingPackage.BIP_PACKAGE__PORT_TYPES:
            return getPortTypes();
        case PackagingPackage.BIP_PACKAGE__DATA_TYPES:
            return getDataTypes();
        case PackagingPackage.BIP_PACKAGE__USED_PACKAGES:
            return getUsed_packages();
        case PackagingPackage.BIP_PACKAGE__CONST_DATA:
            return getConstData();
        case PackagingPackage.BIP_PACKAGE__PROTOTYPES:
            return getPrototypes();
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
        case PackagingPackage.BIP_PACKAGE__NAME:
            setName((String) newValue);
            return;
        case PackagingPackage.BIP_PACKAGE__ATOM_TYPES:
            getAtomTypes().clear();
            getAtomTypes().addAll((Collection<? extends AtomType>) newValue);
            return;
        case PackagingPackage.BIP_PACKAGE__COMPOUND_TYPES:
            getCompoundTypes().clear();
            getCompoundTypes()
                    .addAll((Collection<? extends CompoundType>) newValue);
            return;
        case PackagingPackage.BIP_PACKAGE__CONNECTOR_TYPES:
            getConnectorTypes().clear();
            getConnectorTypes()
                    .addAll((Collection<? extends ConnectorType>) newValue);
            return;
        case PackagingPackage.BIP_PACKAGE__PORT_TYPES:
            getPortTypes().clear();
            getPortTypes().addAll((Collection<? extends PortType>) newValue);
            return;
        case PackagingPackage.BIP_PACKAGE__DATA_TYPES:
            getDataTypes().clear();
            getDataTypes().addAll((Collection<? extends DataType>) newValue);
            return;
        case PackagingPackage.BIP_PACKAGE__USED_PACKAGES:
            getUsed_packages().clear();
            getUsed_packages()
                    .addAll((Collection<? extends BipPackage>) newValue);
            return;
        case PackagingPackage.BIP_PACKAGE__CONST_DATA:
            getConstData().clear();
            getConstData().addAll(
                    (Collection<? extends ConstDataDeclaration>) newValue);
            return;
        case PackagingPackage.BIP_PACKAGE__PROTOTYPES:
            getPrototypes().clear();
            getPrototypes().addAll((Collection<? extends Prototype>) newValue);
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
        case PackagingPackage.BIP_PACKAGE__NAME:
            setName(NAME_EDEFAULT);
            return;
        case PackagingPackage.BIP_PACKAGE__ATOM_TYPES:
            getAtomTypes().clear();
            return;
        case PackagingPackage.BIP_PACKAGE__COMPOUND_TYPES:
            getCompoundTypes().clear();
            return;
        case PackagingPackage.BIP_PACKAGE__CONNECTOR_TYPES:
            getConnectorTypes().clear();
            return;
        case PackagingPackage.BIP_PACKAGE__PORT_TYPES:
            getPortTypes().clear();
            return;
        case PackagingPackage.BIP_PACKAGE__DATA_TYPES:
            getDataTypes().clear();
            return;
        case PackagingPackage.BIP_PACKAGE__USED_PACKAGES:
            getUsed_packages().clear();
            return;
        case PackagingPackage.BIP_PACKAGE__CONST_DATA:
            getConstData().clear();
            return;
        case PackagingPackage.BIP_PACKAGE__PROTOTYPES:
            getPrototypes().clear();
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
        case PackagingPackage.BIP_PACKAGE__NAME:
            return NAME_EDEFAULT == null ? name != null
                    : !NAME_EDEFAULT.equals(name);
        case PackagingPackage.BIP_PACKAGE__ATOM_TYPES:
            return atomTypes != null && !atomTypes.isEmpty();
        case PackagingPackage.BIP_PACKAGE__COMPOUND_TYPES:
            return compoundTypes != null && !compoundTypes.isEmpty();
        case PackagingPackage.BIP_PACKAGE__CONNECTOR_TYPES:
            return connectorTypes != null && !connectorTypes.isEmpty();
        case PackagingPackage.BIP_PACKAGE__PORT_TYPES:
            return portTypes != null && !portTypes.isEmpty();
        case PackagingPackage.BIP_PACKAGE__DATA_TYPES:
            return dataTypes != null && !dataTypes.isEmpty();
        case PackagingPackage.BIP_PACKAGE__USED_PACKAGES:
            return used_packages != null && !used_packages.isEmpty();
        case PackagingPackage.BIP_PACKAGE__CONST_DATA:
            return constData != null && !constData.isEmpty();
        case PackagingPackage.BIP_PACKAGE__PROTOTYPES:
            return prototypes != null && !prototypes.isEmpty();
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
        result.append(')');
        return result.toString();
    }

} //BipPackageImpl
