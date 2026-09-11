
// Generated from /home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/FullCompileChain/ChipsXmiGenerator/../Chips.g4 by ANTLR 4.13.2


#include "ChipsVisitor.h"

#include "ChipsParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct ChipsParserStaticData final {
  ChipsParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  ChipsParserStaticData(const ChipsParserStaticData&) = delete;
  ChipsParserStaticData(ChipsParserStaticData&&) = delete;
  ChipsParserStaticData& operator=(const ChipsParserStaticData&) = delete;
  ChipsParserStaticData& operator=(ChipsParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag chipsParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<ChipsParserStaticData> chipsParserStaticData = nullptr;

void chipsParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (chipsParserStaticData != nullptr) {
    return;
  }
#else
  assert(chipsParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<ChipsParserStaticData>(
    std::vector<std::string>{
      "program", "system", "preamble", "object_def", "implementation_def", 
      "node_mapping", "function_def", "collective_op_def", "c_output", "l_function_def", 
      "p_function_def", "c_signature", "c_keywords", "with_section", "with_statement", 
      "init_section", "then_section", "expr", "expr0", "expr01", "expr1", 
      "expr2", "cast", "c_expr", "c_stopless_expr", "c_stopless_expr0", 
      "c_stopless_expr01", "c_stopless_expr1", "c_stopless_expr2", "c_cast", 
      "suffixes", "c_suffixes", "s_suffixable_expr", "block", "loop_in", 
      "loop_statement", "c_loop_statement", "s_loop_statement", "if_else_statement", 
      "s_if_else_statement", "c_if_else_statement", "if_statement", "s_if_statement", 
      "c_if_statement", "statement", "s_statement", "s_expr", "collective_operation", 
      "c_statement", "named_output", "p_named_output", "df_parameter_decl", 
      "df_type", "pdf_parameter_type", "pdf_parameter_decl", "cdf_defaulted_decl", 
      "cdf_full_declaration"
    },
    std::vector<std::string>{
      "", "", "'int'", "'float'", "'bool'", "'logical'", "'physical'", "'as'", 
      "'init'", "'then'", "'for'", "'in'", "'if'", "'else'", "'to'", "'link'", 
      "'implements'", "'having'", "'input'", "'stop'", "'among'", "'spread'", 
      "'collect'", "'ctx'", "'object'", "'with'", "'implementation'", "'by'", 
      "'@'", "'default'", "'using'", "'actuator'", "'sensor'", "'->'", "'+'", 
      "'-'", "'*'", "'/'", "'%'", "'<'", "'>'", "'=='", "'<='", "'>='", 
      "'!='", "'&&'", "'||'", "'!'", "'='", "','", "';'", "'('", "')'", 
      "'{'", "'}'", "'['", "']'", "':'", "'.'"
    },
    std::vector<std::string>{
      "", "SYSTEM_KW", "INT_KW", "FLOAT_KW", "BOOL_KW", "LOGICAL_KW", "PHYSICAL_KW", 
      "AS_KW", "INIT_KW", "THEN_KW", "FOREACH_KW", "IN_KW", "IF_KW", "ELSE_KW", 
      "TO_KW", "LINK_KW", "IMPLEMENTS_KW", "HAVING_KW", "INPUT_KW", "STOP_KW", 
      "AMONG_KW", "SPREAD_KW", "COLLECT_KW", "CTX_KW", "OBJECT_KW", "WITH_KW", 
      "IMPLEMENTATION_KW", "BY_KW", "TARGET_KW", "DEFAULT_KW", "USING_KW", 
      "ACTUATOR_KW", "SENSOR_KW", "ARROW", "PLUS", "MINUS", "TIMES", "DIV", 
      "MOD", "LT", "GT", "EQ", "LEQ", "GEQ", "NEQ", "AND", "OR", "NOT", 
      "ASSIGN", "COMMA", "SEMICOL", "L_PARENTH", "R_PARENTH", "L_CURL", 
      "R_CURL", "L_SQUA", "R_SQUA", "COLUMN", "PERIOD", "BOOL", "FLOAT", 
      "INT", "IDENTIFIER", "NEWLINE", "WS", "COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,65,891,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,1,0,5,0,116,8,0,10,0,12,0,119,9,0,1,0,3,0,122,8,0,1,0,1,0,1,1,1,1,
  	1,1,5,1,129,8,1,10,1,12,1,132,9,1,1,1,1,1,1,2,1,2,1,2,1,2,3,2,140,8,2,
  	1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,5,4,154,8,4,10,4,12,4,
  	157,9,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,3,6,169,8,6,1,7,1,7,1,
  	7,5,7,174,8,7,10,7,12,7,177,9,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,5,7,186,8,
  	7,10,7,12,7,189,9,7,1,7,1,7,4,7,193,8,7,11,7,12,7,194,1,8,1,8,1,8,1,8,
  	1,8,1,8,5,8,203,8,8,10,8,12,8,206,9,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
  	5,8,216,8,8,10,8,12,8,219,9,8,1,8,1,8,3,8,223,8,8,1,9,1,9,1,9,1,9,1,9,
  	1,9,5,9,231,8,9,10,9,12,9,234,9,9,3,9,236,8,9,1,9,1,9,1,9,1,9,5,9,242,
  	8,9,10,9,12,9,245,9,9,1,10,1,10,1,10,1,10,1,10,1,10,5,10,253,8,10,10,
  	10,12,10,256,9,10,3,10,258,8,10,1,10,1,10,1,10,1,10,1,10,5,10,265,8,10,
  	10,10,12,10,268,9,10,1,11,1,11,1,11,1,11,1,11,5,11,275,8,11,10,11,12,
  	11,278,9,11,3,11,280,8,11,1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,13,1,13,
  	1,13,5,13,292,8,13,10,13,12,13,295,9,13,1,13,1,13,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,14,3,14,308,8,14,1,14,1,14,1,14,3,14,313,8,14,1,
  	15,1,15,1,15,5,15,318,8,15,10,15,12,15,321,9,15,1,15,1,15,1,16,1,16,1,
  	16,5,16,328,8,16,10,16,12,16,331,9,16,1,16,1,16,1,17,1,17,1,17,1,17,1,
  	17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,
  	17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,
  	17,3,17,368,8,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,18,379,
  	8,18,1,19,1,19,1,19,3,19,384,8,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,
  	1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,3,20,401,8,20,1,21,1,21,1,21,
  	1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,
  	1,21,5,21,421,8,21,10,21,12,21,424,9,21,3,21,426,8,21,1,21,1,21,3,21,
  	430,8,21,1,22,1,22,1,22,1,22,1,22,1,23,1,23,3,23,439,8,23,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,3,24,474,8,24,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,
  	25,3,25,485,8,25,1,26,1,26,1,26,3,26,490,8,26,1,27,1,27,1,27,1,27,1,27,
  	1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,3,27,507,8,27,1,28,
  	1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,
  	1,28,1,28,1,28,1,28,5,28,528,8,28,10,28,12,28,531,9,28,3,28,533,8,28,
  	1,28,1,28,1,28,1,28,1,28,1,28,3,28,541,8,28,1,29,1,29,1,29,1,29,1,29,
  	1,30,1,30,1,30,1,30,5,30,552,8,30,10,30,12,30,555,9,30,1,31,1,31,1,31,
  	1,31,5,31,561,8,31,10,31,12,31,564,9,31,1,32,1,32,1,32,1,32,1,32,1,32,
  	5,32,572,8,32,10,32,12,32,575,9,32,3,32,577,8,32,1,32,3,32,580,8,32,1,
  	32,1,32,1,32,1,32,3,32,586,8,32,1,33,1,33,1,33,1,34,1,34,1,34,1,34,1,
  	34,5,34,596,8,34,10,34,12,34,599,9,34,3,34,601,8,34,1,34,3,34,604,8,34,
  	1,34,1,34,1,35,1,35,1,35,1,35,1,35,1,35,5,35,614,8,35,10,35,12,35,617,
  	9,35,1,35,1,35,1,36,1,36,1,36,1,36,1,36,1,36,5,36,627,8,36,10,36,12,36,
  	630,9,36,1,36,1,36,1,37,1,37,1,37,1,37,1,37,1,37,5,37,640,8,37,10,37,
  	12,37,643,9,37,1,37,1,37,1,38,1,38,1,38,1,38,5,38,651,8,38,10,38,12,38,
  	654,9,38,1,38,1,38,1,39,1,39,1,39,1,39,5,39,662,8,39,10,39,12,39,665,
  	9,39,1,39,1,39,1,40,1,40,1,40,1,40,5,40,673,8,40,10,40,12,40,676,9,40,
  	1,40,1,40,1,41,1,41,1,41,1,41,1,41,1,41,5,41,686,8,41,10,41,12,41,689,
  	9,41,1,41,1,41,1,42,1,42,1,42,1,42,1,42,1,42,5,42,699,8,42,10,42,12,42,
  	702,9,42,1,42,1,42,1,43,1,43,1,43,1,43,1,43,1,43,5,43,712,8,43,10,43,
  	12,43,715,9,43,1,43,1,43,1,44,1,44,1,44,1,44,1,44,3,44,724,8,44,1,44,
  	1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,
  	1,44,1,44,1,44,1,44,3,44,745,8,44,1,45,1,45,1,45,1,45,1,45,1,45,1,45,
  	1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,
  	1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,3,45,
  	781,8,45,1,46,1,46,1,46,1,46,1,46,1,46,1,46,1,46,1,46,1,46,3,46,793,8,
  	46,1,47,1,47,1,47,1,47,1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,
  	48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,3,48,819,8,48,1,
  	49,1,49,1,49,1,49,1,49,1,49,5,49,827,8,49,10,49,12,49,830,9,49,1,49,1,
  	49,1,50,1,50,1,50,1,50,1,50,1,50,1,50,5,50,841,8,50,10,50,12,50,844,9,
  	50,1,50,1,50,1,50,3,50,849,8,50,1,51,1,51,1,51,1,51,1,51,3,51,856,8,51,
  	1,52,1,52,1,52,3,52,861,8,52,1,53,1,53,1,53,1,53,1,53,1,53,1,53,3,53,
  	870,8,53,1,54,1,54,1,54,1,54,3,54,876,8,54,1,55,1,55,1,55,1,55,1,55,1,
  	55,1,56,1,56,1,56,1,56,1,56,3,56,889,8,56,1,56,0,0,57,0,2,4,6,8,10,12,
  	14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,
  	60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,
  	106,108,110,112,0,1,1,0,21,22,960,0,117,1,0,0,0,2,125,1,0,0,0,4,139,1,
  	0,0,0,6,141,1,0,0,0,8,145,1,0,0,0,10,160,1,0,0,0,12,168,1,0,0,0,14,170,
  	1,0,0,0,16,222,1,0,0,0,18,224,1,0,0,0,20,246,1,0,0,0,22,269,1,0,0,0,24,
  	286,1,0,0,0,26,288,1,0,0,0,28,312,1,0,0,0,30,314,1,0,0,0,32,324,1,0,0,
  	0,34,367,1,0,0,0,36,378,1,0,0,0,38,383,1,0,0,0,40,400,1,0,0,0,42,429,
  	1,0,0,0,44,431,1,0,0,0,46,438,1,0,0,0,48,473,1,0,0,0,50,484,1,0,0,0,52,
  	489,1,0,0,0,54,506,1,0,0,0,56,540,1,0,0,0,58,542,1,0,0,0,60,553,1,0,0,
  	0,62,562,1,0,0,0,64,585,1,0,0,0,66,587,1,0,0,0,68,590,1,0,0,0,70,607,
  	1,0,0,0,72,620,1,0,0,0,74,633,1,0,0,0,76,646,1,0,0,0,78,657,1,0,0,0,80,
  	668,1,0,0,0,82,679,1,0,0,0,84,692,1,0,0,0,86,705,1,0,0,0,88,744,1,0,0,
  	0,90,780,1,0,0,0,92,792,1,0,0,0,94,794,1,0,0,0,96,818,1,0,0,0,98,820,
  	1,0,0,0,100,848,1,0,0,0,102,850,1,0,0,0,104,860,1,0,0,0,106,869,1,0,0,
  	0,108,871,1,0,0,0,110,877,1,0,0,0,112,883,1,0,0,0,114,116,3,4,2,0,115,
  	114,1,0,0,0,116,119,1,0,0,0,117,115,1,0,0,0,117,118,1,0,0,0,118,121,1,
  	0,0,0,119,117,1,0,0,0,120,122,3,2,1,0,121,120,1,0,0,0,121,122,1,0,0,0,
  	122,123,1,0,0,0,123,124,5,0,0,1,124,1,1,0,0,0,125,126,5,1,0,0,126,130,
  	5,53,0,0,127,129,3,90,45,0,128,127,1,0,0,0,129,132,1,0,0,0,130,128,1,
  	0,0,0,130,131,1,0,0,0,131,133,1,0,0,0,132,130,1,0,0,0,133,134,5,54,0,
  	0,134,3,1,0,0,0,135,140,3,6,3,0,136,140,3,12,6,0,137,140,3,14,7,0,138,
  	140,3,8,4,0,139,135,1,0,0,0,139,136,1,0,0,0,139,137,1,0,0,0,139,138,1,
  	0,0,0,140,5,1,0,0,0,141,142,5,24,0,0,142,143,5,62,0,0,143,144,3,26,13,
  	0,144,7,1,0,0,0,145,146,5,26,0,0,146,147,5,62,0,0,147,148,5,57,0,0,148,
  	149,5,62,0,0,149,150,5,27,0,0,150,151,5,62,0,0,151,155,5,53,0,0,152,154,
  	3,10,5,0,153,152,1,0,0,0,154,157,1,0,0,0,155,153,1,0,0,0,155,156,1,0,
  	0,0,156,158,1,0,0,0,157,155,1,0,0,0,158,159,5,54,0,0,159,9,1,0,0,0,160,
  	161,5,17,0,0,161,162,5,62,0,0,162,163,5,7,0,0,163,164,5,62,0,0,164,165,
  	5,50,0,0,165,11,1,0,0,0,166,169,3,18,9,0,167,169,3,20,10,0,168,166,1,
  	0,0,0,168,167,1,0,0,0,169,13,1,0,0,0,170,171,3,22,11,0,171,175,5,53,0,
  	0,172,174,3,96,48,0,173,172,1,0,0,0,174,177,1,0,0,0,175,173,1,0,0,0,175,
  	176,1,0,0,0,176,178,1,0,0,0,177,175,1,0,0,0,178,179,5,54,0,0,179,180,
  	5,33,0,0,180,181,5,28,0,0,181,182,5,51,0,0,182,187,3,46,23,0,183,184,
  	5,49,0,0,184,186,3,46,23,0,185,183,1,0,0,0,186,189,1,0,0,0,187,185,1,
  	0,0,0,187,188,1,0,0,0,188,190,1,0,0,0,189,187,1,0,0,0,190,192,5,52,0,
  	0,191,193,3,16,8,0,192,191,1,0,0,0,193,194,1,0,0,0,194,192,1,0,0,0,194,
  	195,1,0,0,0,195,15,1,0,0,0,196,197,5,33,0,0,197,198,5,29,0,0,198,199,
  	5,51,0,0,199,204,3,46,23,0,200,201,5,49,0,0,201,203,3,46,23,0,202,200,
  	1,0,0,0,203,206,1,0,0,0,204,202,1,0,0,0,204,205,1,0,0,0,205,207,1,0,0,
  	0,206,204,1,0,0,0,207,208,5,52,0,0,208,223,1,0,0,0,209,210,5,33,0,0,210,
  	211,5,62,0,0,211,212,5,51,0,0,212,217,3,46,23,0,213,214,5,49,0,0,214,
  	216,3,46,23,0,215,213,1,0,0,0,216,219,1,0,0,0,217,215,1,0,0,0,217,218,
  	1,0,0,0,218,220,1,0,0,0,219,217,1,0,0,0,220,221,5,52,0,0,221,223,1,0,
  	0,0,222,196,1,0,0,0,222,209,1,0,0,0,223,17,1,0,0,0,224,225,5,5,0,0,225,
  	226,5,62,0,0,226,235,5,51,0,0,227,232,3,102,51,0,228,229,5,49,0,0,229,
  	231,3,102,51,0,230,228,1,0,0,0,231,234,1,0,0,0,232,230,1,0,0,0,232,233,
  	1,0,0,0,233,236,1,0,0,0,234,232,1,0,0,0,235,227,1,0,0,0,235,236,1,0,0,
  	0,236,237,1,0,0,0,237,238,5,52,0,0,238,239,3,30,15,0,239,243,3,32,16,
  	0,240,242,3,98,49,0,241,240,1,0,0,0,242,245,1,0,0,0,243,241,1,0,0,0,243,
  	244,1,0,0,0,244,19,1,0,0,0,245,243,1,0,0,0,246,247,5,6,0,0,247,248,5,
  	62,0,0,248,257,5,51,0,0,249,254,3,108,54,0,250,251,5,49,0,0,251,253,3,
  	108,54,0,252,250,1,0,0,0,253,256,1,0,0,0,254,252,1,0,0,0,254,255,1,0,
  	0,0,255,258,1,0,0,0,256,254,1,0,0,0,257,249,1,0,0,0,257,258,1,0,0,0,258,
  	259,1,0,0,0,259,260,5,52,0,0,260,261,3,26,13,0,261,262,3,30,15,0,262,
  	266,3,32,16,0,263,265,3,100,50,0,264,263,1,0,0,0,265,268,1,0,0,0,266,
  	264,1,0,0,0,266,267,1,0,0,0,267,21,1,0,0,0,268,266,1,0,0,0,269,270,3,
  	24,12,0,270,279,5,51,0,0,271,276,3,110,55,0,272,273,5,49,0,0,273,275,
  	3,110,55,0,274,272,1,0,0,0,275,278,1,0,0,0,276,274,1,0,0,0,276,277,1,
  	0,0,0,277,280,1,0,0,0,278,276,1,0,0,0,279,271,1,0,0,0,279,280,1,0,0,0,
  	280,281,1,0,0,0,281,282,5,52,0,0,282,283,5,62,0,0,283,284,5,20,0,0,284,
  	285,5,62,0,0,285,23,1,0,0,0,286,287,7,0,0,0,287,25,1,0,0,0,288,289,5,
  	25,0,0,289,293,5,53,0,0,290,292,3,28,14,0,291,290,1,0,0,0,292,295,1,0,
  	0,0,293,291,1,0,0,0,293,294,1,0,0,0,294,296,1,0,0,0,295,293,1,0,0,0,296,
  	297,5,54,0,0,297,27,1,0,0,0,298,299,5,62,0,0,299,300,5,62,0,0,300,313,
  	5,50,0,0,301,302,5,23,0,0,302,303,3,104,52,0,303,304,3,60,30,0,304,307,
  	5,62,0,0,305,306,5,48,0,0,306,308,3,34,17,0,307,305,1,0,0,0,307,308,1,
  	0,0,0,308,309,1,0,0,0,309,310,5,50,0,0,310,313,1,0,0,0,311,313,3,88,44,
  	0,312,298,1,0,0,0,312,301,1,0,0,0,312,311,1,0,0,0,313,29,1,0,0,0,314,
  	315,5,8,0,0,315,319,5,53,0,0,316,318,3,88,44,0,317,316,1,0,0,0,318,321,
  	1,0,0,0,319,317,1,0,0,0,319,320,1,0,0,0,320,322,1,0,0,0,321,319,1,0,0,
  	0,322,323,5,54,0,0,323,31,1,0,0,0,324,325,5,9,0,0,325,329,5,53,0,0,326,
  	328,3,88,44,0,327,326,1,0,0,0,328,331,1,0,0,0,329,327,1,0,0,0,329,330,
  	1,0,0,0,330,332,1,0,0,0,331,329,1,0,0,0,332,333,5,54,0,0,333,33,1,0,0,
  	0,334,335,3,36,18,0,335,336,5,39,0,0,336,337,3,34,17,0,337,368,1,0,0,
  	0,338,339,3,36,18,0,339,340,5,40,0,0,340,341,3,34,17,0,341,368,1,0,0,
  	0,342,343,3,36,18,0,343,344,5,42,0,0,344,345,3,34,17,0,345,368,1,0,0,
  	0,346,347,3,36,18,0,347,348,5,43,0,0,348,349,3,34,17,0,349,368,1,0,0,
  	0,350,351,3,36,18,0,351,352,5,44,0,0,352,353,3,34,17,0,353,368,1,0,0,
  	0,354,355,3,36,18,0,355,356,5,41,0,0,356,357,3,34,17,0,357,368,1,0,0,
  	0,358,359,3,36,18,0,359,360,5,45,0,0,360,361,3,34,17,0,361,368,1,0,0,
  	0,362,363,3,36,18,0,363,364,5,46,0,0,364,365,3,34,17,0,365,368,1,0,0,
  	0,366,368,3,36,18,0,367,334,1,0,0,0,367,338,1,0,0,0,367,342,1,0,0,0,367,
  	346,1,0,0,0,367,350,1,0,0,0,367,354,1,0,0,0,367,358,1,0,0,0,367,362,1,
  	0,0,0,367,366,1,0,0,0,368,35,1,0,0,0,369,370,3,38,19,0,370,371,5,34,0,
  	0,371,372,3,36,18,0,372,379,1,0,0,0,373,374,3,38,19,0,374,375,5,35,0,
  	0,375,376,3,36,18,0,376,379,1,0,0,0,377,379,3,38,19,0,378,369,1,0,0,0,
  	378,373,1,0,0,0,378,377,1,0,0,0,379,37,1,0,0,0,380,381,5,35,0,0,381,384,
  	3,40,20,0,382,384,3,40,20,0,383,380,1,0,0,0,383,382,1,0,0,0,384,39,1,
  	0,0,0,385,386,3,42,21,0,386,387,5,36,0,0,387,388,3,40,20,0,388,401,1,
  	0,0,0,389,390,3,42,21,0,390,391,5,37,0,0,391,392,3,40,20,0,392,401,1,
  	0,0,0,393,394,3,42,21,0,394,395,5,38,0,0,395,396,3,40,20,0,396,401,1,
  	0,0,0,397,398,5,47,0,0,398,401,3,42,21,0,399,401,3,42,21,0,400,385,1,
  	0,0,0,400,389,1,0,0,0,400,393,1,0,0,0,400,397,1,0,0,0,400,399,1,0,0,0,
  	401,41,1,0,0,0,402,430,5,61,0,0,403,430,5,60,0,0,404,430,5,59,0,0,405,
  	406,5,62,0,0,406,430,3,60,30,0,407,408,5,51,0,0,408,409,3,34,17,0,409,
  	410,5,52,0,0,410,430,1,0,0,0,411,412,5,23,0,0,412,413,5,58,0,0,413,414,
  	5,62,0,0,414,430,3,60,30,0,415,416,5,62,0,0,416,425,5,51,0,0,417,422,
  	3,34,17,0,418,419,5,49,0,0,419,421,3,34,17,0,420,418,1,0,0,0,421,424,
  	1,0,0,0,422,420,1,0,0,0,422,423,1,0,0,0,423,426,1,0,0,0,424,422,1,0,0,
  	0,425,417,1,0,0,0,425,426,1,0,0,0,426,427,1,0,0,0,427,430,5,52,0,0,428,
  	430,3,44,22,0,429,402,1,0,0,0,429,403,1,0,0,0,429,404,1,0,0,0,429,405,
  	1,0,0,0,429,407,1,0,0,0,429,411,1,0,0,0,429,415,1,0,0,0,429,428,1,0,0,
  	0,430,43,1,0,0,0,431,432,5,51,0,0,432,433,3,104,52,0,433,434,5,52,0,0,
  	434,435,3,34,17,0,435,45,1,0,0,0,436,439,3,48,24,0,437,439,5,19,0,0,438,
  	436,1,0,0,0,438,437,1,0,0,0,439,47,1,0,0,0,440,441,3,50,25,0,441,442,
  	5,39,0,0,442,443,3,48,24,0,443,474,1,0,0,0,444,445,3,50,25,0,445,446,
  	5,40,0,0,446,447,3,48,24,0,447,474,1,0,0,0,448,449,3,50,25,0,449,450,
  	5,42,0,0,450,451,3,48,24,0,451,474,1,0,0,0,452,453,3,50,25,0,453,454,
  	5,43,0,0,454,455,3,48,24,0,455,474,1,0,0,0,456,457,3,50,25,0,457,458,
  	5,44,0,0,458,459,3,48,24,0,459,474,1,0,0,0,460,461,3,50,25,0,461,462,
  	5,41,0,0,462,463,3,48,24,0,463,474,1,0,0,0,464,465,3,50,25,0,465,466,
  	5,45,0,0,466,467,3,48,24,0,467,474,1,0,0,0,468,469,3,50,25,0,469,470,
  	5,46,0,0,470,471,3,48,24,0,471,474,1,0,0,0,472,474,3,50,25,0,473,440,
  	1,0,0,0,473,444,1,0,0,0,473,448,1,0,0,0,473,452,1,0,0,0,473,456,1,0,0,
  	0,473,460,1,0,0,0,473,464,1,0,0,0,473,468,1,0,0,0,473,472,1,0,0,0,474,
  	49,1,0,0,0,475,476,3,52,26,0,476,477,5,34,0,0,477,478,3,50,25,0,478,485,
  	1,0,0,0,479,480,3,52,26,0,480,481,5,35,0,0,481,482,3,50,25,0,482,485,
  	1,0,0,0,483,485,3,52,26,0,484,475,1,0,0,0,484,479,1,0,0,0,484,483,1,0,
  	0,0,485,51,1,0,0,0,486,487,5,35,0,0,487,490,3,54,27,0,488,490,3,54,27,
  	0,489,486,1,0,0,0,489,488,1,0,0,0,490,53,1,0,0,0,491,492,3,56,28,0,492,
  	493,5,36,0,0,493,494,3,54,27,0,494,507,1,0,0,0,495,496,3,56,28,0,496,
  	497,5,37,0,0,497,498,3,54,27,0,498,507,1,0,0,0,499,500,3,56,28,0,500,
  	501,5,38,0,0,501,502,3,54,27,0,502,507,1,0,0,0,503,504,5,47,0,0,504,507,
  	3,56,28,0,505,507,3,56,28,0,506,491,1,0,0,0,506,495,1,0,0,0,506,499,1,
  	0,0,0,506,503,1,0,0,0,506,505,1,0,0,0,507,55,1,0,0,0,508,509,5,62,0,0,
  	509,541,3,62,31,0,510,541,5,61,0,0,511,541,5,60,0,0,512,541,5,59,0,0,
  	513,541,5,18,0,0,514,515,5,23,0,0,515,516,5,58,0,0,516,517,5,62,0,0,517,
  	541,3,62,31,0,518,519,5,62,0,0,519,520,5,58,0,0,520,521,5,62,0,0,521,
  	541,3,62,31,0,522,523,5,62,0,0,523,532,5,51,0,0,524,529,3,46,23,0,525,
  	526,5,49,0,0,526,528,3,46,23,0,527,525,1,0,0,0,528,531,1,0,0,0,529,527,
  	1,0,0,0,529,530,1,0,0,0,530,533,1,0,0,0,531,529,1,0,0,0,532,524,1,0,0,
  	0,532,533,1,0,0,0,533,534,1,0,0,0,534,541,5,52,0,0,535,536,5,51,0,0,536,
  	537,3,48,24,0,537,538,5,52,0,0,538,541,1,0,0,0,539,541,3,58,29,0,540,
  	508,1,0,0,0,540,510,1,0,0,0,540,511,1,0,0,0,540,512,1,0,0,0,540,513,1,
  	0,0,0,540,514,1,0,0,0,540,518,1,0,0,0,540,522,1,0,0,0,540,535,1,0,0,0,
  	540,539,1,0,0,0,541,57,1,0,0,0,542,543,5,51,0,0,543,544,3,104,52,0,544,
  	545,5,52,0,0,545,546,3,48,24,0,546,59,1,0,0,0,547,548,5,55,0,0,548,549,
  	3,34,17,0,549,550,5,56,0,0,550,552,1,0,0,0,551,547,1,0,0,0,552,555,1,
  	0,0,0,553,551,1,0,0,0,553,554,1,0,0,0,554,61,1,0,0,0,555,553,1,0,0,0,
  	556,557,5,55,0,0,557,558,3,48,24,0,558,559,5,56,0,0,559,561,1,0,0,0,560,
  	556,1,0,0,0,561,564,1,0,0,0,562,560,1,0,0,0,562,563,1,0,0,0,563,63,1,
  	0,0,0,564,562,1,0,0,0,565,586,5,62,0,0,566,579,5,62,0,0,567,576,5,51,
  	0,0,568,573,3,34,17,0,569,570,5,49,0,0,570,572,3,34,17,0,571,569,1,0,
  	0,0,572,575,1,0,0,0,573,571,1,0,0,0,573,574,1,0,0,0,574,577,1,0,0,0,575,
  	573,1,0,0,0,576,568,1,0,0,0,576,577,1,0,0,0,577,578,1,0,0,0,578,580,5,
  	52,0,0,579,567,1,0,0,0,579,580,1,0,0,0,580,586,1,0,0,0,581,582,3,66,33,
  	0,582,583,5,58,0,0,583,584,5,62,0,0,584,586,1,0,0,0,585,565,1,0,0,0,585,
  	566,1,0,0,0,585,581,1,0,0,0,586,65,1,0,0,0,587,588,5,62,0,0,588,589,3,
  	60,30,0,589,67,1,0,0,0,590,603,5,62,0,0,591,600,5,51,0,0,592,597,3,34,
  	17,0,593,594,5,49,0,0,594,596,3,34,17,0,595,593,1,0,0,0,596,599,1,0,0,
  	0,597,595,1,0,0,0,597,598,1,0,0,0,598,601,1,0,0,0,599,597,1,0,0,0,600,
  	592,1,0,0,0,600,601,1,0,0,0,601,602,1,0,0,0,602,604,5,52,0,0,603,591,
  	1,0,0,0,603,604,1,0,0,0,604,605,1,0,0,0,605,606,3,60,30,0,606,69,1,0,
  	0,0,607,608,5,10,0,0,608,609,5,62,0,0,609,610,5,11,0,0,610,611,3,68,34,
  	0,611,615,5,53,0,0,612,614,3,88,44,0,613,612,1,0,0,0,614,617,1,0,0,0,
  	615,613,1,0,0,0,615,616,1,0,0,0,616,618,1,0,0,0,617,615,1,0,0,0,618,619,
  	5,54,0,0,619,71,1,0,0,0,620,621,5,10,0,0,621,622,5,62,0,0,622,623,5,11,
  	0,0,623,624,3,68,34,0,624,628,5,53,0,0,625,627,3,96,48,0,626,625,1,0,
  	0,0,627,630,1,0,0,0,628,626,1,0,0,0,628,629,1,0,0,0,629,631,1,0,0,0,630,
  	628,1,0,0,0,631,632,5,54,0,0,632,73,1,0,0,0,633,634,5,10,0,0,634,635,
  	5,62,0,0,635,636,5,11,0,0,636,637,3,64,32,0,637,641,5,53,0,0,638,640,
  	3,90,45,0,639,638,1,0,0,0,640,643,1,0,0,0,641,639,1,0,0,0,641,642,1,0,
  	0,0,642,644,1,0,0,0,643,641,1,0,0,0,644,645,5,54,0,0,645,75,1,0,0,0,646,
  	647,3,82,41,0,647,648,5,13,0,0,648,652,5,53,0,0,649,651,3,88,44,0,650,
  	649,1,0,0,0,651,654,1,0,0,0,652,650,1,0,0,0,652,653,1,0,0,0,653,655,1,
  	0,0,0,654,652,1,0,0,0,655,656,5,54,0,0,656,77,1,0,0,0,657,658,3,84,42,
  	0,658,659,5,13,0,0,659,663,5,53,0,0,660,662,3,90,45,0,661,660,1,0,0,0,
  	662,665,1,0,0,0,663,661,1,0,0,0,663,664,1,0,0,0,664,666,1,0,0,0,665,663,
  	1,0,0,0,666,667,5,54,0,0,667,79,1,0,0,0,668,669,3,86,43,0,669,670,5,13,
  	0,0,670,674,5,53,0,0,671,673,3,96,48,0,672,671,1,0,0,0,673,676,1,0,0,
  	0,674,672,1,0,0,0,674,675,1,0,0,0,675,677,1,0,0,0,676,674,1,0,0,0,677,
  	678,5,54,0,0,678,81,1,0,0,0,679,680,5,12,0,0,680,681,5,51,0,0,681,682,
  	3,34,17,0,682,683,5,52,0,0,683,687,5,53,0,0,684,686,3,88,44,0,685,684,
  	1,0,0,0,686,689,1,0,0,0,687,685,1,0,0,0,687,688,1,0,0,0,688,690,1,0,0,
  	0,689,687,1,0,0,0,690,691,5,54,0,0,691,83,1,0,0,0,692,693,5,12,0,0,693,
  	694,5,51,0,0,694,695,3,34,17,0,695,696,5,52,0,0,696,700,5,53,0,0,697,
  	699,3,90,45,0,698,697,1,0,0,0,699,702,1,0,0,0,700,698,1,0,0,0,700,701,
  	1,0,0,0,701,703,1,0,0,0,702,700,1,0,0,0,703,704,5,54,0,0,704,85,1,0,0,
  	0,705,706,5,12,0,0,706,707,5,51,0,0,707,708,3,46,23,0,708,709,5,52,0,
  	0,709,713,5,53,0,0,710,712,3,96,48,0,711,710,1,0,0,0,712,715,1,0,0,0,
  	713,711,1,0,0,0,713,714,1,0,0,0,714,716,1,0,0,0,715,713,1,0,0,0,716,717,
  	5,54,0,0,717,87,1,0,0,0,718,719,3,104,52,0,719,720,3,60,30,0,720,723,
  	5,62,0,0,721,722,5,48,0,0,722,724,3,34,17,0,723,721,1,0,0,0,723,724,1,
  	0,0,0,724,725,1,0,0,0,725,726,5,50,0,0,726,745,1,0,0,0,727,728,5,62,0,
  	0,728,729,3,60,30,0,729,730,5,48,0,0,730,731,3,34,17,0,731,732,5,50,0,
  	0,732,745,1,0,0,0,733,734,5,23,0,0,734,735,5,58,0,0,735,736,5,62,0,0,
  	736,737,3,60,30,0,737,738,5,48,0,0,738,739,3,34,17,0,739,740,5,50,0,0,
  	740,745,1,0,0,0,741,745,3,70,35,0,742,745,3,76,38,0,743,745,3,82,41,0,
  	744,718,1,0,0,0,744,727,1,0,0,0,744,733,1,0,0,0,744,741,1,0,0,0,744,742,
  	1,0,0,0,744,743,1,0,0,0,745,89,1,0,0,0,746,747,5,62,0,0,747,748,3,60,
  	30,0,748,749,5,62,0,0,749,750,5,50,0,0,750,781,1,0,0,0,751,752,3,66,33,
  	0,752,753,5,58,0,0,753,754,5,62,0,0,754,755,5,51,0,0,755,756,3,92,46,
  	0,756,757,5,52,0,0,757,758,5,50,0,0,758,781,1,0,0,0,759,760,5,15,0,0,
  	760,761,5,62,0,0,761,762,3,60,30,0,762,763,5,14,0,0,763,764,5,62,0,0,
  	764,765,3,60,30,0,765,766,5,50,0,0,766,781,1,0,0,0,767,768,5,62,0,0,768,
  	769,3,60,30,0,769,770,5,26,0,0,770,771,5,62,0,0,771,772,3,60,30,0,772,
  	773,5,30,0,0,773,774,5,62,0,0,774,775,5,50,0,0,775,781,1,0,0,0,776,781,
  	3,74,37,0,777,781,3,78,39,0,778,781,3,84,42,0,779,781,3,88,44,0,780,746,
  	1,0,0,0,780,751,1,0,0,0,780,759,1,0,0,0,780,767,1,0,0,0,780,776,1,0,0,
  	0,780,777,1,0,0,0,780,778,1,0,0,0,780,779,1,0,0,0,781,91,1,0,0,0,782,
  	783,3,66,33,0,783,784,5,58,0,0,784,785,5,62,0,0,785,793,1,0,0,0,786,787,
  	3,94,47,0,787,788,3,66,33,0,788,789,5,58,0,0,789,790,5,62,0,0,790,793,
  	1,0,0,0,791,793,3,34,17,0,792,782,1,0,0,0,792,786,1,0,0,0,792,791,1,0,
  	0,0,793,93,1,0,0,0,794,795,5,51,0,0,795,796,5,62,0,0,796,797,5,52,0,0,
  	797,95,1,0,0,0,798,799,3,112,56,0,799,800,5,50,0,0,800,819,1,0,0,0,801,
  	802,5,62,0,0,802,803,3,62,31,0,803,804,5,48,0,0,804,805,3,46,23,0,805,
  	806,5,50,0,0,806,819,1,0,0,0,807,808,5,23,0,0,808,809,5,58,0,0,809,810,
  	5,62,0,0,810,811,3,62,31,0,811,812,5,48,0,0,812,813,3,46,23,0,813,814,
  	5,50,0,0,814,819,1,0,0,0,815,819,3,72,36,0,816,819,3,80,40,0,817,819,
  	3,86,43,0,818,798,1,0,0,0,818,801,1,0,0,0,818,807,1,0,0,0,818,815,1,0,
  	0,0,818,816,1,0,0,0,818,817,1,0,0,0,819,97,1,0,0,0,820,821,5,33,0,0,821,
  	822,5,62,0,0,822,823,5,51,0,0,823,828,3,34,17,0,824,825,5,49,0,0,825,
  	827,3,34,17,0,826,824,1,0,0,0,827,830,1,0,0,0,828,826,1,0,0,0,828,829,
  	1,0,0,0,829,831,1,0,0,0,830,828,1,0,0,0,831,832,5,52,0,0,832,99,1,0,0,
  	0,833,834,5,33,0,0,834,835,5,31,0,0,835,836,5,62,0,0,836,837,5,51,0,0,
  	837,842,3,34,17,0,838,839,5,49,0,0,839,841,3,34,17,0,840,838,1,0,0,0,
  	841,844,1,0,0,0,842,840,1,0,0,0,842,843,1,0,0,0,843,845,1,0,0,0,844,842,
  	1,0,0,0,845,846,5,52,0,0,846,849,1,0,0,0,847,849,3,98,49,0,848,833,1,
  	0,0,0,848,847,1,0,0,0,849,101,1,0,0,0,850,851,3,104,52,0,851,852,3,60,
  	30,0,852,855,5,62,0,0,853,854,5,48,0,0,854,856,3,34,17,0,855,853,1,0,
  	0,0,855,856,1,0,0,0,856,103,1,0,0,0,857,861,5,2,0,0,858,861,5,3,0,0,859,
  	861,5,4,0,0,860,857,1,0,0,0,860,858,1,0,0,0,860,859,1,0,0,0,861,105,1,
  	0,0,0,862,863,3,104,52,0,863,864,3,60,30,0,864,870,1,0,0,0,865,866,5,
  	32,0,0,866,867,3,104,52,0,867,868,3,60,30,0,868,870,1,0,0,0,869,862,1,
  	0,0,0,869,865,1,0,0,0,870,107,1,0,0,0,871,872,3,106,53,0,872,875,5,62,
  	0,0,873,874,5,48,0,0,874,876,3,34,17,0,875,873,1,0,0,0,875,876,1,0,0,
  	0,876,109,1,0,0,0,877,878,3,104,52,0,878,879,3,60,30,0,879,880,5,62,0,
  	0,880,881,5,48,0,0,881,882,3,46,23,0,882,111,1,0,0,0,883,884,3,104,52,
  	0,884,885,3,60,30,0,885,888,5,62,0,0,886,887,5,48,0,0,887,889,3,46,23,
  	0,888,886,1,0,0,0,888,889,1,0,0,0,889,113,1,0,0,0,71,117,121,130,139,
  	155,168,175,187,194,204,217,222,232,235,243,254,257,266,276,279,293,307,
  	312,319,329,367,378,383,400,422,425,429,438,473,484,489,506,529,532,540,
  	553,562,573,576,579,585,597,600,603,615,628,641,652,663,674,687,700,713,
  	723,744,780,792,818,828,842,848,855,860,869,875,888
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  chipsParserStaticData = std::move(staticData);
}

}

ChipsParser::ChipsParser(TokenStream *input) : ChipsParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

ChipsParser::ChipsParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  ChipsParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *chipsParserStaticData->atn, chipsParserStaticData->decisionToDFA, chipsParserStaticData->sharedContextCache, options);
}

