/**
 * @file    AnyBase.hpp
 *
 * @date    2019-08-03
 *
 * framework
 *
 * Copyright (c) organization
 *
 */

#ifndef ANYBASE_HPP_
#define ANYBASE_HPP_

#include <memory>
#include <string>

namespace pe
{
struct AnyBase {
 public:
    virtual ~AnyBase()
    {
    }
};

template <typename DATA_TYPE> struct Any : public AnyBase {
 public:
    explicit Any(const DATA_TYPE& data) : data(data)
    {
    }

    Any()
    {
    }

    DATA_TYPE data;
};

}  // namespace pe
#endif /* ANYBASE_HPP_ */
