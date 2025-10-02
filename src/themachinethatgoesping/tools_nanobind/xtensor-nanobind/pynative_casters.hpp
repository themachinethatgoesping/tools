/***************************************************************************
* Copyright (c) Wolf Vollprecht, Johan Mabille and Sylvain Corlay          *
* Copyright (c) QuantStack                                                 *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef PYNATIVE_CASTERS_HPP
#define PYNATIVE_CASTERS_HPP

#include "xtensor_type_caster_base.hpp"

namespace nanobind
{
	namespace detail
	{
		template <class T, xt::layout_type L>
		struct type_caster<xt::xarray<T, L>> : xtensor_type_caster_base<xt::xarray<T, L>>
		{
		};

		template <class T, std::size_t N, xt::layout_type L>
		struct type_caster<xt::xtensor<T, N, L>> : xtensor_type_caster_base<xt::xtensor<T, N, L>>
		{
		};

		template <class T, class FSH, xt::layout_type L>
		struct type_caster<xt::xtensor_fixed<T, FSH, L>> : xtensor_type_caster_base<xt::xtensor_fixed<T, FSH, L>>
		{
		};

		template <class CT, class S, xt::layout_type L, class FST>
		struct type_caster<xt::xstrided_view<CT, S, L, FST>>
		{
			using view_type = xt::xstrided_view<CT, S, L, FST>;
			using ndarray_t = xt_nb_detail::ndarray_for_xtensor_t<view_type, false, ::nanobind::numpy>;

			NB_TYPE_CASTER(view_type, make_caster<ndarray_t>::Name)

			bool from_python(handle, uint8_t, cleanup_list*) noexcept
			{
				return false;
			}

			static handle from_cpp(const view_type& view, rv_policy policy, cleanup_list* cleanup) noexcept
			{
				return xtensor_type_caster_base<view_type>::from_cpp(view, policy, cleanup);
			}
		};

		template <class EC, xt::layout_type L, class SC, class Tag>
		struct type_caster<xt::xarray_adaptor<EC, L, SC, Tag>> : xtensor_type_caster_base<xt::xarray_adaptor<EC, L, SC, Tag>>
		{
		};

		template <class EC, std::size_t N, xt::layout_type L, class Tag>
		struct type_caster<xt::xtensor_adaptor<EC, N, L, Tag>> : xtensor_type_caster_base<xt::xtensor_adaptor<EC, N, L, Tag>>
		{
		};
	}
}

#endif
