#pragma once

/* generated doc strings */
#include ".docstrings/variant.doc.hpp"

#include <variant>

namespace themachinethatgoesping::tools::helper {
// source https://gist.github.com/s3rvac/d1f30364ce1f732d75ef0c89a1c8c1ef
template<typename... Ts>
struct make_overload : Ts...
{
    using Ts::operator()...;
};
template<typename... Ts>
make_overload(Ts...) -> make_overload<Ts...>;

template<typename Variant, typename... Alternatives>
decltype(auto) visit_variant(Variant&& variant, Alternatives&&... alternatives)
{
    return std::visit(make_overload{ std::forward<Alternatives>(alternatives)... },
                      std::forward<Variant>(variant));
}

template<typename Variant, typename... Alternatives>
decltype(auto) visit_variant_no_return(Variant&& variant, Alternatives&&... alternatives)
{
    std::visit(make_overload{ std::forward<Alternatives>(alternatives)... },
               std::forward<Variant>(variant));
}
} // namespace themachinethatgoesping::tools::helper