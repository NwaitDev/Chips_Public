/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
 *  Anna Gallone (anna.galdel@protonmail.com)
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

package ujf.verimag.bip.parser.loader;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Stack;

import org.antlr.runtime.ANTLRInputStream;
import org.antlr.runtime.CharStream;
import org.antlr.runtime.CommonTokenStream;
import org.antlr.runtime.RecognitionException;
import org.antlr.runtime.tree.CommonTree;
import org.antlr.runtime.tree.CommonTreeNodeStream;
import org.eclipse.emf.common.util.Diagnostic;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.emf.ecore.util.Diagnostician;
import org.eclipse.emf.ecore.xmi.impl.EcoreResourceFactoryImpl;
import org.eclipse.emf.ecore.xmi.impl.XMIResourceFactoryImpl;
import org.eclipse.emf.ecore.xmi.impl.XMLResourceFactoryImpl;

import ujf.verimag.bip.error.GenericError;
import ujf.verimag.bip.error.message.ErrorCodeEnum;
import ujf.verimag.bip.error.message.ErrorSeverity;
import ujf.verimag.bip.metamodel.AnnotatedEObject;
import ujf.verimag.bip.parser.Bip2Lexer;
import ujf.verimag.bip.parser.Bip2Parser;
import ujf.verimag.bip.parser.Bip2Walker;
import ujf.verimag.bip.parser.error.DiagnosticError;
import ujf.verimag.bip.parser.error.ParserOrLexerError;
import ujf.verimag.bip.parser.loader.error.CycleFoundInPackageDep;
import ujf.verimag.bip.parser.loader.error.PackageNameDoesNotMatchFileName;
import ujf.verimag.bip.parser.loader.error.PackageNotFoundError;
import ujf.verimag.bip.parser.loader.error.PackageNotLoaded;
import ujf.verimag.bip.parser.registry.PackageAlreadyRegisteredException;
import ujf.verimag.bip.parser.registry.PackageRegistry;
import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataType;
import bip2.ujf.verimag.bip.packaging.BipPackage;
import bip2.ujf.verimag.bip.types.AtomType;
import bip2.ujf.verimag.bip.types.ComponentType;
import bip2.ujf.verimag.bip.types.CompoundType;
import bip2.ujf.verimag.bip.types.ConnectorType;
import bip2.ujf.verimag.bip.types.PortType;
import bip2.ujf.verimag.bip.packaging.BipPackage;
import bip2.ujf.verimag.bip.packaging.PackagingFactory;
import bip2.Bip2Package;
/**
 * The package loaded is used for loading and keeping track of loaded packages.
 * It has a similar role as the java class loader. Mainly, it takes care of returning
 * a valid package when given a package name. It is responsible for using
 * caching techniques, calling the parser, etc.
 */
public class PackageLoader {

    /**
     * The registry that keeps track of packages.
     */
    protected PackageRegistry registry = new PackageRegistry();
    
    /**
     * The loader is kind of "re-entrant", meaning that it may call itself.
     * This stack keeps track of all calls, the last being at the top of the stack.
     */
    private Stack<String> beingLoadedPackage = new Stack<String>();

    /**
     * Used to store the URL to the files being parsed. Could be merged with
     * previous stack ?
     */
    private Stack<URL> fileParsed = new Stack<URL>();
    
    
    /**
     * Keep track of errors/warnings found since last purge
     */
    private List<GenericError> errors = new ArrayList<GenericError>();
    
    public void purgeErrors() {
        this.errors = new ArrayList<GenericError>();
    }
    
    public List<GenericError> getErrors() {
        return errors;
    }
    
    /**
     * The URLClassLoader used to locate BIP files. As described earlier, the
     * package loader is very similar to a class loader. In fact, it relies on
     * a class loeader to handle the file location service.
     */
    protected URLClassLoader classloader; 
    
    /**
     * FIXME: add comment about the role of the map of symbols
     */
    protected Map<AnnotatedEObject, Bip2Walker.SymbolTable> globalSymbolMap = new HashMap<AnnotatedEObject, Bip2Walker.SymbolTable>();
    public Map<AnnotatedEObject, Bip2Walker.SymbolTable> getGlobalSymbolMap() { return this.globalSymbolMap; }
    
    /**
     * Create a new PackageLoader with an unmutable set of search paths.
     * @param includePaths list of search paths
     */
    public PackageLoader(URL[] includePaths){
        this.classloader = new URLClassLoader(includePaths, null);
    }
    
    /**
     * Get the number of currently loaded package
     * @return the number of loaded packages
     */
    public int packageCount(){
        return this.registry.packageCount();
    }
    
