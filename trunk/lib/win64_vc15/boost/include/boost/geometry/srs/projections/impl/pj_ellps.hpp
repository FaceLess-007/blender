// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Geometry Library by Barend Gehrels (Geodan, Amsterdam)

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_ELLPS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_ELLPS_HPP

#include <boost/geometry/srs/projections/impl/projects.hpp>

#include <string>

namespace boost { namespace geometry { namespace projections {

namespace detail {

// Originally defined in projects.h
struct pj_ellps_type
{
    std::string id;    /* ellipse keyword name */
    std::string major_v; /* a's value */
    std::string ell_n;   /* elliptical parameter name */
    std::string ell_v;   /* elliptical parameter value */
    std::string name;  /* comments */
};

static const pj_ellps_type pj_ellps[] =
{
    {"MERIT",     "6378137.0",   "rf", "298.257",           "MERIT 1983"},
    {"SGS85",     "6378136.0",   "rf", "298.257",           "Soviet Geodetic System 85"},
    {"GRS80",     "6378137.0",   "rf", "298.257222101",     "GRS 1980(IUGG, 1980)"},
    {"IAU76",     "6378140.0",   "rf", "298.257",           "IAU 1976"},
    {"airy",      "6377563.396", "b",  "6356256.910",       "Airy 1830"},
    {"APL4.9",    "6378137.0.",  "rf", "298.25",            "Appl. Physics. 1965"},
    {"NWL9D",     "6378145.0.",  "rf", "298.25",            "Naval Weapons Lab., 1965"},
    {"mod_airy",  "6377340.189", "b",  "6356034.446",       "Modified Airy"},
    {"andrae",    "6377104.43",  "rf", "300.0",             "Andrae 1876 (Den., Iclnd.)"},
    {"aust_SA",   "6378160.0",   "rf", "298.25",            "Australian Natl & S. Amer. 1969"},
    {"GRS67",     "6378160.0",   "rf", "298.2471674270",    "GRS 67(IUGG 1967)"},
    {"bessel",    "6377397.155", "rf", "299.1528128",       "Bessel 1841"},
    {"bess_nam",  "6377483.865", "rf", "299.1528128",       "Bessel 1841 (Namibia)"},
    {"clrk66",    "6378206.4",   "b",  "6356583.8",         "Clarke 1866"},
    {"clrk80",    "6378249.145", "rf", "293.4663",          "Clarke 1880 mod."},
    {"clrk80ign", "6378249.2",   "rf", "293.4660212936269", "Clarke 1880 (IGN)."},
    {"CPM",       "6375738.7",   "rf", "334.29",            "Comm. des Poids et Mesures 1799"},
    {"delmbr",    "6376428.",    "rf", "311.5",             "Delambre 1810 (Belgium)"},
    {"engelis",   "6378136.05",  "rf", "298.2566",          "Engelis 1985"},
    {"evrst30",   "6377276.345", "rf", "300.8017",          "Everest 1830"},
    {"evrst48",   "6377304.063", "rf", "300.8017",          "Everest 1948"},
    {"evrst56",   "6377301.243", "rf", "300.8017",          "Everest 1956"},
    {"evrst69",   "6377295.664", "rf", "300.8017",          "Everest 1969"},
    {"evrstSS",   "6377298.556", "rf", "300.8017",          "Everest (Sabah & Sarawak)"},
    {"fschr60",   "6378166.",    "rf", "298.3",             "Fischer (Mercury Datum) 1960"},
    {"fschr60m",  "6378155.",    "rf", "298.3",             "Modified Fischer 1960"},
    {"fschr68",   "6378150.",    "rf", "298.3",             "Fischer 1968"},
    {"helmert",   "6378200.",    "rf", "298.3",             "Helmert 1906"},
    {"hough",     "6378270.0",   "rf", "297.",              "Hough"},
    {"intl",      "6378388.0",   "rf", "297.",              "International 1909 (Hayford)"},
    {"krass",     "6378245.0",   "rf", "298.3",             "Krassovsky, 1942"},
    {"kaula",     "6378163.",    "rf", "298.24",            "Kaula 1961"},
    {"lerch",     "6378139.",    "rf", "298.257",           "Lerch 1979"},
    {"mprts",     "6397300.",    "rf", "191.",              "Maupertius 1738"},
    {"new_intl",  "6378157.5",   "b",  "6356772.2",         "New International 1967"},
    {"plessis",   "6376523.",    "b",  "6355863.",          "Plessis 1817 (France)"},
    {"SEasia",    "6378155.0",   "b",  "6356773.3205",      "Southeast Asia"},
    {"walbeck",   "6376896.0",   "b",  "6355834.8467",      "Walbeck"},
    {"WGS60",     "6378165.0",   "rf", "298.3",             "WGS 60"},
    {"WGS66",     "6378145.0",   "rf", "298.25",            "WGS 66"},
    {"WGS72",     "6378135.0",   "rf", "298.26",            "WGS 72"},
    {"WGS84",     "6378137.0",   "rf", "298.257223563",     "WGS 84"},
    {"sphere",    "6370997.0",   "b",  "6370997.0",         "Normal Sphere (r=6370997)"}
};

} // namespace detail
}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_ELLPS_HPP
