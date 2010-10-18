/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: WaveReader.cpp
 Creation date: 2010/08/10
 Author: Hélder Vasconcelos helder.vasc@e-2points.com 
 Description: Class Tester
 
 
 Copyright (c) 2010 Hélder Vasconcelos
 
 This library is free software; you can redistribute it and/or modify 
 it under the terms of the GNU Lesser General Public License as published by 
 the Free Software Foundation; either version 2.1 of the License, or 
 (at your option) any later version.
 
 This library is distributed in the hope that it will be useful, 
 but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License 
 for more details.
 
 You should have received a copy of the GNU Lesser General Public License 
 along with this library; if not, write to the Free Software Foundation, Inc., 
 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 
 
 ****************************************************************************/

#include "WavReader.h"

#include <stdio.h>
#include <stdexcept>
#include <string>
#include <cstring>
#include <assert.h>
#include <limits.h>

using namespace std;

WavReader::WavReader(const char *fileName)
{
   
	
	// Try to open the file for reading
    fptr = fopen(fileName, "rb");
    if (fptr == NULL) 
    {
        // didn't succeed
        string msg = "Error : Unable to open file \"";
        msg += fileName;
        msg += "\" for reading.";
        throw runtime_error(msg);
    }
	
    Init();
}


WavReader::WavReader(FILE *file)
{
    // Try to open the file for reading
    fptr = file;
    if (!file) 
    {
        // didn't succeed
        string msg = "Error : Unable to access input stream for reading";
        throw runtime_error(msg);
    }
	
    Init();
}


/// Init the WAV file stream
void WavReader::Init()
{
    int hdrsOk;
	
    // assume file stream is already open
    assert(fptr);
	
    // Read the file headers
    hdrsOk = ReadWavHeaders();
    if (hdrsOk != 0) 
    {
        // Something didn't match in the wav file headers 
        string msg = "Input file is corrupt or not a WAV file";
        throw runtime_error(msg);
    }
	
    if (header.format.fixed != 1)
    {
        string msg = "Input file uses unsupported encoding.";
        throw runtime_error(msg);
    }
	
    dataRead = 0;
}



WavReader::~WavReader()
{
    if (fptr) fclose(fptr);
    fptr = NULL;
}



void WavReader::Rewind()
{
    int hdrsOk;
	
    fseek(fptr, 0, SEEK_SET);
    hdrsOk = ReadWavHeaders();
    assert(hdrsOk == 0);
    dataRead = 0;
}


int WavReader::CheckCharTags() const
{
    // header.format.fmt should equal to 'fmt '
    if (memcmp(fmtStr, header.format.fmt, 4) != 0) return -1;
    // header.data.data_field should equal to 'data'
    if (memcmp(dataStr, header.data.data_field, 4) != 0) return -1;
	
    return 0;
}


int WavReader::Read(char *buffer, int maxElems)
{
    int numBytes;
    UInt32 afterDataRead;
	
    // ensure it's 8 bit format
    if (header.format.bits_per_sample != 8)
    {
        throw runtime_error("Error: WavInFile::read(char*, int) works only with 8bit samples.");
    }
    assert(sizeof(char) == 1);
	
    numBytes = maxElems;
    afterDataRead = dataRead + numBytes;
    if (afterDataRead > header.data.data_len) 
    {
        // Don't read more samples than are marked available in header
        numBytes = (int)header.data.data_len - (int)dataRead;
        assert(numBytes >= 0);
    }
	
    assert(buffer);
    numBytes = fread(buffer, 1, numBytes, fptr);
    dataRead += numBytes;
	
    return numBytes;
}


int WavReader::Read(short *buffer, int maxElems)
{
    unsigned int afterDataRead;
    int numBytes;
    int numElems;
	
    assert(buffer);
    if (header.format.bits_per_sample == 8)
    {
        // 8 bit format
        char *temp = new char[maxElems];
        int i;
		
        numElems = (int)Read(temp, maxElems);
        // convert from 8 to 16 bit
        for (i = 0; i < numElems; i ++)
        {
            buffer[i] = temp[i] << 8;
        }
        delete[] temp;
    }
    else
    {
        // 16 bit format
        assert(header.format.bits_per_sample == 16);
        assert(sizeof(short) == 2);
		
        numBytes = maxElems * 2;
        afterDataRead = dataRead + numBytes;
        if (afterDataRead > header.data.data_len) 
        {
            // Don't read more samples than are marked available in header
            numBytes = (int)header.data.data_len - (int)dataRead;
            assert(numBytes >= 0);
        }
		
        numBytes = fread(buffer, 1, numBytes, fptr);
        dataRead += numBytes;
        numElems = numBytes / 2;
		
        // 16bit samples, swap byte order if necessary
        _swap16Buffer((unsigned short *)buffer, numElems);
    }
	
    return numElems;
}



int WavReader::Read(float *buffer, int maxElems)
{
    short *temp = new short[maxElems];
    int num;
    int i;
    double fscale;
	
    num = Read(temp, maxElems);
	
    fscale = 1.0 / 32768.0;
    // convert to floats, scale to range [-1..+1[
    for (i = 0; i < num; i ++)
    {
        buffer[i] = (float)(fscale * (double)temp[i]);
    }
	
    delete[] temp;
	
    return num;
}


