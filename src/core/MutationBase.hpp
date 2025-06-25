#pragma once

#include <string>
#include <concepts>

template<typename Mutation>
concept MutationLike = requires(Mutation m) {
    { m.to_string() } -> std::convertible_to<std::string>;
};
