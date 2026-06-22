/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
 *  Anakreontas Mentis
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

tree grammar Bip2Walker;

options {
    tokenVocab=Bip2;
    ASTLabelType=CommonTree;
    backtrack=true;
    memoize=true;
    output=AST;
}

// Used for representing the current scope of a BIP program.
// kind record the kind of scope
// object is the EMF object to which the scope should be associated
// symbols is the symbol table for this scope.
scope BipScope {
    BipScopeKind kind;
    AnnotatedEObject object;
    SymbolTable symbols;
}

// Used for storing the set of objects that should be annotated by a given
// set of annotations.
// This is usefull in presence of multiple declarations having a comme
// set of annotations (e.g. declaration of ports, variables, components
// instances, connectors instances).
scope AnnotatedScope{
    List<AnnotatedElement> elements;
}

@header {
package ujf.verimag.bip.parser;
import java.net.URL;
import java.util.Set;
import java.util.Collection;
import java.util.HashSet;
import java.util.Map;
import java.util.EnumMap;
import ujf.verimag.bip.parser.loader.PackageLoader;
import ujf.verimag.bip.parser.loader.LoadPackageException;
import ujf.verimag.bip.parser.error.AmbiguousSymbolException;
import ujf.verimag.bip.parser.error.AmbiguousTypeException;
import ujf.verimag.bip.parser.error.AmbiguousVariableException;
import ujf.verimag.bip.parser.error.Bip2WalkerException;
import ujf.verimag.bip.parser.error.IncorrectParametersException;
import ujf.verimag.bip.parser.error.IncorrectBipTypeException;
import ujf.verimag.bip.parser.error.IncorrectNumberFormatException;
import ujf.verimag.bip.parser.error.OperationInvalidOrNotSupportedException;
import ujf.verimag.bip.parser.error.RedefinedTypeException;
import ujf.verimag.bip.parser.error.GenericWalkerErrorException;
import ujf.verimag.bip.parser.error.RedefinedSymbolException;
import ujf.verimag.bip.parser.error.RedefinedVariableException;
import ujf.verimag.bip.parser.error.RedefinedAnnotationException;
import ujf.verimag.bip.parser.error.RedefinedAnnotationParameterException;
import ujf.verimag.bip.parser.error.UndefinedSymbolException;
import ujf.verimag.bip.parser.error.UndefinedTypeException;
import ujf.verimag.bip.parser.error.UndefinedStateException;
import ujf.verimag.bip.parser.error.UndefinedVariableException;
import ujf.verimag.bip.parser.error.ParserOrLexerError;
import ujf.verimag.bip.error.message.ErrorCodeEnum;
import ujf.verimag.bip.metamodel.AnnotatedEObject;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

import org.eclipse.emf.ecore.util.EcoreUtil;
import org.eclipse.emf.ecore.EObject;
/*
 * metamodel classes
 */
import bip2.ujf.verimag.bip.types.Type;
import bip2.ujf.verimag.bip.types.AtomType;
import bip2.ujf.verimag.bip.types.CompoundType;
import bip2.ujf.verimag.bip.types.ComponentType;
import bip2.ujf.verimag.bip.types.BipType;

import bip2.ujf.verimag.bip.types.ConnectorType;
import bip2.ujf.verimag.bip.types.PortType;
import bip2.ujf.verimag.bip.connector.ConnectorDataDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionPortReference;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionDefinition;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionNestedDefinition;

import bip2.ujf.verimag.bip.behavior.Transition;
import bip2.ujf.verimag.bip.behavior.PetriNet;
import bip2.ujf.verimag.bip.behavior.State;
import bip2.ujf.verimag.bip.component.atom.AtomInternalExternalPortDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomInternalPortDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomExternalPortDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomExportPortDeclaration;
import bip2.ujf.verimag.bip.component.atom.EventConsumptionPolicy;
import bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration;
import bip2.ujf.verimag.bip.behavior.BehaviorFactory;
import bip2.ujf.verimag.bip.component.atom.AtomFactory;
import bip2.ujf.verimag.bip.component.compound.CompoundFactory;
import bip2.ujf.verimag.bip.component.compound.CompoundExportPortDeclaration;
import bip2.ujf.verimag.bip.component.compound.CompoundExportDataDeclaration;
import bip2.ujf.verimag.bip.component.ComponentDataParameterDeclaration;
import bip2.ujf.verimag.bip.component.ComponentDeclaration;
import bip2.ujf.verimag.bip.component.ComponentFactory;
import bip2.ujf.verimag.bip.connector.ConnectorFactory;
import bip2.ujf.verimag.bip.connector.ConnectorDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionDefinition;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionPortReference;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionNestedDefinition;
import bip2.ujf.verimag.bip.priority.PriorityFactory;
import bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration;
import bip2.ujf.verimag.bip.priority.ConnectorInteraction;
import bip2.ujf.verimag.bip.invariant.InvariantFactory;
import bip2.ujf.verimag.bip.invariant.AtomInvariant;

import bip2.ujf.verimag.bip.annotation.AnnotationFactory;
import bip2.ujf.verimag.bip.annotation.AnnotatedElement;
import bip2.ujf.verimag.bip.annotation.BipAnnotation;

import bip2.ujf.verimag.bip.port.PortFactory;
import bip2.ujf.verimag.bip.port.PortDeclaration;
import bip2.ujf.verimag.bip.port.PortDataParameterDeclaration;
import bip2.ujf.verimag.bip.port.PortDeclarationReferenceParameter;

import bip2.ujf.verimag.bip.port.SubPortDeclarationReference;
import bip2.ujf.verimag.bip.types.TypesFactory;
import bip2.ujf.verimag.bip.packaging.BipPackage;
import bip2.ujf.verimag.bip.packaging.PackagingFactory;
import bip2.ujf.verimag.bip.packaging.ConstDataDeclaration;
import bip2.ujf.verimag.bip.packaging.Prototype;
import bip2.ujf.verimag.bip.packaging.PrototypeParameterDeclaration;
import bip2.ujf.verimag.bip.packaging.FunctionCallPrototype;
import bip2.ujf.verimag.bip.packaging.UnaryOpPrototype;
import bip2.ujf.verimag.bip.packaging.BinaryOpPrototype;
import bip2.ujf.verimag.bip.types.ConnectorType;

import bip2.ujf.verimag.bip.connector.ConnectorPortParameterDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorFactory;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionAction;

import bip2.ujf.verimag.bip.connector.ConnectorExportedPortDeclaration;
import bip2.ujf.verimag.bip.data.DataDeclarationReferenceDataParameter;


import bip2.ujf.verimag.bip.data.DataFactory;
import bip2.ujf.verimag.bip.data.DataType;
import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.SubDataDeclarationReference;
import bip2.ujf.verimag.bip.component.atom.AtomInternalDataDeclaration;

import bip2.ujf.verimag.bip.actionlang.ValuedExpression;
import bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.IfThenElseExpression;
import bip2.ujf.verimag.bip.actionlang.ActionlangFactory;
import bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.BinaryOperators;
import bip2.ujf.verimag.bip.actionlang.UnaryOperators;
import bip2.ujf.verimag.bip.actionlang.BinaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.UnaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.Expression;
import bip2.ujf.verimag.bip.actionlang.AssignmentExpression;
import bip2.ujf.verimag.bip.actionlang.FunctionCallExpression;
import bip2.ujf.verimag.bip.actionlang.DirectBooleanExpression;
import bip2.ujf.verimag.bip.actionlang.DirectIntegerExpression;
import bip2.ujf.verimag.bip.actionlang.DirectFloatExpression;
import bip2.ujf.verimag.bip.actionlang.DirectStringExpression;

import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.emf.ecore.xmi.impl.XMIResourceFactoryImpl;
import org.eclipse.emf.ecore.xmi.impl.XMLResourceFactoryImpl;

/*
 * end of metamodel classes
 */
}


