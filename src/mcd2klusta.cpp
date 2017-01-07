#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

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

using namespace std;

void ReadRawData(CMCSAStream* Stream, int channelsInStream, vector<shared_ptr<ofstream> > outputFiles);


int main(int argc, char **argv) {
  CMCSAStreamFile m_MCSFile;

  if (argc != 3) {
	  printf("Usage: filepath.mcd outputdir\n");
	  exit(0);
  }
  string csFileName(argv[1]);
  string outputDir(argv[2]);


  short sFileOpenResult = m_MCSFile.OpenFile(csFileName.c_str());

  if(sFileOpenResult > 0) {
    std::string s;
    s = "Error loading file: " + csFileName + "\n\n";

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
    cout << s << endl;
    exit(0);
  }

  mkdir(outputDir.c_str(), S_IRWXU);

  string streamId = "elec0001";
  long streamIndex = m_MCSFile.GetStreamIndexForStreamID((char*) streamId.c_str());

  CMCSAStream* Stream = m_MCSFile.GetStream(streamIndex);
  cout << "Channels in stream: " << Stream->GetChannelCount() << endl;

  int channelsInStream = Stream->GetChannelCount();

  vector<shared_ptr<ofstream> > outputFiles;
  outputFiles.push_back(shared_ptr<ofstream>(new ofstream(outputDir + "/out.dat", ios::binary | ios::out)));

  cout << "MEA Channels layout:" << endl;
  for (int i = 0; i < channelsInStream; ++i) {
    printf("%d: (%d, %d),\n", i, Stream->GetRelativeChannelPosX(i), Stream->GetRelativeChannelPosY(i));
  }

  ReadRawData(Stream, channelsInStream, outputFiles);

  m_MCSFile.CloseFile();
}

vector<shared_ptr<ofstream> > CreateOutputStreams(string outputDir, int channelsInStream) {
  vector<shared_ptr<ofstream> > outputFiles(channelsInStream);
  for (int i = 0; i < channelsInStream; ++i) {
    string filename = outputDir + "/" + to_string(i) + ".dat";
    outputFiles[i] = shared_ptr<ofstream>(
            new ofstream(filename, ios::binary | ios::out));
  }
  return outputFiles;
}

void ReadRawData(CMCSAStream* Stream, int channelsInStream, vector<shared_ptr<ofstream> > outputFiles) {
    int ADZero = Stream->GetADZero();
    double UnitsPerAD = Stream->GetUnitsPerAD();

    CMCSAChunk* currentChunk = Stream->GetFirstChunk();

    while (currentChunk) {
      CMCSATimeStamp* toTimestamp = currentChunk->GetTimeStampFrom();
      cout << "Processing from second: " << toTimestamp->GetSecondFromStart() << "\r";
      if (toTimestamp->GetSecondFromStart() > 2) {
          return;
      }

      long bufferSize = currentChunk->GetSize();
      short* buffer = new short[bufferSize];
      currentChunk->ReadData(buffer);
      currentChunk = Stream->GetNextChunk(currentChunk);
      for (int i = 0; i < bufferSize; ++i) {
        int channel = i % channelsInStream;
        double realWordValue = (((unsigned short) buffer[i]) - ADZero) * UnitsPerAD;
        int16_t value = (int16_t) (realWordValue * 1000000);
        char* valueBytes = static_cast<char*>(static_cast<void*>(&value));
        (*outputFiles[channel % outputFiles.size()]) <<  valueBytes;
      }
      delete[] buffer;
    }
}

