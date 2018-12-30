#ifndef _TPLIB_TPLIB_H__
#define _TPLIB_TPLIB_H__

//check compiler version
#if __cplusplus < 201402L
	#error "Please use c++14 standard"
#endif

#include "tplib/stl.h"

namespace tplib{
	
	#include "tplib/tpl.h"
	
	
	//Call library
	
	//Bitmap library
	#ifdef TPIMPORT_BITMAP
		#include "bitmap/bitmap.h"
	#endif
	
	//Container library
	
		//map
		#ifdef TPIMPORT_MAP
			#include "map/map.h"
		#endif
		
		//queue
		#ifdef TPIMPORT_QUEUE
			#include "queue/queue.h"
		#endif
	
	//Math library
	
		//Matrix
		#ifdef TPIMPORT_MATRIX
			#include "matrix/matrix.h"
		#endif
		
		//Signal
		#ifdef TPIMPORT_SIGNAL
			#include "signal/signal.h"
		#endif
		
	
};

#endif