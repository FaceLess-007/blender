// Boost.Geometry - gis-projections (based on PROJ4)

// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Boost.Geometry by Barend Gehrels

// Last updated version of proj: 5.0.0

// Original copyright notice:

// Purpose:  Implementation of the airy (Airy) projection.
// Author:   Gerald Evenden (1995)
//           Thomas Knudsen (2016) - revise/add regression tests
// Copyright (c) 1995, Gerald Evenden

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef BOOST_GEOMETRY_PROJECTIONS_AIRY_HPP
#define BOOST_GEOMETRY_PROJECTIONS_AIRY_HPP

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

#include <boost/geometry/srs/projections/par4.hpp> // airy tag

namespace boost { namespace geometry
{

namespace srs { namespace par4
{
    // already defined in par4.hpp as ellps name
    //struct airy {};

}} //namespace srs::par4

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace airy
    {

            static const double epsilon = 1.e-10;
            enum mode_type {
                n_pole = 0,
                s_pole = 1,
                equit  = 2,
                obliq  = 3
            };

            template <typename T>
            struct par_airy
            {
                T    p_halfpi;
                T    sinph0;
                T    cosph0;
                T    Cb;
                mode_type mode;
                int  no_cut;    /* do not cut at hemisphere limit */
            };

            // template class, using CRTP to implement forward/inverse
            template <typename T, typename Parameters>
            struct base_airy_spheroid
                : public base_t_f<base_airy_spheroid<T, Parameters>, T, Parameters>
            {
                par_airy<T> m_proj_parm;

                inline base_airy_spheroid(const Parameters& par)
                    : base_t_f<base_airy_spheroid<T, Parameters>, T, Parameters>(*this, par)
                {}

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(T& lp_lon, T& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T  sinlam, coslam, cosphi, sinphi, t, s, Krho, cosz;

                    sinlam = sin(lp_lon);
                    coslam = cos(lp_lon);
                    switch (this->m_proj_parm.mode) {
                    case equit:
                    case obliq:
                        sinphi = sin(lp_lat);
                        cosphi = cos(lp_lat);
                        cosz = cosphi * coslam;
                        if (this->m_proj_parm.mode == obliq)
                            cosz = this->m_proj_parm.sinph0 * sinphi + this->m_proj_parm.cosph0 * cosz;
                        if (!this->m_proj_parm.no_cut && cosz < -epsilon) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        if (fabs(s = 1. - cosz) > epsilon) {
                            t = 0.5 * (1. + cosz);
                            Krho = -log(t)/s - this->m_proj_parm.Cb / t;
                        } else
                            Krho = 0.5 - this->m_proj_parm.Cb;
                        xy_x = Krho * cosphi * sinlam;
                        if (this->m_proj_parm.mode == obliq)
                            xy_y = Krho * (this->m_proj_parm.cosph0 * sinphi -
                                this->m_proj_parm.sinph0 * cosphi * coslam);
                        else
                            xy_y = Krho * sinphi;
                        break;
                    case s_pole:
                    case n_pole:
                        lp_lat = fabs(this->m_proj_parm.p_halfpi - lp_lat);
                        if (!this->m_proj_parm.no_cut && (lp_lat - epsilon) > half_pi)
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        if ((lp_lat *= 0.5) > epsilon) {
                            t = tan(lp_lat);
                            Krho = -2.*(log(cos(lp_lat)) / t + t * this->m_proj_parm.Cb);
                            xy_x = Krho * sinlam;
                            xy_y = Krho * coslam;
                            if (this->m_proj_parm.mode == n_pole)
                                xy_y = -xy_y;
                        } else
                            xy_x = xy_y = 0.;
                    }
                }

                static inline std::string get_name()
                {
                    return "airy_spheroid";
                }

            };

            // Airy
            template <typename Parameters, typename T>
            inline void setup_airy(Parameters& par, par_airy<T>& proj_parm)
            {
                static const T half_pi = detail::half_pi<T>();

                T beta;

                proj_parm.no_cut = pj_get_param_b(par.params, "no_cut");
                beta = 0.5 * (half_pi - pj_get_param_r(par.params, "lat_b"));
                if (fabs(beta) < epsilon)
                    proj_parm.Cb = -0.5;
                else {
                    proj_parm.Cb = 1./tan(beta);
                    proj_parm.Cb *= proj_parm.Cb * log(cos(beta));
                }

                if (fabs(fabs(par.phi0) - half_pi) < epsilon)
                    if (par.phi0 < 0.) {
                        proj_parm.p_halfpi = -half_pi;
                        proj_parm.mode = s_pole;
                    } else {
                        proj_parm.p_halfpi =  half_pi;
                        proj_parm.mode = n_pole;
                    }
                else {
                    if (fabs(par.phi0) < epsilon)
                        proj_parm.mode = equit;
                    else {
                        proj_parm.mode = obliq;
                        proj_parm.sinph0 = sin(par.phi0);
                        proj_parm.cosph0 = cos(par.phi0);
                    }
                }
                par.es = 0.;
            }

    }} // namespace detail::airy
    #endif // doxygen

    /*!
        \brief Airy projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Projection parameters
         - no_cut: Do not cut at hemisphere limit (boolean)
         - lat_b (degrees)
        \par Example
        \image html ex_airy.gif
    */
    template <typename T, typename Parameters>
    struct airy_spheroid : public detail::airy::base_airy_spheroid<T, Parameters>
    {
        inline airy_spheroid(const Parameters& par) : detail::airy::base_airy_spheroid<T, Parameters>(par)
        {
            detail::airy::setup_airy(this->m_par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION(srs::par4::airy, airy_spheroid, airy_spheroid)

        // Factory entry(s)
        template <typename T, typename Parameters>
        class airy_entry : public detail::factory_entry<T, Parameters>
        {
            public :
                virtual base_v<T, Parameters>* create_new(const Parameters& par) const
                {
                    return new base_v_f<airy_spheroid<T, Parameters>, T, Parameters>(par);
                }
        };

        template <typename T, typename Parameters>
        inline void airy_init(detail::base_factory<T, Parameters>& factory)
        {
            factory.add_to_factory("airy", new airy_entry<T, Parameters>);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_AIRY_HPP