@members {
    /** 
     * Used for representing all symbols of a scope, and
     * maps these symbols to EMF objects.
     * Each namespace of NameSpace has its own symbol table.
     * Symbols could be overloaded in a given namespace, i.e.
     * each symbol may be associated to 0, 1, or more objects.
     */
    public class SymbolTable {
      /**
       * Create a new symbol table containing empty maps (non null) for
       * all namespaces.
       */
      SymbolTable() {
        table = new EnumMap<NameSpace, Map<String, List<AnnotatedEObject>>>(NameSpace.class);

        for (NameSpace namespace : NameSpace.values()) {
          table.put(namespace, new HashMap<String, List<AnnotatedEObject>>());
        }
      }

      /**
       * Put a symbol in a namespace without associating any object.
       * Create automatically a map for the given namespace if it has
       * no table.
       * Create automatically an empty list of objects if the symbol is not
       * already in the table.
       * @param symbol the symbol to put in the table
       * @param namespace the namespace in which the symbol should be put
       */
      private void put(String symbol, NameSpace namespace) {
        if (table.get(namespace) == null) {
          table.put(namespace, new HashMap<String, List<AnnotatedEObject>>());
        }

        if (table.get(namespace).get(symbol) == null) {
          List<AnnotatedEObject> emptyList = new ArrayList<AnnotatedEObject>();
          table.get(namespace).put(symbol, emptyList);
        }
      }

      /**
       * Associate a new object to a given symbol in a given namespace.
       * As put(String symbol, NameSpace namespace), automatically create list
       * and maps if required.
       * @param symbol the target symbol that can be already in the table
       * @param namespace the target namespace
       * @param object the target object
       */
      public void put(String symbol, NameSpace namespace, AnnotatedEObject object) {
        put(symbol, namespace);
        table.get(namespace).get(symbol).add(object);
      }

      /**
       * Associate a new objects to a given symbol in a given namespace.
       * As put(String symbol, NameSpace namespace), automatically create list
       * and maps if required.
       * @param symbol the target symbol that can be already in the table
       * @param namespace the target namespace
       * @param object the target object
       */
      public void put(String symbol, NameSpace namespace, List<AnnotatedEObject> objects) {
        put(symbol, namespace);
        table.get(namespace).get(symbol).addAll(objects);
      }

      /**
       * Merge an existing table.
       * @param table the table to be merged
       */
      public void put(SymbolTable tableToPut) {
        for (Map.Entry<NameSpace, Map<String, List<AnnotatedEObject>>> namespaceentry : tableToPut.table.entrySet()) {
          for (Map.Entry<String, List<AnnotatedEObject>> entry : namespaceentry.getValue().entrySet()) {
            put(entry.getKey(), namespaceentry.getKey(), entry.getValue());
          }
        }
      }

      /**
       * Returns the map from symbol to objects for a given namespace.
       * /!\ Could be null
       * @param namespace the target namespace
       */
      private Map<String, List<AnnotatedEObject>> get(NameSpace namespace) { return table.get(namespace); }

      /**
       * Retrieve the objects (if exists) mapped to a symbol in a namespace.
       * @param symbol the target symbol
       * @param namespace the target namespace
       * @return the list of objects mapped to symbol in namespace
       * /!\ could be null if the symbol is not in the table
       */
      public List<AnnotatedEObject> get(String symbol, NameSpace namespace) {
        List<AnnotatedEObject> ret = null;

        if (table.get(namespace) != null) {
          ret = table.get(namespace).get(symbol);
        }

        return ret;
      }

      /**
       * The map used to record mapping of symbols to objects in different
       * namespaces.
       */
      private Map<NameSpace, Map<String, List<AnnotatedEObject>>> table;
    }
    
    
    private enum BipScopeKind {
        MAIN_COMPONENT_DECLARATION,
        GLOBAL,
        PACKAGE,
        COMPOUND_DEFINITION,
        ATOM_DEFINITION,
        CONNECTOR_DEFINITION,
        PORT_DEFINITION
    };

    public static final String srcLocationAnnotationName = "source-location";
    
    private static final BinaryOperators[] comparison_operators = {
        BinaryOperators.EQUAL,
        BinaryOperators.NOT_EQUAL,
        BinaryOperators.GREATER_THAN,
        BinaryOperators.GREATER_THAN_OR_EQUAL,
        BinaryOperators.LESS_THAN,
        BinaryOperators.LESS_THAN_OR_EQUAL
    };
    
    private static final BinaryOperators[] arithmetic_binary_operators = {
        BinaryOperators.ADDITION,
        BinaryOperators.SUBTRACTION,
        BinaryOperators.MULTIPLICATION,
        BinaryOperators.DIVISION,
        BinaryOperators.MODULO
    };
    
    private static final UnaryOperators[] arithmetic_unary_operators = {
        UnaryOperators.PLUS,
        UnaryOperators.MINUS
    };
    
    private static final BinaryOperators[] bwise_binary_operators = {
        BinaryOperators.BWISE_AND,
        BinaryOperators.BWISE_XOR,
        BinaryOperators.BWISE_OR
    };
    
    private static final UnaryOperators[] bwise_unary_operators = {
        UnaryOperators.BWISE_NOT
    };
    
    private static final BinaryOperators[] logical_binary_operators = {
        BinaryOperators.LOGICAL_OR,
        BinaryOperators.LOGICAL_AND
    };
    
    private static final UnaryOperators[] logical_unary_operators = {
        UnaryOperators.LOGICAL_NOT
    };

    protected PackageLoader loader;
    protected URL parsedFileURL;
    protected StringBuffer parsedStringBuffer;

    private void setSourceInfo(AnnotatedEObject eobject, CommonTree tree){
      setSourceInfo(eobject, tree.getLine(), -1, tree.getCharPositionInLine(), -1);
    }
    
    private void setSourceInfo(AnnotatedEObject eobject, int linestart,
                               int linestop, int colstart, int colstop){   
		if (this.parsedFileURL != null) {
          eobject.setSourceURL(this.parsedFileURL);
          eobject.setLocationInfo(linestart, linestop, colstart, colstop);
        }
        
        if (this.parsedStringBuffer != null) {
          eobject.setSourceStringBuffer(this.parsedStringBuffer);
          eobject.setLocationInfo(linestart, linestop, colstart, colstop);
        }
    }

    /*
     *
     */
  public void setLoader(PackageLoader loader) {
      this.loader = loader;
  }

  public void setParsedFileURL(URL fileurl){
    this.parsedFileURL = fileurl;
  }

  public void setParsedStringBuffer(StringBuffer parsedStringBuffer){
    this.parsedStringBuffer = parsedStringBuffer;
  }

  public void setGlobalSymbolMap(Map<AnnotatedEObject, SymbolTable> globalSymbolMap) {
    this.globalSymbolMap = globalSymbolMap;
  }

  public List<ParserOrLexerError> errors = new ArrayList<ParserOrLexerError>();

  public void reportError(Bip2WalkerException re) {
    if (! state.errorRecovery ) {
        registerError(re);
        state.syntaxErrors++; // don't count spurious
        state.errorRecovery = true;
    }
  }

  protected void registerError(Bip2WalkerException re) {
    ParserOrLexerError new_error = new ParserOrLexerError(re);
    this.errors.add(new_error);
  }
    /*
     * Root EMF object : the package.
     */
     public BipPackage parsed_package;

    /*
     * Global maps for storing symbols exported by objects
     */
     protected Map<AnnotatedEObject, SymbolTable> globalSymbolMap;

    /*
     * Paraphrase system directly from ANTLR documentation
     * Allows for better error message (in particular, context)
     */
    Stack<String> paraphrases = new Stack<String>();

    public String getParaPhrases(){
        StringBuffer parabuf = new StringBuffer();

        if (paraphrases.size() > 0) {
            String paraphrase = paraphrases.peek();
            parabuf.append(" " + paraphrase);
        }
        return parabuf.toString();
    }

    /*
     * Override this method to handle our custom Exception class
     * + for the handling of the paraphrases
     */
    @Override
    public String getErrorMessage(RecognitionException e, String[] tokenNames) {
        String msg;

        if ( e instanceof Bip2WalkerException ) {
            Bip2WalkerException bwe = (Bip2WalkerException)e;
            String tokenName="<unknown>";
            msg = bwe.getMessage();
        } else {
            msg = super.getErrorMessage(e, tokenNames);
        }
        return msg + getParaPhrases();
    }

    /*
     * Possible namespaces for symbols:
     * TYPE: symbols representing names of types (data types, port types, connector
     * types, component types)
     * NAME: symbols representing names of instances/variables/function
     * EXPORTED_TYPE / EXPORTED_NAME: exported symbols, i.e. accessible outside from
     * the scope
     * /!\ Exported symbols are not necessarely contained in normal namespaces:
     *   e.g. export port Port p(), q() as exp_()
     */
    protected enum NameSpace {
        TYPE,
        NAME,
        EXPORTED_TYPE,
        EXPORTED_NAME
    }
    
    /*
     * Initialize a scope for annotations.
     */
    public void initAnnotatedScope() {
      $AnnotatedScope::elements = new ArrayList<AnnotatedElement>();
    }

    /*
     * Initialize a scope for annotations with an element to annotated.
     * @param element the element to be annotated
     */
    public void initAnnotatedScope(AnnotatedElement element) {
      initAnnotatedScope();
      addElementToAnnotate(element);
    }

    /*
     * Add an element to annoated in the scope.
     * @param element the element to be annotated
     */
    public void addElementToAnnotate(AnnotatedElement element) {
      $AnnotatedScope::elements.add(element);
    }
    
    /**
     * Initialize the current bip scope.
     * @param kind the kind of scope
     * @param object the object to which the scope should be associated
     */
    public void initScope(BipScopeKind kind, AnnotatedEObject object){
      int s = $BipScope.size() - 1;

      $BipScope[s]::kind = kind;
      $BipScope[s]::object = object;
      $BipScope[s]::symbols = new SymbolTable();

      // associate the scope to object
      this.globalSymbolMap.put(object, $BipScope[s]::symbols);
    }

    /**
     * Initialize the current bip scope.
     * @param kind the kind of scope
     */
    public void initScope(BipScopeKind kind){
      int s = $BipScope.size() - 1;

      $BipScope[s]::kind = kind;
      $BipScope[s]::object = null;
      $BipScope[s]::symbols = new SymbolTable();
    }
    
    /**
     * Initialize the current bip scope.
     * @param kind the kind of scope
     */
    public void initScope(BipScopeKind kind, SymbolTable table){
      int s = $BipScope.size() - 1;

      $BipScope[s]::kind = kind;
      $BipScope[s]::object = null;
      $BipScope[s]::symbols = table;
    }
    
    /**
     * Determine whether an object may overload another one for
     * a given symbol.
     * @param symbol the target symbol
     * @param namespace the target namespace
     * @param overloader the object that wants to overload
     * @param overloaded the object that may be overloaded
     * @return true if overloader can overload overloaded
     */
    public boolean canOverload(String symbol, NameSpace namespace,
        AnnotatedEObject overloader, AnnotatedEObject overloaded) {
      boolean areBothFunctionPrototypes = (overloaded instanceof FunctionCallPrototype &&
          overloader instanceof FunctionCallPrototype);
          
      EObject overloaderHolder = overloader.eContainer();
      EObject overloadedHolder = overloaded.eContainer();
          
      boolean areFromDifferentPackages =
             overloaderHolder instanceof BipPackage &&
             overloadedHolder instanceof BipPackage &&
             overloaderHolder != overloadedHolder;
      
      return areBothFunctionPrototypes || areFromDifferentPackages;
    }

    private AmbiguousSymbolException createAmbiguousSymbolException(
        String symbol, NameSpace namespace, List<AnnotatedEObject> objects,
        TreeNodeStream input, CommonTree start) {
      AmbiguousSymbolException ret = null;

      switch (namespace) {
      case TYPE:
      case EXPORTED_TYPE:
        ret = new AmbiguousTypeException(input, start, objects, symbol);
        break;
      case NAME:
      case EXPORTED_NAME:
        ret = new AmbiguousVariableException(input, start, objects, symbol);
        break;
      default:
        assert(false);
      }

      return ret;
    }

    private UndefinedSymbolException createUndefinedSymbolException(
        String symbol, NameSpace namespace,
        TreeNodeStream input, CommonTree start) {
      UndefinedSymbolException ret = null;

      switch (namespace) {
      case TYPE:
      case EXPORTED_TYPE:
        ret = new UndefinedTypeException(input, start, symbol);
        break;
      case NAME:
      case EXPORTED_NAME:
        ret = new UndefinedVariableException(input, start, symbol);
        break;
      default:
        assert(false);
      }

      return ret;
    }

    private RedefinedSymbolException createRedefinedSymbolException(
        String symbol, NameSpace namespace, AnnotatedEObject object,
        TreeNodeStream input, CommonTree start) {
      RedefinedSymbolException ret = null;

      switch (namespace) {
      case TYPE:
      case EXPORTED_TYPE:
        ret = new RedefinedTypeException(input, start, object, symbol);
        break;
      case NAME:
      case EXPORTED_NAME:
        ret = new RedefinedVariableException(input, start, object, symbol);
        break;
      default:
        assert(false);
      }

      return ret;
    }

    private IncorrectBipTypeException createIncorrectBipTypeException(
        String symbol, NameSpace namespace, Class expected,
        TreeNodeStream input, CommonTree start) {
      IncorrectBipTypeException ret = null;

      if (expected == BipPackage.class) {
        ret = new IncorrectBipTypeException(input, start, symbol, "bip package");
      }
      else if (expected == DataType.class) {
        ret = new IncorrectBipTypeException(input, start, symbol, "data type");
      }
      else if (expected == PortType.class) {
        ret = new IncorrectBipTypeException(input, start, symbol, "port type");
      }
      else if (expected == ConnectorType.class) {
        ret = new IncorrectBipTypeException(input, start, symbol, "connector type");
      }
      else if (expected == ComponentType.class) {
        ret = new IncorrectBipTypeException(input, start, symbol, "component type");
      }
      else if (expected == ConnectorDeclaration.class) {
        ret = new IncorrectBipTypeException(input, start, symbol, "connector");
      }
      else if (expected == AtomInternalDataDeclaration.class) {
        ret = new IncorrectBipTypeException(input, start, symbol, "atom variable");
      }
      else if (expected == ConnectorDataDeclaration.class) {
        ret = new IncorrectBipTypeException(input, start, symbol, "connector variable");
      }
      else if (expected == ConnectorPortParameterDeclaration.class) {
        ret = new IncorrectBipTypeException(input, start, symbol, "port");
      }
      else if (expected == PortDeclaration.class) {
        ret = new IncorrectBipTypeException(input, start, symbol, "port");
      }
      else if (expected == SubPortDeclarationReference.class) {
        ret = new IncorrectBipTypeException(input, start, symbol, "port");
      }
      else if (expected == SubDataDeclarationReference.class) {
        ret = new IncorrectBipTypeException(input, start, symbol, "variable");
      }
      else if (expected == AtomInternalPortDeclaration.class) {
        ret = new IncorrectBipTypeException(input, start, symbol, "port");
      }
      else if (expected == AtomExternalPortDeclaration.class) {
        ret = new IncorrectBipTypeException(input, start, symbol, "port");
      }
      else if (expected == AtomInternalExternalPortDeclaration.class) {
        ret = new IncorrectBipTypeException(input, start, symbol, "port");
      }
      else if (expected == DataDeclaration.class) {
        ret = new IncorrectBipTypeException(input, start, symbol, "variable");
      }
      else if (expected == State.class) {
      	ret = new IncorrectBipTypeException(input, start, symbol, "place");
      }
      else {
        assert(false);
        ret = new IncorrectBipTypeException(input, start, symbol, "?");
      }

      return ret;
    }

    /**
     * Put a symbol in a specific symbol table
     */
    public void putSymbol(SymbolTable table, String symbol, NameSpace namespace, AnnotatedEObject object,
        TreeNodeStream input, CommonTree start)
        throws RedefinedSymbolException {     
      List<AnnotatedEObject> objects = table.get(symbol, namespace);
        
      if (objects != null) {
        if (!objects.isEmpty()) {
          boolean overload = true;
        
          for (AnnotatedEObject obj : objects) {
            if (!canOverload(symbol, namespace, object, obj)) {
              overload = false;
            }
          }
        
          if (!overload) {
            // FIXME: handle the case size() > 1
            assert(objects.size() == 1);

            throw createRedefinedSymbolException(symbol, namespace, objects.get(0), input, start);
          }
        }
      }
      
      table.put(symbol, namespace, object);
    }

    /**
     * Put a symbol in a specific symbol table
     */
    public void putSymbol(SymbolTable table, String symbol, NameSpace namespace, List<AnnotatedEObject> objects,
        TreeNodeStream input, CommonTree start)
        throws RedefinedSymbolException {     
      List<AnnotatedEObject> existingObjects = table.get(symbol, namespace);
        
      if (existingObjects != null) {
        if (!existingObjects.isEmpty()) {
          boolean overload = true;
        
          for (AnnotatedEObject extObj : existingObjects) {
            for (AnnotatedEObject obj : objects) {
              if (!canOverload(symbol, namespace, obj, extObj)) {
                overload = false;
              }
            }
          }
        
          if (!overload) {
            // FIXME: handle the case size() > 1
            assert(objects.size() == 1);

            throw createRedefinedSymbolException(symbol, namespace, objects.get(0), input, start);
          }
        }
      }
      
      table.put(symbol, namespace, objects);
    }
    
    /**
     * Put a symbol in the current scope
     */
    public void putSymbol(String symbol, NameSpace namespace, AnnotatedEObject object,
        TreeNodeStream input, CommonTree start)
        throws RedefinedSymbolException {
      int s = $BipScope.size() - 1;
      putSymbol($BipScope[s]::symbols, symbol, namespace, object, input, start);
    }

    /**
     * Put a symbol in the current scope
     */
    public void putSymbol(String symbol, NameSpace namespace, List<AnnotatedEObject> objects,
        TreeNodeStream input, CommonTree start)
        throws RedefinedSymbolException {
      int s = $BipScope.size() - 1;
      putSymbol($BipScope[s]::symbols, symbol, namespace, objects, input, start);
    }

    /**
     * Retrieve an object from a specific symbol table
     */
    public AnnotatedEObject getObject(SymbolTable table, String symbol, NameSpace namespace,
        TreeNodeStream input, CommonTree start)
        throws AmbiguousSymbolException, UndefinedSymbolException {
      AnnotatedEObject ret = null;

      if (table != null) {
        List<AnnotatedEObject> objects = table.get(symbol, namespace);
        
        if (objects != null) {
          if (objects.size() > 1) {
            throw createAmbiguousSymbolException(symbol, namespace, objects, input, start);
          }
        
          if (objects.size() == 1) {
            ret = objects.get(0);
          }
        }
      }
      
      if (ret == null) {
        throw createUndefinedSymbolException(symbol, namespace, input, start);
      }
      
      return ret;
    }

    /**
     * Retrieve an object using scoping.
     */
    public AnnotatedEObject getObject(String symbol, NameSpace namespace,
        TreeNodeStream input, CommonTree start) throws Bip2WalkerException {
      AnnotatedEObject ret = null;

      for (int s = $BipScope.size() - 1 ; s >= 0 ; s--) {
        try {
          ret = getObject($BipScope[s]::symbols, symbol, namespace, input, start);
          break;
        }
        catch (Bip2WalkerException exception) {
          if (s == 0) throw exception;
        }
      }

      return ret;
    }

    public void typeCheck(String symbol, NameSpace namespace,
        AnnotatedEObject object, Class expectedType,
        TreeNodeStream input, CommonTree start) throws IncorrectBipTypeException {
      if (!expectedType.isInstance(object)) {
        throw createIncorrectBipTypeException(symbol, namespace, expectedType, input, start);
      }
    }

    /**
     * Put all symbols of exported namespace of table in the current scope.
     */
    public void putAllExportedSymbols(String holderName, SymbolTable table, boolean directAccess,
        TreeNodeStream input, CommonTree start) throws RedefinedSymbolException {
      for (Map.Entry<String, List<AnnotatedEObject>> entry : table.get(NameSpace.EXPORTED_NAME).entrySet()) {
        if (directAccess) {
          putSymbol(entry.getKey(), NameSpace.NAME, entry.getValue(), input, start);         
        }

        putSymbol(holderName + "." + entry.getKey(), NameSpace.NAME, entry.getValue(), input, start);
      }

      for (Map.Entry<String, List<AnnotatedEObject>> entry : table.get(NameSpace.EXPORTED_TYPE).entrySet()) {
        if (directAccess) {
          putSymbol(entry.getKey(), NameSpace.TYPE, entry.getValue(), input, start);
        }

        putSymbol(holderName + "." + entry.getKey(), NameSpace.TYPE, entry.getValue(), input, start);
      }
    }

    /**
     * Put reference in the current scope (i.e. of the form 'decl1.decl2').
     * This is useful for accessing inner declarations of instances of port,
     * connector, component.
     */
    public void putFieldAccessSymbol(String holderName, AnnotatedEObject holder,
        String objectName, AnnotatedEObject object,
        TreeNodeStream input, CommonTree start) throws RedefinedSymbolException {
      AnnotatedEObject reference = null;
      
      if (object instanceof DataDeclaration) {
        SubDataDeclarationReference subref = DataFactory.eINSTANCE.createSubDataDeclarationReference();
        subref.setForwardDataDeclaration((DataDeclaration) object);

        if (holder instanceof ComponentDeclaration) {
          subref.setComponentDeclaration((ComponentDeclaration) holder);
        }
        else if (holder instanceof PortDeclaration) {
          subref.setPortDeclaration((PortDeclaration) holder);
        }
        else {
          // FIXME: generate an internal error here: unsupported export operation!!!
          assert(false);
        }

        reference = subref;
      }
      else if (object instanceof PortDeclaration) {
        SubPortDeclarationReference subref = PortFactory.eINSTANCE.createSubPortDeclarationReference();
        subref.setForwardPortDeclaration((PortDeclaration) object);

        if (holder instanceof ComponentDeclaration) {
          subref.setComponentDeclaration((ComponentDeclaration) holder);
        }
        else if (holder instanceof ConnectorDeclaration) {
          subref.setConnectorDeclaration((ConnectorDeclaration) holder);
        }
        else {
          // FIXME: generate an internal error here: unsupported export operation!!!
          assert(false);
        }

        reference = subref;
      }
      else {
        // FIXME: generate an internal error here: unsupported export operation!!!
        assert(false);
      }

      putSymbol(holderName + "." + objectName, NameSpace.NAME, reference, input, start);
    }

    /**
     * Put all field access symbols in the current scope.
     */
    public void putAllFieldAccessSymbols(String name, AnnotatedEObject holder, SymbolTable table,
        TreeNodeStream input, CommonTree start) throws RedefinedSymbolException {
      for (Map.Entry<String, List<AnnotatedEObject>> entry : table.get(NameSpace.EXPORTED_NAME).entrySet()) {
        for (AnnotatedEObject object : entry.getValue()) {
          putFieldAccessSymbol(name, holder, entry.getKey(), object, input, start);
        }
      }
    }

    /** Locates a port declaration based on its name. */
    private ConnectorPortParameterDeclaration getPortDeclaration(
        Collection<ConnectorPortParameterDeclaration> declarations,
        String name) {
        for (ConnectorPortParameterDeclaration p : declarations) {
            if (name.equals(p.getName())) {
                return p;
            }
        }
        return null;
    }        
}

