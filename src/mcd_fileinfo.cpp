#include <stdlib.h>

#include <cstring>
#include <memory>
#include <string>
#include <vector>


#include "typedefs.h"

#include "MCSAChannel.h"
#include "MCSAStream.h"
#include "MCSAStream.h"
#include "mat.h"
#include "mex.h"

using namespace std;

string getString(const mxArray *arg);
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);

string getString(const mxArray *arg) {
    size_t buflen = mxGetN(arg) + 1;
    char *buf = (char *) mxMalloc(buflen);
    mxGetString(arg, buf, (mwSize) buflen);
    return string(buf);
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  CMCSAStreamFile m_MCSFile;
  if (nrhs != 1) {
      mexErrMsgIdAndTxt("mcdtools:mcdtools:nrhs", "Inputs: mcd_file");
  }
  if (nlhs > 1) {
      mexErrMsgIdAndTxt("mcdtools:mcdtools:nlhs", "Outputs: [par] file info struct");
  }

  string csFileName = getString(prhs[0]);

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
    return;
  }

  string streamId = "elec0001";
  long streamIndex = m_MCSFile.GetStreamIndexForStreamID((char*) streamId.c_str());
  CMCSAStream* Stream = m_MCSFile.GetStream(streamIndex);
  long channelsCount = Stream->GetChannelCount();

  const char *fieldnames[3] = {
      "channels_count",
      "sample_rate",
      "channel_names"
  };
  mxArray *result = mxCreateStructMatrix(1, 1, 3, fieldnames);
  //fieldnames[2] = (char*)mxMalloc(20);

  mxSetFieldByNumber(result, 0, 0, mxCreateDoubleScalar(channelsCount));
  mxSetFieldByNumber(result, 0, 1, mxCreateDoubleScalar(Stream->GetSampleRate()));

  int dims[] = {(int) channelsCount};
  mxArray* channelNameArray = mxCreateCellArray(1, dims);
  for (int i = 0; i < channelsCount; ++i) {
    mxSetCell(channelNameArray, i, mxCreateString( Stream->GetChannel(i)->GetDecoratedName()));
  }
  mxSetFieldByNumber(result, 0, 2, channelNameArray);
  m_MCSFile.CloseFile();

  plhs[0] = result;
}

