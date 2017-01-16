#include <inttypes.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>


#include "typedefs.h"

#include "MCSAChannel.h"
#include "MCSAChunk.h"
#include "MCSAEvent.h"
#include "MCSAEvtParam.h"
#include "MCSAEvtRaw.h"
#include "MCSAEvtSpike.h"
#include "MCSAEvtTrigger.h"
#include "MCSAInfoFilter.h"
#include "MCSAInfoParam.h"
#include "MCSAInfoSpike.h"
#include "MCSAInfoTrigger.h"
#include "MCSAStream.h"
#include "MCSAStreamFile.h"
#include "MCSATimeStamp.h"
#include "MCSAStream.h"
#include "mat.h"
#include "matrix.h"
#include "mex.h"

using namespace std;

string getString(const mxArray *arg);
vector<string> GetChannelNames(CMCSAStream* stream);
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);
MATFile* CreateMatOutput(string outputDir, char* channel);
double* ReadRawData(CMCSAStream* Stream, int channelsInStream, long size);

string getString(const mxArray *arg) {
    size_t buflen = mxGetN(arg) + 1;
    char *buf = (char *) mxMalloc(buflen);
    mxGetString(arg, buf, (mwSize) buflen);
    return string(buf);
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  CMCSAStreamFile m_MCSFile;
  if (nrhs != 2) {
      mexErrMsgIdAndTxt("mcdtools:mcdtools:nrhs", "Inputs: sourceFile outputDir");
  }
  string csFileName = getString(prhs[0]);

  mexPrintf("Input file %s", csFileName.c_str());

  short sFileOpenResult = m_MCSFile.OpenFile(csFileName.c_str());

  if(sFileOpenResult > 0) {
    string s = "Error loading file: " + csFileName + "\n\n";

    switch(sFileOpenResult) {
      case 1:
        s += "File can not be opened.";
        break;
      case 2:
        s += "Wrong file format.";
        break;
      case 3:
        s += "Wrong file header.";
	      break;
      case 4:
        s += "Empty data file.";
	      break;
      default:
	      break;
    }
    mexErrMsgIdAndTxt("mcdtools:mcdtools:nrhs", s.c_str());
  }
  string outputDir(mxArrayToString(prhs[1]));

  system(("mkdir -p " + outputDir).c_str());

  char* bufferId = m_MCSFile.GetStream(0L)->GetBufferID();
  string streamId = "elec0001";
  long streamIndex = m_MCSFile.GetStreamIndexForStreamID((char*) streamId.c_str());
  CMCSAStream* Stream = m_MCSFile.GetStream(streamIndex);
  int channelsInStream = Stream->GetChannelCount();

  for (int i = 0; i < channelsInStream; ++i) {
    char* channel = Stream->GetChannel(i)->GetDecoratedName();
    MATFile* matFile = CreateMatOutput(outputDir, channel);
    long size = Stream->GetRawDataBufferSizeOfChannel();
    mxArray* pa = mxCreateDoubleMatrix(1, size, mxREAL);
    double* data = ReadRawData(Stream, i, size);
    memcpy((void *)(mxGetPr(pa)), (void *)data, sizeof(double) * size);
    matPutVariable(matFile, "data", pa);

    mwSize dims = 1;
    mxArray *channelNameArray = mxCreateString(channel);
    matPutVariable(matFile, "channel", channelNameArray);

    mxArray *samplingIntervalArray = mxCreateDoubleScalar(Stream->GetSampleRate());
    matPutVariable(matFile, "sr", samplingIntervalArray);

    matClose(matFile);
    mxDestroyArray(pa);
    mxDestroyArray(channelNameArray);
    mxDestroyArray(samplingIntervalArray);
    mxFree(data);
  }

  m_MCSFile.CloseFile();
}

MATFile* CreateMatOutput(string outputDir, char* channel) {
  MATFile *matFile;

  string file = outputDir + "/out_" + channel + ".mat" ;
  mexPrintf("Creating file %s...\n\n", file.c_str());
  matFile = matOpen(file.c_str(), "w");

  return matFile;
}


double* ReadRawData(CMCSAStream* Stream, int channel, long size) {
  int channelsInStream = Stream->GetChannelCount();

  int ADZero = Stream->GetADZero();
  double UnitsPerAD = Stream->GetUnitsPerAD();

  mexPrintf("Reading data for channel %d\n", channel);

  CMCSAChunk* currentChunk = Stream->GetFirstChunk();
  double* data = (double *) mxMalloc(sizeof(double) * size);
  short *buffer = (short *) mxMalloc(sizeof(short) * size);
  Stream->GetRawDataOfChannel(buffer, channel);
  for (int i = 0; i < size; ++i) {
    double realWordValue = (((unsigned short) buffer[i]) - ADZero) * UnitsPerAD;
    data[i] = realWordValue;
  }
  mxFree(buffer);
  return data;
}

