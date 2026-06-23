/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Anakreontas Mentis
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
 *  Anna Gallone (anna.galdel@protonmail.com)
 * 
 * This software is a computer program whose purpose is to generate
 * executable code from a .bip file a .xmi specification of BIP models.
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

package ujf.verimag.bip.userinterface.cli;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.StringWriter;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;
import java.util.logging.ConsoleHandler;
import java.util.logging.Handler;
import java.util.logging.Level;
import java.util.logging.LogManager;
import java.util.logging.Logger;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.antlr.runtime.ANTLRStringStream;
import org.antlr.runtime.CharStream;
import org.antlr.runtime.CommonTokenStream;
import org.antlr.runtime.RecognitionException;
import org.antlr.runtime.tree.CommonTree;
import org.antlr.runtime.tree.CommonTreeNodeStream;

import bip2.ujf.verimag.bip.actionlang.ActionlangFactory;
import bip2.ujf.verimag.bip.actionlang.DirectBooleanExpression;
import bip2.ujf.verimag.bip.actionlang.DirectFloatExpression;
import bip2.ujf.verimag.bip.actionlang.DirectIntegerExpression;
import bip2.ujf.verimag.bip.actionlang.DirectStringExpression;
import bip2.ujf.verimag.bip.actionlang.ValuedExpression;
import bip2.ujf.verimag.bip.component.ComponentDeclaration;
import bip2.ujf.verimag.bip.component.ComponentFactory;
import bip2.ujf.verimag.bip.instance.ComponentInstance;
import bip2.ujf.verimag.bip.packaging.BipPackage;
import bip2.ujf.verimag.bip.types.ComponentType;
import bip2.ujf.verimag.bip.types.CompoundType;

import ujf.verimag.bip.backend.BackendStatus;
import ujf.verimag.bip.backend.Backendable;
import ujf.verimag.bip.backend.BackendStatusEnum;
import ujf.verimag.bip.backend.error.BackendGenericError;
import ujf.verimag.bip.error.GenericError;
import ujf.verimag.bip.instantiator.Instantiator;
import ujf.verimag.bip.instantiator.InstantiatorException;
import ujf.verimag.bip.instantiator.error.InstantiatorErrorStringifier;
import ujf.verimag.bip.metamodel.AnnotatedEObject;
import ujf.verimag.bip.middleend.FilterStatus;
import ujf.verimag.bip.middleend.FilterStatusEnum;
import ujf.verimag.bip.middleend.Filterable;
import ujf.verimag.bip.middleend.error.FilterGenericError;
import ujf.verimag.bip.parser.Bip2Lexer;
import ujf.verimag.bip.parser.Bip2Parser;
import ujf.verimag.bip.parser.Bip2Walker;
import ujf.verimag.bip.parser.error.DiagnosticError;
import ujf.verimag.bip.parser.error.LoaderErrorStringifier;
import ujf.verimag.bip.parser.error.ParserOrLexerError;
import ujf.verimag.bip.parser.loader.LoadPackageException;
import ujf.verimag.bip.parser.loader.PackageLoader;

import joptsimple.OptionParser;
import joptsimple.OptionSet;
import joptsimple.OptionSpec;

/**
 * This is the main class for the command line interface.
 * It is responsible for loading/configuring the different parts of the
 * compiler, binding them together and executing them.
 * It also takes care of error handling as they are surfacing.
 * 
 * The flow of execution is the following:
 *  - get low level configuration from java property (this includes backends to load)
 *  - load backend classes and do the early configuration part (get cli parameters)
 *  - parse command line arguments
 *  - configure all backends (give them the handle to parsed arguments)
 *  - call the PackageLoader on the top level package (cli param)
 *  - if an instance graph is requested, call the Instantiator
 *  - if any backend used, sequentially call them for both type graph and instance graph (if they support them).
 *
 * In any case, if an error is reported, it should be wrapped in an error/exception
 * class defined in ujf.verimag.bip.parser.error package.
 */
public class Runner {
    protected Logger logger = Logger.getLogger("ujf.userinterface.cli");

    /**
     * The following two vars are used to declare command line arguments The
     * first one is used for arg with no parameters (on/off switches). Its
     * format is the following: { <option name>, <description> } The name can be
     * long ('--blabla') or short ('-f'). It's automatically handled.
     * 
     * The second one is used for arg with string parameters. It also takes care
     * of synonyms. The format is the following: { <option name 1>, <option name
     * 2>, ..., <description>} The different names can be long or short. The
     * result (parameters) are gathered in a map indexed by the first name
     * *only*. The map is called ospecs.
     * 
     * If you are using arg that can be repeated (like '-I'), you get an array
     * with all values with: options.valuesOf(ospecs.get("I")) If the option can
     * be used only once, use: options.valueOf(ospecs.get("model"));
     * 
     * - Repeated 'non parameterized' option are not handled. - all parameters
     * are considered as string
     */
    private String[][] options_no_params = {
            { "h", "displays help message"},
            { "Werr", "make all warnings into errors (same as gcc's -Werr)"},
            { "profile", "Simple profiling of compiler internals (implies -v FINER)."},
            { "skip-validation", "Skip model validation: DANGEROUS."},
            { "version", "display compiler version info"},
    };

