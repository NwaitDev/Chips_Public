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

package ujf.verimag.bip.middleend.flattening;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.Stack;
import java.util.TreeSet;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import joptsimple.OptionSet;
import joptsimple.OptionSpec;

import org.eclipse.emf.common.util.BasicEList ;
import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.ecore.util.EcoreUtil;

import ujf.verimag.bip.error.GenericError;
import ujf.verimag.bip.middleend.FilterStatus;
import ujf.verimag.bip.middleend.FilterStatusEnum;
import ujf.verimag.bip.middleend.Filterable;
import bip2.ujf.verimag.bip.actionlang.ActionlangFactory;
import bip2.ujf.verimag.bip.actionlang.BinaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.BinaryOperators;
import bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.Expression;
import bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.ValuedExpression;
import bip2.ujf.verimag.bip.component.ComponentDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorDataDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorFactory;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionAction;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionDefinition;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionNestedDefinition;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionPortReference;
import bip2.ujf.verimag.bip.connector.ConnectorPortParameterDeclaration;
import bip2.ujf.verimag.bip.data.DataDeclarationReferenceDataParameter;
import bip2.ujf.verimag.bip.data.SubDataDeclarationReference;
import bip2.ujf.verimag.bip.packaging.BipPackage;
import bip2.ujf.verimag.bip.port.PortDeclaration;
import bip2.ujf.verimag.bip.port.PortDeclarationReferenceParameter;
import bip2.ujf.verimag.bip.port.SubPortDeclarationReference;
import bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration;
import bip2.ujf.verimag.bip.priority.ConnectorInteraction;
import bip2.ujf.verimag.bip.types.CompoundType;
import bip2.ujf.verimag.bip.types.ConnectorType;
import bip2.ujf.verimag.bip.types.TypesFactory;


public class FlatteningFilter implements Filterable {
	private class PortReferenceUpdater extends ExpressionTreeTransformer {
		private Map<String, ConnectorPortParameterDeclaration> ports;

		public PortReferenceUpdater(Map<String, ConnectorPortParameterDeclaration> ports) {
			this.ports = ports;
		}

		public ValuedExpression traverseSubData(SubDataDeclarationReferenceExpression sub) {
			if (sub.getSubDataDeclarationRef() != null) {
				sub = EcoreUtil.copy(sub);
				SubDataDeclarationReference ref = sub.getSubDataDeclarationRef();
				ConnectorPortParameterDeclaration port = ports.get(ref.getPortDeclaration().getName());
				if (port == null) {
					return sub;
				}
				ref.setPortDeclaration(port);
			}
			return sub;
		}
	}

	private class UserConnectorExpressionWalker extends PortReferenceUpdater {
		private ConnectorPortParameterDeclaration rem;
		private List<DataDeclarationReferenceDataParameter> params;
		private Map<String, ConnectorDataDeclaration> importedVars;

		public UserConnectorExpressionWalker(Map<String, ConnectorPortParameterDeclaration> ports,
											 Map<String, ConnectorDataDeclaration> importedVars,
											 ConnectorPortParameterDeclaration rem,
											 List<DataDeclarationReferenceDataParameter> params) {
			super(ports);
			this.rem = rem;
			this.params = params;
			this.importedVars = importedVars;
		}

		public ValuedExpression traverseSubData(SubDataDeclarationReferenceExpression ex) {
			SubDataDeclarationReferenceExpression sub =
				(SubDataDeclarationReferenceExpression) super.traverseSubData(ex);
			if (sub.getSubDataDeclarationRef() != null) {
				SubDataDeclarationReference ref = sub.getSubDataDeclarationRef();
				if (ref.getPortDeclaration() == rem) {
					int index = ref.getPortDeclaration().getPortType()
						.getDataParameterDeclarations().indexOf(ref.getForwardDataDeclaration());
					DirectDataDeclarationReferenceExpression result =
						ActionlangFactory.eINSTANCE.createDirectDataDeclarationReferenceExpression();
					ConnectorDataDeclaration decl =
						(ConnectorDataDeclaration) params.get(index).getDataDeclarationReference();
					assert(decl != null);
					ConnectorDataDeclaration eDecl = importedVars.get(decl.getName());
					if (eDecl != null) {
						result.setDataDeclaration(eDecl);
					} else {
						result.setDataDeclaration(decl);
					}
					return result;
				}
			}
			return sub;
		}
	}

	private class ExporterConnectorExpressionWalker extends PortReferenceUpdater {
		private Map<String, ConnectorDataDeclaration> variables;
		public ExporterConnectorExpressionWalker(Map<String, ConnectorPortParameterDeclaration> ports,
												 Map<String, ConnectorDataDeclaration> vars) {
			super(ports);
			variables = vars;
		}

