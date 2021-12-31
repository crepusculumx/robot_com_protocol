//
// Created by crepusculumx on 2021/12/21.
//

#include "CrcCheck.h"

uint16_t CRC_crunch(char x, uint16_t g_accum) {
  uint16_t Gr1 = 0x0810;
  // Compute CRC using BitbyBit method
  int i;

  i = (x >> 7) & 1;
  if (g_accum & 0x8000) {
    g_accum = ((g_accum ^ Gr1) << 1) + (i ^ 1);
  } else {
    g_accum = (g_accum << 1) + i;
  }
  g_accum &= 0x0ffff;
  x <<= 1;
  //1
  i = (x >> 7) & 1;
  if (g_accum & 0x8000) {
    g_accum = ((g_accum ^ Gr1) << 1) + (i ^ 1);
  } else {
    g_accum = (g_accum << 1) + i;
  }
  g_accum &= 0x0ffff;
  x <<= 1;
  //2
  i = (x >> 7) & 1;
  if (g_accum & 0x8000) {
    g_accum = ((g_accum ^ Gr1) << 1) + (i ^ 1);
  } else {
    g_accum = (g_accum << 1) + i;
  }
  g_accum &= 0x0ffff;
  x <<= 1;
  //3
  i = (x >> 7) & 1;
  if (g_accum & 0x8000) {
    g_accum = ((g_accum ^ Gr1) << 1) + (i ^ 1);
  } else {
    g_accum = (g_accum << 1) + i;
  }
  g_accum &= 0x0ffff;
  x <<= 1;
  //4
  i = (x >> 7) & 1;
  if (g_accum & 0x8000) {
    g_accum = ((g_accum ^ Gr1) << 1) + (i ^ 1);
  } else {
    g_accum = (g_accum << 1) + i;
  }
  g_accum &= 0x0ffff;
  x <<= 1;
  //5
  i = (x >> 7) & 1;
  if (g_accum & 0x8000) {
    g_accum = ((g_accum ^ Gr1) << 1) + (i ^ 1);
  } else {
    g_accum = (g_accum << 1) + i;
  }
  g_accum &= 0x0ffff;
  x <<= 1;
  //6
  i = (x >> 7) & 1;
  if (g_accum & 0x8000) {
    g_accum = ((g_accum ^ Gr1) << 1) + (i ^ 1);
  } else {
    g_accum = (g_accum << 1) + i;
  }
  g_accum &= 0x0ffff;
  x <<= 1;
  //7
  i = (x >> 7) & 1;
  if (g_accum & 0x8000) {
    g_accum = ((g_accum ^ Gr1) << 1) + (i ^ 1);
  } else {
    g_accum = (g_accum << 1) + i;
  }
  g_accum &= 0x0ffff;
  x <<= 1;
  return g_accum;
}

uint16_t CRC16_check(const uint8_t data[], size_t length) {
  uint16_t g_accum = 0;

  for (size_t it = 0; it < length; it++) {
    g_accum = CRC_crunch(data[it], g_accum);
  }
  g_accum = CRC_crunch(0, g_accum);
  g_accum = CRC_crunch(0, g_accum);

  return g_accum;
}