    private String[][] options_with_param_string = {
            { "v",
                    "verbose level: FINEST, FINER, FINE, CONFIG, INFO, WARNING, SEVERE" },
            { "p", "package to compile" },
            { "xmi", "xmi file to compile (cannot be used along with -p or -I, the model must be a single self containd package)" },
            { "e", "error strings file name"},
            { "d", "component definition to use for root instance" },
            { "I", "add a directory to the include paths [can be used more than once]" },
            { "f", "filter", "filter chain specification"},
            { "filter-file", "read filter chain specification from file (ignored if -f is given)"},
            { "s", "serialization format: ecore, xml, xmi." },
            { "so", "serialization output directory"}
            };

    /**
     * Gather all options without parameters from back-ends
     */
    private List<String[]> extraParamsWithNoOpt = new ArrayList<String[]>();

    /**
     * Gather all options with parameters from back-ends
     */
    private List<String[]> extraParamsWithOpt = new ArrayList<String[]>();

    private Map<String, OptionSpec<String>> ospecs = new HashMap<String, OptionSpec<String>>();
    private OptionParser parser = new OptionParser();

    
    private Map<String, Class<?>> all_backend_classes = new HashMap<String, Class<?>>();
    private Map<String, Class<?>> all_filter_classes = new HashMap<String, Class<?>>();
    private Map<String, Class<?>> filter_classes = new HashMap<String, Class<?>>();
    private Map<String, Class<?>> backend_classes = new HashMap<String, Class<?>>();
    
    private Map<String, Backendable> abstract_backends = new HashMap<String, Backendable>();

    /**
     * The package loader object
     */
    private PackageLoader pl;
    
    private String rootDefinition;
    private String rootPackageName;
    private boolean xmiMode = false;

    /*
     * Holds filter chain specs (from command line)
     * and filters after chain has been build.
     */
    private String filters_chain_spec;
    private List<Filterable> filters_chain = new ArrayList<Filterable>();
    /**
     * If set to true, treats warnings as errors.
     */
    private boolean werr_flag = false;

    private String serializationFmt = null;
    private String serialization_output = null;

    private boolean skip_validation = false;

    /**
     * If set to true, then profile execution times for some
     * compiler parts
     */
    private boolean profile_compiler = false;
    final HashMap<String, Long> profile_counters = new HashMap<String,Long>();
    
    private LoaderErrorStringifier loaderErrorStringifier;
    private InstantiatorErrorStringifier instantiatorErrorStringifier;

    /**
     * this field contains the result of the instantiator, if applicable
     */
    protected ComponentInstance rootInstance;
    
    public ComponentInstance getRootInstance() {
        return rootInstance;
    }

    /**
     * this field contains the result of the package loader, if applicable
     */
    protected BipPackage rootPackage;

    public BipPackage getRootPackage() {
        return rootPackage;
    }
    
    /**
     * This is used for error management 
     */
    protected List<GenericError> severe_errors;
    protected List<GenericError> warning_errors;
    
    /**
     * Add two set of command line parameters: without and with options
     * 
     * @param paramsWithNoOpt
     *            array of parameters without options
     * @param paramsWithOpt
     *            array of parameters with options
     */
    protected void registerParam(String[][] paramsWithNoOpt,
            String[][] paramsWithOpt) {
        if (paramsWithNoOpt != null) {
            for (String[] p : paramsWithNoOpt) {
                extraParamsWithNoOpt.add(p);
            }
        }
        if (paramsWithOpt != null) {
            for (String[] p : paramsWithOpt) {
                extraParamsWithOpt.add(p);
            }
        }
    }

    /**
     * Display a message and exit. If the exit status reports an error (not 0)
     * then the message is displayed on standard error. If no error is reported
     * (0), then standard out is used.
     * 
     * @param message
     *            the text to display before exiting
     * @param exitcode
     *            the exit status
     */
    protected void bailOut(String message, int exitcode) {
        Level level = (exitcode != 0) ? Level.SEVERE : Level.INFO;
        
        if (message != null)
            logger.log(level, message);

        System.exit(exitcode);
    }

    /**
     * Display a message, all the command line arguments and exit. If the exit
     * status reports an error (not 0) then the message is displayed on standard
     * error. If no error is reported (0), then standard out is used.
     * 
     * @param message
     *            the text to display before exiting
     * @param parser
     *            the parser object
     * @param exitcode
     *            the exit status
     * @throws IOException
     *             if an error occurs when printing the command line arguments.
     */
    protected void bailOutParser(String message, OptionParser parser,
            int exitcode) throws IOException {
        Level level = (exitcode != 0) ? Level.SEVERE : Level.INFO;
        
        StringWriter sw = new StringWriter();
        parser.printHelpOn(sw);
        logger.log(level, sw.toString());
        
        if (message != null)
            logger.log(level, message);

        System.exit(exitcode);
    }

