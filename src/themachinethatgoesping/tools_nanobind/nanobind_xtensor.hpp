// BSD 3-Clause License

// Copyright (c) 2024, SebastianThiede

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.

// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.

// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// source: https://github.com/SebastianThiede/nanobind_xtensor

#ifndef NANOBIND_XTENSOR_CASTER
#define NANOBIND_XTENSOR_CASTER

#include "xtensor/containers/xtensor.hpp"
#include "nanobind/nanobind.h"
#include "nanobind/ndarray.h"
#include <cstring>
#include <type_traits>
#include <vector>

NAMESPACE_BEGIN(NB_NAMESPACE)
NAMESPACE_BEGIN(detail)

namespace nb = nanobind;

// detectors -------------------------------------------------------------------

template<typename T>
struct is_xtensor_fixed : std::false_type {};

template<class ET, class S, xt::layout_type L, bool SH, class Tag>
struct is_xtensor_fixed<xt::xfixed_container<ET, S, L, SH, Tag>> : std::true_type {};

template<typename T>
constexpr bool is_xtensor_fixed_v = is_xtensor_fixed<T>::value;



template<typename T>
struct is_xtensor : std::false_type {};

template<class EC, std::size_t N, xt::layout_type L, class Tag>
struct is_xtensor<xt::xtensor_container<EC, N, L, Tag>> : std::true_type {};

template<typename T>
constexpr bool is_xtensor_v = is_xtensor<T>::value;



template<typename T>
struct is_xarray : std::false_type {};

template<class EC, xt::layout_type L, class SC, class Tag>
struct is_xarray<xt::xarray_container<EC, L, SC, Tag>> : std::true_type {};

template<typename T>
constexpr bool is_xarray_v = is_xarray<T>::value;

// utilities -------------------------------------------------------------------

template<typename T>
struct nb_shape_param {
    using value = nb::detail::unused;
};

template<class ET, xt::layout_type L, bool SH, class Tag, std::size_t... Sizes>
struct nb_shape_param<xt::xfixed_container<ET, xt::xshape<Sizes...>, L, SH, Tag>> {
    using value = nb::shape<Sizes...>;
};

template<class EC, std::size_t N, xt::layout_type L, class Tag>
struct nb_shape_param<xt::xtensor_container<EC, N, L, Tag>> {
    using value = nb::ndim<N>;
};

template<typename T>
using nb_shape_param_v = typename nb_shape_param<T>::value;



// Get scalar type of an xexpression
template<typename T>
using xexpression_scalar_t = typename std::decay_t<T>::value_type;

// Get the nanobind array type for an xtensor
template<typename T, typename... additional>
struct NDArray_for_xtensor {
    using scalar_t = xexpression_scalar_t<T>;
    using type = ndarray<
        scalar_t,
        std::conditional_t<T::static_layout == xt::layout_type::row_major,
            nb::c_contig,
            std::conditional_t<T::static_layout == xt::layout_type::column_major,
                nb::f_contig, 
                nb::any_contig
            >
        >,
        nb_shape_param_v<T>,
        additional...
    >;
};

template<typename T, typename... additional>
using NDArray_for_xtensor_t = typename NDArray_for_xtensor<T, additional...>::type;

// const version
template<typename T, typename... additional>
struct constNDArray_for_xtensor {
    using scalar_t = std::add_const_t<xexpression_scalar_t<T>>;
    using type = ndarray<
        scalar_t,
        std::conditional_t<T::static_layout == xt::layout_type::row_major,
            nb::c_contig,
            std::conditional_t<T::static_layout == xt::layout_type::column_major,
                nb::f_contig, 
                nb::any_contig
            >
        >,
        nb_shape_param_v<T>,
        additional...
    >;
};
template<typename T, typename... additional>
using constNDArray_for_xtensor_t = typename constNDArray_for_xtensor<T, additional...>::type;

// Bind xtensor ----------------------------------------------------------------
template<typename T>
struct type_caster<T, enable_if_t<
                        (is_xtensor_fixed_v<T> || is_xtensor_v<T> || is_xarray_v<T>) &&
                        is_ndarray_scalar_v<xexpression_scalar_t<T>>
                      >>
{
    using self_t = T;
    using self_shape_t = std::conditional_t<is_xtensor_fixed_v<T>, std::array<std::size_t, T::rank>, typename T::shape_type>;
    using NDArray_t = NDArray_for_xtensor_t<T>;
    using constNDArray_t = constNDArray_for_xtensor_t<T>;
    using NDArray_return_t = NDArray_for_xtensor_t<T, nb::numpy>;

    NB_TYPE_CASTER(self_t, make_caster<NDArray_t>::Name)

    bool from_python(
        handle src,
        uint8_t flags,
        cleanup_list* cleanup
    ) noexcept
    {
        make_caster<constNDArray_t> caster;

        flags = flags_for_local_caster<constNDArray_t>(flags);

        bool succ = caster.from_python(src, flags, cleanup);
        if (!succ)
            return false;
        
        constNDArray_t& NDArray = caster.value;

        value = self_t();

        if constexpr (!is_xtensor_fixed_v<self_t>)
        {
            self_shape_t shape{NDArray.ndim()};
            for (std::size_t i = 0; i < NDArray.ndim(); i++)
            {
                shape[i] = NDArray.shape(i);
            }
            value.resize(shape);
        };

        memcpy(value.data(), NDArray.data(), NDArray.size() * sizeof(typename constNDArray_for_xtensor<self_t>::scalar_t));

        return true;
    };

    static handle from_cpp(
        const self_t& tensor,
        rv_policy policy,
        cleanup_list *cleanup
    ) noexcept
    {
        const auto ndim = static_cast<size_t>(tensor.dimension());

        std::vector<size_t> shape;
        shape.reserve(ndim);
        for (auto extent : tensor.shape())
        {
            shape.push_back(static_cast<size_t>(extent));
        }

        std::vector<int64_t> stride_buffer;
        stride_buffer.reserve(ndim);
        if (ndim > 0)
        {
            for (auto stride_value : tensor.strides())
            {
                stride_buffer.push_back(static_cast<int64_t>(stride_value));
            }
        }

        void* ptr = (void *) tensor.data();

        switch (policy) {
            case rv_policy::automatic:
                policy = rv_policy::move;
                break;

            case rv_policy::automatic_reference:
                policy = rv_policy::reference;
                break;

            default: // leave policy unchanged
                break;
        }

        object owner = steal(handle());
        if (policy == rv_policy::move) {
            self_t *temp = new self_t(std::move(tensor));
            owner = capsule(temp, [](void *p) noexcept { delete (self_t *) p; });
            ptr = temp->data();
            policy = rv_policy::reference;
        } else if (policy == rv_policy::reference_internal && cleanup->self()) {
            owner = borrow(cleanup->self());
            policy = rv_policy::reference;
        }

        const size_t* shape_ptr = shape.empty() ? nullptr : shape.data();
        const int64_t* stride_ptr = stride_buffer.empty() ? nullptr : stride_buffer.data();

        object o = steal(
            make_caster<NDArray_return_t>::from_cpp(
                NDArray_return_t(
                    ptr,
                    ndim,
                    shape_ptr,
                    owner,
                    stride_ptr
                    ),
                policy,
                cleanup
            )
        );

        return o.release();
    };
};

NAMESPACE_END(detail)
NAMESPACE_END(NB_NAMESPACE)

#endif