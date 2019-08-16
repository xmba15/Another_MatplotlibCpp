/**
 * @file    TestInitialization.cpp
 *
 * @author  btran
 *
 * @date    2019-08-16
 *
 * Copyright (c) organization
 *
 */

#include "gtest/gtest.h"
#include <ctime>

#include <matplotlib_cpp/MatplotlibCpp.hpp>

class TestMatplotlibCpp : public ::testing::Test
{
 protected:
    void SetUp() override
    {
        start_time_ = time(nullptr);
    }

    void TearDown() override
    {
        const time_t end_time = time(nullptr);

        // expect test time less than 5 sec
        EXPECT_LE(end_time - start_time_, 5);
    }

    time_t start_time_;
};
