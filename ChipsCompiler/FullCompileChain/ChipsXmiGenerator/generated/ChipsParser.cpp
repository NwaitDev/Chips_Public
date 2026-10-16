
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
      "program", "system", "preamble", "object_def", "function_def", "collective_op_def", 
      "c_default_output", "c_channeled_output", "l_function_def", "p_function_def", 
      "c_signature", "c_keywords", "with_section", "with_statement", "init_section", 
      "then_section", "expr", "expr0", "expr01", "expr1", "expr2", "cast", 
      "c_expr", "c_stopless_expr", "c_stopless_expr0", "c_stopless_expr01", 
      "c_stopless_expr1", "c_stopless_expr2", "c_cast", "suffixes", "c_suffixes", 
      "s_suffixable_expr", "block", "loop_in", "c_loop_in", "loop_statement", 
      "c_loop_statement", "s_loop_statement", "if_else_statement", "s_if_else_statement", 
      "c_if_else_statement", "if_statement", "s_if_statement", "c_if_statement", 
      "statement", "s_statement", "s_expr", "collective_operation", "c_statement", 
      "named_output", "p_named_output", "df_parameter_decl", "df_type", 
      "pdf_parameter_type", "pdf_parameter_decl", "cdf_defaulted_decl", 
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
  	4,1,65,899,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,1,0,5,0,116,8,0,10,0,12,0,119,9,0,1,0,3,0,122,8,0,1,0,1,0,1,1,1,1,
  	1,1,5,1,129,8,1,10,1,12,1,132,9,1,1,1,1,1,1,2,1,2,1,2,3,2,139,8,2,1,3,
  	1,3,1,3,1,3,1,4,1,4,3,4,147,8,4,1,5,1,5,1,5,5,5,152,8,5,10,5,12,5,155,
  	9,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,5,5,164,8,5,10,5,12,5,167,9,5,1,5,1,5,
  	4,5,171,8,5,11,5,12,5,172,1,5,5,5,176,8,5,10,5,12,5,179,9,5,1,5,1,5,5,
  	5,183,8,5,10,5,12,5,186,9,5,3,5,188,8,5,1,6,1,6,1,6,1,6,1,6,1,6,5,6,196,
  	8,6,10,6,12,6,199,9,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,5,7,209,8,7,10,
  	7,12,7,212,9,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,5,8,222,8,8,10,8,12,8,
  	225,9,8,3,8,227,8,8,1,8,1,8,1,8,1,8,5,8,233,8,8,10,8,12,8,236,9,8,1,9,
  	1,9,1,9,1,9,1,9,1,9,5,9,244,8,9,10,9,12,9,247,9,9,3,9,249,8,9,1,9,1,9,
  	1,9,1,9,1,9,5,9,256,8,9,10,9,12,9,259,9,9,1,10,1,10,1,10,1,10,1,10,5,
  	10,266,8,10,10,10,12,10,269,9,10,3,10,271,8,10,1,10,1,10,1,10,1,10,1,
  	10,1,11,1,11,1,12,1,12,1,12,5,12,283,8,12,10,12,12,12,286,9,12,1,12,1,
  	12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,3,13,299,8,13,1,13,1,
  	13,1,13,3,13,304,8,13,1,14,1,14,1,14,5,14,309,8,14,10,14,12,14,312,9,
  	14,1,14,1,14,1,15,1,15,1,15,5,15,319,8,15,10,15,12,15,322,9,15,1,15,1,
  	15,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,
  	16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,
  	16,1,16,1,16,1,16,1,16,1,16,3,16,359,8,16,1,17,1,17,1,17,1,17,1,17,1,
  	17,1,17,1,17,1,17,3,17,370,8,17,1,18,1,18,1,18,3,18,375,8,18,1,19,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,
  	392,8,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,
  	1,20,1,20,1,20,1,20,1,20,1,20,5,20,412,8,20,10,20,12,20,415,9,20,3,20,
  	417,8,20,1,20,1,20,3,20,421,8,20,1,21,1,21,1,21,1,21,1,21,1,22,1,22,3,
  	22,430,8,22,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,
  	23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,
  	23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,3,23,465,8,23,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,3,24,476,8,24,1,25,1,25,1,25,3,25,481,8,25,
  	1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,
  	1,26,3,26,498,8,26,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,
  	1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,5,27,519,8,27,10,27,12,27,
  	522,9,27,3,27,524,8,27,1,27,1,27,1,27,1,27,1,27,1,27,3,27,532,8,27,1,
  	28,1,28,1,28,1,28,1,28,1,29,1,29,1,29,1,29,5,29,543,8,29,10,29,12,29,
  	546,9,29,1,30,1,30,1,30,1,30,5,30,552,8,30,10,30,12,30,555,9,30,1,31,
  	1,31,1,31,1,31,1,31,1,31,5,31,563,8,31,10,31,12,31,566,9,31,3,31,568,
  	8,31,1,31,3,31,571,8,31,1,31,1,31,1,31,1,31,3,31,577,8,31,1,32,1,32,1,
  	32,1,33,1,33,1,33,1,33,1,33,5,33,587,8,33,10,33,12,33,590,9,33,3,33,592,
  	8,33,1,33,3,33,595,8,33,1,33,1,33,1,34,1,34,1,34,1,34,1,34,5,34,604,8,
  	34,10,34,12,34,607,9,34,3,34,609,8,34,1,34,3,34,612,8,34,1,34,1,34,1,
  	35,1,35,1,35,1,35,1,35,1,35,5,35,622,8,35,10,35,12,35,625,9,35,1,35,1,
  	35,1,36,1,36,1,36,1,36,1,36,1,36,5,36,635,8,36,10,36,12,36,638,9,36,1,
  	36,1,36,1,37,1,37,1,37,1,37,1,37,1,37,5,37,648,8,37,10,37,12,37,651,9,
  	37,1,37,1,37,1,38,1,38,1,38,1,38,5,38,659,8,38,10,38,12,38,662,9,38,1,
  	38,1,38,1,39,1,39,1,39,1,39,5,39,670,8,39,10,39,12,39,673,9,39,1,39,1,
  	39,1,40,1,40,1,40,1,40,5,40,681,8,40,10,40,12,40,684,9,40,1,40,1,40,1,
  	41,1,41,1,41,1,41,1,41,1,41,5,41,694,8,41,10,41,12,41,697,9,41,1,41,1,
  	41,1,42,1,42,1,42,1,42,1,42,1,42,5,42,707,8,42,10,42,12,42,710,9,42,1,
  	42,1,42,1,43,1,43,1,43,1,43,1,43,1,43,5,43,720,8,43,10,43,12,43,723,9,
  	43,1,43,1,43,1,44,1,44,1,44,1,44,1,44,3,44,732,8,44,1,44,1,44,1,44,1,
  	44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,
  	44,1,44,3,44,753,8,44,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,
  	45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,
  	45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,3,45,789,8,45,1,
  	46,1,46,1,46,1,46,1,46,1,46,1,46,1,46,1,46,1,46,3,46,801,8,46,1,47,1,
  	47,1,47,1,47,1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,
  	48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,3,48,827,8,48,1,49,1,49,1,
  	49,1,49,1,49,1,49,5,49,835,8,49,10,49,12,49,838,9,49,1,49,1,49,1,50,1,
  	50,1,50,1,50,1,50,1,50,1,50,5,50,849,8,50,10,50,12,50,852,9,50,1,50,1,
  	50,1,50,3,50,857,8,50,1,51,1,51,1,51,1,51,1,51,3,51,864,8,51,1,52,1,52,
  	1,52,3,52,869,8,52,1,53,1,53,1,53,1,53,1,53,1,53,1,53,3,53,878,8,53,1,
  	54,1,54,1,54,1,54,3,54,884,8,54,1,55,1,55,1,55,1,55,1,55,1,55,1,56,1,
  	56,1,56,1,56,1,56,3,56,897,8,56,1,56,0,0,57,0,2,4,6,8,10,12,14,16,18,
  	20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,
  	66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,
  	110,112,0,1,1,0,21,22,971,0,117,1,0,0,0,2,125,1,0,0,0,4,138,1,0,0,0,6,
  	140,1,0,0,0,8,146,1,0,0,0,10,148,1,0,0,0,12,189,1,0,0,0,14,202,1,0,0,
  	0,16,215,1,0,0,0,18,237,1,0,0,0,20,260,1,0,0,0,22,277,1,0,0,0,24,279,
  	1,0,0,0,26,303,1,0,0,0,28,305,1,0,0,0,30,315,1,0,0,0,32,358,1,0,0,0,34,
  	369,1,0,0,0,36,374,1,0,0,0,38,391,1,0,0,0,40,420,1,0,0,0,42,422,1,0,0,
  	0,44,429,1,0,0,0,46,464,1,0,0,0,48,475,1,0,0,0,50,480,1,0,0,0,52,497,
  	1,0,0,0,54,531,1,0,0,0,56,533,1,0,0,0,58,544,1,0,0,0,60,553,1,0,0,0,62,
  	576,1,0,0,0,64,578,1,0,0,0,66,581,1,0,0,0,68,598,1,0,0,0,70,615,1,0,0,
  	0,72,628,1,0,0,0,74,641,1,0,0,0,76,654,1,0,0,0,78,665,1,0,0,0,80,676,
  	1,0,0,0,82,687,1,0,0,0,84,700,1,0,0,0,86,713,1,0,0,0,88,752,1,0,0,0,90,
  	788,1,0,0,0,92,800,1,0,0,0,94,802,1,0,0,0,96,826,1,0,0,0,98,828,1,0,0,
  	0,100,856,1,0,0,0,102,858,1,0,0,0,104,868,1,0,0,0,106,877,1,0,0,0,108,
  	879,1,0,0,0,110,885,1,0,0,0,112,891,1,0,0,0,114,116,3,4,2,0,115,114,1,
  	0,0,0,116,119,1,0,0,0,117,115,1,0,0,0,117,118,1,0,0,0,118,121,1,0,0,0,
  	119,117,1,0,0,0,120,122,3,2,1,0,121,120,1,0,0,0,121,122,1,0,0,0,122,123,
  	1,0,0,0,123,124,5,0,0,1,124,1,1,0,0,0,125,126,5,1,0,0,126,130,5,53,0,
  	0,127,129,3,90,45,0,128,127,1,0,0,0,129,132,1,0,0,0,130,128,1,0,0,0,130,
  	131,1,0,0,0,131,133,1,0,0,0,132,130,1,0,0,0,133,134,5,54,0,0,134,3,1,
  	0,0,0,135,139,3,6,3,0,136,139,3,8,4,0,137,139,3,10,5,0,138,135,1,0,0,
  	0,138,136,1,0,0,0,138,137,1,0,0,0,139,5,1,0,0,0,140,141,5,24,0,0,141,
  	142,5,62,0,0,142,143,3,24,12,0,143,7,1,0,0,0,144,147,3,16,8,0,145,147,
  	3,18,9,0,146,144,1,0,0,0,146,145,1,0,0,0,147,9,1,0,0,0,148,149,3,20,10,
  	0,149,153,5,53,0,0,150,152,3,96,48,0,151,150,1,0,0,0,152,155,1,0,0,0,
  	153,151,1,0,0,0,153,154,1,0,0,0,154,156,1,0,0,0,155,153,1,0,0,0,156,157,
  	5,54,0,0,157,158,5,33,0,0,158,159,5,28,0,0,159,160,5,51,0,0,160,165,3,
  	44,22,0,161,162,5,49,0,0,162,164,3,44,22,0,163,161,1,0,0,0,164,167,1,
  	0,0,0,165,163,1,0,0,0,165,166,1,0,0,0,166,168,1,0,0,0,167,165,1,0,0,0,
  	168,187,5,52,0,0,169,171,3,14,7,0,170,169,1,0,0,0,171,172,1,0,0,0,172,
  	170,1,0,0,0,172,173,1,0,0,0,173,188,1,0,0,0,174,176,3,14,7,0,175,174,
  	1,0,0,0,176,179,1,0,0,0,177,175,1,0,0,0,177,178,1,0,0,0,178,180,1,0,0,
  	0,179,177,1,0,0,0,180,184,3,12,6,0,181,183,3,14,7,0,182,181,1,0,0,0,183,
  	186,1,0,0,0,184,182,1,0,0,0,184,185,1,0,0,0,185,188,1,0,0,0,186,184,1,
  	0,0,0,187,170,1,0,0,0,187,177,1,0,0,0,188,11,1,0,0,0,189,190,5,33,0,0,
  	190,191,5,29,0,0,191,192,5,51,0,0,192,197,3,44,22,0,193,194,5,49,0,0,
  	194,196,3,44,22,0,195,193,1,0,0,0,196,199,1,0,0,0,197,195,1,0,0,0,197,
  	198,1,0,0,0,198,200,1,0,0,0,199,197,1,0,0,0,200,201,5,52,0,0,201,13,1,
  	0,0,0,202,203,5,33,0,0,203,204,5,62,0,0,204,205,5,51,0,0,205,210,3,44,
  	22,0,206,207,5,49,0,0,207,209,3,44,22,0,208,206,1,0,0,0,209,212,1,0,0,
  	0,210,208,1,0,0,0,210,211,1,0,0,0,211,213,1,0,0,0,212,210,1,0,0,0,213,
  	214,5,52,0,0,214,15,1,0,0,0,215,216,5,5,0,0,216,217,5,62,0,0,217,226,
  	5,51,0,0,218,223,3,102,51,0,219,220,5,49,0,0,220,222,3,102,51,0,221,219,
  	1,0,0,0,222,225,1,0,0,0,223,221,1,0,0,0,223,224,1,0,0,0,224,227,1,0,0,
  	0,225,223,1,0,0,0,226,218,1,0,0,0,226,227,1,0,0,0,227,228,1,0,0,0,228,
  	229,5,52,0,0,229,230,3,28,14,0,230,234,3,30,15,0,231,233,3,98,49,0,232,
  	231,1,0,0,0,233,236,1,0,0,0,234,232,1,0,0,0,234,235,1,0,0,0,235,17,1,
  	0,0,0,236,234,1,0,0,0,237,238,5,6,0,0,238,239,5,62,0,0,239,248,5,51,0,
  	0,240,245,3,108,54,0,241,242,5,49,0,0,242,244,3,108,54,0,243,241,1,0,
  	0,0,244,247,1,0,0,0,245,243,1,0,0,0,245,246,1,0,0,0,246,249,1,0,0,0,247,
  	245,1,0,0,0,248,240,1,0,0,0,248,249,1,0,0,0,249,250,1,0,0,0,250,251,5,
  	52,0,0,251,252,3,24,12,0,252,253,3,28,14,0,253,257,3,30,15,0,254,256,
  	3,100,50,0,255,254,1,0,0,0,256,259,1,0,0,0,257,255,1,0,0,0,257,258,1,
  	0,0,0,258,19,1,0,0,0,259,257,1,0,0,0,260,261,3,22,11,0,261,270,5,51,0,
  	0,262,267,3,110,55,0,263,264,5,49,0,0,264,266,3,110,55,0,265,263,1,0,
  	0,0,266,269,1,0,0,0,267,265,1,0,0,0,267,268,1,0,0,0,268,271,1,0,0,0,269,
  	267,1,0,0,0,270,262,1,0,0,0,270,271,1,0,0,0,271,272,1,0,0,0,272,273,5,
  	52,0,0,273,274,5,62,0,0,274,275,5,20,0,0,275,276,5,62,0,0,276,21,1,0,
  	0,0,277,278,7,0,0,0,278,23,1,0,0,0,279,280,5,25,0,0,280,284,5,53,0,0,
  	281,283,3,26,13,0,282,281,1,0,0,0,283,286,1,0,0,0,284,282,1,0,0,0,284,
  	285,1,0,0,0,285,287,1,0,0,0,286,284,1,0,0,0,287,288,5,54,0,0,288,25,1,
  	0,0,0,289,290,5,62,0,0,290,291,5,62,0,0,291,304,5,50,0,0,292,293,5,23,
  	0,0,293,294,3,104,52,0,294,295,3,58,29,0,295,298,5,62,0,0,296,297,5,48,
  	0,0,297,299,3,32,16,0,298,296,1,0,0,0,298,299,1,0,0,0,299,300,1,0,0,0,
  	300,301,5,50,0,0,301,304,1,0,0,0,302,304,3,88,44,0,303,289,1,0,0,0,303,
  	292,1,0,0,0,303,302,1,0,0,0,304,27,1,0,0,0,305,306,5,8,0,0,306,310,5,
  	53,0,0,307,309,3,88,44,0,308,307,1,0,0,0,309,312,1,0,0,0,310,308,1,0,
  	0,0,310,311,1,0,0,0,311,313,1,0,0,0,312,310,1,0,0,0,313,314,5,54,0,0,
  	314,29,1,0,0,0,315,316,5,9,0,0,316,320,5,53,0,0,317,319,3,88,44,0,318,
  	317,1,0,0,0,319,322,1,0,0,0,320,318,1,0,0,0,320,321,1,0,0,0,321,323,1,
  	0,0,0,322,320,1,0,0,0,323,324,5,54,0,0,324,31,1,0,0,0,325,326,3,34,17,
  	0,326,327,5,39,0,0,327,328,3,32,16,0,328,359,1,0,0,0,329,330,3,34,17,
  	0,330,331,5,40,0,0,331,332,3,32,16,0,332,359,1,0,0,0,333,334,3,34,17,
  	0,334,335,5,42,0,0,335,336,3,32,16,0,336,359,1,0,0,0,337,338,3,34,17,
  	0,338,339,5,43,0,0,339,340,3,32,16,0,340,359,1,0,0,0,341,342,3,34,17,
  	0,342,343,5,44,0,0,343,344,3,32,16,0,344,359,1,0,0,0,345,346,3,34,17,
  	0,346,347,5,41,0,0,347,348,3,32,16,0,348,359,1,0,0,0,349,350,3,34,17,
  	0,350,351,5,45,0,0,351,352,3,32,16,0,352,359,1,0,0,0,353,354,3,34,17,
  	0,354,355,5,46,0,0,355,356,3,32,16,0,356,359,1,0,0,0,357,359,3,34,17,
  	0,358,325,1,0,0,0,358,329,1,0,0,0,358,333,1,0,0,0,358,337,1,0,0,0,358,
  	341,1,0,0,0,358,345,1,0,0,0,358,349,1,0,0,0,358,353,1,0,0,0,358,357,1,
  	0,0,0,359,33,1,0,0,0,360,361,3,36,18,0,361,362,5,34,0,0,362,363,3,34,
  	17,0,363,370,1,0,0,0,364,365,3,36,18,0,365,366,5,35,0,0,366,367,3,34,
  	17,0,367,370,1,0,0,0,368,370,3,36,18,0,369,360,1,0,0,0,369,364,1,0,0,
  	0,369,368,1,0,0,0,370,35,1,0,0,0,371,372,5,35,0,0,372,375,3,38,19,0,373,
  	375,3,38,19,0,374,371,1,0,0,0,374,373,1,0,0,0,375,37,1,0,0,0,376,377,
  	3,40,20,0,377,378,5,36,0,0,378,379,3,38,19,0,379,392,1,0,0,0,380,381,
  	3,40,20,0,381,382,5,37,0,0,382,383,3,38,19,0,383,392,1,0,0,0,384,385,
  	3,40,20,0,385,386,5,38,0,0,386,387,3,38,19,0,387,392,1,0,0,0,388,389,
  	5,47,0,0,389,392,3,40,20,0,390,392,3,40,20,0,391,376,1,0,0,0,391,380,
  	1,0,0,0,391,384,1,0,0,0,391,388,1,0,0,0,391,390,1,0,0,0,392,39,1,0,0,
  	0,393,421,5,61,0,0,394,421,5,60,0,0,395,421,5,59,0,0,396,397,5,23,0,0,
  	397,398,5,58,0,0,398,399,5,62,0,0,399,421,3,58,29,0,400,401,5,62,0,0,
  	401,421,3,58,29,0,402,403,5,51,0,0,403,404,3,32,16,0,404,405,5,52,0,0,
  	405,421,1,0,0,0,406,407,5,62,0,0,407,416,5,51,0,0,408,413,3,32,16,0,409,
  	410,5,49,0,0,410,412,3,32,16,0,411,409,1,0,0,0,412,415,1,0,0,0,413,411,
  	1,0,0,0,413,414,1,0,0,0,414,417,1,0,0,0,415,413,1,0,0,0,416,408,1,0,0,
  	0,416,417,1,0,0,0,417,418,1,0,0,0,418,421,5,52,0,0,419,421,3,42,21,0,
  	420,393,1,0,0,0,420,394,1,0,0,0,420,395,1,0,0,0,420,396,1,0,0,0,420,400,
  	1,0,0,0,420,402,1,0,0,0,420,406,1,0,0,0,420,419,1,0,0,0,421,41,1,0,0,
  	0,422,423,5,51,0,0,423,424,3,104,52,0,424,425,5,52,0,0,425,426,3,32,16,
  	0,426,43,1,0,0,0,427,430,3,46,23,0,428,430,5,19,0,0,429,427,1,0,0,0,429,
  	428,1,0,0,0,430,45,1,0,0,0,431,432,3,48,24,0,432,433,5,39,0,0,433,434,
  	3,46,23,0,434,465,1,0,0,0,435,436,3,48,24,0,436,437,5,40,0,0,437,438,
  	3,46,23,0,438,465,1,0,0,0,439,440,3,48,24,0,440,441,5,42,0,0,441,442,
  	3,46,23,0,442,465,1,0,0,0,443,444,3,48,24,0,444,445,5,43,0,0,445,446,
  	3,46,23,0,446,465,1,0,0,0,447,448,3,48,24,0,448,449,5,44,0,0,449,450,
  	3,46,23,0,450,465,1,0,0,0,451,452,3,48,24,0,452,453,5,41,0,0,453,454,
  	3,46,23,0,454,465,1,0,0,0,455,456,3,48,24,0,456,457,5,45,0,0,457,458,
  	3,46,23,0,458,465,1,0,0,0,459,460,3,48,24,0,460,461,5,46,0,0,461,462,
  	3,46,23,0,462,465,1,0,0,0,463,465,3,48,24,0,464,431,1,0,0,0,464,435,1,
  	0,0,0,464,439,1,0,0,0,464,443,1,0,0,0,464,447,1,0,0,0,464,451,1,0,0,0,
  	464,455,1,0,0,0,464,459,1,0,0,0,464,463,1,0,0,0,465,47,1,0,0,0,466,467,
  	3,50,25,0,467,468,5,34,0,0,468,469,3,48,24,0,469,476,1,0,0,0,470,471,
  	3,50,25,0,471,472,5,35,0,0,472,473,3,48,24,0,473,476,1,0,0,0,474,476,
  	3,50,25,0,475,466,1,0,0,0,475,470,1,0,0,0,475,474,1,0,0,0,476,49,1,0,
  	0,0,477,478,5,35,0,0,478,481,3,52,26,0,479,481,3,52,26,0,480,477,1,0,
  	0,0,480,479,1,0,0,0,481,51,1,0,0,0,482,483,3,54,27,0,483,484,5,36,0,0,
  	484,485,3,52,26,0,485,498,1,0,0,0,486,487,3,54,27,0,487,488,5,37,0,0,
  	488,489,3,52,26,0,489,498,1,0,0,0,490,491,3,54,27,0,491,492,5,38,0,0,
  	492,493,3,52,26,0,493,498,1,0,0,0,494,495,5,47,0,0,495,498,3,54,27,0,
  	496,498,3,54,27,0,497,482,1,0,0,0,497,486,1,0,0,0,497,490,1,0,0,0,497,
  	494,1,0,0,0,497,496,1,0,0,0,498,53,1,0,0,0,499,500,5,62,0,0,500,532,3,
  	60,30,0,501,532,5,61,0,0,502,532,5,60,0,0,503,532,5,59,0,0,504,532,5,
  	18,0,0,505,506,5,23,0,0,506,507,5,58,0,0,507,508,5,62,0,0,508,532,3,60,
  	30,0,509,510,5,62,0,0,510,511,5,58,0,0,511,512,5,62,0,0,512,532,3,60,
  	30,0,513,514,5,62,0,0,514,523,5,51,0,0,515,520,3,44,22,0,516,517,5,49,
  	0,0,517,519,3,44,22,0,518,516,1,0,0,0,519,522,1,0,0,0,520,518,1,0,0,0,
  	520,521,1,0,0,0,521,524,1,0,0,0,522,520,1,0,0,0,523,515,1,0,0,0,523,524,
  	1,0,0,0,524,525,1,0,0,0,525,532,5,52,0,0,526,527,5,51,0,0,527,528,3,46,
  	23,0,528,529,5,52,0,0,529,532,1,0,0,0,530,532,3,56,28,0,531,499,1,0,0,
  	0,531,501,1,0,0,0,531,502,1,0,0,0,531,503,1,0,0,0,531,504,1,0,0,0,531,
  	505,1,0,0,0,531,509,1,0,0,0,531,513,1,0,0,0,531,526,1,0,0,0,531,530,1,
  	0,0,0,532,55,1,0,0,0,533,534,5,51,0,0,534,535,3,104,52,0,535,536,5,52,
  	0,0,536,537,3,46,23,0,537,57,1,0,0,0,538,539,5,55,0,0,539,540,3,32,16,
  	0,540,541,5,56,0,0,541,543,1,0,0,0,542,538,1,0,0,0,543,546,1,0,0,0,544,
  	542,1,0,0,0,544,545,1,0,0,0,545,59,1,0,0,0,546,544,1,0,0,0,547,548,5,
  	55,0,0,548,549,3,46,23,0,549,550,5,56,0,0,550,552,1,0,0,0,551,547,1,0,
  	0,0,552,555,1,0,0,0,553,551,1,0,0,0,553,554,1,0,0,0,554,61,1,0,0,0,555,
  	553,1,0,0,0,556,577,5,62,0,0,557,570,5,62,0,0,558,567,5,51,0,0,559,564,
  	3,32,16,0,560,561,5,49,0,0,561,563,3,32,16,0,562,560,1,0,0,0,563,566,
  	1,0,0,0,564,562,1,0,0,0,564,565,1,0,0,0,565,568,1,0,0,0,566,564,1,0,0,
  	0,567,559,1,0,0,0,567,568,1,0,0,0,568,569,1,0,0,0,569,571,5,52,0,0,570,
  	558,1,0,0,0,570,571,1,0,0,0,571,577,1,0,0,0,572,573,3,64,32,0,573,574,
  	5,58,0,0,574,575,5,62,0,0,575,577,1,0,0,0,576,556,1,0,0,0,576,557,1,0,
  	0,0,576,572,1,0,0,0,577,63,1,0,0,0,578,579,5,62,0,0,579,580,3,58,29,0,
  	580,65,1,0,0,0,581,594,5,62,0,0,582,591,5,51,0,0,583,588,3,32,16,0,584,
  	585,5,49,0,0,585,587,3,32,16,0,586,584,1,0,0,0,587,590,1,0,0,0,588,586,
  	1,0,0,0,588,589,1,0,0,0,589,592,1,0,0,0,590,588,1,0,0,0,591,583,1,0,0,
  	0,591,592,1,0,0,0,592,593,1,0,0,0,593,595,5,52,0,0,594,582,1,0,0,0,594,
  	595,1,0,0,0,595,596,1,0,0,0,596,597,3,58,29,0,597,67,1,0,0,0,598,611,
  	5,62,0,0,599,608,5,51,0,0,600,605,3,44,22,0,601,602,5,49,0,0,602,604,
  	3,44,22,0,603,601,1,0,0,0,604,607,1,0,0,0,605,603,1,0,0,0,605,606,1,0,
  	0,0,606,609,1,0,0,0,607,605,1,0,0,0,608,600,1,0,0,0,608,609,1,0,0,0,609,
  	610,1,0,0,0,610,612,5,52,0,0,611,599,1,0,0,0,611,612,1,0,0,0,612,613,
  	1,0,0,0,613,614,3,58,29,0,614,69,1,0,0,0,615,616,5,10,0,0,616,617,5,62,
  	0,0,617,618,5,11,0,0,618,619,3,66,33,0,619,623,5,53,0,0,620,622,3,88,
  	44,0,621,620,1,0,0,0,622,625,1,0,0,0,623,621,1,0,0,0,623,624,1,0,0,0,
  	624,626,1,0,0,0,625,623,1,0,0,0,626,627,5,54,0,0,627,71,1,0,0,0,628,629,
  	5,10,0,0,629,630,5,62,0,0,630,631,5,11,0,0,631,632,3,68,34,0,632,636,
  	5,53,0,0,633,635,3,96,48,0,634,633,1,0,0,0,635,638,1,0,0,0,636,634,1,
  	0,0,0,636,637,1,0,0,0,637,639,1,0,0,0,638,636,1,0,0,0,639,640,5,54,0,
  	0,640,73,1,0,0,0,641,642,5,10,0,0,642,643,5,62,0,0,643,644,5,11,0,0,644,
  	645,3,62,31,0,645,649,5,53,0,0,646,648,3,90,45,0,647,646,1,0,0,0,648,
  	651,1,0,0,0,649,647,1,0,0,0,649,650,1,0,0,0,650,652,1,0,0,0,651,649,1,
  	0,0,0,652,653,5,54,0,0,653,75,1,0,0,0,654,655,3,82,41,0,655,656,5,13,
  	0,0,656,660,5,53,0,0,657,659,3,88,44,0,658,657,1,0,0,0,659,662,1,0,0,
  	0,660,658,1,0,0,0,660,661,1,0,0,0,661,663,1,0,0,0,662,660,1,0,0,0,663,
  	664,5,54,0,0,664,77,1,0,0,0,665,666,3,84,42,0,666,667,5,13,0,0,667,671,
  	5,53,0,0,668,670,3,90,45,0,669,668,1,0,0,0,670,673,1,0,0,0,671,669,1,
  	0,0,0,671,672,1,0,0,0,672,674,1,0,0,0,673,671,1,0,0,0,674,675,5,54,0,
  	0,675,79,1,0,0,0,676,677,3,86,43,0,677,678,5,13,0,0,678,682,5,53,0,0,
  	679,681,3,96,48,0,680,679,1,0,0,0,681,684,1,0,0,0,682,680,1,0,0,0,682,
  	683,1,0,0,0,683,685,1,0,0,0,684,682,1,0,0,0,685,686,5,54,0,0,686,81,1,
  	0,0,0,687,688,5,12,0,0,688,689,5,51,0,0,689,690,3,32,16,0,690,691,5,52,
  	0,0,691,695,5,53,0,0,692,694,3,88,44,0,693,692,1,0,0,0,694,697,1,0,0,
  	0,695,693,1,0,0,0,695,696,1,0,0,0,696,698,1,0,0,0,697,695,1,0,0,0,698,
  	699,5,54,0,0,699,83,1,0,0,0,700,701,5,12,0,0,701,702,5,51,0,0,702,703,
  	3,32,16,0,703,704,5,52,0,0,704,708,5,53,0,0,705,707,3,90,45,0,706,705,
  	1,0,0,0,707,710,1,0,0,0,708,706,1,0,0,0,708,709,1,0,0,0,709,711,1,0,0,
  	0,710,708,1,0,0,0,711,712,5,54,0,0,712,85,1,0,0,0,713,714,5,12,0,0,714,
  	715,5,51,0,0,715,716,3,44,22,0,716,717,5,52,0,0,717,721,5,53,0,0,718,
  	720,3,96,48,0,719,718,1,0,0,0,720,723,1,0,0,0,721,719,1,0,0,0,721,722,
  	1,0,0,0,722,724,1,0,0,0,723,721,1,0,0,0,724,725,5,54,0,0,725,87,1,0,0,
  	0,726,727,3,104,52,0,727,728,3,58,29,0,728,731,5,62,0,0,729,730,5,48,
  	0,0,730,732,3,32,16,0,731,729,1,0,0,0,731,732,1,0,0,0,732,733,1,0,0,0,
  	733,734,5,50,0,0,734,753,1,0,0,0,735,736,5,62,0,0,736,737,3,58,29,0,737,
  	738,5,48,0,0,738,739,3,32,16,0,739,740,5,50,0,0,740,753,1,0,0,0,741,742,
  	5,23,0,0,742,743,5,58,0,0,743,744,5,62,0,0,744,745,3,58,29,0,745,746,
  	5,48,0,0,746,747,3,32,16,0,747,748,5,50,0,0,748,753,1,0,0,0,749,753,3,
  	70,35,0,750,753,3,76,38,0,751,753,3,82,41,0,752,726,1,0,0,0,752,735,1,
  	0,0,0,752,741,1,0,0,0,752,749,1,0,0,0,752,750,1,0,0,0,752,751,1,0,0,0,
  	753,89,1,0,0,0,754,755,5,62,0,0,755,756,3,58,29,0,756,757,5,62,0,0,757,
  	758,5,50,0,0,758,789,1,0,0,0,759,760,3,64,32,0,760,761,5,58,0,0,761,762,
  	5,62,0,0,762,763,5,51,0,0,763,764,3,92,46,0,764,765,5,52,0,0,765,766,
  	5,50,0,0,766,789,1,0,0,0,767,768,5,15,0,0,768,769,5,62,0,0,769,770,3,
  	58,29,0,770,771,5,14,0,0,771,772,5,62,0,0,772,773,3,58,29,0,773,774,5,
  	50,0,0,774,789,1,0,0,0,775,776,5,62,0,0,776,777,3,58,29,0,777,778,5,26,
  	0,0,778,779,5,62,0,0,779,780,3,58,29,0,780,781,5,30,0,0,781,782,5,62,
  	0,0,782,783,5,50,0,0,783,789,1,0,0,0,784,789,3,74,37,0,785,789,3,78,39,
  	0,786,789,3,84,42,0,787,789,3,88,44,0,788,754,1,0,0,0,788,759,1,0,0,0,
  	788,767,1,0,0,0,788,775,1,0,0,0,788,784,1,0,0,0,788,785,1,0,0,0,788,786,
  	1,0,0,0,788,787,1,0,0,0,789,91,1,0,0,0,790,791,3,64,32,0,791,792,5,58,
  	0,0,792,793,5,62,0,0,793,801,1,0,0,0,794,795,3,94,47,0,795,796,3,64,32,
  	0,796,797,5,58,0,0,797,798,5,62,0,0,798,801,1,0,0,0,799,801,3,32,16,0,
  	800,790,1,0,0,0,800,794,1,0,0,0,800,799,1,0,0,0,801,93,1,0,0,0,802,803,
  	5,51,0,0,803,804,5,62,0,0,804,805,5,52,0,0,805,95,1,0,0,0,806,807,3,112,
  	56,0,807,808,5,50,0,0,808,827,1,0,0,0,809,810,5,62,0,0,810,811,3,60,30,
  	0,811,812,5,48,0,0,812,813,3,44,22,0,813,814,5,50,0,0,814,827,1,0,0,0,
  	815,816,5,23,0,0,816,817,5,58,0,0,817,818,5,62,0,0,818,819,3,60,30,0,
  	819,820,5,48,0,0,820,821,3,44,22,0,821,822,5,50,0,0,822,827,1,0,0,0,823,
  	827,3,72,36,0,824,827,3,80,40,0,825,827,3,86,43,0,826,806,1,0,0,0,826,
  	809,1,0,0,0,826,815,1,0,0,0,826,823,1,0,0,0,826,824,1,0,0,0,826,825,1,
  	0,0,0,827,97,1,0,0,0,828,829,5,33,0,0,829,830,5,62,0,0,830,831,5,51,0,
  	0,831,836,3,32,16,0,832,833,5,49,0,0,833,835,3,32,16,0,834,832,1,0,0,
  	0,835,838,1,0,0,0,836,834,1,0,0,0,836,837,1,0,0,0,837,839,1,0,0,0,838,
  	836,1,0,0,0,839,840,5,52,0,0,840,99,1,0,0,0,841,842,5,33,0,0,842,843,
  	5,31,0,0,843,844,5,62,0,0,844,845,5,51,0,0,845,850,3,32,16,0,846,847,
  	5,49,0,0,847,849,3,32,16,0,848,846,1,0,0,0,849,852,1,0,0,0,850,848,1,
  	0,0,0,850,851,1,0,0,0,851,853,1,0,0,0,852,850,1,0,0,0,853,854,5,52,0,
  	0,854,857,1,0,0,0,855,857,3,98,49,0,856,841,1,0,0,0,856,855,1,0,0,0,857,
  	101,1,0,0,0,858,859,3,104,52,0,859,860,3,58,29,0,860,863,5,62,0,0,861,
  	862,5,48,0,0,862,864,3,32,16,0,863,861,1,0,0,0,863,864,1,0,0,0,864,103,
  	1,0,0,0,865,869,5,2,0,0,866,869,5,3,0,0,867,869,5,4,0,0,868,865,1,0,0,
  	0,868,866,1,0,0,0,868,867,1,0,0,0,869,105,1,0,0,0,870,871,3,104,52,0,
  	871,872,3,58,29,0,872,878,1,0,0,0,873,874,5,32,0,0,874,875,3,104,52,0,
  	875,876,3,58,29,0,876,878,1,0,0,0,877,870,1,0,0,0,877,873,1,0,0,0,878,
  	107,1,0,0,0,879,880,3,106,53,0,880,883,5,62,0,0,881,882,5,48,0,0,882,
  	884,3,32,16,0,883,881,1,0,0,0,883,884,1,0,0,0,884,109,1,0,0,0,885,886,
  	3,104,52,0,886,887,3,60,30,0,887,888,5,62,0,0,888,889,5,48,0,0,889,890,
  	3,44,22,0,890,111,1,0,0,0,891,892,3,104,52,0,892,893,3,60,30,0,893,896,
  	5,62,0,0,894,895,5,48,0,0,895,897,3,44,22,0,896,894,1,0,0,0,896,897,1,
  	0,0,0,897,113,1,0,0,0,75,117,121,130,138,146,153,165,172,177,184,187,
  	197,210,223,226,234,245,248,257,267,270,284,298,303,310,320,358,369,374,
  	391,413,416,420,429,464,475,480,497,520,523,531,544,553,564,567,570,576,
  	588,591,594,605,608,611,623,636,649,660,671,682,695,708,721,731,752,788,
  	800,826,836,850,856,863,868,877,883,896
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
      ((1ULL << _la) & 23068768) != 0)) {
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
    setState(138);
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
    setState(140);
    match(ChipsParser::OBJECT_KW);
    setState(141);
    match(ChipsParser::IDENTIFIER);
    setState(142);
    with_section();
   
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
  enterRule(_localctx, 8, ChipsParser::RuleFunction_def);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(146);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ChipsParser::LOGICAL_KW: {
        _localctx = _tracker.createInstance<ChipsParser::LogicalDefintionContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(144);
        l_function_def();
        break;
      }

      case ChipsParser::PHYSICAL_KW: {
        _localctx = _tracker.createInstance<ChipsParser::PhysicalDefinitionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(145);
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

ChipsParser::C_default_outputContext* ChipsParser::Collective_op_defContext::c_default_output() {
  return getRuleContext<ChipsParser::C_default_outputContext>(0);
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

std::vector<ChipsParser::C_channeled_outputContext *> ChipsParser::Collective_op_defContext::c_channeled_output() {
  return getRuleContexts<ChipsParser::C_channeled_outputContext>();
}

ChipsParser::C_channeled_outputContext* ChipsParser::Collective_op_defContext::c_channeled_output(size_t i) {
  return getRuleContext<ChipsParser::C_channeled_outputContext>(i);
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
  enterRule(_localctx, 10, ChipsParser::RuleCollective_op_def);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(148);
    c_signature();
    setState(149);
    match(ChipsParser::L_CURL);
    setState(153);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(150);
      c_statement();
      setState(155);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(156);
    match(ChipsParser::R_CURL);
    setState(157);
    match(ChipsParser::ARROW);
    setState(158);
    match(ChipsParser::TARGET_KW);
    setState(159);
    match(ChipsParser::L_PARENTH);
    setState(160);
    c_expr();
    setState(165);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ChipsParser::COMMA) {
      setState(161);
      match(ChipsParser::COMMA);
      setState(162);
      c_expr();
      setState(167);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(168);
    match(ChipsParser::R_PARENTH);
    setState(187);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      setState(170); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(169);
        c_channeled_output();
        setState(172); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == ChipsParser::ARROW);
      break;
    }

    case 2: {
      setState(177);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(174);
          c_channeled_output(); 
        }
        setState(179);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
      }
      setState(180);
      c_default_output();
      setState(184);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ChipsParser::ARROW) {
        setState(181);
        c_channeled_output();
        setState(186);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
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

//----------------- C_default_outputContext ------------------------------------------------------------------

ChipsParser::C_default_outputContext::C_default_outputContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::C_default_outputContext::ARROW() {
  return getToken(ChipsParser::ARROW, 0);
}

tree::TerminalNode* ChipsParser::C_default_outputContext::DEFAULT_KW() {
  return getToken(ChipsParser::DEFAULT_KW, 0);
}

tree::TerminalNode* ChipsParser::C_default_outputContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

std::vector<ChipsParser::C_exprContext *> ChipsParser::C_default_outputContext::c_expr() {
  return getRuleContexts<ChipsParser::C_exprContext>();
}

ChipsParser::C_exprContext* ChipsParser::C_default_outputContext::c_expr(size_t i) {
  return getRuleContext<ChipsParser::C_exprContext>(i);
}

tree::TerminalNode* ChipsParser::C_default_outputContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

std::vector<tree::TerminalNode *> ChipsParser::C_default_outputContext::COMMA() {
  return getTokens(ChipsParser::COMMA);
}

tree::TerminalNode* ChipsParser::C_default_outputContext::COMMA(size_t i) {
  return getToken(ChipsParser::COMMA, i);
}


size_t ChipsParser::C_default_outputContext::getRuleIndex() const {
  return ChipsParser::RuleC_default_output;
}


std::any ChipsParser::C_default_outputContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitC_default_output(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::C_default_outputContext* ChipsParser::c_default_output() {
  C_default_outputContext *_localctx = _tracker.createInstance<C_default_outputContext>(_ctx, getState());
  enterRule(_localctx, 12, ChipsParser::RuleC_default_output);
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
    setState(189);
    match(ChipsParser::ARROW);
    setState(190);
    match(ChipsParser::DEFAULT_KW);
    setState(191);
    match(ChipsParser::L_PARENTH);
    setState(192);
    c_expr();
    setState(197);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ChipsParser::COMMA) {
      setState(193);
      match(ChipsParser::COMMA);
      setState(194);
      c_expr();
      setState(199);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(200);
    match(ChipsParser::R_PARENTH);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- C_channeled_outputContext ------------------------------------------------------------------

ChipsParser::C_channeled_outputContext::C_channeled_outputContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::C_channeled_outputContext::ARROW() {
  return getToken(ChipsParser::ARROW, 0);
}

tree::TerminalNode* ChipsParser::C_channeled_outputContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

tree::TerminalNode* ChipsParser::C_channeled_outputContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

std::vector<ChipsParser::C_exprContext *> ChipsParser::C_channeled_outputContext::c_expr() {
  return getRuleContexts<ChipsParser::C_exprContext>();
}

ChipsParser::C_exprContext* ChipsParser::C_channeled_outputContext::c_expr(size_t i) {
  return getRuleContext<ChipsParser::C_exprContext>(i);
}

tree::TerminalNode* ChipsParser::C_channeled_outputContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

std::vector<tree::TerminalNode *> ChipsParser::C_channeled_outputContext::COMMA() {
  return getTokens(ChipsParser::COMMA);
}

tree::TerminalNode* ChipsParser::C_channeled_outputContext::COMMA(size_t i) {
  return getToken(ChipsParser::COMMA, i);
}


size_t ChipsParser::C_channeled_outputContext::getRuleIndex() const {
  return ChipsParser::RuleC_channeled_output;
}


std::any ChipsParser::C_channeled_outputContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitC_channeled_output(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::C_channeled_outputContext* ChipsParser::c_channeled_output() {
  C_channeled_outputContext *_localctx = _tracker.createInstance<C_channeled_outputContext>(_ctx, getState());
  enterRule(_localctx, 14, ChipsParser::RuleC_channeled_output);
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
    setState(202);
    match(ChipsParser::ARROW);
    setState(203);
    match(ChipsParser::IDENTIFIER);
    setState(204);
    match(ChipsParser::L_PARENTH);
    setState(205);
    c_expr();
    setState(210);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ChipsParser::COMMA) {
      setState(206);
      match(ChipsParser::COMMA);
      setState(207);
      c_expr();
      setState(212);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(213);
    match(ChipsParser::R_PARENTH);
   
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
  enterRule(_localctx, 16, ChipsParser::RuleL_function_def);
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
    setState(215);
    match(ChipsParser::LOGICAL_KW);
    setState(216);
    match(ChipsParser::IDENTIFIER);
    setState(217);
    match(ChipsParser::L_PARENTH);
    setState(226);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 28) != 0)) {
      setState(218);
      df_parameter_decl();
      setState(223);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ChipsParser::COMMA) {
        setState(219);
        match(ChipsParser::COMMA);
        setState(220);
        df_parameter_decl();
        setState(225);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(228);
    match(ChipsParser::R_PARENTH);
    setState(229);
    init_section();
    setState(230);
    then_section();
    setState(234);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ChipsParser::ARROW) {
      setState(231);
      named_output();
      setState(236);
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
  enterRule(_localctx, 18, ChipsParser::RuleP_function_def);
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
    setState(237);
    match(ChipsParser::PHYSICAL_KW);
    setState(238);
    match(ChipsParser::IDENTIFIER);
    setState(239);
    match(ChipsParser::L_PARENTH);
    setState(248);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4294967324) != 0)) {
      setState(240);
      pdf_parameter_decl();
      setState(245);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ChipsParser::COMMA) {
        setState(241);
        match(ChipsParser::COMMA);
        setState(242);
        pdf_parameter_decl();
        setState(247);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(250);
    match(ChipsParser::R_PARENTH);
    setState(251);
    with_section();
    setState(252);
    init_section();
    setState(253);
    then_section();
    setState(257);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ChipsParser::ARROW) {
      setState(254);
      p_named_output();
      setState(259);
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
  enterRule(_localctx, 20, ChipsParser::RuleC_signature);
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
    setState(260);
    c_keywords();
    setState(261);
    match(ChipsParser::L_PARENTH);
    setState(270);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 28) != 0)) {
      setState(262);
      cdf_defaulted_decl();
      setState(267);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ChipsParser::COMMA) {
        setState(263);
        match(ChipsParser::COMMA);
        setState(264);
        cdf_defaulted_decl();
        setState(269);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(272);
    match(ChipsParser::R_PARENTH);
    setState(273);
    match(ChipsParser::IDENTIFIER);
    setState(274);
    match(ChipsParser::AMONG_KW);
    setState(275);
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
  enterRule(_localctx, 22, ChipsParser::RuleC_keywords);
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
    setState(277);
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
  enterRule(_localctx, 24, ChipsParser::RuleWith_section);
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
    setState(279);
    match(ChipsParser::WITH_KW);
    setState(280);
    match(ChipsParser::L_CURL);
    setState(284);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(281);
      with_statement();
      setState(286);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(287);
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
  enterRule(_localctx, 26, ChipsParser::RuleWith_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(303);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::ChannelDeclarationContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(289);
      match(ChipsParser::IDENTIFIER);
      setState(290);
      match(ChipsParser::IDENTIFIER);
      setState(291);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::ContextualDeclarationContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(292);
      match(ChipsParser::CTX_KW);
      setState(293);
      df_type();
      setState(294);
      suffixes();
      setState(295);
      match(ChipsParser::IDENTIFIER);
      setState(298);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ChipsParser::ASSIGN) {
        setState(296);
        match(ChipsParser::ASSIGN);
        setState(297);
        expr();
      }
      setState(300);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::WithRegularStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(302);
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
  enterRule(_localctx, 28, ChipsParser::RuleInit_section);
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
    setState(305);
    match(ChipsParser::INIT_KW);
    setState(306);
    match(ChipsParser::L_CURL);
    setState(310);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(307);
      statement();
      setState(312);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(313);
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
  enterRule(_localctx, 30, ChipsParser::RuleThen_section);
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
    setState(315);
    match(ChipsParser::THEN_KW);
    setState(316);
    match(ChipsParser::L_CURL);
    setState(320);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(317);
      statement();
      setState(322);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(323);
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
  enterRule(_localctx, 32, ChipsParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(358);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::LTContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(325);
      expr0();
      setState(326);
      match(ChipsParser::LT);
      setState(327);
      expr();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::GTContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(329);
      expr0();
      setState(330);
      match(ChipsParser::GT);
      setState(331);
      expr();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::LEQContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(333);
      expr0();
      setState(334);
      match(ChipsParser::LEQ);
      setState(335);
      expr();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::GEQContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(337);
      expr0();
      setState(338);
      match(ChipsParser::GEQ);
      setState(339);
      expr();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::NEQContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(341);
      expr0();
      setState(342);
      match(ChipsParser::NEQ);
      setState(343);
      expr();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ChipsParser::EQContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(345);
      expr0();
      setState(346);
      match(ChipsParser::EQ);
      setState(347);
      expr();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ChipsParser::ANDContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(349);
      expr0();
      setState(350);
      match(ChipsParser::AND);
      setState(351);
      expr();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<ChipsParser::ORContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(353);
      expr0();
      setState(354);
      match(ChipsParser::OR);
      setState(355);
      expr();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<ChipsParser::PassExpr0Context>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(357);
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
  enterRule(_localctx, 34, ChipsParser::RuleExpr0);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(369);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::PLUSContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(360);
      expr01();
      setState(361);
      match(ChipsParser::PLUS);
      setState(362);
      expr0();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::SUBContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(364);
      expr01();
      setState(365);
      match(ChipsParser::MINUS);
      setState(366);
      expr0();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::PassExpr01Context>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(368);
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
  enterRule(_localctx, 36, ChipsParser::RuleExpr01);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(374);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ChipsParser::MINUS: {
        _localctx = _tracker.createInstance<ChipsParser::NegateContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(371);
        match(ChipsParser::MINUS);
        setState(372);
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
        setState(373);
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
  enterRule(_localctx, 38, ChipsParser::RuleExpr1);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(391);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::MULTContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(376);
      expr2();
      setState(377);
      match(ChipsParser::TIMES);
      setState(378);
      expr1();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::DIVContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(380);
      expr2();
      setState(381);
      match(ChipsParser::DIV);
      setState(382);
      expr1();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::MODContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(384);
      expr2();
      setState(385);
      match(ChipsParser::MOD);
      setState(386);
      expr1();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::NOTContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(388);
      match(ChipsParser::NOT);
      setState(389);
      expr2();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::PassExpr2Context>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(390);
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
  enterRule(_localctx, 40, ChipsParser::RuleExpr2);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(420);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::IntLiteralContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(393);
      match(ChipsParser::INT);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::FloatLiteralContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(394);
      match(ChipsParser::FLOAT);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::BoolLiteralContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(395);
      match(ChipsParser::BOOL);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::VarContextContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(396);
      match(ChipsParser::CTX_KW);
      setState(397);
      match(ChipsParser::PERIOD);
      setState(398);
      match(ChipsParser::IDENTIFIER);
      setState(399);
      suffixes();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::VarContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(400);
      match(ChipsParser::IDENTIFIER);
      setState(401);
      suffixes();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ChipsParser::ParensContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(402);
      match(ChipsParser::L_PARENTH);
      setState(403);
      expr();
      setState(404);
      match(ChipsParser::R_PARENTH);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ChipsParser::FunctionContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(406);
      match(ChipsParser::IDENTIFIER);
      setState(407);
      match(ChipsParser::L_PARENTH);
      setState(416);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 8649303856221519872) != 0)) {
        setState(408);
        expr();
        setState(413);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ChipsParser::COMMA) {
          setState(409);
          match(ChipsParser::COMMA);
          setState(410);
          expr();
          setState(415);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(418);
      match(ChipsParser::R_PARENTH);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<ChipsParser::CastAsContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(419);
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
  enterRule(_localctx, 42, ChipsParser::RuleCast);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(422);
    match(ChipsParser::L_PARENTH);
    setState(423);
    df_type();
    setState(424);
    match(ChipsParser::R_PARENTH);
    setState(425);
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
  enterRule(_localctx, 44, ChipsParser::RuleC_expr);

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
        setState(427);
        c_stopless_expr();
        break;
      }

      case ChipsParser::STOP_KW: {
        _localctx = _tracker.createInstance<ChipsParser::StopContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(428);
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
  enterRule(_localctx, 46, ChipsParser::RuleC_stopless_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(464);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::CLTContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(431);
      c_stopless_expr0();
      setState(432);
      match(ChipsParser::LT);
      setState(433);
      c_stopless_expr();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::CGTContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(435);
      c_stopless_expr0();
      setState(436);
      match(ChipsParser::GT);
      setState(437);
      c_stopless_expr();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::CLEQContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(439);
      c_stopless_expr0();
      setState(440);
      match(ChipsParser::LEQ);
      setState(441);
      c_stopless_expr();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::CGEQContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(443);
      c_stopless_expr0();
      setState(444);
      match(ChipsParser::GEQ);
      setState(445);
      c_stopless_expr();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::CNEQContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(447);
      c_stopless_expr0();
      setState(448);
      match(ChipsParser::NEQ);
      setState(449);
      c_stopless_expr();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ChipsParser::CEQContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(451);
      c_stopless_expr0();
      setState(452);
      match(ChipsParser::EQ);
      setState(453);
      c_stopless_expr();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ChipsParser::CANDContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(455);
      c_stopless_expr0();
      setState(456);
      match(ChipsParser::AND);
      setState(457);
      c_stopless_expr();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<ChipsParser::CORContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(459);
      c_stopless_expr0();
      setState(460);
      match(ChipsParser::OR);
      setState(461);
      c_stopless_expr();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<ChipsParser::PassCExpr0Context>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(463);
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
  enterRule(_localctx, 48, ChipsParser::RuleC_stopless_expr0);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(475);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::CPLUSContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(466);
      c_stopless_expr01();
      setState(467);
      match(ChipsParser::PLUS);
      setState(468);
      c_stopless_expr0();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::CSUBContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(470);
      c_stopless_expr01();
      setState(471);
      match(ChipsParser::MINUS);
      setState(472);
      c_stopless_expr0();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::PassCExpr01Context>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(474);
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
  enterRule(_localctx, 50, ChipsParser::RuleC_stopless_expr01);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(480);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ChipsParser::MINUS: {
        _localctx = _tracker.createInstance<ChipsParser::CNegateContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(477);
        match(ChipsParser::MINUS);
        setState(478);
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
        setState(479);
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
  enterRule(_localctx, 52, ChipsParser::RuleC_stopless_expr1);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(497);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::CMULTContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(482);
      c_stopless_expr2();
      setState(483);
      match(ChipsParser::TIMES);
      setState(484);
      c_stopless_expr1();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::CDIVContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(486);
      c_stopless_expr2();
      setState(487);
      match(ChipsParser::DIV);
      setState(488);
      c_stopless_expr1();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::CMODContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(490);
      c_stopless_expr2();
      setState(491);
      match(ChipsParser::MOD);
      setState(492);
      c_stopless_expr1();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::CNOTContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(494);
      match(ChipsParser::NOT);
      setState(495);
      c_stopless_expr2();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::PassCExpr2Context>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(496);
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
  enterRule(_localctx, 54, ChipsParser::RuleC_stopless_expr2);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(531);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::CVariableExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(499);
      match(ChipsParser::IDENTIFIER);
      setState(500);
      c_suffixes();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::CINTContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(501);
      match(ChipsParser::INT);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::CFLOATContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(502);
      match(ChipsParser::FLOAT);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::CBOOLContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(503);
      match(ChipsParser::BOOL);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::INPUTContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(504);
      match(ChipsParser::INPUT_KW);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ChipsParser::CtxVariableExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(505);
      match(ChipsParser::CTX_KW);
      setState(506);
      match(ChipsParser::PERIOD);
      setState(507);
      match(ChipsParser::IDENTIFIER);
      setState(508);
      c_suffixes();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ChipsParser::ChanneledAccuExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(509);
      match(ChipsParser::IDENTIFIER);
      setState(510);
      match(ChipsParser::PERIOD);
      setState(511);
      match(ChipsParser::IDENTIFIER);
      setState(512);
      c_suffixes();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<ChipsParser::FunctionCallContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(513);
      match(ChipsParser::IDENTIFIER);
      setState(514);
      match(ChipsParser::L_PARENTH);
      setState(523);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 8649303856222306304) != 0)) {
        setState(515);
        c_expr();
        setState(520);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ChipsParser::COMMA) {
          setState(516);
          match(ChipsParser::COMMA);
          setState(517);
          c_expr();
          setState(522);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(525);
      match(ChipsParser::R_PARENTH);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<ChipsParser::CParenthesisContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(526);
      match(ChipsParser::L_PARENTH);
      setState(527);
      c_stopless_expr();
      setState(528);
      match(ChipsParser::R_PARENTH);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<ChipsParser::CCastAsContext>(_localctx);
      enterOuterAlt(_localctx, 10);
      setState(530);
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
  enterRule(_localctx, 56, ChipsParser::RuleC_cast);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(533);
    match(ChipsParser::L_PARENTH);
    setState(534);
    df_type();
    setState(535);
    match(ChipsParser::R_PARENTH);
    setState(536);
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
  enterRule(_localctx, 58, ChipsParser::RuleSuffixes);
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
    setState(544);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ChipsParser::L_SQUA) {
      setState(538);
      match(ChipsParser::L_SQUA);
      setState(539);
      expr();
      setState(540);
      match(ChipsParser::R_SQUA);
      setState(546);
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
  enterRule(_localctx, 60, ChipsParser::RuleC_suffixes);
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
      c_stopless_expr();
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
  enterRule(_localctx, 62, ChipsParser::RuleS_suffixable_expr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(576);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::SSuffixableVariableExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(556);
      match(ChipsParser::IDENTIFIER);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::SSuffixableFunctionCallExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(557);
      match(ChipsParser::IDENTIFIER);
      setState(570);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ChipsParser::L_PARENTH) {
        setState(558);
        match(ChipsParser::L_PARENTH);
        setState(567);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 8649303856221519872) != 0)) {
          setState(559);
          expr();
          setState(564);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == ChipsParser::COMMA) {
            setState(560);
            match(ChipsParser::COMMA);
            setState(561);
            expr();
            setState(566);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(569);
        match(ChipsParser::R_PARENTH);
      }
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::SSuffixableBlockOutputExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(572);
      block();
      setState(573);
      match(ChipsParser::PERIOD);
      setState(574);
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
  enterRule(_localctx, 64, ChipsParser::RuleBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(578);
    match(ChipsParser::IDENTIFIER);
    setState(579);
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
  enterRule(_localctx, 66, ChipsParser::RuleLoop_in);
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
    setState(581);
    match(ChipsParser::IDENTIFIER);
    setState(594);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ChipsParser::L_PARENTH) {
      setState(582);
      match(ChipsParser::L_PARENTH);
      setState(591);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 8649303856221519872) != 0)) {
        setState(583);
        expr();
        setState(588);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ChipsParser::COMMA) {
          setState(584);
          match(ChipsParser::COMMA);
          setState(585);
          expr();
          setState(590);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(593);
      match(ChipsParser::R_PARENTH);
    }
    setState(596);
    suffixes();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- C_loop_inContext ------------------------------------------------------------------

