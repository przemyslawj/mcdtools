#ifndef MCDIO_H
#define MCDIO_H

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

void ReadRawData(
        CMCSAStream* Stream,
        int channel,
        long size,
        short* buffer,
        double* output);

#endif
