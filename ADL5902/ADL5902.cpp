/*
ADL5902.cpp

This file contains the sources for the ADL5902 TruPwr detector.
https://www.analog.com/en/products/adl5902.html


Copyright (c) 2021, Mihai Ursu

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "ADL5902.h"


//!************************************************************************
//! Constructor
//!************************************************************************
ADL5902::ADL5902()
    : mFrequencyGhz( 2.412 )
    , mSlope( 0 )
    , mIntercept( 0 )
{
    updateParameters();
}


//!************************************************************************
//! Destructor
//!************************************************************************
ADL5902::~ADL5902()
{
}


//!************************************************************************
//! Get the RF power 
//!
//! @returns: the RF power in dBm
//!************************************************************************
double ADL5902::getRfPower
    (
    const double aVoltage           //!< voltage in Volts
    )
{
    double rfPwr = -99;   // dBm
    
    if( 0 != mSlope && 0 != mIntercept )
    {
        rfPwr = mIntercept + aVoltage * 1000 / mSlope;
    }
    
    return rfPwr;
}


//!************************************************************************
//! Set the operating frequency
//!
//! @returns: true if the value is in the operating range
//!************************************************************************
bool ADL5902::setFrequency
    (
    const double aFrequencyGhz      //!< frequency in GHz
    )
{
    bool couldSet( false );
    
    if( aFrequencyGhz >= FREQ_MIN_GHZ && aFrequencyGhz <= FREQ_MAX_GHZ )
    {
        mFrequencyGhz = aFrequencyGhz;
        couldSet = true;        
    }
 
    // if the frequency is out of range the slope and intercept will be 0, and the power -99dBm
    updateParameters();
    
    // return the status
    return couldSet;
}


//!************************************************************************
//! Update the slope and intercept values
//!
//! @returns: nothing
//!************************************************************************
void ADL5902::updateParameters()
{
    mSlope = 0;
    mIntercept = 0;
    
    if( mFrequencyGhz >= FREQ_MIN_GHZ && mFrequencyGhz < 0.1 )
    {
        mIntercept = -62.1;
        mSlope = 53.8;
    }
    else if( mFrequencyGhz < 0.7 )
    {
        mIntercept = -61.98333 - 1.16667 * mFrequencyGhz;
        mSlope = 53.81667 - 0.16667 * mFrequencyGhz;
    }
    else if( mFrequencyGhz < 0.9 )
    {
        mIntercept = -63.15 + 0.5 * mFrequencyGhz;
        mSlope = 53.7;
    }
    else if( mFrequencyGhz < 1.4 )
    {
        mIntercept = -67.884 + 5.76 * mFrequencyGhz;
        mSlope = 55.086 - 1.54 * mFrequencyGhz;
    }   
    else if( mFrequencyGhz < 1.9 )
    {
        mIntercept = -52.036 - 5.56 * mFrequencyGhz;
        mSlope = 53.854 - 0.66 * mFrequencyGhz;
    }
    else if( mFrequencyGhz < 2.14 )
    {
        mIntercept = -60.225 - 1.25 * mFrequencyGhz;
        mSlope = 54.18333 - 0.83333 * mFrequencyGhz;
    }
    else if( mFrequencyGhz < 2.6 )
    {
        mIntercept = -66.62174 + 1.73913 * mFrequencyGhz;
        mSlope = 58.91304 - 3.04348 * mFrequencyGhz;
    }
    else if( mFrequencyGhz < 3.5 )
    {
        mIntercept = -59.2111 - 1.11111 * mFrequencyGhz;
        mSlope = 55.04444 - 1.55556 * mFrequencyGhz;
    }
    else if( mFrequencyGhz < 5.8 )
    {
        mIntercept = -76.79565 + 3.91304 * mFrequencyGhz;
        mSlope = 60.1 - 3.0 * mFrequencyGhz;
    }
    else if( mFrequencyGhz < 7.0 )
    {
        mIntercept = -67.63333 + 2.33333 * mFrequencyGhz;
        mSlope = 66.64917 - 4.12917 * mFrequencyGhz; 
    }
    else if( mFrequencyGhz < 8.0 )
    {
        mIntercept = -64.6 + 1.9 * mFrequencyGhz;
        mSlope = 58.325 - 2.94 * mFrequencyGhz;
    }   
    else if( mFrequencyGhz <= FREQ_MAX_GHZ )
    {
        mIntercept = -79.0 + 3.7 * mFrequencyGhz;
        mSlope = 58.365 - 2.945 * mFrequencyGhz;
    }
}
