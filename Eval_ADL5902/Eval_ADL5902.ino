/*
Eval_ADL5902.ino

This file contains the Arduino demo source for the EVAL-ADL5902-ARDZ.
https://www.analog.com/en/design-center/evaluation-hardware-and-software/evaluation-boards-kits/eval-adl5902-ardz.html


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

#include <Arduino.h>
#include <ADL5902.h>

ADL5902 adl5902;
double freqGhz = 1.4204;

double adConvert
    (
    int rawValue
    )
{
    const uint16_t RAW_FS = ( 1 << 10 ) - 1;
    const double VOLT_FS = 5.0;
    return rawValue * VOLT_FS / RAW_FS;
}

void setup()
{
    Serial.begin( 9600 );
    Serial.print( "Setting f [GHz] = " ); 
    Serial.println( freqGhz, 4 );
    adl5902.setFrequency( freqGhz );
}

void loop() 
{
    const uint8_t SAMPLES_COUNT = 5;
    double pwrDbmAvg = 0;

    for( int i = 0; i < SAMPLES_COUNT; i++ )
    {
        int vOutRaw = analogRead( A0 );
        double vOut = adConvert( vOutRaw );
        double pwrDbm = adl5902.getRfPower( vOut );
        pwrDbmAvg += pwrDbm;
        delay( 1000 / SAMPLES_COUNT );
    }

    pwrDbmAvg /= SAMPLES_COUNT;
    Serial.print( "RF pwr = " ); 
    Serial.print( pwrDbmAvg, 1 ); 
    Serial.println( " dBm" ); 
}
