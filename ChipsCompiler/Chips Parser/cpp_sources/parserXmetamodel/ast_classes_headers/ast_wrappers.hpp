#ifndef __chips_wrapper__
#define __chips_wrapper__
#include "meta_type_conversions.hpp"
#include "metamodel_enums.hpp"
#include "ast_lrxvalues.hpp"

namespace chips {
	
	union direct_value{
		int int_val;
		bool bool_val;
		double float_val;
	};

	class rvalue_primitive_wrapper{
	private:
		rvalue_variant<expression_env::PRIMITIVE> m_data;

	public:
		rvalue_primitive_wrapper(direct_value dv, const dataflow_type dft){
			switch (dft) {
				case dataflow_type::INT:
				m_data = new direct<dataflow_type::INT, expression_env::PRIMITIVE>(dv.int_val);
				break;

				case dataflow_type::FLOAT:
				m_data = new direct<dataflow_type::FLOAT, expression_env::PRIMITIVE>(dv.float_val);
				break;
				
				case dataflow_type::BOOL:
				m_data = new direct<dataflow_type::BOOL, expression_env::PRIMITIVE>(dv.bool_val);
				break;
            }
            }
	};

}

#endif