    /**
     * Initialize the parser from the 2 arrays containing the arguments with and
     * without parameters.
     */
    private void initParser(){
        for (String[] opt : options_no_params){
            assert(opt.length == 2) : "Options with params must only have opt name + description";
            parser.accepts( opt[0], opt[1]);
        }

        for (String[] opt : options_with_param_string){
            assert(opt.length >= 2) : "Options with params must have one or" +
            " more opt name + description";
            Set<String> ts = new TreeSet<String>();
            for (int opt_idx=0; opt_idx<opt.length-1; opt_idx++){
                ts.add(opt[opt_idx]);
            }
            OptionSpec<String> tmpos = parser.acceptsAll( ts, opt[opt.length-1]).withRequiredArg().ofType(String.class);
            ospecs.put(opt[0], tmpos);
        }
    }

    /**
     * Get the list of the backends to use from a property, find the
     * corresponding classes and initialize the parser from optional static
     * attributes in these classes.
     * No instantiation is taking place here.
     */
    void initParserFromBackends(){
        String backends_str = System.getProperty("bip.compiler.backends");
        if (backends_str == null){
            backends_str = "";
        }

        // Load backends and initialize parser
        String [] backends = backends_str.split(";");

        List<String> backends_str_list = new ArrayList<String>();
        List<String> all_backends = new ArrayList<String>();

        for (String s : backends) {
            if (!s.isEmpty()) {
                backends_str_list.add(s);
            }
        }

        all_backends.addAll(backends_str_list);

        for (String backend : all_backends) {
            try {
                Class<?> backend_class = Class.forName(backend);
                backend_classes.put(backend, backend_class);

                String[][] without_p = new String[0][0];
                String[][] with_p = new String[0][0];

                try {
                    without_p = (String[][]) backend_class.getField(
                            "backend_options_with_no_params").get(null);
                } catch (NoSuchFieldException e) {
                    logger.log(Level.FINEST, "Backend " + backend
                            + " does not declare cli options without params");
                }
                try {
                    with_p = (String[][]) backend_class.getField(
                            "backend_options_with_params").get(null);
                } catch (NoSuchFieldException e) {
                    logger.log(Level.FINEST, "Backend " + backend
                            + " does not declare cli options with params");
                }
                registerParam(without_p, with_p);

            } catch (ClassNotFoundException e) {
                bailOut("Can't load backend: " + backend
                        + "! Check classpath or backend name!", -1);
            } catch (Exception e) {
                e.printStackTrace();
                bailOut("Unexpected problem when loading backend " + backend,
                        -1);
            }
        }

        all_backend_classes.putAll(backend_classes);

        for (String[] opt : extraParamsWithNoOpt) {
            assert (opt.length == 2) : "Options with params must only have opt name + description";
            parser.accepts(opt[0], opt[1]);
        }
        for (String[] opt : extraParamsWithOpt) {
            assert (opt.length >= 2) : "Options with params must have one or"
                    + " more opt name + description";
            Set<String> ts = new TreeSet<String>();
            for (int opt_idx = 0; opt_idx < opt.length - 1; opt_idx++) {
                ts.add(opt[opt_idx]);
            }
            OptionSpec<String> tmpos = parser
                    .acceptsAll(ts, opt[opt.length - 1]).withRequiredArg()
                    .ofType(String.class);
            ospecs.put(opt[0], tmpos);
        }
    }
    
    /**
     * Get the list of the filters to use from a property, find the
     * corresponding classes and initialize the parser from optional static
     * attributes in these classes.
     * No instantiation is taking place here.
     */
    void initParserFromFilters(){
        String filters_str = System.getProperty("bip.compiler.filters");
        if (filters_str== null){
            filters_str = "";
        }

        // Load filters and initialize parser
        String [] filters= filters_str.split(";");

        List<String> filters_str_list = new ArrayList<String>();

        List<String> all_filters = new ArrayList<String>();
        for (String s : filters) {
            if (!s.isEmpty()) {
                filters_str_list.add(s);
            }
        }

        all_filters.addAll(filters_str_list);

        for (String filter : all_filters) {
            try {
                Class<?> filter_class = Class.forName(filter);
                filter_classes.put(filter, filter_class);

                String[][] without_p = new String[0][0];
                String[][] with_p = new String[0][0];

                try {
                    without_p = (String[][]) filter_class.getField(
                            "filter_options_with_no_params").get(null);
                } catch (NoSuchFieldException e) {
                    logger.log(Level.FINEST, "Filter " + filter
                            + " does not declare cli options without params");
                }
                try {
                    with_p = (String[][]) filter_class.getField(
                            "filter_options_with_params").get(null);
                } catch (NoSuchFieldException e) {
                    logger.log(Level.FINEST, "Filter" + filter
                            + " does not declare cli options with params");
                }
                registerParam(without_p, with_p);

            } catch (ClassNotFoundException e) {
                bailOut("Can't load filter: " + filter
                        + "! Check classpath or filtername!", -1);
            } catch (Exception e) {
                e.printStackTrace();
                bailOut("Unexpected problem when loading filter" + filter,
                        -1);
            }
        }

        all_filter_classes.putAll(filter_classes);

        for (String[] opt : extraParamsWithNoOpt) {
            assert (opt.length == 2) : "Options with params must only have opt name + description";
            parser.accepts(opt[0], opt[1]);
        }
        for (String[] opt : extraParamsWithOpt) {
            assert (opt.length >= 2) : "Options with params must have one or"
                    + " more opt name + description";
            Set<String> ts = new TreeSet<String>();
            for (int opt_idx = 0; opt_idx < opt.length - 1; opt_idx++) {
                ts.add(opt[opt_idx]);
            }
            OptionSpec<String> tmpos = parser
                    .acceptsAll(ts, opt[opt.length - 1]).withRequiredArg()
                    .ofType(String.class);
            ospecs.put(opt[0], tmpos);
        }
    }
    
