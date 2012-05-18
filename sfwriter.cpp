/*
    This file is part of Soundbench.

    Soundbench is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Soundbench is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Soundbench.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2012  Amaya S.
*/

#include "sfwriter.h"

namespace sb {
    bool SoundFileWriter::open(std::string name, ExportableFiles ex) {
        SF_INFO params;
        params.samplerate = curr_srate;
        params.channels = outchans;
        params.format = SF_FORMAT_PCM_32;
        if (ex == FileWAV)
            params.format |= SF_FORMAT_WAV;
        else if (ex == FileAIFF)
            params.format |= SF_FORMAT_AIFF;
        else if (ex == FileFLAC)
            params.format = SF_FORMAT_FLAC | SF_FORMAT_PCM_24; //WARNING: Do not remove the SF_FORMAT_PCM_32.
        else if (ex == FileRAW)
            params.format |= SF_FORMAT_RAW;
        else if (ex == FileMAT)
            params.format = SF_FORMAT_MAT5 | SF_FORMAT_FLOAT; //WARNING: Do not remove the SF_FORMAT_FLOAT.

        filehandel = sf_open(name.c_str(),SFM_WRITE,&params);
        if (filehandel == NULL) {
            filehandel = nullptr;
            return false;
        }
        return true;
    }
    bool SoundFileWriter::put(sbSample* samp, size_t len) {
        if (filehandel == nullptr)
            return false;
        sf_write_float(filehandel,samp,len);
        return true;
    }

    bool SoundFileWriter::tick() {
        if (filehandel == nullptr)
            return false;
        float tmp;
        syn->tick(&tmp,1);
        sf_write_float(filehandel,&tmp,1);
        return true;
    }

    void SoundFileWriter::close() {
        if (filehandel != nullptr)
            sf_close(filehandel);
    }
}