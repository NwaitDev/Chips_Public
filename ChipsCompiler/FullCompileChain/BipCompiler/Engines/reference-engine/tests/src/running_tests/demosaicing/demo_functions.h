#ifndef _SIZE_H_
#define _SIZE_H_ 

#include<string.h>

// the two parameters below determine how the image is splitted
// changing them requires to change the associated bip model
#include "timeout.h"

#include <iostream>
#include <string>

#define NB_COL 3
#define NB_LINE 3
// RAW_H and RAW_V must be set to the size of the source image
// to have blocks of the same size, we require that 
//   RAW_H - 4 % NB_COL == 0
//   RAW_V - 4 % NB_LINE == 0
// the function load_img generates a test image from that size (by duplicating the raw_data_648)
#define RAW_H 2500
#define RAW_V 2500

// remaining constants should not be changed  
#define RGB_H (RAW_H - 4)
#define RGB_V (RAW_V - 4)
#define RGB_BLOCK_H (RGB_H/NB_COL)
#define RGB_BLOCK_V (RGB_V/NB_LINE)
#define RAW_BLOCK_H (RGB_BLOCK_H + 4)
#define RAW_BLOCK_V (RGB_BLOCK_V + 4)

// types for raw image, line and block
typedef short raw_img[RAW_H*RAW_V];
typedef short raw_line[RAW_H*RAW_BLOCK_V];
typedef short raw_block[RAW_BLOCK_H*RAW_BLOCK_V];

// types for each of the 3 (r,g and b) output image line and  block
typedef short rgb_img[RGB_H*RGB_V];
typedef short rgb_line[RGB_H*RGB_BLOCK_V];
typedef short rgb_block[RGB_BLOCK_H*RGB_BLOCK_V];

// print functions
void print(const std::string &s, int v1);
void print(const std::string &s, int v1, int v2);


// wrappers for types [raw|rgb]_[img|line|block]
class RawImg {
 public:
  RawImg();
  RawImg(const RawImg &rawImg);
  ~RawImg();

  RawImg &operator=(const RawImg &rawImg);

  raw_img m_raw_img;
};

class RawLine {
 public:
  RawLine();
  RawLine(const RawLine &rawLine);
  ~RawLine();

  RawLine &operator=(const RawLine &rawLine);

  raw_line m_raw_line;
};

class RawBlock {
 public:
  RawBlock();
  RawBlock(const RawBlock &rawBlock);
  ~RawBlock();

  RawBlock &operator=(const RawBlock &rawBlock);

  raw_block m_raw_block;
};


class RgbImg {
 public:
  RgbImg();
  RgbImg(const RgbImg &rgbImg);
  ~RgbImg();

  RgbImg &operator=(const RgbImg &rgbImg);

  rgb_img m_rgb_img;
};

class RgbLine {
 public:
  RgbLine();
  RgbLine(const RgbLine &rgbLine);
  ~RgbLine();

  RgbLine &operator=(const RgbLine &rgbLine);

  rgb_line m_rgb_line;
};

class RgbBlock {
 public:
  RgbBlock();
  RgbBlock(const RgbBlock &rgbBlock);
  ~RgbBlock();

  RgbBlock &operator=(const RgbBlock &rgbBlock);

  rgb_block m_rgb_block;
};

// function to load ihe initial image (from the disk ?)
void load_img(int index,raw_img &new_img);
void load_img(int index, RawImg &newImg);

// functions that split img into lines and lines into blocks
void split_img_to_line(raw_img &source, raw_line &l1, raw_line &l2, raw_line &l3);
void split_img_to_line(RawImg &source, RawLine &l1, RawLine &l2, RawLine &l3);

void split_line_to_block(raw_line &source, raw_block &b1, raw_block &b2, raw_block &b3);
void split_line_to_block(RawLine &source, RawBlock &b1, RawBlock &b2, RawBlock &b3);

// function that get a specific raw_line (resp raw_block) from a raw_img (resp
// raw_line)
void get_line_from_img(raw_img &source, raw_line &dest, int line_nb);
void get_line_from_img(RawImg &source, RawLine &dest, int line_nb);

void get_block_from_line(raw_line &source, raw_block &dest, int col_nb);
void get_block_from_line(RawLine &source, RawBlock &dest, int col_nb);

// function that takes a raw block and generates the corresponding r,g and b
// blocks 
void demosaicing(raw_block &src, rgb_block &r, rgb_block &g, rgb_block &b, int col, int line);
void demosaicing(RawBlock &src, RgbBlock &r, RgbBlock &g, RgbBlock &b, int col, int line);

// function that writes data from one block to the right place in a line
void join_block_into_line(rgb_block &source, rgb_line &dest, int col_nb);
void join_block_into_line(RgbBlock &source, RgbLine &dest, int col_nb);

// function that writes data from a line in the right place in img
void join_line_into_img(rgb_line &source, rgb_img &dest, int line_nb);
void join_line_into_img(RgbLine &source, RgbImg &dest, int line_nb);

void copy_block(rgb_block &src, rgb_block &dest);
void copy_block(RgbBlock &src, RgbBlock &dest);

void copy_line(rgb_line &src, rgb_line &dest);
void copy_line(RgbLine &src, RgbLine &dest);

void output_img(rgb_img &img);
void output_img(RgbImg &img);


#endif