ChipsParser::C_loop_inContext::C_loop_inContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ChipsParser::C_loop_inContext::IDENTIFIER() {
  return getToken(ChipsParser::IDENTIFIER, 0);
}

ChipsParser::SuffixesContext* ChipsParser::C_loop_inContext::suffixes() {
  return getRuleContext<ChipsParser::SuffixesContext>(0);
}

tree::TerminalNode* ChipsParser::C_loop_inContext::L_PARENTH() {
  return getToken(ChipsParser::L_PARENTH, 0);
}

tree::TerminalNode* ChipsParser::C_loop_inContext::R_PARENTH() {
  return getToken(ChipsParser::R_PARENTH, 0);
}

std::vector<ChipsParser::C_exprContext *> ChipsParser::C_loop_inContext::c_expr() {
  return getRuleContexts<ChipsParser::C_exprContext>();
}

ChipsParser::C_exprContext* ChipsParser::C_loop_inContext::c_expr(size_t i) {
  return getRuleContext<ChipsParser::C_exprContext>(i);
}

std::vector<tree::TerminalNode *> ChipsParser::C_loop_inContext::COMMA() {
  return getTokens(ChipsParser::COMMA);
}

tree::TerminalNode* ChipsParser::C_loop_inContext::COMMA(size_t i) {
  return getToken(ChipsParser::COMMA, i);
}


