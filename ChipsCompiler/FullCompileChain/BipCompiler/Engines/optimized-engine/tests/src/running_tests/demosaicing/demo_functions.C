#include <stdio.h>
#include <stdlib.h>
#include "demo_functions.h"
#include "com_def.h"
#include "raw_data_28.h"
#include "filters.h"

// print functions
void print(const std::string &s, int v1) {
  std::cout << s << v1 << std::endl;
}

void print(const std::string &s, int v1, int v2) {
  std::cout << s << v1 << ", " << v2 << std::endl;
}


// function to make an arbitrary sized image from the basic 648x648 sample
void load_img(int index,raw_img &new_img){
    //memcpy(new_img ,raw_data_648,sizeof(raw_data_648)) ;
  for(int i=0; i<(RAW_H*RAW_V)/(28*28); i++){
    memcpy(new_img + i*28*28,raw_data_28,sizeof(short)*28*28) ;
  
  if((RAW_H*RAW_V) % (28*28) != 0){
    memcpy(new_img + ((RAW_H*RAW_V)/(28*28))*28*28,raw_data_28,sizeof(short)*((RAW_H*RAW_V) % (28*28)));
  }
 }
}

void load_img(int index, RawImg &new_img){
  load_img(index, new_img.m_raw_img);
}

void split_img_to_line(raw_img &source, raw_line &l1, raw_line &l2, raw_line &l3){
  memcpy(l1,  source,                                     sizeof(raw_line));
  memcpy(l2,  source + RAW_H*RGB_BLOCK_V,   sizeof(raw_line));
  memcpy(l3,  source + 2*RAW_H*RGB_BLOCK_V, sizeof(raw_line));
}

void split_img_to_line(RawImg &source, RawLine &l1, RawLine &l2, RawLine &l3) {
  split_img_to_line(source.m_raw_img, l1.m_raw_line, l2.m_raw_line, l3.m_raw_line);
}


void split_line_to_block(raw_line &source, raw_block &b1, raw_block &b2, raw_block &b3){
  int i;
  for(i=0;i<RAW_BLOCK_V;i++){
    memcpy(b1+i*RAW_BLOCK_H,source + i*RAW_H               ,sizeof(short)*RAW_BLOCK_H);
    memcpy(b2+i*RAW_BLOCK_H,source + i*RAW_H+RGB_BLOCK_H   ,sizeof(short)*RAW_BLOCK_H);
    memcpy(b3+i*RAW_BLOCK_H,source + i*RAW_H+2*RGB_BLOCK_H ,sizeof(short)*RAW_BLOCK_H);
  }
}

void split_line_to_block(RawLine &source, RawBlock &b1, RawBlock &b2, RawBlock &b3) {
  split_line_to_block(source.m_raw_line, b1.m_raw_block, b2.m_raw_block, b3.m_raw_block);
}

// line_nb is numbered from 0
void get_line_from_img(raw_img &source, raw_line &dest, int line_nb){
  memcpy(dest,  source + line_nb*RAW_H*RGB_BLOCK_V, sizeof(raw_line));
}

void get_line_from_img(RawImg &source, RawLine &dest, int line_nb) {
  get_line_from_img(source.m_raw_img, dest.m_raw_line, line_nb);
}

// col_nb is numbered from 0
void get_block_from_line(raw_line &source, raw_block &dest, int col_nb){
  for(int i=0;i<RAW_BLOCK_V;i++){
    memcpy(dest+i*RAW_BLOCK_H,source + i*RAW_H +col_nb*RGB_BLOCK_H,sizeof(short)*RAW_BLOCK_H);
  }
}

void get_block_from_line(RawLine &source, RawBlock &dest, int col_nb) {
  get_block_from_line(source.m_raw_line, dest.m_raw_block, col_nb);
}

// idem
void join_block_into_line(rgb_block &source, rgb_line &dest, int col_nb){
  for(int i=0;i<RGB_BLOCK_V;i++){
    memcpy(dest+i*RGB_H +col_nb*RGB_BLOCK_H,source+i*RGB_BLOCK_H,sizeof(short)*RGB_BLOCK_H);
  }
}

void join_block_into_line(RgbBlock &source, RgbLine &dest, int col_nb) {
  join_block_into_line(source.m_rgb_block, dest.m_rgb_line, col_nb);
}


// idem
void join_line_into_img(rgb_line &source, rgb_img &dest, int line_nb){
  memcpy(dest+ line_nb*RGB_H*RGB_BLOCK_V,source, sizeof(rgb_line));
}

void join_line_into_img(RgbLine &source, RgbImg &dest, int line_nb) {
  join_line_into_img(source.m_rgb_line, dest.m_rgb_img, line_nb);
}


void copy_block(rgb_block &src, rgb_block &dest){
  memcpy(dest,src,sizeof(rgb_block));
}

void copy_block(RgbBlock &src, RgbBlock &dest) {
  copy_block(src.m_rgb_block, dest.m_rgb_block);
}

void copy_line(rgb_line &src, rgb_line &dest){
  memcpy(dest,src,sizeof(rgb_line));
}

void copy_line(RgbLine &src, RgbLine &dest) {
  copy_line(src.m_rgb_line, dest.m_rgb_line);
}

/* 
 * Calls the interpolation function to compute the r,g,b components from the
 * raw block. col and line are the indices (starting from 0) of the line and
 * column of the current block. These are needed to know which color is the
 * current pixel in the interpolation function.
 */
