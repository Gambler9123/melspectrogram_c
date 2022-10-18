#include <iostream>
#include <string>
#include "librosamel_and_mfcc.h"

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
vector<float> file_load(char *filename)
{
    FILE *fp;
    uint8_t ret = 0;
    uint32_t i = 0;
    int16_t data[176000] = {0};
    vector<float> audio;
    // 进行文件读出操作
    fp = fopen(filename,"rb");
    if(NULL == fp){
        printf("open file error\n");
    }
    ret = fseek(fp,WAV_HEAD_LONG,SEEK_CUR);
    if(0 != ret){
        printf("fseek file error\n");
    }

    // 没判返回值，返回值不规律，但读出来是对的
    fread(data,2,176000,fp);
    fclose(fp);

    // 进行归一化处理，带符号
    for(i = 0;i < 176000;i++)
        audio.push_back((float)data[i] / 32767);

    return audio;
}



int main()
{
    uint8_t ret = 0;
    char filename[] = "normal_id_01_00000000.wav";
    int hopLength = 512;
    int n_fft = 1024;
    double sampleRate = 16000;
    int frames = 5;
    int mels = 128;
    int dims = mels * frames;
    

// 加载wav文件，并对数据归一化处理,16000采样率，16bit采样，单通道
    auto audio = file_load(filename);

    if(0 == audio.size()){
        printf("file load error\n");
        return ERROR;   
    }
    
    Lib_Mfcc lib;
    auto data_to_mel = lib.domelspectrogram(audio,hopLength,n_fft,sampleRate);

    int row = data_to_mel.size();
    int col = data_to_mel[0].size();
    vector<vector<float>> log_mel_spectrogram(row,vector<float>(col));
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            log_mel_spectrogram[i][j] = 20 / 2 *log10(data_to_mel[i][j]);
        }
    }

    int vector_array_size = data_to_mel[0].size() - frames + 1;
    if (vector_array_size < 1)
        return ERROR;
    vector<vector<float>> vector_array(vector_array_size,vector<float>(dims));
    vector<vector<float>> log_mel_spectrogram_t(col,vector<float>(row));
    // 矩阵转置
    for (int i = 0; i < log_mel_spectrogram.size(); i++){
    for (int j = 0; j < log_mel_spectrogram[0].size(); j++){
            log_mel_spectrogram_t[j][i] = log_mel_spectrogram[i][j];
        }
    }
    // 矩阵拼接,将5帧拼成640维，即 dims = mels * frames
    for (int k = 0; k < frames; k++){
        for (int i = 0; i < vector_array.size(); i++){
            for (int j = 0; j < log_mel_spectrogram_t[0].size(); j++){
            vector_array[i][j + k * mels] = log_mel_spectrogram_t[i + k][j];
            }
        }
    }
    
    return 0;
}




// #ifdef __cplusplus
// }
// #endif