size_t ChipsParser::C_loop_inContext::getRuleIndex() const {
  return ChipsParser::RuleC_loop_in;
}


std::any ChipsParser::C_loop_inContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ChipsVisitor*>(visitor))
    return parserVisitor->visitC_loop_in(this);
  else
    return visitor->visitChildren(this);
}

ChipsParser::C_loop_inContext* ChipsParser::c_loop_in() {
  C_loop_inContext *_localctx = _tracker.createInstance<C_loop_inContext>(_ctx, getState());
  enterRule(_localctx, 68, ChipsParser::RuleC_loop_in);
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
    setState(598);
    match(ChipsParser::IDENTIFIER);
    setState(611);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ChipsParser::L_PARENTH) {
      setState(599);
      match(ChipsParser::L_PARENTH);
      setState(608);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 8649303856222306304) != 0)) {
        setState(600);
        c_expr();
        setState(605);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ChipsParser::COMMA) {
          setState(601);
          match(ChipsParser::COMMA);
          setState(602);
          c_expr();
          setState(607);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(610);
      match(ChipsParser::R_PARENTH);
    }
    setState(613);
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
    setState(615);
    match(ChipsParser::FOREACH_KW);
    setState(616);
    match(ChipsParser::IDENTIFIER);
    setState(617);
    match(ChipsParser::IN_KW);
    setState(618);
    loop_in();
    setState(619);
    match(ChipsParser::L_CURL);
    setState(623);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(620);
      statement();
      setState(625);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(626);
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