@rulecatch{
  catch (Bip2WalkerException walkerException){
      reportError(walkerException);
      //recover(input, walkerException);
      throw walkerException;
  }

  catch (RecognitionException recogException){
    reportError(recogException);
    //recover(input, recogException);
    // error in produced AST, internal error.
    throw recogException;
  }
}

fully_qualified_name returns [String fullname, List<String> names]
@init {
    $fullname = "";
    $names = new ArrayList<String>(); 
}
@after {
    for (int i = 0 ; i < $names.size() ; i++) {
      if (i > 0) $fullname += ".";
      $fullname += $names.get(i);
    }
}
    : ^(FULLY_QUALIFIED_NAME
        (ID { $names.add($ID.text); } )+)
    ;

fully_qualified_reference [NameSpace namespace, Class expected] returns [String fullname, AnnotatedEObject object]
    : fully_qualified_name {
        $fullname = $fully_qualified_name.fullname;
        $object = getObject($fully_qualified_name.fullname, namespace, input, $start);
        typeCheck($fully_qualified_name.fullname, namespace, $object, expected, input, $start);
      }
    ;

simple_name returns [String name]
    : ID { $name = $ID.text; }
    ;

simple_reference [NameSpace namespace, Class expected] returns [String name, AnnotatedEObject object]
    : simple_name {
        $name = $simple_name.name;
        $object = getObject($name, namespace, input, $start);
        typeCheck($name, namespace, $object, expected, input, $start);
      }
    ;
    
data_type_reference returns [ DataType datatype ]
@init {
  $datatype = null;
}
    : fully_qualified_reference [ NameSpace.TYPE, DataType.class ] { $datatype = (DataType) $fully_qualified_reference.object; }
    | native_data_type_reference { $datatype = $native_data_type_reference.datatype; }
    ;
    
data_type returns [ DataType datatype, boolean isconst ]
@init {
  $datatype = null;
  $isconst = false;
}
    : ^(DATA_TYPE
          data_type_reference { $datatype = $data_type_reference.datatype; }
          (CONST { $isconst = true; })?)
    ;

