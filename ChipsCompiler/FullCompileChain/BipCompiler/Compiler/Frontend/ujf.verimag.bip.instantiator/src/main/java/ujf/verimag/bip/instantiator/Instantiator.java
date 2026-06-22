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

package ujf.verimag.bip.instantiator;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

import org.eclipse.emf.common.util.Diagnostic;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.emf.ecore.util.Diagnostician;
import org.eclipse.emf.ecore.util.EcoreUtil;
import org.eclipse.emf.ecore.xmi.impl.XMLResourceFactoryImpl;

import ujf.verimag.bip.instantiator.error.InstantiatorDiagnosticError;
import ujf.verimag.bip.metamodel.AnnotatedEObject;
import ujf.verimag.bip.parser.loader.PackageLoader;

import bip2.ujf.verimag.bip.actionlang.ActionlangFactory;
import bip2.ujf.verimag.bip.actionlang.BinaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.DirectBooleanExpression;
import bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.DirectFloatExpression;
import bip2.ujf.verimag.bip.actionlang.DirectIntegerExpression;
import bip2.ujf.verimag.bip.actionlang.DirectStringExpression;
import bip2.ujf.verimag.bip.actionlang.FunctionCallExpression;
import bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.UnaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.ValuedExpression;
import bip2.ujf.verimag.bip.actionlang.ValuedReferenceExpression;
import bip2.ujf.verimag.bip.component.ComponentDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomExportPortDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomExternalPortDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomInternalPortDeclaration;
import bip2.ujf.verimag.bip.component.compound.CompoundExportDataDeclaration;
import bip2.ujf.verimag.bip.component.compound.CompoundExportPortDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorExportedPortDeclaration;
import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataDeclarationReferenceDataParameter;
import bip2.ujf.verimag.bip.data.SubDataDeclarationReference;
import bip2.ujf.verimag.bip.instance.AtomExternalPortInstance;
import bip2.ujf.verimag.bip.instance.AtomInstance;
import bip2.ujf.verimag.bip.instance.AtomInternalPortInstance;
import bip2.ujf.verimag.bip.instance.ComponentInstance;
import bip2.ujf.verimag.bip.instance.CompoundInstance;
import bip2.ujf.verimag.bip.instance.CompoundPriorityInstance;
import bip2.ujf.verimag.bip.instance.ConnectorInstance;
import bip2.ujf.verimag.bip.instance.ConnectorPortInstance;
import bip2.ujf.verimag.bip.instance.DataInstance;
import bip2.ujf.verimag.bip.instance.ExportedPortInstance;
import bip2.ujf.verimag.bip.instance.InstanceFactory;
import bip2.ujf.verimag.bip.instance.PortInstance;
import bip2.ujf.verimag.bip.packaging.BipPackage;
import bip2.ujf.verimag.bip.port.PortDeclaration;
import bip2.ujf.verimag.bip.port.PortDeclarationReferenceParameter;
import bip2.ujf.verimag.bip.port.SubPortDeclarationReference;
import bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration;
import bip2.ujf.verimag.bip.types.AtomType;
import bip2.ujf.verimag.bip.types.CompoundType;
import bip2.ujf.verimag.bip.types.ConnectorType;


/**
 * This class is used to create an instance graph given a type graph and
 * a component type to instantiate (+ some potential arguments for this root instance).
 * The instance graph is a representation of the system as it should be at runtime
 * after deployment. It can thus be used to guide the deployment method (in backend for example).
 */
public class Instantiator {
    /**
     * The instanciator relies on a PackageLoader, similar in its role to the
     * java ClassLoader.
     */
    protected PackageLoader loader;

    /**
     * This stack is used to keep track of compound that must be handled :
     * the instantiator must create instances out of its sub components and connectors.
     */
    protected Stack<CompoundInstance> compound_instances_stack = new Stack<CompoundInstance>();

    /**
     * Creates a new Instantiator
     * @param loader the package loader the instantiator will use.
     */
    public Instantiator(PackageLoader loader) {
        this.loader = loader;
    }

    /**
     * Currently, the instantiator takes instances during a single pass. In some cases
     * it is not possible to create the graph like that (a connector declaration that
     * links another connector not yet declared, for example).
     * When a hole is found, this exception is raised. A multi-pass instantiator
     * could be done.
     */
    private class PostPoneInstantiationException extends Exception {
        private static final long serialVersionUID = 1L;
    }

