#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__
#include <string>



// CLASSES OF RESOURCES SENT TO THE USER
const int R_PAGE = 1;
const int R_NO_PAGE = 0;
const int R_CONNEXION_PAGE = 2;
const int R_OTHER_PAGE = 0;
const int R_PREVIOUS_PAGE = 4;
const int R_NEW_PAGE = 0;

// CLASSES OF ACTIONS PERFORMED BY THE USER
const int A_SIGNAL = 1;
const int A_NO_SIGNAL = 0;
const int A_STAY = 2;
const int A_LEAVE = 0;
const int A_ASK_FOR_MANY_IMAGES = 4;
const int A_ASK_FOR_FEW_IMAGES = 0;
const int A_PRIVATE_PAGE = 8;
const int A_PUBLIC_PAGE = 0;
const int A_AUTH_DATA = 16;
const int A_NO_AUTH_DATA = 0;

// CLASSES OF REQUESTS TO VALIDATE BY THE SERVER
const int PRIVATE_PAGE = 1;
const int PUBLIC_PAGE = 0;
const int ASK_FOR_MANY_IMAGES = 2;
const int ASK_FOR_FEW_IMAGES = 0;


// Parameters to tune for the system model
const float G_P_COEF = 0.0;
const float G_I_COEF = 0.0;
const float G_D_COEF = 0.0;

const float DTB_P_COEF = -1;
const float DTB_I_COEF = -0.01;
const float DTB_D_COEF = 0.0;


const float G_COMMAND = 4.0; 

const float NO_REQ_STEP = 0.3;
const float REQ_TIME = 2.0;

const float CACHE_MAX_SIZE = 1000;
const float CACHE_MIN_SIZE = 20;

const int DB_SIZE = 40;

const int DEFAULT_IMG_NUM = 2;
const int ADDITIONNAL_IMG_CONNECTED = 1;
const int ADDITIONNAL_IMG_PRIVATE = 1;
const int ADDITIONNAL_IMG_BIG_REQ = 5;

/*
    Other general purpose constants
*/
const int KO = 0; // failed check
const bool VERBOSE = false; // false == the partial connexions will not print their trace in stdout by default

int cst(const std::string cname);

double cstfloat(const std::string cname);
#endif