#include "audio.h"

AudioProcess::AudioProcess() {
  // dataIn = new float[BUFFER_SIZE];
  dataOut = new float[BUFFER_SIZE];
  alignRamp = new float[BUFFER_SIZE];
  dataSize = BUFFER_SIZE;
  i = 0;
}

AudioProcess::~AudioProcess() {
  // delete[] dataIn;
  delete[] dataOut;
  delete[] alignRamp;
  dataIn = NULL; dataOut = NULL;
  alignRamp = NULL;
}

void AudioProcess::writeDataIn(float *d) {
  dataIn = d;
}

float *AudioProcess::getDataOut() {
  return dataOut;
}

float *AudioProcess::getDataIn() {
  return dataIn;
}

void AudioProcess::derive() {
  dataOut[i] = 0;
  for (i=1; i<dataSize; i++) {
    dataOut[i] = dataIn[i] - dataIn[i-1];
  }
}

void AudioProcess::integrate() {
  dataOut[0] = dataIn[0];
  for (i=1; i<dataSize; i++) {
    dataOut[i] = dataOut[i-1] + dataIn[i];
  }
}

float *AudioProcess::alignWave(float trigger, unsigned long int waveLen, long int offset, bool edge=false) {
  unsigned long int i = dataSize - waveLen + offset;
  // (void)edge;
  // while (dataIn[i] - trigger < 0) i++;
  // alignRamp[i] = 0;
  // for (i=0;i<dataSize;i++) {
  //   alignRamp[i] = alignRamp[i-1] + 1;
  // }

  for (i = 0; i<dataSize; i++) {
    alignRamp[i]=2*(float)i/dataSize-1;
  }
  return alignRamp;
}