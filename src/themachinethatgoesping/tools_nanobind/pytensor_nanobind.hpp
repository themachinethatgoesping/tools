// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/pytensor_nanobind.doc.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <utility>

#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

#include <xtl/xsequence.hpp>

#include <xtensor/containers/xarray.hpp>
#include <xtensor/containers/xbuffer_adaptor.hpp>
#include <xtensor/containers/xtensor.hpp>
#include <xtensor/containers/xscalar.hpp>
#include <xtensor/core/xassign.hpp>
#include <xtensor/core/xeval.hpp>

namespace xt
{
    namespace nanobind
    {
        namespace detail
        {
            template <class TensorRef, class IndicesContainer, std::size_t Dim>
            class pytensor_index_view
            {
            public:
                using tensor_type = std::remove_reference_t<TensorRef>;
                using value_type = typename tensor_type::value_type;
                using size_type = typename tensor_type::size_type;

                pytensor_index_view(TensorRef tensor, IndicesContainer& indices)
                    : m_tensor(tensor)
                    , m_indices(indices)
                {
                }

                template <class Expression>
                pytensor_index_view& operator=(const Expression& expression)
                {
                    auto evaluated = xt::eval(expression);
                    auto expected_size = m_indices.size();
                    if (evaluated.size() != expected_size)
                    {
                        throw std::runtime_error("pytensor index_view assignment size mismatch");
                    }

                    for (std::size_t idx = 0; idx < expected_size; ++idx)
                    {
                        assign_element(m_indices[idx], static_cast<value_type>(evaluated(idx)));
                    }
                    return *this;
                }

            private:
                template <class Index>
                void assign_element(const Index& index, const value_type& value)
                {
                    assign_element_impl(index, value, std::make_index_sequence<Dim>{});
                }

                template <class Index, std::size_t... Axis>
                void assign_element_impl(const Index& index, const value_type& value, std::index_sequence<Axis...>)
                {
                    m_tensor(static_cast<size_type>(index[Axis])...) = value;
                }

                TensorRef m_tensor;
                IndicesContainer& m_indices;
            };
        } // namespace detail

        namespace detail
        {
            template <class Strides, class Shape>
            inline bool is_row_major(const Strides& strides, const Shape& shape)
            {
                using size_type = typename Shape::value_type;
                constexpr std::size_t rank = std::tuple_size_v<Shape>;
                if constexpr (rank <= 1)
                {
                    return true;
                }

                auto expected = static_cast<std::make_signed_t<size_type>>(1);
                for (std::ptrdiff_t axis = static_cast<std::ptrdiff_t>(rank) - 1; axis >= 0; --axis)
                {
                    if (static_cast<std::make_signed_t<size_type>>(strides[static_cast<size_type>(axis)]) != expected)
                    {
                        return false;
                    }
                    expected *= static_cast<std::make_signed_t<size_type>>(shape[static_cast<size_type>(axis)]);
                }
                return true;
            }

            template <class Strides, class Shape>
            inline bool is_column_major(const Strides& strides, const Shape& shape)
            {
                using size_type = typename Shape::value_type;
                constexpr std::size_t rank = std::tuple_size_v<Shape>;
                if constexpr (rank <= 1)
                {
                    return true;
                }

                auto expected = static_cast<std::make_signed_t<size_type>>(1);
                for (size_type axis = 0; axis < rank; ++axis)
                {
                    if (static_cast<std::make_signed_t<size_type>>(strides[axis]) != expected)
                    {
                        return false;
                    }
                    expected *= static_cast<std::make_signed_t<size_type>>(shape[axis]);
                }
                return true;
            }

            template <class Shape, class Strides>
            inline void compute_contiguous_strides_row_major(Shape& shape, Strides& strides)
            {
                using size_type = typename Shape::value_type;
                constexpr std::size_t rank = std::tuple_size_v<Shape>;
                if constexpr (rank == 0)
                {
                    return;
                }

                strides.back() = size_type(1);
                for (std::ptrdiff_t axis = static_cast<std::ptrdiff_t>(rank) - 2; axis >= 0; --axis)
                {
                    auto next_axis = static_cast<size_type>(axis + 1);
                    strides[static_cast<size_type>(axis)] = strides[next_axis] * std::max(shape[next_axis], size_type(1));
                }
            }

            template <class Shape, class Strides>
            inline void compute_contiguous_strides_column_major(Shape& shape, Strides& strides)
            {
                using size_type = typename Shape::value_type;
                constexpr std::size_t rank = std::tuple_size_v<Shape>;
                if constexpr (rank == 0)
                {
                    return;
                }

                strides.front() = size_type(1);
                for (size_type axis = 1; axis < rank; ++axis)
                {
                    auto previous_axis = static_cast<size_type>(axis - 1);
                    strides[axis] = strides[previous_axis] * std::max(shape[previous_axis], size_type(1));
                }
            }
        } // namespace detail