    /**
     * Loads the backends:
     * <ul>
     * <li>finds the constructor</li>
     * <li>creates one instances of each backend</li>
     * </ul>
     */
    void loadBackends(OptionSet options, Map<String, OptionSpec<String>> ospecs){
        Object[] constructor_params_instances = new Object[0];

        for (Map.Entry<String, Class<?>> backend_class_kv: all_backend_classes.entrySet()){
            Class<?>[]  constructor_params = new Class[0];

            try {
                    @SuppressWarnings("unchecked")
                    Constructor<Backendable> constructor = (Constructor<Backendable>) backend_class_kv.getValue().getConstructor(constructor_params);
                    Backendable ab = constructor.newInstance(constructor_params_instances);
                    logger.log(Level.FINEST, "Backend instanciated : " + backend_class_kv.getValue().getSimpleName());
                    GenericError[] backend_conf_errors = ab.configure(options, ospecs);
                    logger.log(Level.FINEST, "Backend configured.");
                    
                    if (backend_conf_errors.length > 0){
                        for (GenericError ge : backend_conf_errors){
                            BackendGenericError bge = (BackendGenericError) ge;
                            logger.log(Level.SEVERE, bge.message);
                        }
                        bailOut("Compiler stopping because of error(s) reported by backend", -1);
                    }
                    abstract_backends.put(backend_class_kv.getKey(), ab);
            } catch (SecurityException e) {
                e.printStackTrace();
                bailOut("Security error", -1);
            } catch (NoSuchMethodException e) {
                bailOut("Backend " + backend_class_kv.getValue().getName() + " does not expose correct constructor", -1);
            } catch (IllegalArgumentException e) {
                e.printStackTrace();
                bailOut("Error creating instance of backend", -1);
            } catch (InstantiationException e) {
                e.printStackTrace();
                bailOut("Error creating instance of backend", -1);
            } catch (IllegalAccessException e) {
                e.printStackTrace();
                bailOut("Error creating instance of backend", -1);
            } catch (InvocationTargetException e) {
                e.printStackTrace();
                bailOut("Error creating instance of backend", -1);
            }
        }
    }

    private void exitSummary(int severe, int warning){
        StringBuffer sb = new StringBuffer();

        if (severe > 0) sb.append(severe + " error(s)");
        if (severe > 0 && warning > 0) sb.append(" and ");
        if (warning > 0) sb.append(warning + " warning(s)");
        logger.log(Level.WARNING, sb.toString());
    }

    /**
     * Loads the filters:
     * <ul>
     * <li>finds the constructor</li>
     * <li>creates one instances of each filter</li>
     * </ul>
     */
    void loadFilters(OptionSet options, Map<String, OptionSpec<String>> ospecs){

        String [] filters = filters_chain_spec.split("!");

        for (String filter_with_param : filters){
//        for (Map.Entry<String, Class<?>> filter_class_kv: all_filter_classes.entrySet()){
            String[] filter_array = filter_with_param.trim().split(" ");
            String filter_name = filter_array[0];
            Map<String,String> parameters = new HashMap<String,String>();

            for (int i=1; i < filter_array.length; i++){
                String[] param_item = filter_array[i].trim().split("=");
                parameters.put(param_item[0], param_item[1]);
            }

            Class<?> filter_class = all_filter_classes.get(filter_name);
            Class<?>[] constructor_params = new Class[]{Map.class};

            Object[] constructor_params_instances = new Object[]{parameters};
            try {
                    @SuppressWarnings("unchecked")
                    Constructor<Filterable> constructor = (Constructor<Filterable>) filter_class.getConstructor(constructor_params);
                    Filterable af = constructor.newInstance(constructor_params_instances);
                    logger.log(Level.FINEST, "Filter instanciated : " + filter_class.getSimpleName());
                    GenericError[] filter_conf_errors = af.configure(options, ospecs);
                    logger.log(Level.FINEST, "Filter configured.");
                    
                    if (filter_conf_errors.length > 0){
                        for (GenericError ge : filter_conf_errors){
                            FilterGenericError bge = (FilterGenericError) ge;
                            logger.log(Level.SEVERE, bge.message);
                        }
                        bailOut("Compiler stopping because of error(s) reported by filter", -1);
                    }
                    filters_chain.add(af);
            } catch (SecurityException e) {
                e.printStackTrace();
                bailOut("Security error", -1);
            } catch (NoSuchMethodException e) {
                bailOut("Filter " + filter_name + " does not expose correct constructor", -1);
            } catch (IllegalArgumentException e) {
                e.printStackTrace();
                bailOut("Error creating instance of filter", -1);
            } catch (InstantiationException e) {
                e.printStackTrace();
                bailOut("Error creating instance of filter", -1);
            } catch (IllegalAccessException e) {
                e.printStackTrace();
                bailOut("Error creating instance of filter", -1);
            } catch (InvocationTargetException e) {
                e.printStackTrace();
                bailOut("Error creating instance of filter", -1);
            }
        }
    }