    /**
     * Serialize an instance object to a file. The file's extension is used to
     * decide the serialization format
     * 
     * @param filename
     *            the target filename
     * @param instance
     */
    public void serializeInstance(String filename, EObject instance) {
        // create resource set and resource
        ResourceSet resourceSet = new ResourceSetImpl();

        // Register XML resource factory
        resourceSet.getResourceFactoryRegistry().getExtensionToFactoryMap()
                .put("xsd", new XMLResourceFactoryImpl());

        Resource resource = resourceSet.createResource(URI
                .createFileURI(filename));
        // add the root object to the resource
        resource.getContents().add(instance);
        // serialize resource you can specify also serialization
        // options which defined on org.eclipse.emf.ecore.xmi.XMIResource
        try {
            resource.save(null);
        } catch (IOException e) {
        }
    }



    /**
     * Create an instance of a component type and validate it if asked.
     * @param declaration component declaration to instantiate
     * @param validate if true, validate the result. Skip validation if false.
     * @throws InstantiatorException in case of validation error or instantiation error
     * @return the instance
     */
    public ComponentInstance instantiateTopLevel(ComponentDeclaration declaration, boolean validate) throws InstantiatorException{
        ComponentInstance ci = instantiate(declaration);
        if (validate){
            InstantiatorDiagnosticError[] errors = validate(ci);
            if (errors.length != 0){
                throw new InstantiatorException(errors);
            }
        }
        return ci;
    }

    /**
     * Create an instance of a component type and validate it.
     * @param declaration component declaration to instantiate
     * @throws InstantiatorException in case of validation error or instantiation error
     * @return the instance
     */
    public ComponentInstance instantiateTopLevel(ComponentDeclaration declaration) throws InstantiatorException{
        return instantiateTopLevel(declaration, true);
    }