    /**
     * Locate a package and returns its path (beware that the path can contain URL protocol)
     * @param name the package name
     * @return the path to the package, null if it can't be located.
     */
    protected String locatePackage(String name){
        String p = name.replace('.', '/') + ".bip";
        URL url = this.classloader.getResource(p);
        if (url != null)
            return url.getPath();
        else
            return null;
    }
    
    /**
     * Utility method, mainly used for debugging, that calls EMF serialization
     * service.
     * @param filename the filename in which to output the result
     * @param pack the package to serialize
     */
    protected void serializePackage(String filename, BipPackage pack){
        // create resource set and resource 
        ResourceSet resourceSet = new ResourceSetImpl();

        // Register XML resource factory
        resourceSet.getResourceFactoryRegistry().getExtensionToFactoryMap().put("xmi", 
                new XMIResourceFactoryImpl());
        resourceSet.getResourceFactoryRegistry().getExtensionToFactoryMap().put("ecore", 
                new EcoreResourceFactoryImpl());
        resourceSet.getResourceFactoryRegistry().getExtensionToFactoryMap().put("xml", 
                new XMLResourceFactoryImpl());
        
        Resource resource = resourceSet.createResource(URI.createFileURI(filename));
        // add the root object to the resource
        resource.getContents().add(pack);
        // serialize resource you can specify also serialization
        // options which defined on org.eclipse.emf.ecore.xmi.XMIResource
        try {
          resource.save(null);
        } catch (IOException e) {}
    }

    /**
     * Utility method to extract a backend interpretable bip data structure
     * from a .xmi file respecting the BIP.ecore metamodel.
     * (/!\ This method is not the rigorous inverse of PackageLoader.serializePackage)
     * @param filename the name of the xmi file that contains a serialized bip model specification
     * @return A BipPackage object that can be compiled through the middle-end and back-end layers of the bip compiler 
     */
    public BipPackage deserializePackage(String filename) throws Exception {
        // create resource set and resource 
        ResourceSet resourceSet = new ResourceSetImpl();

        // Register XML resource factory
        resourceSet.getResourceFactoryRegistry().getExtensionToFactoryMap().put("xmi", 
                new XMIResourceFactoryImpl());

        EPackage.Registry.INSTANCE.put(Bip2Package.eNS_URI, Bip2Package.eINSTANCE);
        URI fileUri = URI.createFileURI(new File(filename).getAbsolutePath());
        Resource resource = resourceSet.getResource(fileUri,true);
        
        // The root object of a serialized BipPackage should be the first content element
        EObject root = resource.getContents().get(0);
        
        if (!(root instanceof BipPackage)) {
            throw new LoadPackageException("Root element is not a BipPackage, found: " 
            + root.eClass().getName());
        }

        BipPackage pack = (BipPackage) root;
        this.registry.registerPackage(pack);
        return pack;
    }
    /**
     * Locate a package and returns an InputStream
     * @param name the package name
     * @return an InputStream for the file corresponding to the package, null if it can't be located.
     */
    protected InputStream locatePackageAsStream(String name, boolean setParsedFile){
        String p = name.replace('.', '/') + ".bip";
        InputStream stream = this.classloader.getResourceAsStream(p);
        if (stream != null){
            URL url = this.classloader.getResource(p);
            this.fileParsed.push(url);
        }
        return stream;
    }

    /**
     * Returns the model object for a given BIP package. If the package is not
     * loaded and 'load' argument is set to true, the package will be looked up
     * and loaded if possible.
     * 
     * @param name
     *            the package name
     * @param load
     *            if true and package is not loaded, try to load it
     * @return the BipPackage object for the package
     * @throws LoadPackageException
     *             if the package is not loaded or can't be loaded.
     */
    public BipPackage getPackage(String name, boolean load) throws LoadPackageException {
        return getPackage(name, load, true);
    }