ChipsParser::~ChipsParser() {
  delete _interpreter;
}

const atn::ATN& ChipsParser::getATN() const {
  return *chipsParserStaticData->atn;
}

std::string ChipsParser::getGrammarFileName() const {
  return "Chips.g4";
}

const std::vector<std::string>& ChipsParser::getRuleNames() const {
  return chipsParserStaticData->ruleNames;
}

const dfa::Vocabulary& ChipsParser::getVocabulary() const {
  return chipsParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView ChipsParser::getSerializedATN() const {
  return chipsParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

ChipsParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::ProgramContext::EOF() {
  return getToken(ChipsParser::EOF, 0);
}

std::vector<ChipsParser::PreambleContext *> ChipsParser::ProgramContext::preamble() {
  return getRuleContexts<ChipsParser::PreambleContext>();
}

ChipsParser::PreambleContext* ChipsParser::ProgramContext::preamble(size_t i) {
  return getRuleContext<ChipsParser::PreambleContext>(i);
}

ChipsParser::SystemContext* ChipsParser::ProgramContext::system() {
  return getRuleContext<ChipsParser::SystemContext>(0);
}


size_t ChipsParser::ProgramContext::getRuleIndex() const {
  return ChipsParser::RuleProgram;
}


std::any ChipsParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::ProgramContext* ChipsParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, ChipsParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(117);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 90177632) != 0)) {
      setState(114);
      preamble();
      setState(119);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(121);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ChipsParser::SYSTEM_KW) {
      setState(120);
      system();
    }
    setState(123);
    match(ChipsParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SystemContext ------------------------------------------------------------------

ChipsParser::SystemContext::SystemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::SystemContext::SYSTEM_KW() {
  return getToken(ChipsParser::SYSTEM_KW, 0);
}

tree::TerminalNode* ChipsParser::SystemContext::L_CURL() {
  return getToken(ChipsParser::L_CURL, 0);
}

tree::TerminalNode* ChipsParser::SystemContext::R_CURL() {
  return getToken(ChipsParser::R_CURL, 0);
}

std::vector<ChipsParser::S_statementContext *> ChipsParser::SystemContext::s_statement() {
  return getRuleContexts<ChipsParser::S_statementContext>();
}

ChipsParser::S_statementContext* ChipsParser::SystemContext::s_statement(size_t i) {
  return getRuleContext<ChipsParser::S_statementContext>(i);
}


size_t ChipsParser::SystemContext::getRuleIndex() const {
  return ChipsParser::RuleSystem;
}


std::any ChipsParser::SystemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitSystem(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::SystemContext* ChipsParser::system() {
  SystemContext *_localctx = _tracker.createInstance<SystemContext>(_ctx, getState());
  enterRule(_localctx, 2, ChipsParser::RuleSystem);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(125);
    match(ChipsParser::SYSTEM_KW);
    setState(126);
    match(ChipsParser::L_CURL);
    setState(130);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435814428) != 0)) {
      setState(127);
      s_statement();
      setState(132);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(133);
    match(ChipsParser::R_CURL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PreambleContext ------------------------------------------------------------------

ChipsParser::PreambleContext::PreambleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::PreambleContext::getRuleIndex() const {
  return ChipsParser::RulePreamble;
}

void ChipsParser::PreambleContext::copyFrom(PreambleContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CollectiveOperationDefinitionContext ------------------------------------------------------------------

ChipsParser::Collective_op_defContext* ChipsParser::CollectiveOperationDefinitionContext::collective_op_def() {
  return getRuleContext<ChipsParser::Collective_op_defContext>(0);
}

ChipsParser::CollectiveOperationDefinitionContext::CollectiveOperationDefinitionContext(PreambleContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::CollectiveOperationDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCollectiveOperationDefinition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ObjectDefinitionContext ------------------------------------------------------------------

ChipsParser::Object_defContext* ChipsParser::ObjectDefinitionContext::object_def() {
  return getRuleContext<ChipsParser::Object_defContext>(0);
}

ChipsParser::ObjectDefinitionContext::ObjectDefinitionContext(PreambleContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::ObjectDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitObjectDefinition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionDefinitionContext ------------------------------------------------------------------

ChipsParser::Function_defContext* ChipsParser::FunctionDefinitionContext::function_def() {
  return getRuleContext<ChipsParser::Function_defContext>(0);
}

ChipsParser::FunctionDefinitionContext::FunctionDefinitionContext(PreambleContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::FunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ImplementationDefinitionContext ------------------------------------------------------------------

ChipsParser::Implementation_defContext* ChipsParser::ImplementationDefinitionContext::implementation_def() {
  return getRuleContext<ChipsParser::Implementation_defContext>(0);
}

ChipsParser::ImplementationDefinitionContext::ImplementationDefinitionContext(PreambleContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::ImplementationDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitImplementationDefinition(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::PreambleContext* ChipsParser::preamble() {
  PreambleContext *_localctx = _tracker.createInstance<PreambleContext>(_ctx, getState());
  enterRule(_localctx, 4, ChipsParser::RulePreamble);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(139);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ChipsParser::OBJECT_KW: {
        _localctx = _tracker.createInstance<ChipsParser::ObjectDefinitionContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(135);
        object_def();
        break;
      }

      case ChipsParser::LOGICAL_KW:
      case ChipsParser::PHYSICAL_KW: {
        _localctx = _tracker.createInstance<ChipsParser::FunctionDefinitionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(136);
        function_def();
        break;
      }

      case ChipsParser::SPREAD_KW:
      case ChipsParser::COLLECT_KW: {
        _localctx = _tracker.createInstance<ChipsParser::CollectiveOperationDefinitionContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(137);
        collective_op_def();
        break;
      }

      case ChipsParser::IMPLEMENTATION_KW: {
        _localctx = _tracker.createInstance<ChipsParser::ImplementationDefinitionContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(138);
        implementation_def();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Object_defContext ------------------------------------------------------------------

ChipsParser::Object_defContext::Object_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::Object_defContext::OBJECT_KW() {
  return getToken(ChipsParser::OBJECT_KW, 0);
}

tree::TerminalNode* ChipsParser::Object_defContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

ChipsParser::With_sectionContext* ChipsParser::Object_defContext::with_section() {
  return getRuleContext<ChipsParser::With_sectionContext>(0);
}


size_t ChipsParser::Object_defContext::getRuleIndex() const {
  return ChipsParser::RuleObject_def;
}


std::any ChipsParser::Object_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitObject_def(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::Object_defContext* ChipsParser::object_def() {
  Object_defContext *_localctx = _tracker.createInstance<Object_defContext>(_ctx, getState());
  enterRule(_localctx, 6, ChipsParser::RuleObject_def);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(141);
    match(ChipsParser::OBJECT_KW);
    setState(142);
    match(ChipsParser::IDENTIFIER);
    setState(143);
    with_section();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Implementation_defContext ------------------------------------------------------------------

ChipsParser::Implementation_defContext::Implementation_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::Implementation_defContext::IMPLEMENTATION_KW() {
  return getToken(ChipsParser::IMPLEMENTATION_KW, 0);
}

std::vector<tree::TerminalNode *> ChipsParser::Implementation_defContext::IDENTIFIER() {
  return getTokens(ChipsParser::IDENTIFIER);
}

tree::TerminalNode* ChipsParser::Implementation_defContext::IDENTIFIER(size_t i) {
  return getToken(ChipsParser::IDENTIFIER, i);
}

tree::TerminalNode* ChipsParser::Implementation_defContext::COLUMN() {
  return getToken(ChipsParser::COLUMN, 0);
}

tree::TerminalNode* ChipsParser::Implementation_defContext::BY_KW() {
  return getToken(ChipsParser::BY_KW, 0);
}

tree::TerminalNode* ChipsParser::Implementation_defContext::L_CURL() {
  return getToken(ChipsParser::L_CURL, 0);
}

tree::TerminalNode* ChipsParser::Implementation_defContext::R_CURL() {
  return getToken(ChipsParser::R_CURL, 0);
}

std::vector<ChipsParser::Node_mappingContext *> ChipsParser::Implementation_defContext::node_mapping() {
  return getRuleContexts<ChipsParser::Node_mappingContext>();
}

ChipsParser::Node_mappingContext* ChipsParser::Implementation_defContext::node_mapping(size_t i) {
  return getRuleContext<ChipsParser::Node_mappingContext>(i);
}


size_t ChipsParser::Implementation_defContext::getRuleIndex() const {
  return ChipsParser::RuleImplementation_def;
}


std::any ChipsParser::Implementation_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitImplementation_def(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::Implementation_defContext* ChipsParser::implementation_def() {
  Implementation_defContext *_localctx = _tracker.createInstance<Implementation_defContext>(_ctx, getState());
  enterRule(_localctx, 8, ChipsParser::RuleImplementation_def);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(145);
    match(ChipsParser::IMPLEMENTATION_KW);
    setState(146);
    match(ChipsParser::IDENTIFIER);
    setState(147);
    match(ChipsParser::COLUMN);
    setState(148);
    match(ChipsParser::IDENTIFIER);
    setState(149);
    match(ChipsParser::BY_KW);
    setState(150);
    match(ChipsParser::IDENTIFIER);
    setState(151);
    match(ChipsParser::L_CURL);
    setState(155);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ChipsParser::HAVING_KW) {
      setState(152);
      node_mapping();
      setState(157);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(158);
    match(ChipsParser::R_CURL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Node_mappingContext ------------------------------------------------------------------

ChipsParser::Node_mappingContext::Node_mappingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::Node_mappingContext::HAVING_KW() {
  return getToken(ChipsParser::HAVING_KW, 0);
}

std::vector<tree::TerminalNode *> ChipsParser::Node_mappingContext::IDENTIFIER() {
  return getTokens(ChipsParser::IDENTIFIER);
}

tree::TerminalNode* ChipsParser::Node_mappingContext::IDENTIFIER(size_t i) {
  return getToken(ChipsParser::IDENTIFIER, i);
}

tree::TerminalNode* ChipsParser::Node_mappingContext::AS_KW() {
  return getToken(ChipsParser::AS_KW, 0);
}

tree::TerminalNode* ChipsParser::Node_mappingContext::SEMICOL() {
  return getToken(ChipsParser::SEMICOL, 0);
}


size_t ChipsParser::Node_mappingContext::getRuleIndex() const {
  return ChipsParser::RuleNode_mapping;
}


std::any ChipsParser::Node_mappingContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitNode_mapping(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::Node_mappingContext* ChipsParser::node_mapping() {
  Node_mappingContext *_localctx = _tracker.createInstance<Node_mappingContext>(_ctx, getState());
  enterRule(_localctx, 10, ChipsParser::RuleNode_mapping);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(160);
    match(ChipsParser::HAVING_KW);
    setState(161);
    match(ChipsParser::IDENTIFIER);
    setState(162);
    match(ChipsParser::AS_KW);
    setState(163);
    match(ChipsParser::IDENTIFIER);
    setState(164);
    match(ChipsParser::SEMICOL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Function_defContext ------------------------------------------------------------------

ChipsParser::Function_defContext::Function_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::Function_defContext::getRuleIndex() const {
  return ChipsParser::RuleFunction_def;
}

void ChipsParser::Function_defContext::copyFrom(Function_defContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LogicalDefintionContext ------------------------------------------------------------------

ChipsParser::L_function_defContext* ChipsParser::LogicalDefintionContext::l_function_def() {
  return getRuleContext<ChipsParser::L_function_defContext>(0);
}

ChipsParser::LogicalDefintionContext::LogicalDefintionContext(Function_defContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::LogicalDefintionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitLogicalDefintion(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PhysicalDefinitionContext ------------------------------------------------------------------

ChipsParser::P_function_defContext* ChipsParser::PhysicalDefinitionContext::p_function_def() {
  return getRuleContext<ChipsParser::P_function_defContext>(0);
}

ChipsParser::PhysicalDefinitionContext::PhysicalDefinitionContext(Function_defContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::PhysicalDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitPhysicalDefinition(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::Function_defContext* ChipsParser::function_def() {
  Function_defContext *_localctx = _tracker.createInstance<Function_defContext>(_ctx, getState());
  enterRule(_localctx, 12, ChipsParser::RuleFunction_def);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(168);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ChipsParser::LOGICAL_KW: {
        _localctx = _tracker.createInstance<ChipsParser::LogicalDefintionContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(166);
        l_function_def();
        break;
      }

      case ChipsParser::PHYSICAL_KW: {
        _localctx = _tracker.createInstance<ChipsParser::PhysicalDefinitionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(167);
        p_function_def();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Collective_op_defContext ------------------------------------------------------------------

ChipsParser::Collective_op_defContext::Collective_op_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ChipsParser::C_signatureContext* ChipsParser::Collective_op_defContext::c_signature() {
  return getRuleContext<ChipsParser::C_signatureContext>(0);
}

tree::TerminalNode* ChipsParser::Collective_op_defContext::L_CURL() {
  return getToken(ChipsParser::L_CURL, 0);
}

tree::TerminalNode* ChipsParser::Collective_op_defContext::R_CURL() {
  return getToken(ChipsParser::R_CURL, 0);
}

tree::TerminalNode* ChipsParser::Collective_op_defContext::ARROW() {
  return getToken(ChipsParser::ARROW, 0);
}

tree::TerminalNode* ChipsParser::Collective_op_defContext::TARGET_KW() {
  return getToken(ChipsParser::TARGET_KW, 0);
}

tree::TerminalNode* ChipsParser::Collective_op_defContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

std::vector<ChipsParser::C_exprContext *> ChipsParser::Collective_op_defContext::c_expr() {
  return getRuleContexts<ChipsParser::C_exprContext>();
}

ChipsParser::C_exprContext* ChipsParser::Collective_op_defContext::c_expr(size_t i) {
  return getRuleContext<ChipsParser::C_exprContext>(i);
}

tree::TerminalNode* ChipsParser::Collective_op_defContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

std::vector<ChipsParser::C_statementContext *> ChipsParser::Collective_op_defContext::c_statement() {
  return getRuleContexts<ChipsParser::C_statementContext>();
}

ChipsParser::C_statementContext* ChipsParser::Collective_op_defContext::c_statement(size_t i) {
  return getRuleContext<ChipsParser::C_statementContext>(i);
}

std::vector<tree::TerminalNode *> ChipsParser::Collective_op_defContext::COMMA() {
  return getTokens(ChipsParser::COMMA);
}

tree::TerminalNode* ChipsParser::Collective_op_defContext::COMMA(size_t i) {
  return getToken(ChipsParser::COMMA, i);
}

std::vector<ChipsParser::C_outputContext *> ChipsParser::Collective_op_defContext::c_output() {
  return getRuleContexts<ChipsParser::C_outputContext>();
}

ChipsParser::C_outputContext* ChipsParser::Collective_op_defContext::c_output(size_t i) {
  return getRuleContext<ChipsParser::C_outputContext>(i);
}


size_t ChipsParser::Collective_op_defContext::getRuleIndex() const {
  return ChipsParser::RuleCollective_op_def;
}


std::any ChipsParser::Collective_op_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCollective_op_def(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::Collective_op_defContext* ChipsParser::collective_op_def() {
  Collective_op_defContext *_localctx = _tracker.createInstance<Collective_op_defContext>(_ctx, getState());
  enterRule(_localctx, 14, ChipsParser::RuleCollective_op_def);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
    c_signature();
    setState(171);
    match(ChipsParser::L_CURL);
    setState(175);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(172);
      c_statement();
      setState(177);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(178);
    match(ChipsParser::R_CURL);
    setState(179);
    match(ChipsParser::ARROW);
    setState(180);
    match(ChipsParser::TARGET_KW);
    setState(181);
    match(ChipsParser::L_PARENTH);
    setState(182);
    c_expr();
    setState(187);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ChipsParser::COMMA) {
      setState(183);
      match(ChipsParser::COMMA);
      setState(184);
      c_expr();
      setState(189);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(190);
    match(ChipsParser::R_PARENTH);
    setState(192); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(191);
      c_output();
      setState(194); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ChipsParser::ARROW);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- C_outputContext ------------------------------------------------------------------

ChipsParser::C_outputContext::C_outputContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::C_outputContext::getRuleIndex() const {
  return ChipsParser::RuleC_output;
}

void ChipsParser::C_outputContext::copyFrom(C_outputContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DefaultOutputContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::DefaultOutputContext::ARROW() {
  return getToken(ChipsParser::ARROW, 0);
}

tree::TerminalNode* ChipsParser::DefaultOutputContext::DEFAULT_KW() {
  return getToken(ChipsParser::DEFAULT_KW, 0);
}

tree::TerminalNode* ChipsParser::DefaultOutputContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

std::vector<ChipsParser::C_exprContext *> ChipsParser::DefaultOutputContext::c_expr() {
  return getRuleContexts<ChipsParser::C_exprContext>();
}

ChipsParser::C_exprContext* ChipsParser::DefaultOutputContext::c_expr(size_t i) {
  return getRuleContext<ChipsParser::C_exprContext>(i);
}

tree::TerminalNode* ChipsParser::DefaultOutputContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

std::vector<tree::TerminalNode *> ChipsParser::DefaultOutputContext::COMMA() {
  return getTokens(ChipsParser::COMMA);
}

tree::TerminalNode* ChipsParser::DefaultOutputContext::COMMA(size_t i) {
  return getToken(ChipsParser::COMMA, i);
}

ChipsParser::DefaultOutputContext::DefaultOutputContext(C_outputContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::DefaultOutputContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitDefaultOutput(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ChanneledOutputContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::ChanneledOutputContext::ARROW() {
  return getToken(ChipsParser::ARROW, 0);
}

tree::TerminalNode* ChipsParser::ChanneledOutputContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::ChanneledOutputContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

std::vector<ChipsParser::C_exprContext *> ChipsParser::ChanneledOutputContext::c_expr() {
  return getRuleContexts<ChipsParser::C_exprContext>();
}

ChipsParser::C_exprContext* ChipsParser::ChanneledOutputContext::c_expr(size_t i) {
  return getRuleContext<ChipsParser::C_exprContext>(i);
}

tree::TerminalNode* ChipsParser::ChanneledOutputContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

std::vector<tree::TerminalNode *> ChipsParser::ChanneledOutputContext::COMMA() {
  return getTokens(ChipsParser::COMMA);
}

tree::TerminalNode* ChipsParser::ChanneledOutputContext::COMMA(size_t i) {
  return getToken(ChipsParser::COMMA, i);
}

ChipsParser::ChanneledOutputContext::ChanneledOutputContext(C_outputContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::ChanneledOutputContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitChanneledOutput(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::C_outputContext* ChipsParser::c_output() {
  C_outputContext *_localctx = _tracker.createInstance<C_outputContext>(_ctx, getState());
  enterRule(_localctx, 16, ChipsParser::RuleC_output);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(222);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::DefaultOutputContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(196);
      match(ChipsParser::ARROW);
      setState(197);
      match(ChipsParser::DEFAULT_KW);
      setState(198);
      match(ChipsParser::L_PARENTH);
      setState(199);
      c_expr();
      setState(204);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ChipsParser::COMMA) {
        setState(200);
        match(ChipsParser::COMMA);
        setState(201);
        c_expr();
        setState(206);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(207);
      match(ChipsParser::R_PARENTH);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::ChanneledOutputContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(209);
      match(ChipsParser::ARROW);
      setState(210);
      match(ChipsParser::IDENTIFIER);
      setState(211);
      match(ChipsParser::L_PARENTH);
      setState(212);
      c_expr();
      setState(217);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ChipsParser::COMMA) {
        setState(213);
        match(ChipsParser::COMMA);
        setState(214);
        c_expr();
        setState(219);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(220);
      match(ChipsParser::R_PARENTH);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- L_function_defContext ------------------------------------------------------------------

ChipsParser::L_function_defContext::L_function_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::L_function_defContext::LOGICAL_KW() {
  return getToken(ChipsParser::LOGICAL_KW, 0);
}

tree::TerminalNode* ChipsParser::L_function_defContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::L_function_defContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

tree::TerminalNode* ChipsParser::L_function_defContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

ChipsParser::Init_sectionContext* ChipsParser::L_function_defContext::init_section() {
  return getRuleContext<ChipsParser::Init_sectionContext>(0);
}

ChipsParser::Then_sectionContext* ChipsParser::L_function_defContext::then_section() {
  return getRuleContext<ChipsParser::Then_sectionContext>(0);
}

std::vector<ChipsParser::Df_parameter_declContext *> ChipsParser::L_function_defContext::df_parameter_decl() {
  return getRuleContexts<ChipsParser::Df_parameter_declContext>();
}

ChipsParser::Df_parameter_declContext* ChipsParser::L_function_defContext::df_parameter_decl(size_t i) {
  return getRuleContext<ChipsParser::Df_parameter_declContext>(i);
}

std::vector<ChipsParser::Named_outputContext *> ChipsParser::L_function_defContext::named_output() {
  return getRuleContexts<ChipsParser::Named_outputContext>();
}

ChipsParser::Named_outputContext* ChipsParser::L_function_defContext::named_output(size_t i) {
  return getRuleContext<ChipsParser::Named_outputContext>(i);
}

std::vector<tree::TerminalNode *> ChipsParser::L_function_defContext::COMMA() {
  return getTokens(ChipsParser::COMMA);
}

tree::TerminalNode* ChipsParser::L_function_defContext::COMMA(size_t i) {
  return getToken(ChipsParser::COMMA, i);
}


size_t ChipsParser::L_function_defContext::getRuleIndex() const {
  return ChipsParser::RuleL_function_def;
}


std::any ChipsParser::L_function_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitL_function_def(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::L_function_defContext* ChipsParser::l_function_def() {
  L_function_defContext *_localctx = _tracker.createInstance<L_function_defContext>(_ctx, getState());
  enterRule(_localctx, 18, ChipsParser::RuleL_function_def);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(224);
    match(ChipsParser::LOGICAL_KW);
    setState(225);
    match(ChipsParser::IDENTIFIER);
    setState(226);
    match(ChipsParser::L_PARENTH);
    setState(235);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 28) != 0)) {
      setState(227);
      df_parameter_decl();
      setState(232);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ChipsParser::COMMA) {
        setState(228);
        match(ChipsParser::COMMA);
        setState(229);
        df_parameter_decl();
        setState(234);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(237);
    match(ChipsParser::R_PARENTH);
    setState(238);
    init_section();
    setState(239);
    then_section();
    setState(243);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ChipsParser::ARROW) {
      setState(240);
      named_output();
      setState(245);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- P_function_defContext ------------------------------------------------------------------

ChipsParser::P_function_defContext::P_function_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::P_function_defContext::PHYSICAL_KW() {
  return getToken(ChipsParser::PHYSICAL_KW, 0);
}

tree::TerminalNode* ChipsParser::P_function_defContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::P_function_defContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

tree::TerminalNode* ChipsParser::P_function_defContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

ChipsParser::With_sectionContext* ChipsParser::P_function_defContext::with_section() {
  return getRuleContext<ChipsParser::With_sectionContext>(0);
}

ChipsParser::Init_sectionContext* ChipsParser::P_function_defContext::init_section() {
  return getRuleContext<ChipsParser::Init_sectionContext>(0);
}

ChipsParser::Then_sectionContext* ChipsParser::P_function_defContext::then_section() {
  return getRuleContext<ChipsParser::Then_sectionContext>(0);
}

std::vector<ChipsParser::Pdf_parameter_declContext *> ChipsParser::P_function_defContext::pdf_parameter_decl() {
  return getRuleContexts<ChipsParser::Pdf_parameter_declContext>();
}

ChipsParser::Pdf_parameter_declContext* ChipsParser::P_function_defContext::pdf_parameter_decl(size_t i) {
  return getRuleContext<ChipsParser::Pdf_parameter_declContext>(i);
}

std::vector<ChipsParser::P_named_outputContext *> ChipsParser::P_function_defContext::p_named_output() {
  return getRuleContexts<ChipsParser::P_named_outputContext>();
}

ChipsParser::P_named_outputContext* ChipsParser::P_function_defContext::p_named_output(size_t i) {
  return getRuleContext<ChipsParser::P_named_outputContext>(i);
}

std::vector<tree::TerminalNode *> ChipsParser::P_function_defContext::COMMA() {
  return getTokens(ChipsParser::COMMA);
}

tree::TerminalNode* ChipsParser::P_function_defContext::COMMA(size_t i) {
  return getToken(ChipsParser::COMMA, i);
}


size_t ChipsParser::P_function_defContext::getRuleIndex() const {
  return ChipsParser::RuleP_function_def;
}


std::any ChipsParser::P_function_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitP_function_def(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::P_function_defContext* ChipsParser::p_function_def() {
  P_function_defContext *_localctx = _tracker.createInstance<P_function_defContext>(_ctx, getState());
  enterRule(_localctx, 20, ChipsParser::RuleP_function_def);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(246);
    match(ChipsParser::PHYSICAL_KW);
    setState(247);
    match(ChipsParser::IDENTIFIER);
    setState(248);
    match(ChipsParser::L_PARENTH);
    setState(257);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4294967324) != 0)) {
      setState(249);
      pdf_parameter_decl();
      setState(254);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ChipsParser::COMMA) {
        setState(250);
        match(ChipsParser::COMMA);
        setState(251);
        pdf_parameter_decl();
        setState(256);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(259);
    match(ChipsParser::R_PARENTH);
    setState(260);
    with_section();
    setState(261);
    init_section();
    setState(262);
    then_section();
    setState(266);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ChipsParser::ARROW) {
      setState(263);
      p_named_output();
      setState(268);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- C_signatureContext ------------------------------------------------------------------

ChipsParser::C_signatureContext::C_signatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ChipsParser::C_keywordsContext* ChipsParser::C_signatureContext::c_keywords() {
  return getRuleContext<ChipsParser::C_keywordsContext>(0);
}

tree::TerminalNode* ChipsParser::C_signatureContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

tree::TerminalNode* ChipsParser::C_signatureContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

std::vector<tree::TerminalNode *> ChipsParser::C_signatureContext::IDENTIFIER() {
  return getTokens(ChipsParser::IDENTIFIER);
}

tree::TerminalNode* ChipsParser::C_signatureContext::IDENTIFIER(size_t i) {
  return getToken(ChipsParser::IDENTIFIER, i);
}

tree::TerminalNode* ChipsParser::C_signatureContext::AMONG_KW() {
  return getToken(ChipsParser::AMONG_KW, 0);
}

std::vector<ChipsParser::Cdf_defaulted_declContext *> ChipsParser::C_signatureContext::cdf_defaulted_decl() {
  return getRuleContexts<ChipsParser::Cdf_defaulted_declContext>();
}

ChipsParser::Cdf_defaulted_declContext* ChipsParser::C_signatureContext::cdf_defaulted_decl(size_t i) {
  return getRuleContext<ChipsParser::Cdf_defaulted_declContext>(i);
}

std::vector<tree::TerminalNode *> ChipsParser::C_signatureContext::COMMA() {
  return getTokens(ChipsParser::COMMA);
}

tree::TerminalNode* ChipsParser::C_signatureContext::COMMA(size_t i) {
  return getToken(ChipsParser::COMMA, i);
}


size_t ChipsParser::C_signatureContext::getRuleIndex() const {
  return ChipsParser::RuleC_signature;
}


std::any ChipsParser::C_signatureContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitC_signature(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::C_signatureContext* ChipsParser::c_signature() {
  C_signatureContext *_localctx = _tracker.createInstance<C_signatureContext>(_ctx, getState());
  enterRule(_localctx, 22, ChipsParser::RuleC_signature);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(269);
    c_keywords();
    setState(270);
    match(ChipsParser::L_PARENTH);
    setState(279);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 28) != 0)) {
      setState(271);
      cdf_defaulted_decl();
      setState(276);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ChipsParser::COMMA) {
        setState(272);
        match(ChipsParser::COMMA);
        setState(273);
        cdf_defaulted_decl();
        setState(278);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(281);
    match(ChipsParser::R_PARENTH);
    setState(282);
    match(ChipsParser::IDENTIFIER);
    setState(283);
    match(ChipsParser::AMONG_KW);
    setState(284);
    match(ChipsParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- C_keywordsContext ------------------------------------------------------------------

ChipsParser::C_keywordsContext::C_keywordsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::C_keywordsContext::SPREAD_KW() {
  return getToken(ChipsParser::SPREAD_KW, 0);
}

tree::TerminalNode* ChipsParser::C_keywordsContext::COLLECT_KW() {
  return getToken(ChipsParser::COLLECT_KW, 0);
}


size_t ChipsParser::C_keywordsContext::getRuleIndex() const {
  return ChipsParser::RuleC_keywords;
}


std::any ChipsParser::C_keywordsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitC_keywords(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::C_keywordsContext* ChipsParser::c_keywords() {
  C_keywordsContext *_localctx = _tracker.createInstance<C_keywordsContext>(_ctx, getState());
  enterRule(_localctx, 24, ChipsParser::RuleC_keywords);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(286);
    _la = _input->LA(1);
    if (!(_la == ChipsParser::SPREAD_KW

    || _la == ChipsParser::COLLECT_KW)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- With_sectionContext ------------------------------------------------------------------

ChipsParser::With_sectionContext::With_sectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::With_sectionContext::WITH_KW() {
  return getToken(ChipsParser::WITH_KW, 0);
}

tree::TerminalNode* ChipsParser::With_sectionContext::L_CURL() {
  return getToken(ChipsParser::L_CURL, 0);
}

tree::TerminalNode* ChipsParser::With_sectionContext::R_CURL() {
  return getToken(ChipsParser::R_CURL, 0);
}

std::vector<ChipsParser::With_statementContext *> ChipsParser::With_sectionContext::with_statement() {
  return getRuleContexts<ChipsParser::With_statementContext>();
}

ChipsParser::With_statementContext* ChipsParser::With_sectionContext::with_statement(size_t i) {
  return getRuleContext<ChipsParser::With_statementContext>(i);
}


size_t ChipsParser::With_sectionContext::getRuleIndex() const {
  return ChipsParser::RuleWith_section;
}


std::any ChipsParser::With_sectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitWith_section(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::With_sectionContext* ChipsParser::with_section() {
  With_sectionContext *_localctx = _tracker.createInstance<With_sectionContext>(_ctx, getState());
  enterRule(_localctx, 26, ChipsParser::RuleWith_section);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(288);
    match(ChipsParser::WITH_KW);
    setState(289);
    match(ChipsParser::L_CURL);
    setState(293);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(290);
      with_statement();
      setState(295);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(296);
    match(ChipsParser::R_CURL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- With_statementContext ------------------------------------------------------------------

ChipsParser::With_statementContext::With_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::With_statementContext::getRuleIndex() const {
  return ChipsParser::RuleWith_statement;
}

void ChipsParser::With_statementContext::copyFrom(With_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ContextualDeclarationContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::ContextualDeclarationContext::CTX_KW() {
  return getToken(ChipsParser::CTX_KW, 0);
}

ChipsParser::Df_typeContext* ChipsParser::ContextualDeclarationContext::df_type() {
  return getRuleContext<ChipsParser::Df_typeContext>(0);
}

ChipsParser::SuffixesContext* ChipsParser::ContextualDeclarationContext::suffixes() {
  return getRuleContext<ChipsParser::SuffixesContext>(0);
}

tree::TerminalNode* ChipsParser::ContextualDeclarationContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::ContextualDeclarationContext::SEMICOL() {
  return getToken(ChipsParser::SEMICOL, 0);
}

tree::TerminalNode* ChipsParser::ContextualDeclarationContext::ASSIGN() {
  return getToken(ChipsParser::ASSIGN, 0);
}

ChipsParser::ExprContext* ChipsParser::ContextualDeclarationContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}

ChipsParser::ContextualDeclarationContext::ContextualDeclarationContext(With_statementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::ContextualDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitContextualDeclaration(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WithRegularStatementContext ------------------------------------------------------------------

ChipsParser::StatementContext* ChipsParser::WithRegularStatementContext::statement() {
  return getRuleContext<ChipsParser::StatementContext>(0);
}

ChipsParser::WithRegularStatementContext::WithRegularStatementContext(With_statementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::WithRegularStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitWithRegularStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ChannelDeclarationContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> ChipsParser::ChannelDeclarationContext::IDENTIFIER() {
  return getTokens(ChipsParser::IDENTIFIER);
}

tree::TerminalNode* ChipsParser::ChannelDeclarationContext::IDENTIFIER(size_t i) {
  return getToken(ChipsParser::IDENTIFIER, i);
}

tree::TerminalNode* ChipsParser::ChannelDeclarationContext::SEMICOL() {
  return getToken(ChipsParser::SEMICOL, 0);
}

ChipsParser::ChannelDeclarationContext::ChannelDeclarationContext(With_statementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::ChannelDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitChannelDeclaration(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::With_statementContext* ChipsParser::with_statement() {
  With_statementContext *_localctx = _tracker.createInstance<With_statementContext>(_ctx, getState());
  enterRule(_localctx, 28, ChipsParser::RuleWith_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(312);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::ChannelDeclarationContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(298);
      match(ChipsParser::IDENTIFIER);
      setState(299);
      match(ChipsParser::IDENTIFIER);
      setState(300);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::ContextualDeclarationContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(301);
      match(ChipsParser::CTX_KW);
      setState(302);
      df_type();
      setState(303);
      suffixes();
      setState(304);
      match(ChipsParser::IDENTIFIER);
      setState(307);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ChipsParser::ASSIGN) {
        setState(305);
        match(ChipsParser::ASSIGN);
        setState(306);
        expr();
      }
      setState(309);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::WithRegularStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(311);
      statement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Init_sectionContext ------------------------------------------------------------------

ChipsParser::Init_sectionContext::Init_sectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::Init_sectionContext::INIT_KW() {
  return getToken(ChipsParser::INIT_KW, 0);
}

tree::TerminalNode* ChipsParser::Init_sectionContext::L_CURL() {
  return getToken(ChipsParser::L_CURL, 0);
}

tree::TerminalNode* ChipsParser::Init_sectionContext::R_CURL() {
  return getToken(ChipsParser::R_CURL, 0);
}

std::vector<ChipsParser::StatementContext *> ChipsParser::Init_sectionContext::statement() {
  return getRuleContexts<ChipsParser::StatementContext>();
}

ChipsParser::StatementContext* ChipsParser::Init_sectionContext::statement(size_t i) {
  return getRuleContext<ChipsParser::StatementContext>(i);
}


size_t ChipsParser::Init_sectionContext::getRuleIndex() const {
  return ChipsParser::RuleInit_section;
}


std::any ChipsParser::Init_sectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitInit_section(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::Init_sectionContext* ChipsParser::init_section() {
  Init_sectionContext *_localctx = _tracker.createInstance<Init_sectionContext>(_ctx, getState());
  enterRule(_localctx, 30, ChipsParser::RuleInit_section);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(314);
    match(ChipsParser::INIT_KW);
    setState(315);
    match(ChipsParser::L_CURL);
    setState(319);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(316);
      statement();
      setState(321);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(322);
    match(ChipsParser::R_CURL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Then_sectionContext ------------------------------------------------------------------

ChipsParser::Then_sectionContext::Then_sectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::Then_sectionContext::THEN_KW() {
  return getToken(ChipsParser::THEN_KW, 0);
}

tree::TerminalNode* ChipsParser::Then_sectionContext::L_CURL() {
  return getToken(ChipsParser::L_CURL, 0);
}

tree::TerminalNode* ChipsParser::Then_sectionContext::R_CURL() {
  return getToken(ChipsParser::R_CURL, 0);
}

std::vector<ChipsParser::StatementContext *> ChipsParser::Then_sectionContext::statement() {
  return getRuleContexts<ChipsParser::StatementContext>();
}

ChipsParser::StatementContext* ChipsParser::Then_sectionContext::statement(size_t i) {
  return getRuleContext<ChipsParser::StatementContext>(i);
}


size_t ChipsParser::Then_sectionContext::getRuleIndex() const {
  return ChipsParser::RuleThen_section;
}


std::any ChipsParser::Then_sectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitThen_section(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::Then_sectionContext* ChipsParser::then_section() {
  Then_sectionContext *_localctx = _tracker.createInstance<Then_sectionContext>(_ctx, getState());
  enterRule(_localctx, 32, ChipsParser::RuleThen_section);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(324);
    match(ChipsParser::THEN_KW);
    setState(325);
    match(ChipsParser::L_CURL);
    setState(329);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(326);
      statement();
      setState(331);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(332);
    match(ChipsParser::R_CURL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

ChipsParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::ExprContext::getRuleIndex() const {
  return ChipsParser::RuleExpr;
}

void ChipsParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- GEQContext ------------------------------------------------------------------

ChipsParser::Expr0Context* ChipsParser::GEQContext::expr0() {
  return getRuleContext<ChipsParser::Expr0Context>(0);
}

tree::TerminalNode* ChipsParser::GEQContext::GEQ() {
  return getToken(ChipsParser::GEQ, 0);
}

ChipsParser::ExprContext* ChipsParser::GEQContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}

ChipsParser::GEQContext::GEQContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::GEQContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitGEQ(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ORContext ------------------------------------------------------------------

ChipsParser::Expr0Context* ChipsParser::ORContext::expr0() {
  return getRuleContext<ChipsParser::Expr0Context>(0);
}

tree::TerminalNode* ChipsParser::ORContext::OR() {
  return getToken(ChipsParser::OR, 0);
}

ChipsParser::ExprContext* ChipsParser::ORContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}

ChipsParser::ORContext::ORContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::ORContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitOR(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ANDContext ------------------------------------------------------------------

ChipsParser::Expr0Context* ChipsParser::ANDContext::expr0() {
  return getRuleContext<ChipsParser::Expr0Context>(0);
}

tree::TerminalNode* ChipsParser::ANDContext::AND() {
  return getToken(ChipsParser::AND, 0);
}

ChipsParser::ExprContext* ChipsParser::ANDContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}

ChipsParser::ANDContext::ANDContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::ANDContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitAND(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LTContext ------------------------------------------------------------------

ChipsParser::Expr0Context* ChipsParser::LTContext::expr0() {
  return getRuleContext<ChipsParser::Expr0Context>(0);
}

tree::TerminalNode* ChipsParser::LTContext::LT() {
  return getToken(ChipsParser::LT, 0);
}

ChipsParser::ExprContext* ChipsParser::LTContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}

ChipsParser::LTContext::LTContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::LTContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitLT(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LEQContext ------------------------------------------------------------------

ChipsParser::Expr0Context* ChipsParser::LEQContext::expr0() {
  return getRuleContext<ChipsParser::Expr0Context>(0);
}

tree::TerminalNode* ChipsParser::LEQContext::LEQ() {
  return getToken(ChipsParser::LEQ, 0);
}

ChipsParser::ExprContext* ChipsParser::LEQContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}

ChipsParser::LEQContext::LEQContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::LEQContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitLEQ(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassExpr0Context ------------------------------------------------------------------

ChipsParser::Expr0Context* ChipsParser::PassExpr0Context::expr0() {
  return getRuleContext<ChipsParser::Expr0Context>(0);
}

ChipsParser::PassExpr0Context::PassExpr0Context(ExprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::PassExpr0Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitPassExpr0(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NEQContext ------------------------------------------------------------------

ChipsParser::Expr0Context* ChipsParser::NEQContext::expr0() {
  return getRuleContext<ChipsParser::Expr0Context>(0);
}

tree::TerminalNode* ChipsParser::NEQContext::NEQ() {
  return getToken(ChipsParser::NEQ, 0);
}

ChipsParser::ExprContext* ChipsParser::NEQContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}

ChipsParser::NEQContext::NEQContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::NEQContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitNEQ(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EQContext ------------------------------------------------------------------

ChipsParser::Expr0Context* ChipsParser::EQContext::expr0() {
  return getRuleContext<ChipsParser::Expr0Context>(0);
}

tree::TerminalNode* ChipsParser::EQContext::EQ() {
  return getToken(ChipsParser::EQ, 0);
}

ChipsParser::ExprContext* ChipsParser::EQContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}

ChipsParser::EQContext::EQContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::EQContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitEQ(this);
  else
    return visitor->visitChildren(this);
}
//----------------- GTContext ------------------------------------------------------------------

ChipsParser::Expr0Context* ChipsParser::GTContext::expr0() {
  return getRuleContext<ChipsParser::Expr0Context>(0);
}

tree::TerminalNode* ChipsParser::GTContext::GT() {
  return getToken(ChipsParser::GT, 0);
}

ChipsParser::ExprContext* ChipsParser::GTContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}

ChipsParser::GTContext::GTContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::GTContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitGT(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::ExprContext* ChipsParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 34, ChipsParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(367);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::LTContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(334);
      expr0();
      setState(335);
      match(ChipsParser::LT);
      setState(336);
      expr();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::GTContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(338);
      expr0();
      setState(339);
      match(ChipsParser::GT);
      setState(340);
      expr();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::LEQContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(342);
      expr0();
      setState(343);
      match(ChipsParser::LEQ);
      setState(344);
      expr();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::GEQContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(346);
      expr0();
      setState(347);
      match(ChipsParser::GEQ);
      setState(348);
      expr();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::NEQContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(350);
      expr0();
      setState(351);
      match(ChipsParser::NEQ);
      setState(352);
      expr();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ChipsParser::EQContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(354);
      expr0();
      setState(355);
      match(ChipsParser::EQ);
      setState(356);
      expr();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ChipsParser::ANDContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(358);
      expr0();
      setState(359);
      match(ChipsParser::AND);
      setState(360);
      expr();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<ChipsParser::ORContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(362);
      expr0();
      setState(363);
      match(ChipsParser::OR);
      setState(364);
      expr();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<ChipsParser::PassExpr0Context>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(366);
      expr0();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Expr0Context ------------------------------------------------------------------

ChipsParser::Expr0Context::Expr0Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::Expr0Context::getRuleIndex() const {
  return ChipsParser::RuleExpr0;
}

void ChipsParser::Expr0Context::copyFrom(Expr0Context *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SUBContext ------------------------------------------------------------------

ChipsParser::Expr01Context* ChipsParser::SUBContext::expr01() {
  return getRuleContext<ChipsParser::Expr01Context>(0);
}

tree::TerminalNode* ChipsParser::SUBContext::MINUS() {
  return getToken(ChipsParser::MINUS, 0);
}

ChipsParser::Expr0Context* ChipsParser::SUBContext::expr0() {
  return getRuleContext<ChipsParser::Expr0Context>(0);
}

ChipsParser::SUBContext::SUBContext(Expr0Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::SUBContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitSUB(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassExpr01Context ------------------------------------------------------------------

ChipsParser::Expr01Context* ChipsParser::PassExpr01Context::expr01() {
  return getRuleContext<ChipsParser::Expr01Context>(0);
}

ChipsParser::PassExpr01Context::PassExpr01Context(Expr0Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::PassExpr01Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitPassExpr01(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PLUSContext ------------------------------------------------------------------

ChipsParser::Expr01Context* ChipsParser::PLUSContext::expr01() {
  return getRuleContext<ChipsParser::Expr01Context>(0);
}

tree::TerminalNode* ChipsParser::PLUSContext::PLUS() {
  return getToken(ChipsParser::PLUS, 0);
}

ChipsParser::Expr0Context* ChipsParser::PLUSContext::expr0() {
  return getRuleContext<ChipsParser::Expr0Context>(0);
}

ChipsParser::PLUSContext::PLUSContext(Expr0Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::PLUSContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitPLUS(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::Expr0Context* ChipsParser::expr0() {
  Expr0Context *_localctx = _tracker.createInstance<Expr0Context>(_ctx, getState());
  enterRule(_localctx, 36, ChipsParser::RuleExpr0);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(378);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::PLUSContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(369);
      expr01();
      setState(370);
      match(ChipsParser::PLUS);
      setState(371);
      expr0();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::SUBContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(373);
      expr01();
      setState(374);
      match(ChipsParser::MINUS);
      setState(375);
      expr0();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::PassExpr01Context>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(377);
      expr01();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Expr01Context ------------------------------------------------------------------

ChipsParser::Expr01Context::Expr01Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::Expr01Context::getRuleIndex() const {
  return ChipsParser::RuleExpr01;
}

void ChipsParser::Expr01Context::copyFrom(Expr01Context *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- PassExpr1Context ------------------------------------------------------------------

ChipsParser::Expr1Context* ChipsParser::PassExpr1Context::expr1() {
  return getRuleContext<ChipsParser::Expr1Context>(0);
}

ChipsParser::PassExpr1Context::PassExpr1Context(Expr01Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::PassExpr1Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitPassExpr1(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NegateContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::NegateContext::MINUS() {
  return getToken(ChipsParser::MINUS, 0);
}

ChipsParser::Expr1Context* ChipsParser::NegateContext::expr1() {
  return getRuleContext<ChipsParser::Expr1Context>(0);
}

ChipsParser::NegateContext::NegateContext(Expr01Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::NegateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitNegate(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::Expr01Context* ChipsParser::expr01() {
  Expr01Context *_localctx = _tracker.createInstance<Expr01Context>(_ctx, getState());
  enterRule(_localctx, 38, ChipsParser::RuleExpr01);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(383);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ChipsParser::MINUS: {
        _localctx = _tracker.createInstance<ChipsParser::NegateContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(380);
        match(ChipsParser::MINUS);
        setState(381);
        expr1();
        break;
      }

      case ChipsParser::CTX_KW:
      case ChipsParser::NOT:
      case ChipsParser::L_PARENTH:
      case ChipsParser::BOOL:
      case ChipsParser::FLOAT:
      case ChipsParser::INT:
      case ChipsParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<ChipsParser::PassExpr1Context>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(382);
        expr1();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Expr1Context ------------------------------------------------------------------

ChipsParser::Expr1Context::Expr1Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::Expr1Context::getRuleIndex() const {
  return ChipsParser::RuleExpr1;
}

void ChipsParser::Expr1Context::copyFrom(Expr1Context *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DIVContext ------------------------------------------------------------------

ChipsParser::Expr2Context* ChipsParser::DIVContext::expr2() {
  return getRuleContext<ChipsParser::Expr2Context>(0);
}

tree::TerminalNode* ChipsParser::DIVContext::DIV() {
  return getToken(ChipsParser::DIV, 0);
}

ChipsParser::Expr1Context* ChipsParser::DIVContext::expr1() {
  return getRuleContext<ChipsParser::Expr1Context>(0);
}

ChipsParser::DIVContext::DIVContext(Expr1Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::DIVContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitDIV(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NOTContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::NOTContext::NOT() {
  return getToken(ChipsParser::NOT, 0);
}

ChipsParser::Expr2Context* ChipsParser::NOTContext::expr2() {
  return getRuleContext<ChipsParser::Expr2Context>(0);
}

ChipsParser::NOTContext::NOTContext(Expr1Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::NOTContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitNOT(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MODContext ------------------------------------------------------------------

ChipsParser::Expr2Context* ChipsParser::MODContext::expr2() {
  return getRuleContext<ChipsParser::Expr2Context>(0);
}

tree::TerminalNode* ChipsParser::MODContext::MOD() {
  return getToken(ChipsParser::MOD, 0);
}

ChipsParser::Expr1Context* ChipsParser::MODContext::expr1() {
  return getRuleContext<ChipsParser::Expr1Context>(0);
}

ChipsParser::MODContext::MODContext(Expr1Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::MODContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitMOD(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MULTContext ------------------------------------------------------------------

ChipsParser::Expr2Context* ChipsParser::MULTContext::expr2() {
  return getRuleContext<ChipsParser::Expr2Context>(0);
}

tree::TerminalNode* ChipsParser::MULTContext::TIMES() {
  return getToken(ChipsParser::TIMES, 0);
}

ChipsParser::Expr1Context* ChipsParser::MULTContext::expr1() {
  return getRuleContext<ChipsParser::Expr1Context>(0);
}

ChipsParser::MULTContext::MULTContext(Expr1Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::MULTContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitMULT(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassExpr2Context ------------------------------------------------------------------

ChipsParser::Expr2Context* ChipsParser::PassExpr2Context::expr2() {
  return getRuleContext<ChipsParser::Expr2Context>(0);
}

ChipsParser::PassExpr2Context::PassExpr2Context(Expr1Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::PassExpr2Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitPassExpr2(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::Expr1Context* ChipsParser::expr1() {
  Expr1Context *_localctx = _tracker.createInstance<Expr1Context>(_ctx, getState());
  enterRule(_localctx, 40, ChipsParser::RuleExpr1);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(400);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::MULTContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(385);
      expr2();
      setState(386);
      match(ChipsParser::TIMES);
      setState(387);
      expr1();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::DIVContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(389);
      expr2();
      setState(390);
      match(ChipsParser::DIV);
      setState(391);
      expr1();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::MODContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(393);
      expr2();
      setState(394);
      match(ChipsParser::MOD);
      setState(395);
      expr1();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::NOTContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(397);
      match(ChipsParser::NOT);
      setState(398);
      expr2();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::PassExpr2Context>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(399);
      expr2();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Expr2Context ------------------------------------------------------------------

ChipsParser::Expr2Context::Expr2Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::Expr2Context::getRuleIndex() const {
  return ChipsParser::RuleExpr2;
}

void ChipsParser::Expr2Context::copyFrom(Expr2Context *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CastAsContext ------------------------------------------------------------------

ChipsParser::CastContext* ChipsParser::CastAsContext::cast() {
  return getRuleContext<ChipsParser::CastContext>(0);
}

ChipsParser::CastAsContext::CastAsContext(Expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::CastAsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCastAs(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::FunctionContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::FunctionContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

tree::TerminalNode* ChipsParser::FunctionContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

std::vector<ChipsParser::ExprContext *> ChipsParser::FunctionContext::expr() {
  return getRuleContexts<ChipsParser::ExprContext>();
}

ChipsParser::ExprContext* ChipsParser::FunctionContext::expr(size_t i) {
  return getRuleContext<ChipsParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> ChipsParser::FunctionContext::COMMA() {
  return getTokens(ChipsParser::COMMA);
}

tree::TerminalNode* ChipsParser::FunctionContext::COMMA(size_t i) {
  return getToken(ChipsParser::COMMA, i);
}

ChipsParser::FunctionContext::FunctionContext(Expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::FunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitFunction(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BoolLiteralContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::BoolLiteralContext::BOOL() {
  return getToken(ChipsParser::BOOL, 0);
}

ChipsParser::BoolLiteralContext::BoolLiteralContext(Expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::BoolLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitBoolLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FloatLiteralContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::FloatLiteralContext::FLOAT() {
  return getToken(ChipsParser::FLOAT, 0);
}

ChipsParser::FloatLiteralContext::FloatLiteralContext(Expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::FloatLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitFloatLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::VarContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

ChipsParser::SuffixesContext* ChipsParser::VarContext::suffixes() {
  return getRuleContext<ChipsParser::SuffixesContext>(0);
}

ChipsParser::VarContext::VarContext(Expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::VarContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitVar(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParensContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::ParensContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

ChipsParser::ExprContext* ChipsParser::ParensContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}

tree::TerminalNode* ChipsParser::ParensContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

ChipsParser::ParensContext::ParensContext(Expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::ParensContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitParens(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarContextContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::VarContextContext::CTX_KW() {
  return getToken(ChipsParser::CTX_KW, 0);
}

tree::TerminalNode* ChipsParser::VarContextContext::PERIOD() {
  return getToken(ChipsParser::PERIOD, 0);
}

tree::TerminalNode* ChipsParser::VarContextContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

ChipsParser::SuffixesContext* ChipsParser::VarContextContext::suffixes() {
  return getRuleContext<ChipsParser::SuffixesContext>(0);
}

ChipsParser::VarContextContext::VarContextContext(Expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::VarContextContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitVarContext(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntLiteralContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::IntLiteralContext::INT() {
  return getToken(ChipsParser::INT, 0);
}

ChipsParser::IntLiteralContext::IntLiteralContext(Expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::IntLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitIntLiteral(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::Expr2Context* ChipsParser::expr2() {
  Expr2Context *_localctx = _tracker.createInstance<Expr2Context>(_ctx, getState());
  enterRule(_localctx, 42, ChipsParser::RuleExpr2);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(429);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::IntLiteralContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(402);
      match(ChipsParser::INT);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::FloatLiteralContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(403);
      match(ChipsParser::FLOAT);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::BoolLiteralContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(404);
      match(ChipsParser::BOOL);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::VarContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(405);
      match(ChipsParser::IDENTIFIER);
      setState(406);
      suffixes();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::ParensContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(407);
      match(ChipsParser::L_PARENTH);
      setState(408);
      expr();
      setState(409);
      match(ChipsParser::R_PARENTH);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ChipsParser::VarContextContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(411);
      match(ChipsParser::CTX_KW);
      setState(412);
      match(ChipsParser::PERIOD);
      setState(413);
      match(ChipsParser::IDENTIFIER);
      setState(414);
      suffixes();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ChipsParser::FunctionContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(415);
      match(ChipsParser::IDENTIFIER);
      setState(416);
      match(ChipsParser::L_PARENTH);
      setState(425);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 8649303856221519872) != 0)) {
        setState(417);
        expr();
        setState(422);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ChipsParser::COMMA) {
          setState(418);
          match(ChipsParser::COMMA);
          setState(419);
          expr();
          setState(424);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(427);
      match(ChipsParser::R_PARENTH);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<ChipsParser::CastAsContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(428);
      cast();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CastContext ------------------------------------------------------------------

ChipsParser::CastContext::CastContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::CastContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

ChipsParser::Df_typeContext* ChipsParser::CastContext::df_type() {
  return getRuleContext<ChipsParser::Df_typeContext>(0);
}

tree::TerminalNode* ChipsParser::CastContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

ChipsParser::ExprContext* ChipsParser::CastContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}


size_t ChipsParser::CastContext::getRuleIndex() const {
  return ChipsParser::RuleCast;
}


std::any ChipsParser::CastContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCast(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::CastContext* ChipsParser::cast() {
  CastContext *_localctx = _tracker.createInstance<CastContext>(_ctx, getState());
  enterRule(_localctx, 44, ChipsParser::RuleCast);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(431);
    match(ChipsParser::L_PARENTH);
    setState(432);
    df_type();
    setState(433);
    match(ChipsParser::R_PARENTH);
    setState(434);
    expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- C_exprContext ------------------------------------------------------------------

ChipsParser::C_exprContext::C_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::C_exprContext::getRuleIndex() const {
  return ChipsParser::RuleC_expr;
}

void ChipsParser::C_exprContext::copyFrom(C_exprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CStoplessExpressionContext ------------------------------------------------------------------

ChipsParser::C_stopless_exprContext* ChipsParser::CStoplessExpressionContext::c_stopless_expr() {
  return getRuleContext<ChipsParser::C_stopless_exprContext>(0);
}

ChipsParser::CStoplessExpressionContext::CStoplessExpressionContext(C_exprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::CStoplessExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCStoplessExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StopContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::StopContext::STOP_KW() {
  return getToken(ChipsParser::STOP_KW, 0);
}

ChipsParser::StopContext::StopContext(C_exprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::StopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitStop(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::C_exprContext* ChipsParser::c_expr() {
  C_exprContext *_localctx = _tracker.createInstance<C_exprContext>(_ctx, getState());
  enterRule(_localctx, 46, ChipsParser::RuleC_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(438);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ChipsParser::INPUT_KW:
      case ChipsParser::CTX_KW:
      case ChipsParser::MINUS:
      case ChipsParser::NOT:
      case ChipsParser::L_PARENTH:
      case ChipsParser::BOOL:
      case ChipsParser::FLOAT:
      case ChipsParser::INT:
      case ChipsParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<ChipsParser::CStoplessExpressionContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(436);
        c_stopless_expr();
        break;
      }

      case ChipsParser::STOP_KW: {
        _localctx = _tracker.createInstance<ChipsParser::StopContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(437);
        match(ChipsParser::STOP_KW);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- C_stopless_exprContext ------------------------------------------------------------------

ChipsParser::C_stopless_exprContext::C_stopless_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::C_stopless_exprContext::getRuleIndex() const {
  return ChipsParser::RuleC_stopless_expr;
}

void ChipsParser::C_stopless_exprContext::copyFrom(C_stopless_exprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CGTContext ------------------------------------------------------------------

ChipsParser::C_stopless_expr0Context* ChipsParser::CGTContext::c_stopless_expr0() {
  return getRuleContext<ChipsParser::C_stopless_expr0Context>(0);
}

tree::TerminalNode* ChipsParser::CGTContext::GT() {
  return getToken(ChipsParser::GT, 0);
}

ChipsParser::C_stopless_exprContext* ChipsParser::CGTContext::c_stopless_expr() {
  return getRuleContext<ChipsParser::C_stopless_exprContext>(0);
}

ChipsParser::CGTContext::CGTContext(C_stopless_exprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::CGTContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCGT(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CORContext ------------------------------------------------------------------

ChipsParser::C_stopless_expr0Context* ChipsParser::CORContext::c_stopless_expr0() {
  return getRuleContext<ChipsParser::C_stopless_expr0Context>(0);
}

tree::TerminalNode* ChipsParser::CORContext::OR() {
  return getToken(ChipsParser::OR, 0);
}

ChipsParser::C_stopless_exprContext* ChipsParser::CORContext::c_stopless_expr() {
  return getRuleContext<ChipsParser::C_stopless_exprContext>(0);
}

ChipsParser::CORContext::CORContext(C_stopless_exprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::CORContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCOR(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassCExpr0Context ------------------------------------------------------------------

ChipsParser::C_stopless_expr0Context* ChipsParser::PassCExpr0Context::c_stopless_expr0() {
  return getRuleContext<ChipsParser::C_stopless_expr0Context>(0);
}

ChipsParser::PassCExpr0Context::PassCExpr0Context(C_stopless_exprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::PassCExpr0Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitPassCExpr0(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CNEQContext ------------------------------------------------------------------

ChipsParser::C_stopless_expr0Context* ChipsParser::CNEQContext::c_stopless_expr0() {
  return getRuleContext<ChipsParser::C_stopless_expr0Context>(0);
}

tree::TerminalNode* ChipsParser::CNEQContext::NEQ() {
  return getToken(ChipsParser::NEQ, 0);
}

ChipsParser::C_stopless_exprContext* ChipsParser::CNEQContext::c_stopless_expr() {
  return getRuleContext<ChipsParser::C_stopless_exprContext>(0);
}

ChipsParser::CNEQContext::CNEQContext(C_stopless_exprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::CNEQContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCNEQ(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CLTContext ------------------------------------------------------------------

ChipsParser::C_stopless_expr0Context* ChipsParser::CLTContext::c_stopless_expr0() {
  return getRuleContext<ChipsParser::C_stopless_expr0Context>(0);
}

tree::TerminalNode* ChipsParser::CLTContext::LT() {
  return getToken(ChipsParser::LT, 0);
}

ChipsParser::C_stopless_exprContext* ChipsParser::CLTContext::c_stopless_expr() {
  return getRuleContext<ChipsParser::C_stopless_exprContext>(0);
}

ChipsParser::CLTContext::CLTContext(C_stopless_exprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::CLTContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCLT(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CLEQContext ------------------------------------------------------------------

ChipsParser::C_stopless_expr0Context* ChipsParser::CLEQContext::c_stopless_expr0() {
  return getRuleContext<ChipsParser::C_stopless_expr0Context>(0);
}

tree::TerminalNode* ChipsParser::CLEQContext::LEQ() {
  return getToken(ChipsParser::LEQ, 0);
}

ChipsParser::C_stopless_exprContext* ChipsParser::CLEQContext::c_stopless_expr() {
  return getRuleContext<ChipsParser::C_stopless_exprContext>(0);
}

ChipsParser::CLEQContext::CLEQContext(C_stopless_exprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::CLEQContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCLEQ(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CANDContext ------------------------------------------------------------------

ChipsParser::C_stopless_expr0Context* ChipsParser::CANDContext::c_stopless_expr0() {
  return getRuleContext<ChipsParser::C_stopless_expr0Context>(0);
}

tree::TerminalNode* ChipsParser::CANDContext::AND() {
  return getToken(ChipsParser::AND, 0);
}

ChipsParser::C_stopless_exprContext* ChipsParser::CANDContext::c_stopless_expr() {
  return getRuleContext<ChipsParser::C_stopless_exprContext>(0);
}

ChipsParser::CANDContext::CANDContext(C_stopless_exprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::CANDContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCAND(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CEQContext ------------------------------------------------------------------

ChipsParser::C_stopless_expr0Context* ChipsParser::CEQContext::c_stopless_expr0() {
  return getRuleContext<ChipsParser::C_stopless_expr0Context>(0);
}

tree::TerminalNode* ChipsParser::CEQContext::EQ() {
  return getToken(ChipsParser::EQ, 0);
}

ChipsParser::C_stopless_exprContext* ChipsParser::CEQContext::c_stopless_expr() {
  return getRuleContext<ChipsParser::C_stopless_exprContext>(0);
}

ChipsParser::CEQContext::CEQContext(C_stopless_exprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::CEQContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCEQ(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CGEQContext ------------------------------------------------------------------

ChipsParser::C_stopless_expr0Context* ChipsParser::CGEQContext::c_stopless_expr0() {
  return getRuleContext<ChipsParser::C_stopless_expr0Context>(0);
}

tree::TerminalNode* ChipsParser::CGEQContext::GEQ() {
  return getToken(ChipsParser::GEQ, 0);
}

ChipsParser::C_stopless_exprContext* ChipsParser::CGEQContext::c_stopless_expr() {
  return getRuleContext<ChipsParser::C_stopless_exprContext>(0);
}

ChipsParser::CGEQContext::CGEQContext(C_stopless_exprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::CGEQContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCGEQ(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::C_stopless_exprContext* ChipsParser::c_stopless_expr() {
  C_stopless_exprContext *_localctx = _tracker.createInstance<C_stopless_exprContext>(_ctx, getState());
  enterRule(_localctx, 48, ChipsParser::RuleC_stopless_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(473);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::CLTContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(440);
      c_stopless_expr0();
      setState(441);
      match(ChipsParser::LT);
      setState(442);
      c_stopless_expr();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::CGTContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(444);
      c_stopless_expr0();
      setState(445);
      match(ChipsParser::GT);
      setState(446);
      c_stopless_expr();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::CLEQContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(448);
      c_stopless_expr0();
      setState(449);
      match(ChipsParser::LEQ);
      setState(450);
      c_stopless_expr();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::CGEQContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(452);
      c_stopless_expr0();
      setState(453);
      match(ChipsParser::GEQ);
      setState(454);
      c_stopless_expr();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::CNEQContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(456);
      c_stopless_expr0();
      setState(457);
      match(ChipsParser::NEQ);
      setState(458);
      c_stopless_expr();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ChipsParser::CEQContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(460);
      c_stopless_expr0();
      setState(461);
      match(ChipsParser::EQ);
      setState(462);
      c_stopless_expr();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ChipsParser::CANDContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(464);
      c_stopless_expr0();
      setState(465);
      match(ChipsParser::AND);
      setState(466);
      c_stopless_expr();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<ChipsParser::CORContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(468);
      c_stopless_expr0();
      setState(469);
      match(ChipsParser::OR);
      setState(470);
      c_stopless_expr();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<ChipsParser::PassCExpr0Context>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(472);
      c_stopless_expr0();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- C_stopless_expr0Context ------------------------------------------------------------------

ChipsParser::C_stopless_expr0Context::C_stopless_expr0Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::C_stopless_expr0Context::getRuleIndex() const {
  return ChipsParser::RuleC_stopless_expr0;
}

void ChipsParser::C_stopless_expr0Context::copyFrom(C_stopless_expr0Context *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CSUBContext ------------------------------------------------------------------

ChipsParser::C_stopless_expr01Context* ChipsParser::CSUBContext::c_stopless_expr01() {
  return getRuleContext<ChipsParser::C_stopless_expr01Context>(0);
}

tree::TerminalNode* ChipsParser::CSUBContext::MINUS() {
  return getToken(ChipsParser::MINUS, 0);
}

ChipsParser::C_stopless_expr0Context* ChipsParser::CSUBContext::c_stopless_expr0() {
  return getRuleContext<ChipsParser::C_stopless_expr0Context>(0);
}

ChipsParser::CSUBContext::CSUBContext(C_stopless_expr0Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::CSUBContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCSUB(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CPLUSContext ------------------------------------------------------------------

ChipsParser::C_stopless_expr01Context* ChipsParser::CPLUSContext::c_stopless_expr01() {
  return getRuleContext<ChipsParser::C_stopless_expr01Context>(0);
}

tree::TerminalNode* ChipsParser::CPLUSContext::PLUS() {
  return getToken(ChipsParser::PLUS, 0);
}

ChipsParser::C_stopless_expr0Context* ChipsParser::CPLUSContext::c_stopless_expr0() {
  return getRuleContext<ChipsParser::C_stopless_expr0Context>(0);
}

ChipsParser::CPLUSContext::CPLUSContext(C_stopless_expr0Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::CPLUSContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCPLUS(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassCExpr01Context ------------------------------------------------------------------

ChipsParser::C_stopless_expr01Context* ChipsParser::PassCExpr01Context::c_stopless_expr01() {
  return getRuleContext<ChipsParser::C_stopless_expr01Context>(0);
}

ChipsParser::PassCExpr01Context::PassCExpr01Context(C_stopless_expr0Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::PassCExpr01Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitPassCExpr01(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::C_stopless_expr0Context* ChipsParser::c_stopless_expr0() {
  C_stopless_expr0Context *_localctx = _tracker.createInstance<C_stopless_expr0Context>(_ctx, getState());
  enterRule(_localctx, 50, ChipsParser::RuleC_stopless_expr0);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(484);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::CPLUSContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(475);
      c_stopless_expr01();
      setState(476);
      match(ChipsParser::PLUS);
      setState(477);
      c_stopless_expr0();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::CSUBContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(479);
      c_stopless_expr01();
      setState(480);
      match(ChipsParser::MINUS);
      setState(481);
      c_stopless_expr0();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::PassCExpr01Context>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(483);
      c_stopless_expr01();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- C_stopless_expr01Context ------------------------------------------------------------------

ChipsParser::C_stopless_expr01Context::C_stopless_expr01Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::C_stopless_expr01Context::getRuleIndex() const {
  return ChipsParser::RuleC_stopless_expr01;
}

void ChipsParser::C_stopless_expr01Context::copyFrom(C_stopless_expr01Context *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- PassCExpr1Context ------------------------------------------------------------------

ChipsParser::C_stopless_expr1Context* ChipsParser::PassCExpr1Context::c_stopless_expr1() {
  return getRuleContext<ChipsParser::C_stopless_expr1Context>(0);
}

ChipsParser::PassCExpr1Context::PassCExpr1Context(C_stopless_expr01Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::PassCExpr1Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitPassCExpr1(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CNegateContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::CNegateContext::MINUS() {
  return getToken(ChipsParser::MINUS, 0);
}

ChipsParser::C_stopless_expr1Context* ChipsParser::CNegateContext::c_stopless_expr1() {
  return getRuleContext<ChipsParser::C_stopless_expr1Context>(0);
}

ChipsParser::CNegateContext::CNegateContext(C_stopless_expr01Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::CNegateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCNegate(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::C_stopless_expr01Context* ChipsParser::c_stopless_expr01() {
  C_stopless_expr01Context *_localctx = _tracker.createInstance<C_stopless_expr01Context>(_ctx, getState());
  enterRule(_localctx, 52, ChipsParser::RuleC_stopless_expr01);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(489);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ChipsParser::MINUS: {
        _localctx = _tracker.createInstance<ChipsParser::CNegateContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(486);
        match(ChipsParser::MINUS);
        setState(487);
        c_stopless_expr1();
        break;
      }

      case ChipsParser::INPUT_KW:
      case ChipsParser::CTX_KW:
      case ChipsParser::NOT:
      case ChipsParser::L_PARENTH:
      case ChipsParser::BOOL:
      case ChipsParser::FLOAT:
      case ChipsParser::INT:
      case ChipsParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<ChipsParser::PassCExpr1Context>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(488);
        c_stopless_expr1();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- C_stopless_expr1Context ------------------------------------------------------------------

ChipsParser::C_stopless_expr1Context::C_stopless_expr1Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::C_stopless_expr1Context::getRuleIndex() const {
  return ChipsParser::RuleC_stopless_expr1;
}

void ChipsParser::C_stopless_expr1Context::copyFrom(C_stopless_expr1Context *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CMODContext ------------------------------------------------------------------

ChipsParser::C_stopless_expr2Context* ChipsParser::CMODContext::c_stopless_expr2() {
  return getRuleContext<ChipsParser::C_stopless_expr2Context>(0);
}

tree::TerminalNode* ChipsParser::CMODContext::MOD() {
  return getToken(ChipsParser::MOD, 0);
}

ChipsParser::C_stopless_expr1Context* ChipsParser::CMODContext::c_stopless_expr1() {
  return getRuleContext<ChipsParser::C_stopless_expr1Context>(0);
}

ChipsParser::CMODContext::CMODContext(C_stopless_expr1Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::CMODContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCMOD(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CDIVContext ------------------------------------------------------------------

ChipsParser::C_stopless_expr2Context* ChipsParser::CDIVContext::c_stopless_expr2() {
  return getRuleContext<ChipsParser::C_stopless_expr2Context>(0);
}

tree::TerminalNode* ChipsParser::CDIVContext::DIV() {
  return getToken(ChipsParser::DIV, 0);
}

ChipsParser::C_stopless_expr1Context* ChipsParser::CDIVContext::c_stopless_expr1() {
  return getRuleContext<ChipsParser::C_stopless_expr1Context>(0);
}

ChipsParser::CDIVContext::CDIVContext(C_stopless_expr1Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::CDIVContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCDIV(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PassCExpr2Context ------------------------------------------------------------------

ChipsParser::C_stopless_expr2Context* ChipsParser::PassCExpr2Context::c_stopless_expr2() {
  return getRuleContext<ChipsParser::C_stopless_expr2Context>(0);
}

ChipsParser::PassCExpr2Context::PassCExpr2Context(C_stopless_expr1Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::PassCExpr2Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitPassCExpr2(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CMULTContext ------------------------------------------------------------------

ChipsParser::C_stopless_expr2Context* ChipsParser::CMULTContext::c_stopless_expr2() {
  return getRuleContext<ChipsParser::C_stopless_expr2Context>(0);
}

tree::TerminalNode* ChipsParser::CMULTContext::TIMES() {
  return getToken(ChipsParser::TIMES, 0);
}

ChipsParser::C_stopless_expr1Context* ChipsParser::CMULTContext::c_stopless_expr1() {
  return getRuleContext<ChipsParser::C_stopless_expr1Context>(0);
}

ChipsParser::CMULTContext::CMULTContext(C_stopless_expr1Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::CMULTContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCMULT(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CNOTContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::CNOTContext::NOT() {
  return getToken(ChipsParser::NOT, 0);
}

ChipsParser::C_stopless_expr2Context* ChipsParser::CNOTContext::c_stopless_expr2() {
  return getRuleContext<ChipsParser::C_stopless_expr2Context>(0);
}

ChipsParser::CNOTContext::CNOTContext(C_stopless_expr1Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::CNOTContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCNOT(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::C_stopless_expr1Context* ChipsParser::c_stopless_expr1() {
  C_stopless_expr1Context *_localctx = _tracker.createInstance<C_stopless_expr1Context>(_ctx, getState());
  enterRule(_localctx, 54, ChipsParser::RuleC_stopless_expr1);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(506);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::CMULTContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(491);
      c_stopless_expr2();
      setState(492);
      match(ChipsParser::TIMES);
      setState(493);
      c_stopless_expr1();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::CDIVContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(495);
      c_stopless_expr2();
      setState(496);
      match(ChipsParser::DIV);
      setState(497);
      c_stopless_expr1();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::CMODContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(499);
      c_stopless_expr2();
      setState(500);
      match(ChipsParser::MOD);
      setState(501);
      c_stopless_expr1();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::CNOTContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(503);
      match(ChipsParser::NOT);
      setState(504);
      c_stopless_expr2();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::PassCExpr2Context>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(505);
      c_stopless_expr2();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- C_stopless_expr2Context ------------------------------------------------------------------

ChipsParser::C_stopless_expr2Context::C_stopless_expr2Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::C_stopless_expr2Context::getRuleIndex() const {
  return ChipsParser::RuleC_stopless_expr2;
}

void ChipsParser::C_stopless_expr2Context::copyFrom(C_stopless_expr2Context *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ChanneledAccuExpressionContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> ChipsParser::ChanneledAccuExpressionContext::IDENTIFIER() {
  return getTokens(ChipsParser::IDENTIFIER);
}

tree::TerminalNode* ChipsParser::ChanneledAccuExpressionContext::IDENTIFIER(size_t i) {
  return getToken(ChipsParser::IDENTIFIER, i);
}

tree::TerminalNode* ChipsParser::ChanneledAccuExpressionContext::PERIOD() {
  return getToken(ChipsParser::PERIOD, 0);
}

ChipsParser::C_suffixesContext* ChipsParser::ChanneledAccuExpressionContext::c_suffixes() {
  return getRuleContext<ChipsParser::C_suffixesContext>(0);
}

ChipsParser::ChanneledAccuExpressionContext::ChanneledAccuExpressionContext(C_stopless_expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::ChanneledAccuExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitChanneledAccuExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CParenthesisContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::CParenthesisContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

ChipsParser::C_stopless_exprContext* ChipsParser::CParenthesisContext::c_stopless_expr() {
  return getRuleContext<ChipsParser::C_stopless_exprContext>(0);
}

tree::TerminalNode* ChipsParser::CParenthesisContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

ChipsParser::CParenthesisContext::CParenthesisContext(C_stopless_expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::CParenthesisContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCParenthesis(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CVariableExpressionContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::CVariableExpressionContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

ChipsParser::C_suffixesContext* ChipsParser::CVariableExpressionContext::c_suffixes() {
  return getRuleContext<ChipsParser::C_suffixesContext>(0);
}

ChipsParser::CVariableExpressionContext::CVariableExpressionContext(C_stopless_expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::CVariableExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCVariableExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CBOOLContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::CBOOLContext::BOOL() {
  return getToken(ChipsParser::BOOL, 0);
}

ChipsParser::CBOOLContext::CBOOLContext(C_stopless_expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::CBOOLContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCBOOL(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CtxVariableExpressionContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::CtxVariableExpressionContext::CTX_KW() {
  return getToken(ChipsParser::CTX_KW, 0);
}

tree::TerminalNode* ChipsParser::CtxVariableExpressionContext::PERIOD() {
  return getToken(ChipsParser::PERIOD, 0);
}

tree::TerminalNode* ChipsParser::CtxVariableExpressionContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

ChipsParser::C_suffixesContext* ChipsParser::CtxVariableExpressionContext::c_suffixes() {
  return getRuleContext<ChipsParser::C_suffixesContext>(0);
}

ChipsParser::CtxVariableExpressionContext::CtxVariableExpressionContext(C_stopless_expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::CtxVariableExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCtxVariableExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CINTContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::CINTContext::INT() {
  return getToken(ChipsParser::INT, 0);
}

ChipsParser::CINTContext::CINTContext(C_stopless_expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::CINTContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCINT(this);
  else
    return visitor->visitChildren(this);
}
//----------------- INPUTContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::INPUTContext::INPUT_KW() {
  return getToken(ChipsParser::INPUT_KW, 0);
}

ChipsParser::INPUTContext::INPUTContext(C_stopless_expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::INPUTContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitINPUT(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CCastAsContext ------------------------------------------------------------------

ChipsParser::C_castContext* ChipsParser::CCastAsContext::c_cast() {
  return getRuleContext<ChipsParser::C_castContext>(0);
}

ChipsParser::CCastAsContext::CCastAsContext(C_stopless_expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::CCastAsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCCastAs(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CFLOATContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::CFLOATContext::FLOAT() {
  return getToken(ChipsParser::FLOAT, 0);
}

ChipsParser::CFLOATContext::CFLOATContext(C_stopless_expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::CFLOATContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCFLOAT(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionCallContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::FunctionCallContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::FunctionCallContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

tree::TerminalNode* ChipsParser::FunctionCallContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

std::vector<ChipsParser::C_exprContext *> ChipsParser::FunctionCallContext::c_expr() {
  return getRuleContexts<ChipsParser::C_exprContext>();
}

ChipsParser::C_exprContext* ChipsParser::FunctionCallContext::c_expr(size_t i) {
  return getRuleContext<ChipsParser::C_exprContext>(i);
}

std::vector<tree::TerminalNode *> ChipsParser::FunctionCallContext::COMMA() {
  return getTokens(ChipsParser::COMMA);
}

tree::TerminalNode* ChipsParser::FunctionCallContext::COMMA(size_t i) {
  return getToken(ChipsParser::COMMA, i);
}

ChipsParser::FunctionCallContext::FunctionCallContext(C_stopless_expr2Context *ctx) { copyFrom(ctx); }


std::any ChipsParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::C_stopless_expr2Context* ChipsParser::c_stopless_expr2() {
  C_stopless_expr2Context *_localctx = _tracker.createInstance<C_stopless_expr2Context>(_ctx, getState());
  enterRule(_localctx, 56, ChipsParser::RuleC_stopless_expr2);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(540);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::CVariableExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(508);
      match(ChipsParser::IDENTIFIER);
      setState(509);
      c_suffixes();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::CINTContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(510);
      match(ChipsParser::INT);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::CFLOATContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(511);
      match(ChipsParser::FLOAT);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::CBOOLContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(512);
      match(ChipsParser::BOOL);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::INPUTContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(513);
      match(ChipsParser::INPUT_KW);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ChipsParser::CtxVariableExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(514);
      match(ChipsParser::CTX_KW);
      setState(515);
      match(ChipsParser::PERIOD);
      setState(516);
      match(ChipsParser::IDENTIFIER);
      setState(517);
      c_suffixes();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ChipsParser::ChanneledAccuExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(518);
      match(ChipsParser::IDENTIFIER);
      setState(519);
      match(ChipsParser::PERIOD);
      setState(520);
      match(ChipsParser::IDENTIFIER);
      setState(521);
      c_suffixes();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<ChipsParser::FunctionCallContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(522);
      match(ChipsParser::IDENTIFIER);
      setState(523);
      match(ChipsParser::L_PARENTH);
      setState(532);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 8649303856222306304) != 0)) {
        setState(524);
        c_expr();
        setState(529);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ChipsParser::COMMA) {
          setState(525);
          match(ChipsParser::COMMA);
          setState(526);
          c_expr();
          setState(531);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(534);
      match(ChipsParser::R_PARENTH);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<ChipsParser::CParenthesisContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(535);
      match(ChipsParser::L_PARENTH);
      setState(536);
      c_stopless_expr();
      setState(537);
      match(ChipsParser::R_PARENTH);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<ChipsParser::CCastAsContext>(_localctx);
      enterOuterAlt(_localctx, 10);
      setState(539);
      c_cast();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- C_castContext ------------------------------------------------------------------

ChipsParser::C_castContext::C_castContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::C_castContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

ChipsParser::Df_typeContext* ChipsParser::C_castContext::df_type() {
  return getRuleContext<ChipsParser::Df_typeContext>(0);
}

tree::TerminalNode* ChipsParser::C_castContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

ChipsParser::C_stopless_exprContext* ChipsParser::C_castContext::c_stopless_expr() {
  return getRuleContext<ChipsParser::C_stopless_exprContext>(0);
}


size_t ChipsParser::C_castContext::getRuleIndex() const {
  return ChipsParser::RuleC_cast;
}


std::any ChipsParser::C_castContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitC_cast(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::C_castContext* ChipsParser::c_cast() {
  C_castContext *_localctx = _tracker.createInstance<C_castContext>(_ctx, getState());
  enterRule(_localctx, 58, ChipsParser::RuleC_cast);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(542);
    match(ChipsParser::L_PARENTH);
    setState(543);
    df_type();
    setState(544);
    match(ChipsParser::R_PARENTH);
    setState(545);
    c_stopless_expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SuffixesContext ------------------------------------------------------------------

ChipsParser::SuffixesContext::SuffixesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ChipsParser::SuffixesContext::L_SQUA() {
  return getTokens(ChipsParser::L_SQUA);
}

tree::TerminalNode* ChipsParser::SuffixesContext::L_SQUA(size_t i) {
  return getToken(ChipsParser::L_SQUA, i);
}

std::vector<ChipsParser::ExprContext *> ChipsParser::SuffixesContext::expr() {
  return getRuleContexts<ChipsParser::ExprContext>();
}

ChipsParser::ExprContext* ChipsParser::SuffixesContext::expr(size_t i) {
  return getRuleContext<ChipsParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> ChipsParser::SuffixesContext::R_SQUA() {
  return getTokens(ChipsParser::R_SQUA);
}

tree::TerminalNode* ChipsParser::SuffixesContext::R_SQUA(size_t i) {
  return getToken(ChipsParser::R_SQUA, i);
}


size_t ChipsParser::SuffixesContext::getRuleIndex() const {
  return ChipsParser::RuleSuffixes;
}


std::any ChipsParser::SuffixesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitSuffixes(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::SuffixesContext* ChipsParser::suffixes() {
  SuffixesContext *_localctx = _tracker.createInstance<SuffixesContext>(_ctx, getState());
  enterRule(_localctx, 60, ChipsParser::RuleSuffixes);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(553);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ChipsParser::L_SQUA) {
      setState(547);
      match(ChipsParser::L_SQUA);
      setState(548);
      expr();
      setState(549);
      match(ChipsParser::R_SQUA);
      setState(555);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- C_suffixesContext ------------------------------------------------------------------

ChipsParser::C_suffixesContext::C_suffixesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ChipsParser::C_suffixesContext::L_SQUA() {
  return getTokens(ChipsParser::L_SQUA);
}

tree::TerminalNode* ChipsParser::C_suffixesContext::L_SQUA(size_t i) {
  return getToken(ChipsParser::L_SQUA, i);
}

std::vector<ChipsParser::C_stopless_exprContext *> ChipsParser::C_suffixesContext::c_stopless_expr() {
  return getRuleContexts<ChipsParser::C_stopless_exprContext>();
}

ChipsParser::C_stopless_exprContext* ChipsParser::C_suffixesContext::c_stopless_expr(size_t i) {
  return getRuleContext<ChipsParser::C_stopless_exprContext>(i);
}

std::vector<tree::TerminalNode *> ChipsParser::C_suffixesContext::R_SQUA() {
  return getTokens(ChipsParser::R_SQUA);
}

tree::TerminalNode* ChipsParser::C_suffixesContext::R_SQUA(size_t i) {
  return getToken(ChipsParser::R_SQUA, i);
}


size_t ChipsParser::C_suffixesContext::getRuleIndex() const {
  return ChipsParser::RuleC_suffixes;
}


std::any ChipsParser::C_suffixesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitC_suffixes(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::C_suffixesContext* ChipsParser::c_suffixes() {
  C_suffixesContext *_localctx = _tracker.createInstance<C_suffixesContext>(_ctx, getState());
  enterRule(_localctx, 62, ChipsParser::RuleC_suffixes);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(562);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ChipsParser::L_SQUA) {
      setState(556);
      match(ChipsParser::L_SQUA);
      setState(557);
      c_stopless_expr();
      setState(558);
      match(ChipsParser::R_SQUA);
      setState(564);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- S_suffixable_exprContext ------------------------------------------------------------------

ChipsParser::S_suffixable_exprContext::S_suffixable_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::S_suffixable_exprContext::getRuleIndex() const {
  return ChipsParser::RuleS_suffixable_expr;
}

void ChipsParser::S_suffixable_exprContext::copyFrom(S_suffixable_exprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SSuffixableVariableExpressionContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::SSuffixableVariableExpressionContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

ChipsParser::SSuffixableVariableExpressionContext::SSuffixableVariableExpressionContext(S_suffixable_exprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::SSuffixableVariableExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitSSuffixableVariableExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SSuffixableFunctionCallExpressionContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::SSuffixableFunctionCallExpressionContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::SSuffixableFunctionCallExpressionContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

tree::TerminalNode* ChipsParser::SSuffixableFunctionCallExpressionContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

std::vector<ChipsParser::ExprContext *> ChipsParser::SSuffixableFunctionCallExpressionContext::expr() {
  return getRuleContexts<ChipsParser::ExprContext>();
}

ChipsParser::ExprContext* ChipsParser::SSuffixableFunctionCallExpressionContext::expr(size_t i) {
  return getRuleContext<ChipsParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> ChipsParser::SSuffixableFunctionCallExpressionContext::COMMA() {
  return getTokens(ChipsParser::COMMA);
}

tree::TerminalNode* ChipsParser::SSuffixableFunctionCallExpressionContext::COMMA(size_t i) {
  return getToken(ChipsParser::COMMA, i);
}

ChipsParser::SSuffixableFunctionCallExpressionContext::SSuffixableFunctionCallExpressionContext(S_suffixable_exprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::SSuffixableFunctionCallExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitSSuffixableFunctionCallExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SSuffixableBlockOutputExpressionContext ------------------------------------------------------------------

ChipsParser::BlockContext* ChipsParser::SSuffixableBlockOutputExpressionContext::block() {
  return getRuleContext<ChipsParser::BlockContext>(0);
}

tree::TerminalNode* ChipsParser::SSuffixableBlockOutputExpressionContext::PERIOD() {
  return getToken(ChipsParser::PERIOD, 0);
}

tree::TerminalNode* ChipsParser::SSuffixableBlockOutputExpressionContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

ChipsParser::SSuffixableBlockOutputExpressionContext::SSuffixableBlockOutputExpressionContext(S_suffixable_exprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::SSuffixableBlockOutputExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitSSuffixableBlockOutputExpression(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::S_suffixable_exprContext* ChipsParser::s_suffixable_expr() {
  S_suffixable_exprContext *_localctx = _tracker.createInstance<S_suffixable_exprContext>(_ctx, getState());
  enterRule(_localctx, 64, ChipsParser::RuleS_suffixable_expr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(585);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::SSuffixableVariableExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(565);
      match(ChipsParser::IDENTIFIER);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::SSuffixableFunctionCallExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(566);
      match(ChipsParser::IDENTIFIER);
      setState(579);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ChipsParser::L_PARENTH) {
        setState(567);
        match(ChipsParser::L_PARENTH);
        setState(576);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 8649303856221519872) != 0)) {
          setState(568);
          expr();
          setState(573);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == ChipsParser::COMMA) {
            setState(569);
            match(ChipsParser::COMMA);
            setState(570);
            expr();
            setState(575);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(578);
        match(ChipsParser::R_PARENTH);
      }
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::SSuffixableBlockOutputExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(581);
      block();
      setState(582);
      match(ChipsParser::PERIOD);
      setState(583);
      match(ChipsParser::IDENTIFIER);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

ChipsParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::BlockContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

ChipsParser::SuffixesContext* ChipsParser::BlockContext::suffixes() {
  return getRuleContext<ChipsParser::SuffixesContext>(0);
}


size_t ChipsParser::BlockContext::getRuleIndex() const {
  return ChipsParser::RuleBlock;
}


std::any ChipsParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::BlockContext* ChipsParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 66, ChipsParser::RuleBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(587);
    match(ChipsParser::IDENTIFIER);
    setState(588);
    suffixes();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Loop_inContext ------------------------------------------------------------------

ChipsParser::Loop_inContext::Loop_inContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::Loop_inContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

ChipsParser::SuffixesContext* ChipsParser::Loop_inContext::suffixes() {
  return getRuleContext<ChipsParser::SuffixesContext>(0);
}

tree::TerminalNode* ChipsParser::Loop_inContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

tree::TerminalNode* ChipsParser::Loop_inContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

std::vector<ChipsParser::ExprContext *> ChipsParser::Loop_inContext::expr() {
  return getRuleContexts<ChipsParser::ExprContext>();
}

ChipsParser::ExprContext* ChipsParser::Loop_inContext::expr(size_t i) {
  return getRuleContext<ChipsParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> ChipsParser::Loop_inContext::COMMA() {
  return getTokens(ChipsParser::COMMA);
}

tree::TerminalNode* ChipsParser::Loop_inContext::COMMA(size_t i) {
  return getToken(ChipsParser::COMMA, i);
}


size_t ChipsParser::Loop_inContext::getRuleIndex() const {
  return ChipsParser::RuleLoop_in;
}


std::any ChipsParser::Loop_inContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitLoop_in(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::Loop_inContext* ChipsParser::loop_in() {
  Loop_inContext *_localctx = _tracker.createInstance<Loop_inContext>(_ctx, getState());
  enterRule(_localctx, 68, ChipsParser::RuleLoop_in);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(590);
    match(ChipsParser::IDENTIFIER);
    setState(603);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ChipsParser::L_PARENTH) {
      setState(591);
      match(ChipsParser::L_PARENTH);
      setState(600);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 8649303856221519872) != 0)) {
        setState(592);
        expr();
        setState(597);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ChipsParser::COMMA) {
          setState(593);
          match(ChipsParser::COMMA);
          setState(594);
          expr();
          setState(599);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(602);
      match(ChipsParser::R_PARENTH);
    }
    setState(605);
    suffixes();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Loop_statementContext ------------------------------------------------------------------

ChipsParser::Loop_statementContext::Loop_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::Loop_statementContext::FOREACH_KW() {
  return getToken(ChipsParser::FOREACH_KW, 0);
}

tree::TerminalNode* ChipsParser::Loop_statementContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::Loop_statementContext::IN_KW() {
  return getToken(ChipsParser::IN_KW, 0);
}

ChipsParser::Loop_inContext* ChipsParser::Loop_statementContext::loop_in() {
  return getRuleContext<ChipsParser::Loop_inContext>(0);
}

tree::TerminalNode* ChipsParser::Loop_statementContext::L_CURL() {
  return getToken(ChipsParser::L_CURL, 0);
}

tree::TerminalNode* ChipsParser::Loop_statementContext::R_CURL() {
  return getToken(ChipsParser::R_CURL, 0);
}

std::vector<ChipsParser::StatementContext *> ChipsParser::Loop_statementContext::statement() {
  return getRuleContexts<ChipsParser::StatementContext>();
}

ChipsParser::StatementContext* ChipsParser::Loop_statementContext::statement(size_t i) {
  return getRuleContext<ChipsParser::StatementContext>(i);
}


size_t ChipsParser::Loop_statementContext::getRuleIndex() const {
  return ChipsParser::RuleLoop_statement;
}


std::any ChipsParser::Loop_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitLoop_statement(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::Loop_statementContext* ChipsParser::loop_statement() {
  Loop_statementContext *_localctx = _tracker.createInstance<Loop_statementContext>(_ctx, getState());
  enterRule(_localctx, 70, ChipsParser::RuleLoop_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(607);
    match(ChipsParser::FOREACH_KW);
    setState(608);
    match(ChipsParser::IDENTIFIER);
    setState(609);
    match(ChipsParser::IN_KW);
    setState(610);
    loop_in();
    setState(611);
    match(ChipsParser::L_CURL);
    setState(615);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(612);
      statement();
      setState(617);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(618);
    match(ChipsParser::R_CURL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- C_loop_statementContext ------------------------------------------------------------------

ChipsParser::C_loop_statementContext::C_loop_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::C_loop_statementContext::FOREACH_KW() {
  return getToken(ChipsParser::FOREACH_KW, 0);
}

tree::TerminalNode* ChipsParser::C_loop_statementContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::C_loop_statementContext::IN_KW() {
  return getToken(ChipsParser::IN_KW, 0);
}

ChipsParser::Loop_inContext* ChipsParser::C_loop_statementContext::loop_in() {
  return getRuleContext<ChipsParser::Loop_inContext>(0);
}

tree::TerminalNode* ChipsParser::C_loop_statementContext::L_CURL() {
  return getToken(ChipsParser::L_CURL, 0);
}

tree::TerminalNode* ChipsParser::C_loop_statementContext::R_CURL() {
  return getToken(ChipsParser::R_CURL, 0);
}

std::vector<ChipsParser::C_statementContext *> ChipsParser::C_loop_statementContext::c_statement() {
  return getRuleContexts<ChipsParser::C_statementContext>();
}

ChipsParser::C_statementContext* ChipsParser::C_loop_statementContext::c_statement(size_t i) {
  return getRuleContext<ChipsParser::C_statementContext>(i);
}


size_t ChipsParser::C_loop_statementContext::getRuleIndex() const {
  return ChipsParser::RuleC_loop_statement;
}


std::any ChipsParser::C_loop_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitC_loop_statement(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::C_loop_statementContext* ChipsParser::c_loop_statement() {
  C_loop_statementContext *_localctx = _tracker.createInstance<C_loop_statementContext>(_ctx, getState());
  enterRule(_localctx, 72, ChipsParser::RuleC_loop_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(620);
    match(ChipsParser::FOREACH_KW);
    setState(621);
    match(ChipsParser::IDENTIFIER);
    setState(622);
    match(ChipsParser::IN_KW);
    setState(623);
    loop_in();
    setState(624);
    match(ChipsParser::L_CURL);
    setState(628);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(625);
      c_statement();
      setState(630);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(631);
    match(ChipsParser::R_CURL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- S_loop_statementContext ------------------------------------------------------------------

ChipsParser::S_loop_statementContext::S_loop_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::S_loop_statementContext::FOREACH_KW() {
  return getToken(ChipsParser::FOREACH_KW, 0);
}

tree::TerminalNode* ChipsParser::S_loop_statementContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::S_loop_statementContext::IN_KW() {
  return getToken(ChipsParser::IN_KW, 0);
}

ChipsParser::S_suffixable_exprContext* ChipsParser::S_loop_statementContext::s_suffixable_expr() {
  return getRuleContext<ChipsParser::S_suffixable_exprContext>(0);
}

tree::TerminalNode* ChipsParser::S_loop_statementContext::L_CURL() {
  return getToken(ChipsParser::L_CURL, 0);
}

tree::TerminalNode* ChipsParser::S_loop_statementContext::R_CURL() {
  return getToken(ChipsParser::R_CURL, 0);
}

std::vector<ChipsParser::S_statementContext *> ChipsParser::S_loop_statementContext::s_statement() {
  return getRuleContexts<ChipsParser::S_statementContext>();
}

ChipsParser::S_statementContext* ChipsParser::S_loop_statementContext::s_statement(size_t i) {
  return getRuleContext<ChipsParser::S_statementContext>(i);
}


size_t ChipsParser::S_loop_statementContext::getRuleIndex() const {
  return ChipsParser::RuleS_loop_statement;
}


std::any ChipsParser::S_loop_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitS_loop_statement(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::S_loop_statementContext* ChipsParser::s_loop_statement() {
  S_loop_statementContext *_localctx = _tracker.createInstance<S_loop_statementContext>(_ctx, getState());
  enterRule(_localctx, 74, ChipsParser::RuleS_loop_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(633);
    match(ChipsParser::FOREACH_KW);
    setState(634);
    match(ChipsParser::IDENTIFIER);
    setState(635);
    match(ChipsParser::IN_KW);
    setState(636);
    s_suffixable_expr();
    setState(637);
    match(ChipsParser::L_CURL);
    setState(641);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435814428) != 0)) {
      setState(638);
      s_statement();
      setState(643);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(644);
    match(ChipsParser::R_CURL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- If_else_statementContext ------------------------------------------------------------------

ChipsParser::If_else_statementContext::If_else_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ChipsParser::If_statementContext* ChipsParser::If_else_statementContext::if_statement() {
  return getRuleContext<ChipsParser::If_statementContext>(0);
}

tree::TerminalNode* ChipsParser::If_else_statementContext::ELSE_KW() {
  return getToken(ChipsParser::ELSE_KW, 0);
}

tree::TerminalNode* ChipsParser::If_else_statementContext::L_CURL() {
  return getToken(ChipsParser::L_CURL, 0);
}

tree::TerminalNode* ChipsParser::If_else_statementContext::R_CURL() {
  return getToken(ChipsParser::R_CURL, 0);
}

std::vector<ChipsParser::StatementContext *> ChipsParser::If_else_statementContext::statement() {
  return getRuleContexts<ChipsParser::StatementContext>();
}

ChipsParser::StatementContext* ChipsParser::If_else_statementContext::statement(size_t i) {
  return getRuleContext<ChipsParser::StatementContext>(i);
}


size_t ChipsParser::If_else_statementContext::getRuleIndex() const {
  return ChipsParser::RuleIf_else_statement;
}


std::any ChipsParser::If_else_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitIf_else_statement(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::If_else_statementContext* ChipsParser::if_else_statement() {
  If_else_statementContext *_localctx = _tracker.createInstance<If_else_statementContext>(_ctx, getState());
  enterRule(_localctx, 76, ChipsParser::RuleIf_else_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(646);
    if_statement();
    setState(647);
    match(ChipsParser::ELSE_KW);
    setState(648);
    match(ChipsParser::L_CURL);
    setState(652);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(649);
      statement();
      setState(654);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(655);
    match(ChipsParser::R_CURL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- S_if_else_statementContext ------------------------------------------------------------------

ChipsParser::S_if_else_statementContext::S_if_else_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ChipsParser::S_if_statementContext* ChipsParser::S_if_else_statementContext::s_if_statement() {
  return getRuleContext<ChipsParser::S_if_statementContext>(0);
}

tree::TerminalNode* ChipsParser::S_if_else_statementContext::ELSE_KW() {
  return getToken(ChipsParser::ELSE_KW, 0);
}

tree::TerminalNode* ChipsParser::S_if_else_statementContext::L_CURL() {
  return getToken(ChipsParser::L_CURL, 0);
}

tree::TerminalNode* ChipsParser::S_if_else_statementContext::R_CURL() {
  return getToken(ChipsParser::R_CURL, 0);
}

std::vector<ChipsParser::S_statementContext *> ChipsParser::S_if_else_statementContext::s_statement() {
  return getRuleContexts<ChipsParser::S_statementContext>();
}

ChipsParser::S_statementContext* ChipsParser::S_if_else_statementContext::s_statement(size_t i) {
  return getRuleContext<ChipsParser::S_statementContext>(i);
}


size_t ChipsParser::S_if_else_statementContext::getRuleIndex() const {
  return ChipsParser::RuleS_if_else_statement;
}


std::any ChipsParser::S_if_else_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitS_if_else_statement(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::S_if_else_statementContext* ChipsParser::s_if_else_statement() {
  S_if_else_statementContext *_localctx = _tracker.createInstance<S_if_else_statementContext>(_ctx, getState());
  enterRule(_localctx, 78, ChipsParser::RuleS_if_else_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(657);
    s_if_statement();
    setState(658);
    match(ChipsParser::ELSE_KW);
    setState(659);
    match(ChipsParser::L_CURL);
    setState(663);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435814428) != 0)) {
      setState(660);
      s_statement();
      setState(665);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(666);
    match(ChipsParser::R_CURL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- C_if_else_statementContext ------------------------------------------------------------------

ChipsParser::C_if_else_statementContext::C_if_else_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ChipsParser::C_if_statementContext* ChipsParser::C_if_else_statementContext::c_if_statement() {
  return getRuleContext<ChipsParser::C_if_statementContext>(0);
}

tree::TerminalNode* ChipsParser::C_if_else_statementContext::ELSE_KW() {
  return getToken(ChipsParser::ELSE_KW, 0);
}

tree::TerminalNode* ChipsParser::C_if_else_statementContext::L_CURL() {
  return getToken(ChipsParser::L_CURL, 0);
}

tree::TerminalNode* ChipsParser::C_if_else_statementContext::R_CURL() {
  return getToken(ChipsParser::R_CURL, 0);
}

std::vector<ChipsParser::C_statementContext *> ChipsParser::C_if_else_statementContext::c_statement() {
  return getRuleContexts<ChipsParser::C_statementContext>();
}

ChipsParser::C_statementContext* ChipsParser::C_if_else_statementContext::c_statement(size_t i) {
  return getRuleContext<ChipsParser::C_statementContext>(i);
}


size_t ChipsParser::C_if_else_statementContext::getRuleIndex() const {
  return ChipsParser::RuleC_if_else_statement;
}


std::any ChipsParser::C_if_else_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitC_if_else_statement(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::C_if_else_statementContext* ChipsParser::c_if_else_statement() {
  C_if_else_statementContext *_localctx = _tracker.createInstance<C_if_else_statementContext>(_ctx, getState());
  enterRule(_localctx, 80, ChipsParser::RuleC_if_else_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(668);
    c_if_statement();
    setState(669);
    match(ChipsParser::ELSE_KW);
    setState(670);
    match(ChipsParser::L_CURL);
    setState(674);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(671);
      c_statement();
      setState(676);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(677);
    match(ChipsParser::R_CURL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- If_statementContext ------------------------------------------------------------------

ChipsParser::If_statementContext::If_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::If_statementContext::IF_KW() {
  return getToken(ChipsParser::IF_KW, 0);
}

tree::TerminalNode* ChipsParser::If_statementContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

ChipsParser::ExprContext* ChipsParser::If_statementContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}

tree::TerminalNode* ChipsParser::If_statementContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

tree::TerminalNode* ChipsParser::If_statementContext::L_CURL() {
  return getToken(ChipsParser::L_CURL, 0);
}

tree::TerminalNode* ChipsParser::If_statementContext::R_CURL() {
  return getToken(ChipsParser::R_CURL, 0);
}

std::vector<ChipsParser::StatementContext *> ChipsParser::If_statementContext::statement() {
  return getRuleContexts<ChipsParser::StatementContext>();
}

ChipsParser::StatementContext* ChipsParser::If_statementContext::statement(size_t i) {
  return getRuleContext<ChipsParser::StatementContext>(i);
}


size_t ChipsParser::If_statementContext::getRuleIndex() const {
  return ChipsParser::RuleIf_statement;
}


std::any ChipsParser::If_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitIf_statement(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::If_statementContext* ChipsParser::if_statement() {
  If_statementContext *_localctx = _tracker.createInstance<If_statementContext>(_ctx, getState());
  enterRule(_localctx, 82, ChipsParser::RuleIf_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(679);
    match(ChipsParser::IF_KW);
    setState(680);
    match(ChipsParser::L_PARENTH);
    setState(681);
    expr();
    setState(682);
    match(ChipsParser::R_PARENTH);
    setState(683);
    match(ChipsParser::L_CURL);
    setState(687);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(684);
      statement();
      setState(689);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(690);
    match(ChipsParser::R_CURL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- S_if_statementContext ------------------------------------------------------------------

ChipsParser::S_if_statementContext::S_if_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::S_if_statementContext::IF_KW() {
  return getToken(ChipsParser::IF_KW, 0);
}

tree::TerminalNode* ChipsParser::S_if_statementContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

ChipsParser::ExprContext* ChipsParser::S_if_statementContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}

tree::TerminalNode* ChipsParser::S_if_statementContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

tree::TerminalNode* ChipsParser::S_if_statementContext::L_CURL() {
  return getToken(ChipsParser::L_CURL, 0);
}

tree::TerminalNode* ChipsParser::S_if_statementContext::R_CURL() {
  return getToken(ChipsParser::R_CURL, 0);
}

std::vector<ChipsParser::S_statementContext *> ChipsParser::S_if_statementContext::s_statement() {
  return getRuleContexts<ChipsParser::S_statementContext>();
}

ChipsParser::S_statementContext* ChipsParser::S_if_statementContext::s_statement(size_t i) {
  return getRuleContext<ChipsParser::S_statementContext>(i);
}


size_t ChipsParser::S_if_statementContext::getRuleIndex() const {
  return ChipsParser::RuleS_if_statement;
}


std::any ChipsParser::S_if_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitS_if_statement(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::S_if_statementContext* ChipsParser::s_if_statement() {
  S_if_statementContext *_localctx = _tracker.createInstance<S_if_statementContext>(_ctx, getState());
  enterRule(_localctx, 84, ChipsParser::RuleS_if_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(692);
    match(ChipsParser::IF_KW);
    setState(693);
    match(ChipsParser::L_PARENTH);
    setState(694);
    expr();
    setState(695);
    match(ChipsParser::R_PARENTH);
    setState(696);
    match(ChipsParser::L_CURL);
    setState(700);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435814428) != 0)) {
      setState(697);
      s_statement();
      setState(702);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(703);
    match(ChipsParser::R_CURL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- C_if_statementContext ------------------------------------------------------------------

ChipsParser::C_if_statementContext::C_if_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::C_if_statementContext::IF_KW() {
  return getToken(ChipsParser::IF_KW, 0);
}

tree::TerminalNode* ChipsParser::C_if_statementContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

ChipsParser::C_exprContext* ChipsParser::C_if_statementContext::c_expr() {
  return getRuleContext<ChipsParser::C_exprContext>(0);
}

tree::TerminalNode* ChipsParser::C_if_statementContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

tree::TerminalNode* ChipsParser::C_if_statementContext::L_CURL() {
  return getToken(ChipsParser::L_CURL, 0);
}

tree::TerminalNode* ChipsParser::C_if_statementContext::R_CURL() {
  return getToken(ChipsParser::R_CURL, 0);
}

std::vector<ChipsParser::C_statementContext *> ChipsParser::C_if_statementContext::c_statement() {
  return getRuleContexts<ChipsParser::C_statementContext>();
}

ChipsParser::C_statementContext* ChipsParser::C_if_statementContext::c_statement(size_t i) {
  return getRuleContext<ChipsParser::C_statementContext>(i);
}


size_t ChipsParser::C_if_statementContext::getRuleIndex() const {
  return ChipsParser::RuleC_if_statement;
}


std::any ChipsParser::C_if_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitC_if_statement(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::C_if_statementContext* ChipsParser::c_if_statement() {
  C_if_statementContext *_localctx = _tracker.createInstance<C_if_statementContext>(_ctx, getState());
  enterRule(_localctx, 86, ChipsParser::RuleC_if_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(705);
    match(ChipsParser::IF_KW);
    setState(706);
    match(ChipsParser::L_PARENTH);
    setState(707);
    c_expr();
    setState(708);
    match(ChipsParser::R_PARENTH);
    setState(709);
    match(ChipsParser::L_CURL);
    setState(713);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(710);
      c_statement();
      setState(715);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(716);
    match(ChipsParser::R_CURL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

ChipsParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::StatementContext::getRuleIndex() const {
  return ChipsParser::RuleStatement;
}

void ChipsParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- StatementIfContext ------------------------------------------------------------------

ChipsParser::If_statementContext* ChipsParser::StatementIfContext::if_statement() {
  return getRuleContext<ChipsParser::If_statementContext>(0);
}

ChipsParser::StatementIfContext::StatementIfContext(StatementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::StatementIfContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitStatementIf(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StatementDeclarationContext ------------------------------------------------------------------

ChipsParser::Df_typeContext* ChipsParser::StatementDeclarationContext::df_type() {
  return getRuleContext<ChipsParser::Df_typeContext>(0);
}

ChipsParser::SuffixesContext* ChipsParser::StatementDeclarationContext::suffixes() {
  return getRuleContext<ChipsParser::SuffixesContext>(0);
}

tree::TerminalNode* ChipsParser::StatementDeclarationContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::StatementDeclarationContext::SEMICOL() {
  return getToken(ChipsParser::SEMICOL, 0);
}

tree::TerminalNode* ChipsParser::StatementDeclarationContext::ASSIGN() {
  return getToken(ChipsParser::ASSIGN, 0);
}

ChipsParser::ExprContext* ChipsParser::StatementDeclarationContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}

ChipsParser::StatementDeclarationContext::StatementDeclarationContext(StatementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::StatementDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitStatementDeclaration(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StatementLoopContext ------------------------------------------------------------------

ChipsParser::Loop_statementContext* ChipsParser::StatementLoopContext::loop_statement() {
  return getRuleContext<ChipsParser::Loop_statementContext>(0);
}

ChipsParser::StatementLoopContext::StatementLoopContext(StatementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::StatementLoopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitStatementLoop(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StatementContextualAssignmentContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::StatementContextualAssignmentContext::CTX_KW() {
  return getToken(ChipsParser::CTX_KW, 0);
}

tree::TerminalNode* ChipsParser::StatementContextualAssignmentContext::PERIOD() {
  return getToken(ChipsParser::PERIOD, 0);
}

tree::TerminalNode* ChipsParser::StatementContextualAssignmentContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

ChipsParser::SuffixesContext* ChipsParser::StatementContextualAssignmentContext::suffixes() {
  return getRuleContext<ChipsParser::SuffixesContext>(0);
}

tree::TerminalNode* ChipsParser::StatementContextualAssignmentContext::ASSIGN() {
  return getToken(ChipsParser::ASSIGN, 0);
}

ChipsParser::ExprContext* ChipsParser::StatementContextualAssignmentContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}

tree::TerminalNode* ChipsParser::StatementContextualAssignmentContext::SEMICOL() {
  return getToken(ChipsParser::SEMICOL, 0);
}

ChipsParser::StatementContextualAssignmentContext::StatementContextualAssignmentContext(StatementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::StatementContextualAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitStatementContextualAssignment(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StatementAssignmentContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::StatementAssignmentContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

ChipsParser::SuffixesContext* ChipsParser::StatementAssignmentContext::suffixes() {
  return getRuleContext<ChipsParser::SuffixesContext>(0);
}

tree::TerminalNode* ChipsParser::StatementAssignmentContext::ASSIGN() {
  return getToken(ChipsParser::ASSIGN, 0);
}

ChipsParser::ExprContext* ChipsParser::StatementAssignmentContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}

tree::TerminalNode* ChipsParser::StatementAssignmentContext::SEMICOL() {
  return getToken(ChipsParser::SEMICOL, 0);
}

ChipsParser::StatementAssignmentContext::StatementAssignmentContext(StatementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::StatementAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitStatementAssignment(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StatementIfElseContext ------------------------------------------------------------------

ChipsParser::If_else_statementContext* ChipsParser::StatementIfElseContext::if_else_statement() {
  return getRuleContext<ChipsParser::If_else_statementContext>(0);
}

ChipsParser::StatementIfElseContext::StatementIfElseContext(StatementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::StatementIfElseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitStatementIfElse(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::StatementContext* ChipsParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 88, ChipsParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(744);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::StatementDeclarationContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(718);
      df_type();
      setState(719);
      suffixes();
      setState(720);
      match(ChipsParser::IDENTIFIER);
      setState(723);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ChipsParser::ASSIGN) {
        setState(721);
        match(ChipsParser::ASSIGN);
        setState(722);
        expr();
      }
      setState(725);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::StatementAssignmentContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(727);
      match(ChipsParser::IDENTIFIER);
      setState(728);
      suffixes();
      setState(729);
      match(ChipsParser::ASSIGN);
      setState(730);
      expr();
      setState(731);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::StatementContextualAssignmentContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(733);
      match(ChipsParser::CTX_KW);
      setState(734);
      match(ChipsParser::PERIOD);
      setState(735);
      match(ChipsParser::IDENTIFIER);
      setState(736);
      suffixes();
      setState(737);
      match(ChipsParser::ASSIGN);
      setState(738);
      expr();
      setState(739);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::StatementLoopContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(741);
      loop_statement();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::StatementIfElseContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(742);
      if_else_statement();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ChipsParser::StatementIfContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(743);
      if_statement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- S_statementContext ------------------------------------------------------------------

ChipsParser::S_statementContext::S_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::S_statementContext::getRuleIndex() const {
  return ChipsParser::RuleS_statement;
}

void ChipsParser::S_statementContext::copyFrom(S_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FeedingStatementContext ------------------------------------------------------------------

ChipsParser::BlockContext* ChipsParser::FeedingStatementContext::block() {
  return getRuleContext<ChipsParser::BlockContext>(0);
}

tree::TerminalNode* ChipsParser::FeedingStatementContext::PERIOD() {
  return getToken(ChipsParser::PERIOD, 0);
}

tree::TerminalNode* ChipsParser::FeedingStatementContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::FeedingStatementContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

ChipsParser::S_exprContext* ChipsParser::FeedingStatementContext::s_expr() {
  return getRuleContext<ChipsParser::S_exprContext>(0);
}

tree::TerminalNode* ChipsParser::FeedingStatementContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

tree::TerminalNode* ChipsParser::FeedingStatementContext::SEMICOL() {
  return getToken(ChipsParser::SEMICOL, 0);
}

ChipsParser::FeedingStatementContext::FeedingStatementContext(S_statementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::FeedingStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitFeedingStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SLoopStatementContext ------------------------------------------------------------------

ChipsParser::S_loop_statementContext* ChipsParser::SLoopStatementContext::s_loop_statement() {
  return getRuleContext<ChipsParser::S_loop_statementContext>(0);
}

ChipsParser::SLoopStatementContext::SLoopStatementContext(S_statementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::SLoopStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitSLoopStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ObjectDeclarationContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> ChipsParser::ObjectDeclarationContext::IDENTIFIER() {
  return getTokens(ChipsParser::IDENTIFIER);
}

tree::TerminalNode* ChipsParser::ObjectDeclarationContext::IDENTIFIER(size_t i) {
  return getToken(ChipsParser::IDENTIFIER, i);
}

ChipsParser::SuffixesContext* ChipsParser::ObjectDeclarationContext::suffixes() {
  return getRuleContext<ChipsParser::SuffixesContext>(0);
}

tree::TerminalNode* ChipsParser::ObjectDeclarationContext::SEMICOL() {
  return getToken(ChipsParser::SEMICOL, 0);
}

ChipsParser::ObjectDeclarationContext::ObjectDeclarationContext(S_statementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::ObjectDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitObjectDeclaration(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LinkingStatementContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::LinkingStatementContext::LINK_KW() {
  return getToken(ChipsParser::LINK_KW, 0);
}

std::vector<tree::TerminalNode *> ChipsParser::LinkingStatementContext::IDENTIFIER() {
  return getTokens(ChipsParser::IDENTIFIER);
}

tree::TerminalNode* ChipsParser::LinkingStatementContext::IDENTIFIER(size_t i) {
  return getToken(ChipsParser::IDENTIFIER, i);
}

std::vector<ChipsParser::SuffixesContext *> ChipsParser::LinkingStatementContext::suffixes() {
  return getRuleContexts<ChipsParser::SuffixesContext>();
}

ChipsParser::SuffixesContext* ChipsParser::LinkingStatementContext::suffixes(size_t i) {
  return getRuleContext<ChipsParser::SuffixesContext>(i);
}

tree::TerminalNode* ChipsParser::LinkingStatementContext::TO_KW() {
  return getToken(ChipsParser::TO_KW, 0);
}

tree::TerminalNode* ChipsParser::LinkingStatementContext::SEMICOL() {
  return getToken(ChipsParser::SEMICOL, 0);
}

ChipsParser::LinkingStatementContext::LinkingStatementContext(S_statementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::LinkingStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitLinkingStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SIfStatementContext ------------------------------------------------------------------

ChipsParser::S_if_statementContext* ChipsParser::SIfStatementContext::s_if_statement() {
  return getRuleContext<ChipsParser::S_if_statementContext>(0);
}

ChipsParser::SIfStatementContext::SIfStatementContext(S_statementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::SIfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitSIfStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SIfElseStatementContext ------------------------------------------------------------------

ChipsParser::S_if_else_statementContext* ChipsParser::SIfElseStatementContext::s_if_else_statement() {
  return getRuleContext<ChipsParser::S_if_else_statementContext>(0);
}

ChipsParser::SIfElseStatementContext::SIfElseStatementContext(S_statementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::SIfElseStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitSIfElseStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ImplementationStatementContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> ChipsParser::ImplementationStatementContext::IDENTIFIER() {
  return getTokens(ChipsParser::IDENTIFIER);
}

tree::TerminalNode* ChipsParser::ImplementationStatementContext::IDENTIFIER(size_t i) {
  return getToken(ChipsParser::IDENTIFIER, i);
}

std::vector<ChipsParser::SuffixesContext *> ChipsParser::ImplementationStatementContext::suffixes() {
  return getRuleContexts<ChipsParser::SuffixesContext>();
}

ChipsParser::SuffixesContext* ChipsParser::ImplementationStatementContext::suffixes(size_t i) {
  return getRuleContext<ChipsParser::SuffixesContext>(i);
}

tree::TerminalNode* ChipsParser::ImplementationStatementContext::IMPLEMENTATION_KW() {
  return getToken(ChipsParser::IMPLEMENTATION_KW, 0);
}

tree::TerminalNode* ChipsParser::ImplementationStatementContext::USING_KW() {
  return getToken(ChipsParser::USING_KW, 0);
}

tree::TerminalNode* ChipsParser::ImplementationStatementContext::SEMICOL() {
  return getToken(ChipsParser::SEMICOL, 0);
}

ChipsParser::ImplementationStatementContext::ImplementationStatementContext(S_statementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::ImplementationStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitImplementationStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RegularStatementContext ------------------------------------------------------------------

ChipsParser::StatementContext* ChipsParser::RegularStatementContext::statement() {
  return getRuleContext<ChipsParser::StatementContext>(0);
}

ChipsParser::RegularStatementContext::RegularStatementContext(S_statementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::RegularStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitRegularStatement(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::S_statementContext* ChipsParser::s_statement() {
  S_statementContext *_localctx = _tracker.createInstance<S_statementContext>(_ctx, getState());
  enterRule(_localctx, 90, ChipsParser::RuleS_statement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(780);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::ObjectDeclarationContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(746);
      match(ChipsParser::IDENTIFIER);
      setState(747);
      suffixes();
      setState(748);
      match(ChipsParser::IDENTIFIER);
      setState(749);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::FeedingStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(751);
      block();
      setState(752);
      match(ChipsParser::PERIOD);
      setState(753);
      match(ChipsParser::IDENTIFIER);
      setState(754);
      match(ChipsParser::L_PARENTH);
      setState(755);
      s_expr();
      setState(756);
      match(ChipsParser::R_PARENTH);
      setState(757);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::LinkingStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(759);
      match(ChipsParser::LINK_KW);
      setState(760);
      match(ChipsParser::IDENTIFIER);
      setState(761);
      suffixes();
      setState(762);
      match(ChipsParser::TO_KW);
      setState(763);
      match(ChipsParser::IDENTIFIER);
      setState(764);
      suffixes();
      setState(765);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::ImplementationStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(767);
      match(ChipsParser::IDENTIFIER);
      setState(768);
      suffixes();
      setState(769);
      match(ChipsParser::IMPLEMENTATION_KW);
      setState(770);
      match(ChipsParser::IDENTIFIER);
      setState(771);
      suffixes();
      setState(772);
      match(ChipsParser::USING_KW);
      setState(773);
      match(ChipsParser::IDENTIFIER);
      setState(774);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::SLoopStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(776);
      s_loop_statement();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ChipsParser::SIfElseStatementContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(777);
      s_if_else_statement();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ChipsParser::SIfStatementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(778);
      s_if_statement();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<ChipsParser::RegularStatementContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(779);
      statement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- S_exprContext ------------------------------------------------------------------

ChipsParser::S_exprContext::S_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::S_exprContext::getRuleIndex() const {
  return ChipsParser::RuleS_expr;
}

void ChipsParser::S_exprContext::copyFrom(S_exprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SRegularExpressionContext ------------------------------------------------------------------

ChipsParser::ExprContext* ChipsParser::SRegularExpressionContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}

ChipsParser::SRegularExpressionContext::SRegularExpressionContext(S_exprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::SRegularExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitSRegularExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SBlockOutputExpressionContext ------------------------------------------------------------------

ChipsParser::BlockContext* ChipsParser::SBlockOutputExpressionContext::block() {
  return getRuleContext<ChipsParser::BlockContext>(0);
}

tree::TerminalNode* ChipsParser::SBlockOutputExpressionContext::PERIOD() {
  return getToken(ChipsParser::PERIOD, 0);
}

tree::TerminalNode* ChipsParser::SBlockOutputExpressionContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

ChipsParser::SBlockOutputExpressionContext::SBlockOutputExpressionContext(S_exprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::SBlockOutputExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitSBlockOutputExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SCollectiveCastExpressionContext ------------------------------------------------------------------

ChipsParser::Collective_operationContext* ChipsParser::SCollectiveCastExpressionContext::collective_operation() {
  return getRuleContext<ChipsParser::Collective_operationContext>(0);
}

ChipsParser::BlockContext* ChipsParser::SCollectiveCastExpressionContext::block() {
  return getRuleContext<ChipsParser::BlockContext>(0);
}

tree::TerminalNode* ChipsParser::SCollectiveCastExpressionContext::PERIOD() {
  return getToken(ChipsParser::PERIOD, 0);
}

tree::TerminalNode* ChipsParser::SCollectiveCastExpressionContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

ChipsParser::SCollectiveCastExpressionContext::SCollectiveCastExpressionContext(S_exprContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::SCollectiveCastExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitSCollectiveCastExpression(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::S_exprContext* ChipsParser::s_expr() {
  S_exprContext *_localctx = _tracker.createInstance<S_exprContext>(_ctx, getState());
  enterRule(_localctx, 92, ChipsParser::RuleS_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(792);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::SBlockOutputExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(782);
      block();
      setState(783);
      match(ChipsParser::PERIOD);
      setState(784);
      match(ChipsParser::IDENTIFIER);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::SCollectiveCastExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(786);
      collective_operation();
      setState(787);
      block();
      setState(788);
      match(ChipsParser::PERIOD);
      setState(789);
      match(ChipsParser::IDENTIFIER);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::SRegularExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(791);
      expr();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Collective_operationContext ------------------------------------------------------------------

ChipsParser::Collective_operationContext::Collective_operationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::Collective_operationContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

tree::TerminalNode* ChipsParser::Collective_operationContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::Collective_operationContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}


size_t ChipsParser::Collective_operationContext::getRuleIndex() const {
  return ChipsParser::RuleCollective_operation;
}


std::any ChipsParser::Collective_operationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCollective_operation(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::Collective_operationContext* ChipsParser::collective_operation() {
  Collective_operationContext *_localctx = _tracker.createInstance<Collective_operationContext>(_ctx, getState());
  enterRule(_localctx, 94, ChipsParser::RuleCollective_operation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(794);
    match(ChipsParser::L_PARENTH);
    setState(795);
    match(ChipsParser::IDENTIFIER);
    setState(796);
    match(ChipsParser::R_PARENTH);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- C_statementContext ------------------------------------------------------------------

ChipsParser::C_statementContext::C_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::C_statementContext::getRuleIndex() const {
  return ChipsParser::RuleC_statement;
}

void ChipsParser::C_statementContext::copyFrom(C_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CollectiveIfElseStatementContext ------------------------------------------------------------------

ChipsParser::C_if_else_statementContext* ChipsParser::CollectiveIfElseStatementContext::c_if_else_statement() {
  return getRuleContext<ChipsParser::C_if_else_statementContext>(0);
}

ChipsParser::CollectiveIfElseStatementContext::CollectiveIfElseStatementContext(C_statementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::CollectiveIfElseStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCollectiveIfElseStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CollectiveLoopStatementContext ------------------------------------------------------------------

ChipsParser::C_loop_statementContext* ChipsParser::CollectiveLoopStatementContext::c_loop_statement() {
  return getRuleContext<ChipsParser::C_loop_statementContext>(0);
}

ChipsParser::CollectiveLoopStatementContext::CollectiveLoopStatementContext(C_statementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::CollectiveLoopStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCollectiveLoopStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CollectiveIfStatementContext ------------------------------------------------------------------

ChipsParser::C_if_statementContext* ChipsParser::CollectiveIfStatementContext::c_if_statement() {
  return getRuleContext<ChipsParser::C_if_statementContext>(0);
}

ChipsParser::CollectiveIfStatementContext::CollectiveIfStatementContext(C_statementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::CollectiveIfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCollectiveIfStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CollectiveAssignmentContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::CollectiveAssignmentContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

ChipsParser::C_suffixesContext* ChipsParser::CollectiveAssignmentContext::c_suffixes() {
  return getRuleContext<ChipsParser::C_suffixesContext>(0);
}

tree::TerminalNode* ChipsParser::CollectiveAssignmentContext::ASSIGN() {
  return getToken(ChipsParser::ASSIGN, 0);
}

ChipsParser::C_exprContext* ChipsParser::CollectiveAssignmentContext::c_expr() {
  return getRuleContext<ChipsParser::C_exprContext>(0);
}

tree::TerminalNode* ChipsParser::CollectiveAssignmentContext::SEMICOL() {
  return getToken(ChipsParser::SEMICOL, 0);
}

ChipsParser::CollectiveAssignmentContext::CollectiveAssignmentContext(C_statementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::CollectiveAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCollectiveAssignment(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CollectiveVariableDeclarationContext ------------------------------------------------------------------

ChipsParser::Cdf_full_declarationContext* ChipsParser::CollectiveVariableDeclarationContext::cdf_full_declaration() {
  return getRuleContext<ChipsParser::Cdf_full_declarationContext>(0);
}

tree::TerminalNode* ChipsParser::CollectiveVariableDeclarationContext::SEMICOL() {
  return getToken(ChipsParser::SEMICOL, 0);
}

ChipsParser::CollectiveVariableDeclarationContext::CollectiveVariableDeclarationContext(C_statementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::CollectiveVariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCollectiveVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ContextualAssignmentContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::ContextualAssignmentContext::CTX_KW() {
  return getToken(ChipsParser::CTX_KW, 0);
}

tree::TerminalNode* ChipsParser::ContextualAssignmentContext::PERIOD() {
  return getToken(ChipsParser::PERIOD, 0);
}

tree::TerminalNode* ChipsParser::ContextualAssignmentContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

ChipsParser::C_suffixesContext* ChipsParser::ContextualAssignmentContext::c_suffixes() {
  return getRuleContext<ChipsParser::C_suffixesContext>(0);
}

tree::TerminalNode* ChipsParser::ContextualAssignmentContext::ASSIGN() {
  return getToken(ChipsParser::ASSIGN, 0);
}

ChipsParser::C_exprContext* ChipsParser::ContextualAssignmentContext::c_expr() {
  return getRuleContext<ChipsParser::C_exprContext>(0);
}

tree::TerminalNode* ChipsParser::ContextualAssignmentContext::SEMICOL() {
  return getToken(ChipsParser::SEMICOL, 0);
}

ChipsParser::ContextualAssignmentContext::ContextualAssignmentContext(C_statementContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::ContextualAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitContextualAssignment(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::C_statementContext* ChipsParser::c_statement() {
  C_statementContext *_localctx = _tracker.createInstance<C_statementContext>(_ctx, getState());
  enterRule(_localctx, 96, ChipsParser::RuleC_statement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(818);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::CollectiveVariableDeclarationContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(798);
      cdf_full_declaration();
      setState(799);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::CollectiveAssignmentContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(801);
      match(ChipsParser::IDENTIFIER);
      setState(802);
      c_suffixes();
      setState(803);
      match(ChipsParser::ASSIGN);
      setState(804);
      c_expr();
      setState(805);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::ContextualAssignmentContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(807);
      match(ChipsParser::CTX_KW);
      setState(808);
      match(ChipsParser::PERIOD);
      setState(809);
      match(ChipsParser::IDENTIFIER);
      setState(810);
      c_suffixes();
      setState(811);
      match(ChipsParser::ASSIGN);
      setState(812);
      c_expr();
      setState(813);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::CollectiveLoopStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(815);
      c_loop_statement();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::CollectiveIfElseStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(816);
      c_if_else_statement();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ChipsParser::CollectiveIfStatementContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(817);
      c_if_statement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Named_outputContext ------------------------------------------------------------------

ChipsParser::Named_outputContext::Named_outputContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::Named_outputContext::ARROW() {
  return getToken(ChipsParser::ARROW, 0);
}

tree::TerminalNode* ChipsParser::Named_outputContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::Named_outputContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

std::vector<ChipsParser::ExprContext *> ChipsParser::Named_outputContext::expr() {
  return getRuleContexts<ChipsParser::ExprContext>();
}

ChipsParser::ExprContext* ChipsParser::Named_outputContext::expr(size_t i) {
  return getRuleContext<ChipsParser::ExprContext>(i);
}

tree::TerminalNode* ChipsParser::Named_outputContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

std::vector<tree::TerminalNode *> ChipsParser::Named_outputContext::COMMA() {
  return getTokens(ChipsParser::COMMA);
}

tree::TerminalNode* ChipsParser::Named_outputContext::COMMA(size_t i) {
  return getToken(ChipsParser::COMMA, i);
}


size_t ChipsParser::Named_outputContext::getRuleIndex() const {
  return ChipsParser::RuleNamed_output;
}


std::any ChipsParser::Named_outputContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitNamed_output(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::Named_outputContext* ChipsParser::named_output() {
  Named_outputContext *_localctx = _tracker.createInstance<Named_outputContext>(_ctx, getState());
  enterRule(_localctx, 98, ChipsParser::RuleNamed_output);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(820);
    match(ChipsParser::ARROW);
    setState(821);
    match(ChipsParser::IDENTIFIER);
    setState(822);
    match(ChipsParser::L_PARENTH);
    setState(823);
    expr();
    setState(828);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ChipsParser::COMMA) {
      setState(824);
      match(ChipsParser::COMMA);
      setState(825);
      expr();
      setState(830);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(831);
    match(ChipsParser::R_PARENTH);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- P_named_outputContext ------------------------------------------------------------------

ChipsParser::P_named_outputContext::P_named_outputContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::P_named_outputContext::getRuleIndex() const {
  return ChipsParser::RuleP_named_output;
}

void ChipsParser::P_named_outputContext::copyFrom(P_named_outputContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FunctionOutputContext ------------------------------------------------------------------

ChipsParser::Named_outputContext* ChipsParser::FunctionOutputContext::named_output() {
  return getRuleContext<ChipsParser::Named_outputContext>(0);
}

ChipsParser::FunctionOutputContext::FunctionOutputContext(P_named_outputContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::FunctionOutputContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitFunctionOutput(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ActuatorOutputContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::ActuatorOutputContext::ARROW() {
  return getToken(ChipsParser::ARROW, 0);
}

tree::TerminalNode* ChipsParser::ActuatorOutputContext::ACTUATOR_KW() {
  return getToken(ChipsParser::ACTUATOR_KW, 0);
}

tree::TerminalNode* ChipsParser::ActuatorOutputContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::ActuatorOutputContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

std::vector<ChipsParser::ExprContext *> ChipsParser::ActuatorOutputContext::expr() {
  return getRuleContexts<ChipsParser::ExprContext>();
}

ChipsParser::ExprContext* ChipsParser::ActuatorOutputContext::expr(size_t i) {
  return getRuleContext<ChipsParser::ExprContext>(i);
}

tree::TerminalNode* ChipsParser::ActuatorOutputContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

std::vector<tree::TerminalNode *> ChipsParser::ActuatorOutputContext::COMMA() {
  return getTokens(ChipsParser::COMMA);
}

tree::TerminalNode* ChipsParser::ActuatorOutputContext::COMMA(size_t i) {
  return getToken(ChipsParser::COMMA, i);
}

ChipsParser::ActuatorOutputContext::ActuatorOutputContext(P_named_outputContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::ActuatorOutputContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitActuatorOutput(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::P_named_outputContext* ChipsParser::p_named_output() {
  P_named_outputContext *_localctx = _tracker.createInstance<P_named_outputContext>(_ctx, getState());
  enterRule(_localctx, 100, ChipsParser::RuleP_named_output);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(848);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::ActuatorOutputContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(833);
      match(ChipsParser::ARROW);
      setState(834);
      match(ChipsParser::ACTUATOR_KW);
      setState(835);
      match(ChipsParser::IDENTIFIER);
      setState(836);
      match(ChipsParser::L_PARENTH);
      setState(837);
      expr();
      setState(842);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ChipsParser::COMMA) {
        setState(838);
        match(ChipsParser::COMMA);
        setState(839);
        expr();
        setState(844);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(845);
      match(ChipsParser::R_PARENTH);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::FunctionOutputContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(847);
      named_output();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Df_parameter_declContext ------------------------------------------------------------------

ChipsParser::Df_parameter_declContext::Df_parameter_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ChipsParser::Df_typeContext* ChipsParser::Df_parameter_declContext::df_type() {
  return getRuleContext<ChipsParser::Df_typeContext>(0);
}

ChipsParser::SuffixesContext* ChipsParser::Df_parameter_declContext::suffixes() {
  return getRuleContext<ChipsParser::SuffixesContext>(0);
}

tree::TerminalNode* ChipsParser::Df_parameter_declContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::Df_parameter_declContext::ASSIGN() {
  return getToken(ChipsParser::ASSIGN, 0);
}

ChipsParser::ExprContext* ChipsParser::Df_parameter_declContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}


size_t ChipsParser::Df_parameter_declContext::getRuleIndex() const {
  return ChipsParser::RuleDf_parameter_decl;
}


std::any ChipsParser::Df_parameter_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitDf_parameter_decl(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::Df_parameter_declContext* ChipsParser::df_parameter_decl() {
  Df_parameter_declContext *_localctx = _tracker.createInstance<Df_parameter_declContext>(_ctx, getState());
  enterRule(_localctx, 102, ChipsParser::RuleDf_parameter_decl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(850);
    df_type();
    setState(851);
    suffixes();
    setState(852);
    match(ChipsParser::IDENTIFIER);
    setState(855);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ChipsParser::ASSIGN) {
      setState(853);
      match(ChipsParser::ASSIGN);
      setState(854);
      expr();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Df_typeContext ------------------------------------------------------------------

ChipsParser::Df_typeContext::Df_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::Df_typeContext::getRuleIndex() const {
  return ChipsParser::RuleDf_type;
}

void ChipsParser::Df_typeContext::copyFrom(Df_typeContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BoolTypeContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::BoolTypeContext::BOOL_KW() {
  return getToken(ChipsParser::BOOL_KW, 0);
}

ChipsParser::BoolTypeContext::BoolTypeContext(Df_typeContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::BoolTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitBoolType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntTypeContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::IntTypeContext::INT_KW() {
  return getToken(ChipsParser::INT_KW, 0);
}

ChipsParser::IntTypeContext::IntTypeContext(Df_typeContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::IntTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitIntType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FloatTypeContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::FloatTypeContext::FLOAT_KW() {
  return getToken(ChipsParser::FLOAT_KW, 0);
}

ChipsParser::FloatTypeContext::FloatTypeContext(Df_typeContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::FloatTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitFloatType(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::Df_typeContext* ChipsParser::df_type() {
  Df_typeContext *_localctx = _tracker.createInstance<Df_typeContext>(_ctx, getState());
  enterRule(_localctx, 104, ChipsParser::RuleDf_type);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(860);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ChipsParser::INT_KW: {
        _localctx = _tracker.createInstance<ChipsParser::IntTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(857);
        match(ChipsParser::INT_KW);
        break;
      }

      case ChipsParser::FLOAT_KW: {
        _localctx = _tracker.createInstance<ChipsParser::FloatTypeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(858);
        match(ChipsParser::FLOAT_KW);
        break;
      }

      case ChipsParser::BOOL_KW: {
        _localctx = _tracker.createInstance<ChipsParser::BoolTypeContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(859);
        match(ChipsParser::BOOL_KW);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pdf_parameter_typeContext ------------------------------------------------------------------

ChipsParser::Pdf_parameter_typeContext::Pdf_parameter_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ChipsParser::Pdf_parameter_typeContext::getRuleIndex() const {
  return ChipsParser::RulePdf_parameter_type;
}

void ChipsParser::Pdf_parameter_typeContext::copyFrom(Pdf_parameter_typeContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SensorParameterTypeContext ------------------------------------------------------------------

tree::TerminalNode* ChipsParser::SensorParameterTypeContext::SENSOR_KW() {
  return getToken(ChipsParser::SENSOR_KW, 0);
}

ChipsParser::Df_typeContext* ChipsParser::SensorParameterTypeContext::df_type() {
  return getRuleContext<ChipsParser::Df_typeContext>(0);
}

ChipsParser::SuffixesContext* ChipsParser::SensorParameterTypeContext::suffixes() {
  return getRuleContext<ChipsParser::SuffixesContext>(0);
}

ChipsParser::SensorParameterTypeContext::SensorParameterTypeContext(Pdf_parameter_typeContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::SensorParameterTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitSensorParameterType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionParameterTypeContext ------------------------------------------------------------------

ChipsParser::Df_typeContext* ChipsParser::FunctionParameterTypeContext::df_type() {
  return getRuleContext<ChipsParser::Df_typeContext>(0);
}

ChipsParser::SuffixesContext* ChipsParser::FunctionParameterTypeContext::suffixes() {
  return getRuleContext<ChipsParser::SuffixesContext>(0);
}

ChipsParser::FunctionParameterTypeContext::FunctionParameterTypeContext(Pdf_parameter_typeContext *ctx) { copyFrom(ctx); }


std::any ChipsParser::FunctionParameterTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitFunctionParameterType(this);
  else
    return visitor->visitChildren(this);
}
ChipsParser::Pdf_parameter_typeContext* ChipsParser::pdf_parameter_type() {
  Pdf_parameter_typeContext *_localctx = _tracker.createInstance<Pdf_parameter_typeContext>(_ctx, getState());
  enterRule(_localctx, 106, ChipsParser::RulePdf_parameter_type);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(869);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ChipsParser::INT_KW:
      case ChipsParser::FLOAT_KW:
      case ChipsParser::BOOL_KW: {
        _localctx = _tracker.createInstance<ChipsParser::FunctionParameterTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(862);
        df_type();
        setState(863);
        suffixes();
        break;
      }

      case ChipsParser::SENSOR_KW: {
        _localctx = _tracker.createInstance<ChipsParser::SensorParameterTypeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(865);
        match(ChipsParser::SENSOR_KW);
        setState(866);
        df_type();
        setState(867);
        suffixes();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pdf_parameter_declContext ------------------------------------------------------------------

ChipsParser::Pdf_parameter_declContext::Pdf_parameter_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ChipsParser::Pdf_parameter_typeContext* ChipsParser::Pdf_parameter_declContext::pdf_parameter_type() {
  return getRuleContext<ChipsParser::Pdf_parameter_typeContext>(0);
}

tree::TerminalNode* ChipsParser::Pdf_parameter_declContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::Pdf_parameter_declContext::ASSIGN() {
  return getToken(ChipsParser::ASSIGN, 0);
}

ChipsParser::ExprContext* ChipsParser::Pdf_parameter_declContext::expr() {
  return getRuleContext<ChipsParser::ExprContext>(0);
}


size_t ChipsParser::Pdf_parameter_declContext::getRuleIndex() const {
  return ChipsParser::RulePdf_parameter_decl;
}


std::any ChipsParser::Pdf_parameter_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitPdf_parameter_decl(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::Pdf_parameter_declContext* ChipsParser::pdf_parameter_decl() {
  Pdf_parameter_declContext *_localctx = _tracker.createInstance<Pdf_parameter_declContext>(_ctx, getState());
  enterRule(_localctx, 108, ChipsParser::RulePdf_parameter_decl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(871);
    pdf_parameter_type();
    setState(872);
    match(ChipsParser::IDENTIFIER);
    setState(875);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ChipsParser::ASSIGN) {
      setState(873);
      match(ChipsParser::ASSIGN);
      setState(874);
      expr();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Cdf_defaulted_declContext ------------------------------------------------------------------

ChipsParser::Cdf_defaulted_declContext::Cdf_defaulted_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ChipsParser::Df_typeContext* ChipsParser::Cdf_defaulted_declContext::df_type() {
  return getRuleContext<ChipsParser::Df_typeContext>(0);
}

ChipsParser::SuffixesContext* ChipsParser::Cdf_defaulted_declContext::suffixes() {
  return getRuleContext<ChipsParser::SuffixesContext>(0);
}

tree::TerminalNode* ChipsParser::Cdf_defaulted_declContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::Cdf_defaulted_declContext::ASSIGN() {
  return getToken(ChipsParser::ASSIGN, 0);
}

ChipsParser::C_exprContext* ChipsParser::Cdf_defaulted_declContext::c_expr() {
  return getRuleContext<ChipsParser::C_exprContext>(0);
}


size_t ChipsParser::Cdf_defaulted_declContext::getRuleIndex() const {
  return ChipsParser::RuleCdf_defaulted_decl;
}


std::any ChipsParser::Cdf_defaulted_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCdf_defaulted_decl(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::Cdf_defaulted_declContext* ChipsParser::cdf_defaulted_decl() {
  Cdf_defaulted_declContext *_localctx = _tracker.createInstance<Cdf_defaulted_declContext>(_ctx, getState());
  enterRule(_localctx, 110, ChipsParser::RuleCdf_defaulted_decl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(877);
    df_type();
    setState(878);
    suffixes();
    setState(879);
    match(ChipsParser::IDENTIFIER);
    setState(880);
    match(ChipsParser::ASSIGN);
    setState(881);
    c_expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Cdf_full_declarationContext ------------------------------------------------------------------

ChipsParser::Cdf_full_declarationContext::Cdf_full_declarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ChipsParser::Df_typeContext* ChipsParser::Cdf_full_declarationContext::df_type() {
  return getRuleContext<ChipsParser::Df_typeContext>(0);
}

ChipsParser::SuffixesContext* ChipsParser::Cdf_full_declarationContext::suffixes() {
  return getRuleContext<ChipsParser::SuffixesContext>(0);
}

tree::TerminalNode* ChipsParser::Cdf_full_declarationContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::Cdf_full_declarationContext::ASSIGN() {
  return getToken(ChipsParser::ASSIGN, 0);
}

ChipsParser::C_exprContext* ChipsParser::Cdf_full_declarationContext::c_expr() {
  return getRuleContext<ChipsParser::C_exprContext>(0);
}


size_t ChipsParser::Cdf_full_declarationContext::getRuleIndex() const {
  return ChipsParser::RuleCdf_full_declaration;
}


std::any ChipsParser::Cdf_full_declarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitCdf_full_declaration(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::Cdf_full_declarationContext* ChipsParser::cdf_full_declaration() {
  Cdf_full_declarationContext *_localctx = _tracker.createInstance<Cdf_full_declarationContext>(_ctx, getState());
  enterRule(_localctx, 112, ChipsParser::RuleCdf_full_declaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(883);
    df_type();
    setState(884);
    suffixes();
    setState(885);
    match(ChipsParser::IDENTIFIER);
    setState(888);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ChipsParser::ASSIGN) {
      setState(886);
      match(ChipsParser::ASSIGN);
      setState(887);
      c_expr();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void ChipsParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  chipsParserInitialize();
#else
  ::antlr4::internal::call_once(chipsParserOnceFlag, chipsParserInitialize);
#endif
}