		public ValuedExpression traverseDirectData(DirectDataDeclarationReferenceExpression ex) {
			ConnectorDataDeclaration decl = variables.get(ex.getDataDeclaration().getName());
			if (decl != null) {
				ex = EcoreUtil.copy(ex);
				ex.setDataDeclaration(decl);
			}
			return ex;
		}
	}



	private Map<String, ConnectorType> merged = new HashMap<String, ConnectorType>();
	private Map<ConnectorType, Integer> useCounter;
	private BipPackage pack;

	public FlatteningFilter(Map<String,String> parameters) {}

	@Override
	public GenericError[] configure(OptionSet options,
									Map<String, OptionSpec<String>> ospecs) {
		return new GenericError[0];
	}

	@Override
	public boolean isEnabled() {
		return true;
	}

	@Override
	public FilterStatus filterPackage(BipPackage pack) {
		this.pack = pack;
		this.useCounter = new HashMap<ConnectorType, Integer>();
		for (CompoundType ct : pack.getCompoundTypes()) {
			processCompound(ct);
		}
		for (ConnectorType tt : useCounter.keySet()) {
		    int count = useCounter.get(tt);
		    //count is one of
		    //0 - Introduced connector types not used in the model
		    //> 0 - Introduced and used connector types
		    //< 0 - Connector types of the original model
		    if (count == 0) {
		        pack.getConnectorTypes().remove(tt);
		    }
		}
		return new FilterStatus(FilterStatusEnum.SUCCESS);
	}

	/**
	 * Applies recursevly the connector flattening to sub-components
	 * and flattens the connectors of the provided compound component.
	 * @param ct is the compound component type to flatten
	 */
	private void processCompound(CompoundType ct) {
		for (ComponentDeclaration scomp : ct.getComponentDeclarations()) {
			if (scomp.getType() instanceof CompoundType) {
				processCompound((CompoundType) scomp.getType());
			}
		}
		for (ConnectorDeclaration exporter
				 : new ArrayList<ConnectorDeclaration>(ct.getConnectorDeclarations())) {
			if (exporter.getType().getExportedPortDeclaration() == null) {
				continue;
			}
			boolean didMerge = false;
			for (ConnectorDeclaration cd : ct.getConnectorDeclarations()) {
				if (exporter == cd) {
					continue;
				}
				ConnectorDeclaration user = null;
				ConnectorPortParameterDeclaration iport = null;
				for (PortDeclarationReferenceParameter param : cd.getPortParameters()) {
					SubPortDeclarationReference sub = param.getSubPortDeclarationReference();
					if (sub.getConnectorDeclaration() == exporter) {
						user = cd;
						iport = (ConnectorPortParameterDeclaration) param.getParameterDeclaration();
						break;
					}
				}
				if (user != null) {
					String name = user.getType().getName()
						+ "_" + exporter.getType().getName();
					ConnectorType mType = merged.get(name);
					if (mType == null) {
						mType = mergeConnectors(exporter.getType()
												, user.getType()

												, iport);
						merged.put(name, mType);
						mType.setName(name);
						pack.getConnectorTypes().add(mType);
					}
					updateUse(mType, 1);
					updateUse(user.getType(), -1);
					updateUse(exporter.getType(), -1);
					user.setType(mType);
					addDeclarationPorts(exporter, user, iport);
					processPriorities(ct, exporter, user);
					didMerge = true;
				}
			}
			if (didMerge) {
				ct.getConnectorDeclarations().remove(exporter);
			}
		}
	}

	private void updateUse(ConnectorType type, int inc) {
		Integer old = useCounter.get(type);
		int val = old == null ? 0 : old.intValue();
		useCounter.put(type, val + inc);
	}

	/**
	 * Replaces the port of the user connector bounded to the exported
	 * port of the exporter connector with the port parameters of the
	 * exporter.
	 * @param exporter the connector exporting a port.
	 * @param user the connector that uses the exported port.
	 * @param eport the port of the user connector bound to the
	 * exported port
	 */
	private void addDeclarationPorts(ConnectorDeclaration exporter,
									 ConnectorDeclaration user,
									 PortDeclaration eport) {
		int index = 0;
		List<PortDeclarationReferenceParameter> lst =
			new ArrayList<PortDeclarationReferenceParameter>(user.getPortParameters());
		for (PortDeclarationReferenceParameter p : lst) {
			if (p.getParameterDeclaration().equals(eport)) {
				user.getPortParameters().remove(index);
				for (PortDeclarationReferenceParameter p2 : exporter.getPortParameters()) {
					PortDeclarationReferenceParameter copy = EcoreUtil.copy(p2);
					copy.setParameterDeclaration(EcoreUtil.copy(copy.getParameterDeclaration()));
					user.getPortParameters().add(index, copy);
					index++;
				}
				break;
			}
			index++;
		}
	}

