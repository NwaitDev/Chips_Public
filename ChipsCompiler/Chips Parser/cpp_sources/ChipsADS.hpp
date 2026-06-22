// Chips language Abstract Data Structure


#ifndef CHIPS_ADS
#define CHIPS_ADS

#include "./chips_exceptions.cpp"
#include <cstddef>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>



enum COMPILE_STATE {
    CONFIGURING,
    DEFINING,
    IN_PURE,
    IN_PHYSICAL,
    IN_VIRTUAL
};

enum DATAFLOW_TYPE{
    INT_DF,
    FLOAT_DF,
    BOOL_DF
};

enum FUNCTION_TYPE{
    VIRTUAL,
    PHYSICAL,
    PURE
};

enum EXPRESSION_TYPE{
    PLUS_EXP, // binary
    MINUS_EXP, // binary
    U_MINUS_EXP,  // unary
    TIMES_EXP, // binary
    DIV_EXP, // binary
    FCALL_EXP, // Fcall
    MOD_EXP, // binary
    AND_EXP, // binary
    OR_EXP, // binary
    EQ_EXP, // binary
    NEQ_EXP, // binary
    GT_EXP, // binary
    LT_EXP, // binary
    GEQ_EXP, // binary
    LEQ_EXP, // binary
    NOT_EXP, // unary
    IDENT_EXP, // Ident
    CAST_TO_INT_EXP, // unary
    CAST_TO_FLOAT_EXP, // unary
    CAST_TO_BOOL_EXP, // unary
    INT_EXP, // number literal
    FLOAT_EXP, // number literal
    BOOL_EXP, // number literal
    OBJ_PHY_ATTR_EXP, // (ref to json file)
    OBJ_VIRT_IN_EXP, // (ref to input/output of functional block)
    OBJ_VIRT_OUT_EXP
};

enum STATEMENT_TYPE {
    INST_ST,
    ASSI_ST,
    IF_ST,
    IFELSE_ST,
    LOOP_ST,
    FCALL_ST
};

enum C_STATEMENT_TYPE {
    C_LOOP_ST,
    C_IF_ST,
    C_IFELSE_ST,
    C_INST_ST,
    C_FCT_PLUG_ST,
    C_LINK_ST,
    C_AT_ST,
    C_DF_INST_ST,
    C_DF_ASSI_ST,
    C_FCALL_ST
};


/**
    Contains all the classes that have to do with data 
    coherence checking for a system definition and configuration.
*/
namespace chips_ads {


    class full_context;

    /*
        DIMENSION class
    */
    class dimension_t {
        private:
            std::vector<size_t> dimension;

        public:
            dimension_t(std::vector<size_t> arr) : dimension(std::vector<size_t>(arr)) {
                for (size_t e : dimension){
                    if (e==0){
                        throw chips_exception("Cannot instanciate a variable with a 0 elements dimension.");
                    }
                }
            }
            dimension_t(size_t size) : dimension(std::vector<size_t>({size})) {
                if (size==0){
                    throw chips_exception("Cannot instanciate a variable with a 0 elements dimension.");
                }
            }
            dimension_t(const dimension_t& other) {
                for(const size_t e : other.dimension){
                    if (e==0) {
                        throw chips_exception("Cannot instanciate a variable with a 0 elements dimension.");
                    }
                    dimension.push_back(e);
                }
            }
            
            void debug(){for (int n : dimension) { std::cout<<"["<<n<<"]"; }}

            size_t get_cardinality();

            inline const std::vector<size_t> get_dimension() const {return dimension;}

            size_t linearize(std::vector<size_t> pos);
            size_t linearize(size_t pos);

            uint8_t constains(std::vector<size_t> position) const;
            inline size_t depth() const { return dimension.size();}

            inline const size_t operator[](size_t i) const {return dimension.at(i);}

            inline const uint8_t operator==(size_t othern) const {return (depth()==1) && (this->dimension[0]==othern);}
            const uint8_t operator==(const std::vector<size_t>& otherv) const;
            const uint8_t operator==(const dimension_t& other) const ;

            inline const uint8_t operator!=(size_t othern) const {return !(operator==(othern));}
            inline const uint8_t operator!=(const std::vector<size_t>& otherv) const {return !(operator==(otherv));}
            inline const uint8_t operator!=(const dimension_t& other) const {return !(operator==(other));}

            
    };



    /*
        VARIABLE class
    */

