#start
cmake_minimum_required(VERSION 2.8)

##set(ATOM_FILES)
##set(COMPOUND_FILES)
set(PORT_FILES)
set(TYPE_FILES)
##set(CONNECTOR_FILES)

set(EXTRA_SRC)
set(EXTRA_OBJ)





# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/AT__TeaStoreVariation__UserMachine_xcore.hpp src/TeaStoreVariation/AT__TeaStoreVariation__UserMachine_xcore.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/AT__TeaStoreVariation__ServerMachine_xcore.hpp src/TeaStoreVariation/AT__TeaStoreVariation__ServerMachine_xcore.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/AT__TeaStoreVariation__UserActionInterpreter_xcore.hpp src/TeaStoreVariation/AT__TeaStoreVariation__UserActionInterpreter_xcore.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/AT__TeaStoreVariation__Authenticator_xcore.hpp src/TeaStoreVariation/AT__TeaStoreVariation__Authenticator_xcore.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/AT__TeaStoreVariation__RequestValidator_xcore.hpp src/TeaStoreVariation/AT__TeaStoreVariation__RequestValidator_xcore.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/AT__TeaStoreVariation__RequestLimiter_xcore.hpp src/TeaStoreVariation/AT__TeaStoreVariation__RequestLimiter_xcore.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/AT__TeaStoreVariation__Cache_xcore.hpp src/TeaStoreVariation/AT__TeaStoreVariation__Cache_xcore.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/AT__TeaStoreVariation__DataProvider_xcore.hpp src/TeaStoreVariation/AT__TeaStoreVariation__DataProvider_xcore.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/AT__TeaStoreVariation__WebPageService_xcore.hpp src/TeaStoreVariation/AT__TeaStoreVariation__WebPageService_xcore.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/AT__TeaStoreVariation__PidController_xcore.hpp src/TeaStoreVariation/AT__TeaStoreVariation__PidController_xcore.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/AT__TeaStoreVariation__int_xbuffer_xt.hpp src/TeaStoreVariation/AT__TeaStoreVariation__int_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/AT__TeaStoreVariation__float_xbuffer_xt.hpp src/TeaStoreVariation/AT__TeaStoreVariation__float_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/AT__TeaStoreVariation__bool_xbuffer_xt.hpp src/TeaStoreVariation/AT__TeaStoreVariation__bool_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/AT__TeaStoreVariation__int_xconstant_xt.hpp src/TeaStoreVariation/AT__TeaStoreVariation__int_xconstant_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/AT__TeaStoreVariation__float_xconstant_xt.hpp src/TeaStoreVariation/AT__TeaStoreVariation__float_xconstant_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/AT__TeaStoreVariation__bool_xconstant_xt.hpp src/TeaStoreVariation/AT__TeaStoreVariation__bool_xconstant_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__UserMachine_xcompoundtype.hpp src/TeaStoreVariation/CT__TeaStoreVariation__UserMachine_xcompoundtype.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__ServerMachine_xcompoundtype.hpp src/TeaStoreVariation/CT__TeaStoreVariation__ServerMachine_xcompoundtype.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__UserActionInterpreter_xcompoundtype.hpp src/TeaStoreVariation/CT__TeaStoreVariation__UserActionInterpreter_xcompoundtype.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__Authenticator_xcompoundtype.hpp src/TeaStoreVariation/CT__TeaStoreVariation__Authenticator_xcompoundtype.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__RequestValidator_xcompoundtype.hpp src/TeaStoreVariation/CT__TeaStoreVariation__RequestValidator_xcompoundtype.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__RequestLimiter_xcompoundtype.hpp src/TeaStoreVariation/CT__TeaStoreVariation__RequestLimiter_xcompoundtype.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__Cache_xcompoundtype.hpp src/TeaStoreVariation/CT__TeaStoreVariation__Cache_xcompoundtype.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__DataProvider_xcompoundtype.hpp src/TeaStoreVariation/CT__TeaStoreVariation__DataProvider_xcompoundtype.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__WebPageService_xcompoundtype.hpp src/TeaStoreVariation/CT__TeaStoreVariation__WebPageService_xcompoundtype.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__PidController_xcompoundtype.hpp src/TeaStoreVariation/CT__TeaStoreVariation__PidController_xcompoundtype.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__intintintintint_xinput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__intintintintint_xinput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__intintint_xinput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__intintint_xinput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__boolintint_xinput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__boolintint_xinput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__bool_xinput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__bool_xinput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__boolintint_xinput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__boolintint_xinput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__boolintintintint_xinput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__boolintintintint_xinput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__intint_xinput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__intint_xinput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__boolboolintint_xinput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__boolboolintint_xinput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__boolint_xinput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__boolint_xinput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__boolfloatfloat_xinput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__boolfloatfloat_xinput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__int_xoutput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__int_xoutput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__boolintintint_xoutput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__boolintintint_xoutput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__boolintint_xoutput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__boolintint_xoutput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__bool_xoutput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__bool_xoutput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__boolintint_xoutput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__boolintint_xoutput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__boolintint_xoutput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__boolintint_xoutput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__bool_xoutput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__bool_xoutput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__boolboolfloatintint_xoutput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__boolboolfloatintint_xoutput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__boolboolint_xoutput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__boolboolint_xoutput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__int_xoutput_xbuffer_xt.hpp src/TeaStoreVariation/CT__TeaStoreVariation__int_xoutput_xbuffer_xt.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/CT__TeaStoreVariation__SYSTEM_xCOMPOUND.hpp src/TeaStoreVariation/CT__TeaStoreVariation__SYSTEM_xCOMPOUND.cpp)


# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xintintintintint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xintintintintint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xintintintintint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xintintintintint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xintintintintint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xintintintintint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xintintint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xintintint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xintintint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xintintint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xintintint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xintintint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xboolintint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xboolintint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xboolintint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xboolintint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xboolintint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xboolintint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xbool_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xbool_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xbool_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xbool_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xbool_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xbool_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xboolintintintint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xboolintintintint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xboolintintintint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xboolintintintint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xboolintintintint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xboolintintintint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xintint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xintint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xintint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xintint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xintint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xintint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xboolboolintint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xboolboolintint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xboolboolintint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xboolboolintint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xboolboolintint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xboolboolintint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xboolint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xboolint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xboolint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xboolint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xboolint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xboolint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xboolfloatfloat_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xboolfloatfloat_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xboolfloatfloat_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__many2one_xboolfloatfloat_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xboolfloatfloat_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__many2one_xboolfloatfloat_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__one2many_xint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__one2many_xint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__one2many_xint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__one2many_xint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__one2many_xint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__one2many_xint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__one2many_xboolintintint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__one2many_xboolintintint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__one2many_xboolintintint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__one2many_xboolintintint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__one2many_xboolintintint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__one2many_xboolintintint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__one2many_xboolintint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__one2many_xboolintint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__one2many_xboolintint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__one2many_xboolintint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__one2many_xboolintint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__one2many_xboolintint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__one2many_xbool_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__one2many_xbool_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__one2many_xbool_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__one2many_xbool_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__one2many_xbool_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__one2many_xbool_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__one2many_xboolboolfloatintint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__one2many_xboolboolfloatintint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__one2many_xboolboolfloatintint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__one2many_xboolboolfloatintint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__one2many_xboolboolfloatintint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__one2many_xboolboolfloatintint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__one2many_xboolboolint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__one2many_xboolboolint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__one2many_xboolboolint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__one2many_xboolboolint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__one2many_xboolboolint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__one2many_xboolboolint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xintintintintint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xintintintintint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__flow_xintintintintint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__flow_xintintintintint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__flow_xintintintintint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__flow_xintintintintint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xintintint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xintintint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__flow_xintintint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__flow_xintintint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__flow_xintintint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__flow_xintintint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolintint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolintint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolintint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolintint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolintint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolintint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xbool_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xbool_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__flow_xbool_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__flow_xbool_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__flow_xbool_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__flow_xbool_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolintintintint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolintintintint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolintintintint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolintintintint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolintintintint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolintintintint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xintint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xintint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__flow_xintint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__flow_xintint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__flow_xintint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__flow_xintint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolboolintint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolboolintint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolboolintint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolboolintint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolboolintint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolboolintint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolfloatfloat_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolfloatfloat_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolfloatfloat_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolfloatfloat_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolfloatfloat_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolfloatfloat_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__flow_xint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__flow_xint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__flow_xint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__flow_xint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolintintint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolintintint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolintintint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolintintint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolintintint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolintintint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolboolfloatintint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolboolfloatintint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolboolfloatintint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolboolfloatintint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolboolfloatintint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolboolfloatintint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolboolint_xt.hpp src/TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolboolint_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolboolint_xt.cpp 
                        include/TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolboolint_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolboolint_xt.cpp 
                        include/TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolboolint_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/PT__TeaStoreVariation__int_xport_xt.hpp src/TeaStoreVariation/PT__TeaStoreVariation__int_xport_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/ConnPort__TeaStoreVariation__int_xport_xt.cpp
                        include/TeaStoreVariation/ConnPort__TeaStoreVariation__int_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/CpndEPort__TeaStoreVariation__int_xport_xt.cpp 
                        include/TeaStoreVariation/CpndEPort__TeaStoreVariation__int_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomEPort__TeaStoreVariation__int_xport_xt.cpp 
                        include/TeaStoreVariation/AtomEPort__TeaStoreVariation__int_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomIPort__TeaStoreVariation__int_xport_xt.cpp
                        include/TeaStoreVariation/AtomIPort__TeaStoreVariation__int_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__int_xport_xt.cpp
                        include/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__int_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/PV__TeaStoreVariation__int_xport_xt.cpp
                        include/TeaStoreVariation/PV__TeaStoreVariation__int_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/QPR__TeaStoreVariation__int_xport_xt.cpp
                        include/TeaStoreVariation/QPR__TeaStoreVariation__int_xport_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/PT__TeaStoreVariation__float_xport_xt.hpp src/TeaStoreVariation/PT__TeaStoreVariation__float_xport_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/ConnPort__TeaStoreVariation__float_xport_xt.cpp
                        include/TeaStoreVariation/ConnPort__TeaStoreVariation__float_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/CpndEPort__TeaStoreVariation__float_xport_xt.cpp 
                        include/TeaStoreVariation/CpndEPort__TeaStoreVariation__float_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomEPort__TeaStoreVariation__float_xport_xt.cpp 
                        include/TeaStoreVariation/AtomEPort__TeaStoreVariation__float_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomIPort__TeaStoreVariation__float_xport_xt.cpp
                        include/TeaStoreVariation/AtomIPort__TeaStoreVariation__float_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__float_xport_xt.cpp
                        include/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__float_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/PV__TeaStoreVariation__float_xport_xt.cpp
                        include/TeaStoreVariation/PV__TeaStoreVariation__float_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/QPR__TeaStoreVariation__float_xport_xt.cpp
                        include/TeaStoreVariation/QPR__TeaStoreVariation__float_xport_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/PT__TeaStoreVariation__bool_xport_xt.hpp src/TeaStoreVariation/PT__TeaStoreVariation__bool_xport_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/ConnPort__TeaStoreVariation__bool_xport_xt.cpp
                        include/TeaStoreVariation/ConnPort__TeaStoreVariation__bool_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/CpndEPort__TeaStoreVariation__bool_xport_xt.cpp 
                        include/TeaStoreVariation/CpndEPort__TeaStoreVariation__bool_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomEPort__TeaStoreVariation__bool_xport_xt.cpp 
                        include/TeaStoreVariation/AtomEPort__TeaStoreVariation__bool_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomIPort__TeaStoreVariation__bool_xport_xt.cpp
                        include/TeaStoreVariation/AtomIPort__TeaStoreVariation__bool_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__bool_xport_xt.cpp
                        include/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__bool_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/PV__TeaStoreVariation__bool_xport_xt.cpp
                        include/TeaStoreVariation/PV__TeaStoreVariation__bool_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/QPR__TeaStoreVariation__bool_xport_xt.cpp
                        include/TeaStoreVariation/QPR__TeaStoreVariation__bool_xport_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/PT__TeaStoreVariation__port_xt.hpp src/TeaStoreVariation/PT__TeaStoreVariation__port_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/ConnPort__TeaStoreVariation__port_xt.cpp
                        include/TeaStoreVariation/ConnPort__TeaStoreVariation__port_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/CpndEPort__TeaStoreVariation__port_xt.cpp 
                        include/TeaStoreVariation/CpndEPort__TeaStoreVariation__port_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomEPort__TeaStoreVariation__port_xt.cpp 
                        include/TeaStoreVariation/AtomEPort__TeaStoreVariation__port_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomIPort__TeaStoreVariation__port_xt.cpp
                        include/TeaStoreVariation/AtomIPort__TeaStoreVariation__port_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__port_xt.cpp
                        include/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__port_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/PV__TeaStoreVariation__port_xt.cpp
                        include/TeaStoreVariation/PV__TeaStoreVariation__port_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/QPR__TeaStoreVariation__port_xt.cpp
                        include/TeaStoreVariation/QPR__TeaStoreVariation__port_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/PT__TeaStoreVariation__intintintintint_xport_xt.hpp src/TeaStoreVariation/PT__TeaStoreVariation__intintintintint_xport_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/ConnPort__TeaStoreVariation__intintintintint_xport_xt.cpp
                        include/TeaStoreVariation/ConnPort__TeaStoreVariation__intintintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/CpndEPort__TeaStoreVariation__intintintintint_xport_xt.cpp 
                        include/TeaStoreVariation/CpndEPort__TeaStoreVariation__intintintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomEPort__TeaStoreVariation__intintintintint_xport_xt.cpp 
                        include/TeaStoreVariation/AtomEPort__TeaStoreVariation__intintintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomIPort__TeaStoreVariation__intintintintint_xport_xt.cpp
                        include/TeaStoreVariation/AtomIPort__TeaStoreVariation__intintintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__intintintintint_xport_xt.cpp
                        include/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__intintintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/PV__TeaStoreVariation__intintintintint_xport_xt.cpp
                        include/TeaStoreVariation/PV__TeaStoreVariation__intintintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/QPR__TeaStoreVariation__intintintintint_xport_xt.cpp
                        include/TeaStoreVariation/QPR__TeaStoreVariation__intintintintint_xport_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/PT__TeaStoreVariation__intintint_xport_xt.hpp src/TeaStoreVariation/PT__TeaStoreVariation__intintint_xport_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/ConnPort__TeaStoreVariation__intintint_xport_xt.cpp
                        include/TeaStoreVariation/ConnPort__TeaStoreVariation__intintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/CpndEPort__TeaStoreVariation__intintint_xport_xt.cpp 
                        include/TeaStoreVariation/CpndEPort__TeaStoreVariation__intintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomEPort__TeaStoreVariation__intintint_xport_xt.cpp 
                        include/TeaStoreVariation/AtomEPort__TeaStoreVariation__intintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomIPort__TeaStoreVariation__intintint_xport_xt.cpp
                        include/TeaStoreVariation/AtomIPort__TeaStoreVariation__intintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__intintint_xport_xt.cpp
                        include/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__intintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/PV__TeaStoreVariation__intintint_xport_xt.cpp
                        include/TeaStoreVariation/PV__TeaStoreVariation__intintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/QPR__TeaStoreVariation__intintint_xport_xt.cpp
                        include/TeaStoreVariation/QPR__TeaStoreVariation__intintint_xport_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/PT__TeaStoreVariation__boolintint_xport_xt.hpp src/TeaStoreVariation/PT__TeaStoreVariation__boolintint_xport_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/ConnPort__TeaStoreVariation__boolintint_xport_xt.cpp
                        include/TeaStoreVariation/ConnPort__TeaStoreVariation__boolintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/CpndEPort__TeaStoreVariation__boolintint_xport_xt.cpp 
                        include/TeaStoreVariation/CpndEPort__TeaStoreVariation__boolintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomEPort__TeaStoreVariation__boolintint_xport_xt.cpp 
                        include/TeaStoreVariation/AtomEPort__TeaStoreVariation__boolintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomIPort__TeaStoreVariation__boolintint_xport_xt.cpp
                        include/TeaStoreVariation/AtomIPort__TeaStoreVariation__boolintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__boolintint_xport_xt.cpp
                        include/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__boolintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/PV__TeaStoreVariation__boolintint_xport_xt.cpp
                        include/TeaStoreVariation/PV__TeaStoreVariation__boolintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/QPR__TeaStoreVariation__boolintint_xport_xt.cpp
                        include/TeaStoreVariation/QPR__TeaStoreVariation__boolintint_xport_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/PT__TeaStoreVariation__boolintintintint_xport_xt.hpp src/TeaStoreVariation/PT__TeaStoreVariation__boolintintintint_xport_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/ConnPort__TeaStoreVariation__boolintintintint_xport_xt.cpp
                        include/TeaStoreVariation/ConnPort__TeaStoreVariation__boolintintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/CpndEPort__TeaStoreVariation__boolintintintint_xport_xt.cpp 
                        include/TeaStoreVariation/CpndEPort__TeaStoreVariation__boolintintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomEPort__TeaStoreVariation__boolintintintint_xport_xt.cpp 
                        include/TeaStoreVariation/AtomEPort__TeaStoreVariation__boolintintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomIPort__TeaStoreVariation__boolintintintint_xport_xt.cpp
                        include/TeaStoreVariation/AtomIPort__TeaStoreVariation__boolintintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__boolintintintint_xport_xt.cpp
                        include/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__boolintintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/PV__TeaStoreVariation__boolintintintint_xport_xt.cpp
                        include/TeaStoreVariation/PV__TeaStoreVariation__boolintintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/QPR__TeaStoreVariation__boolintintintint_xport_xt.cpp
                        include/TeaStoreVariation/QPR__TeaStoreVariation__boolintintintint_xport_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/PT__TeaStoreVariation__intint_xport_xt.hpp src/TeaStoreVariation/PT__TeaStoreVariation__intint_xport_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/ConnPort__TeaStoreVariation__intint_xport_xt.cpp
                        include/TeaStoreVariation/ConnPort__TeaStoreVariation__intint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/CpndEPort__TeaStoreVariation__intint_xport_xt.cpp 
                        include/TeaStoreVariation/CpndEPort__TeaStoreVariation__intint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomEPort__TeaStoreVariation__intint_xport_xt.cpp 
                        include/TeaStoreVariation/AtomEPort__TeaStoreVariation__intint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomIPort__TeaStoreVariation__intint_xport_xt.cpp
                        include/TeaStoreVariation/AtomIPort__TeaStoreVariation__intint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__intint_xport_xt.cpp
                        include/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__intint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/PV__TeaStoreVariation__intint_xport_xt.cpp
                        include/TeaStoreVariation/PV__TeaStoreVariation__intint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/QPR__TeaStoreVariation__intint_xport_xt.cpp
                        include/TeaStoreVariation/QPR__TeaStoreVariation__intint_xport_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/PT__TeaStoreVariation__boolboolintint_xport_xt.hpp src/TeaStoreVariation/PT__TeaStoreVariation__boolboolintint_xport_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/ConnPort__TeaStoreVariation__boolboolintint_xport_xt.cpp
                        include/TeaStoreVariation/ConnPort__TeaStoreVariation__boolboolintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/CpndEPort__TeaStoreVariation__boolboolintint_xport_xt.cpp 
                        include/TeaStoreVariation/CpndEPort__TeaStoreVariation__boolboolintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomEPort__TeaStoreVariation__boolboolintint_xport_xt.cpp 
                        include/TeaStoreVariation/AtomEPort__TeaStoreVariation__boolboolintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomIPort__TeaStoreVariation__boolboolintint_xport_xt.cpp
                        include/TeaStoreVariation/AtomIPort__TeaStoreVariation__boolboolintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__boolboolintint_xport_xt.cpp
                        include/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__boolboolintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/PV__TeaStoreVariation__boolboolintint_xport_xt.cpp
                        include/TeaStoreVariation/PV__TeaStoreVariation__boolboolintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/QPR__TeaStoreVariation__boolboolintint_xport_xt.cpp
                        include/TeaStoreVariation/QPR__TeaStoreVariation__boolboolintint_xport_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/PT__TeaStoreVariation__boolint_xport_xt.hpp src/TeaStoreVariation/PT__TeaStoreVariation__boolint_xport_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/ConnPort__TeaStoreVariation__boolint_xport_xt.cpp
                        include/TeaStoreVariation/ConnPort__TeaStoreVariation__boolint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/CpndEPort__TeaStoreVariation__boolint_xport_xt.cpp 
                        include/TeaStoreVariation/CpndEPort__TeaStoreVariation__boolint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomEPort__TeaStoreVariation__boolint_xport_xt.cpp 
                        include/TeaStoreVariation/AtomEPort__TeaStoreVariation__boolint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomIPort__TeaStoreVariation__boolint_xport_xt.cpp
                        include/TeaStoreVariation/AtomIPort__TeaStoreVariation__boolint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__boolint_xport_xt.cpp
                        include/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__boolint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/PV__TeaStoreVariation__boolint_xport_xt.cpp
                        include/TeaStoreVariation/PV__TeaStoreVariation__boolint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/QPR__TeaStoreVariation__boolint_xport_xt.cpp
                        include/TeaStoreVariation/QPR__TeaStoreVariation__boolint_xport_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/PT__TeaStoreVariation__boolfloatfloat_xport_xt.hpp src/TeaStoreVariation/PT__TeaStoreVariation__boolfloatfloat_xport_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/ConnPort__TeaStoreVariation__boolfloatfloat_xport_xt.cpp
                        include/TeaStoreVariation/ConnPort__TeaStoreVariation__boolfloatfloat_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/CpndEPort__TeaStoreVariation__boolfloatfloat_xport_xt.cpp 
                        include/TeaStoreVariation/CpndEPort__TeaStoreVariation__boolfloatfloat_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomEPort__TeaStoreVariation__boolfloatfloat_xport_xt.cpp 
                        include/TeaStoreVariation/AtomEPort__TeaStoreVariation__boolfloatfloat_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomIPort__TeaStoreVariation__boolfloatfloat_xport_xt.cpp
                        include/TeaStoreVariation/AtomIPort__TeaStoreVariation__boolfloatfloat_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__boolfloatfloat_xport_xt.cpp
                        include/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__boolfloatfloat_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/PV__TeaStoreVariation__boolfloatfloat_xport_xt.cpp
                        include/TeaStoreVariation/PV__TeaStoreVariation__boolfloatfloat_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/QPR__TeaStoreVariation__boolfloatfloat_xport_xt.cpp
                        include/TeaStoreVariation/QPR__TeaStoreVariation__boolfloatfloat_xport_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/PT__TeaStoreVariation__boolintintint_xport_xt.hpp src/TeaStoreVariation/PT__TeaStoreVariation__boolintintint_xport_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/ConnPort__TeaStoreVariation__boolintintint_xport_xt.cpp
                        include/TeaStoreVariation/ConnPort__TeaStoreVariation__boolintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/CpndEPort__TeaStoreVariation__boolintintint_xport_xt.cpp 
                        include/TeaStoreVariation/CpndEPort__TeaStoreVariation__boolintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomEPort__TeaStoreVariation__boolintintint_xport_xt.cpp 
                        include/TeaStoreVariation/AtomEPort__TeaStoreVariation__boolintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomIPort__TeaStoreVariation__boolintintint_xport_xt.cpp
                        include/TeaStoreVariation/AtomIPort__TeaStoreVariation__boolintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__boolintintint_xport_xt.cpp
                        include/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__boolintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/PV__TeaStoreVariation__boolintintint_xport_xt.cpp
                        include/TeaStoreVariation/PV__TeaStoreVariation__boolintintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/QPR__TeaStoreVariation__boolintintint_xport_xt.cpp
                        include/TeaStoreVariation/QPR__TeaStoreVariation__boolintintint_xport_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/PT__TeaStoreVariation__boolboolfloatintint_xport_xt.hpp src/TeaStoreVariation/PT__TeaStoreVariation__boolboolfloatintint_xport_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/ConnPort__TeaStoreVariation__boolboolfloatintint_xport_xt.cpp
                        include/TeaStoreVariation/ConnPort__TeaStoreVariation__boolboolfloatintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/CpndEPort__TeaStoreVariation__boolboolfloatintint_xport_xt.cpp 
                        include/TeaStoreVariation/CpndEPort__TeaStoreVariation__boolboolfloatintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomEPort__TeaStoreVariation__boolboolfloatintint_xport_xt.cpp 
                        include/TeaStoreVariation/AtomEPort__TeaStoreVariation__boolboolfloatintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomIPort__TeaStoreVariation__boolboolfloatintint_xport_xt.cpp
                        include/TeaStoreVariation/AtomIPort__TeaStoreVariation__boolboolfloatintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__boolboolfloatintint_xport_xt.cpp
                        include/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__boolboolfloatintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/PV__TeaStoreVariation__boolboolfloatintint_xport_xt.cpp
                        include/TeaStoreVariation/PV__TeaStoreVariation__boolboolfloatintint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/QPR__TeaStoreVariation__boolboolfloatintint_xport_xt.cpp
                        include/TeaStoreVariation/QPR__TeaStoreVariation__boolboolfloatintint_xport_xt.hpp)

