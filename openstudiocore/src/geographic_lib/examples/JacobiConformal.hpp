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

#include <GeographicLib/EllipticFunction.hpp>

namespace GeographicLib {
  /**
   * \brief Jacobi's conformal projection of a triaxial ellipsoid
   *
   * <b>NOTE:</b> This is just sample code.  It is not part of GeographicLib
   * itself.
   *
   * This is a conformal projection of the ellipsoid to a plane in which
   * the grid lines are straight; see Jacobi,
   * <a href="https://books.google.com/books?id=ryEOAAAAQAAJ&pg=PA212">
   * Vorlesungen &uuml;ber Dynamik, &sect;28</a>.  The constructor takes the
   * semi-axes of the ellipsoid (which must be in order).  Member functions map
   * the ellipsoidal coordinates &omega; and &beta; separately to \e x and \e
   * y.  Jacobi's coordinates have been multiplied by
   * (<i>a</i><sup>2</sup>&minus;<i>c</i><sup>2</sup>)<sup>1/2</sup> /
   * (2<i>b</i>) so that the customary results are returned in the cases of
   * a sphere or an ellipsoid of revolution.
   *
   * The ellipsoid is oriented so that the large principal ellipse, \f$Z=0\f$,
   * is the equator, \f$\beta=0\f$, while the small principal ellipse,
   * \f$Y=0\f$, is the prime meridian, \f$\omega=0\f$.  The four umbilic
   * points, \f$\left|\omega\right| = \left|\beta\right| = \frac12\pi\f$, lie
   * on middle principal ellipse in the plane \f$X=0\f$.
   *
   * For more information on this projection, see \ref jacobi.
   **********************************************************************/
  class JacobiConformal {
    typedef Math::real real;
    real _a, _b, _c, _ab2, _bc2, _ac2;
    EllipticFunction _ex, _ey;
    static void norm(real& x, real& y)
    { real z = Math::hypot(x, y); x /= z; y /= z; }
  public:
    /**
     * Constructor for a trixial ellipsoid with semi-axes
     *
     * @param[in] a the largest semi-axis.
     * @param[in] b the middle semi-axis.
     * @param[in] c the smallest semi-axis.
     *
     * The semi-axes must satisfy \e a &ge; \e b &ge; \e c > 0 and \e a >
     * \e c.  This form of the constructor cannot be used to specify a
     * sphere (use the next constructor).
     **********************************************************************/
    JacobiConformal(real a, real b, real c)
      : _a(a), _b(b), _c(c)
      , _ab2((_a - _b) * (_a + _b))
      , _bc2((_b - _c) * (_b + _c))
      , _ac2((_a - _c) * (_a + _c))
      , _ex(_ab2 / _ac2 * Math::sq(_c / _b), -_ab2 / Math::sq(_b),
            _bc2 / _ac2 * Math::sq(_a / _b), Math::sq(_a / _b))
      , _ey(_bc2 / _ac2 * Math::sq(_a / _b), +_bc2 / Math::sq(_b),
            _ab2 / _ac2 * Math::sq(_c / _b), Math::sq(_c / _b))
    {
      if (!(a >= b && b >= c && c > 0))
        throw GeographicErr("JacobiConformal: axes are not in order");
      if (!(a > c))
        throw GeographicErr("JacobiConformal: use alternate constructor for sphere");
    }
    /**
     * Alternate constructor for a triaxial ellipsoid.
     *
     * @param[in] a the largest semi-axis.
     * @param[in] b the middle semi-axis.
     * @param[in] c the smallest semi-axis.
     * @param[in] ab the relative magnitude of \e a &minus; \e b.
     * @param[in] bc the relative magnitude of \e b &minus; \e c.
     *
     * This form can be used to specify a sphere.  The semi-axes must
     * satisfy \e a &ge; \e b &ge; c > 0.  The ratio \e ab : \e bc must equal
     * (<i>a</i>&minus;<i>b</i>) : (<i>b</i>&minus;<i>c</i>) with \e ab
     * &ge; 0, \e bc &ge; 0, and \e ab + \e bc > 0.
     **********************************************************************/
    JacobiConformal(real a, real b, real c, real ab, real bc)
      : _a(a), _b(b), _c(c)
      , _ab2(ab * (_a + _b))
      , _bc2(bc * (_b + _c))
      , _ac2(_ab2 + _bc2)
      , _ex(_ab2 / _ac2 * Math::sq(_c / _b),
            -(_a - _b) * (_a + _b) / Math::sq(_b),
            _bc2 / _ac2 * Math::sq(_a / _b), Math::sq(_a / _b))
      , _ey(_bc2 / _ac2 * Math::sq(_a / _b),
            +(_b - _c) * (_b + _c) / Math::sq(_b),
            _ab2 / _ac2 * Math::sq(_c / _b), Math::sq(_c / _b))
    {
      if (!(a >= b && b >= c && c > 0 && ab >= 0 && bc >= 0))
        throw GeographicErr("JacobiConformal: axes are not in order");
      if (!(ab + bc > 0))
        throw GeographicErr("JacobiConformal: ab + bc must be positive");
    }
    /**
     * @return the quadrant length in the \e x direction
     **********************************************************************/
    Math::real x() const { return Math::sq(_a / _b) * _ex.Pi(); }
    /**
     * The \e x projection
     *
     * @param[in] somg sin(&omega;)
     * @param[in] comg cos(&omega;)
     * @return \e x
     **********************************************************************/
    Math::real x(real somg, real comg) const {
      real somg1 = _b * somg, comg1 = _a * comg; norm(somg1, comg1);
      return Math::sq(_a / _b)
        * _ex.Pi(somg1, comg1, _ex.Delta(somg1, comg1));
    }
    /**
     * The \e x projection
     *
     * @param[in] omg &omega; (in degrees)
     * @return \e x (in degrees)
     *
     * &omega; must be in (&minus;180&deg;, 180&deg;].
     **********************************************************************/
    Math::real x(real omg) const {
      real somg, comg;
      Math::sincosd(omg, somg, comg);
      return x(somg, comg) / Math::degree();
    }
    /**
     * @return the quadrant length in the \e y direction
     **********************************************************************/
    Math::real y() const { return Math::sq(_c / _b) * _ey.Pi(); }
    /**
     * The \e y projection
     *
     * @param[in] sbet sin(&beta;)
     * @param[in] cbet cos(&beta;)
     * @return \e y
     **********************************************************************/
    Math::real y(real sbet, real cbet) const {
      real sbet1 = _b * sbet, cbet1 = _c * cbet; norm(sbet1, cbet1);
      return Math::sq(_c / _b)
        * _ey.Pi(sbet1, cbet1, _ey.Delta(sbet1, cbet1));
    }
    /**
     * The \e y projection
     *
     * @param[in] bet &beta; (in degrees)
     * @return \e y (in degrees)
     *
     * &beta; must be in (&minus;180&deg;, 180&deg;].
     **********************************************************************/
    Math::real y(real bet) const {
      real sbet, cbet;
      Math::sincosd(bet, sbet, cbet);
      return y(sbet, cbet) / Math::degree();
    }
  };

} // namespace GeographicLib
