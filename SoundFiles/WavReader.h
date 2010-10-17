/*
 *  WavReader.h
 *  Library
 *
 *  Created by Helder Vasconcelos on 10/10/05.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef WAVEREADER_H
#define WAVEREADER_H


#include <stdio.h>
#include "Utils.h"

typedef unsigned int UInt32 ;

static const char riffStr[] = "RIFF";
static const char waveStr[] = "WAVE";
static const char fmtStr[]  = "fmt ";
static const char dataStr[] = "data";

/*

 Wavfile Specification

 Riff Chunk
 ---------------------------------------------------------------------------------------------
 |   ckid(4) =RIFF   |  cksize(4+N)	|   waveid (4)   | Wave Chunks(N))=Format Chunk + Data Chunk |
 ---------------------------------------------------------------------------------------------
 
 
 Format Chunk
 ------------------------
 |   ckid(4)			|	
 ------------------------
 ------------------------
 |   len(4)				|
 ------------------------
 ------------------------
 |   Format code(2)		|
 ------------------------
 ------------------------
 |   nChannels(2)		|
 ------------------------
 ------------------------------------
 |   nSamplesPerSec(4)				|	Sampling rate (blocks per second)
 ------------------------------------
 --------------------------------
 |   nAvgBytesPerSec	(4)		|	Data rate
 -------------------------------
 ----------------------------
 |   nBlockAlign	(2)		|		Data block size (bytes)
 ----------------------------
 ----------------------------
 |   wBitsPerSample	(2)		|		Bits per sample
 ----------------------------
 
 Format Code 
 
 0x0001	WAVE_FORMAT_PCM	PCM
 0x0003	WAVE_FORMAT_IEEE_FLOAT	IEEE float
 0x0006	WAVE_FORMAT_ALAW	8-bit ITU-T G.711 A-law
 0x0007	WAVE_FORMAT_MULAW	8-bit ITU-T G.711 µ-law
 0xFFFE	WAVE_FORMAT_EXTENSIBLE	Determined by SubForma
 
  
 */



/// WAV audio file 'riff' section header
typedef struct 
{
    char riff_char[4];
    int  package_len;
    char wave[4];
} WavRiff;

/// WAV audio file 'format' section header
typedef struct 
{
    char  fmt[4];
    int   format_len;
    short fixed;
    short channel_number;
    int   sample_rate;
    int   byte_rate;
    short byte_per_sample;
    short bits_per_sample;
} WavFormat;

/// WAV audio file 'data' section header
typedef struct 
{
    char  data_field[4];
    UInt32  data_len;
} WavData;


/// WAV audio file header
typedef struct 
{
    WavRiff   riff;
    WavFormat format;
    WavData   data;
} WavHeader;



class WavReader {
	
	
	private :
	
	FILE *fptr;
	
	WavHeader header;
	
	UInt32 dataRead;
	
	/// Init the WAV file stream
    void Init();
	
    /// Read WAV file headers.
    /// \return zero if all ok, nonzero if file format is invalid.
    int ReadWavHeaders();
	
    /// Checks WAV file header tags.
    /// \return zero if all ok, nonzero if file format is invalid.
    int CheckCharTags() const;
	
    /// Reads a single WAV file header block.
    /// \return zero if all ok, nonzero if file format is invalid.
    int ReadHeaderBlock();
	
    /// Reads WAV file 'riff' block
    int ReadRIFFBlock();
	
	public :
	
	
	/// Constructor: Opens the given WAV file. If the file can't be opened,
    /// throws 'runtime_error' exception.
    WavReader(const char *filename);
	
    WavReader(FILE *file);
	
    /// Destructor: Closes the file.
    ~WavReader();
	
    /// Rewind to beginning of the file
    void Rewind();
	
    /// Get sample rate.
    UInt32 GetSampleRate() const;
	
    /// Get number of bits per sample, i.e. 8 or 16.
    UInt32 GetNumBits() const;
	
    /// Get sample data size in bytes. Ahem, this should return same information as 
    /// 'getBytesPerSample'...
    UInt32 GetDataSizeInBytes() const;
	
    /// Get total number of samples in file.
    UInt32 GetNumSamples() const;
	
    /// Get number of bytes per audio sample (e.g. 16bit stereo = 4 bytes/sample)
    UInt32 GetBytesPerSample() const;
    
    /// Get number of audio channels in the file (1=mono, 2=stereo)
    UInt32 GetNumChannels() const;
	
    /// Get the audio file length in milliseconds
    UInt32 GetLengthMS() const;
	
    /// Reads audio samples from the WAV file. This routine works only for 8 bit samples.
    /// Reads given number of elements from the file or if end-of-file reached, as many 
    /// elements as are left in the file.
    ///
    /// \return Number of 8-bit integers read from the file.
    int Read(char *buffer, int maxElems);
	
    /// Reads audio samples from the WAV file to 16 bit integer format. Reads given number 
    /// of elements from the file or if end-of-file reached, as many elements as are 
    /// left in the file.
    ///
    /// \return Number of 16-bit integers read from the file.
    int Read(short *buffer,     ///< Pointer to buffer where to read data.
             int maxElems       ///< Size of 'buffer' array (number of array elements).
             );
	
    /// Reads audio samples from the WAV file to floating point format, converting 
    /// sample values to range [-1,1[. Reads given number of elements from the file
    /// or if end-of-file reached, as many elements as are left in the file.
    ///
    /// \return Number of elements read from the file.
    int Read(float *buffer,     ///< Pointer to buffer where to read data.
             int maxElems       ///< Size of 'buffer' array (number of array elements).
             );
	
    /// Check end-of-file.
    ///
    /// \return Nonzero if end-of-file reached.
    int Eof() const;
	
	
	
};


#endif
