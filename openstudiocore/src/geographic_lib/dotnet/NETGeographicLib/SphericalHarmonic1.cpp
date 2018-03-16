/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2018, Alliance for Sustainable Energy, LLC. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#include "stdafx.h"
#include "GeographicLib/SphericalHarmonic1.hpp"
#include "SphericalHarmonic1.h"
#include "CircularEngine.h"
#include "SphericalCoefficients.h"
#include "NETGeographicLib.h"

using namespace NETGeographicLib;

const char BADALLOC[] = "Failed to allocate memory for a GeographicLib::SphericalHarmonic1";

//*****************************************************************************
SphericalHarmonic1::!SphericalHarmonic1(void)
{
    if ( m_pSphericalHarmonic1 != NULL )
    {
        delete m_pSphericalHarmonic1;
        m_pSphericalHarmonic1 = NULL;
    }

    if ( m_C != NULL )
    {
        for ( int i = 0; i < m_numCoeffVectors; i++ )
            if ( m_C[i] != NULL )
                delete m_C[i];
        delete [] m_C;
        m_C = NULL;
    }

    if ( m_S != NULL )
    {
        for ( int i = 0; i < m_numCoeffVectors; i++ )
            if ( m_S[i] != NULL )
                delete m_S[i];
        delete [] m_S;
        m_S = NULL;
    }
}

//*****************************************************************************
SphericalHarmonic1::SphericalHarmonic1( array<double>^ C,
                                        array<double>^ S,
                                        int N,
                                        array<double>^ C1,
                                        array<double>^ S1,
                                        int N1,
                                        double a,
                                        Normalization norm )
{
    try
    {
        m_C = new std::vector<double>*[m_numCoeffVectors];
        for ( int i = 0; i < m_numCoeffVectors; i++ ) m_C[i] = new std::vector<double>();
        m_S = new std::vector<double>*[m_numCoeffVectors];
        for ( int i = 0; i < m_numCoeffVectors; i++ ) m_S[i] = new std::vector<double>();
        for each ( double x in C ) m_C[0]->push_back( x );
        for each ( double x in S ) m_S[0]->push_back( x );
        for each ( double x in C1 ) m_C[1]->push_back( x );
        for each ( double x in S1 ) m_S[1]->push_back( x );
        m_pSphericalHarmonic1 = new GeographicLib::SphericalHarmonic1(
            *m_C[0], *m_S[0], N, *m_C[1], *m_S[1], N1, a, (unsigned)norm );
    }
    catch ( std::bad_alloc )
    {
        throw gcnew GeographicErr( BADALLOC );
    }
    catch ( const std::exception& err )
    {
        throw gcnew GeographicErr( err.what() );
    }
    catch ( System::Exception^ sxpt )
    {
        throw gcnew GeographicErr( sxpt->Message );
    }
}

//*****************************************************************************
SphericalHarmonic1::SphericalHarmonic1( array<double>^ C,
                                        array<double>^ S,
                                        int N, int nmx, int mmx,
                                        array<double>^ C1,
                                        array<double>^ S1,
                                        int N1, int nmx1, int mmx1,
                                        double a,
                                        Normalization norm )
{
    try
    {
        m_C = new std::vector<double>*[m_numCoeffVectors];
        for ( int i = 0; i < m_numCoeffVectors; i++ ) m_C[i] = new std::vector<double>();
        m_S = new std::vector<double>*[m_numCoeffVectors];
        for ( int i = 0; i < m_numCoeffVectors; i++ ) m_S[i] = new std::vector<double>();
        for each ( double x in C ) m_C[0]->push_back( x );
        for each ( double x in S ) m_S[0]->push_back( x );
        for each ( double x in C1 ) m_C[1]->push_back( x );
        for each ( double x in S1 ) m_S[1]->push_back( x );
        m_pSphericalHarmonic1 = new GeographicLib::SphericalHarmonic1(
            *m_C[0], *m_S[0], N, nmx, mmx, *m_C[1], *m_S[1], N1, nmx1, mmx1, a,
            (unsigned)norm );
    }
    catch ( std::bad_alloc )
    {
        throw gcnew GeographicErr( BADALLOC );
    }
    catch ( const std::exception& err )
    {
        throw gcnew GeographicErr( err.what() );
    }
    catch ( System::Exception^ sxpt )
    {
        throw gcnew GeographicErr( sxpt->Message );
    }
}

//*****************************************************************************
double SphericalHarmonic1::HarmonicSum(double tau, double x, double y, double z)
{
    return m_pSphericalHarmonic1->operator()( tau, x, y, z );
}

//*****************************************************************************
double SphericalHarmonic1::HarmonicSum(double tau, double x, double y, double z,
                        [System::Runtime::InteropServices::Out] double% gradx,
                        [System::Runtime::InteropServices::Out] double% grady,
                        [System::Runtime::InteropServices::Out] double% gradz)
{
    double lgradx, lgrady, lgradz;
    double out = m_pSphericalHarmonic1->operator()( tau, x, y, z, lgradx, lgrady, lgradz );
    gradx = lgradx;
    grady = lgrady;
    gradz = lgradz;
    return out;
}

//*****************************************************************************
CircularEngine^ SphericalHarmonic1::Circle(double tau, double p, double z, bool gradp)
{
    try
    {
        return gcnew CircularEngine( m_pSphericalHarmonic1->Circle( tau, p, z, gradp ) );
    }
    catch ( std::bad_alloc )
    {
        throw gcnew GeographicErr( "Failed to allocate memory for a CircularEngine in SphericalHarmonic1::Circle" );
    }
}

//*****************************************************************************
SphericalCoefficients^ SphericalHarmonic1::Coefficients()
{
    return gcnew SphericalCoefficients( m_pSphericalHarmonic1->Coefficients() );
}

//*****************************************************************************
SphericalCoefficients^ SphericalHarmonic1::Coefficients1()
{
    return gcnew SphericalCoefficients( m_pSphericalHarmonic1->Coefficients1() );
}
