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
import java.util.Map;

import org.eclipse.emf.ecore.EObject;

/**
 * Subclass of EObject used to add extra information on model nodes so that
 * the compiler can get/set extra information (code line, specific annotations, etc).
 */
public interface AnnotatedEObject extends EObject {
    
    /**
     * Set the source for this element to this URL
     * @param sourceURL the source URL
     */
    public void setSourceURL(URL sourceURL);
    
    /**
     * Get the source URL as a String
     * @return the string representation of the URL if any, null if not.
     */
    public String getSourceURLString();
    
    /**
     * Get the source URL object
     * @return the source URL if any, null if not
     */
    public URL getSourceURL();

    /**
     * If the model element comes from generated BIP code,
     * sets this code from the buffer
     * @param sourceStringBuffer the buffer containing the generated code
     */
    public void setSourceStringBuffer(StringBuffer sourceStringBuffer);
    
    /**
     * Get the buffer containing the BIP code.
     * @return the buffer, null if there is none
     */
    public StringBuffer getSourceStringBuffer();
    
    /**
     * Get the first line corresponding to the model element
     * @return the starting line
     */
    public int getLineStart();
    
    /**
     * Get the last line corresponding to the model element
     * @return the end line
     */
    public int getLineStop();

    /**
     * Get the first column corresponding to the model element
     * @return the first column
     */
    public int getColStart();
    
    /**
     * Get the last column corresponding to the model element
     * @return the last column
     */
    public int getColStop();
    
    /**
     * Sets the location within source code
     * @param linestart the line
     * @param colstart the column
     */
    public void setLocationInfo(int linestart, int colstart);
    
    /**
     * Sets the location within source code 
     * @param linestart first line
     * @param linestop last line
     * @param colstart first column
     * @param colstop last column
     */
    public void setLocationInfo(int linestart, int linestop, int colstart, int colstop);

    /**
     * Get the line within the compiler that created the model element
     * @return the line number
     */
    public int getGeneratorLine();
    
    /**
     * Get the filename corresponding to the compiler java code that created
     * the model element
     * @return the filename as a String
     */
    public String getGeneratorFilename();
    
    /**
     * Get the name of the method that created the model element
     * @return the method name
     */
    public String getGeneratorMethod();
    
    /**
     * Get the name of the class that created the model element
     * @return the class name
     */
    public String getGeneratorClass();
    
    /**
     * Wrapper method around previous ones to get a single string
     * giving the exact location within the compiler source code
     * @return the location string
     */
    public String getGeneratorLocation();
    
    /**
     * Get annotations used by the compiler during the compilation. These annotations
     * have nothing to do with annotation within the BIP source code.
     * @return the annotations
     */
    public Map<String,String> getAnnotations();
}
