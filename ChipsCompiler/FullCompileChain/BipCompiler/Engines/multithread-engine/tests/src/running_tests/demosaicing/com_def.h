#ifndef	_COM_DEF_H_
#define	_COM_DEF_H_

// Prints traces for DEBUG
//#define TRACE_ON

// Writes resulting RGB elements in files (in joiner.c)
//#define RES_IN_FILES


/**************************************************************************************************
	TYPEDEF
**************************************************************************************************/
typedef unsigned char	uchar;
typedef unsigned short	ushort;
typedef unsigned long	ulong;
typedef ushort			ERROR_CODE;

#define		E_OK					0
#define		E_KO					1

// number of sub-images for parallelization
#define NB_Clst 1
#define NB_Core 6


/**************************************************************************************************
	DEFINE
**************************************************************************************************/
// CONSTANTS
#define RAW_PATH "./"


/**************************************************************************************************^M
        MACRO SETTINGS
**************************************************************************************************/
#define RES_IN_FILES
#define TRACE_ON
//#define MPARM

#ifdef MPARM
#define PRINTNUM(arg0, arg1, arg2) _printdecn(#arg0, arg2)
#define PRINTSTR(arg0)             _printstrn(#arg0)
#else
#define PRINTNUM(arg0, arg1, arg2) printf(#arg0 #arg1 "\n", arg2)
#define PRINTSTR(arg0)             printf(#arg0 "\n")
#endif


/**************************************************************************************************
	FROM main.c
**************************************************************************************************/
/**************************************************************************************************
	for SETTING PARAMETERS
**************************************************************************************************/

// ----- Image Size -------------------------------------------------------------------------------
#define		RAW_IMAGE_SIZE_H		30
#define		RAW_IMAGE_SIZE_V		30
#define		RGB_IMAGE_SIZE_H		(RAW_IMAGE_SIZE_H - 4)
#define		RGB_IMAGE_SIZE_V		(RAW_IMAGE_SIZE_V - 4)
#define		Y_IMAGE_SIZE_H			(RAW_IMAGE_SIZE_H - 4)
#define		Y_IMAGE_SIZE_V			(RAW_IMAGE_SIZE_V - 4)
#define		UV_IMAGE_SIZE_H			(RAW_IMAGE_SIZE_H - 4)
#define		UV_IMAGE_SIZE_V			(RAW_IMAGE_SIZE_V - 4)
#define		EDGE_IMAGE_SIZE_H		(RAW_IMAGE_SIZE_H - 4)
#define		EDGE_IMAGE_SIZE_V		(RAW_IMAGE_SIZE_V - 4)
#define		JPEG_IMAGE_SIZE_H		640
#define		JPEG_IMAGE_SIZE_V		480
#define		JPEG_IMAGE_BYTE			500*1024

// ----- AE/AWB Statistics ------------------------------------------------------------------------
#define		STAT_OFFSET_H			4
#define		STAT_OFFSET_V			4
#define		STAT_WINDOW_SIZE_H		10
#define		STAT_WINDOW_SIZE_V		10
#define		STAT_INTERVAL_H			0
#define		STAT_INTERVAL_V			0
#define		STAT_WINDOW_CNT_H		64
#define		STAT_WINDOW_CNT_V		48
#define		STAT_OFST_GAIN_R		2048
#define		STAT_OFST_GAIN_G		1024
#define		STAT_OFST_GAIN_B		2048

// ----- AE Calculation ---------------------------------------------------------------------------
#define		AE_WEI_WINDOW_STA_H		24
#define		AE_WEI_WINDOW_END_H		40
#define		AE_WEI_WINDOW_STA_V		18
#define		AE_WEI_WINDOW_END_V		30
#define		AE_WEIGHT				4
#define		AE_TARGET_VALUE			265


/**************************************************************************************************
	FROM ae_awb_proc.h
**************************************************************************************************/
/**************************************************************************************************
	STRUCT
**************************************************************************************************/
typedef struct{
	short	*Address;
	short	AreaSizeH;
	short	AreaSizeV;
	short	OffsetH;
	short	OffsetV;
	short	WindowSizeH;
	short	WindowSizeV;
	short	IntervalH;
	short	IntervalV;
	short	WindowCntH;
	short	WindowCntV;
	short	OffsetGainR;
	short	OffsetGainG;
	short	OffsetGainB;
	char	BayerPatn;
} StatisticsInType;

typedef struct{
	short	*AverageR;
	short	*AverageGr;
	short	*AverageGb;
	short	*AverageB;
	short	*AverageY;
} StatisticsOutType;

typedef struct{
	short	WindowCntH;
	short	WindowCntV;
	short	WeiWindowStaH;
	short	WeiWindowEndH;
	short	WeiWindowStaV;
	short	WeiWindowEndV;
	short	Weight;
	short	*AverageY;
	short	TargetValue;
} AeCalcInType;

typedef struct{
	short	AdjGain;
} AeCalcOutType;

typedef struct{
	short	WindowCntH;
	short	WindowCntV;
	short	OffsetGainR;
	short	OffsetGainG;
	short	OffsetGainB;
	short	*AverageR;
	short	*AverageGr;
	short	*AverageGb;
	short	*AverageB;
} AwbCalcInType;

typedef struct{
	short	AdjGainR;
	short	AdjGainB;
	short	*RGBMatrix;
} AwbCalcOutType;


/**************************************************************************************************
	FROM image_proc.h
**************************************************************************************************/
/**************************************************************************************************
	STRUCT
**************************************************************************************************/
typedef struct{
	short	*Address[3];
	short	AreaSizeH;
	short	AreaSizeV;
	short	ImageSizeH;
	short	ImageSizeV;
	short	OffsetH;
	short	OffsetV;
	char	BayerPatn;
} ImageConfigType;