use_package_declaration
    : ^(USE (fully_qualified_name {
           BipPackage bp = null;
           try {
              bp = this.loader.getPackage($fully_qualified_name.fullname, true);
              parsed_package.getUsed_packages().add(bp);
            } catch (LoadPackageException e) {
              throw new ujf.verimag.bip.parser.error.LoadPackageException(input, $start, e);
            }

            putAllExportedSymbols(bp.getName(), this.globalSymbolMap.get(bp), true, input, $start);
         }
      )+)
    ;

bip_package
scope {
  BipPackage parsed_package;
}
scope AnnotatedScope, BipScope;
@init {
    initScope(BipScopeKind.GLOBAL);
    $bip_package::parsed_package = PackagingFactory.eINSTANCE.createBipPackage();
    parsed_package = $bip_package::parsed_package;
    setSourceInfo($bip_package::parsed_package, $start);
    initAnnotatedScope($bip_package::parsed_package);
}
    : ^(BIP_PACKAGE
           fully_qualified_name {
             $bip_package::parsed_package.setName($fully_qualified_name.fullname);
           }
           use_package_declaration?
           package_body
           annotations?)
    ;
    
package_body
scope BipScope;
@init {
    initScope(BipScopeKind.PACKAGE, $bip_package::parsed_package);
}
    : annotated_declaration*
    ;

annotated_declaration
    : annotated_multi_data_declaration
    | annotated_extern_data_type_declaration
    | annotated_extern_prototype_declaration
    | annotated_bip_type_definition
    ;

// If this rule has to be used from a different context than
// Component Type def, then, use scope and if/elses.
component_data_params returns [List<ComponentDataParameterDeclaration> dataparams]
@init{
  $dataparams = new ArrayList<ComponentDataParameterDeclaration>();
}
    :   ^(DATA_PARAMS
            (^(DATA_PARAM data_type
                          simple_name
               {
                DataType dt = (DataType) $data_type.datatype;

                ComponentDataParameterDeclaration cdpd = ComponentFactory.eINSTANCE.createComponentDataParameterDeclaration();

                setSourceInfo(cdpd, $data_type.start);
                cdpd.setName($simple_name.name);
                cdpd.setDataType(dt);
                cdpd.setConst($data_type.isconst);

                putSymbol($simple_name.name, NameSpace.NAME, cdpd, input, $data_type.start);

                $dataparams.add(cdpd);
              }
              ))+)
    ;

native_data_type_reference returns [DataType datatype]
    : ^(NATIVE_DATA_TYPE (
            i=CT_INT    { $datatype = $bip_package::parsed_package.getIntDataType(); }
          | i=CT_BOOL   { $datatype = $bip_package::parsed_package.getBoolDataType(); }
          | i=CT_FLOAT  { $datatype = $bip_package::parsed_package.getFloatDataType(); }
          | i=CT_STRING { $datatype = $bip_package::parsed_package.getStringDataType(); } ))
    ;
    
annotated_multi_data_declaration
scope AnnotatedScope;
@init {
  initAnnotatedScope();
}
    : ^(ANNOTATED_DATA_DECLARATION
        multi_data_declaration
        annotations?)
    ;

multi_data_declaration
@init{
  DataDeclaration dd = null;
}
    :   ^(DATA_DECLARATION data_type
            ^(DATA_DECLARATION_NAMES
                (^(simple_name {
                        // code specific to the context (scope)
                        if ($BipScope::kind.equals(BipScopeKind.CONNECTOR_DEFINITION)){
                          ConnectorDataDeclaration cd = ConnectorFactory.eINSTANCE.createConnectorDataDeclaration();

                          cd.setConst($data_type.isconst);

                          $connector_type_definition::ct.getDataDeclarations().add(cd);

                          dd = cd;
                        } else if ($BipScope::kind.equals(BipScopeKind.ATOM_DEFINITION)){
                          AtomInternalDataDeclaration aid = AtomFactory.eINSTANCE.createAtomInternalDataDeclaration();
    
                          aid.setExported($multi_data_declaration_with_modifiers::exported);
                          aid.setConst($data_type.isconst);

                          $atom_type_definition::at.getInternalDataDeclarations().add(aid);

                          if(aid.isExported()){
                            putSymbol($simple_name.name, NameSpace.EXPORTED_NAME, aid, input, $simple_name.start);
                            $atom_type_definition::at.getExportedDataDeclarations().add(aid);
                          }

                          dd = aid;
                        } else if ($BipScope::kind.equals(BipScopeKind.PACKAGE)){
                          ConstDataDeclaration cdd = PackagingFactory.eINSTANCE.createConstDataDeclaration();

                          cdd.setConst($data_type.isconst);

                          putSymbol($simple_name.name, NameSpace.EXPORTED_NAME, cdd, input, $simple_name.start);

                          $bip_package::parsed_package.getConstData().add(cdd);

                          dd = cdd;
                        }

                        // code common to all context (scopes)
                        setSourceInfo(dd, $simple_name.start);

                        dd.setDataType($data_type.datatype);
                        dd.setName($simple_name.name);
                    
                        putSymbol($simple_name.name, NameSpace.NAME, dd, input, $simple_name.start);

                        addElementToAnnotate(dd);
                    }
                    (partial_statement { dd.setValue($partial_statement.expression); })?))+))
    ;

multi_data_declaration_with_modifiers
scope {
  boolean exported;
}
scope AnnotatedScope;
@init {
  $multi_data_declaration_with_modifiers::exported = false;
  initAnnotatedScope();
}
    :   ^(DATA_DECLARATION_WITH_MODIFIERS
               (^(DATA_MODIFIERS (EXPORT {$multi_data_declaration_with_modifiers::exported = true;} )?))?
               multi_data_declaration
               annotations?)
    ;

fragment_port_declaration
@init {
  PortDeclaration pd = null;
  Class targetClassOfParameters = null;
  int param_index = 0;
}
    :  ^(port_name=simple_name {
                        if ($BipScope::kind.equals(BipScopeKind.ATOM_DEFINITION)){                          
                           PortType pt = $multi_port_declaration::pt;

                           if ($multi_port_declaration_with_modifiers::external) {
                             assert(!$multi_port_declaration_with_modifiers::exported);

                             AtomExternalPortDeclaration p = AtomFactory.eINSTANCE.createAtomExternalPortDeclaration();
                             setSourceInfo(p, $start);

                             // FIXME: to be moved to a safer place
                             addElementToAnnotate(p);

                             pd = p;
                             p.setName($port_name.name);
                             p.setPortType(pt);

                             if ($multi_port_declaration_with_modifiers::hasExternalName) {
                               p.setBackendName($multi_port_declaration_with_modifiers::externalName);
                             }

                             p.setPolicy($multi_port_declaration_with_modifiers::policy);

                             putSymbol($port_name.name, NameSpace.NAME, p, input, $start);

                             $atom_type_definition::at.getExternalPortDeclarations().add(p);
                           }
                           else {
                             AtomInternalPortDeclaration p = AtomFactory.eINSTANCE.createAtomInternalPortDeclaration();
                             setSourceInfo(p, $start);

                             // FIXME: to be moved to a safer place
                             addElementToAnnotate(p);

                             pd = p;
                             p.setName($port_name.name);
                             p.setPortType(pt);

                             // extern attribute
                             //p.setExternal($multi_port_declaration_with_modifiers::external);

                             // 2 scenarii:
                             // - single export, the ExportPort must be created here
                             // - merged export, the ExportPort is already created
                             if ($multi_port_declaration_with_modifiers::exported){
                               assert(!$multi_port_declaration_with_modifiers::external);
                               assert(!$multi_port_declaration_with_modifiers::hasExternalName);
                               assert($multi_port_declaration_with_modifiers::externalName == "");

                               AtomExportPortDeclaration aepd_tmp = $multi_port_declaration_with_modifiers::aepd;
                               // exportport does not exist, create it and add it to the list
                               // of exported ports. In the other case, it is added by the caller rule.
                               if (aepd_tmp == null){
                                 aepd_tmp = AtomFactory.eINSTANCE.createAtomExportPortDeclaration();
                                 aepd_tmp.setName($port_name.name);
                                 addElementToAnnotate(aepd_tmp);

                                 putSymbol($port_name.name, NameSpace.EXPORTED_NAME, aepd_tmp, input, $start);

                                 $atom_type_definition::at.getExportPortDeclarations().add(aepd_tmp);
                                 $atom_type_definition::at.getExportedPortDeclarations().add(aepd_tmp);
                               }
                               setSourceInfo(aepd_tmp, $start);
                               aepd_tmp.setPortType(pt);
                               aepd_tmp.getPortDeclarationReferences().add(p);
                             }

                             putSymbol($port_name.name, NameSpace.NAME, p, input, $start);

                             $atom_type_definition::at.getInternalPortDeclarations().add(p);
                           }

                           // parameters should be internal data of atoms
                           targetClassOfParameters = AtomInternalDataDeclaration.class;
                        } else if ($BipScope::kind.equals(BipScopeKind.CONNECTOR_DEFINITION)) {
                           PortType pt = $single_port_declaration::pt;

                           ConnectorExportedPortDeclaration p = ConnectorFactory.eINSTANCE.createConnectorExportedPortDeclaration();
                           setSourceInfo(p, $start);

                           // FIXME: to be moved to a safer place
                           addElementToAnnotate(p);

                           pd = p;
                           p.setName($port_name.name);
                           p.setPortType(pt);

                           putSymbol($port_name.name, NameSpace.NAME, p, input, $start);
                           putSymbol($port_name.name, NameSpace.EXPORTED_NAME, p, input, $start);

                           $connector_type_definition::ct.setExportedPortDeclaration(p);
                             
                           // parameters should be internal data of connectors
                           targetClassOfParameters = ConnectorDataDeclaration.class;
                        }

                        assert(targetClassOfParameters != null);
                     }
            (^(DATA_PARAMS (simple_reference [NameSpace.NAME, targetClassOfParameters] {
                             DataDeclarationReferenceDataParameter ddrdp = DataFactory.eINSTANCE.createDataDeclarationReferenceDataParameter();
                             setSourceInfo(ddrdp, $simple_reference.start);

                             DataDeclaration dd = (DataDeclaration) $simple_reference.object;

                             // if you wonder why this piece of code is here and why the test is not
                             // carried only by EMF: we need to set some backpointers to param decl
                             // which is not possible in case the list is too large. But testing only
                             // for overflow and not underflow would not be consistent.
                             if (param_index > pd.getPortType().getDataParameterDeclarations().size()-1) {
                                throw new IncorrectParametersException(input, $simple_reference.start);
                             }

                             ddrdp.setDataDeclarationReference(dd);
                             DataDeclaration p_decl = pd.getPortType().getDataParameterDeclarations().get(param_index);
                             ddrdp.setParameterDeclaration(p_decl);
                             ddrdp.setType(dd.getDataType());
                             pd.getDataParameters().add(ddrdp);
                             param_index++;
                            }
                           )+))?)
    ;