void demosaicing(raw_block &src, rgb_block &r, rgb_block &g, rgb_block &b,int col,int line){
  //ERROR_CODE err;
  ImageConfigType raw_cfg,rgb_cfg; 

  raw_cfg.Address[0]		= src;
  raw_cfg.Address[1]		= src;			/* no need */
  raw_cfg.Address[2]		= src;			/* no need */
  raw_cfg.AreaSizeH		= RAW_BLOCK_H;
  raw_cfg.AreaSizeV		= RAW_BLOCK_V;
  raw_cfg.ImageSizeH	        = RGB_BLOCK_H;
  raw_cfg.ImageSizeV		= RGB_BLOCK_V;
  raw_cfg.OffsetH		= 2;
  raw_cfg.OffsetV		= 2;
  raw_cfg.BayerPatn		= BAYER_GRBG;

  rgb_cfg.Address[0]		= r;
  rgb_cfg.Address[1]		= g;
  rgb_cfg.Address[2]		= b;
  rgb_cfg.AreaSizeH		= RGB_BLOCK_H ;
  rgb_cfg.AreaSizeV		= RGB_BLOCK_V ;
  rgb_cfg.ImageSizeH		= RGB_BLOCK_H ;
  rgb_cfg.ImageSizeV		= RGB_BLOCK_V ;
  rgb_cfg.OffsetH		= 0;
  rgb_cfg.OffsetV		= 0;
  rgb_cfg.BayerPatn		= 0;					/* no need */

  color_interpolation(&raw_cfg, &rgb_cfg, g_DemosaicFilterR, g_DemosaicFilterGr, g_DemosaicFilterGb, g_DemosaicFilterB, 2+RGB_BLOCK_V*line, 2+RGB_BLOCK_H*col);

}

void demosaicing(RawBlock &src, RgbBlock &r, RgbBlock &g, RgbBlock &b, int col, int line) {
  demosaicing(src.m_raw_block, r.m_rgb_block, g.m_rgb_block, b.m_rgb_block, col, line);
}


void output_img(rgb_img &img){
  for(int j=0;j<RGB_V;j++){
    for(int i=0;i<RGB_H;i++){
      printf("%hu, ",img[j*RGB_H+i]);
    }
    printf("\n");
  }
}

void output_img(RgbImg &img) {
  output_img(img.m_rgb_img);
}


RawImg::RawImg() {
}

RawImg::RawImg(const RawImg &rawImg) {
  memcpy(m_raw_img, rawImg.m_raw_img, sizeof(m_raw_img));
}

RawImg::~RawImg() {
}

RawImg &RawImg::operator=(const RawImg &rawImg) {
  if (this != &rawImg) {
    memcpy(m_raw_img, rawImg.m_raw_img, sizeof(m_raw_img));
  }
  return *this;
}


RawLine::RawLine() {
}

RawLine::RawLine(const RawLine &rawLine) {
  memcpy(m_raw_line, rawLine.m_raw_line, sizeof(m_raw_line));
}

RawLine::~RawLine() {
}

RawLine &RawLine::operator=(const RawLine &rawLine) {
  if (this != &rawLine) {
    memcpy(m_raw_line, rawLine.m_raw_line, sizeof(m_raw_line));
  }
  return *this;
}


RawBlock::RawBlock() {
}

RawBlock::RawBlock(const RawBlock &rawBlock) {
  memcpy(m_raw_block, rawBlock.m_raw_block, sizeof(m_raw_block));
}

RawBlock::~RawBlock() {
}

RawBlock &RawBlock::operator=(const RawBlock &rawBlock) {
  if (this != &rawBlock) {
    memcpy(m_raw_block, rawBlock.m_raw_block, sizeof(m_raw_block));
  }
  return *this;
}



RgbImg::RgbImg() {
}

RgbImg::RgbImg(const RgbImg &rgbImg) {
  memcpy(m_rgb_img, rgbImg.m_rgb_img, sizeof(m_rgb_img));
}

RgbImg::~RgbImg() {
}

RgbImg &RgbImg::operator=(const RgbImg &rgbImg) {
  if (this != &rgbImg) {
    memcpy(m_rgb_img, rgbImg.m_rgb_img, sizeof(m_rgb_img));
  }
  return *this;
}


RgbLine::RgbLine() {
}

RgbLine::RgbLine(const RgbLine &rgbLine) {
  memcpy(m_rgb_line, rgbLine.m_rgb_line, sizeof(m_rgb_line));
}

RgbLine::~RgbLine() {
}

RgbLine &RgbLine::operator=(const RgbLine &rgbLine) {
  if (this != &rgbLine) {
    memcpy(m_rgb_line, rgbLine.m_rgb_line, sizeof(m_rgb_line));
  }
  return *this;
}


RgbBlock::RgbBlock() {
}

RgbBlock::RgbBlock(const RgbBlock &rgbBlock) {
  memcpy(m_rgb_block, rgbBlock.m_rgb_block, sizeof(m_rgb_block));
}

RgbBlock::~RgbBlock() {
}

RgbBlock &RgbBlock::operator=(const RgbBlock &rgbBlock) {
  if (this != &rgbBlock) {
    memcpy(m_rgb_block, rgbBlock.m_rgb_block, sizeof(m_rgb_block));
  }
  return *this;
}