    /**
     * Create an instance of a component type
     * 
     * @param declaration
     *            the component declaration
     * @return the instance
     * @throws InstantiatorException
     */
    public ComponentInstance instantiate(ComponentDeclaration declaration)
            throws InstantiatorException {
        ComponentInstance ci = null;

        if (declaration.getType() instanceof AtomType) {
            AtomInstance ai = InstanceFactory.eINSTANCE.createAtomInstance();
            ci = ai;
            ai.setDeclaration(declaration);

            /*
             * An atom can host data and port (internal & exported). No
             * connector nor component
             */
            AtomType type = (AtomType) declaration.getType();

            // data
            for (DataDeclaration dd : type.getInternalDataDeclarations()) {
                DataInstance di = instantiate(dd);
                ai.getSubDataInstances().add(di);
            }
            // internal ports
            for (AtomInternalPortDeclaration pd : type
                    .getInternalPortDeclarations()) {
                List<DataInstance> param = new ArrayList<DataInstance>();
                for (DataDeclarationReferenceDataParameter ddrdp : pd
                        .getDataParameters()) {
                    DataInstance di = ai.getInternalDataInstance(ddrdp
                            .getDataDeclarationReference().getName());
                    if (di == null)
                        // This is an error as the reference does not point to
                        // data in the instance. This should not happen, as
                        // previous checks should prevent to reach this...
                        throw new InstantiatorException(ddrdp,
                                "Internal error: could not find corresponding instance.");
                    param.add(di);
                }

                AtomInternalPortInstance aipi = instantiate(pd,
                        param.toArray(new DataInstance[0]));
                ai.getInternalPorts().add(aipi);
            }
            
            // internal ports
            for (AtomExternalPortDeclaration pd : type
                    .getExternalPortDeclarations()) {
                List<DataInstance> param = new ArrayList<DataInstance>();
                for (DataDeclarationReferenceDataParameter ddrdp : pd
                        .getDataParameters()) {
                    DataInstance di = ai.getInternalDataInstance(ddrdp
                            .getDataDeclarationReference().getName());
                    if (di == null)
                        // This is an error as the reference does not point to
                        // data in the instance. This should not happen, as
                        // previous checks should prevent to reach this...
                        throw new InstantiatorException(ddrdp,
                                "Internal error: could not find corresponding instance.");
                    param.add(di);
                }

                AtomExternalPortInstance aipi = instantiate(pd,
                        param.toArray(new DataInstance[0]));
                ai.getExternalPorts().add(aipi);
            }

            // exported ports.
            for (PortDeclaration pd : type.getExportedPortDeclarations()) {
                ExportedPortInstance epi = InstanceFactory.eINSTANCE
                        .createExportedPortInstance();
                epi.setDeclaration(pd);
                // cast is safe, we know we have an Atom type.
                AtomExportPortDeclaration aepd = (AtomExportPortDeclaration) pd;
                for (AtomInternalPortDeclaration sub_pd : aepd
                        .getPortDeclarationReferences()) {
                    AtomInternalPortInstance sub_pi = ai
                            .getInternalPortInstance(sub_pd.getName());
                    epi.getReferencedPorts().add(sub_pi);
                }

                ai.getExportedPorts().add(epi);
            }
        } else if (declaration.getType() instanceof CompoundType) {
            CompoundType ct = (CompoundType) declaration.getType();

            CompoundInstance compoundi = InstanceFactory.eINSTANCE
                    .createCompoundInstance();
            ci = compoundi;
            ci.setDeclaration(declaration);

            // push this instance on the stack so that
            // inner declaration can access it.
            this.compound_instances_stack.push(compoundi);

            /*
             * A compound can host component and connector
             */

            // sub components
            for (ComponentDeclaration cd : ct.getComponentDeclarations()) {
                ComponentInstance sub_ci = instantiate(cd);
                if (sub_ci instanceof AtomInstance) {
                    compoundi.getSubAtomInstances().add((AtomInstance) sub_ci);
                } else if (sub_ci instanceof CompoundInstance) {
                    compoundi.getSubCompoundInstances().add(
                            (CompoundInstance) sub_ci);
                } else {
                    throw new InstantiatorException(cd,
                            "Internal error: component instance is neither an atom nor a compound.");
                }
            }

            // sub connectors (first pass, only for connectors connecting
            // components).
            for (ConnectorDeclaration cd : ct.getConnectorDeclarations()) {
                try {
                    List<PortInstance> params = new ArrayList<PortInstance>();

                    for (PortDeclarationReferenceParameter pp : cd
                            .getPortParameters()) {
                        SubPortDeclarationReference spdr = pp
                                .getSubPortDeclarationReference();

                        ComponentDeclaration comp_decl = spdr
                                .getComponentDeclaration();

                        ConnectorDeclaration conn_decl = spdr
                                .getConnectorDeclaration();
                        
                        if (comp_decl == null && conn_decl == null)
                            throw new PostPoneInstantiationException();
                        PortInstance pi = null;
                        if (comp_decl != null){
                            ComponentInstance subcompi = compoundi
                                    .getComponentInstance(comp_decl.getName());
                            if (subcompi == null)
                                throw new InstantiatorException(
                                        comp_decl,
                                        "Internal error, can't find corresponding component instance for port reference.");
                            pi = subcompi.getPortInstance(spdr
                                    .getForwardPortDeclaration().getName());
                        } else { // conn_decl != null
                            ConnectorInstance subconni = compoundi.getConnectorInstance(conn_decl.getName());
                            if (subconni == null)
                                throw new InstantiatorException(
                                        conn_decl,
                                        "Internal error, can't find corresponding connector instance for port reference.");
                            pi = subconni.getExportedPort();
                            
                            if (!pi.getDeclaration().getName().equals(spdr.getForwardPortDeclaration().getName())){
                                // names do not match !
                                pi = null;
                            }
                        }
                        if (pi == null)
                            throw new InstantiatorException(spdr,
                                    "Internal error, can't find corresponding port instance for port reference.");
                        params.add(pi);
                    }

                    ConnectorInstance connecti = instantiate(cd,
                            params.toArray(new PortInstance[0]));
                    compoundi.getSubConnectorInstances().add(connecti);
                } catch (PostPoneInstantiationException e) {
                    throw new InstantiatorException(
                            cd,
                            "Postponed instantiation not supported. Move connector type definition above first declaration using the type.");
                }
            }

            // priorities
            for (CompoundPriorityDeclaration pd : ct.getPriorities()) {
                CompoundPriorityInstance pi = InstanceFactory.eINSTANCE
                        .createCompoundPriorityInstance();
                pi.setDeclaration(pd);
                compoundi.getSubPriorities().add(pi);
                
                if (pd.getLow() != null){
                    String connector_name = pd.getLow().getConnectorDeclaration().getName();
                    ConnectorInstance conn_instance = compoundi.getConnectorInstance(connector_name);
                    pi.setLowConnector(conn_instance);
                    
                    for (SubPortDeclarationReference spdr : pd.getLow().getPortDeclarationReferences()){
                        PortInstance port_instance = null;
                        if (spdr.getComponentDeclaration() != null){
                            ComponentInstance comp_instance = compoundi.getComponentInstance(spdr.getComponentDeclaration().getName());
                            port_instance = comp_instance.getPortInstance(spdr.getForwardPortDeclaration().getName());
                        } else if (spdr.getConnectorDeclaration() != null) {
                            ConnectorInstance sconn_instance = compoundi.getConnectorInstance(spdr.getConnectorDeclaration().getName());
                            port_instance = sconn_instance.getExportedPort();
                        }
                        pi.getLowPorts().add(port_instance);
                    }
                }
                
                if (pd.getHigh() != null){
                    String connector_name = pd.getHigh().getConnectorDeclaration().getName();
                    ConnectorInstance conn_instance = compoundi.getConnectorInstance(connector_name);
                    pi.setHighConnector(conn_instance);
                    
                    for (SubPortDeclarationReference spdr : pd.getHigh().getPortDeclarationReferences()){
                        PortInstance port_instance = null;
                        if (spdr.getComponentDeclaration() != null){
                            ComponentInstance comp_instance = compoundi.getComponentInstance(spdr.getComponentDeclaration().getName());
                            port_instance = comp_instance.getPortInstance(spdr.getForwardPortDeclaration().getName());
                        } else if (spdr.getConnectorDeclaration() != null) {
                            ConnectorInstance sconn_instance = compoundi.getConnectorInstance(spdr.getConnectorDeclaration().getName());
                            port_instance = sconn_instance.getExportedPort();
                        }
                        pi.getHighPorts().add(port_instance);
                    }
                }
            }

            // exported data
            for (CompoundExportDataDeclaration cedd : ct
                    .getExportDataDeclarations()) {
                DataInstance di = InstanceFactory.eINSTANCE
                        .createDataInstance();
                di.setDeclaration(cedd);

                SubDataDeclarationReference ddr = cedd
                        .getDataDeclarationReference();
                // export data should only point to component data...
                assert (ddr.getComponentDeclaration() != null);

                ComponentInstance sub_ci = compoundi.getComponentInstance(ddr
                        .getComponentDeclaration().getName());
                DataInstance sub_di = sub_ci.getDataInstance(ddr
                        .getForwardDataDeclaration().getName());

                di.setProxyLink(sub_di);
                compoundi.getSubDataInstances().add(di);
            }

            // exported ports
            for (CompoundExportPortDeclaration cepd : ct
                    .getExportPortDeclarations()) {
                ExportedPortInstance epi = InstanceFactory.eINSTANCE
                        .createExportedPortInstance();
                epi.setDeclaration(cepd);
                for (SubPortDeclarationReference pdr : cepd
                        .getPortDeclarationReferences()) {
                    PortInstance sub_pi;

                    if (pdr.getComponentDeclaration() != null) {
                        ComponentInstance sub_ci = compoundi
                                .getComponentInstance(pdr
                                        .getComponentDeclaration().getName());
                        sub_pi = sub_ci.getPortInstance(pdr
                                .getForwardPortDeclaration().getName());
                    } else if (pdr.getConnectorDeclaration() != null) {
                        ConnectorInstance sub_ci = compoundi
                                .getConnectorInstance(pdr
                                        .getConnectorDeclaration().getName());
                        sub_pi = sub_ci.getExportedPort();
                        if (!sub_pi
                                .getDeclaration()
                                .getName()
                                .equals(pdr.getForwardPortDeclaration()
                                        .getName())) {
                            throw new InstantiatorException(cepd,
                                    "Internal error: exported port name does not match name found in instance.");
                        }
                    } else {
                        throw new InstantiatorException(
                                cepd,
                                "Internal error: compound export port does not contain any forwarding port, this should not be possible.");
                    }
                    epi.getReferencedPorts().add(sub_pi);
                }
                compoundi.getExportedPorts().add(epi);
            }
            // compound instantiation finished, pop it from the stack.
            this.compound_instances_stack.pop();
        }
        assert (ci != null); // should never be the case as type can only be an
                             // atom or a compound... But who knows what will be
                             // added in the future.
        
        return ci;
    }