multi_port_declaration
scope {
  PortType pt;
}
    :   ^(PORT_DECLARATION fully_qualified_reference [ NameSpace.TYPE, PortType.class ] {
             $multi_port_declaration::pt = (PortType) $fully_qualified_reference.object;
        }
        ^(PORT_DECLARATION_NAMES fragment_port_declaration+))
    ;

multi_port_declaration_with_modifiers
scope{
  boolean exported;
  boolean external;
  boolean hasExternalName;
  String externalName;
  EventConsumptionPolicy policy;
  AtomExportPortDeclaration aepd;
}
scope AnnotatedScope;
@init{
  $multi_port_declaration_with_modifiers::exported = false;
  $multi_port_declaration_with_modifiers::external = false;
  $multi_port_declaration_with_modifiers::hasExternalName = false;
  $multi_port_declaration_with_modifiers::externalName = "";
  $multi_port_declaration_with_modifiers::policy = EventConsumptionPolicy.REMEMBER;
  $multi_port_declaration_with_modifiers::aepd = null;
  initAnnotatedScope();
}
    :    ^(PORT_DECLARATION_WITH_MODIFIERS
           ^(PORT_MODIFIERS 
                    (EXPORT {$multi_port_declaration_with_modifiers::exported = true;})?
                    (EXTERN {$multi_port_declaration_with_modifiers::external = true;}
                      (^(AS backend_name=STRING {
                          $multi_port_declaration_with_modifiers::hasExternalName = true;
                          $multi_port_declaration_with_modifiers::externalName =
                              $backend_name.text.substring(1, $backend_name.text.length() - 1); }
                      ))?
                      (   REMEMBER { $multi_port_declaration_with_modifiers::policy = EventConsumptionPolicy.REMEMBER; }
                        | IGNORE   { $multi_port_declaration_with_modifiers::policy = EventConsumptionPolicy.IGNORE; }
                        | ERROR    { $multi_port_declaration_with_modifiers::policy = EventConsumptionPolicy.ERROR; }
                      )?    
                    )?
                    (^(EXPORT_PORT_MERGED simple_name {
                        $multi_port_declaration_with_modifiers::exported = true;
                        $multi_port_declaration_with_modifiers::aepd = AtomFactory.eINSTANCE.createAtomExportPortDeclaration();
                        $multi_port_declaration_with_modifiers::aepd.setName($simple_name.name);
                        addElementToAnnotate($multi_port_declaration_with_modifiers::aepd);

                        putSymbol($simple_name.name, NameSpace.EXPORTED_NAME, $multi_port_declaration_with_modifiers::aepd, input, $EXPORT_PORT_MERGED);
                        setSourceInfo($multi_port_declaration_with_modifiers::aepd, $EXPORT_PORT_MERGED);

                        $atom_type_definition::at.getExportPortDeclarations().add($multi_port_declaration_with_modifiers::aepd);
                        $atom_type_definition::at.getExportedPortDeclarations().add($multi_port_declaration_with_modifiers::aepd);
                    }))?
             )
           multi_port_declaration
           annotations?)
    ;

binary_op_no_commutative_no_associative returns [BinaryOpExpression expression]
@init{
  $expression = ActionlangFactory.eINSTANCE.createBinaryOpExpression();
  setSourceInfo($expression, $start);
  BinaryOperators op = BinaryOperators.LOGICAL_OR; //I have to initialize it
}
    : ^((  OR_OP        {op = BinaryOperators.LOGICAL_OR;}
         | AND_OP       {op = BinaryOperators.LOGICAL_AND;}
         | BWISE_OR_OP  {op = BinaryOperators.BWISE_OR;}
         | BWISE_XOR_OP {op = BinaryOperators.BWISE_XOR;}
         | BWISE_AND_OP {op = BinaryOperators.BWISE_AND;}
         | PLUS_OP      {op = BinaryOperators.ADDITION;}
         | MINUS_OP     {op = BinaryOperators.SUBTRACTION;}
         | MULT_OP      {op = BinaryOperators.MULTIPLICATION;}
         | EQ_OP        {op = BinaryOperators.EQUAL;}
         | NE_OP        {op = BinaryOperators.NOT_EQUAL;}
         | LT_OP        {op = BinaryOperators.LESS_THAN;}
         | GT_OP        {op = BinaryOperators.GREATER_THAN;}
         | LE_OP        {op = BinaryOperators.LESS_THAN_OR_EQUAL;}
         | GE_OP        {op = BinaryOperators.GREATER_THAN_OR_EQUAL;}
         | DIV_OP       {op = BinaryOperators.DIVISION;}
         | MOD_OP       {op = BinaryOperators.MODULO;}
         )
         lhs=partial_statement rhs=partial_statement)
       {
          $expression.setOperator(op);
          $expression.setLeft($lhs.expression);
          $expression.setRight($rhs.expression);
       }
    ;

unary_op returns [UnaryOpExpression expression]
@init {
  $expression = ActionlangFactory.eINSTANCE.createUnaryOpExpression();
  setSourceInfo($expression, $start);
}
    : ^((  UNARY_MINUS  {$expression.setOperator(UnaryOperators.MINUS);}
         | BWISE_NOT_OP {$expression.setOperator(UnaryOperators.BWISE_NOT);}
         | NOT_OP       {$expression.setOperator(UnaryOperators.LOGICAL_NOT);}
         )
         partial_statement {$expression.setOperand($partial_statement.expression);})
    ;

partial_statement returns [ValuedExpression expression]
    :
      unary_op { $expression = $unary_op.expression;}
    | binary_op_no_commutative_no_associative  {$expression = $binary_op_no_commutative_no_associative.expression;}
    | postfix_expression {$expression = $postfix_expression.expression;}
    ;

assignment_statement returns [AssignmentExpression expression;]
@init {
  $expression = ActionlangFactory.eINSTANCE.createAssignmentExpression();
  setSourceInfo($expression, $start);
}
  : ^(ASSIGN_OP postfix_expression
          partial_statement)
     {
           ValuedExpression ve = $postfix_expression.expression;

           $expression.setRhs($partial_statement.expression);

           if (ve instanceof DirectDataDeclarationReferenceExpression ||
               ve instanceof SubDataDeclarationReferenceExpression) {
            $expression.setLhs(ve);
           } else {
            throw new OperationInvalidOrNotSupportedException(input, $start);
           }
     }
  ;

argument_expression_list
    : ^(ARGUMENT_EXPR_LIST (partial_statement{
                        $function_call_expression::fce.getParameters().add($partial_statement.expression);
                  })+)
    ;

statement_block [List<Expression> actions]
  :
   (
       partial_statement {$actions.add($partial_statement.expression);}
     | assignment_statement {$actions.add($assignment_statement.expression);}
     | if_then_else_expression {$actions.add($if_then_else_expression.expression);}
     )+
  ;

if_then_else_expression returns [IfThenElseExpression expression]
@init {
    $expression = ActionlangFactory.eINSTANCE.createIfThenElseExpression();
    setSourceInfo($expression, $start);
}
  : ^(IFTHENELSE_EXPRESSION condition=partial_statement then_blk=then_subexpr[$expression.getThen()] else_blk=else_subexpr[$expression.getElse()] )
     {
         $expression.setCondition($condition.expression);
     }
  ;

then_subexpr [List<Expression> actions]
  : ^(THEN_SUBEXPR statement_block [$actions])
  ;

else_subexpr [List<Expression> actions]
  : ^(ELSE_SUBEXPR (statement_block[$actions])?)
  ;

function_call_expression returns [ValuedExpression expression]
scope {
  FunctionCallExpression fce;
}
@init{
   $function_call_expression::fce = ActionlangFactory.eINSTANCE.createFunctionCallExpression();
   setSourceInfo($function_call_expression::fce, $start);
   $expression = $function_call_expression::fce;
}
  : ^(FUNCTION_CALL_EXPRESSION fully_qualified_name argument_expression_list?) {
        $function_call_expression::fce.setFunctionName($fully_qualified_name.fullname);
      }
  ;

postfix_expression returns [ValuedExpression expression]
  : function_call_expression {$expression = $function_call_expression.expression;}
  | primary_expression {$expression = $primary_expression.expression;}
  ;

primary_expression returns [ValuedExpression expression;]
    : fully_qualified_reference [NameSpace.NAME, AnnotatedEObject.class] {
        AnnotatedEObject object = $fully_qualified_reference.object;

        if (object instanceof DataDeclaration) {
          DirectDataDeclarationReferenceExpression dddre = ActionlangFactory.eINSTANCE.createDirectDataDeclarationReferenceExpression();
          setSourceInfo(dddre, $start);
          dddre.setDataDeclaration((DataDeclaration) object);
          $expression = dddre;
        }
        else if (object instanceof SubDataDeclarationReference) {
          SubDataDeclarationReferenceExpression sddrexpr = ActionlangFactory.eINSTANCE.createSubDataDeclarationReferenceExpression();
          setSourceInfo(sddrexpr, $start);
          sddrexpr.setSubDataDeclarationRef((SubDataDeclarationReference) EcoreUtil.copy(object));
          $expression = sddrexpr;
        }
        else {
          throw createIncorrectBipTypeException($fully_qualified_reference.fullname, NameSpace.NAME, DataDeclaration.class, input, $start);
        }
      }

    | INT {
       DirectIntegerExpression dve = ActionlangFactory.eINSTANCE.createDirectIntegerExpression();
       setSourceInfo(dve, $start);
       try {
         dve.setValue(Integer.parseInt($INT.text));
       } catch (NumberFormatException e) {
         throw new IncorrectNumberFormatException(input, $start, $INT.text);
       }
       $expression = dve;
      }

    | FLOAT {
       DirectFloatExpression dve = ActionlangFactory.eINSTANCE.createDirectFloatExpression();
       setSourceInfo(dve, $start);
       try {
         dve.setValue(Float.parseFloat($FLOAT.text));
       } catch (NumberFormatException e) {
         throw new IncorrectNumberFormatException(input, $start, $FLOAT.text);
       }
       $expression = dve;
    }

    | STRING {
       DirectStringExpression dve = ActionlangFactory.eINSTANCE.createDirectStringExpression();
       setSourceInfo(dve, $start);
       dve.setValue($STRING.text);
       $expression = dve;
    }
    | TRUE {
       DirectBooleanExpression tfde = ActionlangFactory.eINSTANCE.createDirectBooleanExpression();
       setSourceInfo(tfde, $start);
       tfde.setValue(true);
       $expression = tfde;
    }
    | FALSE {
       DirectBooleanExpression tfde = ActionlangFactory.eINSTANCE.createDirectBooleanExpression();
       setSourceInfo(tfde, $start);
       tfde.setValue(false);
       $expression = tfde;
    }
  ;

transition_action [List<Expression> actions]
    :(
       partial_statement {$actions.add($partial_statement.expression);}
     | if_then_else_expression {$actions.add($if_then_else_expression.expression);}
     | assignment_statement {$actions.add($assignment_statement.expression);}
     )+
    ;

transition_guard returns [ValuedExpression expression;]
  : partial_statement {$expression = $partial_statement.expression;}
  ;

