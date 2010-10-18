/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: HanningWindow.cpp
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

#ifndef CASCADEFILTER_H
#define CASCADEFILTER_H

#include "Utils.h"
#include "Complex.h"



typedef unsigned int UInt32;

class CascadeFilter{


private:
	
	
public:	
	
 CascadeFilter();
 CascadeFilter(UInt32 Stages ,UInt32 Channels);
 ~CascadeFilter();	
	
	
	
 void ProcessI( UInt32 frames, Float32 *dest, int skip=0 );
 void ProcessII( UInt32 frames,Float32 *dest, int skip=0 );
 void Process( UInt32 frames , Float32 *dest, int skip=0 );
	
 Complex  Response( Float32 w );
 int GetStageCount( void ){return m_nstage;}
 int SetStageCount(int stagecount){this->m_nstage=stagecount;}	
	
 void Clear( void );
 void Reset        ( void );
	
 void Scale    ( Float32 scale );

protected:

	struct Hist;
	struct Stage;
	
	struct Hist
	{
		Float32 v[4];
	};
	
	struct Stage
	{
		Float32 a[3];    // a[0] unused
		Float32 b[3];
		
	};
	
	void ProcessISSEStageStereo( UInt32 frames, Float32 *dest, Stage *s, Hist *h, int skip  );
	void ProcessISSEStereo( UInt32 frames, Float32 *dest, int skip );


	
	
	
	//void SetAStage    ( Float32 x1, Float32 x2 );
	//void SetBStage    ( Float32 x0, Float32 x1, Float32 x2 );
	
	void SetStage     ( Float32 a1, Float32 a2, Float32 b0, Float32 b1, Float32 b2 );
	
	void  GetStages(Stage **stagesptr);

	int        m_nchan;
	int        m_nstage;
	Stage *    m_stagep;
	Hist *    m_histp;
	

	
	struct ResponseFunctor
	{
		CascadeFilter *m_filter;
		Float32 operator()( Float32 w );
		ResponseFunctor( CascadeFilter *filter );
	};
	
	

};
#endif