	private int portIndex(List<SubPortDeclarationReference> ports, PortDeclaration port) {
		int result = 0;
		for (SubPortDeclarationReference sub : ports) {
			if (sub.getForwardPortDeclaration() == port) {
				return result;
			}
			result++;
		}
		return -1;
	}

	private void processPriorities(CompoundType ct, ConnectorDeclaration exporter,
								   ConnectorDeclaration user) {
		PortDeclaration exported = exporter.getType().getExportedPortDeclaration();
		for (CompoundPriorityDeclaration cpd
				 : new ArrayList<CompoundPriorityDeclaration>(ct.getPriorities())) {
			int pIndex;
			if (cpd.getLow() != null
				&& cpd.getLow().getConnectorDeclaration() == user
				&& (pIndex = portIndex(cpd.getLow().getPortDeclarationReferences(), exported)) > -1) {
				ConnectorInteraction low = cpd.getLow();
				low.getPortDeclarationReferences().remove(pIndex);
				for (PortDeclarationReferenceParameter e : exporter.getPortParameters()) {
					low.getPortDeclarationReferences().add(pIndex,
														   EcoreUtil.copy(e.getSubPortDeclarationReference()));
					pIndex++;
				}
			} else if (cpd.getHigh() != null
					   && cpd.getHigh().getConnectorDeclaration() == user
					   && (pIndex = portIndex(cpd.getHigh().getPortDeclarationReferences(), exported)) > -1) {
				cpd.getHigh().getPortDeclarationReferences().remove(pIndex);
				ct.getPriorities().remove(cpd);
				int prioIndex = 0;
				// TODO: enumeration
				for (List<ConnectorPortParameterDeclaration> intr :
					getDefinedInteractions(exporter.getType().getInteractionDefinition())) {
					CompoundPriorityDeclaration copy = EcoreUtil.copy(cpd);
					if (prioIndex != 0) {
						boolean found = false;
						String name = copy.getName();
						do {
							copy.setName(name + prioIndex);
							prioIndex++;
							found = false;
							for (CompoundPriorityDeclaration p : ct.getPriorities()) {
								found = p.getName().equals(copy.getName());
								if (found) {
									break;
								}
							}
						} while (found);
					} else {
						prioIndex = 1;
					}
					ConnectorInteraction high = copy.getHigh();
					for (PortDeclarationReferenceParameter e : exporter.getPortParameters()) {
						if (!intr.contains(e.getParameterDeclaration())) {
							continue;
						}
						SubPortDeclarationReference repl = EcoreUtil.copy(e.getSubPortDeclarationReference());
						high.getPortDeclarationReferences().add(pIndex, repl);
					}
					ct.getPriorities().add(copy);
				}
			}
		}
	}