initial_transition
    : ^(INITIAL_TRANSITION_DECLARATION
          (simple_reference [NameSpace.NAME, State.class] {
              State s = (State) $simple_reference.object;
              $atom_type_definition::pn.getInitStates().add(s);
            }
          )+
          (^(TRANSITION_ACTION  transition_action[$atom_type_definition::pn.getInitialActions()]))?)
    ;

transition
scope AnnotatedScope;
@init{
   List<State> sstates = new ArrayList<State>();
   List<State> estates = new ArrayList<State>();
   AtomInternalExternalPortDeclaration p = null;
   Transition t = BehaviorFactory.eINSTANCE.createTransition();
   setSourceInfo(t, $start);

   initAnnotatedScope(t);
}
    :^(TRANSITION_DECLARATION
            (port_ref = simple_reference [NameSpace.NAME, AtomInternalExternalPortDeclaration.class] {
                 p = (AtomInternalExternalPortDeclaration) $port_ref.object;
                 t.setTriggerPort(p);
            })?

            ^(PLACES (pn = simple_reference [NameSpace.NAME, State.class] {
                 State s = (State) $pn.object;
                 sstates.add(s);
              })+)

            ^(PLACES (pn = simple_reference [NameSpace.NAME, State.class] {
                 State s = (State) $pn.object;
                 estates.add(s);
              })+)

            (^(TRANSITION_GUARD transition_guard {t.setGuard($transition_guard.expression);}))?
            (^(TRANSITION_ACTION transition_action[t.getActions()]))?
            annotations?
            )
            {
              t.getSources().addAll(sstates);
              t.getDestinations().addAll(estates);
              $atom_type_definition::pn.getTransitions().add(t);
            }
    ;

compound_inner_port_reference returns [SubPortDeclarationReference portref]
    : fully_qualified_reference [NameSpace.NAME, SubPortDeclarationReference.class] {
          SubPortDeclarationReference pd = (SubPortDeclarationReference) $fully_qualified_reference.object;
          $portref = EcoreUtil.copy(pd);
      }
    ;

compound_interaction returns [ConnectorInteraction inter]
@init{
  $inter = null;
}
    : ^(CONNECTOR_INTERACTION simple_reference [NameSpace.NAME, ConnectorDeclaration.class] {
          ConnectorDeclaration cd = (ConnectorDeclaration) $simple_reference.object;

          $inter = PriorityFactory.eINSTANCE.createConnectorInteraction();
          setSourceInfo($inter, $start);
          $inter.setConnectorDeclaration(cd);
        }
      (^(CONNECTOR_PORT_INTERACTION (compound_inner_port_reference {
          $inter.getPortDeclarationReferences().add($compound_inner_port_reference.portref);
        }
      )+))?)
     | MULT_OP COLON MULT_OP // do nothing, this will add 'null' as the interaction. This should be read as 'anything'.
    ;

places_declaration
    :^(PLACES (simple_name
           {
             State s = BehaviorFactory.eINSTANCE.createState();
             s.setName($simple_name.name);
             setSourceInfo(s, $simple_name.start);

             putSymbol($simple_name.name, NameSpace.NAME, s, input, $simple_name.start);

             $atom_type_definition::pn.getStates().add(s);
           })+)
    ;

main_component_declaration [BipPackage main_package] returns [ComponentDeclaration cd]
scope BipScope;
@init {
  initScope(BipScopeKind.MAIN_COMPONENT_DECLARATION, this.globalSymbolMap.get(main_package));
  ComponentType ct = null;
  $cd = ComponentFactory.eINSTANCE.createComponentDeclaration();
  setSourceInfo($cd, $start);
}

    : ^(COMPONENT_DECLARATION fully_qualified_reference [NameSpace.TYPE, ComponentType.class] {
          ct = (ComponentType) $fully_qualified_reference.object;
          $cd.setName("ROOT");
          $cd.setType(ct);
        }
        (^(DATA_PARAMS (partial_statement {
                $cd.getParameters().add($partial_statement.expression);
              }
          )+))?)
    ;

fragment_component_declaration
@init{
  ComponentDeclaration cd = ComponentFactory.eINSTANCE.createComponentDeclaration();
  addElementToAnnotate(cd);
}
@after {
  putAllFieldAccessSymbols(cd.getName(), cd, this.globalSymbolMap.get(cd.getType()), input, $start);
}
    :^(simple_name {
          setSourceInfo(cd, $start);
          cd.setName($simple_name.name);
          cd.setType($multi_component_declaration::ct);

          putSymbol($simple_name.name, NameSpace.NAME, cd, input, $start);

          $compound_type_definition::ct.getComponentDeclarations().add(cd);
        }
        (^(DATA_PARAMS (partial_statement {
                cd.getParameters().add($partial_statement.expression);
              }
          )+))?)
    ;

multi_component_declaration
scope {
  ComponentType ct;
}
scope AnnotatedScope;
@init{
  initAnnotatedScope();
}
    :^(COMPONENT_DECLARATION fully_qualified_reference [NameSpace.TYPE, ComponentType.class] {
         $multi_component_declaration::ct = (ComponentType) $fully_qualified_reference.object;
       }
       ^(COMPONENT_DECLARATION_NAMES fragment_component_declaration+)
       annotations?)
    ;

fragment_connector_declaration
@init {
  ConnectorDeclaration cd = ConnectorFactory.eINSTANCE.createConnectorDeclaration();
  addElementToAnnotate(cd);
  setSourceInfo(cd, $start);
  int port_index = 0;
}
@after {
  putAllFieldAccessSymbols(cd.getName(), cd, this.globalSymbolMap.get(cd.getType()), input, $start);
}
    :    ^(simple_name {                 
                 cd.setName($simple_name.name);
                 cd.setType($multi_connector_declaration::ct);

                 putSymbol($simple_name.name, NameSpace.NAME, cd, input, $start);

                 $compound_type_definition::ct.getConnectorDeclarations().add(cd);
             }
           ^(PORT_PARAMS (compound_inner_port_reference {
                            PortDeclarationReferenceParameter pdrp = PortFactory.eINSTANCE.createPortDeclarationReferenceParameter();
                            setSourceInfo(pdrp, $start);

                            ConnectorType ct = cd.getType();
                            if (port_index > ct.getPorts().size() - 1) {
                              throw new IncorrectParametersException(input, $start);
                            }

                            ConnectorPortParameterDeclaration pd = ct.getPorts().get(port_index);
                            pdrp.setParameterDeclaration(pd);
                            pdrp.setSubPortDeclarationReference($compound_inner_port_reference.portref);
                            cd.getPortParameters().add(pdrp);
                            port_index++;
                          }
                         )+))
    ;

compound_priority_guard returns [ValuedExpression expression;]
  : partial_statement {$expression = $partial_statement.expression;}
  ;

compound_priority_declaration
@init{
  CompoundPriorityDeclaration pd = PriorityFactory.eINSTANCE.createCompoundPriorityDeclaration();
  setSourceInfo(pd, $start);
  paraphrases.push(" in priority declaration");
}
    :^(COMPOUND_PRIORITY_DECLARATION simple_name
                low=compound_interaction high=compound_interaction
         {

           pd.setName($simple_name.name);
           pd.setLow($low.inter);
           pd.setHigh($high.inter);
         }
                (^(kk=COMPOUND_PRIORITY_GUARD
                compound_priority_guard) {pd.setGuard($compound_priority_guard.expression);})?)
                {                  
                  putSymbol(pd.getName(), NameSpace.NAME, pd, input, $start);

                  $compound_type_definition::ct.getPriorities().add(pd);
                }
    ;

multi_connector_declaration
scope {
  ConnectorType ct;
}
scope AnnotatedScope;
@init{
  initAnnotatedScope();
}
    : ^(CONNECTOR_DECLARATION fully_qualified_reference [NameSpace.TYPE, ConnectorType.class] {
          $multi_connector_declaration::ct = (ConnectorType) $fully_qualified_reference.object;
        }
        ^(CONNECTOR_DECLARATION_NAMES fragment_connector_declaration+)
        annotations?)
    ;

export_inner_port
scope AnnotatedScope;
@init {
    CompoundExportPortDeclaration cepd = CompoundFactory.eINSTANCE.createCompoundExportPortDeclaration();

    initAnnotatedScope(cepd);
}
    :^(COMPOUND_EXPORT_PORT
                (compound_inner_port_reference {
                                 cepd.getPortDeclarationReferences().add($compound_inner_port_reference.portref);
                                 // not checking for correct type. Should be handled by EMF constraint.
                     cepd.setPortType($compound_inner_port_reference.portref.getForwardPortDeclaration().getPortType());
                })+

                simple_name {
                   cepd.setName($simple_name.name);

                   putSymbol($simple_name.name, NameSpace.EXPORTED_NAME, cepd, input, $simple_name.start);
                   setSourceInfo(cepd, $simple_name.start);

                   $compound_type_definition::ct.getExportPortDeclarations().add(cepd);
                   $compound_type_definition::ct.getExportedPortDeclarations().add(cepd);
                  }
                annotations?
                )
    ;

compound_inner_data_reference returns [SubDataDeclarationReference dataref]
    :    fully_qualified_reference [NameSpace.NAME, SubDataDeclarationReference.class] {
            SubDataDeclarationReference dd = (SubDataDeclarationReference) $fully_qualified_reference.object;
            $dataref = EcoreUtil.copy(dd);
         }
    ;

export_inner_data
scope AnnotatedScope;
@init{
    CompoundExportDataDeclaration cedd = CompoundFactory.eINSTANCE.createCompoundExportDataDeclaration();
    initAnnotatedScope(cedd);
}
    : ^(COMPOUND_EXPORT_DATA compound_inner_data_reference simple_name annotations? {
                cedd.setName($simple_name.name);
                cedd.setDataDeclarationReference($compound_inner_data_reference.dataref);
                cedd.setDataType($compound_inner_data_reference.dataref.getForwardDataDeclaration().getDataType());

                putSymbol($simple_name.name, NameSpace.EXPORTED_NAME, cedd, input, $simple_name.start); 
                setSourceInfo(cedd, $simple_name.start);

                $compound_type_definition::ct.getExportDataDeclarations().add(cedd);
                $compound_type_definition::ct.getExportedDataDeclarations().add(cedd);
             })
    ;

compound_type_definition returns [CompoundType type;]
scope {
  CompoundType ct;
}
@init {
  paraphrases.push("in compound definition,");
  $compound_type_definition::ct = TypesFactory.eINSTANCE.createCompoundType();
  setSourceInfo($compound_type_definition::ct, $start);
  $type = $compound_type_definition::ct;
}
@after{
paraphrases.pop();
}
    : ^(COMPOUND_TYPE
           simple_name {
             $type.setName($simple_name.name);

             putSymbol($simple_name.name, NameSpace.TYPE, $type, input, $start);
             putSymbol($simple_name.name, NameSpace.EXPORTED_TYPE, $type, input, $start);
           }
           compound_type_body
         )
    ;

export_inner_data_or_port
    : export_inner_data
    | export_inner_port
    ;

multi_component_or_connector_declaration
    : multi_component_declaration
    | multi_connector_declaration
    ;

