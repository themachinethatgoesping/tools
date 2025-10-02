/***************************************************************************
* Copyright (c) Wolf Vollprecht, Johan Mabille and Sylvain Corlay          *
* Copyright (c) QuantStack                                                 *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef PY_CONTAINER_HPP
#define PY_CONTAINER_HPP

#include <algorithm>
#include <array>
#include <cmath>
#include <complex>
#include <cstddef>
#include <functional>
#include <limits>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <type_traits>

#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/complex.h>

#ifndef FORCE_IMPORT_ARRAY
#define NO_IMPORT_ARRAY
#endif
#ifndef PY_ARRAY_UNIQUE_SYMBOL
#define PY_ARRAY_UNIQUE_SYMBOL xtensor_python_ARRAY_API
#endif
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

// Required because pyconfig.hpp defines copysign to _copysign
#undef copysign

#include "xtensor/containers/xcontainer.hpp"

#include "xtl/xsequence.hpp"
#include "xtl/xcomplex.hpp"

namespace xt
{

    namespace nb = ::nanobind;

    /**
     * @class pycontainer
     * @brief Base class for xtensor containers wrapping numpy arrays using nanobind.
     *
     * The pycontainer class should not be instantiated directly. Instead, users should
     * use pytensor and pyarray instances.
     *
     * @tparam D The derived type, i.e. the inheriting class for which pycontainer
     *           provides the interface.
     */
    template <class D>
    class pycontainer : public nb::object,
                        public xcontainer<D>
    {
    public:

        using derived_type = D;

        using base_type = xcontainer<D>;
        using inner_types = xcontainer_inner_types<D>;
        using storage_type = typename inner_types::storage_type;
        using value_type = typename storage_type::value_type;
        using reference = typename storage_type::reference;
        using const_reference = typename storage_type::const_reference;
        using pointer = typename storage_type::pointer;
        using const_pointer = typename storage_type::const_pointer;
        using size_type = typename storage_type::size_type;
        using difference_type = typename storage_type::difference_type;

        using shape_type = typename inner_types::shape_type;
        using strides_type = typename inner_types::strides_type;
        using backstrides_type = typename inner_types::backstrides_type;
        using inner_shape_type = typename inner_types::inner_shape_type;
        using inner_strides_type = typename inner_types::inner_strides_type;

        using iterable_base = xcontainer<D>;

        using iterator = typename iterable_base::iterator;
        using const_iterator = typename iterable_base::const_iterator;

        using stepper = typename iterable_base::stepper;
        using const_stepper = typename iterable_base::const_stepper;

        template <class S = shape_type>
        void resize(const S& shape);
        template <class S = shape_type>
        void resize(const S& shape, layout_type l);
        template <class S = shape_type>
        void resize(const S& shape, const strides_type& strides);

        template <class S = shape_type>
        auto& reshape(S&& shape, layout_type layout = base_type::static_layout) &;

        layout_type layout() const;
        bool is_contiguous() const noexcept;

        using base_type::operator();
        using base_type::operator[];
        using base_type::begin;
        using base_type::end;

    protected:

        pycontainer();
        ~pycontainer() = default;

        pycontainer(nb::handle h, nb::borrowed_t);
        pycontainer(nb::handle h, nb::steal_t);
        pycontainer(const nb::object& o);

        pycontainer(const pycontainer&) = default;
        pycontainer& operator=(const pycontainer&) = default;

        pycontainer(pycontainer&&) = default;
        pycontainer& operator=(pycontainer&&) = default;

        static derived_type ensure(nb::handle h);
        static bool check_(nb::handle h);
        static PyObject* raw_array_t(PyObject* ptr);

        derived_type& derived_cast();
        const derived_type& derived_cast() const;

        PyArrayObject* python_array() const;
        size_type get_buffer_size() const;
    };

    namespace detail
    {
        inline constexpr int log2(std::size_t n, int k = 0)
        {
            return (n <= 1) ? k : log2(n >> 1, k + 1);
        }

        template <class T, class Enable = void>
        struct is_fmt_numeric
        {
            static constexpr bool value = false;
        };

        template <class T>
        struct is_fmt_numeric<T, std::enable_if_t<std::is_arithmetic_v<std::remove_cv_t<T>>>>
        {
            static constexpr bool value = true;
            using plain_t = std::remove_cv_t<T>;
            static constexpr int index = std::is_same_v<plain_t, bool>
                                             ? 0
                                             : 1 + (std::is_integral_v<plain_t>
                                                        ? log2(sizeof(plain_t)) * 2 + std::is_unsigned_v<plain_t>
                                                        : 8 + (std::is_same_v<plain_t, double>
                                                                   ? 1
                                                                   : std::is_same_v<plain_t, long double> ? 2 : 0));
        };

        template <class T>
        struct is_fmt_numeric<std::complex<T>, std::enable_if_t<std::is_floating_point_v<T>>>
        {
            static constexpr bool value = true;
            static constexpr int index = is_fmt_numeric<T>::index + 3;
        };

        template <class T, template <class> class... Predicates>
        struct satisfies_any_of
            : std::bool_constant<(Predicates<std::decay_t<T>>::value || ...)>;

        template <class T, class E = void>
        struct numpy_traits;

        template <class T>
        struct numpy_traits<T, std::enable_if_t<satisfies_any_of<T, std::is_arithmetic, xtl::is_complex>::value>>
        {
        private:
            using value_type = std::remove_const_t<T>;
            constexpr static const int value_list[15] = {
                NPY_BOOL,
                NPY_BYTE, NPY_UBYTE, NPY_SHORT, NPY_USHORT,
                NPY_INT32, NPY_UINT32, NPY_INT64, NPY_UINT64,
                NPY_FLOAT, NPY_DOUBLE, NPY_LONGDOUBLE,
                NPY_CFLOAT, NPY_CDOUBLE, NPY_CLONGDOUBLE};

        public:
            static constexpr int type_num = value_list[is_fmt_numeric<value_type>::index];
        };

        template <bool>
        struct numpy_enum_adjuster
        {
            static inline int pyarray_type(PyArrayObject* obj)
            {
                return PyArray_TYPE(obj);
            }
        };

        template <>
        struct numpy_enum_adjuster<true>
        {
            static inline int pyarray_type(PyArrayObject* obj)
            {
                int res = PyArray_TYPE(obj);
                if (res == NPY_LONGLONG || res == NPY_ULONGLONG)
                {
                    res -= 2;
                }
                return res;
            }
        };

        inline int pyarray_type(PyArrayObject* obj)
        {
            return numpy_enum_adjuster<NPY_LONGLONG != NPY_INT64>::pyarray_type(obj);
        }

        template <class T>
        void default_initialize_impl(T& /*storage*/, std::false_type)
        {
        }

        template <class T>
        void default_initialize_impl(T& storage, std::true_type)
        {
            using value_type = typename T::value_type;
            storage[0] = value_type{};
        }

        template <class T>
        void default_initialize(T& storage)
        {
            using value_type = typename T::value_type;
            default_initialize_impl(storage, std::is_copy_assignable<value_type>());
        }

        template <class T>
        bool check_array_type(const nb::handle& src, std::true_type)
        {
            int type_num = numpy_traits<T>::type_num;
            return pyarray_type(reinterpret_cast<PyArrayObject*>(src.ptr())) == type_num;
        }

        template <class T>
        bool check_array_type(const nb::handle& src, std::false_type)
        {
            nb::object dtype = nb::dtype<T>();
            return PyArray_EquivTypes(PyArray_DESCR(reinterpret_cast<PyArrayObject*>(src.ptr())),
                                      reinterpret_cast<PyArray_Descr*>(dtype.ptr())) != 0;
        }

        template <class T>
        bool check_array(const nb::handle& src)
        {
            if (!src || !PyArray_Check(src.ptr()))
            {
                return false;
            }
            using has_numpy_traits = satisfies_any_of<T, std::is_arithmetic, xtl::is_complex>;
            return check_array_type<T>(src, has_numpy_traits{});
        }
    }

    /******************************
     * pycontainer implementation *
     ******************************/

    template <class D>
    inline pycontainer<D>::pycontainer()
        : nb::object()
    {
    }

    template <class D>
    inline pycontainer<D>::pycontainer(nb::handle h, nb::borrowed_t b)
        : nb::object(h, b)
    {
    }

    template <class D>
    inline pycontainer<D>::pycontainer(nb::handle h, nb::steal_t s)
        : nb::object(h, s)
    {
    }

    template <class D>
    inline pycontainer<D>::pycontainer(const nb::object& o)
        : nb::object(nb::steal<nb::object>(raw_array_t(o.ptr())))
    {
        if (!this->m_ptr)
        {
            throw nb::python_error();
        }
    }

    template <class D>
    inline auto pycontainer<D>::ensure(nb::handle h) -> derived_type
    {
        auto raw = raw_array_t(h.ptr());
        if (raw == nullptr)
        {
            PyErr_Clear();
            return derived_type();
        }
        return nb::steal<derived_type>(raw);
    }

    template <class D>
    inline bool pycontainer<D>::check_(nb::handle h)
    {
        return detail::check_array<typename D::value_type>(h);
    }

    template <class D>
    inline PyObject* pycontainer<D>::raw_array_t(PyObject* ptr)
    {
        if (ptr == nullptr)
        {
            return nullptr;
        }

        auto dtype_obj = nb::dtype<value_type>();
        PyObject* dtype_ptr = dtype_obj.ptr();
        Py_INCREF(dtype_ptr);
        auto res = PyArray_FromAny(ptr, reinterpret_cast<PyArray_Descr*>(dtype_ptr), 0, 0,
                                   NPY_ARRAY_ENSUREARRAY | NPY_ARRAY_FORCECAST, nullptr);
        return res;
    }

    template <class D>
    inline PyArrayObject* pycontainer<D>::python_array() const
    {
        return reinterpret_cast<PyArrayObject*>(this->m_ptr);
    }

    template <class D>
    inline auto pycontainer<D>::get_buffer_size() const -> size_type
    {
        const size_type& (*min)(const size_type&, const size_type&) = std::min<size_type>;
        size_type min_stride = this->strides().empty() ? size_type(1) :
            std::max(size_type(1), std::accumulate(this->strides().cbegin(),
                                                   this->strides().cend(),
                                                   std::numeric_limits<size_type>::max(),
                                                   min));
        return min_stride * static_cast<size_type>(PyArray_SIZE(this->python_array()));
    }

    template <class D>
    inline auto pycontainer<D>::derived_cast() -> derived_type&
    {
        return *static_cast<derived_type*>(this);
    }

    template <class D>
    inline auto pycontainer<D>::derived_cast() const -> const derived_type&
    {
        return *static_cast<const derived_type*>(this);
    }

    namespace detail
    {
        template <class S>
        struct check_dims
        {
            static bool run(std::size_t)
            {
                return true;
            }
        };

        template <class T, std::size_t N>
        struct check_dims<std::array<T, N>>
        {
            static bool run(std::size_t new_dim)
            {
                if(new_dim != N)
                {
                    std::ostringstream err_msg;
                    err_msg << "Invalid conversion to pycontainer, expecting a container of dimension "
                            << N << ", got a container of dimension " << new_dim << ".";
                    throw std::runtime_error(err_msg.str());
                }
                return new_dim == N;
            }
        };
    }

    /**
     * resizes the container.
     * @param shape the new shape
     */
    template <class D>
    template <class S>
    inline void pycontainer<D>::resize(const S& shape)
    {
        if (shape.size() != this->dimension() || !std::equal(std::begin(shape), std::end(shape), std::begin(this->shape())))
        {
            resize(shape, layout_type::row_major);
        }
    }

    /**
     * resizes the container.
     * @param shape the new shape
     * @param l the new layout
     */
    template <class D>
    template <class S>
    inline void pycontainer<D>::resize(const S& shape, layout_type l)
    {
        strides_type strides = xtl::make_sequence<strides_type>(shape.size(), size_type(1));
        compute_strides(shape, l, strides);
        resize(shape, strides);
    }

    /**
     * resizes the container.
     * @param shape the new shape
     * @param strides the new strides
     */
    template <class D>
    template <class S>
    inline void pycontainer<D>::resize(const S& shape, const strides_type& strides)
    {
        detail::check_dims<shape_type>::run(shape.size());
        derived_type tmp(xtl::forward_sequence<shape_type, decltype(shape)>(shape), strides);
        *static_cast<derived_type*>(this) = std::move(tmp);
    }

    template <class D>
    template <class S>
    inline auto& pycontainer<D>::reshape(S&& shape, layout_type layout) &
    {
        if (compute_size(shape) != this->size())
        {
            throw std::runtime_error("Cannot reshape with incorrect number of elements (" + std::to_string(this->size()) + " vs " + std::to_string(compute_size(shape)) + ")");
        }
        detail::check_dims<shape_type>::run(shape.size());
        layout = default_assignable_layout(layout);

        NPY_ORDER npy_layout;
        if (layout == layout_type::row_major)
        {
            npy_layout = NPY_CORDER;
        }
        else if (layout == layout_type::column_major)
        {
            npy_layout = NPY_FORTRANORDER;
        }
        else
        {
            throw std::runtime_error("Cannot reshape with unknown layout_type.");
        }

        using shape_ptr = typename std::decay_t<S>::pointer;
        PyArray_Dims dims = {reinterpret_cast<npy_intp*>(const_cast<shape_ptr>(shape.data())), static_cast<int>(shape.size())};
        auto new_ptr = PyArray_Newshape(this->python_array(), &dims, npy_layout);
        auto old_ptr = this->m_ptr;
        this->m_ptr = reinterpret_cast<PyObject*>(new_ptr);
        Py_XDECREF(old_ptr);
        this->derived_cast().init_from_python();
        return *this;
    }

    /**
     * Return the layout_type of the container
     * @return layout_type of the container
     */
    template <class D>
    inline layout_type pycontainer<D>::layout() const
    {
        if (PyArray_CHKFLAGS(python_array(), NPY_ARRAY_C_CONTIGUOUS))
        {
            return layout_type::row_major;
        }
        else if (PyArray_CHKFLAGS(python_array(), NPY_ARRAY_F_CONTIGUOUS))
        {
            return layout_type::column_major;
        }
        else
        {
            return layout_type::dynamic;
        }
    }

    /**
     * Return whether or not the container uses contiguous buffer
     * @return Boolean for contiguous buffer
     */
    template <class D>
    inline bool pycontainer<D>::is_contiguous() const noexcept
    {
        if (this->strides().size() == 0)
        {
            return true;
        }
        else if (PyArray_CHKFLAGS(python_array(), NPY_ARRAY_C_CONTIGUOUS))
        {
            return 1 == this->strides().back();
        }
        else if (PyArray_CHKFLAGS(python_array(), NPY_ARRAY_F_CONTIGUOUS))
        {
            return 1 == this->strides().front();
        }
        else
        {
            return false;
        }
    }

    inline void import_numpy()
    {
#ifdef FORCE_IMPORT_ARRAY
        if (_import_array() < 0)
        {
            PyErr_Print();
            PyErr_SetString(PyExc_ImportError, "numpy.core.multiarray failed to import");
        }
#endif
    }

}

#endif
