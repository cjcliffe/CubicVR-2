/*
    This file is part of CubicVR.

    Copyright (C) 2003 by Charles J. Cliffe

		Permission is hereby granted, free of charge, to any person obtaining a copy
		of this software and associated documentation files (the "Software"), to deal
		in the Software without restriction, including without limitation the rights
		to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
		copies of the Software, and to permit persons to whom the Software is
		furnished to do so, subject to the following conditions:

		The above copyright notice and this permission notice shall be included in
		all copies or substantial portions of the Software.

		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
		IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
		FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
		AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
		LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
		OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
		THE SOFTWARE.
*/

#include <cubicvr2/core/Timer.h>

#ifdef _WIN32
	#include <windows.h>
#endif

namespace CubicVR {

Timer::Timer(void) : time_elapsed(0), system_milliseconds(0), start_time(0), end_time(0), last_update(0), paused_time(0), offset(0), paused_state(false)
{
}


void Timer::start(void) 
{
	update();
	num_updates = 0;
	start_time = system_milliseconds;
	last_update = start_time;
	paused_state = false;
	lock_state = false;
	lock_rate = 0;
	paused_time = 0;
	offset = 0;
}


void Timer::stop(void) 
{
	end_time = system_milliseconds;
}


void Timer::reset(void)
{
	start();
}


void Timer::lockFramerate(float f_rate)
{
	lock_rate = (unsigned long)((1.0/f_rate)*1000.0);
	lock_state = true;
}


void Timer::unlock()
{
	unsigned long msec_tmp = system_milliseconds;
	
	lock_state = false;

	update();
	
	last_update = system_milliseconds-lock_rate;
	
	offset += msec_tmp-system_milliseconds;
	
	lock_rate = 0;
}

bool Timer::locked()
{
	return lock_state;
}

void Timer::update(void) 
{
	num_updates++;
	last_update = system_milliseconds;
	
	
	if (lock_state)
	{
		system_milliseconds += (unsigned long)(lock_rate*1000.0);
	}
	else
	{
#ifdef _WIN32
		system_milliseconds = timeGetTime ();
#else
		gettimeofday(&time_val,&time_zone);

		system_milliseconds = (unsigned long)time_val.tv_usec;
		system_milliseconds /= 1000;
		system_milliseconds += (unsigned long)(time_val.tv_sec*1000);
#endif
	}


	if (paused_state) paused_time += system_milliseconds-last_update;

	time_elapsed = system_milliseconds-start_time-paused_time+offset;
}


unsigned long Timer::getMilliseconds(void) 
{
	return time_elapsed;
}



double Timer::getSeconds(void) 
{
	return ((double)getMilliseconds())/1000.0;
}


void Timer::setMilliseconds(unsigned long milliseconds_in) 
{
	offset -= (system_milliseconds-start_time-paused_time+offset)-milliseconds_in;
}



void Timer::setSeconds(double seconds_in) 
{
	setMilliseconds((long)(seconds_in*1000.0));
}


double Timer::lastUpdateSeconds(void)
{
	return ((double)lastUpdateMilliseconds())/1000.0;
}


unsigned long Timer::lastUpdateMilliseconds(void)
{
	return system_milliseconds-last_update;
}

unsigned long Timer::totalMilliseconds()
{
	return system_milliseconds-start_time;
}


double Timer::totalSeconds(void)
{
	return totalMilliseconds()/1000.0;
}


unsigned long Timer::getNumUpdates(void)
{
	return num_updates;
}


void Timer::paused(bool pause_in)
{
	paused_state = pause_in;
}

bool Timer::paused()
{
	return paused_state;
}
    
}