    /**
     * Returns the model object for a given BIP package. If the package is not
     * loaded and 'load' argument is set to true, the package will be looked up
     * and loaded if possible.
     * 
     * @param name
     *            the package name
     * @param load
     *            if true and package is not loaded, try to load it
     * @param validate if true, model is validated
     * @return the BipPackage object for the package
     * @throws LoadPackageException
     *             if the package is not loaded or can't be loaded.
     */
    public BipPackage getPackage(String name, boolean load, boolean validate) throws LoadPackageException {
        BipPackage bp = this.registry.getPackage(name);
        
        if (bp != null) {
            return bp;
        } else if (load) {
            
            if (this.beingLoadedPackage.contains(name)){
                throw new LoadPackageException(new GenericError[]{new CycleFoundInPackageDep(name)});
            } else {
                this.beingLoadedPackage.push(name);
            }
            
            // locatePackageAsStream pushes an URL on fileParsed stack.
            InputStream filestream= locatePackageAsStream(name, true);
            
            if (filestream== null)
                throw new LoadPackageException(new GenericError[]{new PackageNotFoundError(name)});
            try {
                bp = loadPackageStream(filestream, validate);
            } catch (LoadPackageException e){
                this.beingLoadedPackage.pop();
                this.fileParsed.pop();
                throw e;
            }

            if (!name.equals(bp.getName())){
                this.beingLoadedPackage.pop();
                this.fileParsed.pop();
                throw new LoadPackageException(new GenericError[]{new PackageNameDoesNotMatchFileName(bp.getName(), name)});
            }

            this.beingLoadedPackage.pop();
            this.fileParsed.pop();
        } else {
            throw new LoadPackageException(new GenericError[]{new PackageNotLoaded(name)});
        }

        return bp;
    }
    
    /**
     * Find a data declaration within a package by name
     * 
     * @param name
     *            the data declaration name
     * @return the list of ConstDataDeclaration found
     */
    public List<DataDeclaration> getConstDataDeclaration(String name) {
        List<DataDeclaration> cds = new ArrayList<DataDeclaration>();
        
        for (BipPackage bp : this.registry.getPackages()) {
            DataDeclaration cd = bp.getConstDataDeclaration(name);
            
            if (cd != null) {
                cds.add(cd);
            }
        }
        return cds;
    }


    /**
     * Find a port type within a package by name
     * 
     * @param name
     *            the port type name
     * @return the list of PortType found
     */
    public List<PortType> getPortType(String name) {
        List<PortType> pts = new ArrayList<PortType>();
        
        for (BipPackage bp : this.registry.getPackages()) {
            PortType pt = bp.getPortType(name);
            
            if (pt != null) {
                pts.add(pt);
            }
        }
        
        return pts;
    }

    /**
     * Find a connector type within a package by name
     * 
     * @param name
     *            the connector type name
     * @return the list of ConnectorType found
     */
    public List<ConnectorType> getConnectorType(String name) {
        List<ConnectorType> cts = new ArrayList<ConnectorType>();
        
        for (BipPackage bp : this.registry.getPackages()) {
            ConnectorType ct = bp.getConnectorType(name);
            
            if (ct != null) {
                cts.add(ct);
            }
        }
        
        return cts;
    }

    /**
     * Find an atom type within a package by name
     * 
     * @param name
     *            the atom type name
     * @return the list of AtomType found
     */
    public List<AtomType> getAtomType(String name) {
        List<AtomType> ats = new ArrayList<AtomType>();
        
        for (BipPackage bp : this.registry.getPackages()) {
            AtomType at = bp.getAtomType(name);
            if (at != null) {
                ats.add(at);
            }
        }
        
        return ats;
    }

    /**
     * Find a compound type within a package by name
     * 
     * @param name
     *            the compound type name
     * @return the list of CompoundType found
     */
    public List<CompoundType> getCompoundType(String name) {
        List<CompoundType> cts = new ArrayList<CompoundType>();
        
        for (BipPackage bp : this.registry.getPackages()) {
            CompoundType ct = bp.getCompoundType(name);
            
            if (ct != null) {
                cts.add(ct);
            }
        }
        
        return cts;
    }

    /**
     * Find a component type (can be atom or compound) within a package by name
     * 
     * @param name
     *            the component type name
     * @return the list of ComponentType found
     */
    public List<ComponentType> getComponentType(String name) {
        List<ComponentType> cts = new ArrayList<ComponentType>();
        
        cts.addAll(getAtomType(name));
        cts.addAll(getCompoundType(name));
        
        return cts;
    }

    /**
     * Find a data type within a package by name
     * 
     * @param name
     *            the data type name
     * @return the list DataType found
     */
    public List<DataType> getDataType(String name) {
        List<DataType> dts = new ArrayList<DataType>();
        
        for (BipPackage bp : this.registry.getPackages()) {
            DataType dt = bp.getDataType(name);
            
            if (dt != null) {
                dts.add(dt);
            }
        }
        
        return dts;
    }
    
    /**
     * Loads (ie. parse) a package from an InputStream
     * @param filestream a stream containing BIP source
     * @param validate if true, model is validated
     * @return the corresponding BipPackage
     * @throws LoadPackageException in case the BIP can't be loaded
     */
    public BipPackage loadPackageStream(InputStream filestream, boolean validate) throws LoadPackageException {
        CharStream input = null;

        try {
            input = new ANTLRInputStream(filestream);
            assert(input != null);
            return loadPackageFromCharStream(input, validate);
        } catch (IOException e) {
            throw new LoadPackageException(e);
        }
    }
    