compound_type_body
scope BipScope;
@init {
  initScope(BipScopeKind.COMPOUND_DEFINITION, $compound_type_definition::ct);
}
    : (component_data_params {
        $compound_type_definition::ct.getDataParameterDeclarations().addAll($component_data_params.dataparams);
      })?
      ^(COMPONENT_OR_CONNECTOR_DECLARATIONS multi_component_or_connector_declaration+)
      (^(COMPOUND_PRIORITY_DECLARATIONS compound_priority_declaration+))?
      (^(COMPOUND_EXPORT_DATA_OR_PORT export_inner_data_or_port+))?
    ;
    

atom_priority_guard returns [ValuedExpression expression;]
  : partial_statement {$expression = $partial_statement.expression;}
  ;

port_reference_wildcard returns [String name, AtomInternalPortDeclaration port]
@init {
    $port = null;
}
    : simple_reference [NameSpace.NAME, AtomInternalPortDeclaration.class] {
        $name = $simple_reference.name;
        $port = (AtomInternalPortDeclaration) $simple_reference.object;
      }
    | MULT_OP {$name = "*";}
    ;

atom_priority_declaration
@init{
  AtomPriorityDeclaration pd = PriorityFactory.eINSTANCE.createAtomPriorityDeclaration();
  setSourceInfo(pd, $start);
  paraphrases.push(" in atom priority declaration");
}
    :
        ^(ATOM_PRIORITY_DECLARATION simple_name
            low=port_reference_wildcard high=port_reference_wildcard
          {
                pd.setName($simple_name.name);

                if (!$low.name.equals("*")) {
                   pd.setLow($low.port);
                }
                if (!$high.name.equals("*")) {
                   pd.setHigh($high.port);
                }
           }
            (^(ATOM_PRIORITY_GUARD atom_priority_guard) {pd.setGuard($atom_priority_guard.expression);})?)
           {
            putSymbol($simple_name.name, NameSpace.NAME, pd, input, $start);

            $atom_type_definition::at.getPriorities().add(pd);
           }
;

atom_invariant_guard returns [ValuedExpression expression;]
    : partial_statement {$expression = $partial_statement.expression;}
    ;

atom_invariant_declaration
@init{
  AtomInvariant inv = InvariantFactory.eINSTANCE.createAtomInvariant();
  inv.setExactState(false);
  setSourceInfo(inv, $start);
  paraphrases.push(" in atom invariant declaration");
}
    :
        ^(INVARIANT simple_name { inv.setName($simple_name.name); }
            ((^(INVARIANT_AT
                { inv.setExactState(true); }
                (p=simple_reference [NameSpace.NAME, State.class] {
                    inv.getSources().add((State) $p.object);
                })+))
            | (^(INVARIANT_FROM
                { inv.setExactState(false); }  
                (p=simple_reference [NameSpace.NAME, State.class] {
                    inv.getSources().add((State) $p.object);
                })+)))?
            (^(INVARIANT_GUARD atom_invariant_guard {
                inv.setGuard($atom_invariant_guard.expression);
            }))
            {
                putSymbol($simple_name.name, NameSpace.NAME, inv, input, $start);
                
                $atom_type_definition::at.getInvariants().add(inv);
            })
    ;
    
atom_priority_or_invariant_declaration
    : atom_priority_declaration
    | atom_invariant_declaration
    ;

atom_type_definition returns [AtomType type]
scope {
  PetriNet pn;
  AtomType at;
}
@init {
  paraphrases.push("in atom definition,");
  $atom_type_definition::pn = BehaviorFactory.eINSTANCE.createPetriNet();
  setSourceInfo($atom_type_definition::pn, $start);
  $atom_type_definition::at = TypesFactory.eINSTANCE.createAtomType();
  setSourceInfo($atom_type_definition::at, $start);
  $type = $atom_type_definition::at;
}
@after{
paraphrases.pop();
}
    :^(ATOM_TYPE
         simple_name {
           $type.setName($simple_name.name);
           $type.setBehavior($atom_type_definition::pn);
           putSymbol($simple_name.name, NameSpace.TYPE, $atom_type_definition::at, input, $start);
           putSymbol($simple_name.name, NameSpace.EXPORTED_TYPE, $atom_type_definition::at, input, $start);
         }
         atom_type_body
     )
    ;

atom_type_body
scope BipScope;
@init {
  initScope(BipScopeKind.ATOM_DEFINITION, $atom_type_definition::at);
}
    : (component_data_params {
             $atom_type_definition::at.getDataParameterDeclarations().addAll($component_data_params.dataparams);
        })?
      (^(DATA_OR_PORT_DECLARATIONS multi_data_or_port_declaration_with_modifiers+))?
      places_declaration
      initial_transition
      ^(TRANSITION_DECLARATIONS transition+)
      (^(ATOM_PRIORITY_OR_INVARIANT_DECLARATIONS atom_priority_or_invariant_declaration+))?
    ;

multi_data_or_port_declaration_with_modifiers
    : multi_data_declaration_with_modifiers
    | multi_port_declaration_with_modifiers
    ;

port_type_definition returns [PortType type;]
scope {
  PortType pt;
}
@init {
  paraphrases.push("in port definition,");
  $port_type_definition::pt = TypesFactory.eINSTANCE.createPortType();
  $type = $port_type_definition::pt;
  setSourceInfo($type, $start);
}
@after{
  paraphrases.pop();
}
    :^(PORT_TYPE
         simple_name {
           $type.setName($simple_name.name);

           putSymbol($simple_name.name, NameSpace.TYPE, $type, input, $start);
           putSymbol($simple_name.name, NameSpace.EXPORTED_TYPE, $type, input, $start);
         }
         port_type_body)
    ;

port_type_body
scope BipScope;
@init {
  initScope(BipScopeKind.PORT_DEFINITION, $port_type_definition::pt);
}
    : (port_data_params {
          $port_type_definition::pt.getDataParameterDeclarations().addAll($port_data_params.dataparams);
      })?
    ;

// If this rule has to be used from a different context
// than port type def, use scope instead of list return
port_data_params returns [List<PortDataParameterDeclaration> dataparams]
@init {
  $dataparams = new ArrayList<PortDataParameterDeclaration>();
}
    :   ^(DATA_PARAMS
            (^(DATA_PARAM data_type
                          simple_name
              {
                DataType dt = $data_type.datatype;

                PortDataParameterDeclaration pdpd = PortFactory.eINSTANCE.createPortDataParameterDeclaration();
                pdpd.setName($simple_name.name);
                setSourceInfo(pdpd, $simple_name.start);
                pdpd.setDataType(dt);
                pdpd.setConst($data_type.isconst);

                putSymbol($simple_name.name, NameSpace.NAME, pdpd, input, $simple_name.start);
                putSymbol($simple_name.name, NameSpace.EXPORTED_NAME, pdpd, input, $simple_name.start);

                $dataparams.add(pdpd);
              }
         ))+)
    ;

port_type_param
@init {
  ConnectorPortParameterDeclaration cpp = ConnectorFactory.eINSTANCE.createConnectorPortParameterDeclaration();
}
@after {
  putAllFieldAccessSymbols(cpp.getName(), cpp, this.globalSymbolMap.get(cpp.getPortType()), input, $start);
}
    :^(PORT_PARAM fully_qualified_reference [NameSpace.TYPE, PortType.class]
                  simple_name
      {
        PortType pt = (PortType) $fully_qualified_reference.object;
        setSourceInfo(cpp, $start);
        cpp.setName($simple_name.name);
        cpp.setPortType(pt);

        putSymbol($simple_name.name, NameSpace.NAME, cpp, input, $start);

        $connector_type_definition::ct.getPorts().add(cpp);
      })
    ;

annotated_export_port_declaration
scope AnnotatedScope;
@init {
    initAnnotatedScope();
}
    : ^(ANNOTATED_EXPORT_PORT_DECLARATION
        single_port_declaration
        annotations?)
    ;

single_port_declaration
scope{
  PortType pt;
}
    : ^(PORT_DECLARATION fully_qualified_reference [NameSpace.TYPE, PortType.class] {
         $single_port_declaration::pt = (PortType) $fully_qualified_reference.object;
      }
      ^(PORT_DECLARATION_NAMES fragment_port_declaration))
    ;

connector_interaction_definition
scope {
    HashSet<ConnectorPortParameterDeclaration> defined_ports;
}
@init {
    ConnectorType type = $connector_type_definition::ct;
    ConnectorInteractionNestedDefinition def = 
        ConnectorFactory.eINSTANCE.createConnectorInteractionNestedDefinition();
    $connector_interaction_definition::defined_ports
        = new HashSet<ConnectorPortParameterDeclaration>();
}
@after {
    type.setInteractionDefinition(def.getSubInteractions().size() == 1
                                                        ? def.getSubInteractions().get(0)
                                                        : def);
    if ($connector_interaction_definition::defined_ports.size() != type.getPorts().size()){
        throw new GenericWalkerErrorException(input, $start, type,
                                              ErrorCodeEnum.invalidConnectorDefine);
    }
}
    : (
          port_nested_expression  {def.getSubInteractions().add($port_nested_expression.nport);}
        | port_primary_expression {def.getSubInteractions().add($port_primary_expression.port);}
      )+
;

port_nested_expression returns [ConnectorInteractionNestedDefinition nport;]
@init{
   $nport = 
       ConnectorFactory.eINSTANCE.createConnectorInteractionNestedDefinition();
}
    : ^(NESTED_PORT_EXPRESSION (n=port_nested_expression {
                $nport.getSubInteractions().add($n.nport);}
        | p=port_primary_expression {
                $nport.getSubInteractions().add($p.port);
        })+(QUOTE {$nport.setQuoted(true);})?)
        ;

port_primary_expression returns [ConnectorInteractionPortReference port;]
@init{
   $port = ConnectorFactory.eINSTANCE.createConnectorInteractionPortReference();
   setSourceInfo($port, $start);
}
    :  ^(PRIMARY_PORT_EXPRESSION simple_reference [NameSpace.NAME, ConnectorPortParameterDeclaration.class] {
            ConnectorPortParameterDeclaration cpp = (ConnectorPortParameterDeclaration) $simple_reference.object;
            $port.setPort(cpp);
            if ($connector_interaction_definition::defined_ports.contains(cpp)) {
                throw new GenericWalkerErrorException(input, $start, cpp,
                                                      ErrorCodeEnum.invalidConnectorDefine);
            } else {
                $connector_interaction_definition::defined_ports.add(cpp);
            }
        } (QUOTE {$port.setQuoted(true);})?)
    ;

connector_action [List<Expression> target]
    :(
       ps = partial_statement {$target.add($ps.expression);}
     | ite = if_then_else_expression {$target.add($ite.expression);}
     | as = assignment_statement  {$target.add($as.expression);}
     )*
    ;

connector_guard returns [ValuedExpression expression;]
  : partial_statement {$expression = $partial_statement.expression;}
  ;

