// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include "m_helper.hpp"
// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include <themachinethatgoesping/tools/helper/printing.hpp>
#include <themachinethatgoesping/tools/helper/stringconversion.hpp>

#include <themachinethatgoesping/tools_nanobind/pytensor_nanobind.hpp>

// extra
#include <themachinethatgoesping/tools/helper/xtensor.hpp>
#include <xtensor/containers/xadapt.hpp>
#include <xtensor/containers/xtensor.hpp>
#include <xtensor/misc/xsort.hpp>
#include <xtensor/views/xview.hpp>

// -- include system headers
#include <sstream>

// -- include nanobind headers
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/optional.h>

namespace nb = nanobind;
using namespace themachinethatgoesping::tools::helper;
template<typename t_region>
inline bool is_null_region(const t_region& region, const t_region& null_region)
{
    // if t_region is a floating point check if null_region is NaN
    if constexpr (std::is_floating_point_v<t_region>)
    {
        if (std::isnan(null_region))
            return std::isnan(region);
    }

    return region == null_region;
}
template<typename t_region_view>
inline auto get_non_null_mask(const t_region_view&                      region_view,
                              const typename t_region_view::value_type& null_region)
{
    if constexpr (std::is_floating_point_v<typename t_region_view::value_type>)
    {
        if (std::isnan(null_region))
            return xt::isfinite(region_view);
    }

    return xt::not_equal(region_view, null_region);
}
void init_m_helper(nb::module_& m)
{
    auto m_helper = m.def_submodule("helper", "Small helper functions");

    m_helper.def("int_as_string_4b",
                 &int_as_string<int32_t>,
                 "Interprete an integer to a 4 byte string",
                 nb::arg("value"));
    m_helper.def("int_as_string_8b",
                 &int_as_string<int64_t>,
                 "Interprete an integer to a 8 byte string",
                 nb::arg("value"));
    m_helper.def("string_as_int_4b",
                 &string_as_int<int32_t>,
                 "Interprete a 4 byte string to an integer",
                 nb::arg("value"));
    m_helper.def("string_as_int_8b",
                 &string_as_int<int64_t>,
                 "Interprete a 8 byte string to an integer",
                 nb::arg("value"));
    m_helper.def(
        "superscript", &superscript, "convert integer number to superscript", nb::arg("exponent"));

    // performance tests
    m_helper.def("pytensor_load_ref",
                 [](xt::nanobind::pytensor<double, 2>& t) { t.unchecked(0, 0) += 1.0; });
    m_helper.def("pytensor_const_load_ref", [](const xt::nanobind::pytensor<double, 2>& t) {
        auto t2 = t;
        t2.unchecked(0, 0) += 1.0;
        return t2;
    });
    m_helper.def("pytensor_load_copy", [](xt::nanobind::pytensor<double, 2> t) {
        t.unchecked(0, 0) += 1.0;
        return t;
    });

    m_helper.def("pytensor_loop_ref", [](xt::nanobind::pytensor<double, 2>& t) {
        using tensor_type = xt::nanobind::pytensor<double, 2>;
        for (tensor_type::size_type i = 0; i < t.size(); i += 1)
            t.flat(i) += 1.0;
    });
    m_helper.def("pytensor_loop_ref2", [](xt::nanobind::pytensor<double, 2>& t) {
        using tensor_type = xt::nanobind::pytensor<double, 2>;
        for (tensor_type::size_type i = 0; i < t.size(); i += 1)
            t.data()[i] += 1.0;
    });
    m_helper.def("pytensor_sum_ref",
                 [](xt::nanobind::pytensor<double, 2>& t) { t += xt::sum(t)(); });
    m_helper.def("pytensor_sum_const_ref", [](const xt::nanobind::pytensor<double, 2>& t) {
        xt::nanobind::pytensor<double, 2> t2 = xt::eval(t + xt::sum(t)());
        return t2;
    });
    m_helper.def("pytensor_sum_const_ref2", [](const xt::nanobind::pytensor<double, 2>& t) {
        return xt::eval(t + xt::sum(t)());
    });
    m_helper.def("pytensor_sum_const_ref3", [](const xt::nanobind::pytensor<double, 2>& t) {
        return xt::nanobind::pytensor<double, 2>(t + xt::sum(t)());
    });
    m_helper.def("pytensor_view_ref", [](xt::nanobind::pytensor<double, 2>& t) {
        auto shape = t.shape();
        xt::view(t,
                 xt::range(int(0.1 * shape[0]), int(0.9 * shape[0])),
                 xt::range(int(0.1 * shape[1]), int(0.9 * shape[1]))) += 1.0;
    });

    m_helper.def("pytensor_make", [](size_t rows, size_t cols) {
        return xt::nanobind::pytensor<double, 2>::from_shape({ rows, cols });
    });

    m_helper.def("pytensor_from", [](size_t rows, size_t cols) {
         xt::nanobind::pytensor<double, 2>::from_shape({ rows, cols });
    });
    m_helper.def("pytensor_make_xtensor", [](size_t rows, size_t cols) {
        return xt::xtensor<double, 2>::from_shape({ rows, cols });
    });

    m_helper.def("grow_regions_tools",
        [](xt::nanobind::pytensor<int8_t, 2>&       regions_image,
           const xt::nanobind::pytensor<double, 2>& data_image,
           const int8_t                             null_region,
           const std::optional<double>              threshold,
           const bool                               force_negative_gradient,
           const bool                               eat_neighbor_regions,
           const int                                mp_cores) {
            {
                using value_type  = typename xt::nanobind::pytensor<double, 2>::value_type;
                using region_type = typename xt::nanobind::pytensor<int8_t, 2>::value_type;
                using namespace themachinethatgoesping;

                static_assert(tools::helper::c_xtensor_2d<xt::nanobind::pytensor<double, 2>>,
                              "Template parameter must be a 2D tensor");
                static_assert(tools::helper::c_xtensor_2d<xt::nanobind::pytensor<double, 2>>,
                              "Template parameter must be a 2D tensor");

                if (regions_image.shape() != data_image.shape())
                    throw std::invalid_argument(
                        "regions_image and data_image must have the same shape.");

                const int64_t ny = data_image.shape()[1];
                const int64_t nx = data_image.shape()[0];

                // create vectors to store region changes
                std::vector<xt::xtensor_fixed<int64_t, xt::xshape<2>>> grow_region_indices;
                std::vector<region_type>                               grow_region_regions;

                // preprocess threshold
                const auto threshold_val =
                    threshold.value_or(std::numeric_limits<value_type>::lowest());

#pragma omp parallel num_threads(mp_cores)
                {
#pragma omp for
                    for (int64_t x = 0; x < nx; ++x)
                    {
                        const int64_t start_x = std::max(x - 1, int64_t(0));
                        const int64_t end_x   = std::min(x + 2, nx);
                        for (int64_t y = 0; y < ny; ++y)
                        {
                            const int64_t start_y = std::max(y - 1, int64_t(0));
                            const int64_t end_y   = std::min(y + 2, ny);

                            // test if current neighbor is null
                            const region_type region = regions_image.unchecked(x, y);

                            const bool region_is_null = is_null_region(region, null_region);
                            if (!region_is_null && !eat_neighbor_regions)
                                continue;

                            // test if current value exceeds threshold
                            const value_type val = data_image.unchecked(x, y);

                            if (!(val > threshold_val))
                                continue;

                            // Get the neighboring regions
                            auto regions_neighborhood = xt::view(regions_image,
                                                                 xt::range(start_x, end_x),
                                                                 xt::range(start_y, end_y));

                            // Create a boolean mask for non-null regions
                            auto non_null_mask =
                                xt::eval(get_non_null_mask(regions_neighborhood, null_region));

                            //continue;
                            // Filter out same region (if the center pixel belongs to a region)
                            if (eat_neighbor_regions && !region_is_null)
                                non_null_mask =
                                    non_null_mask && xt::not_equal(regions_neighborhood, region);

                            // Filter regions values based on non-null mask
                            auto neighbor_regions = xt::filter(regions_neighborhood, non_null_mask);

                            // Check if there are any non-null regions
                            if (neighbor_regions.size() == 0)
                                continue;

                            // Filter data values based on non-null mask
                            auto neighborhood_data = xt::view(
                                data_image, xt::range(start_x, end_x), xt::range(start_y, end_y));

                            auto non_null_data = xt::filter(neighborhood_data, non_null_mask);

                            // get the index of the maximum value in the non-null data
                            auto max_index = xt::argmax(non_null_data)();

                            // test gradient
                            if ((force_negative_gradient || !region_is_null) &&
                                non_null_data.unchecked(max_index) < val)
                                continue;

#pragma omp critical
                            {
                                grow_region_indices.push_back({ x, y });
                                grow_region_regions.push_back(
                                    neighbor_regions.unchecked(max_index));
                            }
                        }
                    }
                }

                // update regions
                xt::index_view(regions_image, grow_region_indices) = xt::adapt(grow_region_regions);

                return bool(grow_region_indices.size() > 0);
            }
        },
        nb::arg("region_image").noconvert(),
        nb::arg("data_image").noconvert(),
        nb::arg("null_region")             = 0,
        nb::arg("threshold")               = std::nullopt,
        nb::arg("force_negative_gradient") = true,
        nb::arg("eat_neighbor_regions")    = false,
        nb::arg("mp_cores")                = 1)
        ;
}
