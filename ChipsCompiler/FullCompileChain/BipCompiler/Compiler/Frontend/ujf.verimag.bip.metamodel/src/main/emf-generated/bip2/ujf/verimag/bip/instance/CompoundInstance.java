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

package bip2.ujf.verimag.bip.instance;

import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Compound Instance</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.instance.CompoundInstance#getSubPriorities <em>Sub Priorities</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.CompoundInstance#getSubConnectorInstances <em>Sub Connector Instances</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.CompoundInstance#getSubAtomInstances <em>Sub Atom Instances</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.CompoundInstance#getSubCompoundInstances <em>Sub Compound Instances</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.CompoundInstance#getSubDataInstances <em>Sub Data Instances</em>}</li>
 * </ul>
 *
 * @see bip2.ujf.verimag.bip.instance.InstancePackage#getCompoundInstance()
 * @model
 * @generated
 */
public interface CompoundInstance extends ComponentInstance {
    /**
     * Returns the value of the '<em><b>Sub Priorities</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.instance.CompoundPriorityInstance}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Sub Priorities</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Sub Priorities</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.instance.InstancePackage#getCompoundInstance_SubPriorities()
     * @model containment="true"
     * @generated
     */
    EList<CompoundPriorityInstance> getSubPriorities();

    /**
     * Returns the value of the '<em><b>Sub Connector Instances</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.instance.ConnectorInstance}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Sub Connector Instances</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Sub Connector Instances</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.instance.InstancePackage#getCompoundInstance_SubConnectorInstances()
     * @model containment="true"
     * @generated
     */
    EList<ConnectorInstance> getSubConnectorInstances();

    /**
     * Returns the value of the '<em><b>Sub Atom Instances</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.instance.AtomInstance}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Sub Atom Instances</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Sub Atom Instances</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.instance.InstancePackage#getCompoundInstance_SubAtomInstances()
     * @model containment="true"
     * @generated
     */
    EList<AtomInstance> getSubAtomInstances();

    /**
     * Returns the value of the '<em><b>Sub Compound Instances</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.instance.CompoundInstance}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Sub Compound Instances</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Sub Compound Instances</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.instance.InstancePackage#getCompoundInstance_SubCompoundInstances()
     * @model containment="true"
     * @generated
     */
    EList<CompoundInstance> getSubCompoundInstances();

    /**
     * Returns the value of the '<em><b>Sub Data Instances</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.instance.DataInstance}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Sub Data Instances</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Sub Data Instances</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.instance.InstancePackage#getCompoundInstance_SubDataInstances()
     * @model containment="true"
     * @generated
     */
    EList<DataInstance> getSubDataInstances();

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    ComponentInstance getComponentInstance(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    AtomInstance getAtomInstance(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    CompoundInstance getCompoundInstance(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    ConnectorInstance getConnectorInstance(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    CompoundPriorityInstance getCompoundPriorityInstance(String name);

} // CompoundInstance