	/**
	 * Produces a flat connector from one that exports a port and a
	 * connector that uses the exported port.
	 * @param exporter The connector that exports a port
	 * @param user The connector that uses the exporter port.
	 * @param eport The declaration of the exported port
	 * @return a flattened connector that supports the same
	 * interactions as the two merged connectors. Note that if the
	 * user connector exports a port, the merged connector also
	 * exports a port.
	 */
	private ConnectorType mergeConnectors(ConnectorType exporter,
										  ConnectorType user,
										  ConnectorPortParameterDeclaration eport) {
		ConnectorType result = TypesFactory.eINSTANCE.createConnectorType();
		//construct the interaction definition of the new connector
		//and add the ports of both connectors to the list of ports of
		//the resulting connector
		Map<String, ConnectorPortParameterDeclaration> ports =
			constructInteractionDefinition(exporter, user, result, eport);

		ConnectorInteractionDefinition newDef = result.getInteractionDefinition();
		if (newDef instanceof ConnectorInteractionPortReference) {
			result.getPorts().add(((ConnectorInteractionPortReference) newDef).getPort());
		} else {
			result.getPorts()
				.addAll(getPorts((ConnectorInteractionNestedDefinition) result.getInteractionDefinition()));
		}
		//copy the data declarations of the user connector. Store the
		//variable names used for detecting name clashes when
		//importing data declarations from the exporter
		Set<String> usedVars = new TreeSet<String>();
		for (ConnectorDataDeclaration d : user.getDataDeclarations()) {
			result.getDataDeclarations().add(EcoreUtil.copy(d));
			usedVars.add(d.getName());
		}
		//copy data declarations of the exporter to the merged
		//connector. These variables are used in the down statements
		//of the connector. Store a mapping between old var names and
		//the corresponding data declaration object
		Map<String,  ConnectorDataDeclaration> importedVars =
			new HashMap<String,  ConnectorDataDeclaration>();
		for (ConnectorDataDeclaration d : exporter.getDataDeclarations()) {
			String nName = createUniqueName(d.getName(), usedVars);
			usedVars.add(nName);
			ConnectorDataDeclaration copy = EcoreUtil.copy(d);
			copy.setName(nName);
			importedVars.put(d.getName(), copy);
			result.getDataDeclarations().add(copy);
		}
		if (user.getExportedPortDeclaration() != null) {
			result.setExportedPortDeclaration(EcoreUtil.copy(user.getExportedPortDeclaration()));
		}
		Map<String, ConnectorPortParameterDeclaration> userPorts =
			new HashMap<String, ConnectorPortParameterDeclaration>();
		for (ConnectorPortParameterDeclaration up : user.getPorts()) {
			if (eport.getName().equals(up.getName())) {
				continue;
			}
			for (ConnectorPortParameterDeclaration cp : result.getPorts()) {
				if (cp.getName().equals(up.getName())) {
					userPorts.put(cp.getName(), cp);
					break;
				}
			}
		}
		ExporterConnectorExpressionWalker exporterWalker =
			new ExporterConnectorExpressionWalker(ports, importedVars);
		UserConnectorExpressionWalker u = 
			new UserConnectorExpressionWalker(userPorts, importedVars, eport,
											  exporter.getExportedPortDeclaration().getDataParameters());
		StatementTransformer userTransformer = new StatementTransformer(),
			exporterTransformer = new StatementTransformer();
		userTransformer.setExpressionTransformer(u);
		exporterTransformer.setExpressionTransformer(exporterWalker);

		//replace each interaction of the user connector that involves
		//the port imported from the exporter with the interactions of
		//exporter.
		
		for (List<ConnectorPortParameterDeclaration> prts : getDefinedInteractions(user.getInteractionDefinition())) {
			//I need Sets because the equals method in Lists takes into account the order of elements 
			Set<ConnectorPortParameterDeclaration>
				myPorts = new HashSet<ConnectorPortParameterDeclaration>(),
				interactionPorts = new HashSet<ConnectorPortParameterDeclaration>();
			for (Object prt : prts) {
				assert(prt instanceof ConnectorPortParameterDeclaration);
				myPorts.add((ConnectorPortParameterDeclaration) prt);
			}
			ConnectorInteractionAction action = null;
			for (ConnectorInteractionAction cia : user.getInteractions()) {
				interactionPorts.addAll(cia.getOnPorts());
				if (myPorts.equals(interactionPorts)) {
					action = cia;
					break;
				}
			}
			if (action == null && exporter.getInteractions().isEmpty()) {
				continue;
			}
			if (action == null) {
				action = ConnectorFactory.eINSTANCE.createConnectorInteractionAction();
				action.getOnPorts().addAll(myPorts);
			}
			int pIndex = action.getOnPorts().indexOf(eport);
			if (pIndex < 0) {
				result.getInteractions().add(replaceOnPorts(action, result.getPorts(), null));
				//No further processing required for this interaction since
				//it does not involve the exported port
				continue;
			}
			ConnectorInteractionAction template = replaceOnPorts(action, result.getPorts(),
																 eport.getName());

			//The down statements of the template interaction may
			//contain references to parameters of the removed port. We
			//replace such references with the variable of the
			//exporter connector bound to the specific port parameter
			List<Expression>
				down = userTransformer.traverseExpressionList(template.getDown()),
				up = userTransformer.traverseExpressionList(template.getUp());
			template.getDown().clear();
			template.getDown().addAll(down);
			template.getUp().clear();
			template.getUp().addAll(up);
			//if the exporter has no defined interactions we add the
			//template action to the interactions of the combined connector.
			if (exporter.getInteractions().isEmpty()) {
				result.getInteractions().add(template);
			}
			//Now that the template no longer contains references to
			//the removed port we combine it with each interaction of
			//the exporter connector and add the resulting interaction
			//to the new connector
			for (ConnectorInteractionAction repl : exporter.getInteractions()) {
				int index = pIndex; //points to the removed port
				ConnectorInteractionAction copy = EcoreUtil.copy(template);
				//add the ports of the exporter interactions to the merged interaction
				for (ConnectorPortParameterDeclaration port2 : repl.getOnPorts()) {
					copy.getOnPorts().add(index, ports.get(port2.getName()));
					index++;
				}
				//When the user connector has guarded interactions
				//that involve the exported port of the exporter
				//connector and the up statements of the exporter
				//include if statements the values of the exported
				//port depend on the followed branch of the if
				//statements. Since assignments are not possible in
				//the guard, we have to transform the if statements
				//into a boolean expression.
				ValuedExpression
					eGuard = repl.getGuard() != null ? exporterWalker.traverseValued(repl.getGuard()) : null,
					uGuard = copy.getGuard() != null
					? traverseGuard(exporter.getExportedPortDeclaration().getDataParameters(),
									eport, repl.getUp(), copy.getGuard()) : null;
				if (eGuard != null) {
					if (uGuard != null) {
						//if both interactions have guards, combine them in one guard
						BinaryOpExpression bop =
							ActionlangFactory.eINSTANCE.createBinaryOpExpression();
						//						bop.eAdapters().add();
											 
						bop.setOperator(BinaryOperators.LOGICAL_AND);
						bop.setLeft(eGuard);
						bop.setRight(uGuard);
						copy.setGuard(bop);
					} else {
						copy.setGuard(eGuard);
					}
				} else {
					copy.setGuard(uGuard);
				}
				index = 0;
				//if the user connector has up statements, prepped the
				//exporter's up, otherwise copy each statement of the
				//exporter interaction in the beginning of the down
				//statements of the merged interaction. Computations
				//performed in the exporter's up are now performed
				//before the statements of the merged interaction
				List<Expression> actions = copy.getUp().isEmpty()
					? copy.getDown() : copy.getUp();
				for (Expression ex : repl.getUp()) {
					Expression tr = exporterTransformer.traverseExpression(ex);
					actions.add(index, tr);
					index++;
				}
				//append the down statements of the exporter interaction
				for (Expression ex : repl.getDown()) {
					Expression tr = exporterTransformer.traverseExpression(ex);
					copy.getDown().add(tr);
				}
				result.getInteractions().add(copy);
			}
		}
		return result;
	}

