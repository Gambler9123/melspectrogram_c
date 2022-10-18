#include <iostream>
#include <string>
#include "librosamel_and_mfcc.h"
#include "data_process.h"

using namespace std;

#define WAV_HEAD_LONG 44
#define FS 16000
#define OK 0
#define ERROR -1

// #ifdef __cplusplus
// extern "C" {
// #endif

/**
 * 函数描述：       加载音频文件
 * 参数描述：       filename            文件名
 *                 data_normalized     传出来处理后的数据数组
 * 返回值  ：       加载是否成功，0表示成功，否则失败
 **/

int main()
{
    char filename[] = "normal_id_01_00000000.wav";
    int hopLength = 512;
    int n_fft = 1024;
    double sampleRate = 16000;
    auto data = data_process(filename ,n_fft ,hopLength ,sampleRate);

    return 0;
}




// #ifdef __cplusplus
// }
// #endif
