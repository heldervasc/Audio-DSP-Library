/*
 *  Writer.cpp
 *  Library
 *
 *  Created by Helder Vasconcelos on 10/10/05.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "WavWriter.h"

#include <stdio.h>
#include <stdexcept>
#include <string>
#include <cstring>
#include <assert.h>
#include <limits.h>

using namespace std;

WavWriter::WavWriter(const char *fileName, int sampleRate, int bits, int channels)
{
    BytesWritten = 0;
    fptr = fopen(fileName, "wb");
    if (fptr == NULL) 
    {
        string msg = "Error : Unable to open file \"";
        msg += fileName;
        msg += "\" for writing.";
        //pmsg = msg.c_str;
        throw runtime_error(msg);
    }
	
    FillInHeader(sampleRate, bits, channels);
    WriteHeader();
}


WavWriter::WavWriter(FILE *file, int sampleRate, int bits, int channels)
{
    BytesWritten = 0;
    fptr = file;
    if (fptr == NULL) 
    {
        string msg = "Error : Unable to access output file stream.";
        throw runtime_error(msg);
    }
	
    FillInHeader(sampleRate, bits, channels);
    WriteHeader();
}



WavWriter::~WavWriter()
{
    FinishHeader();
    if (fptr) fclose(fptr);
    fptr = NULL;
}



void WavWriter::FillInHeader(UInt32 sampleRate, UInt32 bits, UInt32 channels)
{
    // fill in the 'riff' part..
	
    // copy string 'RIFF' to riff_char
    memcpy(&(header.riff.riff_char), riffStr, 4);
    // package_len unknown so far
    header.riff.package_len = 0;
    // copy string 'WAVE' to wave
    memcpy(&(header.riff.wave), waveStr, 4);
	
	
    // fill in the 'format' part..
	
    // copy string 'fmt ' to fmt
    memcpy(&(header.format.fmt), fmtStr, 4);
	
    header.format.format_len = 0x10;
    header.format.fixed = 1;
    header.format.channel_number = (short)channels;
    header.format.sample_rate = (int)sampleRate;
    header.format.bits_per_sample = (short)bits;
    header.format.byte_per_sample = (short)(bits * channels / 8);
    header.format.byte_rate = header.format.byte_per_sample * (int)sampleRate;
    header.format.sample_rate = (int)sampleRate;
	
    // fill in the 'data' part..
	
    // copy string 'data' to data_field
    memcpy(&(header.data.data_field), dataStr, 4);
    // data_len unknown so far
    header.data.data_len = 0;
}


void WavWriter::FinishHeader()
{
    // supplement the file length into the header structure
    header.riff.package_len = BytesWritten + 36;
    header.data.data_len = BytesWritten;
	
    WriteHeader();
}



void WavWriter::WriteHeader()
{
    WavHeader hdrTemp;
    int res;
	
    // swap byte order if necessary
    hdrTemp = header;
    _swap32((unsigned int   &)hdrTemp.riff.package_len);
    _swap32((unsigned int   &)hdrTemp.format.format_len);
    _swap16((unsigned short &)hdrTemp.format.fixed);
    _swap16((unsigned short &)hdrTemp.format.channel_number);
    _swap32((unsigned int   &)hdrTemp.format.sample_rate);
    _swap32((unsigned int   &)hdrTemp.format.byte_rate);
    _swap16((unsigned short &)hdrTemp.format.byte_per_sample);
    _swap16((unsigned short &)hdrTemp.format.bits_per_sample);
    _swap32((unsigned int   &)hdrTemp.data.data_len);
	
    // write the supplemented header in the beginning of the file
    fseek(fptr, 0, SEEK_SET);
    res = fwrite(&hdrTemp, sizeof(hdrTemp), 1, fptr);
    if (res != 1)
    {
        throw runtime_error("Error while writing to a wav file.");
    }
	
    // jump back to the end of the file
    fseek(fptr, 0, SEEK_END);
}



void WavWriter::Write(const char *buffer, int numElems)
{
    int res;
	
    if (header.format.bits_per_sample != 8)
    {
        throw runtime_error("Error: WavOutFile::write(const char*, int) accepts only 8bit samples.");
    }
    assert(sizeof(char) == 1);
	
    res = fwrite(buffer, 1, numElems, fptr);
    if (res != numElems) 
    {
        throw runtime_error("Error while writing to a wav file.");
    }
	
    BytesWritten += numElems;
}


void WavWriter::Write(const short *buffer, int numElems)
{
    int res;
	
    // 16 bit samples
    if (numElems < 1) return;   // nothing to do
	
    if (header.format.bits_per_sample == 8)
    {
        int i;
        char *temp = new char[numElems];
        // convert from 16bit format to 8bit format
        for (i = 0; i < numElems; i ++)
        {
            temp[i] = buffer[i] >> 8;
        }
        // write in 8bit format
        Write(temp, numElems);
        delete[] temp;
    }
    else
    {
        // 16bit format
        unsigned short *pTemp = new unsigned short[numElems];
		
        assert(header.format.bits_per_sample == 16);
		
        // allocate temp buffer to swap byte order if necessary
        memcpy(pTemp, buffer, numElems * 2);
        _swap16Buffer(pTemp, numElems);
		
        res = fwrite(pTemp, 2, numElems, fptr);
		
        delete[] pTemp;
		
        if (res != numElems) 
        {
            throw runtime_error("Error while writing to a wav file.");
        }
        BytesWritten += 2 * numElems;
    }
}


void WavWriter::Write(const float *buffer, int numElems)
{
    int i;
    short *temp = new short[numElems];
    int iTemp;
	
    // convert to 16 bit integer
    for (i = 0; i < numElems; i ++)
    {
        // convert to integer
        iTemp = (int)(32768.0f * buffer[i]);
		
        // saturate
        if (iTemp < -32768) iTemp = -32768;
        if (iTemp > 32767)  iTemp = 32767;
        temp[i] = (short)iTemp;
    }
	
    Write(temp, numElems);
	
    delete[] temp;
}

