// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean
// Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief Interface class for vector interpolators
 *
 * @authors Peter Urban
 *
 */

#pragma once

/* generated doc strings */
#include ".docstrings/i_interpolator.doc.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <iterator>
#include <omp.h>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>
#include <xtensor/containers/xtensor.hpp>

#include "../classhelper/objectprinter.hpp"
#include "../classhelper/option.hpp"
#include "../helper/downsampling.hpp"
#include "../helper/xtensor.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {

/**
 * @brief extrapolation mode type.
 *
 */
enum class t_extr_mode : uint8_t
{
    extrapolate = 0, ///< interpolate using the closest value pair in the internal x vector
    fail    = 1, ///< throw out_of_range exception if x value exceeds boundaries of internal vector
    nearest = 2, ///< return nearest value in the vector.
    nan     = 3  ///< return NaN if x value exceeds boundaries of internal vector (only for floating
                 ///< point types)
};

using o_extr_mode = classhelper::Option<t_extr_mode>;

/**
 * @brief Duplicate-handling mode for insert().
 *
 * insert() always silently drops EXACT duplicates (same x AND exactly the same
 * y). This mode only controls what happens on a genuine CONFLICT: the same x
 * value present with a DIFFERENT y value.
 */
enum class t_dup_mode : uint8_t
{
    fail       = 0, ///< throw a domain_error on a conflicting duplicate x value (default)
    keep_first = 1, ///< on conflict keep the first occurrence (the existing / earlier value)
    keep_last  = 2  ///< on conflict keep the last occurrence (the newly inserted / later value)
};

using o_dup_mode = classhelper::Option<t_dup_mode>;

/**
 * @brief Interface class for interpolator classes
 * Create an interpolator object by providing vectors for x and y (same size). X
 * must be sorted and no duplicates are allowed. then call interpolator(new
 * x value) to get a corresponding y value at this x position.
 *
 * @tparam XType: type of the x values (must be floating point)
 * @tparam YType: type of the y values (typically double or float, but will be a vector
 * for the slerp interpolator class)
 */
template<std::floating_point XType, typename YType>
class I_Interpolator
{
  public:
    using t_XType = XType;
    using t_YType = YType;

  protected:
    o_extr_mode _extr_mode; ///< extrapolation mode

