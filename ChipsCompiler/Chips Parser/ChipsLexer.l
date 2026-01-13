%{
    #include <iostream>
    #include <cstdlib>
    #include <memory>
    #include "ChipsParser.hpp"
    #include "location.hh"

    # define YY_USER_ACTION  loc.columns (yyleng);

    # define YY_DECL yy::parser::symbol_type yylex () 

    driver drv;
%}

%option noyywrap 
%option nounput 
%option noinput 
%option batch 
%option debug

DIGIT           [0-9]
IDENT           [a-zA-Z][a-zA-Z0-9_]*
ATTRIBUTE       \.[a-zA-Z][a-zA-Z0-9_]*

%%

%{
  yy::location& loc = drv.location;
  loc.step ();
%}


"//"[^\n]*          /* eat up comments   */
[ \t\r]+            {}
\n+                 {loc.lines(yyleng); loc.step();}


{DIGIT}+            { return yy::parser::make_INT(std::stoi(std::string(yytext)),loc);     }
"."{DIGIT}+         { return yy::parser::make_FLOAT(stod(std::string(yytext)),loc);  }
{DIGIT}+"."{DIGIT}* { return yy::parser::make_FLOAT(stod(std::string(yytext)),loc);  }
"true"              { return yy::parser::make_BOOL(true, loc);          }
"false"             { return yy::parser::make_BOOL(false, loc);       }

"int"               { return yy::parser::make_INT_KW(loc);                            }
"float"             { return yy::parser::make_FLOAT_KW(loc);                          }
"bool"              { return yy::parser::make_BOOL_KW(loc);                           }
"logical"           { return yy::parser::make_LOGICAL_KW(loc);                        }
"physical"          { return yy::parser::make_PHYSICAL_KW(loc);                       }
"pure"              { return yy::parser::make_PURE_KW(loc);                           }
"import"            { return yy::parser::make_IMPORT_KW(loc);                         }
"as"                { return yy::parser::make_AS_KW(loc);                             }
"init"              { return yy::parser::make_INIT_KW(loc);                           }
"then"              { return yy::parser::make_THEN_KW(loc);                           }
"this"              { return yy::parser::make_THIS_KW(loc);                           }
"foreach"           { return yy::parser::make_FOREACH_KW(loc);                        }
"at"                { return yy::parser::make_AT_KW(loc);                             }
"in"                { return yy::parser::make_IN_KW(loc);                             }
"if"                { return yy::parser::make_IF_KW(loc);                             }
"to"                { return yy::parser::make_TO_KW(loc);                             }
"else"              { return yy::parser::make_ELSE_KW(loc);                           }
"SYSTEM"|"system"   { return yy::parser::make_SYSTEM_KW(loc);                         }
"dimensions"|"dim"  { return yy::parser::make_DIMENSION_KW(loc);                      }
"link"              { return yy::parser::make_LINK_KW(loc);                           }
"implements"        { return yy::parser::make_IMPLEMENTS_KW(loc);                     }
"having"            { return yy::parser::make_HAVING_KW(loc);                         }
"input"             { return yy::parser::make_INPUT_KW(loc);                          }
"stop"              { return yy::parser::make_STOP_KW(loc);                           }
"channel"           { return yy::parser::make_CHANNEL_KW(loc);                        }
"channels"          { return yy::parser::make_CHANNELS_KW(loc);                       }
"among"             { return yy::parser::make_AMONG_KW(loc);                          }
"spread"            { return yy::parser::make_SPREAD_KW(loc);                         }
"collect"           { return yy::parser::make_COLLECT_KW(loc);                        }
"ctx"               { return yy::parser::make_CTX_KW(loc);                            }
"object"            { return yy::parser::make_OBJECT_KW(loc);                         }
"with"              { return yy::parser::make_WITH_KW(loc);                           }
"implementation"    { return yy::parser::make_IMPLEMENTATION_KW(loc);                 }
"by"                { return yy::parser::make_BY_KW(loc);                             }
"target"            { return yy::parser::make_TARGET_KW(loc);                         }
"default"           { return yy::parser::make_DEFAULT_KW(loc);                        }
"using"             { return yy::parser::make_USING_KW(loc);                          }
"actuator"          { return yy::parser::make_ACTUATOR_KW(loc);                       }
"sensor"            { return yy::parser::make_SENSOR_KW(loc);                         }
".in"               { return yy::parser::make_INPUT_SUF(loc);                         }
".out"              { return yy::parser::make_OUTPUT_SUF(loc);                     }
"->"                { return yy::parser::make_ARROW(loc);                             }
"+"                 { return yy::parser::make_PLUS(loc);                              }
"-"                 { return yy::parser::make_MINUS(loc);                             }
"*"                 { return yy::parser::make_TIMES(loc);                             }
"/"                 { return yy::parser::make_DIV(loc);                               }
"%"                 { return yy::parser::make_MOD(loc);                               }
"<"                 { return yy::parser::make_LT(loc);                                }
">"                 { return yy::parser::make_GT(loc);                                }
"=="                { return yy::parser::make_EQ(loc);                                }
"<="                { return yy::parser::make_LEQ(loc);                               }
">="                { return yy::parser::make_GEQ(loc);                               }
"!="                { return yy::parser::make_NEQ(loc);                               }
"!"                 { return yy::parser::make_NOT(loc);                               }

"="                 { return yy::parser::make_ASSIGN(loc);                            }

","                 { return yy::parser::make_COMMA(loc);                             }
";"                 { return yy::parser::make_SEMICOL(loc);                           }
"("                 { return yy::parser::make_L_PARENTH(loc);                         }
")"                 { return yy::parser::make_R_PARENTH(loc);                         }
"{"                 { return yy::parser::make_L_CURL(loc);                            }
"}"                 { return yy::parser::make_R_CURL(loc);                            }
"["                 { return yy::parser::make_L_SQUA(loc);                            }
"]"                 { return yy::parser::make_R_SQUA(loc);                            }
":"                 { return yy::parser::make_COLUMN(loc);                            }

{IDENT}             { return yy::parser::make_IDENTIFIER(std::string(yytext),loc);          }
\".*\"              { return yy::parser::make_STR(std::string(yytext),loc);           }
"."                 { return yy::parser::make_PERIOD(loc);                            }
.                   { std::cout<<"Unknown char!\n";}
<<EOF>>             {return yy::parser::make_YYEOF (loc);}

%%

void
driver::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (!(yyin = fopen (file.c_str (), "r")))
    {
      std::cerr << "cannot open " << file << ": " << strerror (errno) << '\n';
      exit (EXIT_FAILURE);
    }
}


void
driver::scan_end ()
{
  fclose (yyin);
}