    /**
     * Executes the loaded backends. Each backend is tested for its enabled
     * status & capabilities before executing it.
     * 
     * @param pack
     *            the <it>root</it> package to generate. Must be provided.
     * @param instance
     *            the <it>root</it> instance, if it exists. If null, no backend
     *            will be executed to generate something from instance.
     */
    void executeBackends(BipPackage pack, ComponentInstance instance) {
        logger.log(Level.FINEST, "executeBackends");
        for (Map.Entry<String, Backendable> abe_kv : abstract_backends
                .entrySet()) {
            Backendable backend = abe_kv.getValue();
            String backend_id = abe_kv.getKey();
            boolean dirty = false;
            
            try {
                if (backend.isEnabled()) {
                    logger.log(Level.FINEST,
                            "Backend enabled : " + backend_id);
                    if (backend.canGenerateFromPackage()){
                        startProfile("BACKEND->TYPES");
                        BackendStatus status = backend.generateFromPackage(pack);
                        if (status.getStatus().equals(BackendStatusEnum.SUCCESS)){
                            stopProfile("BACKEND->TYPES");
                            logger.log(Level.FINEST,backend_id + 
                                    " backend successfuly generated types for package");
                        } else {
                            dirty = true;
                            logger.log(Level.SEVERE, backend_id + 
                                    " backend failed to generate types for package");
                        }
                    }
                    if (!dirty && backend.canGenerateFromInstance()){
                        if (instance != null) {
                            startProfile("BACKEND->INSTANCE");
                            BackendStatus status = backend.generateFromInstance(instance);
                            if (status.getStatus().equals(BackendStatusEnum.SUCCESS)){
                                stopProfile("BACKEND->INSTANCE");
                                logger.log(Level.FINEST, backend_id +
                                        " backend successfuly executed for instance");
                            } else {
                                dirty = true;
                                logger.log(Level.SEVERE, backend_id +
                                        "Backend failed execution for instance");
                            }
                        } else {
                            logger.log(Level.FINEST,
                                    "Backend can generate from instance, but no instance provided");
                        }
                    }
                    if (dirty){
                        logger.log(Level.FINEST, "Backend failed : "
                                + backend_id);
                    } else {
                        logger.log(Level.FINEST, "Backend executed successfully : "
                                + backend_id);
                    }
                } else {
                    logger.log(
                            Level.FINEST,
                            "Backend disabled, not executing it : "
                                    + backend_id);
                }
            } catch (Exception e) {
                e.printStackTrace();
                bailOut("Problem when invoking the backend", -1);
            }
        }
    }

    /**
     * Executes the loaded filters.
     * @param pack
     *            the <it>root</it> package to generate. Must be provided.
     */
    void executeFilters(BipPackage pack) {
        for (Filterable filter: filters_chain) {
            String filter_id = filter.getClass().getSimpleName();
            boolean dirty = false;

            try {
                if (filter.isEnabled()) {
                    logger.log(Level.FINEST,
                            "Filter enabled : " + filter_id);
                    FilterStatus status = filter.filterPackage(pack);
                    if (status.getStatus().equals(FilterStatusEnum.SUCCESS)){
                        logger.log(Level.FINEST,filter_id + 
                                   " filter successfuly generated types for package");
                    } else {
                        dirty = true;
                        logger.log(Level.SEVERE, filter_id+ 
                                   " filter failed to filter types for package");
                    }
                } else {
                    logger.log(
                            Level.FINEST,
                            "Filter disabled, not executing it : "
                                    + filter_id);
                }
            } catch (Exception e) {
                e.printStackTrace();
                bailOut("Problem when invoking the filter", -1);
            }
        }
    }

    private void startProfile(final String name){
        if (!profile_compiler) return;
        if (profile_counters.put(name , System.nanoTime()) != null){
            logger.log(Level.FINE, "Error in profiling, counter already started: " + name);
        }
    }

    private void stopProfile(final String name){
        if(!profile_compiler) return;
        if (!profile_counters.containsKey(name)){
            logger.log(Level.FINE, "Error in profiling, counter not started: " + name);
        } else {
            final long profile_counter2 = System.nanoTime();
            final long diff = profile_counter2 - profile_counters.get(name);
            final double dbl_diff = diff/1000000000;
            final String s = String.format("%.4f", dbl_diff);
            logger.log(Level.FINER, "[" + name + "] : " + s + " s");
            profile_counters.remove(name);
        }
    }