    /**
     * Create an instance of a connector
     * 
     * @param type
     *            the connector declaration
     * @return the instance
     * @throws InstantiatorException
     */
    private ConnectorInstance instantiate(ConnectorDeclaration declaration,
            PortInstance[] portParameters) throws InstantiatorException {
        ConnectorType ct = declaration.getType();

        ConnectorInstance ci = InstanceFactory.eINSTANCE
                .createConnectorInstance();
        ci.setDeclaration(declaration);

        for (PortInstance pi : portParameters) {
            ci.getPortParamInstances().add(pi);
        }

        for (DataDeclaration dd : ct.getDataDeclarations()) {
            DataInstance di = instantiate(dd);
            ci.getSubDataInstances().add(di);
        }

        if (ct.getExportedPortDeclaration() != null) {
            ConnectorExportedPortDeclaration cepd = ct
                    .getExportedPortDeclaration();

            List<DataInstance> param = new ArrayList<DataInstance>();
            for (DataDeclarationReferenceDataParameter ddrdp : cepd.getDataParameters()){
                DataInstance di = ci.getDataInstance(ddrdp.getDataDeclarationReference().getName());

                if (di == null)
                    throw new InstantiatorException(ddrdp,
                            "Internal error: could not find corresponding instance.");
                param.add(di);
            }

            ConnectorPortInstance pi = instantiate(cepd,
                    param.toArray(new DataInstance[0]));
            ci.setExportedPort(pi);
        }
        return ci;
    }