	private ValuedExpression traverseGuard(final List<DataDeclarationReferenceDataParameter> params,
										   final ConnectorPortParameterDeclaration rem,
										   List<Expression> up,
										   ValuedExpression ex) {
		// final ExpressionPrinter printer = new ExpressionPrinter();
		ExpressionEvaluator evaluator = new ExpressionEvaluator();
		evaluator.traverseExpressionList(up);
		ValuedExpression result = null;
		final Map<String, ValuedExpression> vars = new HashMap<String, ValuedExpression>();

		ExpressionTreeTransformer portCollector =
			new ExpressionTreeTransformer() {
				public ValuedExpression traverseSubData(SubDataDeclarationReferenceExpression ex) {
					SubDataDeclarationReference ref = ex.getSubDataDeclarationRef();
					if (ref.getPortDeclaration().equals(rem)) {
						int paramIndex = rem.getPortType()
							.getDataParameterDeclarations().indexOf(ref.getForwardDataDeclaration());
						DataDeclarationReferenceDataParameter data = params.get(paramIndex);
						return EcoreUtil.copy(vars.get(data.getDataDeclarationReference().getName()));
					}
					return super.traverseSubData(ex);
				}
			};
		for (ExpressionEvaluator ev : evaluator.getPaths()) {
			vars.clear();
			vars.putAll(ev.context);
			ValuedExpression guard = portCollector.traverseValued(ex);
			if (ev.condition != null) {
				BinaryOpExpression bop =
					ActionlangFactory.eINSTANCE.createBinaryOpExpression();
				bop.setOperator(BinaryOperators.LOGICAL_AND);
				bop.setLeft(EcoreUtil.copy(ev.condition));
				bop.setRight(guard);
				guard = bop;
			}
			if (result == null) {
				result = guard;
			} else {
				BinaryOpExpression bop =
					ActionlangFactory.eINSTANCE.createBinaryOpExpression();
				bop.setOperator(BinaryOperators.LOGICAL_OR);
				bop.setLeft(result);
				bop.setRight(guard);
				result = bop;
			}
		}
		return result;
	}


	private ConnectorInteractionAction replaceOnPorts(ConnectorInteractionAction act,
													  List<ConnectorPortParameterDeclaration> ports,
													  String iport) {
		ConnectorInteractionAction result = EcoreUtil.copy(act);
		result.getOnPorts().clear();
		for (ConnectorPortParameterDeclaration port : act.getOnPorts()) {
			for (ConnectorPortParameterDeclaration orPort : ports) {
				if (port.getName().equals(orPort.getName())
					&& !port.getName().equals(iport)) {
					result.getOnPorts().add(orPort);
					break;
				}
			}
		}
		//at most one port (the imported one) is not copied
		assert(act.getOnPorts().size() - result.getOnPorts().size() <= 1);
		return result;
	}


