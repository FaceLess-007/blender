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

// Purpose:  Stub projection for geocentric.  The transformation isn't
//           really done here since this code is 2D.  The real transformation
//           is handled by pj_transform.c.
// Author:   Frank Warmerdam, warmerdam@pobox.com
// Copyright (c) 2002, Frank Warmerdam

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_GEOCENT_HPP
#define BOOST_GEOMETRY_PROJECTIONS_GEOCENT_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace srs { namespace par4
{
    struct geocent {}; // Geocentric

}} //namespace srs::par4

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace geocent
    {

            // template class, using CRTP to implement forward/inverse
            template <typename T, typename Parameters>
            struct base_geocent_other
                : public base_t_fi<base_geocent_other<T, Parameters>, T, Parameters>
            {
                inline base_geocent_other(const Parameters& par)
                    : base_t_fi<base_geocent_other<T, Parameters>, T, Parameters>(*this, par)
                {}

                // FORWARD(forward)
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(T& lp_lon, T& lp_lat, T& xy_x, T& xy_y) const
                {
                        xy_x = lp_lon;
                        xy_y = lp_lat;
                }

                // INVERSE(inverse)
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(T& xy_x, T& xy_y, T& lp_lon, T& lp_lat) const
                {
                        lp_lat = xy_y;
                        lp_lon = xy_x;
                }

                static inline std::string get_name()
                {
                    return "geocent_other";
                }

            };

            // Geocentric
            template <typename Parameters>
            inline void setup_geocent(Parameters& par)
            {
                par.is_geocent = 1;
                par.x0 = 0.0;
                par.y0 = 0.0;
            }

    }} // namespace detail::geocent
    #endif // doxygen

    /*!
        \brief Geocentric projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Example
        \image html ex_geocent.gif
    */
    template <typename T, typename Parameters>
    struct geocent_other : public detail::geocent::base_geocent_other<T, Parameters>
    {
        inline geocent_other(const Parameters& par) : detail::geocent::base_geocent_other<T, Parameters>(par)
        {
            detail::geocent::setup_geocent(this->m_par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION(srs::par4::geocent, geocent_other, geocent_other)

        // Factory entry(s)
        template <typename T, typename Parameters>
        class geocent_entry : public detail::factory_entry<T, Parameters>
        {
            public :
                virtual base_v<T, Parameters>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<geocent_other<T, Parameters>, T, Parameters>(par);
                }
        };

        template <typename T, typename Parameters>
        inline void geocent_init(detail::base_factory<T, Parameters>& factory)
        {
            factory.add_to_factory("geocent", new geocent_entry<T, Parameters>);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_GEOCENT_HPP