    public Runner(String[] args) throws Exception {
        // init errors containers
        this.severe_errors = new ArrayList<GenericError>();
        this.warning_errors = new ArrayList<GenericError>();
        
        
        // Init the parser
        initParser();

        // Get CLI args from filters
        initParserFromFilters();
       
         // Get CLI args from backends
        initParserFromBackends();

        /*
         * Starts real job:
         *  - parsing cli args
         *  - validation of cli args
         *  - fetch input model from .xmi file or parse it from .bip file
         *  - backends invocations
         */
        OptionSet options = null;
        try {
            options = parser.parse(args);
        } catch (joptsimple.OptionException e){
            StringBuffer sb = new StringBuffer();
            
            for (String o: e.options()){
                sb.append('\'' + o + "', ");
            }
            if (!e.options().isEmpty()){
                int l = sb.length();
                sb.delete(l-2, l);
                bailOutParser("Unrecognized option(s): " + sb.toString(), parser, -1);
            } else {
                bailOutParser("Problem with option parsing from command line", parser, -1);
            }
        }
        if (!options.nonOptionArguments().isEmpty()){
            StringBuffer sb = new StringBuffer();
            for (String nonOpt : options.nonOptionArguments()){
                sb.append("[" + nonOpt + "]");
            }
            bailOutParser("Garbage found in command line: " + sb.toString(), parser, -1);
        }

        final List<URL> includeDirectories = new ArrayList<URL>() ;

        if (options.has("h")){
            bailOutParser(null, parser, 0);
        }

        if (options.has("version")){
            bailOut("Version: " + Version.VERSION, 0);
        }

        if (options.has("Werr")){
            werr_flag = true;
        }

        final Logger ujfLogger = Logger.getLogger("ujf");
        final InputStream config_is = Runner.class.getResourceAsStream("/ujf/verimag/bip/userinterface/cli/logger.conf");
        
        if (config_is != null){
            LogManager.getLogManager().readConfiguration(config_is);
        }

        if (options.has(ospecs.get("v"))){
            if (options.valuesOf(ospecs.get("v")).size() > 1){
                bailOutParser("Duplicated verbose level (-v)", parser, -1);
            }
            final String level = options.valueOf(ospecs.get("v"));
            Level newLevel = null;
            // FINEST, FINER, FINE, CONFIG, INFO, WARNING, SEVERE
            if (level.equals("FINEST")){
                newLevel = Level.FINEST;
            } else if (level.equals("FINER")) {
                newLevel = Level.FINER;
            } else if (level.equals("FINE")) {
                newLevel = Level.FINE;
            } else if (level.equals("CONFIG")) {
                newLevel = Level.CONFIG;
            } else if (level.equals("INFO")) {
                newLevel = Level.INFO;
            } else if (level.equals("WARNING")) {
                newLevel = Level.WARNING;
            } else if (level.equals("SEVERE")) {
                newLevel = Level.SEVERE;
            } else {
                bailOutParser("Unrecognized verbose level : " + level, parser, -1);
            }
            ujfLogger.setLevel(newLevel);
        } else {
            ujfLogger.setLevel(Level.WARNING);
        }
        // remove default logging handlers
        Handler[] roothandlers = Logger.getLogger("").getHandlers();

        for (Handler h : roothandlers) {
            Logger.getLogger("").removeHandler(h);
        }

        ConsoleHandler  chandler = new ConsoleHandler();
        chandler.setLevel(ujfLogger.getLevel());
        ujfLogger.addHandler(chandler);

        if (options.has("profile")){
            profile_compiler = true;
            if (ujfLogger.getLevel().intValue() > Level.FINER.intValue()){
                ujfLogger.setLevel(Level.FINER);
                chandler.setLevel(Level.FINER);
            }
            logger.log(Level.FINE, "Enabling compiler profiling");
            startProfile("INIT");
        }


        if (options.has(ospecs.get("s"))) {
            serializationFmt = options.valueOf(ospecs.get("s"));
        }

        if (options.has(ospecs.get("so"))) {
            serialization_output = options.valueOf(ospecs.get("so"));
        }

        if (options.has("skip-validation")) {
            logger.log(Level.INFO, "Will skip model validation: YOU'VE BEEN WARNED");
            skip_validation = true;
        }

        rootPackageName = null;

        if (options.has(ospecs.get("xmi"))){
            if (options.has(ospecs.get("p"))){
                bailOutParser("Incompatible options -p and -xmi", parser, -1);
            }
            // Package name can change but should be the same as the xmi file name
            if (options.valuesOf(ospecs.get("xmi")).size() == 1){
                rootPackageName = options.valueOf(ospecs.get("xmi"));
                xmiMode = true;
            } else {
                if (options.valuesOf(ospecs.get("xmi")).size() == 0)
                    bailOutParser("Missing xmi file", parser, -1);
                else
                    bailOutParser("Duplicated xmi source (-xmi)", parser, -1);
            }
        }

        if (options.has(ospecs.get("p"))){
            if (options.valuesOf(ospecs.get("p")).size() == 1){
                rootPackageName= options.valueOf(ospecs.get("p"));
            } else {
                bailOutParser("Duplicated package (-p)", parser, -1);
            }
        } else {
            if (!options.has(ospecs.get("xmi")))
                bailOutParser("Missing root package or xmi file", parser, -1);
        }

        rootDefinition = null;
        if (options.has(ospecs.get("d"))){
            if (options.valuesOf(ospecs.get("d")).size() > 1){
                bailOutParser("Duplicated root definition specification (-e)", parser, -1);
            }
            rootDefinition = options.valueOf(ospecs.get("d"));
        } else {
            logger.log(Level.INFO, "Using \"mainCompound\" as definition of the root for the model.\n"
            + "If you want to specify another root definition, provide its name using the -d option.");
            rootDefinition = "mainCompound";
        }

        
        try {
            if (options.has(ospecs.get("e"))){
                if (options.valuesOf(ospecs.get("e")).size() > 1){
                    bailOutParser("Duplicated error file specification (-e)", parser, -1);
                }
                String errorStringFile = options.valueOf(ospecs.get("e"));
                loaderErrorStringifier = new LoaderErrorStringifier(new File(errorStringFile));
                instantiatorErrorStringifier = new InstantiatorErrorStringifier(new File(errorStringFile));

            } else {
                loaderErrorStringifier = new LoaderErrorStringifier("/ujf/verimag/bip/error/message/english-strings.properties");
                instantiatorErrorStringifier = new InstantiatorErrorStringifier("/ujf/verimag/bip/error/message/english-strings.properties");
            }
        } catch (IOException e) {
            // default stringifier, with not-so-friendly messages
            loaderErrorStringifier = new LoaderErrorStringifier();
        }

        if (options.has(ospecs.get("I"))){
            if (options.has(ospecs.get("xmi"))){
                bailOutParser("Incompatible options -I and -xmi", parser, -1);
            }
            for (String s: options.valuesOf(ospecs.get("I"))){
                File f = new File(s);
                if (!f.exists()){
                    logger.log(Level.WARNING, "Directory: " + s + " does not exist.");
                } else if (!f.isDirectory()){
                    logger.log(Level.WARNING,s + " is not a directory.");
                }
                includeDirectories.add(f.toURI().toURL());
            }
        }

        if (options.has(ospecs.get("f"))){
            if (options.valuesOf(ospecs.get("f")).size() > 1){
                bailOutParser("Duplicated filter chain specification (-f)", parser, -1);
            }
            filters_chain_spec = options.valueOf(ospecs.get("f"));
            logger.log(Level.FINEST, "Filter chain given, loading filters.");
            // creates filter objects
            loadFilters(options, ospecs);
        } else if (options.has(ospecs.get("filter-file"))) {
            if (options.valuesOf(ospecs.get("filter-file")).size() > 1){
                bailOutParser("Duplicated filter chain file specification (--filter-file)", parser, -1);
            }
            logger.log(Level.FINEST, "Filter chain to be read from file, loading filters.");
            String filter_file_name = options.valueOf(ospecs.get("filter-file"));

            try {
                final BufferedReader br = new BufferedReader(new FileReader(filter_file_name));
                final StringBuffer sb = new StringBuffer();
                String b = br.readLine();
                while (b != null){
                    sb.append(b.trim());
                    b = br.readLine();
                }
                filters_chain_spec = sb.toString();
                loadFilters(options, ospecs);
            } catch(FileNotFoundException fnfe) {
                bailOut("Filter file not found: " + filter_file_name, -1);
            } catch (IOException ioe) {
                bailOut("Error when reading filter file: " + filter_file_name, -1);
            }
        } else {
            logger.log(Level.FINEST, "No filter chain given, NOT loading filters.");
        }

        // creates backend objects
        loadBackends(options, ospecs);
        
        // add current directory in the list of include directories (with lower priority)
        File currentDirectory = new File("./");
        includeDirectories.add(currentDirectory.toURI().toURL());
        
        // create the package loader with path from command line argument -I
        pl = new PackageLoader(includeDirectories.toArray(new URL[0]));

        stopProfile("INIT");
    }
    