	/**
	 * Merges the interaction defintions of both connectors. Ports
	 * declared in the exporter connector are imported in the
	 * interaction definition of the user connector. In case both
	 * connectors declare a port with the same name, the port included
	 * from the exporter connector is renamed before import. The
	 * method calculates a mapping from the old names to the new
	 * ports.
	 * @param exporter The connector that exports a port
	 * @param user The connector that uses the exporter port.
	 * @param eport The declaration of the exported port
	 * @return a mapping from old port names to the corresponding port
	 * declaration instance. The map contains both renamed and
	 * unmodified ports.
	 */
	private Map<String, ConnectorPortParameterDeclaration>
		constructInteractionDefinition(ConnectorType exporter,
									   ConnectorType user,
									   ConnectorType cp,
									   PortDeclaration eport) {
		Map<String, ConnectorPortParameterDeclaration> result
			= new HashMap<String, ConnectorPortParameterDeclaration>();
		ConnectorInteractionDefinition ndef,
			def = user.getInteractionDefinition();
		if (def instanceof ConnectorInteractionPortReference) {
			//if the definition only includes a port, just replace it
			//with the definition provided by the exporter
			ndef = copy(exporter.getInteractionDefinition(), new HashSet<String>(), result);
			ndef.setQuoted(user.getInteractionDefinition().isQuoted());
		} else {
			//SortedSet instance
			Set<String> ports = new TreeSet<String>();
			for (ConnectorPortParameterDeclaration p : user.getPorts()) {
				ports.add(p.getName());
			}
			ports.remove(eport.getName());
			ndef =
				replaceImportedPort((ConnectorInteractionNestedDefinition) def,
									exporter.getInteractionDefinition(),
									eport, ports, result);
			simplifyDeclaration(ndef);
		}
		cp.setInteractionDefinition(ndef);

		return result;
	}


	private void simplifyDeclaration(ConnectorInteractionDefinition def) {
		if (def instanceof ConnectorInteractionPortReference) {
			return;
		}
		ConnectorInteractionNestedDefinition tree = (ConnectorInteractionNestedDefinition) def;
		List<ConnectorInteractionDefinition> ndef = new ArrayList<ConnectorInteractionDefinition>();
		boolean changed = false;
		for (ConnectorInteractionDefinition node : tree.getSubInteractions()) {
			if (node instanceof ConnectorInteractionNestedDefinition) {
				ConnectorInteractionNestedDefinition ntree = (ConnectorInteractionNestedDefinition) node;
				simplifyDeclaration(ntree);
				if (allSame(ntree)) {
					ndef.addAll(ntree.getSubInteractions());
					changed = true;
				} else {
					ndef.add(ntree);
				}
			} else {
				ndef.add(node);
			}
		}
		if (changed) {
			tree.getSubInteractions().clear();
			tree.getSubInteractions().addAll(ndef);
		}
	}

	private boolean allSame(ConnectorInteractionNestedDefinition def) {
		for (ConnectorInteractionDefinition node : def.getSubInteractions()) {
			if (def.isQuoted() != node.isQuoted()) {
				return false;
			}
		}
		return true;
	}

	/**
	 * Travjerses an interaction definition and fetches the ports
	 * refered in the definition.
	 * @param tree the expression to traverse
	 * @return a list of ports refered by the expression
	 */
	private List<ConnectorPortParameterDeclaration>
		getPorts(ConnectorInteractionNestedDefinition tree) {
		Stack<ConnectorInteractionNestedDefinition> remains =
			new Stack<ConnectorInteractionNestedDefinition>();
		remains.push(tree);
		List<ConnectorPortParameterDeclaration> result =
			new ArrayList<ConnectorPortParameterDeclaration>();
		do {
			ConnectorInteractionNestedDefinition curr = remains.pop();
			for (ConnectorInteractionDefinition def : curr.getSubInteractions()) {
				if (def instanceof ConnectorInteractionPortReference) {
					ConnectorInteractionPortReference p = (ConnectorInteractionPortReference) def;
					result.add(p.getPort());
				} else {
					remains.push((ConnectorInteractionNestedDefinition) def);
				}
			}
		} while (!remains.isEmpty());
		return result;
	}

	private void interactionToString(ConnectorInteractionDefinition def, StringBuffer sb) {
		if (def instanceof ConnectorInteractionPortReference) {
			sb.append(' ').
				append(((ConnectorInteractionPortReference) def).getPort().getName());
		} else {
			sb.append('(');
			for (ConnectorInteractionDefinition d
					 : ((ConnectorInteractionNestedDefinition) def).getSubInteractions()) {
				interactionToString(d, sb);
			}
			sb.append(')');
		}
		if (def.isQuoted()) {
			sb.append("'");
		}
	}

