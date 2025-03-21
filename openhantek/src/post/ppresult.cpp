// SPDX-License-Identifier: GPL-2.0+

#include "ppresult.h"
#include <QDebug>
#include <stdexcept>

PPresult::PPresult(unsigned int channelCount) { analyzedData.resize(channelCount); }

const DataChannel *PPresult::data(ChannelID channel) const {
    if (channel >= this->analyzedData.size()) return 0;

    return &this->analyzedData[(size_t)channel];
}

DataChannel *PPresult::modifyData(ChannelID channel) { return &this->analyzedData[(size_t)channel]; }

unsigned int PPresult::sampleCount() const {
    // Figure out which channel has all the fast rate samples
    if ((unsigned)analyzedData.size() > 1) {
        if ((unsigned)analyzedData[0].voltage.sample.size() == 0 &&
            (unsigned)analyzedData[1].voltage.sample.size() > 10240) {
            // channel 2 has all the samples
            return (unsigned)analyzedData[1].voltage.sample.size();
        }
    }
    return (unsigned)analyzedData[0].voltage.sample.size();
}

unsigned int PPresult::channelCount() const { return (unsigned)analyzedData.size(); }