    /**
     * 
     */
    private void reportError(GenericError error, boolean isInstantiatorError) {
        if (error.isSilenced) {
            logger.log(Level.FINE, "One Warning/Error silenced.");
        } else {
            String message = "[unable to produce error message for " + error + "]";

            if (isInstantiatorError) {
                message = instantiatorErrorStringifier.stringify(error) + "\n";
            }
            else {
                message = loaderErrorStringifier.stringify(error) + "\n";
            }

            Level l = Level.SEVERE;

            switch (error.severity) {
            case FATAL:
                l = Level.SEVERE;
                break;
                
            case WARNING:
                if (werr_flag) {
                    l = Level.SEVERE;
                }
                else {
                    l = Level.WARNING;
                }
                break;
            }
            
            if (l == Level.SEVERE) {
                this.severe_errors.add(error);
            }
            else {
                this.warning_errors.add(error);
            }
            
            logger.log(l, message);
        }
    }

    private boolean reportErrorsAndSummary(GenericError[] errors) {
        return reportErrorsAndSummary(errors, false);
    }
    
    private boolean reportErrorsAndSummary(GenericError[] errors, boolean isInstantiatorError) {
        for (GenericError error : errors) {
            reportError(error, isInstantiatorError);
        }
        
        if (!this.severe_errors.isEmpty()) {
            exitSummary(severe_errors.size(), warning_errors.size());
            return true;
        }
        
        return false;
    }

    private boolean reportErrorsAndSummary(List<GenericError> errors) {
        return reportErrorsAndSummary(errors, false);
    }
    
    private boolean reportErrorsAndSummary(List<GenericError> errors, boolean isInstantiatorError) {
        for (GenericError error : errors) {
            reportError(error, isInstantiatorError);
        }
        
        if (!this.severe_errors.isEmpty()) {
            exitSummary(severe_errors.size(), warning_errors.size());
            return true;
        }
        
        return false;
    }
    
