#ifndef _DATA_PROCESS_H
#define _DATA_PROCESS_H

#include <vector>
#include <complex>
#include <cmath>

using namespace std;

#define WAV_HEAD_LONG 44
#define FS 16000
#define OK 0
#define ERROR -1

/**
 * 函数描述：       加载音频文件
 * 参数描述：       filename            文件名
 *                 data_normalized     传出来处理后的数据数组
 * 返回值  ：       加载是否成功，0表示成功，否则失败
 **/
vector<float> file_load(char *filename);
/**
 * 函数描述：       加载音频文件
 * 参数描述：       filename            文件名
 *                 data_normalized     传出来处理后的数据数组
 * 返回值  ：       加载是否成功，0表示成功，否则失败
 **/
vector<vector<float>> data_process(char *filename ,int n_fft ,int hopLength ,double sampleRate);







#endif