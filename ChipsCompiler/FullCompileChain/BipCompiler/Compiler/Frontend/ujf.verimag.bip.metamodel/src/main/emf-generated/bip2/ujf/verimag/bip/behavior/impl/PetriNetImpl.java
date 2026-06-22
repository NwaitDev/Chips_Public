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

package bip2.ujf.verimag.bip.behavior.impl;

import bip2.ujf.verimag.bip.actionlang.AssignmentExpression;
import bip2.ujf.verimag.bip.actionlang.BinaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.Expression;
import bip2.ujf.verimag.bip.actionlang.FunctionCallExpression;
import bip2.ujf.verimag.bip.actionlang.IfThenElseExpression;
import bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.UnaryOpExpression;
import bip2.ujf.verimag.bip.behavior.BehaviorPackage;
import bip2.ujf.verimag.bip.behavior.PetriNet;
import bip2.ujf.verimag.bip.behavior.State;
import bip2.ujf.verimag.bip.behavior.Transition;

import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataDeclarationReferenceDataParameter;
import bip2.ujf.verimag.bip.types.AtomType;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.BasicEList;
import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.EObjectImpl;

import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.EObjectResolvingEList;
import org.eclipse.emf.ecore.util.InternalEList;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

import lpsolve.LpSolve;
import lpsolve.LpSolveException;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Petri Net</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.behavior.impl.PetriNetImpl#getStates <em>States</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.behavior.impl.PetriNetImpl#getInitStates <em>Init States</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.behavior.impl.PetriNetImpl#getTransitions <em>Transitions</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.behavior.impl.PetriNetImpl#getInitialActions <em>Initial Actions</em>}</li>
 * </ul>
 *
 * @generated
 */
public class PetriNetImpl extends AnnotatedEObjectImpl implements PetriNet {
    /**
     * The cached value of the '{@link #getStates() <em>States</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getStates()
     * @generated
     * @ordered
     */
    protected EList<State> states;

    /**
     * The cached value of the '{@link #getInitStates() <em>Init States</em>}' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getInitStates()
     * @generated
     * @ordered
     */
    protected EList<State> initStates;

    /**
     * The cached value of the '{@link #getTransitions() <em>Transitions</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getTransitions()
     * @generated
     * @ordered
     */
    protected EList<Transition> transitions;

