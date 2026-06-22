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

package ujf.verimag.bip.metamodel;

import java.net.URL;
import java.util.HashMap;
import java.util.Map;

import org.eclipse.emf.ecore.impl.EObjectImpl;

public class AnnotatedEObjectImpl extends EObjectImpl implements AnnotatedEObject {

    /**
     * When set, contains the URL to the source file that triggered the
     * creation of this model object 
     */
    protected URL sourceURL;
    
    /**
     * When set, contains the direct source text that triggered the creation
     * of this model object (usually when code generation is used)
     */
    protected StringBuffer sourceStringBuffer;
    
    /**
     * The coordinates wrt. to the corresponding source.
     */
    protected int linestart, linestop, colstart, colstop;
    
    /**
     * The classname that created the object (caller of the ctor)
     */
    protected String javaClassname = null;
    
    /**
     * The method that created the object (caller of the ctor)
     */
    protected String javaMethodname = null;
    
    /**
     * The filename that contains the code that created the model object
     */
    protected String javaFileName = null;
    
    /**
     * The line within the java code that contains the code that created
     * the model object
     */
    protected int javaLine = -1;
    
    /**
     * A map for storing compiler annotations.
     * That is, annotation used by the compiler to store custom informations.
     * This has NOTHING to do with annotations within the BIP language.
     */
    Map<String, String> annotations = new HashMap<String,String>();
    
    
    public AnnotatedEObjectImpl(){
        super();
        StackTraceElement[] t = new Throwable().getStackTrace();
        StackTraceElement st;
        int i = 1;
        do {
            st = t[i];
            i++;
        } while(st.getClassName().startsWith("bip2.ujf.verimag.bip") &&
                i < t.length);
            
        this.javaFileName = st.getFileName();
        this.javaLine = st.getLineNumber();
        this.javaClassname = st.getClassName();
        this.javaMethodname = st.getMethodName();
    }
    
    @Override
    public void setSourceURL(URL sourceURL){
        this.sourceURL = sourceURL;
    }
    
    @Override
    public void setLocationInfo(int linestart, int colstart){
        setLocationInfo(linestart, -1, colstart, -1);
    }
    
    @Override
    public void setLocationInfo(int linestart, int linestop, int colstart, int colstop){
        this.linestart = linestart;
        this.linestop = linestop;
        this.colstart = colstart;
        this.colstop = colstop;
        
        new Throwable().getStackTrace()[1].getClassName();
    }
    
    @Override
    public void setSourceStringBuffer(StringBuffer sourceStringBuffer){
        this.sourceStringBuffer = sourceStringBuffer;
    }
    
    @Override
    public Map<String,String> getAnnotations(){
        return this.annotations;
    }
    
    @Override
    public StringBuffer getSourceStringBuffer() {
        return sourceStringBuffer;
    }

    @Override
    public URL getSourceURL() {
        return this.sourceURL;
    }

    @Override
    public int getLineStart() {
        return this.linestart;
    }

    @Override
    public int getLineStop() {
        return this.linestop;
    }

    @Override
    public int getColStart() {
        return this.colstart;
    }

    @Override
    public int getColStop() {
        return this.colstop;
    }

    @Override
    public String getSourceURLString() {
        if (this.sourceURL != null)
            return this.sourceURL.toString();
        else
            return null;
    }

    @Override
    public int getGeneratorLine() {
        return this.javaLine;
    }

    @Override
    public String getGeneratorFilename() {
        return this.javaFileName;
    }

    @Override
    public String getGeneratorMethod() {
        return this.javaClassname;
    }

    @Override
    public String getGeneratorClass() {
        return this.javaClassname;
    }

    @Override
    public String getGeneratorLocation() {
        return this.javaClassname + "." + this.javaMethodname + "@" + this.javaFileName + ":" + this.javaLine;
    }
}
