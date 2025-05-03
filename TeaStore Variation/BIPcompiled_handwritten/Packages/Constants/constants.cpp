#include "constants.hpp"

int cst(const std::string cname){

    // resources received by user computer
    if(cname.compare("R_PAGE")==0){
        return R_PAGE;
    }
    if(cname.compare("R_NO_PAGE")==0){
        return R_NO_PAGE;
    }
    if(cname.compare("R_CONNEXION_PAGE")==0){
        return R_CONNEXION_PAGE;
    }
    if(cname.compare("R_OTHER_PAGE")==0){
        return R_OTHER_PAGE;
    }
    if(cname.compare("R_NEW_PAGE")==0){
        return R_NEW_PAGE;
    }
    if(cname.compare("R_PREVIOUS_PAGE")==0){
        return R_PREVIOUS_PAGE;
    }

    // actions performed by the user and sent to the server
    if(cname.compare("A_SIGNAL")==0){
        return A_SIGNAL;
    }
    if(cname.compare("A_NO_SIGNAL")==0){
        return A_NO_SIGNAL;
    }
    if(cname.compare("A_STAY")==0){
        return A_STAY;
    }
    if(cname.compare("A_LEAVE")==0){
        return A_LEAVE;
    }
    if(cname.compare("A_ASK_FOR_MANY_IMAGES")==0){
        return A_ASK_FOR_MANY_IMAGES;
    }
    if(cname.compare("A_ASK_FOR_FEW_IMAGES")==0){
        return A_ASK_FOR_FEW_IMAGES;
    }
    if(cname.compare("A_PRIVATE_PAGE")==0){
        return A_PRIVATE_PAGE;
    }
    if(cname.compare("A_PUBLIC_PAGE")==0){
        return A_PUBLIC_PAGE;
    }
    if(cname.compare("A_AUTH_DATA")==0){
        return A_AUTH_DATA;
    }
    if(cname.compare("A_NO_AUTH_DATA")==0){
        return A_NO_AUTH_DATA;
    }

    // requests to be validated by the server
    if(cname.compare("PRIVATE_PAGE")==0){
        return PRIVATE_PAGE;
    }
    if(cname.compare("PUBLIC_PAGE")==0){
        return PUBLIC_PAGE;
    }
    if(cname.compare("ASK_FOR_MANY_IMAGES")==0){
        return ASK_FOR_MANY_IMAGES;
    }
    if(cname.compare("ASK_FOR_FEW_IMAGES")==0){
        return ASK_FOR_FEW_IMAGES;
    }

    // other constants
    if(cname.compare("CACHE_MAX_SIZE")==0){
        return CACHE_MAX_SIZE;
    }
    if(cname.compare("CACHE_MIN_SIZE")==0){
        return CACHE_MIN_SIZE;
    }

    if(cname.compare("DB_SIZE")==0){
        return DB_SIZE;
    }
    if(cname.compare("DEFAULT_IMG_NUM")==0){
        return DEFAULT_IMG_NUM;
    }
    if(cname.compare("ADDITIONNAL_IMG_CONNECTED")==0){
        return ADDITIONNAL_IMG_CONNECTED;
    }
    if(cname.compare("ADDITIONNAL_IMG_PRIVATE")==0){
        return ADDITIONNAL_IMG_PRIVATE;
    }
    if(cname.compare("ADDITIONNAL_IMG_BIG_REQ")==0){
        return ADDITIONNAL_IMG_BIG_REQ;
    }

    return -1;
}

double cstfloat(const std::string cname){

    // constants to tune
    if(cname.compare("G_P_COEF")==0){
        return G_P_COEF;
    }
    if(cname.compare("G_I_COEF")==0){
        return G_I_COEF;
    }
    if(cname.compare("G_D_COEF")==0){
        return G_D_COEF;
    }
    if(cname.compare("DTB_P_COEF")==0){
        return DTB_P_COEF;
    }
    if(cname.compare("DTB_I_COEF")==0){
        return DTB_I_COEF;
    }
    if(cname.compare("DTB_D_COEF")==0){
        return DTB_D_COEF;
    }
    if(cname.compare("G_COMMAND")==0){
        return G_COMMAND;
    }
    if(cname.compare("NO_REQ_STEP")==0){
        return NO_REQ_STEP;
    }
    if(cname.compare("REQ_TIME")==0){
        return REQ_TIME;
    }
    return (double)cst(cname);
}