    /**
     * The cached value of the '{@link #getInitialActions() <em>Initial Actions</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getInitialActions()
     * @generated
     * @ordered
     */
    protected EList<Expression> initialActions;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected PetriNetImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return BehaviorPackage.Literals.PETRI_NET;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<State> getStates() {
        if (states == null) {
            states = new EObjectContainmentEList<State>(State.class, this,
                    BehaviorPackage.PETRI_NET__STATES);
        }
        return states;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<State> getInitStates() {
        if (initStates == null) {
            initStates = new EObjectResolvingEList<State>(State.class, this,
                    BehaviorPackage.PETRI_NET__INIT_STATES);
        }
        return initStates;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<Transition> getTransitions() {
        if (transitions == null) {
            transitions = new EObjectContainmentEList<Transition>(
                    Transition.class, this,
                    BehaviorPackage.PETRI_NET__TRANSITIONS);
        }
        return transitions;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<Expression> getInitialActions() {
        if (initialActions == null) {
            initialActions = new EObjectContainmentEList<Expression>(
                    Expression.class, this,
                    BehaviorPackage.PETRI_NET__INITIAL_ACTIONS);
        }
        return initialActions;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public State getState(String name) {
        for (State s : getStates()) {
            if (s.getName().equals(name)) {
                return s;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public Boolean isOneSafe(State state) {
        PetriNetGraph graph = new PetriNetGraph(this);

        return graph.isOneSafeAt(state);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public Boolean mayBeOneSafe(State state) {
        PetriNetGraphWithoutGuards graphWithoutGuards = new PetriNetGraphWithoutGuards(
                this);

        return graphWithoutGuards.isOneSafeAt(state)
                || !graphWithoutGuards.isAcyclic();
    }

    /**
     * Encapsulation of Petri Nets of the metamodel.
     * Provides means for accessing successors/predecessors of transitions and states.
     * @generated NOT
     */
    private class PetriNetGraph {
        PetriNetGraph(PetriNet pn) {
            this.pn = pn;
            this.predecessors = new HashMap<State, List<Transition>>();
            this.successors = new HashMap<State, List<Transition>>();

            // setup the ILP solver
            this.markingEquation = null;
        }

        public List<State> getStates() {
            return this.pn.getStates();
        }

        public List<State> getInitialStates() {
            return this.pn.getInitStates();
        }

        public List<Expression> getInitialActions() {
            return this.pn.getInitialActions();
        }

        public List<Transition> getTransitions() {
            return this.pn.getTransitions();
        }

        public List<State> getSuccessors(Transition transition) {
            return transition.getDestinations();
        }

        public List<State> getPredecessors(Transition transition) {
            return transition.getSources();
        }

        public List<Transition> getSuccessors(State state) {
            if (!this.successors.containsKey(state)) {
                List<Transition> successors = new ArrayList<Transition>();

                for (Transition transition : getTransitions()) {
                    if (transition.getSources().contains(state)) {
                        successors.add(transition);
                    }
                }

                this.successors.put(state, successors);
            }

            return this.successors.get(state);
        }

        public List<Transition> getPredecessors(State state) {
            if (!this.predecessors.containsKey(state)) {
                List<Transition> predecessors = new ArrayList<Transition>();

                for (Transition transition : getTransitions()) {
                    if (transition.getDestinations().contains(state)) {
                        predecessors.add(transition);
                    }
                }

                this.predecessors.put(state, predecessors);
            }

            return this.predecessors.get(state);
        }

        public boolean isOneSafeAt(State s) {
            Map<State, Integer> marking = new HashMap<State, Integer>();

            marking.put(s, 2);

            return !isCoverable(marking);
        }

        /**
         * Determine whether the Petri net is 1-safe or not.
         * @generated NOT
         * @return true if the Petri net is 1-safe, false if it
         * might be not deterministic.
         */
        public boolean isOneSafe() {
            for (State s : getStates()) {
                if (!isOneSafeAt(s)) {
                    return false;
                }
            }

            return true;
        }

        private boolean isAcyclic(Transition transition,
                List<Transition> path) {
            if (path.contains(transition)) {
                return false;
            } else {
                // add transition to the current path
                path.add(transition);

                for (State s : getSuccessors(transition)) {
                    for (Transition t : getSuccessors(s)) {
                        if (!isAcyclic(t, path)) {
                            return false;
                        }
                    }
                }

                // remove transition
                path.remove(path.size() - 1);
            }

            return true;
        }

        /**
         * Determine whether the Petri net is acyclic or not.
         * @generated NOT
         * @return true if the Petri net is acyclic, false if it
         * might be not deterministic.
         */
        public boolean isAcyclic() {
            for (Transition t : getTransitions()) {
                List<Transition> path = new ArrayList<Transition>();

                if (!isAcyclic(t, path)) {
                    return false;
                }
            }

            return true;
        }

        /**
         * Determine whether the Petri net is deterministic or not.
         * @generated NOT
         * @return true if the Petri net is deterministic, false if it
         * might be not deterministic.
         */
        public boolean isDeterministic() {
            for (Transition t1 : getTransitions()) {
                for (Transition t2 : getTransitions()) {
                    if (t1 != t2
                            && t1.getTriggerPort() == t2.getTriggerPort()) {
                        Set<State> states = new HashSet<State>();

                        if (t1.getSources().containsAll(t2.getSources()) || t2
                                .getSources().containsAll(t1.getSources())) {
                            return false;
                        }

                        states.addAll(t1.getSources());
                        states.addAll(t2.getSources());

                        if (isCoverable(states)) {
                            return false;
                        }
                    }
                }
            }

            return true;
        }

        /**
         * Determine whether a marking is coverable or not.
         * WARNING: It uses over-approximations meaning that it can
         * say yes for markings that are actually not reachable.
         * @generated NOT
         * @parameter marking the target marking to check
         * @return false if marking cannot be covered by the Petri net
         */
        public boolean isCoverable(Map<State, Integer> marking) {
            try {
                LpSolve solver = getMarkingEquation();

                for (State s : getStates()) {
                    if (marking.containsKey(s)) {
                        solver.setLowbo(indexOf(s), marking.get(s));
                    } else {
                        solver.setLowbo(indexOf(s), 0);
                    }
                }

                return (solver.solve() != LpSolve.INFEASIBLE);
            } catch (LpSolveException e) {
                // TODO: add a report of that, e.g. for the most verbose modes
                return true;
            }
        }

        public boolean isCoverable(List<State> states) {
            Map<State, Integer> marking = new HashMap<State, Integer>();

            for (State s : states) {
                marking.put(s, 1);
            }

            return isCoverable(marking);
        }

        public boolean isCoverable(Set<State> states) {
            Map<State, Integer> marking = new HashMap<State, Integer>();

            for (State s : states) {
                marking.put(s, 1);
            }

            return isCoverable(marking);
        }

        public boolean isDead(Transition transition) {
            return !isCoverable(getPredecessors(transition));
        }

        private LpSolve getMarkingEquation() throws LpSolveException {
            if (markingEquation == null) {
                markingEquation = LpSolve.makeLp(1,
                        getStates().size() + getTransitions().size());
                markingEquation.setVerbose(LpSolve.CRITICAL);

                // initialize variables & objective
                for (int i = 1; i <= getStates().size()
                        + getTransitions().size(); i++) {
                    markingEquation.setInt(i, true);
                    markingEquation.setLowbo(i, 0);
                    markingEquation.setObj(i, 0);
                }

                // add constraints corresponding the the marking equation
                markingEquation.setAddRowmode(true);

                for (State s : getStates()) {
                    double[] row = new double[1 + getStates().size()
                            + getTransitions().size()];

                    for (Transition t : getTransitions()) {
                        int flow = 0;

                        if (getPredecessors(s).contains(t))
                            flow++;
                        if (getSuccessors(s).contains(t))
                            flow--;

                        row[indexOf(t)] = -flow;
                    }

                    row[indexOf(s)] = 1;

                    int initial = getInitialStates().contains(s) ? 1 : 0;

                    markingEquation.addConstraint(row, LpSolve.EQ, initial);
                }

                // /!\ I don't know why but without doing a copy it does work well
                // TODO: investigate to understand why (the API is not clear about that)
                markingEquation = markingEquation.copyLp();
            }

            return markingEquation;
        }

        // compute indexes for ILP variables associated to states and transitions, starting from 1
        private int indexOf(State s) {
            return 1 + getStates().indexOf(s);
        }

        private int indexOf(Transition t) {
            return 1 + getStates().size() + getTransitions().indexOf(t);
        }

        // the target Petri net
        private PetriNet pn;

        // caches used to speed-up the execution
        private Map<State, List<Transition>> predecessors;
        private Map<State, List<Transition>> successors;
        private LpSolve markingEquation;
    }

    /**
     * Encapsulation of Petri Nets of the metamodel.
     * Provides means for accessing successors/predecessors of transitions and states.
     * @generated NOT
     */
    private class PetriNetGraphWithoutGuards extends PetriNetGraph {
        PetriNetGraphWithoutGuards(PetriNet pn) {
            super(pn);

            transitions = new ArrayList<Transition>();

            for (Transition t : super.getTransitions()) {
                // keep only transitions without guards
                if (t.getGuard() == null) {
                    transitions.add(t);
                }
            }
        }

        @Override
        public List<Transition> getTransitions() {
            return transitions;
        }

        private List<Transition> transitions;
    }

    /**
     * Encapsulation of Petri Nets of the metamodel.
     * Provides means for accessing successors/predecessors of transitions and states.
     * @generated NOT
     */
    private class PetriNetGraphInternalsWithoutGuards extends PetriNetGraph {
        PetriNetGraphInternalsWithoutGuards(PetriNet pn) {
            super(pn);

            transitions = new ArrayList<Transition>();

            for (Transition t : super.getTransitions()) {
                // keep only internal transitions without guards
                if (t.getTriggerPort() == null && t.getGuard() == null) {
                    transitions.add(t);
                }
            }
        }

        @Override
        public List<Transition> getTransitions() {
            return transitions;
        }

        private List<Transition> transitions;
    }

    /**
     * Encapsulation of Petri Nets of the metamodel.
     * Provides means for accessing successors/predecessors of transitions and states.
     * @generated NOT
     */
    private class PetriNetGraphWithoutDeadTransitions extends PetriNetGraph {
        PetriNetGraphWithoutDeadTransitions(PetriNetGraph petriNetGraph) {
            super(petriNetGraph.pn);

            transitions = new ArrayList<Transition>();

            for (Transition t : super.getTransitions()) {
                if (!petriNetGraph.isDead(t)) {
                    transitions.add(t);
                }
            }
        }

        @Override
        public List<Transition> getTransitions() {
            return transitions;
        }

        private List<Transition> transitions;
    }

    /**
     * This class implements an analysis for the use of uninitialized variable
     * in the code associated to transitions of a Petri Net.
     * @generated NOT
     */
    private class UninitializedAnalyzer {
        /**
         * @param pn the target petri net
         * @param uninit the set of variables to be checked, considered uninitialized
         * at the beginning of the analysis
         * @return 
         */
        UninitializedAnalyzer(PetriNetGraph pn,
                Set<DataDeclaration> targetVariables) {
            this.pn = pn;

            // initialize maps content with default values
            initializeMaps();

            // propagate uninit until a fixed point is reached
            initialize(targetVariables);

            // compute errors
            for (Transition t : this.pn.getTransitions()) {
                errors.addAll(getErrors(t));
            }
        }

        /**
         * Create new maps and fill them properly.
         */
        private void initializeMaps() {
            uninitialized = new HashMap<State, Set<DataDeclaration>>();
            errors = new ArrayList<Expression>();

            for (State s : pn.getStates()) {
                uninitialized.put(s, new HashSet<DataDeclaration>());
            }
        }

        /**
         * Create new maps and fill them properly.
         */
        private void initialize(Set<DataDeclaration> targetVariables) {
            // initially, all targetVariables are considered uninitialized
            Set<DataDeclaration> uninitializedAfterInitial = new HashSet<DataDeclaration>();
            uninitializedAfterInitial.addAll(targetVariables);

            checkUninitializedVariables(pn.getInitialActions(),
                    uninitializedAfterInitial, errors);

            // propagate
            for (State s : pn.getInitialStates()) {
                addUninitialized(s, uninitializedAfterInitial);
            }
        }

        /**
         * Add a set of uninitialized variables to a state, and propagate them in
         * the petri net if needed.
         * @param state the target state
         * @param uninit the target set of uninitialized variables
         */
        private void addUninitialized(State state,
                Set<DataDeclaration> uninit) {
            boolean modified = uninitialized.get(state).addAll(uninit);

            if (modified) {
                for (Transition t : pn.getSuccessors(state)) {
                    Set<DataDeclaration> uninitializedAfterT = getUninitializedAfter(
                            t);

                    for (State s : pn.getSuccessors(t)) {
                        addUninitialized(s, uninitializedAfterT);
                    }
                }
            }
        }

        /**
         * Compute the variables that may uninitialized when a given state is marked.
         * @param state the target state
         * @return the set of uninitialized variables
         */
        public Set<DataDeclaration> getUninitialized(State state) {
            return uninitialized.get(state);
        }

        /**
         * Compute the variables remaining uninitialized after the execution of the code
         * associated to a transition, considering that before this execution the set of
         * uninitialized variables is given by getUninitializedBefore().
         * @param transition the target transition
         * @return the set of uninitialized variables after the execution of transition
         */
        public Set<DataDeclaration> getUninitializedAfter(
                Transition transition) {
            Set<DataDeclaration> ret = getUninitializedBefore(transition);

            checkUninitializedVariables(transition.getActions(), ret, null);

            return ret;
        }

        /**
         * Compute the errors related to the use of uninitialized variables by the code of
         * a transition, considering that before the execution of the code the set of uninitialized
         * variables is given by getUninitializedBefore()
         * @param transition the target transition
         * @return the set of erroneous expressions
         */
        private List<Expression> getErrors(Transition transition) {
            List<Expression> ret = new ArrayList<Expression>();
            Set<DataDeclaration> uninitializedBefore = getUninitializedBefore(
                    transition);

            // check guard of the transition
            if (transition.getGuard() != null) {
                EList<DataDeclaration> uninitialized = new BasicEList<DataDeclaration>(
                        uninitializedBefore);

                EList<Expression> guardErrors = transition.getGuard()
                        .getMayReadUninitializedVariables(uninitialized);

                ret.addAll(guardErrors);
            }

            // check code executed by the transition
            checkUninitializedVariables(transition.getActions(),
                    getUninitializedBefore(transition), ret);

            return ret;
        }

        /**
         * Compute the current set of uninitialized variables before the execution of a transition.
         * It corresponds to the intersection of the set of uninitialized of all predecessor states.
         * @param transition the target transition
         * @return the set uninitialized variables before the execution of transition
         */
        public Set<DataDeclaration> getUninitializedBefore(
                Transition transition) {
            Set<DataDeclaration> ret = new HashSet<DataDeclaration>();

            boolean first = true;

            for (State s : pn.getPredecessors(transition)) {
                if (first) {
                    first = false;
                    ret.addAll(uninitialized.get(s));
                } else {
                    ret.retainAll(uninitialized.get(s));
                }
            }

            return ret;
        }

        public List<Expression> getErrors() {
            return errors;
        }

        protected PetriNetGraph pn;
        protected Map<State, Set<DataDeclaration>> uninitialized;
        protected List<Expression> errors;
    }

    /**
     * 
     * @generated NOT
     */
    public void checkUninitializedVariables(List<Expression> expression,
            Set<DataDeclaration> uninitialized, List<Expression> errors) {
        EList<DataDeclaration> uninitializedList = new BasicEList<DataDeclaration>(
                uninitialized);

        // /!\ WARNING: order is critical here since uninitialized is modified
        for (Expression subExpression : expression) {
            EList<Expression> subExpressionErrors = subExpression
                    .getMayReadUninitializedVariables(uninitializedList);

            if (errors != null)
                errors.addAll(subExpressionErrors);
        }

        // update uninitialized
        uninitialized.retainAll(uninitializedList);
    }

    /**
     * Compute data declarations of an atom, including both internal
     * and exported data declarations.
     * @param atom the target atom
     * @return the set of data declarations
     * @generated NOT
     */
    private Set<DataDeclaration> getAllDataDeclarationsWithoutValue(
            AtomType atom) {
        Set<DataDeclaration> ret = new HashSet<DataDeclaration>();

        for (DataDeclaration data : atom.getInternalDataDeclarations()) {
            if (data.getValue() == null) {
                ret.add(data);
            }
        }

        return ret;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public Boolean isCoverable(EList<State> states) {
        PetriNetGraphWithoutGuards graph = new PetriNetGraphWithoutGuards(this);

        return graph.isAcyclic() && graph.isDeterministic()
                && graph.isCoverable(states);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public Boolean mayBeCoverable(EList<State> states) {
        PetriNetGraph graph = new PetriNetGraph(this);

        return graph.isCoverable(states);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public EList<Expression> getUninitializedVariables() {
        assert (this.eContainer() instanceof AtomType);
        AtomType atom = (AtomType) this.eContainer();

        // analysis of uninitialized variables
        PetriNetGraph graph = new PetriNetGraph(this);
        UninitializedAnalyzer analyzer = new UninitializedAnalyzer(graph,
                getAllDataDeclarationsWithoutValue(atom));

        return new BasicEList<Expression>(analyzer.getErrors());
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public EList<DataDeclaration> getUninitializedExportedVariables() {
        assert (this.eContainer() instanceof AtomType);
        AtomType atom = (AtomType) this.eContainer();

        // restrict the Petri net to the initialization phase, i.e. initial actions +
        // internal transitions (those with guards are removed since we are not sure that
        // they can execute)
        PetriNetGraphInternalsWithoutGuards graphInternalsWithoutGuards = new PetriNetGraphInternalsWithoutGuards(
                this);

        // remove all dead transitions from the previous Petri net
        PetriNetGraphWithoutDeadTransitions graph = new PetriNetGraphWithoutDeadTransitions(
                graphInternalsWithoutGuards);

        // focuses only on exported variables
        Set<DataDeclaration> uninitialized = new HashSet<DataDeclaration>();
        uninitialized.addAll(atom.getExportedDataDeclarations());

        // initialize the analysis
        checkUninitializedVariables(graph.getInitialActions(), uninitialized,
                null);

        // acyclic => all analysis using the marking equation are sound and complete
        if (graph.isAcyclic()) {
            if (graph.isDeterministic()) {
                // in this case an execution path involve all transitions
                for (Transition t : graph.getTransitions()) {
                    checkUninitializedVariables(t.getActions(), uninitialized,
                            null);
                }
            } else {
                // in this case an execution path involve at least one of the transitions
                Set<DataDeclaration> remaining = new HashSet<DataDeclaration>();

                for (Transition t : graph.getTransitions()) {
                    Set<DataDeclaration> copyOfuninitialized = new HashSet<DataDeclaration>(
                            uninitialized);
                    checkUninitializedVariables(t.getActions(),
                            copyOfuninitialized, null);

                    remaining.addAll(copyOfuninitialized);
                }

                // set unitialized variables
                uninitialized = remaining;
            }
        }

        return new BasicEList<DataDeclaration>(uninitialized);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public EList<DataDeclaration> getUninitializedExportedVariables(
            Transition transition) {
        EList<DataDeclaration> ret = new BasicEList<DataDeclaration>();

        assert (this.eContainer() instanceof AtomType);
        AtomType atom = (AtomType) this.eContainer();

        // analysis of uninitialized variables
        PetriNetGraph graph = new PetriNetGraph(this);
        UninitializedAnalyzer analyzer = new UninitializedAnalyzer(graph,
                getAllDataDeclarationsWithoutValue(atom));

        if (transition.getTriggerPort() != null) {
            Set<DataDeclaration> uninitializedVariables = new HashSet<DataDeclaration>();

            // check all variables exported by the port of transition t
            for (DataDeclarationReferenceDataParameter p : transition
                    .getTriggerPort().getDataParameters()) {
                uninitializedVariables.add(p.getDataDeclarationReference());
            }

            // faulty variables = the ones uninitialized before the execution of t
            uninitializedVariables
                    .retainAll(analyzer.getUninitializedBefore(transition));

            ret.addAll(uninitializedVariables);
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
        case BehaviorPackage.PETRI_NET__STATES:
            return ((InternalEList<?>) getStates()).basicRemove(otherEnd, msgs);
        case BehaviorPackage.PETRI_NET__TRANSITIONS:
            return ((InternalEList<?>) getTransitions()).basicRemove(otherEnd,
                    msgs);
        case BehaviorPackage.PETRI_NET__INITIAL_ACTIONS:
            return ((InternalEList<?>) getInitialActions())
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
        case BehaviorPackage.PETRI_NET__STATES:
            return getStates();
        case BehaviorPackage.PETRI_NET__INIT_STATES:
            return getInitStates();
        case BehaviorPackage.PETRI_NET__TRANSITIONS:
            return getTransitions();
        case BehaviorPackage.PETRI_NET__INITIAL_ACTIONS:
            return getInitialActions();
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
        case BehaviorPackage.PETRI_NET__STATES:
            getStates().clear();
            getStates().addAll((Collection<? extends State>) newValue);
            return;
        case BehaviorPackage.PETRI_NET__INIT_STATES:
            getInitStates().clear();
            getInitStates().addAll((Collection<? extends State>) newValue);
            return;
        case BehaviorPackage.PETRI_NET__TRANSITIONS:
            getTransitions().clear();
            getTransitions()
                    .addAll((Collection<? extends Transition>) newValue);
            return;
        case BehaviorPackage.PETRI_NET__INITIAL_ACTIONS:
            getInitialActions().clear();
            getInitialActions()
                    .addAll((Collection<? extends Expression>) newValue);
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
        case BehaviorPackage.PETRI_NET__STATES:
            getStates().clear();
            return;
        case BehaviorPackage.PETRI_NET__INIT_STATES:
            getInitStates().clear();
            return;
        case BehaviorPackage.PETRI_NET__TRANSITIONS:
            getTransitions().clear();
            return;
        case BehaviorPackage.PETRI_NET__INITIAL_ACTIONS:
            getInitialActions().clear();
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
        case BehaviorPackage.PETRI_NET__STATES:
            return states != null && !states.isEmpty();
        case BehaviorPackage.PETRI_NET__INIT_STATES:
            return initStates != null && !initStates.isEmpty();
        case BehaviorPackage.PETRI_NET__TRANSITIONS:
            return transitions != null && !transitions.isEmpty();
        case BehaviorPackage.PETRI_NET__INITIAL_ACTIONS:
            return initialActions != null && !initialActions.isEmpty();
        }
        return super.eIsSet(featureID);
    }

} //PetriNetImpl
