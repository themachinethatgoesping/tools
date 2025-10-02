/***************************************************************************
* Copyright (c) Wolf Vollprecht, Johan Mabille and Sylvain Corlay          *
* Copyright (c) QuantStack                                                 *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef PY_TENSOR_HPP
#define PY_TENSOR_HPP

#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <utility>

#include "xtensor/containers/xbuffer_adaptor.hpp"
#include "xtensor/core/xiterator.hpp"
#include "xtensor/core/xsemantic.hpp"
#include "xtensor/utils/xutils.hpp"

#include "pycontainer.hpp"
#include "pystrides_adaptor.hpp"
#include "pynative_casters.hpp"
#include "xtensor_python_config.hpp"

namespace xt
{
    template <class T, std::size_t N, layout_type L = layout_type::dynamic>
    class pytensor;
}

namespace nanobind
{
    namespace detail
    {
        template <class T, std::size_t N, xt::layout_type L>
        struct type_caster<xt::pytensor<T, N, L>>
        {
            using Value = xt::pytensor<T, N, L>;

            NB_TYPE_CASTER(Value, make_caster<ndarray<numpy>>::Name)

            bool from_python(handle src, uint8_t flags, cleanup_list* cleanup) noexcept
            {
                NB_UNUSED(cleanup);

                if (!(flags & NB_IS_CONVERTIBLE) && !xt::detail::check_array<T>(src))
                {
                    return false;
                }

                try
                {
                    Value tmp = Value::ensure(src);
                    if (!tmp)
                    {
                        return false;
                    }
                    value = std::move(tmp);
                    return true;
                }
                catch (const std::runtime_error&)
                {
                    return false;
                }
            }

            static handle from_cpp(const Value& src, rv_policy, cleanup_list* cleanup) noexcept
            {
                NB_UNUSED(cleanup);
                return handle(src.ptr()).inc_ref();
            }
        };

        template <class T, std::size_t N, xt::layout_type L>
        struct type_caster<xt::xexpression<xt::pytensor<T, N, L>>> : type_caster<xt::pytensor<T, N, L>>
        {
            using Base = type_caster<xt::pytensor<T, N, L>>;
            using Type = xt::xexpression<xt::pytensor<T, N, L>>;

            operator Type&()
            {
                return this->value;
            }

            operator const Type&()
            {
                return this->value;
            }
        };
    }
}

namespace xt
{
    namespace nb = ::nanobind;

    namespace detail
    {
        template <std::size_t N>
        struct numpy_strides
        {
            npy_intp value[N];
        };

        template <>
        struct numpy_strides<0>
        {
            npy_intp* value = nullptr;
        };
    }

    template <class T, std::size_t N, layout_type L>
    struct xiterable_inner_types<pytensor<T, N, L>>
        : xcontainer_iterable_types<pytensor<T, N, L>>
    {
    };

    template <class T, std::size_t N, layout_type L>
    struct xcontainer_inner_types<pytensor<T, N, L>>
    {
        using storage_type = xbuffer_adaptor<T*>;
        using reference = typename storage_type::reference;
        using const_reference = typename storage_type::const_reference;
        using size_type = typename storage_type::size_type;
        using shape_type = std::array<npy_intp, N>;
        using strides_type = shape_type;
        using backstrides_type = shape_type;
        using inner_shape_type = shape_type;
        using inner_strides_type = strides_type;
        using inner_backstrides_type = backstrides_type;
        using temporary_type = pytensor<T, N, L>;
        static constexpr layout_type layout = L;
    };

    /**
     * @class pytensor
     * @brief Multidimensional container providing the xtensor container semantics wrapping a numpy array.
     *
     * pytensor is similar to the xtensor container in that it has a static dimensionality.
     *
     * Unlike the pyarray container, pytensor cannot be reshaped with a different number of dimensions
     * and reshapes are not reflected on the Python side. However, pytensor has benefits compared to pyarray
     * in terms of performances. pytensor shapes are stack-allocated which makes iteration upon pytensor
     * faster than with pyarray.
     *
     * @tparam T The type of the element stored in the pyarray.
     * @sa pyarray
     */
    template <class T, std::size_t N, layout_type L>
    class pytensor : public pycontainer<pytensor<T, N, L>>,
                     public xcontainer_semantic<pytensor<T, N, L>>
    {
    public:

        using self_type = pytensor<T, N, L>;
        using semantic_base = xcontainer_semantic<self_type>;
        using base_type = pycontainer<self_type>;
        using storage_type = typename base_type::storage_type;
        using value_type = typename base_type::value_type;
        using reference = typename base_type::reference;
        using const_reference = typename base_type::const_reference;
        using pointer = typename base_type::pointer;
        using size_type = typename base_type::size_type;
        using shape_type = typename base_type::shape_type;
        using strides_type = typename base_type::strides_type;
        using backstrides_type = typename base_type::backstrides_type;
        using inner_shape_type = typename base_type::inner_shape_type;
        using inner_strides_type = typename base_type::inner_strides_type;
        using inner_backstrides_type = typename base_type::inner_backstrides_type;
        constexpr static std::size_t rank = N;

        pytensor();
        pytensor(nested_initializer_list_t<T, N> t);
        pytensor(nb::handle h, nb::borrowed_t);
        pytensor(nb::handle h, nb::steal_t);
        pytensor(const nb::object& o);

        explicit pytensor(const shape_type& shape, layout_type l = layout_type::row_major);
        explicit pytensor(const shape_type& shape, const_reference value, layout_type l = layout_type::row_major);
        explicit pytensor(const shape_type& shape, const strides_type& strides, const_reference value);
        explicit pytensor(const shape_type& shape, const strides_type& strides);

        template <class S = shape_type>
        static pytensor from_shape(S&& shape);

        pytensor(const self_type& rhs);
        self_type& operator=(const self_type& rhs);

        pytensor(self_type&&) = default;
        self_type& operator=(self_type&& e) = default;

        template <class E>
        pytensor(const xexpression<E>& e);

        template <class E>
        self_type& operator=(const xexpression<E>& e);

        using base_type::begin;
        using base_type::end;

        static self_type ensure(nb::handle h);
        static bool check_(nb::handle h);

    private:

        inner_shape_type m_shape;
        inner_strides_type m_strides;
        inner_backstrides_type m_backstrides;
        storage_type m_storage;

        void init_tensor(const shape_type& shape, const strides_type& strides);
        void init_from_python();

        inner_shape_type& shape_impl() noexcept;
        const inner_shape_type& shape_impl() const noexcept;
        inner_strides_type& strides_impl() noexcept;
        const inner_strides_type& strides_impl() const noexcept;
        inner_backstrides_type& backstrides_impl() noexcept;
        const inner_backstrides_type& backstrides_impl() const noexcept;

        storage_type& storage_impl() noexcept;
        const storage_type& storage_impl() const noexcept;

        friend class xcontainer<pytensor<T, N, L>>;
        friend class pycontainer<pytensor<T, N, L>>;
    };

    /***************************
     * pytensor implementation *
     ***************************/

    /**
     * @name Constructors
     */
    //@{
    /**
     * Allocates an uninitialized pytensor that holds 1 element.
     */
    template <class T, std::size_t N, layout_type L>
    inline pytensor<T, N, L>::pytensor()
        : base_type()
    {
        m_shape = xtl::make_sequence<shape_type>(N, size_type(1));
        m_strides = xtl::make_sequence<strides_type>(N, size_type(0));
        init_tensor(m_shape, m_strides);
        detail::default_initialize(m_storage);
    }

    /**
     * Allocates a pytensor with a nested initializer list.
     */
    template <class T, std::size_t N, layout_type L>
    inline pytensor<T, N, L>::pytensor(nested_initializer_list_t<T, N> t)
        : base_type()
    {
        base_type::resize(xt::shape<shape_type>(t), layout_type::row_major);
        nested_copy(m_storage.begin(), t);
    }

    template <class T, std::size_t N, layout_type L>
    inline pytensor<T, N, L>::pytensor(nb::handle h, nb::borrowed_t b)
        : base_type(h, b)
    {
        init_from_python();
    }

    template <class T, std::size_t N, layout_type L>
    inline pytensor<T, N, L>::pytensor(nb::handle h, nb::steal_t s)
        : base_type(h, s)
    {
        init_from_python();
    }

    template <class T, std::size_t N, layout_type L>
    inline pytensor<T, N, L>::pytensor(const nb::object& o)
        : base_type(o)
    {
        init_from_python();
    }

    /**
     * Allocates an uninitialized pytensor with the specified shape and
     * layout.
     * @param shape the shape of the pytensor
     * @param l the layout_type of the pytensor
     */
    template <class T, std::size_t N, layout_type L>
    inline pytensor<T, N, L>::pytensor(const shape_type& shape, layout_type l)
    {
        compute_strides(shape, l, m_strides);
        init_tensor(shape, m_strides);
    }

    /**
     * Allocates a pytensor with the specified shape and layout. Elements
     * are initialized to the specified value.
     * @param shape the shape of the pytensor
     * @param value the value of the elements
     * @param l the layout_type of the pytensor
     */
    template <class T, std::size_t N, layout_type L>
    inline pytensor<T, N, L>::pytensor(const shape_type& shape,
                                    const_reference value,
                                    layout_type l)
    {
        compute_strides(shape, l, m_strides);
        init_tensor(shape, m_strides);
        std::fill(m_storage.begin(), m_storage.end(), value);
    }

    /**
     * Allocates an uninitialized pytensor with the specified shape and strides.
     * Elements are initialized to the specified value.
     * @param shape the shape of the pytensor
     * @param strides the strides of the pytensor
     * @param value the value of the elements
     */
    template <class T, std::size_t N, layout_type L>
    inline pytensor<T, N, L>::pytensor(const shape_type& shape,
                                    const strides_type& strides,
                                    const_reference value)
    {
        init_tensor(shape, strides);
        std::fill(m_storage.begin(), m_storage.end(), value);
    }

    /**
     * Allocates an uninitialized pytensor with the specified shape and strides.
     * @param shape the shape of the pytensor
     * @param strides the strides of the pytensor
     */
    template <class T, std::size_t N, layout_type L>
    inline pytensor<T, N, L>::pytensor(const shape_type& shape,
                                    const strides_type& strides)
    {
        init_tensor(shape, strides);
    }

    /**
     * Allocates and returns an pytensor with the specified shape.
     * @param shape the shape of the pytensor
     */
    template <class T, std::size_t N, layout_type L>
    template <class S>
    inline pytensor<T, N, L> pytensor<T, N, L>::from_shape(S&& shape)
    {
        detail::check_dims<shape_type>::run(shape.size());
        auto shp = xtl::forward_sequence<shape_type, S>(shape);
        return self_type(shp);
    }
    //@}

    /**
     * @name Copy semantic
     */
    //@{
    /**
     * The copy constructor.
     */
    template <class T, std::size_t N, layout_type L>
    inline pytensor<T, N, L>::pytensor(const self_type& rhs)
        : base_type(), semantic_base(rhs)
    {
        init_tensor(rhs.shape(), rhs.strides());
        std::copy(rhs.storage().cbegin(), rhs.storage().cend(), this->storage().begin());
    }

    /**
     * The assignment operator.
     */
    template <class T, std::size_t N, layout_type L>
    inline auto pytensor<T, N, L>::operator=(const self_type& rhs) -> self_type&
    {
        self_type tmp(rhs);
        *this = std::move(tmp);
        return *this;
    }
    //@}

    /**
     * @name Extended copy semantic
     */
    //@{
    /**
     * The extended copy constructor.
     */
    template <class T, std::size_t N, layout_type L>
    template <class E>
    inline pytensor<T, N, L>::pytensor(const xexpression<E>& e)
        : base_type()
    {
        shape_type shape = xtl::forward_sequence<shape_type, decltype(e.derived_cast().shape())>(e.derived_cast().shape());
        strides_type strides = xtl::make_sequence<strides_type>(N, size_type(0));
        compute_strides(shape, layout_type::row_major, strides);
        init_tensor(shape, strides);
        semantic_base::assign(e);
    }

    /**
     * The extended assignment operator.
     */
    template <class T, std::size_t N, layout_type L>
    template <class E>
    inline auto pytensor<T, N, L>::operator=(const xexpression<E>& e) -> self_type&
    {
        return semantic_base::operator=(e);
    }
    //@}

    template <class T, std::size_t N, layout_type L>
    inline auto pytensor<T, N, L>::ensure(nb::handle h) -> self_type
    {
        return base_type::ensure(h);
    }

    template <class T, std::size_t N, layout_type L>
    inline bool pytensor<T, N, L>::check_(nb::handle h)
    {
        return base_type::check_(h);
    }

    template <class T, std::size_t N, layout_type L>
    inline void pytensor<T, N, L>::init_tensor(const shape_type& shape, const strides_type& strides)
    {
        detail::numpy_strides<N> python_strides;
        std::transform(strides.begin(), strides.end(), python_strides.value,
                       [](auto v) { return sizeof(T) * v; });

        int flags = NPY_ARRAY_ALIGNED;
        if (!std::is_const<T>::value)
        {
            flags |= NPY_ARRAY_WRITEABLE;
        }

        auto dtype_obj = nb::dtype<T>();
        PyObject* dtype_ptr = dtype_obj.ptr();
        Py_INCREF(dtype_ptr);

        PyObject* raw = reinterpret_cast<PyObject*>(
            PyArray_NewFromDescr(&PyArray_Type,
                                 reinterpret_cast<PyArray_Descr*>(dtype_ptr),
                                 static_cast<int>(shape.size()),
                                 const_cast<npy_intp*>(shape.data()),
                                 python_strides.value,
                                 nullptr,
                                 flags,
                                 nullptr));

        if (raw == nullptr)
        {
            throw std::runtime_error("NumPy: unable to create ndarray");
        }

        this->m_ptr = raw;
        m_shape = shape;
        m_strides = strides;
        adapt_strides(m_shape, m_strides, m_backstrides);
        m_storage = storage_type(reinterpret_cast<pointer>(PyArray_DATA(this->python_array())),
                                 static_cast<size_type>(PyArray_SIZE(this->python_array())));
    }

    template <class T, std::size_t N, layout_type L>
    inline void pytensor<T, N, L>::init_from_python()
    {
        if (!static_cast<bool>(*this))
        {
            return;
        }

        if (PyArray_NDIM(this->python_array()) != static_cast<int>(N))
        {
            throw std::runtime_error("NumPy: ndarray has incorrect number of dimensions");
        }

        std::copy(PyArray_DIMS(this->python_array()),
                  PyArray_DIMS(this->python_array()) + N,
                  m_shape.begin());
        std::transform(PyArray_STRIDES(this->python_array()),
                       PyArray_STRIDES(this->python_array()) + N,
                       m_strides.begin(),
                       [](auto v) { return v / sizeof(T); });
        adapt_strides(m_shape, m_strides, m_backstrides);

        if (L != layout_type::dynamic && !do_strides_match(m_shape, m_strides, L, 1))
        {
            throw std::runtime_error("NumPy: passing container with bad strides for layout (is it a view?).");
        }

        m_storage = storage_type(reinterpret_cast<pointer>(PyArray_DATA(this->python_array())),
                                 this->get_buffer_size());
    }

    template <class T, std::size_t N, layout_type L>
    inline auto pytensor<T, N, L>::shape_impl() noexcept -> inner_shape_type&
    {
        return m_shape;
    }

    template <class T, std::size_t N, layout_type L>
    inline auto pytensor<T, N, L>::shape_impl() const noexcept -> const inner_shape_type&
    {
        return m_shape;
    }

    template <class T, std::size_t N, layout_type L>
    inline auto pytensor<T, N, L>::strides_impl() noexcept -> inner_strides_type&
    {
        return m_strides;
    }

    template <class T, std::size_t N, layout_type L>
    inline auto pytensor<T, N, L>::strides_impl() const noexcept -> const inner_strides_type&
    {
        return m_strides;
    }

    template <class T, std::size_t N, layout_type L>
    inline auto pytensor<T, N, L>::backstrides_impl() noexcept -> inner_backstrides_type&
    {
        return m_backstrides;
    }

    template <class T, std::size_t N, layout_type L>
    inline auto pytensor<T, N, L>::backstrides_impl() const noexcept -> const inner_backstrides_type&
    {
        return m_backstrides;
    }

    template <class T, std::size_t N, layout_type L>
    inline auto pytensor<T, N, L>::storage_impl() noexcept -> storage_type&
    {
        return m_storage;
    }

    template <class T, std::size_t N, layout_type L>
    inline auto pytensor<T, N, L>::storage_impl() const noexcept -> const storage_type&
    {
        return m_storage;
    }
}

#endif