    class dataflow_t {

        private:
            const DATAFLOW_TYPE type;
            dimension_t dimension;
            uint8_t is_set;
            union {
                int i;
                double f;
                uint8_t b;
                std::vector<int>* vi;
                std::vector<double>* vf;
                std::vector<uint8_t>* vb;
            }value;

        public:
            dataflow_t() = delete;
            dataflow_t(dataflow_t& other);
            dataflow_t(const DATAFLOW_TYPE type, const dimension_t dimensions);
            dataflow_t(const DATAFLOW_TYPE type);
            dataflow_t(const DATAFLOW_TYPE type, const std::vector<size_t> dimensions);
            ~dataflow_t();

            void set_as_argument() {is_set = true;};
            
            void set_value(int value);
            void set_value(double value);
            void set_value(bool value);
            void set_value(int value, std::vector<size_t> position);
            void set_value(double value, std::vector<size_t> position);
            void set_value(bool value, std::vector<size_t> position);
            void set_value(const dataflow_t& other);

            template<typename T>
            inline T operator=(T value) { set_value(value); return value; }
            
            inline bool in_use(){return is_set;}

            void debug(){ std::cout<< type; dimension.debug(); std::cout<<" variable(is set: "<< in_use() <<")\n";}
            
            inline DATAFLOW_TYPE get_df_type(){return type;}
            inline const dimension_t get_dimension(){return dimension.get_dimension();}
    };


    /*
        EXPRESSION class
    */
    class expression_t {
        private:
            const EXPRESSION_TYPE type;
            dataflow_t df;
            std::string name = nullptr;
            dataflow_t* value = nullptr;
            expression_t* left = nullptr;
            expression_t* right = nullptr;
            std::vector<expression_t>* elist = nullptr;


        public:
            expression_t(
                full_context& ctx,
                EXPRESSION_TYPE type,
                std::string* name,
                expression_t* left_child,
                expression_t* right_child,
                dataflow_t* value,
                std::vector<chips_ads::expression_t>* elist);

            inline  dataflow_t get_dataflow() {return df;}

    };


    class statement_t{
        private:
        const STATEMENT_TYPE type;
        public:
        statement_t(STATEMENT_TYPE type);
    };



    class function_t{
        private:
            std::vector<dataflow_t> argument_types;
            std::vector<std::string> argument_names;
            std::vector<expression_t> outputs;
        public:
            virtual FUNCTION_TYPE get_function_type() = 0;
            virtual bool exists(std::string vname) = 0;
            virtual dataflow_t get_df_of(std::string vname) = 0;
            void add_argument(std::string, dataflow_t var);
            void add_output(expression_t expr);
            void add_outputs(std::vector<expression_t> exprs);
            inline std::vector<expression_t> get_outputs() const { return outputs;};
    };

    class pure_t : public function_t {
        private:
        public:
        inline FUNCTION_TYPE get_function_type() override {return PURE;}
        bool exists(std::string vname) override;
        dataflow_t get_df_of(std::string vname) override;
    };

    class object_t : public function_t {
        private:
        std::unordered_map<std::string, dataflow_t> variables;
        std::vector<statement_t> statements;
        public:
        
    };


    class virtual_t : public object_t {
        public:
        inline FUNCTION_TYPE get_function_type()override{return VIRTUAL;}
        bool exists(std::string vname) override;
        dataflow_t get_df_of(std::string vname) override;
    };

    class physical_t : public object_t {
        public:
        inline FUNCTION_TYPE get_function_type()override{return PHYSICAL;}
        bool exists(std::string vname) override;
        dataflow_t get_df_of(std::string vname) override;
    };

    

    class full_context {
        private:
        std::unordered_map<std::string, pure_t> pures;
        std::unordered_map<std::string, physical_t> physicals;
        std::unordered_map<std::string, virtual_t> virtuals;

        COMPILE_STATE st = DEFINING;
        std::string st_attr;

        public:
        void set_state(COMPILE_STATE new_state);
        void set_state(COMPILE_STATE new_state, std::string state_attr);
        inline const std::string get_attr() const {return st_attr;}
        COMPILE_STATE get_state();
        inline pure_t get_pure(std::string fname){return pures.at(fname);}
        inline physical_t get_physical(std::string fname){return physicals.at(fname);}
        inline virtual_t get_virtual(std::string fname){return virtuals.at(fname);}
        
    };


}

#endif //CHIPS_ADS