        template <class T, std::size_t N, layout_type Layout = layout_type::dynamic>
        class pytensor
            : public xtensor_adaptor<
                  xt::xbuffer_adaptor<
                      std::conditional_t<std::is_const_v<T>, const std::remove_const_t<T>*, std::remove_const_t<T>*>,
                      xt::no_ownership,
                      std::allocator<std::remove_const_t<T>>>,
                  N,
                  layout_type::dynamic>
        {
        private:
            using base_type = xtensor_adaptor<
                xt::xbuffer_adaptor<
                    std::conditional_t<std::is_const_v<T>, const std::remove_const_t<T>*, std::remove_const_t<T>*>,
                    xt::no_ownership,
                    std::allocator<std::remove_const_t<T>>>,
                N,
                layout_type::dynamic>;

        public:
            using self_type = pytensor<T, N, Layout>;
            using scalar_type = std::remove_const_t<T>;
            using ndarray_scalar_type = std::conditional_t<std::is_const_v<T>, const scalar_type, scalar_type>;
            using ndarray_type = ::nanobind::ndarray<
                ndarray_scalar_type,
                ::nanobind::ndim<N>,
                ::nanobind::numpy,
                ::nanobind::any_contig>;
            using buffer_type = typename base_type::storage_type;
            using size_type = typename base_type::size_type;
            using shape_type = typename base_type::shape_type;
            using strides_type = typename base_type::strides_type;
            using value_type = scalar_type;
            using reference = std::conditional_t<std::is_const_v<T>, const scalar_type&, scalar_type&>;
            using const_reference = const scalar_type&;
            using pointer = std::conditional_t<std::is_const_v<T>, const scalar_type*, scalar_type*>;
            using const_pointer = const scalar_type*;

            pytensor()
                : base_type(buffer_type{})
            {
                shape_type shape{};
                strides_type strides{};
                if constexpr (std::tuple_size_v<shape_type> > 0)
                {
                    shape.fill(size_type(0));
                    strides.fill(size_type(0));
                }
                this->resize(shape, strides);
            }

            explicit pytensor(ndarray_type array)
                : base_type(buffer_type{})
            {
                reset_from_ndarray(std::move(array));
            }

            pytensor(const pytensor&) = default;
            pytensor(pytensor&&) noexcept = default;
            pytensor& operator=(const pytensor&) = default;
            pytensor& operator=(pytensor&&) noexcept = default;

            using base_type::operator=;
            using base_type::operator+=;
            using base_type::operator-=;
            using base_type::operator*=;
            using base_type::operator/=;

            ~pytensor() = default;

            template <class ShapeLike>
            static self_type from_shape(ShapeLike&& shape_like)
            {
                static_assert(!std::is_const_v<T>, "pytensor::from_shape requires a mutable tensor type");

                shape_type shape = xtl::forward_sequence<shape_type, ShapeLike>(std::forward<ShapeLike>(shape_like));

                strides_type strides{};
                if constexpr (std::tuple_size_v<strides_type> > 0)
                {
                    if constexpr (Layout == layout_type::column_major)
                    {
                        detail::compute_contiguous_strides_column_major(shape, strides);
                    }
                    else
                    {
                        detail::compute_contiguous_strides_row_major(shape, strides);
                    }
                }

                constexpr std::size_t rank = std::tuple_size_v<shape_type>;
                std::array<size_t, rank> shape_buffer{};
                size_t total_size = 1;
                if constexpr (rank > 0)
                {
                    for (std::size_t axis = 0; axis < rank; ++axis)
                    {
                        size_t extent = static_cast<size_t>(shape[axis]);
                        shape_buffer[axis] = extent;
                        total_size *= extent;
                    }
                }

                constexpr std::size_t stride_rank = std::tuple_size_v<strides_type>;
                std::array<int64_t, stride_rank> stride_buffer{};
                if constexpr (stride_rank > 0)
                {
                    for (std::size_t axis = 0; axis < stride_rank; ++axis)
                    {
                        stride_buffer[axis] = static_cast<int64_t>(strides[axis]);
                    }
                }

                scalar_type* raw_ptr = nullptr;
                ::nanobind::object owner;
                if (total_size > 0)
                {
                    raw_ptr = new scalar_type[total_size]();
                    owner = ::nanobind::capsule(
                        raw_ptr,
                        [](void* p) noexcept { delete[] static_cast<scalar_type*>(p); });
                }

                char order = 'C';
                if constexpr (Layout == layout_type::column_major)
                {
                    order = 'F';
                }

                ndarray_type array(
                    static_cast<pointer>(raw_ptr),
                    rank,
                    rank > 0 ? shape_buffer.data() : nullptr,
                    owner.ptr(),
                    stride_rank > 0 ? stride_buffer.data() : nullptr,
                    ::nanobind::dtype<ndarray_scalar_type>(),
                    (int) ::nanobind::device::cpu::value,
                    0,
                    order);

                return self_type(std::move(array));
            }

            template <class Integral,
                      std::enable_if_t<std::is_integral_v<std::decay_t<Integral>>, int> = 0>
            static self_type from_shape(std::initializer_list<Integral> shape_list)
            {
                shape_type shape{};
                std::size_t axis = 0;

                for (auto extent : shape_list)
                {
                    if (axis >= shape.size())
                    {
                        throw std::runtime_error("pytensor::from_shape received too many dimensions");
                    }
                    shape[axis++] = static_cast<size_type>(extent);
                }

                for (; axis < shape.size(); ++axis)
                {
                    shape[axis] = size_type(0);
                }

                return from_shape(std::move(shape));
            }

            template <class Array>
            void reset_from_ndarray(Array&& array [[maybe_unused]])
            {
                ndarray_type nb_array(std::forward<Array>(array));

                auto shape = compute_shape(nb_array);
                auto strides = compute_strides(nb_array, shape);

                if constexpr (Layout == layout_type::row_major)
                {
                    if (!detail::is_row_major(strides, shape))
                    {
                        throw std::runtime_error("Expected row-major contiguous array for pytensor");
                    }
                }
                else if constexpr (Layout == layout_type::column_major)
                {
                    if (!detail::is_column_major(strides, shape))
                    {
                        throw std::runtime_error("Expected column-major contiguous array for pytensor");
                    }
                }

                this->reset_buffer(nb_array.data(), static_cast<size_type>(nb_array.size()));
                this->resize(shape, strides);
                m_array = std::move(nb_array);

                if constexpr (Layout == layout_type::dynamic)
                {
                    this->mutable_layout() = deduce_layout(m_array, shape, strides);
                }
                else
                {
                    this->mutable_layout() = Layout;
                }
            }

            void reset_from_ndarray(ndarray_type array)
            {
                reset_from_ndarray<ndarray_type>(std::move(array));
            }

            template <class Array>
            void bind(Array&& array)
            {
                reset_from_ndarray(std::forward<Array>(array));
            }

            void bind(ndarray_type array)
            {
                reset_from_ndarray(std::move(array));
            }

            bool is_valid() const noexcept
            {
                return m_array.is_valid();
            }

            ndarray_type& ndarray() noexcept
            {
                return m_array;
            }

            const ndarray_type& ndarray() const noexcept
            {
                return m_array;
            }

        private:
            static shape_type compute_shape(const ndarray_type& array)
            {
                shape_type shape{};
                if constexpr (std::tuple_size_v<shape_type> > 0)
                {
                    for (std::size_t axis = 0; axis < shape.size(); ++axis)
                    {
                        shape[axis] = static_cast<size_type>(array.shape(axis));
                    }
                }
                return shape;
            }

            static strides_type compute_strides(const ndarray_type& array, const shape_type& shape)
            {
                strides_type strides{};
                if constexpr (std::tuple_size_v<strides_type> == 0)
                {
                    return strides;
                }

                const int64_t* strides_ptr = array.stride_ptr();
                if (strides_ptr == nullptr)
                {
                    if constexpr (Layout == layout_type::column_major)
                    {
                        detail::compute_contiguous_strides_column_major(shape, strides);
                    }
                    else
                    {
                        detail::compute_contiguous_strides_row_major(shape, strides);
                    }
                }
                else
                {
                    for (std::size_t axis = 0; axis < strides.size(); ++axis)
                    {
                        const auto raw_stride = strides_ptr[axis];

                        using stride_value_type = typename strides_type::value_type;
                        if constexpr (std::is_signed_v<stride_value_type>)
                        {
                            strides[axis] = static_cast<stride_value_type>(raw_stride);
                        }
                        else
                        {
                            if (raw_stride < 0)
                            {
                                throw std::runtime_error("pytensor: negative strides are not supported");
                            }
                            strides[axis] = static_cast<stride_value_type>(raw_stride);
                        }
                    }
                }
                return strides;
            }

            static layout_type deduce_layout(const ndarray_type& array,
                                             const shape_type& shape,
                                             const strides_type& strides)
            {
                if constexpr (Layout != layout_type::dynamic)
                {
                    return Layout;
                }

                if constexpr (std::tuple_size_v<shape_type> <= 1)
                {
                    return layout_type::row_major;
                }

                if (array.stride_ptr() == nullptr)
                {
                    return layout_type::row_major;
                }

                if (detail::is_row_major(strides, shape))
                {
                    return layout_type::row_major;
                }

                if (detail::is_column_major(strides, shape))
                {
                    return layout_type::column_major;
                }

                return layout_type::dynamic;
            }

            ndarray_type m_array;
        };
    } // namespace nanobind
} // namespace xt