    /*
     * This method has been commented out as it lacks correct integration with
     * other parts of the loader.
     * Currently, it should be integrated with getPackage so as to
     * set correctly the stacks fileParsed & beingLoaded.
     */
//   /**
//     * Loads (ie. parse) a package from a file
//     * @param filename a file name containing BIP source
//     * @return the corresponding BipPackage
//     * @throws LoadPackageException in case the BIP can't be loaded
//     */
//    public BipPackage loadPackageFile(String filename) throws LoadPackageException {
//        CharStream input = null;
//        try {
//            this.fileParsed.push(new URL(filename));
//        } catch (MalformedURLException e1) {
//            e1.printStackTrace();
//            throw new LoadPackageException("");
//        }
//        
//        try {
//            input = new ANTLRFileStream(filename);
//            assert(input != null);
//            BipPackage pack =loadPackageFromCharStream(input);
//            
//            return pack;
//        } catch (IOException e) {
//            throw new LoadPackageException(e);
//        } catch (LoadPackageException e){
//            throw new LoadPackageException(e.getMessage() + "in file " + filename);
//        }
//    }
    
    /**
     * Loads a package from an Antlr CharStream (ANTLRFileStream or ANTLRInputStream)
     * @param charstream the charstream 
     * @param validate if true, model is validated
     * @return the corresponding BipPackage model
     * @throws LoadPackageException if the package can't be loaded
     */
    protected BipPackage loadPackageFromCharStream(CharStream charstream, boolean validate) throws LoadPackageException {
        CharStream input = charstream;
        
        Bip2Lexer lexer = new Bip2Lexer(input);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        Bip2Parser parser = new Bip2Parser(tokens);

        Bip2Parser.bip_package_return bfr = null;
        
//        ErrorStringifier errorStringifier = new ErrorStringifier();
        List<ParserOrLexerError> perrors = new ArrayList<ParserOrLexerError>();
        
        try {
            bfr = parser.bip_package();
        } catch (RecognitionException e) {
            // means we have an error in the lexer, get errors directly from it as parser does NOT catch exception from lexer.
            // This is done below, after the catch() block.
        }
        perrors.addAll(lexer.errors);
        perrors.addAll(parser.errors);
        
        /*
         * PLEASE READ THIS.
         * Error handling from parser and upper layers are handled by means of exceptions, and it works great.
         * Error from below (ie. lexer) are not nicely handled, and antlr does not provide a way to do better.
         * In particular, the lexer raises an exception, but it is not catched by the parser. That's why we catch it here.
         * 
         * See : http://markmail.org/message/r6fqwebcor3bw37y#query:related%3Ar6fqwebcor3bw37y+page:1+mid:r6fqwebcor3bw37y+state:results
         * Message from "Tim Halloran" [antlr-interest] How does one suppress 'no viable alternative at character' warning messages
         * Published Sep 17, 2008 11:14:10 am
         * 
         * If you enter the catch above, it means an error was found by the lexer:
         *  => get the list of registered error directly from the lexer.
         * 
         * The following 'if' simply checks if the list is set or not:
         *  - if set, then error in the lexer
         *  - if not set, then proceed normally (check for errors in parser and so on)
         */
        int errors;
        
        errors = parser.getNumberOfSyntaxErrors() + lexer.getNumberOfSyntaxErrors();
        
        if (errors > 0) {
            
            if (perrors.size() != errors){
                // Don't stop the execution as the compiler should already bail out anyway.
                System.out.println("******** Error with error handling, some errors not reported correctly.");
            }
            for (ParserOrLexerError pole : perrors){
                if (pole.getSourceFile() == null){
                    pole.setSourceFile(fileParsed.peek());
                }
            }
            throw new LoadPackageException(perrors.toArray(new ParserOrLexerError[0]));
        }

        CommonTree t = (CommonTree) bfr.getTree();
        CommonTreeNodeStream nodes = new CommonTreeNodeStream(t);
        nodes.setTokenStream(tokens);

        Bip2Walker walker = new Bip2Walker(nodes);
        walker.setLoader(this);
        walker.setParsedFileURL(fileParsed.peek());
        walker.setGlobalSymbolMap(this.globalSymbolMap);
        try {
            walker.bip_package();
        } catch (RecognitionException e) {
            // do nothing, it should be handled by some try/catch higher in the walker.
            // error should be registered..
            // throw new LoadPackageException(e);
        }

        errors = walker.getNumberOfSyntaxErrors();
        if (errors > 0) {
//            StringBuffer sb = new StringBuffer();
            
            List<ParserOrLexerError> plerrors = walker.errors;
            if (plerrors.size() != errors){
                // Don't stop the execution as the compiler should already bail out anyway.
                System.out.println("******** Error with error handling, some errors not reported correctly.");
            }
            for (ParserOrLexerError pole : plerrors){
                if (pole.getSourceFile() == null){
                    pole.setSourceFile(fileParsed.peek());
                }
            }

            /*
             * special treatment for cycle : instead of creating new object,
             * stack packages (build the cycle) and throw the same error object
             * again & again.
             */
            if (plerrors.size() == 1 && 
                    plerrors.get(0).errorcode == ErrorCodeEnum.LoadPackage && 
                    plerrors.get(0).getAntlrException() instanceof ujf.verimag.bip.parser.error.LoadPackageException &&
                    ((ujf.verimag.bip.parser.error.LoadPackageException)plerrors.get(0).getAntlrException()).getLoaderException().getErrors().length == 1 &&
                    ((ujf.verimag.bip.parser.error.LoadPackageException)plerrors.get(0).getAntlrException()).getLoaderException().getErrors()[0].errorcode == ErrorCodeEnum.CycleFoundInPackageDep){
                CycleFoundInPackageDep e = (CycleFoundInPackageDep)((ujf.verimag.bip.parser.error.LoadPackageException)plerrors.get(0).getAntlrException()).getLoaderException().getErrors()[0];
                e.path_to_cycle.push(this.beingLoadedPackage.peek());
              throw new LoadPackageException(new GenericError[]{e});
            }

            throw new LoadPackageException(plerrors.toArray(new ParserOrLexerError[0]));
        }

        DiagnosticError[] derrors = new DiagnosticError[0];
        if (validate)
            derrors = validateType(walker.parsed_package);

        boolean fatal_error_found = false;
        for (DiagnosticError de : derrors){
            this.errors.add(de);
            if (de.severity == ErrorSeverity.FATAL){
                fatal_error_found = true;
            }
        }

        if (derrors.length > 0 && fatal_error_found) {            
            throw new LoadPackageException(getErrors().toArray(new GenericError[0]));
        } else {
            BipPackage loaded_package = walker.parsed_package;
            try {
                this.registry.registerPackage(loaded_package);
            } catch (PackageAlreadyRegisteredException e) {
                throw new LoadPackageException(e);
            }

            return loaded_package;
        }
    }
    
