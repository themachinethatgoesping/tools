/***************************************************************************
* Copyright (c) Wolf Vollprecht, Johan Mabille and Sylvain Corlay          *
* Copyright (c) QuantStack                                                 *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XTENSOR_TYPE_CASTER_HPP
#define XTENSOR_TYPE_CASTER_HPP

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstring>
#include <type_traits>
#include <utility>
#include <vector>

#include "xtensor/containers/xarray.hpp"
#include "xtensor/containers/xadapt.hpp"
#include "xtensor/containers/xtensor.hpp"
#include "xtensor/containers/xfixed.hpp"
#include "xtensor/views/xstrided_view.hpp"

#include "pycontainer.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

namespace nanobind
{
	namespace detail
	{
		namespace xt_nb_detail
		{
			template <typename T>
			struct is_xtensor_fixed : std::false_type
			{
			};

			template <class ET, class S, xt::layout_type L, bool SH, class Tag>
			struct is_xtensor_fixed<xt::xfixed_container<ET, S, L, SH, Tag>> : std::true_type
			{
			};

			template <typename T>
			inline constexpr bool is_xtensor_fixed_v = is_xtensor_fixed<T>::value;

			template <typename T>
			struct is_xtensor : std::false_type
			{
			};

			template <class EC, std::size_t N, xt::layout_type L, class Tag>
			struct is_xtensor<xt::xtensor_container<EC, N, L, Tag>> : std::true_type
			{
			};

			template <class EC, std::size_t N, xt::layout_type L, class Tag>
			struct is_xtensor<xt::xtensor_adaptor<EC, N, L, Tag>> : std::true_type
			{
			};

			template <typename T>
			inline constexpr bool is_xtensor_v = is_xtensor<T>::value;

			template <typename T>
			struct is_xarray : std::false_type
			{
			};

			template <class EC, xt::layout_type L, class SC, class Tag>
			struct is_xarray<xt::xarray_container<EC, L, SC, Tag>> : std::true_type
			{
			};

			template <class EC, xt::layout_type L, class SC, class Tag>
			struct is_xarray<xt::xarray_adaptor<EC, L, SC, Tag>> : std::true_type
			{
			};

			template <typename T>
			inline constexpr bool is_xarray_v = is_xarray<T>::value;

			template <typename T>
			struct is_xstrided_view : std::false_type
			{
			};

			template <class CT, class S, xt::layout_type L, class FST>
			struct is_xstrided_view<xt::xstrided_view<CT, S, L, FST>> : std::true_type
			{
			};

			template <typename T>
			inline constexpr bool is_xstrided_view_v = is_xstrided_view<T>::value;

			template <typename T>
			struct nb_shape_param
			{
				using value = unused;
			};

			template <class ET, xt::layout_type L, bool SH, class Tag, std::size_t... Sizes>
			struct nb_shape_param<xt::xfixed_container<ET, xt::xshape<Sizes...>, L, SH, Tag>>
			{
				using value = shape<Sizes...>;
			};

			template <class EC, std::size_t N, xt::layout_type L, class Tag>
			struct nb_shape_param<xt::xtensor_container<EC, N, L, Tag>>
			{
				using value = ndim<N>;
			};

			template <typename T>
			using nb_shape_param_t = typename nb_shape_param<T>::value;

			template <typename T>
			using scalar_t = std::remove_const_t<typename std::decay_t<T>::value_type>;

			template <typename T, bool IsConst>
			struct array_scalar
			{
				using type = std::conditional_t<IsConst, const scalar_t<T>, scalar_t<T>>;
			};

			template <typename T, bool IsConst>
			using array_scalar_t = typename array_scalar<T, IsConst>::type;

			template <typename T, bool IsConst, typename... Extra>
			struct ndarray_for_xtensor
			{
				using scalar = array_scalar_t<T, IsConst>;
				using order_tag = std::conditional_t<T::static_layout == xt::layout_type::row_major,
													 c_contig,
													 std::conditional_t<T::static_layout == xt::layout_type::column_major,
																		f_contig,
																		any_contig>>;

				using type = ndarray<scalar, order_tag, nb_shape_param_t<T>, Extra...>;
			};

			template <typename T, bool IsConst, typename... Extra>
			using ndarray_for_xtensor_t = typename ndarray_for_xtensor<T, IsConst, Extra...>::type;

			template <class T>
			NB_INLINE bool check_fixed_shape(const T& expected, const ndarray_for_xtensor_t<T, true>& array)
			{
				if (array.ndim() != expected.dimension())
				{
					return false;
				}

				for (std::size_t i = 0; i < array.ndim(); ++i)
				{
					if (static_cast<std::size_t>(array.shape(i)) != static_cast<std::size_t>(expected.shape()[i]))
					{
						return false;
					}
				}
				return true;
			}

			template <class Type>
			NB_INLINE std::vector<std::size_t> shape_from_ndarray(const ndarray_for_xtensor_t<Type, true>& array)
			{
				std::vector<std::size_t> shape(array.ndim());
				for (std::size_t i = 0; i < shape.size(); ++i)
				{
					shape[i] = static_cast<std::size_t>(array.shape(i));
				}
				return shape;
			}

			template <class Type>
			NB_INLINE std::vector<int64_t> strides_from_ndarray(const ndarray_for_xtensor_t<Type, true>& array)
			{
				std::vector<int64_t> strides(array.ndim());
				for (std::size_t i = 0; i < strides.size(); ++i)
				{
					strides[i] = static_cast<int64_t>(array.stride(i));
				}
				return strides;
			}
		}

		template <class Type>
		struct xtensor_type_caster_base
		{
			using self_type = Type;
			using scalar_type = xt_nb_detail::scalar_t<Type>;
			using input_array_t = xt_nb_detail::ndarray_for_xtensor_t<Type, true>;
			using return_array_t = xt_nb_detail::ndarray_for_xtensor_t<Type, false, ::nanobind::numpy>;

			NB_TYPE_CASTER(self_type, make_caster<input_array_t>::Name)

			bool from_python(handle src, uint8_t flags, cleanup_list* cleanup) noexcept
			{
				if (!(flags & NB_IS_CONVERTIBLE) && !xt::detail::check_array<scalar_type>(src))
				{
					return false;
				}

				make_caster<input_array_t> caster;
				uint8_t local_flags = flags_for_local_caster<input_array_t>(flags);

				if (!caster.from_python(src, local_flags, cleanup))
				{
					return false;
				}

				const input_array_t& array = caster.value;

				if constexpr (xt_nb_detail::is_xtensor_fixed_v<self_type>)
				{
					self_type tmp;
					if (!xt_nb_detail::check_fixed_shape(tmp, array))
					{
						return false;
					}
					value = std::move(tmp);
				}
				else if constexpr (xt_nb_detail::is_xtensor_v<self_type>)
				{
					typename self_type::shape_type expected_shape{};
					if (array.ndim() != expected_shape.size())
					{
						return false;
					}

					auto shape = xt_nb_detail::shape_from_ndarray<self_type>(array);
					value = self_type::from_shape(shape);
				}
				else if constexpr (xt_nb_detail::is_xarray_v<self_type>)
				{
					auto shape = xt_nb_detail::shape_from_ndarray<self_type>(array);
					value = self_type::from_shape(shape);
				}
				else if constexpr (xt_nb_detail::is_xstrided_view_v<self_type>)
				{
					return false;
				}
				else
				{
					static_assert(xt_nb_detail::is_xtensor_v<self_type> ||
									  xt_nb_detail::is_xarray_v<self_type> ||
									  xt_nb_detail::is_xtensor_fixed_v<self_type>,
								  "xtensor_type_caster_base received an unsupported type");
				}

				if constexpr (!xt_nb_detail::is_xstrided_view_v<self_type>)
				{
					if (array.size() != value.size())
					{
						return false;
					}

					std::memcpy(value.data(), array.data(), array.size() * sizeof(scalar_type));
					return true;
				}

				return false;
			}

			static handle from_cpp(const self_type& tensor, rv_policy policy, cleanup_list* cleanup) noexcept
			{
				size_t ndim = static_cast<size_t>(tensor.dimension());

				std::vector<std::size_t> shape;
				shape.reserve(ndim);
				for (auto extent : tensor.shape())
				{
					shape.push_back(static_cast<std::size_t>(extent));
				}

				std::vector<int64_t> strides;
				strides.reserve(ndim);
				for (auto stride_val : tensor.strides())
				{
					strides.push_back(static_cast<int64_t>(stride_val) * static_cast<int64_t>(sizeof(scalar_type)));
				}

				void* data_ptr = const_cast<scalar_type*>(tensor.data());
				object owner = steal(handle());

				switch (policy)
				{
				case rv_policy::automatic:
					policy = rv_policy::move;
					break;
				case rv_policy::automatic_reference:
					policy = rv_policy::reference;
					break;
				default:
					break;
				}

				if (policy == rv_policy::move || policy == rv_policy::take_ownership)
				{
					using mutable_type = std::remove_const_t<std::remove_reference_t<self_type>>;
					mutable_type* heap_value = new mutable_type(tensor);
					owner = capsule(heap_value, [](void* ptr) noexcept { delete static_cast<mutable_type*>(ptr); });
					data_ptr = heap_value->data();
					policy = rv_policy::reference;
				}
				else if (policy == rv_policy::copy)
				{
					using mutable_type = std::remove_const_t<std::remove_reference_t<self_type>>;
					mutable_type* heap_value = new mutable_type(tensor);
					owner = capsule(heap_value, [](void* ptr) noexcept { delete static_cast<mutable_type*>(ptr); });
					data_ptr = heap_value->data();
					policy = rv_policy::reference;
				}
				else if (policy == rv_policy::reference_internal && cleanup && cleanup->self())
				{
					owner = borrow(cleanup->self());
					policy = rv_policy::reference;
				}

				const std::size_t* shape_ptr = shape.empty() ? nullptr : shape.data();
				const int64_t* stride_ptr = strides.empty() ? nullptr : strides.data();

				return make_caster<return_array_t>::from_cpp(
					return_array_t(data_ptr,
									ndim,
									shape_ptr,
									owner,
									stride_ptr),
					policy,
					cleanup);
			}
		};
	}
}

#endif