namespace xt
{
    template <class T, std::size_t N, layout_type Layout>
    struct xcontainer_inner_types<nanobind::pytensor<T, N, Layout>>
    {
        using tensor_type = nanobind::pytensor<T, N, Layout>;
        using storage_type = typename tensor_type::buffer_type;
        using reference = typename tensor_type::reference;
        using const_reference = typename tensor_type::const_reference;
        using size_type = typename tensor_type::size_type;
        using shape_type = typename tensor_type::shape_type;
        using strides_type = typename tensor_type::strides_type;
        using backstrides_type = typename tensor_type::strides_type;
        using inner_shape_type = shape_type;
        using inner_strides_type = strides_type;
        using inner_backstrides_type = backstrides_type;
        using temporary_type = tensor_type;
        static constexpr layout_type layout = Layout;
    };

    template <class T, std::size_t N, layout_type Layout>
    struct xiterable_inner_types<nanobind::pytensor<T, N, Layout>>
        : xcontainer_iterable_types<nanobind::pytensor<T, N, Layout>>
    {
    };

    namespace detail
    {
        template <class T, std::size_t N, layout_type Layout>
        struct is_crtp_base_of_impl<xexpression, nanobind::pytensor<T, N, Layout>> : std::true_type
        {
        };
    }

    template <class From, class T, std::size_t N, layout_type Layout>
    struct has_assign_conversion<From, nanobind::pytensor<T, N, Layout>> : std::false_type
    {
    };

