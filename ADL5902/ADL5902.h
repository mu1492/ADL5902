/*
ADL5902.h

This file contains the definitions for the ADL5902 TruPwr detector.
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

#ifndef ADL5902_h
#define ADL5902_h


//************************************************************************
// Class for the ADL5902 TruPwr detector
//************************************************************************
class ADL5902
{
    //************************************************************************
    // data types and constants
    //************************************************************************
    private:
        static constexpr double FREQ_MIN_GHZ = 0.05;    //!< low frequency range [GHz]
        static constexpr double FREQ_MAX_GHZ = 9.0;     //!< high frequency range [GHz]

    //************************************************************************
    // functions
    //************************************************************************
    public:
        ADL5902();
        ~ADL5902();

        bool setFrequency
            (
            const double aFrequencyGhz      //!< frequency in Ghz
            );

        double getRfPower
            (
            const double aVoltage           //!< a voltage in Volts
            );

    private:
        void updateParameters();

    //************************************************************************
    // variables
    //************************************************************************
    private:       
        double      mFrequencyGhz;      //!< operating frequency, 0.05-9.0 [GHz]
        double      mSlope;             //!< logarithmic slope [mV/dB]
        double      mIntercept;         //!< logarithmic intercept [dBm]
};

#endif // ADL5902_h
