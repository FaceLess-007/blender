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

#ifndef BOOST_GEOMETRY_PROJECTIONS_CEA_HPP
#define BOOST_GEOMETRY_PROJECTIONS_CEA_HPP

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_auth.hpp>
#include <boost/geometry/srs/projections/impl/pj_qsfn.hpp>

namespace boost { namespace geometry
{

namespace srs { namespace par4
{
    struct cea {};

}} //namespace srs::par4

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace cea
    {

            static const double epsilon = 1e-10;

            template <typename T>
            struct par_cea
            {
                T qp;
                detail::apa<T> apa;
            };

            // template class, using CRTP to implement forward/inverse
            template <typename T, typename Parameters>
            struct base_cea_ellipsoid
                : public base_t_fi<base_cea_ellipsoid<T, Parameters>, T, Parameters>
            {
                par_cea<T> m_proj_parm;

                inline base_cea_ellipsoid(const Parameters& par)
                    : base_t_fi<base_cea_ellipsoid<T, Parameters>, T, Parameters>(*this, par)
                {}

                // FORWARD(e_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(T& lp_lon, T& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = this->m_par.k0 * lp_lon;
                    xy_y = .5 * pj_qsfn(sin(lp_lat), this->m_par.e, this->m_par.one_es) / this->m_par.k0;
                }

                // INVERSE(e_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(T& xy_x, T& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = pj_authlat(asin( 2. * xy_y * this->m_par.k0 / this->m_proj_parm.qp), this->m_proj_parm.apa);
                    lp_lon = xy_x / this->m_par.k0;
                }

                static inline std::string get_name()
                {
                    return "cea_ellipsoid";
                }

            };

            // template class, using CRTP to implement forward/inverse
            template <typename T, typename Parameters>
            struct base_cea_spheroid
                : public base_t_fi<base_cea_spheroid<T, Parameters>, T, Parameters>
            {
                par_cea<T> m_proj_parm;

                inline base_cea_spheroid(const Parameters& par)
                    : base_t_fi<base_cea_spheroid<T, Parameters>, T, Parameters>(*this, par)
                {}

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(T& lp_lon, T& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = this->m_par.k0 * lp_lon;
                    xy_y = sin(lp_lat) / this->m_par.k0;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(T& xy_x, T& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T t;

                    if ((t = fabs(xy_y *= this->m_par.k0)) - epsilon <= 1.) {
                        if (t >= 1.)
                            lp_lat = xy_y < 0. ? -half_pi : half_pi;
                        else
                            lp_lat = asin(xy_y);
                        lp_lon = xy_x / this->m_par.k0;
                    } else
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                }

                static inline std::string get_name()
                {
                    return "cea_spheroid";
                }

            };

            // Equal Area Cylindrical
            template <typename Parameters, typename T>
            inline void setup_cea(Parameters& par, par_cea<T>& proj_parm)
            {
                T t = 0;

                if (pj_param_r(par.params, "lat_ts", t)) {
                    par.k0 = cos(t);
                    if (par.k0 < 0.) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_lat_ts_larger_than_90) );
                    }
                }
                if (par.es != 0.0) {
                    t = sin(t);
                    par.k0 /= sqrt(1. - par.es * t * t);
                    par.e = sqrt(par.es);
                    proj_parm.apa = pj_authset<T>(par.es);

                    proj_parm.qp = pj_qsfn(1., par.e, par.one_es);
                }
            }

    }} // namespace detail::cea
    #endif // doxygen

    /*!
        \brief Equal Area Cylindrical projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_ts: Latitude of true scale (degrees)
        \par Example
        \image html ex_cea.gif
    */
    template <typename T, typename Parameters>
    struct cea_ellipsoid : public detail::cea::base_cea_ellipsoid<T, Parameters>
    {
        inline cea_ellipsoid(const Parameters& par) : detail::cea::base_cea_ellipsoid<T, Parameters>(par)
        {
            detail::cea::setup_cea(this->m_par, this->m_proj_parm);
        }
    };

    /*!
        \brief Equal Area Cylindrical projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_ts: Latitude of true scale (degrees)
        \par Example
        \image html ex_cea.gif
    */
    template <typename T, typename Parameters>
    struct cea_spheroid : public detail::cea::base_cea_spheroid<T, Parameters>
    {
        inline cea_spheroid(const Parameters& par) : detail::cea::base_cea_spheroid<T, Parameters>(par)
        {
            detail::cea::setup_cea(this->m_par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION(srs::par4::cea, cea_spheroid, cea_ellipsoid)

        // Factory entry(s)
        template <typename T, typename Parameters>
        class cea_entry : public detail::factory_entry<T, Parameters>
        {
            public :
                virtual base_v<T, Parameters>* create_new(const Parameters& par) const
                {
                    if (par.es)
                        return new base_v_fi<cea_ellipsoid<T, Parameters>, T, Parameters>(par);
                    else
                        return new base_v_fi<cea_spheroid<T, Parameters>, T, Parameters>(par);
                }
        };

        template <typename T, typename Parameters>
        inline void cea_init(detail::base_factory<T, Parameters>& factory)
        {
            factory.add_to_factory("cea", new cea_entry<T, Parameters>);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_CEA_HPP