    template <class T, std::size_t N, layout_type Layout, class Indices>
    inline auto index_view(nanobind::pytensor<T, N, Layout>& tensor, Indices& indices)
    {
        return nanobind::detail::pytensor_index_view<nanobind::pytensor<T, N, Layout>&, Indices, N>(tensor, indices);
    }
}

namespace themachinethatgoesping::tools_nanobind
{
    template <class T, std::size_t N, xt::layout_type Layout = xt::layout_type::dynamic>
    using pytensor = xt::nanobind::pytensor<T, N, Layout>;
}

NAMESPACE_BEGIN(NB_NAMESPACE)
NAMESPACE_BEGIN(detail)

    template <class T, std::size_t N, xt::layout_type Layout>
    struct type_caster<xt::nanobind::pytensor<T, N, Layout>>
    {
        using tensor_type = xt::nanobind::pytensor<T, N, Layout>;
        using scalar_type = std::remove_const_t<T>;
        using ndarray_scalar_type = std::conditional_t<std::is_const_v<T>, const scalar_type, scalar_type>;
        using ndarray_type = ::nanobind::ndarray<
            ndarray_scalar_type,
            ::nanobind::ndim<N>,
            ::nanobind::numpy,
            ::nanobind::any_contig>;

        NB_TYPE_CASTER(tensor_type, type_caster<ndarray_type>::Name)

        bool from_python(handle src, uint8_t flags, cleanup_list* cleanup) noexcept
        {
            make_caster<ndarray_type> caster;
            flags = flags_for_local_caster<ndarray_type>(flags);
            if (!caster.from_python(src, flags, cleanup))
            {
                return false;
            }

            try
            {
                value.reset_from_ndarray(std::move(caster.value));
            }
            catch (...)
            {
                return false;
            }
            return true;
        }

        static handle from_cpp(const tensor_type& tensor, rv_policy policy, cleanup_list* cleanup) noexcept
        {
            return make_caster<ndarray_type>::from_cpp(tensor.ndarray(), policy, cleanup);
        }
    };

    template <class T, std::size_t N, xt::layout_type Layout>
    struct type_caster<xt::xexpression<xt::nanobind::pytensor<T, N, Layout>>>
        : type_caster<xt::nanobind::pytensor<T, N, Layout>>
    {
        using expression_type = xt::xexpression<xt::nanobind::pytensor<T, N, Layout>>;
        using base_caster = type_caster<xt::nanobind::pytensor<T, N, Layout>>;

        operator expression_type&()
        {
            return this->value;
        }

        operator const expression_type&()
        {
            return this->value;
        }
    };

NAMESPACE_END(detail)
NAMESPACE_END(NB_NAMESPACE)
