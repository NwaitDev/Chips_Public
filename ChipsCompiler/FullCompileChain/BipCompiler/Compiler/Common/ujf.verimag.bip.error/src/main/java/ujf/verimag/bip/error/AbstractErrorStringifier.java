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

package ujf.verimag.bip.error;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.io.StringReader;
import java.net.URL;
import java.util.logging.Level;
import java.util.logging.Logger;
import ujf.verimag.bip.error.message.ErrorCodeEnum;
import ujf.verimag.bip.error.message.ErrorMessage;
import ujf.verimag.bip.exception.CompilerErrorException;

public abstract class AbstractErrorStringifier {
    protected Logger logger = Logger.getLogger(this.getClass().getName());

    /**
     * When displaying an error in its context (source code before/after)
     * display this many line before the error
     */
    protected static int DEFAULT_BEFORE_LINES_CONTEXT = 1;
    /**
     * When displaying an error in its context (source code before/after)
     * display this many line after the error 
     */
    protected static int DEFAULT_AFTER_LINES_CONTEXT = 2;
    
    /**
     * The string prefix added before the arrow pointing to an error.
     */
    protected static String arrowprefix = "--------";

    /**
     * Used to get error message strings from property files (easy translation)
     */
    protected ErrorMessage errorMessage;
    

    public AbstractErrorStringifier(String propertyFile) throws IOException {
        try {
            this.errorMessage = new ErrorMessage(propertyFile);
        } catch (FileNotFoundException e) {
            logger.log(Level.WARNING, "Can't locate file with error messages:" + propertyFile);
            throw e;
        } catch (IOException e) {
            logger.log(Level.WARNING, "Can't read file with error messages:" + propertyFile);
            throw e;
        }
    }
    
    
    public AbstractErrorStringifier(File propertyFile) throws IOException {
        try {
            this.errorMessage = new ErrorMessage(propertyFile);
        } catch (FileNotFoundException e) {
            logger.log(Level.WARNING, "Can't locate file with error messages:" + propertyFile);
            throw e;
        } catch (IOException e) {
            logger.log(Level.WARNING, "Can't read file with error messages:" + propertyFile);
            throw e;
        }
    }

    public AbstractErrorStringifier(){
    }
    
    
    
    /**
     * Returns a String containing the context formed by the given file and given position in the file.
     * 
     * @param file
     *            the file from which to read the context
     * @param pointerLine
     *            the line number to point
     * @param pointerCol
     *            the column number to point
     * @return the context as a String
     */
    public static String getContext(URL file, int pointerLine, int pointerCol) {
        return getContext(file, pointerLine, pointerCol, DEFAULT_BEFORE_LINES_CONTEXT, DEFAULT_AFTER_LINES_CONTEXT);
    }
    

    public static String getContext(Reader context, int pointerLine, int pointerColstart, int pointerColend, int linesBefore, int linesAfter) {
        String default_res = "<NO CONTEXT FOUND>\n";

        int min = (pointerLine - linesBefore) >0 ? pointerLine - linesBefore : 0;
        int max = pointerLine + linesAfter;

        // no reader => no context => nothing to do.
        if (context== null)
            return default_res;
        
        StringBuffer sb = new StringBuffer();
        try {
            int line_idx;
            
            BufferedReader br = new BufferedReader(context);
            String line = br.readLine();
            
            for (line_idx = 1; line_idx <= pointerLine && line != null; line_idx++) {
                if (line_idx>= min && line_idx<= max){
                    sb.append(String.format("%1$6s: ", line_idx) + line.replace('\t', ' ') + "\n");
                }
                line = br.readLine();
            }
            
            // EOF reached before the source line reached.
            // There must be an error.
            if (line == null && line_idx < pointerLine) {
                return default_res;
            }
            
            //sb.append(String.format("%1$6s: ", error.getLine()) + line + "\n");

            if (pointerLine > 0) {
                sb.append(arrowprefix);
                for (int i = 0; i < pointerColstart - 1; i++) {
                    sb.append("-");
                }
                // sb.append("^");
                if (pointerColend != -1 && pointerColend > pointerColstart) {
                    sb.append(">");
                    for (int i = 0; i < pointerColend - pointerColstart; i++) {
                        sb.append("^");
                    }
                } else {
                    sb.append("-^");
                }
                sb.append("\n");
            }

            for (; line_idx <= max && line != null; line_idx++) {
                sb.append(String.format("%1$6s: ", line_idx) + line + "\n");
                line = br.readLine();
            }
        } catch (IOException e) {
            throw new CompilerErrorException(e);
        }

        return sb.toString();
    }
    
    /**
     * Returns a String containing the context formed by the given reader and given position in the reader.
     * @param context the reader from which to read the context
     * @param pointerLine the line number to point
     * @param pointerCol the column number to point
     * @param linesBefore number of lines before the error to include in the context
     * @param linesAfter number of lines after the error to include in the context
     * @return the context as a String
     */
    public static String getContext(Reader context, int pointerLine, int pointerCol, int linesBefore, int linesAfter) {
        return getContext(context, pointerLine, pointerCol, -1, linesBefore, linesAfter);
    }
    
    /**
     * Returns a String containing the context formed by the given file and given position in the file.
     * @param file the file from which to read the context
     * @param pointerLine the line number to point
     * @param pointerCol the column number to point
     * @param linesBefore number of lines before the error to include in the context
     * @param linesAfter number of lines after the error to include in the context
     * @return the context as a String
     */
    public static String getContext(URL file, int pointerLine, int pointerCol, int linesBefore, int linesAfter) {
        try {
            return getContext(new InputStreamReader(file.openStream()), pointerLine, pointerCol, linesBefore, linesAfter);
        } catch (IOException e) {
            throw new CompilerErrorException(e);
        }
    }

    /**
     * Returns a String containing the context of the error nicely formatted.
     * 
     * @param error
     *            the error for which to build the context
     * @param linesBefore
     *            number of lines before the error to include in the context
     * @param linesAfter
     *            number of lines after the error to include in the context
     * @return the context as a String
     */
    public static String getContext(GenericError error, int linesBefore, int linesAfter) {
        Reader r = null;
        if (error.getSourceFile() != null) {
            try {
                r = new InputStreamReader(error.getSourceFile().openStream());
            } catch (IOException e) {
                throw new CompilerErrorException(e);
            }
        } else if (error.getSourceStringBuffer() != null){
            r = new StringReader(error.getSourceStringBuffer().toString());
        }
        return getContext(r, error.getLine(), error.getColumnStart(), error.getColumnStop(),
                linesBefore, linesAfter);
    }

    /**
     * Returns a String containing the context of the error nicely formatted.
     * @param error the error for which to build the context
     * @return the context as a String
     */
    public static String getContext(GenericError error){
        return getContext(error, DEFAULT_BEFORE_LINES_CONTEXT, DEFAULT_AFTER_LINES_CONTEXT);
    }
    
    
    /**
     * Get the error string from external file
     * @param errorcode the error code
     * @return the corresponding string, null if none exists
     */
    protected String getSpecificErrorMessage(ErrorCodeEnum errorcode){
        String message = null;
        if (this.errorMessage != null){
            if (errorcode != ErrorCodeEnum.GenericDefault){
                String m = this.errorMessage.getMessage(errorcode);
                if (m == null){
                    logger.log(Level.FINEST, "Missing message for " + errorcode.toString());
                } else {
                    message = m;
                }
            }
        }
        return message;
    }
    
    public abstract String stringify(GenericError error);

}