int WavReader::Eof() const
{
    // return true if all data has been read or file eof has reached
    return (dataRead == header.data.data_len || feof(fptr));
}



// test if character code is between a white space ' ' and little 'z'
static int IsAlpha(char c)
{
    return (c >= ' ' && c <= 'z') ? 1 : 0;
}


// test if all characters are between a white space ' ' and little 'z'
static int IsAlphaStr(const char *str)
{
    char c;
	
    c = str[0];
    while (c) 
    {
        if (IsAlpha(c) == 0) return 0;
        str ++;
        c = str[0];
    }
	
    return 1;
}






int WavReader::ReadRIFFBlock()
{
    if (fread(&(header.riff), sizeof(WavRiff), 1, fptr) != 1) return -1;
	
    // swap 32bit data byte order if necessary
    _swap32((unsigned int &)header.riff.package_len);
	
    // header.riff.riff_char should equal to 'RIFF');
    if (memcmp(riffStr, header.riff.riff_char, 4) != 0) return -1;
    // header.riff.wave should equal to 'WAVE'
    if (memcmp(waveStr, header.riff.wave, 4) != 0) return -1;
	
    return 0;
}




int WavReader::ReadHeaderBlock()
{
    char label[5];
    string sLabel;
	
    // lead label string
    if (fread(label, 1, 4, fptr) !=4) return -1;
    label[4] = 0;
	
    if (IsAlphaStr(label) == 0) return -1;    // not a valid label
	
    // Decode blocks according to their label
    if (strcmp(label, fmtStr) == 0)
    {
        int nLen, nDump;
		
        // 'fmt ' block 
        memcpy(header.format.fmt, fmtStr, 4);
		
        // read length of the format field
        if (fread(&nLen, sizeof(int), 1, fptr) != 1) return -1;
        // swap byte order if necessary
        _swap32((unsigned int &)nLen); // int format_len;
        header.format.format_len = nLen;
		
        // calculate how much length differs from expected
        nDump = nLen - ((int)sizeof(header.format) - 8);
		
        // if format_len is larger than expected, read only as much data as we've space for
        if (nDump > 0)
        {
            nLen = sizeof(header.format) - 8;
        }
		
        // read data
        if (fread(&(header.format.fixed), nLen, 1, fptr) != 1) return -1;
		
        // swap byte order if necessary
        _swap16((unsigned short &)header.format.fixed);            // short int fixed;
        _swap16((unsigned short &)header.format.channel_number);   // short int channel_number;
        _swap32((unsigned int   &)header.format.sample_rate);      // int sample_rate;
        _swap32((unsigned int   &)header.format.byte_rate);        // int byte_rate;
        _swap16((unsigned short &)header.format.byte_per_sample);  // short int byte_per_sample;
        _swap16((unsigned short &)header.format.bits_per_sample);  // short int bits_per_sample;
		
        // if format_len is larger than expected, skip the extra data
        if (nDump > 0)
        {
            fseek(fptr, nDump, SEEK_CUR);
        }
		
        return 0;
    }
    else if (strcmp(label, dataStr) == 0)
    {
        // 'data' block
        memcpy(header.data.data_field, dataStr, 4);
        if (fread(&(header.data.data_len), sizeof(UInt32), 1, fptr) != 1) return -1;
		
        // swap byte order if necessary
        _swap32((unsigned int &)header.data.data_len);
		
        return 1;
    }
    else
    {
        UInt32 len, i;
        UInt32 temp;
        // unknown block
		
        // read length
        if (fread(&len, sizeof(len), 1, fptr) != 1) return -1;
        // scan through the block
        for (i = 0; i < len; i ++)
        {
            if (fread(&temp, 1, 1, fptr) != 1) return -1;
            if (feof(fptr)) return -1;   // unexpected eof
        }
    }
    return 0;
}


int WavReader::ReadWavHeaders()
{
    int res;
	
    memset(&header, 0, sizeof(header));
	
    res = ReadRIFFBlock();
    if (res) return 1;
    // read header blocks until data block is found
    do
    {
        // read header blocks
        res = ReadHeaderBlock();
        if (res < 0) return 1;  // error in file structure
    } while (res == 0);
    // check that all required tags are legal
    return CheckCharTags();
}


UInt32 WavReader::GetNumChannels() const
{
    return header.format.channel_number;
}


UInt32 WavReader::GetNumBits() const
{
    return header.format.bits_per_sample;
}


UInt32 WavReader::GetBytesPerSample() const
{
    return GetNumChannels() * GetNumBits() / 8;
}


UInt32 WavReader::GetSampleRate() const
{
    return header.format.sample_rate;
}



UInt32 WavReader::GetDataSizeInBytes() const
{
    return header.data.data_len;
}


UInt32 WavReader::GetNumSamples() const
{
    if (header.format.byte_per_sample == 0) return 0;
    return header.data.data_len / (unsigned short)header.format.byte_per_sample;
}


UInt32 WavReader::GetLengthMS() const
{
	UInt32 numSamples;
	UInt32 sampleRate;
	
	numSamples = GetNumSamples();
	sampleRate = GetSampleRate();
	
	assert(numSamples < UINT_MAX / 1000);
	return (1000 * numSamples / sampleRate);
}