/**************************************************************************************************
	FROM com_def.h
**************************************************************************************************/
// ------------------------------------------------------------------------------------------------
//       Color Filter Array 
// ------------------------------------------------------------------------------------------------
#define		BAYER_GRBG				0
#define		BAYER_RGGB				1
#define		BAYER_BGGR				2
#define		BAYER_GBRG				3

// ------------------------------------------------------------------------------------------------
//       AE/AWB Processing 
// ------------------------------------------------------------------------------------------------

// ----- AE/AWB Statistics ------------------------------------------------------------------------
#define		COEFF_Y_R				306
#define		COEFF_Y_G				601
#define		COEFF_Y_B				117
#define		COEFF_Y_BIT				10

#define		OFFSET_GAIN_BIT			10

// ----- AE Calculation ---------------------------------------------------------------------------
#define		AE_ADJ_GAIN_BIT			8

// ----- AWB Calculation --------------------------------------------------------------------------
#define		AWB_ADJ_GAIN_BIT		9
#define		AWB_MATRIX_BIT			9

// ------------------------------------------------------------------------------------------------
//       IMAGE Processing 
// ------------------------------------------------------------------------------------------------

// ----- OB Clamp ---------------------------------------------------------------------------------
#define		OB_CLAMP_IN_DATA_BIT	10
#define		OB_CLAMP_OUT_DATA_BIT	10

// ----- Color Offset Compensation ----------------------------------------------------------------
#define		C_OFST_CMP_IN_DATA_BIT	10
#define		C_OFST_CMP_OUT_DATA_BIT	10

// ----- WB Compensation --------------------------------------------------------------------------
#define		WB_COMP_IN_DATA_BIT		10
#define		WB_COMP_OUT_DATA_BIT	10
#define		WB_GAIN_BIT				AWB_ADJ_GAIN_BIT

// ----- Gamma Correction -------------------------------------------------------------------------
#define		GAMMA_IN_DATA_BIT		10
#define		GAMMA_OUT_DATA_BIT		9
#define		GAMMA_GAIN_BIT			AE_ADJ_GAIN_BIT
#define		GAMMA_TBL_IN_BIT		10
#define		GAMMA_TBL_OUT_BIT		9

// ----- Color Interpolation ----------------------------------------------------------------------
#define		DEMOSAIC_IN_DATA_BIT	9
#define		DEMOSAIC_OUT_DATA_BIT	9
#define		DEMOSAIC_FILTER_SIZE_H	5
#define		DEMOSAIC_FILTER_SIZE_V	5
#define		DEMOSAIC_FILTER_BIT		9

// ----- Color Correction -------------------------------------------------------------------------
#define		RGB_CORCT_IN_DATA_BIT	9
#define		RGB_CORCT_OUT_DATA_BIT	9
#define		RGB_MATRIX_BIT			AWB_MATRIX_BIT

// ----- Color Conversion -------------------------------------------------------------------------
#define		UV_CONVT_IN_DATA_BIT	9
#define		UV_CONVT_OUT_DATA_BIT	9
#define		UV_MATRIX_BIT			10

// ----- Color Suppression ------------------------------------------------------------------------
#define		C_SUP_IN_DATA_BIT		9
#define		C_SUP_OUT_DATA_BIT		9
#define		C_SUP_Y_DATA_BIT		9
#define		C_SUP_COEFF_BIT			7
#define		C_SUP_TBL_IN_BIT		8

// ----- Color Smoothing --------------------------------------------------------------------------
#define		C_SMOOTH_IN_DATA_BIT	9
#define		C_SMOOTH_OUT_DATA_BIT	9
#define		C_SMOOTH_FILTER_SIZE_H	5
#define		C_SMOOTH_FILTER_SIZE_V	5
#define		C_SMOOTH_FILTER_BIT		7

// ----- Color Clipping ---------------------------------------------------------------------------
#define		C_CLIP_IN_DATA_BIT		9
#define		C_CLIP_OUT_DATA_BIT		8
#define		C_CLIP_TBL_IN_BIT		8
#define		C_CLIP_TBL_OUT_BIT		8

// ----- Edge Detection ---------------------------------------------------------------------------
#define		E_DETECT_IN_DATA_BIT	9
#define		E_DETECT_OUT_DATA_BIT	9
#define		EDGE_FILTER_SIZE_H		5
#define		EDGE_FILTER_SIZE_V		5
#define		EDGE_FILTER_BIT			11

// ----- Edge Coring ------------------------------------------------------------------------------
#define		E_CORING_IN_DATA_BIT	9
#define		E_CORING_OUT_DATA_BIT	9
#define		E_CORING_TBL_IN_BIT		9
#define		E_CORING_TBL_OUT_BIT	9

// ----- Edge Enhancement -------------------------------------------------------------------------
#define		E_ENHANCE_IN_DATA_BIT	9
#define		E_ENHANCE_OUT_DATA_BIT	9
#define		E_ENHANCE_GAIN_BIT		8

// ----- Luma Conversion --------------------------------------------------------------------------
#define		Y_CONVT_IN_DATA_BIT		9
#define		Y_CONVT_OUT_DATA_BIT	9
#define		Y_MATRIX_BIT			10

// ----- Luma Edge Addition -----------------------------------------------------------------------
#define		Y_E_ADD_IN_DATA_BIT		9
#define		Y_E_ADD_OUT_DATA_BIT	8


ERROR_CODE color_interpolation(ImageConfigType *in_raw_cfg, ImageConfigType *out_rgb_cfg, 
								short *filter_r, short *filter_gr, short *filter_gb, short *filter_b, 
								short offset_V, short offset_H);

#endif	/* #ifndef _COM_DEF_H_ */

