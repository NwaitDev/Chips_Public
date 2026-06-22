#include "com_def.h"

/**************************************************************************************************
 Name           : color_interpolation()

 Description    : This function interpolates RGB data from RAW data.
                  This function uses filter.

 Parameter (IN) : ImageConfigType	*in_raw_cfg		: configuration of input RAW image
                  ImageConfigType	*out_rgb_cfg	: configuration of output RGB image
                  short				*filter_r		: de-mosaic filter when center is R
                  short				*filter_gr		: de-mosaic filter when center is Gr
                  short				*filter_gb		: de-mosaic filter when center is Gb
                  short				*filter_b		: de-mosaic filter when center is B
// add JPK 
                  short                offset_V     : vertical  offset for the actual sub_image
                  short                offset_H     : horizontal  offset for the actual sub_image
          
          (OUT) : None

 Return Val.    : ERROR_CODE

 Note           : 
 History        : 
**************************************************************************************************/
ERROR_CODE color_interpolation(ImageConfigType *in_raw_cfg, ImageConfigType *out_rgb_cfg, 
								short *filter_r, short *filter_gr, short *filter_gb, short *filter_b, 
								short offset_V, short offset_H)
{
	ERROR_CODE	err = E_OK;
	short		*in_raw_img;
	short		*out_r_img;
	short		*out_g_img;
	short		*out_b_img;
	short		*filter[2][2];
	long		tmp;
	short		count_x;
	short		count_y;
	short		count_i;
	short		count_j;

	if(in_raw_cfg->BayerPatn == BAYER_GRBG){
		if(((in_raw_cfg->OffsetH & 0x1) == 0) && ((in_raw_cfg->OffsetV & 0x1) == 0)){
			filter[0][0] = filter_gr;
			filter[0][1] = filter_r;
			filter[1][0] = filter_b;
			filter[1][1] = filter_gb;
		}
		else if(((in_raw_cfg->OffsetH & 0x1) == 1) && ((in_raw_cfg->OffsetV & 0x1) == 0)){
			filter[0][0] = filter_r;
			filter[0][1] = filter_gr;
			filter[1][0] = filter_gb;
			filter[1][1] = filter_b;
		}
		else if(((in_raw_cfg->OffsetH & 0x1) == 0) && ((in_raw_cfg->OffsetV & 0x1) == 1)){
			filter[0][0] = filter_b;
			filter[0][1] = filter_gb;
			filter[1][0] = filter_gr;
			filter[1][1] = filter_r;
		}
		else{
			filter[0][0] = filter_gb;
			filter[0][1] = filter_b;
			filter[1][0] = filter_r;
			filter[1][1] = filter_gr;
		}
	}
	else if(in_raw_cfg->BayerPatn == BAYER_RGGB){
		if(((in_raw_cfg->OffsetH & 0x1) == 0) && ((in_raw_cfg->OffsetV & 0x1) == 0)){
			filter[0][0] = filter_r;
			filter[0][1] = filter_gr;
			filter[1][0] = filter_gb;
			filter[1][1] = filter_b;
		}
		else if(((in_raw_cfg->OffsetH & 0x1) == 1) && ((in_raw_cfg->OffsetV & 0x1) == 0)){
			filter[0][0] = filter_gr;
			filter[0][1] = filter_r;
			filter[1][0] = filter_b;
			filter[1][1] = filter_gb;
		}
		else if(((in_raw_cfg->OffsetH & 0x1) == 0) && ((in_raw_cfg->OffsetV & 0x1) == 1)){
			filter[0][0] = filter_gb;
			filter[0][1] = filter_b;
			filter[1][0] = filter_r;
			filter[1][1] = filter_gr;
		}
		else{
			filter[0][0] = filter_b;
			filter[0][1] = filter_gb;
			filter[1][0] = filter_gr;
			filter[1][1] = filter_r;
		}
	}
	else if(in_raw_cfg->BayerPatn == BAYER_BGGR){
		if(((in_raw_cfg->OffsetH & 0x1) == 0) && ((in_raw_cfg->OffsetV & 0x1) == 0)){
			filter[0][0] = filter_b;
			filter[0][1] = filter_gb;
			filter[1][0] = filter_gr;
			filter[1][1] = filter_r;
		}
		else if(((in_raw_cfg->OffsetH & 0x1) == 1) && ((in_raw_cfg->OffsetV & 0x1) == 0)){
			filter[0][0] = filter_gb;
			filter[0][1] = filter_b;
			filter[1][0] = filter_r;
			filter[1][1] = filter_gr;
		}
		else if(((in_raw_cfg->OffsetH & 0x1) == 0) && ((in_raw_cfg->OffsetV & 0x1) == 1)){
			filter[0][0] = filter_gr;
			filter[0][1] = filter_r;
			filter[1][0] = filter_b;
			filter[1][1] = filter_gb;
		}
		else{
			filter[0][0] = filter_r;
			filter[0][1] = filter_gr;
			filter[1][0] = filter_gb;
			filter[1][1] = filter_b;
		}
	}
	else if(in_raw_cfg->BayerPatn == BAYER_GBRG){
		if(((in_raw_cfg->OffsetH & 0x1) == 0) && ((in_raw_cfg->OffsetV & 0x1) == 0)){
			filter[0][0] = filter_gb;
			filter[0][1] = filter_b;
			filter[1][0] = filter_r;
			filter[1][1] = filter_gr;
		}
		else if(((in_raw_cfg->OffsetH & 0x1) == 1) && ((in_raw_cfg->OffsetV & 0x1) == 0)){
			filter[0][0] = filter_b;
			filter[0][1] = filter_gb;
			filter[1][0] = filter_gr;
			filter[1][1] = filter_r;
		}
		else if(((in_raw_cfg->OffsetH & 0x1) == 0) && ((in_raw_cfg->OffsetV & 0x1) == 1)){
			filter[0][0] = filter_r;
			filter[0][1] = filter_gr;
			filter[1][0] = filter_gb;
			filter[1][1] = filter_b;
		}
		else{
			filter[0][0] = filter_gr;
			filter[0][1] = filter_r;
			filter[1][0] = filter_b;
			filter[1][1] = filter_gb;
		}
	}
	else{
	}

	for(count_y=0; count_y<out_rgb_cfg->ImageSizeV; count_y++){
 		in_raw_img = (short *)(in_raw_cfg->Address[0] 
								+ in_raw_cfg->AreaSizeH * (in_raw_cfg->OffsetV + count_y) 
								+ in_raw_cfg->OffsetH);
		out_r_img = (short *)(out_rgb_cfg->Address[0] 
								+ out_rgb_cfg->AreaSizeH * (out_rgb_cfg->OffsetV + count_y) 
								+ out_rgb_cfg->OffsetH);
		out_g_img = (short *)(out_rgb_cfg->Address[1] 
								+ out_rgb_cfg->AreaSizeH * (out_rgb_cfg->OffsetV + count_y) 
								+ out_rgb_cfg->OffsetH);
		out_b_img = (short *)(out_rgb_cfg->Address[2] 
								+ out_rgb_cfg->AreaSizeH * (out_rgb_cfg->OffsetV + count_y) 
								+ out_rgb_cfg->OffsetH);
       
        
		for(count_x=0; count_x<out_rgb_cfg->ImageSizeH; count_x++){

			tmp = 0;
			for(count_j=0; count_j<DEMOSAIC_FILTER_SIZE_V; count_j++){
				for(count_i=0; count_i<DEMOSAIC_FILTER_SIZE_H; count_i++){
					tmp += (*(in_raw_img + in_raw_cfg->AreaSizeH 
								* (count_j-(DEMOSAIC_FILTER_SIZE_V>>1)) 
								+ (count_i-(DEMOSAIC_FILTER_SIZE_H>>1)))) 
								* filter[(count_y+offset_V) & 0x1][(count_x+offset_H) & 0x1]
									[DEMOSAIC_FILTER_SIZE_H*count_j+count_i];
				}
			}
			*out_r_img = (short)(((tmp + (1<<(DEMOSAIC_FILTER_BIT-1))) >> DEMOSAIC_FILTER_BIT) 
									>> (DEMOSAIC_IN_DATA_BIT-DEMOSAIC_OUT_DATA_BIT));
			tmp = 0;
			for(count_j=0; count_j<DEMOSAIC_FILTER_SIZE_V; count_j++){
				for(count_i=0; count_i<DEMOSAIC_FILTER_SIZE_H; count_i++){
					tmp += (*(in_raw_img + in_raw_cfg->AreaSizeH 
								* (count_j-(DEMOSAIC_FILTER_SIZE_V>>1)) 
								+ (count_i-(DEMOSAIC_FILTER_SIZE_H>>1)))) 
								* filter[(count_y+offset_V) & 0x1][(count_x+offset_H) & 0x1] 
									[DEMOSAIC_FILTER_SIZE_H*DEMOSAIC_FILTER_SIZE_V 
									+ DEMOSAIC_FILTER_SIZE_H*count_j+count_i];
				}
			}
			*out_g_img = (short)(((tmp + (1<<(DEMOSAIC_FILTER_BIT-1))) >> DEMOSAIC_FILTER_BIT) 
									>> (DEMOSAIC_IN_DATA_BIT-DEMOSAIC_OUT_DATA_BIT));
			tmp = 0;
			for(count_j=0; count_j<DEMOSAIC_FILTER_SIZE_V; count_j++){
				for(count_i=0; count_i<DEMOSAIC_FILTER_SIZE_H; count_i++){
					tmp += (*(in_raw_img + in_raw_cfg->AreaSizeH 
								* (count_j-(DEMOSAIC_FILTER_SIZE_V>>1)) 
								+ (count_i-(DEMOSAIC_FILTER_SIZE_H>>1)))) 
								* filter[(count_y+offset_V) & 0x1][(count_x+offset_H) & 0x1] 
									[DEMOSAIC_FILTER_SIZE_H*DEMOSAIC_FILTER_SIZE_V*2 
									+ DEMOSAIC_FILTER_SIZE_H*count_j+count_i];
				}
			}
			*out_b_img = (short)(((tmp + (1<<(DEMOSAIC_FILTER_BIT-1))) >> DEMOSAIC_FILTER_BIT) 
									>> (DEMOSAIC_IN_DATA_BIT-DEMOSAIC_OUT_DATA_BIT));

			if(*out_r_img < 0){
				*out_r_img = 0;
			}
			if(*out_r_img > (1<<DEMOSAIC_OUT_DATA_BIT)-1){
				*out_r_img = (1<<DEMOSAIC_OUT_DATA_BIT)-1;
			}
			if(*out_g_img < 0){
				*out_g_img = 0;
			}
			if(*out_g_img > (1<<DEMOSAIC_OUT_DATA_BIT)-1){
				*out_g_img = (1<<DEMOSAIC_OUT_DATA_BIT)-1;
			}
			if(*out_b_img < 0){
				*out_b_img = 0;
			}
			if(*out_b_img > (1<<DEMOSAIC_OUT_DATA_BIT)-1){
				*out_b_img = (1<<DEMOSAIC_OUT_DATA_BIT)-1;
			}

			in_raw_img++;
			out_r_img++;
			out_g_img++;
			out_b_img++;
		}
	}

	return err;
}