    protected boolean before(DiagnosticError e1, DiagnosticError e2) {
        return e1.getLine() <  e2.getLine() ||
              (e1.getLine() == e2.getLine() && e1.getColumnStart() < e2.getColumnStart());
    }
    
    /**
     * Invokes the EMF validation framework on a given model object.
     * @param type the model object to validate (most probably a BIP type)
     * @return an array with all the errors found.
     */
    public DiagnosticError[] validateType(EObject type) {

        Diagnostic diagnostic = Diagnostician.INSTANCE
                .validate(type);

        if (diagnostic.getSeverity() != Diagnostic.OK) {

            List<DiagnosticError> error_list = new ArrayList<DiagnosticError>();

            if (diagnostic.getSeverity() == Diagnostic.ERROR
                    || diagnostic.getSeverity() == Diagnostic.WARNING) {

                for (Diagnostic d : diagnostic.getChildren()) {
                    switch (d.getSeverity()) {
                    case Diagnostic.ERROR:
                    case Diagnostic.WARNING:
                        DiagnosticError diag_error = new DiagnosticError(d);
                        
                        // insert diag_error in error_list by line number increasing
                        boolean inserted = false;
                        
                        for (int i = 0 ; i < error_list.size() ; i++) {
                            if (before(diag_error, error_list.get(i))) {
                                error_list.add(i, diag_error);
                                inserted = true;
                                break;
                            }
                        }
                        
                        if (!inserted) error_list.add(diag_error);
                    }
                }
            }
            return error_list.toArray(new DiagnosticError[0]);
        }
        return new DiagnosticError[0];
    }

    /**
     * Utility method, mainly used when debugging.
     * Invokes the EMF serialization framework to serialize all loaded type
     * to files in the current working directory.
     * 
     * The file extension is used by EMF to decide which format to use. Only
     * known formats by EMF can be used (eg. ecore, xsd).
     * @param extension the file extension (dictates the inner format for the serialization)
     */
    public void serializeAllPackages(String directory, String extension){
        for (BipPackage bp : this.registry.getPackages()){
            serializePackage(directory + File.separator + bp.getName() + "." + extension, bp);
        }
    }
}