# // From Generated code. FIXME: we should give java location.
list(APPEND TYPE_FILES include/TeaStoreVariation/PT__TeaStoreVariation__boolboolint_xport_xt.hpp src/TeaStoreVariation/PT__TeaStoreVariation__boolboolint_xport_xt.cpp)


list (APPEND PORT_FILES src/TeaStoreVariation/ConnPort__TeaStoreVariation__boolboolint_xport_xt.cpp
                        include/TeaStoreVariation/ConnPort__TeaStoreVariation__boolboolint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/CpndEPort__TeaStoreVariation__boolboolint_xport_xt.cpp 
                        include/TeaStoreVariation/CpndEPort__TeaStoreVariation__boolboolint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomEPort__TeaStoreVariation__boolboolint_xport_xt.cpp 
                        include/TeaStoreVariation/AtomEPort__TeaStoreVariation__boolboolint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomIPort__TeaStoreVariation__boolboolint_xport_xt.cpp
                        include/TeaStoreVariation/AtomIPort__TeaStoreVariation__boolboolint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__boolboolint_xport_xt.cpp
                        include/TeaStoreVariation/AtomExternalPort__TeaStoreVariation__boolboolint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/PV__TeaStoreVariation__boolboolint_xport_xt.cpp
                        include/TeaStoreVariation/PV__TeaStoreVariation__boolboolint_xport_xt.hpp)

list (APPEND PORT_FILES src/TeaStoreVariation/QPR__TeaStoreVariation__boolboolint_xport_xt.cpp
                        include/TeaStoreVariation/QPR__TeaStoreVariation__boolboolint_xport_xt.hpp)

include_directories("include")
add_library(pack__TeaStoreVariation 
                      ${TYPE_FILES}
                      ${PORT_FILES}
                      ${EXTRA_SRC}
                      ${EXTRA_OBJ})