  public:
    /**
     * @brief Construct a new Interpolator object from two vectors
     * usage: interpolated_y_value = interpolator.interpolate(x_value)
     *
     * @param extrapolation_mode extrapolation mode (nearest or fail)
     */
    I_Interpolator(o_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
        : _extr_mode(extrapolation_mode)
    {
    }
    virtual ~I_Interpolator() = default;

    /**
     * @brief Get the interpolator name (for debugging)
     *
     * @return std::string_view
     */
    virtual std::string class_name() const { return "I_Interpolator"; }

    /**
     * @brief change the input data to these X and Y vectors
     *
     * @param X: x vector (must be same size, must be sorted in ascending order)
     * @param Y: y vector (must be same size)
     */
    virtual void set_data_XY(std::vector<XType> X, std::vector<YType> Y) = 0;

    // -----------------------
    // getter functions
    // -----------------------
    /**
     * @brief return the x component of the internal data vector
     *
     * @return std::vector<XType>
     */
    virtual const std::vector<XType>& get_data_X() const = 0;

    /**
     * @brief return the y component of the internal data vector
     *
     * @return std::vector<YType>
     */
    virtual const std::vector<YType>& get_data_Y() const = 0;

    /**
     * @brief Get downsampled x values from the interpolator data.
     *
     * This function returns x values at regular intervals, respecting gaps in the data.
     * Useful for reducing the number of interpolation points when dealing with large datasets.
     *
     * @param downsample_interval The interval between consecutive sampled x values
     * @param max_gap Maximum allowed gap between consecutive x values. If the gap between
     *                consecutive x values exceeds this, a new sampling segment is started.
     * @return xt::xtensor<XType, 1> A 1D tensor containing the downsampled x values
     *
     * @note The returned values are actual x values from the data, not interpolated positions.
     *       Use these values with the interpolator to get corresponding y values.
     */
    xt::xtensor<XType, 1> get_sampled_X(
        double downsample_interval,
        double max_gap = std::numeric_limits<double>::quiet_NaN()) const
    {
        return helper::get_value_downsampling(get_data_X(), downsample_interval, max_gap);
    }

    // -----------------------
    // getter setter functions
    // -----------------------
    /**
     * @brief Set the extrapolation mode
     *
     * @param extrapolation_mode :py:class:`t_extr_mode
     * <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>` object (enumerator) that
     * describes the extrapolation mode
     */
    void set_extrapolation_mode(const o_extr_mode extrapolation_mode)
    {
        _extr_mode = extrapolation_mode;
    }

    /**
     * @brief Get the currently set extrapolation mode
     *
     * @return :o_extr_mode
     */
    o_extr_mode get_extrapolation_mode() const { return _extr_mode; }

    //-------------------------
    // interpolation functions
    //-------------------------

    /**
     * @brief get the interpolated y value for given x target
     *
     * @param target_x find the corresponding y value for this x value
     * @return corresponding y value
     */
    virtual YType operator()(XType target_x) const = 0;

    /**
     * @brief get interpolated y values for given x targets (vectorized call)
     *
     * @param targets_x vector of x values. For each of these values find the corresponding y value
     * @param mp_cores Number of OpenMP threads to use for parallelization. Default is 1 (no
     *                 parallelism). Set to higher values to enable parallel interpolation.
     * @return std::vector<YType> corresponding y values
     */
    std::vector<YType> operator()(const std::vector<XType>& targetsX, int mp_cores = 1) const
    {
        std::vector<YType> y_values(targetsX.size());
        const auto         n = static_cast<long>(targetsX.size());

#pragma omp parallel for num_threads(mp_cores)
        for (long i = 0; i < n; ++i)
        {
            y_values[i] = operator()(targetsX[i]);
        }

        return y_values;
    }

    /**
     * @brief get interpolated y values for given x targets (xtensor vectorized call)
     *
     * This overload accepts xtensor containers and returns an xtensor result.
     * The return type matches the value type of the interpolator (YType).
     *
     * @tparam XTensor An xtensor-compatible 1D container type
     * @param targets_x xtensor of x values. For each of these values find the corresponding y value
     * @param mp_cores Number of OpenMP threads to use for parallelization. Default is 1 (no
     *                 parallelism). Set to higher values to enable parallel interpolation.
     * @return xt::xtensor<YType, 1> corresponding y values as a 1D xtensor
     *
     * @note This function requires YType to be a scalar type (not a compound type like Quaternion).
     *       For SlerpInterpolator, use the vector overload or the ypr() method instead.
     */
    template<tools::helper::c_xtensor_1d t_xtensor_1d>
    xt::xtensor<YType, 1> operator()(const t_xtensor_1d& targetsX, int mp_cores = 1) const
    {
        const auto            n        = static_cast<long>(targetsX.size());
        xt::xtensor<YType, 1> y_values = xt::empty<YType>({ static_cast<size_t>(n) });

#pragma omp parallel for num_threads(mp_cores)
        for (long i = 0; i < n; ++i)
        {
            y_values(i) = operator()(static_cast<XType>(targetsX(i)));
        }

        return y_values;
    }

    /**
     * @brief append x and y value lists to the interpolator data (vectorized call)
     * Exception: raises domain error, strong exception guarantee
     *
     * @param X list of x values. Must be sorted in ascending order. All x values must be larger
     * than the largest x value in the interpolator data.
     * @param Y list of corresponding Y values. Must be same size as X
     */
    virtual void extend(const std::vector<XType>& X, const std::vector<YType>& Y) = 0;

    /**
     * @brief append an x- and the corresponding y value to the interpolator data.
     * Exception: raises domain error, strong exception guarantee
     *
     * @param x value, must be > than all existing x values
     * @param y corresponding y value
     */
    virtual void append(XType x, YType y) = 0;

    /**
     * @brief Insert x and y value lists into the interpolator data (vectorized call).
     *
     * The new values are merged into the existing (already sorted) data. Only the
     * NEW values are sorted and then merged with the existing run, which is much
     * faster than re-sorting everything.
     *
     * EXACT duplicates (same x AND exactly the same y) are always dropped
     * silently. A CONFLICT (same x but a DIFFERENT y) is resolved according to
     * @p duplicate_mode.
     *
     * Exception: raises domain_error, strong exception guarantee.
     *
     * @param X list of x values. Does not have to be sorted.
     * @param Y list of corresponding Y values. Must be the same size as X.
     * @param is_sorted set to true if X is already sorted in ascending order (skips
     * sorting the new values). (default: false)
     * @param duplicate_mode how to resolve a conflict where the same x value is
     * present with a different y value: fail (throw, the default), keep_first or
     * keep_last. Exact (x, y) duplicates are always removed regardless of this.
     */
    virtual void insert(const std::vector<XType>& X,
                        const std::vector<YType>& Y,
                        bool                      is_sorted      = false,
                        o_dup_mode                duplicate_mode = t_dup_mode::fail)
    {
        if (X.size() != Y.size())
            throw(std::domain_error("ERROR[Interpolator::insert]: list sizes do not match"));

        if (X.empty())
            return;

        const std::vector<XType>& old_X = get_data_X();
        const std::vector<YType>& old_Y = get_data_Y();

        // Fast path: a sorted, strictly-increasing block that lies entirely after
        // the existing data cannot collide with anything -> cheap append/extend
        // (keeps the incremental spline update for the akima interpolator).
        if (is_sorted && _is_strictly_increasing(X) && (old_X.empty() || X.front() > old_X.back()))
        {
            if (old_X.empty())
                set_data_XY(X, Y);
            else
                extend(X, Y);
            return;
        }

        // General path: merge the existing (sorted) data with the new data, drop
        // exact (x, y) duplicates and resolve x-conflicts per duplicate_mode.
        std::vector<XType> X_new;
        std::vector<YType> Y_new;
        _merge_insert(old_X, old_Y, X, Y, is_sorted, duplicate_mode.value, X_new, Y_new);
        set_data_XY(std::move(X_new), std::move(Y_new));
    }

    /**
     * @brief return a printer object
     *
     * @param float_precision number of digits for floating point numbers
     * @return classhelper::ObjectPrinter
     */
    virtual classhelper::ObjectPrinter __printer__(unsigned int float_precision,
                                                   bool         superscript_exponents) const = 0;

    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__

  protected:
    /**
     * @brief check if input data is valid (e.g. sorted, no duplicated x values)
     *
     */
    static void _check_XY(const std::vector<XType>& X, const std::vector<YType>& Y)
    {
        // if (X.size() < 2)
        //     throw(std::domain_error("ERROR[Interpolation::_check_XY]: list size is < 2!"));
        if (X.size() != Y.size())
            throw(std::domain_error(
                "ERROR[Interpolation::_check_XY]: list X and Y list sizes do not match!"));

        for (size_t i = 0; i < X.size(); ++i)
        {
            if (i + 1 < X.size())
            {
                if (X[i] == X[i + 1])
                    throw(std::domain_error(
                        "ERROR[Interpolation::_check_XY]: X list contains duplicate x values!"));

                if (X[i] > X[i + 1])
                    throw(std::domain_error("ERROR[Interpolation::_check_XY]: X list is not "
                                            "sorted in ascending order!"));
            }

            if (!std::isfinite(X[i]))
                throw(std::domain_error(
                    "ERROR[Interpolation::_check_XY]: X List contains NAN or INFINITE values!"));

            if constexpr (std::is_floating_point<YType>())
                if (!std::isfinite(Y[i]))
                    throw(std::domain_error("ERROR[Interpolation::_check_XY]: Y List contains NAN "
                                            "or INFINITE values!"));
        }
    }

    /**
     * @brief Return true if X is strictly increasing (no equal or decreasing neighbours).
     */
    static bool _is_strictly_increasing(const std::vector<XType>& X)
    {
        return std::adjacent_find(
                   X.begin(), X.end(), [](const XType& a, const XType& b) { return a >= b; }) ==
               X.end();
    }

    /**
     * @brief Equality test for two y values.
     *
     * Handles the different y types used by the interpolators: a plain
     * operator== (arithmetic types), Eigen::Quaternion (compare coefficients,
     * slerp) and nanobind::object (Python equality, nearest-object interpolator).
     * Types for which no equality can be determined are never treated as equal,
     * so same-x values are handled as a conflict rather than silently merged.
     */
    static bool _y_values_equal(const YType& a, const YType& b)
    {
        if constexpr (requires(const YType& x, const YType& y) {
                          { x == y } -> std::convertible_to<bool>;
                      })
            return static_cast<bool>(a == b);
        else if constexpr (requires(const YType& x) { x.coeffs(); })
            return a.coeffs() == b.coeffs();
        else if constexpr (requires(const YType& x, const YType& y) {
                               { x.equal(y) } -> std::convertible_to<bool>;
                           })
            return a.equal(b);
        else
            return false;
    }

    /**
     * @brief Validate that X (and floating-point Y) contain only finite values.
     *
     * Throws domain_error on NaN / infinite values so such inputs are never sorted
     * (keeps a strong exception guarantee: nothing is modified before this check).
     */
    static void _validate_finite(const std::vector<XType>& X, const std::vector<YType>& Y)
    {
        for (size_t i = 0; i < X.size(); ++i)
        {
            if (!std::isfinite(X[i]))
                throw(std::domain_error(
                    "ERROR[Interpolator]: X contains NAN or INFINITE values!"));
            if constexpr (std::is_floating_point_v<YType>)
                if (!std::isfinite(Y[i]))
                    throw(std::domain_error(
                        "ERROR[Interpolator]: Y contains NAN or INFINITE values!"));
        }
    }

    /**
     * @brief Collapse groups of equal x in an already-sorted pair vector.
     *
     * Exact (x, y) duplicates are dropped; a conflict (same x, different y) is
     * resolved via @p duplicate_mode (throw in fail mode, else keep the first /
     * last occurrence). The output (out_X / out_Y) is sorted with unique x values.
     *
     * @param pairs input pairs, already sorted ascending by x
     * @param duplicate_mode conflict resolution for same-x / different-y
     * @param out_X output x values (sorted, unique)
     * @param out_Y output y values (same size as out_X)
     */
    static void _collapse_sorted_pairs(const std::vector<std::pair<XType, YType>>& pairs,
                                       t_dup_mode          duplicate_mode,
                                       std::vector<XType>& out_X,
                                       std::vector<YType>& out_Y)
    {
        out_X.clear();
        out_Y.clear();
        out_X.reserve(pairs.size());
        out_Y.reserve(pairs.size());
        for (size_t i = 0; i < pairs.size();)
        {
            size_t j = i + 1;
            while (j < pairs.size() && pairs[j].first == pairs[i].first)
                ++j;

            size_t keep = i; // default: keep the first occurrence
            if (j - i > 1)
            {
                // A group is a pure (exact) duplicate if all its y values are equal.
                bool all_equal = true;
                for (size_t k = i + 1; k < j; ++k)
                    if (!_y_values_equal(pairs[k].second, pairs[i].second))
                    {
                        all_equal = false;
                        break;
                    }

                if (!all_equal)
                {
                    switch (duplicate_mode)
                    {
                        case t_dup_mode::fail:
                            throw(std::domain_error(
                                "ERROR[Interpolator]: duplicate x value with a differing y value "
                                "(conflict)! Use duplicate_mode keep_first or keep_last to "
                                "resolve."));
                        case t_dup_mode::keep_first:
                            keep = i;
                            break;
                        case t_dup_mode::keep_last:
                            keep = j - 1;
                            break;
                    }
                }
            }

            out_X.push_back(pairs[keep].first);
            out_Y.push_back(pairs[keep].second);
            i = j;
        }
    }

    /**
     * @brief Merge the already-sorted existing data with the new data.
     *
     * Only the new values are sorted; they are then merged with the existing run
     * (O(n + m log m)). Exact (x, y) duplicates are dropped; conflicts (same x,
     * different y) are resolved via @p duplicate_mode (or throw in fail mode).
     * The result (out_X / out_Y) is sorted by x with unique x values.
     *
     * @param old_X existing x values (sorted ascending, unique)
     * @param old_Y existing y values (same size as old_X)
     * @param X new x values to merge in
     * @param Y new y values (same size as X)
     * @param is_sorted set to true if X is already sorted ascending (skips sorting)
     * @param duplicate_mode conflict resolution for same-x / different-y
     * @param out_X output x values (sorted, unique)
     * @param out_Y output y values (same size as out_X)
     */
    static void _merge_insert(const std::vector<XType>& old_X,
                              const std::vector<YType>& old_Y,
                              const std::vector<XType>& X,
                              const std::vector<YType>& Y,
                              bool                      is_sorted,
                              t_dup_mode                duplicate_mode,
                              std::vector<XType>&       out_X,
                              std::vector<YType>&       out_Y)
    {
        // Validate the new values up-front (finite) so we never sort NaNs and keep
        // the strong exception guarantee (nothing is changed on throw).
        _validate_finite(X, Y);

        using t_pair   = std::pair<XType, YType>;
        auto less_by_x = [](const t_pair& a, const t_pair& b) { return a.first < b.first; };

        // New values as pairs, sorted by x (stable: keep input order for equal x).
        std::vector<t_pair> new_pairs;
        new_pairs.reserve(X.size());
        for (size_t i = 0; i < X.size(); ++i)
            new_pairs.emplace_back(X[i], Y[i]);
        if (!is_sorted)
            std::stable_sort(new_pairs.begin(), new_pairs.end(), less_by_x);

        // Existing values as pairs (already sorted with unique x).
        std::vector<t_pair> old_pairs;
        old_pairs.reserve(old_X.size());
        for (size_t i = 0; i < old_X.size(); ++i)
            old_pairs.emplace_back(old_X[i], old_Y[i]);

        // Stable merge: for equal x the existing value comes before the new one.
        std::vector<t_pair> merged;
        merged.reserve(old_pairs.size() + new_pairs.size());
        std::merge(old_pairs.begin(),
                   old_pairs.end(),
                   new_pairs.begin(),
                   new_pairs.end(),
                   std::back_inserter(merged),
                   less_by_x);

        // Drop exact (x, y) duplicates and resolve same-x conflicts.
        _collapse_sorted_pairs(merged, duplicate_mode, out_X, out_Y);
    }

    /**
     * @brief Sort a single (possibly unsorted) X/Y vector and remove duplicates.
     *
     * Used by the deferred-merge finalizer (sort_and_finalize): sorts the
     * accumulated data once (O(n log n)), drops exact (x, y) duplicates and
     * resolves same-x / different-y conflicts via @p duplicate_mode. A stable
     * sort is used so keep_first / keep_last follow the original append order.
     *
     * @param X accumulated x values (any order)
     * @param Y accumulated y values (same size as X)
     * @param duplicate_mode conflict resolution for same-x / different-y
     * @param out_X output x values (sorted, unique)
     * @param out_Y output y values (same size as out_X)
     */
    static void _sort_and_dedup(const std::vector<XType>& X,
                                const std::vector<YType>& Y,
                                t_dup_mode                duplicate_mode,
                                std::vector<XType>&       out_X,
                                std::vector<YType>&       out_Y)
    {
        _validate_finite(X, Y);

        using t_pair   = std::pair<XType, YType>;
        auto less_by_x = [](const t_pair& a, const t_pair& b) { return a.first < b.first; };

        std::vector<t_pair> pairs;
        pairs.reserve(X.size());
        for (size_t i = 0; i < X.size(); ++i)
            pairs.emplace_back(X[i], Y[i]);

        // Stable sort: keep_first / keep_last then follow the original append order.
        std::stable_sort(pairs.begin(), pairs.end(), less_by_x);

        _collapse_sorted_pairs(pairs, duplicate_mode, out_X, out_Y);
    }
};

} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping

// Explicit template instantiation declaration
// mkdoc emits a bare, un-namespaced `mkd_doc_Option` stub for the Option template
// instantiations below; suppress it so it does not clash with the identical stub
// generated for other headers (e.g. pingprocessing's i_pingcommon).
// IGNORE_DOC:mkd_doc_Option
extern template class themachinethatgoesping::tools::classhelper::Option<
    themachinethatgoesping::tools::vectorinterpolators::t_extr_mode>;
extern template class themachinethatgoesping::tools::classhelper::Option<
    themachinethatgoesping::tools::vectorinterpolators::t_dup_mode>;