	/**
	 * Replaces references to removed ports with the ports imported
	 * from the exporter connector. Imported ports with names that
	 * allready exist in the user connector are renamed before
	 * imported. A mapping between the old port names and port
	 * instances is returned.
	 * @param tree is a tree of interaction definition.
	 * @param sub is the interaction definition of the exporter
	 * definition. The removed port of the user connector is replaced
	 * in the tree with sub definition.
	 * @param decl is the port declaration which is substituted with
	 * the sub definition.
	 * @param ports contains the ports of the exporter connector.
	 * @return a map with the names and ports of the merged connector.
	 */
	private ConnectorInteractionNestedDefinition
		replaceImportedPort(ConnectorInteractionNestedDefinition user
							, ConnectorInteractionDefinition exporter
							, PortDeclaration decl
							, Set<String> ports
							, Map<String, ConnectorPortParameterDeclaration> map) {
		ConnectorInteractionNestedDefinition result = EcoreUtil.copy(user);
		Stack<ConnectorInteractionNestedDefinition> remains =
			new Stack<ConnectorInteractionNestedDefinition>();
		remains.push(result);
		boolean done = false;
		do {
			ConnectorInteractionNestedDefinition curr = remains.pop();
			for (ConnectorInteractionDefinition def :
					 new ArrayList<ConnectorInteractionDefinition>(curr.getSubInteractions())) {
				if (def instanceof ConnectorInteractionPortReference) {
					ConnectorInteractionPortReference p = (ConnectorInteractionPortReference) def;
					if (!done && p.getPort().getName().equals(decl.getName())) {
						List<ConnectorInteractionDefinition> interactions = curr.getSubInteractions();
						int index = interactions.indexOf(p);
						interactions.remove(index);
						interactions.add(index, copy(exporter, ports, map));
						done = true;
					} else {
						p.setPort(EcoreUtil.copy(p.getPort()));
					}
				} else {
					remains.push((ConnectorInteractionNestedDefinition) def);
				}
			}
		} while (!remains.isEmpty());
		return result;
	}

	/**
	 * Creates a deep copy of a interaction definition renaming if needed ports of the exporter connector.
	 * All ports are placed in a map.
	 * @param def the interaction definition to copy.
	 * @param ports contains the ports of the user connector.
	 * @param map is used to place old port names and port instances.
	 * @return a copy of the interaction definition.
	 */
	private ConnectorInteractionDefinition
		copy(ConnectorInteractionDefinition def,
			 Set<String> usedNames,
			 Map<String, ConnectorPortParameterDeclaration> map) {
		if (def instanceof ConnectorInteractionPortReference) {
			ConnectorInteractionPortReference result =
				EcoreUtil.copy((ConnectorInteractionPortReference) def);
			copyPort(result, usedNames, map);
			return result;
		}
		Stack<ConnectorInteractionNestedDefinition> remaining =
			new Stack<ConnectorInteractionNestedDefinition>();
		ConnectorInteractionNestedDefinition result =
			EcoreUtil.copy((ConnectorInteractionNestedDefinition) def);
		remaining.push(result);
		while (!remaining.isEmpty()) {
			ConnectorInteractionNestedDefinition curr = remaining.pop();
			for (ConnectorInteractionDefinition sub : curr.getSubInteractions()) {
				if (sub instanceof ConnectorInteractionPortReference) {
					copyPort((ConnectorInteractionPortReference) sub,
							 usedNames, map);
				} else {
					remaining.push((ConnectorInteractionNestedDefinition) sub);
				}
			}
		}
		return result;
	}

	private void copyPort(ConnectorInteractionPortReference ref,
						  Set<String> usedNames,
						  Map<String, ConnectorPortParameterDeclaration> map) {
		String oldName = ref.getPort().getName();
		String newName = createUniqueName(ref.getPort().getName(), usedNames);
		usedNames.add(newName);
		ConnectorPortParameterDeclaration opr = ref.getPort(),
			pr = EcoreUtil.copy(opr);
		pr.setName(newName);
		ref.setPort(pr);
		map.put(oldName, pr);
	}

	private String createUniqueName(String name, Set<String> usedNames) {
		if (!usedNames.contains(name)) {
			return name;
		}
		int index = 1;
		Pattern nums = Pattern.compile("^([0-9]*[a-zA-Z_])+([0-9]+)$");
		Matcher m = nums.matcher(name);
		if (m.matches()) {
			String base = name.substring(0, m.end(1));
			index = Integer.parseInt(name.substring(m.start(2)));
			name = base;
		}
		while (usedNames.contains(name + index)) {
			index++;
		}
		return name + index;
	}