ChipsParser::C_loop_inContext* ChipsParser::C_loop_statementContext::c_loop_in() {
  return getRuleContext<ChipsParser::C_loop_inContext>(0);
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
    setState(628);
    match(ChipsParser::FOREACH_KW);
    setState(629);
    match(ChipsParser::IDENTIFIER);
    setState(630);
    match(ChipsParser::IN_KW);
    setState(631);
    c_loop_in();
    setState(632);
    match(ChipsParser::L_CURL);
    setState(636);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(633);
      c_statement();
      setState(638);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(639);
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
    setState(641);
    match(ChipsParser::FOREACH_KW);
    setState(642);
    match(ChipsParser::IDENTIFIER);
    setState(643);
    match(ChipsParser::IN_KW);
    setState(644);
    s_suffixable_expr();
    setState(645);
    match(ChipsParser::L_CURL);
    setState(649);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435814428) != 0)) {
      setState(646);
      s_statement();
      setState(651);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(652);
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
    setState(654);
    if_statement();
    setState(655);
    match(ChipsParser::ELSE_KW);
    setState(656);
    match(ChipsParser::L_CURL);
    setState(660);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(657);
      statement();
      setState(662);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(663);
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
    setState(665);
    s_if_statement();
    setState(666);
    match(ChipsParser::ELSE_KW);
    setState(667);
    match(ChipsParser::L_CURL);
    setState(671);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435814428) != 0)) {
      setState(668);
      s_statement();
      setState(673);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(674);
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
    setState(676);
    c_if_statement();
    setState(677);
    match(ChipsParser::ELSE_KW);
    setState(678);
    match(ChipsParser::L_CURL);
    setState(682);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(679);
      c_statement();
      setState(684);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(685);
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
    setState(687);
    match(ChipsParser::IF_KW);
    setState(688);
    match(ChipsParser::L_PARENTH);
    setState(689);
    expr();
    setState(690);
    match(ChipsParser::R_PARENTH);
    setState(691);
    match(ChipsParser::L_CURL);
    setState(695);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(692);
      statement();
      setState(697);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(698);
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
    setState(700);
    match(ChipsParser::IF_KW);
    setState(701);
    match(ChipsParser::L_PARENTH);
    setState(702);
    expr();
    setState(703);
    match(ChipsParser::R_PARENTH);
    setState(704);
    match(ChipsParser::L_CURL);
    setState(708);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435814428) != 0)) {
      setState(705);
      s_statement();
      setState(710);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(711);
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
    setState(713);
    match(ChipsParser::IF_KW);
    setState(714);
    match(ChipsParser::L_PARENTH);
    setState(715);
    c_expr();
    setState(716);
    match(ChipsParser::R_PARENTH);
    setState(717);
    match(ChipsParser::L_CURL);
    setState(721);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4611686018435781660) != 0)) {
      setState(718);
      c_statement();
      setState(723);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(724);
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
    setState(752);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::StatementDeclarationContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(726);
      df_type();
      setState(727);
      suffixes();
      setState(728);
      match(ChipsParser::IDENTIFIER);
      setState(731);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ChipsParser::ASSIGN) {
        setState(729);
        match(ChipsParser::ASSIGN);
        setState(730);
        expr();
      }
      setState(733);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::StatementAssignmentContext>(_localctx);
      enterOuterAlt(_localctx, 2);
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

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::StatementContextualAssignmentContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(741);
      match(ChipsParser::CTX_KW);
      setState(742);
      match(ChipsParser::PERIOD);
      setState(743);
      match(ChipsParser::IDENTIFIER);
      setState(744);
      suffixes();
      setState(745);
      match(ChipsParser::ASSIGN);
      setState(746);
      expr();
      setState(747);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::StatementLoopContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(749);
      loop_statement();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::StatementIfElseContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(750);
      if_else_statement();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ChipsParser::StatementIfContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(751);
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
    setState(788);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 64, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::ObjectDeclarationContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(754);
      match(ChipsParser::IDENTIFIER);
      setState(755);
      suffixes();
      setState(756);
      match(ChipsParser::IDENTIFIER);
      setState(757);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::FeedingStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(759);
      block();
      setState(760);
      match(ChipsParser::PERIOD);
      setState(761);
      match(ChipsParser::IDENTIFIER);
      setState(762);
      match(ChipsParser::L_PARENTH);
      setState(763);
      s_expr();
      setState(764);
      match(ChipsParser::R_PARENTH);
      setState(765);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::LinkingStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(767);
      match(ChipsParser::LINK_KW);
      setState(768);
      match(ChipsParser::IDENTIFIER);
      setState(769);
      suffixes();
      setState(770);
      match(ChipsParser::TO_KW);
      setState(771);
      match(ChipsParser::IDENTIFIER);
      setState(772);
      suffixes();
      setState(773);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::ImplementationStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(775);
      match(ChipsParser::IDENTIFIER);
      setState(776);
      suffixes();
      setState(777);
      match(ChipsParser::IMPLEMENTATION_KW);
      setState(778);
      match(ChipsParser::IDENTIFIER);
      setState(779);
      suffixes();
      setState(780);
      match(ChipsParser::USING_KW);
      setState(781);
      match(ChipsParser::IDENTIFIER);
      setState(782);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::SLoopStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(784);
      s_loop_statement();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ChipsParser::SIfElseStatementContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(785);
      s_if_else_statement();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ChipsParser::SIfStatementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(786);
      s_if_statement();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<ChipsParser::RegularStatementContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(787);
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
    setState(800);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::SBlockOutputExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(790);
      block();
      setState(791);
      match(ChipsParser::PERIOD);
      setState(792);
      match(ChipsParser::IDENTIFIER);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::SCollectiveCastExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(794);
      collective_operation();
      setState(795);
      block();
      setState(796);
      match(ChipsParser::PERIOD);
      setState(797);
      match(ChipsParser::IDENTIFIER);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::SRegularExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(799);
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
    setState(802);
    match(ChipsParser::L_PARENTH);
    setState(803);
    match(ChipsParser::IDENTIFIER);
    setState(804);
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
    setState(826);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::CollectiveVariableDeclarationContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(806);
      cdf_full_declaration();
      setState(807);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::CollectiveAssignmentContext>(_localctx);
      enterOuterAlt(_localctx, 2);
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

    case 3: {
      _localctx = _tracker.createInstance<ChipsParser::ContextualAssignmentContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(815);
      match(ChipsParser::CTX_KW);
      setState(816);
      match(ChipsParser::PERIOD);
      setState(817);
      match(ChipsParser::IDENTIFIER);
      setState(818);
      c_suffixes();
      setState(819);
      match(ChipsParser::ASSIGN);
      setState(820);
      c_expr();
      setState(821);
      match(ChipsParser::SEMICOL);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ChipsParser::CollectiveLoopStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(823);
      c_loop_statement();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ChipsParser::CollectiveIfElseStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(824);
      c_if_else_statement();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ChipsParser::CollectiveIfStatementContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(825);
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
    setState(828);
    match(ChipsParser::ARROW);
    setState(829);
    match(ChipsParser::IDENTIFIER);
    setState(830);
    match(ChipsParser::L_PARENTH);
    setState(831);
    expr();
    setState(836);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ChipsParser::COMMA) {
      setState(832);
      match(ChipsParser::COMMA);
      setState(833);
      expr();
      setState(838);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(839);
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
    setState(856);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ChipsParser::ActuatorOutputContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(841);
      match(ChipsParser::ARROW);
      setState(842);
      match(ChipsParser::ACTUATOR_KW);
      setState(843);
      match(ChipsParser::IDENTIFIER);
      setState(844);
      match(ChipsParser::L_PARENTH);
      setState(845);
      expr();
      setState(850);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ChipsParser::COMMA) {
        setState(846);
        match(ChipsParser::COMMA);
        setState(847);
        expr();
        setState(852);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(853);
      match(ChipsParser::R_PARENTH);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ChipsParser::FunctionOutputContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(855);
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
    setState(858);
    df_type();
    setState(859);
    suffixes();
    setState(860);
    match(ChipsParser::IDENTIFIER);
    setState(863);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ChipsParser::ASSIGN) {
      setState(861);
      match(ChipsParser::ASSIGN);
      setState(862);
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
    setState(868);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ChipsParser::INT_KW: {
        _localctx = _tracker.createInstance<ChipsParser::IntTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(865);
        match(ChipsParser::INT_KW);
        break;
      }

      case ChipsParser::FLOAT_KW: {
        _localctx = _tracker.createInstance<ChipsParser::FloatTypeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(866);
        match(ChipsParser::FLOAT_KW);
        break;
      }

      case ChipsParser::BOOL_KW: {
        _localctx = _tracker.createInstance<ChipsParser::BoolTypeContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(867);
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
    setState(877);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ChipsParser::INT_KW:
      case ChipsParser::FLOAT_KW:
      case ChipsParser::BOOL_KW: {
        _localctx = _tracker.createInstance<ChipsParser::FunctionParameterTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(870);
        df_type();
        setState(871);
        suffixes();
        break;
      }

      case ChipsParser::SENSOR_KW: {
        _localctx = _tracker.createInstance<ChipsParser::SensorParameterTypeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(873);
        match(ChipsParser::SENSOR_KW);
        setState(874);
        df_type();
        setState(875);
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
    setState(879);
    pdf_parameter_type();
    setState(880);
    match(ChipsParser::IDENTIFIER);
    setState(883);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ChipsParser::ASSIGN) {
      setState(881);
      match(ChipsParser::ASSIGN);
      setState(882);
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

ChipsParser::C_suffixesContext* ChipsParser::Cdf_defaulted_declContext::c_suffixes() {
  return getRuleContext<ChipsParser::C_suffixesContext>(0);
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
    setState(885);
    df_type();
    setState(886);
    c_suffixes();
    setState(887);
    match(ChipsParser::IDENTIFIER);
    setState(888);
    match(ChipsParser::ASSIGN);
    setState(889);
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

ChipsParser::C_suffixesContext* ChipsParser::Cdf_full_declarationContext::c_suffixes() {
  return getRuleContext<ChipsParser::C_suffixesContext>(0);
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
    setState(891);
    df_type();
    setState(892);
    c_suffixes();
    setState(893);
    match(ChipsParser::IDENTIFIER);
    setState(896);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ChipsParser::ASSIGN) {
      setState(894);
      match(ChipsParser::ASSIGN);
      setState(895);
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
