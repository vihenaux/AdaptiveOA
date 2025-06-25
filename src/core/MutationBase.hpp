#pragma once

#include <string>
#include <concepts>

namespace AdaptiveOA
{

    template<typename Mutation>
    concept MutationLike = requires(Mutation m)
    {
        { m.to_string() } -> std::convertible_to<std::string>;
    };

} // namespace AdaptiveOA