    /**
     * Method that really execute the compiler
     * @return the exit status (0 == OK, anything else is an error)
     */
    public int run(){

        boolean fatal_error_found_loading_type = false;
        int severe_error = 0;
        GenericError[] ges = null;

        // create the type model
        if (!xmiMode) {
            try {
                pl.purgeErrors();
                startProfile("LOADP");
                rootPackage = pl.getPackage(rootPackageName, true, !skip_validation);
            } catch (LoadPackageException lpe){
                fatal_error_found_loading_type = true;
                ges = lpe.getErrors();
            }
        } else {
            try {
                pl.purgeErrors();
                startProfile("LOADP");
                rootPackage = pl.deserializePackage(rootPackageName);
            } catch (Exception e){
                e.printStackTrace();
            }
        }
        
        stopProfile("LOADP");
        
        if (ges == null) {
            ges = pl.getErrors().toArray(new GenericError[0]);
        }

        if (reportErrorsAndSummary(ges)) return -1;

        int c = pl.packageCount();
        logger.log(Level.INFO, "Registry has " + c + " package" + (c>1?"s":"") + " loaded.");

        if (serialization_output != null && serializationFmt != null){
            pl.serializeAllPackages(serialization_output, serializationFmt);
            logger.log(Level.INFO, "Serialized as " + serializationFmt + " all loaded packages");
        }

        ComponentDeclaration cd;

        if (rootDefinition != null){
            startProfile("INSTANTIATION");
            logger.log(Level.INFO, "Instantiating " + rootDefinition);
            Instantiator instantiator = new Instantiator(pl);
            if (!xmiMode) {
                //regular parsing method
                CharStream input = new ANTLRStringStream(rootDefinition);
                    
                Bip2Lexer lexer = new Bip2Lexer(input);
                CommonTokenStream tokens = new CommonTokenStream(lexer);
                Bip2Parser parser = new Bip2Parser(tokens);
                    
                Bip2Parser.main_component_declaration_return fcd = null;
                    
                try {
                    fcd = parser.main_component_declaration();
                } catch (RecognitionException e) {
                    // means we have an error in the lexer, get errors directly from it as parser does NOT catch exception from lexer.
                    // This is done below, after the catch() block.
                }
                List<GenericError> perrors = new ArrayList<GenericError>();
                perrors.addAll(lexer.errors);
                perrors.addAll(parser.errors);
                
                for (GenericError error : perrors) {
                    if (error.getSourceStringBuffer() == null) {
                        error.setSourceStringBuffer(new StringBuffer(rootDefinition));
                    }
                }
                            
                if (reportErrorsAndSummary(perrors)) return -1;

                CommonTree t = (CommonTree) fcd.getTree();
                CommonTreeNodeStream nodes = new CommonTreeNodeStream(t);
                nodes.setTokenStream(tokens);
                    
                Bip2Walker walker = new Bip2Walker(nodes);
                walker.setLoader(null);
                walker.setParsedFileURL(null);
                walker.setParsedStringBuffer(new StringBuffer(rootDefinition));
                walker.setGlobalSymbolMap(pl.getGlobalSymbolMap());
                    
                Bip2Walker.main_component_declaration_return mcd = null;
                    
                try {
                    mcd = walker.main_component_declaration(rootPackage);
                } catch (RecognitionException e) {
                    // do nothing, it should be handled by some try/catch higher in the walker.
                    // error should be registered..
                    // throw new LoadPackageException(e);
                }
                
                for (GenericError error : walker.errors) {
                    if (error.getSourceStringBuffer() == null) {
                        error.setSourceStringBuffer(new StringBuffer(rootDefinition));
                    }
                }
                
                if (reportErrorsAndSummary(new ArrayList<GenericError>(walker.errors))) return -1;
                
                    
                cd = mcd.cd;
            } else {
                // xmi deserialization method
                cd = ComponentFactory.eINSTANCE.createComponentDeclaration();
                cd.setName("ROOT");
                List<ComponentType> cdList = pl.getComponentType(rootDefinition);
                if(cdList.size() > 1){
                    bailOut("Multiple definitions for "+rootDefinition+"!", -1);
                }
                if(cdList.size() == 0 ){
                    bailOut("Cannot find any definition for "+rootDefinition+"!", -1);
                }
                cd.setType(cdList.get(0));
            }

            DiagnosticError[] derrors = new DiagnosticError[0];

            if (!skip_validation)
                derrors = pl.validateType(cd);

            if (derrors.length > 0) {
                logger.log(Level.INFO, "Trying to take instance from badly specified declaration.\n");
                if (reportErrorsAndSummary(derrors)) return -1;
            }
            
            // execute the filters
            startProfile("FILTERS");
            executeFilters(rootPackage);
            stopProfile("FILTERS");

            try {
                rootInstance = instantiator.instantiateTopLevel(cd, !skip_validation);
            } catch (InstantiatorException ie) {
                if (reportErrorsAndSummary(ie.getErrors(), true)) return -1;
            }
            stopProfile("INSTANTIATION");
        }
        
        // run the backends
        startProfile("BACKENDS");
        executeBackends(rootPackage, rootInstance);
        stopProfile("BACKENDS");

        return 0;
    }

    /**
     * Main entry point for the command line user interface
     * @param args command line arguments
     * @throws Exception in case of an unexpected error.
     */
    public static void main(String[] args) throws Exception {
        Runner r = new Runner(args);
        System.exit(r.run());
    }
}