    /**
     * Compute the set of interactions resulting of
     * all possible concatenation of interactions
     * belonging to two input sets of interactions.
     * @param inter1 the first set of interactions
     * @param inter2 the second set of interactions
     * @return the set { i | i = i1 i2 } with i1 in
     * inter1 and i2 in inter2 
     */
	private boolean isSynchron(ConnectorInteractionNestedDefinition definition) {
		boolean ret = true;
		
		for (ConnectorInteractionDefinition def : definition.getSubInteractions()) {
			if (def.isQuoted()) {
				ret = false;
				break;
			}
		}
		
		return ret;
	}

    /**
     * Compute the set of interactions resulting of
     * all possible concatenation of interactions
     * belonging to two input sets of interactions.
     * @param inter1 the first set of interactions
     * @param inter2 the second set of interactions
     * @return the set { i | i = i1 i2 } with i1 in
     * inter1 and i2 in inter2 
     */
    private List<List<ConnectorPortParameterDeclaration>> combine(
            List<List<ConnectorPortParameterDeclaration>> set1,
            List<List<ConnectorPortParameterDeclaration>> set2) {
        List<List<ConnectorPortParameterDeclaration>> ret = null;

        if (set1.isEmpty()) {
            ret = set2;
        } else if (set2.isEmpty()) {
            ret = set1;
        } else {
            ret = new ArrayList<List<ConnectorPortParameterDeclaration>>();

            for (List<ConnectorPortParameterDeclaration> inter1 : set1) {
                for (List<ConnectorPortParameterDeclaration> inter2 : set2) {
                    // add to the returned interactions inter1 union inter2
                    List<ConnectorPortParameterDeclaration> inter = new ArrayList<ConnectorPortParameterDeclaration>(
                            inter1);
                    inter.addAll(inter2);
                    ret.add(inter);
                }
            }
        }

        return ret;
    }

    /**
     * Recursively enumerate of the interactions defined by an
     * interaction definition.
     * @param definition the target interaction definition
     * @return the set of defined interactions
     */
	private List<List<ConnectorPortParameterDeclaration>> getDefinedInteractions(ConnectorInteractionDefinition definition) {
	       List <List <ConnectorPortParameterDeclaration>> ret = new ArrayList <List <ConnectorPortParameterDeclaration>>();

	        if (definition instanceof ConnectorInteractionPortReference) {
	            ConnectorInteractionPortReference portRef = (ConnectorInteractionPortReference) definition;

	            // return a singleton interaction containing only portRef
	            List <ConnectorPortParameterDeclaration> interaction = new ArrayList <ConnectorPortParameterDeclaration>();
	            interaction.add(portRef.getPort());

	            ret.add(interaction);
	        } else if (definition instanceof ConnectorInteractionNestedDefinition) {
	            ConnectorInteractionNestedDefinition nestedDef = (ConnectorInteractionNestedDefinition) definition;

	            if (isSynchron(nestedDef)) {
	                // synchron: enumerate all possible combination of sub interactions
	                for (ConnectorInteractionDefinition def : nestedDef
	                        .getSubInteractions()) {
	                    ret = combine(ret, getDefinedInteractions(def));
	                }
	            } else {
	                // broadcast:
	                for (int triggerIndex = 0; triggerIndex < nestedDef
	                        .getSubInteractions().size(); triggerIndex++) {
	                    // enumerate all possible combination of sub interactions with one active trigger
	                    // the rest being either active or empty
	                    if (nestedDef.getSubInteractions().get(triggerIndex)
	                            .isQuoted()) {
	                        // enumerate with trigger begin the first active trigger
	                        ConnectorInteractionDefinition trigger = nestedDef
	                                .getSubInteractions().get(triggerIndex);

	                        List <List <ConnectorPortParameterDeclaration>> inters = getDefinedInteractions(trigger);

	                        for (int i = 0; i < nestedDef.getSubInteractions()
	                                .size(); i++) {
	                            ConnectorInteractionDefinition def = nestedDef
	                                    .getSubInteractions().get(i);

	                            if (!def.isQuoted() || i > triggerIndex) {
	                                // consider all interactions of def...
	                                List <List <ConnectorPortParameterDeclaration>> intersOfDef = getDefinedInteractions(def);

	                                // ... plus the empty interaction
	                                intersOfDef.add(new ArrayList <ConnectorPortParameterDeclaration>());

	                                inters = combine(inters, intersOfDef);
	                            }
	                        }

	                        ret.addAll(inters);
	                    }
	                }
	            }
	        } else {
	            assert (false);
	        }

	        return ret;
	}
}