connector_interaction
scope AnnotatedScope;
@init {
  ConnectorInteractionAction cia = ConnectorFactory.eINSTANCE.createConnectorInteractionAction();
  HashSet<String> already_seen = new HashSet<String>();
  setSourceInfo(cia, $start);

  initAnnotatedScope(cia);
}
    :^(CONNECTOR_INTERACTION
              ^(CONNECTOR_INTERACTION_PORTS (simple_reference [NameSpace.NAME, ConnectorPortParameterDeclaration.class] {
                ConnectorPortParameterDeclaration ppd = (ConnectorPortParameterDeclaration) $simple_reference.object;

                // check for duplicated port names
                if (already_seen.contains($simple_reference.name)) {
                    throw new GenericWalkerErrorException(input, $start, ppd,
                                ErrorCodeEnum.noDuplicatedPortReference);
                }

                cia.getOnPorts().add(ppd);
                already_seen.add($simple_reference.name);
               })+
               )
              (^(PROVIDED connector_guard) {cia.setGuard($connector_guard.expression);})?
              (^(UP_ACTION  connector_action[cia.getUp()]))?
              (^(DOWN_ACTION connector_action[cia.getDown()]))?
              annotations?
              )
        {
        // add it anyway (maybe it's empty. It should be catched by Model Validation pass.
        $connector_type_definition::ct.getInteractions().add(cia);
        }
    ;

connector_type_definition returns [ConnectorType type;]
scope {
   ConnectorType ct;
}
@init {
  paraphrases.push("in connector definition,");
  $connector_type_definition::ct = TypesFactory.eINSTANCE.createConnectorType();
  setSourceInfo($connector_type_definition::ct, $start);
  $type = $connector_type_definition::ct;
}
@after {
    paraphrases.pop();
}
    :^(CONNECTOR_TYPE
         simple_name {
           $type.setName($simple_name.name);

           putSymbol($simple_name.name, NameSpace.TYPE, $type, input, $start);
           putSymbol($simple_name.name, NameSpace.EXPORTED_TYPE, $type, input, $start);

           paraphrases.pop();
           paraphrases.push("in connector definition (" + $simple_name.name + "),");
         }
         connector_type_body
     )
    ;

connector_type_body
scope BipScope;
@init {
  initScope(BipScopeKind.CONNECTOR_DEFINITION, $connector_type_definition::ct);
}
    : ^(PORT_PARAMS port_type_param+)
      (^(DATA_DECLARATIONS annotated_multi_data_declaration+))?
      (annotated_export_port_declaration)?
      ^(DEFINE connector_interaction_definition)
      (^(CONNECTOR_INTERACTIONS connector_interaction+))?
    ;
  
binary_operator returns [BinaryOperators operator]
  : EQ_OP        { $operator = BinaryOperators.EQUAL; }
  | NE_OP        { $operator = BinaryOperators.NOT_EQUAL; }
  | GT_OP        { $operator = BinaryOperators.GREATER_THAN; }
  | GE_OP        { $operator = BinaryOperators.GREATER_THAN_OR_EQUAL; }
  | LT_OP        { $operator = BinaryOperators.LESS_THAN; }
  | LE_OP        { $operator = BinaryOperators.LESS_THAN_OR_EQUAL; }
  | PLUS_OP      { $operator = BinaryOperators.ADDITION; }
  | MINUS_OP     { $operator = BinaryOperators.SUBTRACTION; }
  | MULT_OP      { $operator = BinaryOperators.MULTIPLICATION; }
  | DIV_OP       { $operator = BinaryOperators.DIVISION; }
  | MOD_OP       { $operator = BinaryOperators.MODULO; }
  | BWISE_AND_OP { $operator = BinaryOperators.BWISE_AND; }
  | BWISE_OR_OP  { $operator = BinaryOperators.BWISE_OR; }
  | BWISE_XOR_OP { $operator = BinaryOperators.BWISE_XOR; }
  | AND_OP       { $operator = BinaryOperators.LOGICAL_AND; }
  | OR_OP        { $operator = BinaryOperators.LOGICAL_OR; }
  ;
  
unary_operator returns [UnaryOperators operator]
  : PLUS_OP      { $operator = UnaryOperators.PLUS; }
  | MINUS_OP     { $operator = UnaryOperators.MINUS; }
  | BWISE_NOT_OP { $operator = UnaryOperators.BWISE_NOT; }
  | NOT_OP       { $operator = UnaryOperators.LOGICAL_NOT; }
  ;
    
annotated_extern_function_prototype_definition returns [FunctionCallPrototype prototype]
scope AnnotatedScope;
@init {
  $prototype = PackagingFactory.eINSTANCE.createFunctionCallPrototype();
  initAnnotatedScope($prototype);
}
  : ^(EXTERN_FUNCTION_PROTOTYPE
      k=simple_name {
        $prototype.setFunctionName($simple_name.name);
        setSourceInfo($prototype, $start);
        
        putSymbol($simple_name.name, NameSpace.NAME, $prototype, input, $start);
        putSymbol($simple_name.name, NameSpace.EXPORTED_NAME, $prototype, input, $start);
      }
      custom_prototype[$prototype]
      annotations?)
  ;
  
annotated_extern_binary_operator_prototype_definition returns [BinaryOpPrototype prototype]
scope AnnotatedScope;
@init {
  $prototype = PackagingFactory.eINSTANCE.createBinaryOpPrototype();
  initAnnotatedScope($prototype);
}
  : ^(EXTERN_BINARY_OPERATOR_PROTOTYPE
      binary_operator {
        $prototype.setOperator($binary_operator.operator);
        setSourceInfo($prototype, $start);
      }
      custom_prototype[$prototype]
      annotations?)
  ;
  
annotated_extern_unary_operator_prototype_definition returns [UnaryOpPrototype prototype]
scope AnnotatedScope;
@init {
  $prototype = PackagingFactory.eINSTANCE.createUnaryOpPrototype();
  initAnnotatedScope($prototype);
}
  : ^(EXTERN_UNARY_OPERATOR_PROTOTYPE
      unary_operator {
        $prototype.setOperator($unary_operator.operator);
        setSourceInfo($prototype, $start);
      }
      custom_prototype[$prototype]
      annotations?)
  ;
    
custom_prototype [Prototype prototype]
    : (prototype_params {
         $prototype.getParameterDeclarations().addAll($prototype_params.params);
       })?
    (fdtn_ret=data_type {
        $prototype.setReturnType($fdtn_ret.datatype);
        $prototype.setConst($fdtn_ret.isconst);
    })?
    ;

prototype_params returns [ List<PrototypeParameterDeclaration> params ]
@init{
  $params = new ArrayList<PrototypeParameterDeclaration>();
}
    : ^(DATA_PARAMS (prototype_param { $params.add($prototype_param.param); })+)
    ;

prototype_param returns [ PrototypeParameterDeclaration param ]
@init{
  $param = null;
  String name = "";
}
    : ^(DATA_PARAM
          data_type
          (simple_name { name = $simple_name.name; })?
          {
            Type dt = $data_type.datatype;
            PrototypeParameterDeclaration pdpd =
            	PackagingFactory.eINSTANCE.createPrototypeParameterDeclaration();

            setSourceInfo(pdpd, $start);
            pdpd.setName(name);
            pdpd.setType(dt);
            pdpd.setConst($data_type.isconst);

            $param = pdpd;
          })
    ;
    
annotation_param returns [ String name, String value ]
    :
      ^(ANNOTATION_PARAM k=ID)      {$name = $k.text.trim(); $value = "true";}
    | ^(ANNOTATION_PARAM k=ID (v=STRING|v=ID|v=TRUE|v=FALSE)) {$name = $k.text.trim(); $value= $v.text.trim();}
    ;

annotation returns [ String name, BipAnnotation bipannotation ]
@init{
  $bipannotation = AnnotationFactory.eINSTANCE.createBipAnnotation();
}
    : ^(ANNOTATION n=ID {
                          $name = $n.text.trim();
                          $bipannotation.setName($name);
                        }
                        (annotation_param {
                          if ($bipannotation.getParameters().containsKey($annotation_param.name)) {
                             throw new RedefinedAnnotationParameterException(input, $annotation_param.start, $annotation_param.name);
                          }

                          $bipannotation.getParameters().put($annotation_param.name, $annotation_param.value);
                        })*)
    ;

annotations
    : ^(ANNOTATIONS (annotation {
          String name = $annotation.name;
          BipAnnotation bipannotation = $annotation.bipannotation;

          // should have at least one element to annotate
          assert(!$AnnotatedScope::elements.isEmpty());

          for (AnnotatedElement element : $AnnotatedScope::elements) {
            if (element.getBipAnnotations().containsKey(name)) {
              throw new RedefinedAnnotationException(input, $annotation.start, element.getBipAnnotations().get(name), name);
            }

            BipAnnotation copyOfbipannotation = EcoreUtil.copy(bipannotation);

            // /!\ BIG WARNING: manual copy of source info
            // source info are not copied by EcoreUtil.copy(),
            // since AnnotatedEObject is a custom class
            setSourceInfo(copyOfbipannotation, $annotation.start);
            element.getBipAnnotations().put(name, copyOfbipannotation);
          }
        })+)
    ;

annotated_bip_type_definition
scope AnnotatedScope;
@init{
  initAnnotatedScope();
}
    : ^(ANNOTATED_TYPE
        bip_type_definition {
          addElementToAnnotate($bip_type_definition.type);
        }
        annotations?)
    ;

bip_type_definition returns [BipType type;]
    : atom_type_definition {
          $type = $atom_type_definition.type;
          $bip_package::parsed_package.getAtomTypes().add($atom_type_definition.type);
      }
    | compound_type_definition {
          $type = $compound_type_definition.type;
          $bip_package::parsed_package.getCompoundTypes().add($compound_type_definition.type);
      }
    | port_type_definition {
          $type = $port_type_definition.type;
          $bip_package::parsed_package.getPortTypes().add($port_type_definition.type);
      }
    | connector_type_definition {
          $type = $connector_type_definition.type;
          $bip_package::parsed_package.getConnectorTypes().add($connector_type_definition.type);
      }
    ;
    
    
annotated_extern_data_type_declaration returns [DataType type]
scope AnnotatedScope;
@init {
  $type = DataFactory.eINSTANCE.createDataType();
  initAnnotatedScope($type);
  setSourceInfo($type, $start);
  $type.setNative(false);
}
  : ^(EXTERN_DATA_TYPE
        simple_name {
           $type.setName($simple_name.name);
           putSymbol($type.getName(), NameSpace.TYPE, $type, input, $start);  
           putSymbol($type.getName(), NameSpace.EXPORTED_TYPE, $type, input, $start);
           $bip_package::parsed_package.getDataTypes().add($type);
        }
        (^(REFINE (data_type_reference { $type.getSuperTypes().add($data_type_reference.datatype); } )+))?
        (^(AS backend_name=STRING { $type.setBackendName($backend_name.text.substring(1, $backend_name.text.length() - 1)); } ))? annotations?
    )
  ;
    
annotated_extern_prototype_declaration
    : annotated_extern_function_prototype_definition {
          $bip_package::parsed_package.getPrototypes().add($annotated_extern_function_prototype_definition.prototype);
      }
    | annotated_extern_binary_operator_prototype_definition {
          $bip_package::parsed_package.getPrototypes().add($annotated_extern_binary_operator_prototype_definition.prototype);
      }
    | annotated_extern_unary_operator_prototype_definition {
          $bip_package::parsed_package.getPrototypes().add($annotated_extern_unary_operator_prototype_definition.prototype);
      }
    ;