    /**
     * Create an instance of an atom internal port
     * 
     * @param type
     *            the port declaration
     * @return the instance
     */
    private AtomInternalPortInstance instantiate(
            AtomInternalPortDeclaration declaration,
            DataInstance[] dataParameters) {
        AtomInternalPortInstance aipi = InstanceFactory.eINSTANCE
                .createAtomInternalPortInstance();

        aipi.setDeclaration(declaration);
        for (DataInstance di : dataParameters) {
            aipi.getDataParamInstances().add(di);
        }
        return aipi;
    }

    /**
     * Create an instance of an atom internal port
     * 
     * @param type
     *            the port declaration
     * @return the instance
     */
    private AtomExternalPortInstance instantiate(
            AtomExternalPortDeclaration declaration,
            DataInstance[] dataParameters) {
        AtomExternalPortInstance aipi = InstanceFactory.eINSTANCE
                .createAtomExternalPortInstance();

        aipi.setDeclaration(declaration);
        for (DataInstance di : dataParameters) {
            aipi.getDataParamInstances().add(di);
        }
        return aipi;
    }

    /**
     * Create an instance of a connector port
     * 
     * @param type
     *            the port declaration
     * @return the instance
     */
    private ConnectorPortInstance instantiate(
            ConnectorExportedPortDeclaration declaration,
            DataInstance[] dataParameters) {
        ConnectorPortInstance cpi = InstanceFactory.eINSTANCE
                .createConnectorPortInstance();

        cpi.setDeclaration(declaration);
        for (DataInstance di : dataParameters) {
            cpi.getDataParamInstances().add(di);
        }
        return cpi;
    }

    /**
     * Create an instance of a data
     * 
     * @param type
     *            the data declaration
     * @return the instance
     */
    private DataInstance instantiate(DataDeclaration declaration) {
        DataInstance di = InstanceFactory.eINSTANCE.createDataInstance();
        di.setDeclaration(declaration);

        return di;
    }

    /**
     * Create an instance of a priority
     * 
     * @param type
     *            the priority declaration
     * @return the instance
     */
    // It is unused ATM, remove the warning.
    @SuppressWarnings("unused")
    private CompoundPriorityInstance instanciate(
            CompoundPriorityDeclaration declaration) {
        CompoundPriorityInstance pi = InstanceFactory.eINSTANCE
                .createCompoundPriorityInstance();
        pi.setDeclaration(declaration);
        return pi;
    }

    /**
     * Calls EMF validation framework to check that the instance graph
     * is correct wrt. Ecore model & constraints expressed in the model.
     * @param instance the root instance for the instance graph to check
     * @return the errors found by the diagnostician
     */
    public InstantiatorDiagnosticError[] validate(EObject instance) {
        Diagnostic diagnostic = Diagnostician.INSTANCE.validate(instance);

        if (diagnostic.getSeverity() != Diagnostic.OK) {
            List<InstantiatorDiagnosticError> error_list = new ArrayList<InstantiatorDiagnosticError>();

            if (diagnostic.getSeverity() == Diagnostic.ERROR
                    || diagnostic.getSeverity() == Diagnostic.WARNING) {

                for (Diagnostic d : diagnostic.getChildren()) {
                    switch (d.getSeverity()) {
                    case Diagnostic.ERROR:
                    case Diagnostic.WARNING:
                        InstantiatorDiagnosticError diag_error = new InstantiatorDiagnosticError(d);
                        error_list.add(diag_error);
                    }
                }
            }
            return error_list.toArray(new InstantiatorDiagnosticError[0]);
        } else {
            return  new InstantiatorDiagnosticError[0];
        }
    }
}
