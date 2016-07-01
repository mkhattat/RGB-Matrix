// ==========================================================================
//
// File      : Timer.hpp
// Part of   : led matrix library
// Copyright : mostafa@khattat.nl 2016
//
// led matrix implementation for an Arduino Due (ATSAM3X8E chip)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef TIMER_HPP
#define TIMER_HPP

#include "hwlib.hpp"

/// Timer class used for wait an amount of time.
//
/// Timer class uses Timer interrupt 0 channel 0. You can use only one instance at a time.
class Timer
{
public:
	/// Timer constructor
	//
	/// Configure timer interrupt 0 channel 0 to be used with a frequenty of 1 MHZ
	Timer();
	/// Delay in microseconds
	//
	/// Delay the flow of a code by given microseconds time interval.
	void delayMicroseconds(uint32_t micro);
	/// Delay in milliseconds
	//
	/// Delay the flow of a code by given milliseconds time interval.
	void delayMilliseconds(uint32_t millis);

private:
	/// Start the timer.
	void start();
	/// Stop the timer.
	void stop();
};

#endif // TIMER_HPP
