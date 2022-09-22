// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <bitsery/adapter/buffer.h>
#include <bitsery/bitsery.h>
#include <bitsery/traits/vector.h>

#include <fstream>

// eigen quaternions
#include "../../themachinethatgoesping/tools/classhelpers/bitsery_helpers/eigen.hpp"

#define TESTTAG "[bitsery]"

using Buffer        = std::vector<uint8_t>;
using OutputAdapter = bitsery::OutputBufferAdapter<Buffer>;
using InputAdapter  = bitsery::InputBufferAdapter<Buffer>;

template<typename custom_bitsery_type>
void test_serialize(custom_bitsery_type& iq)
{
    custom_bitsery_type iq2;

    // create buffer to store data
    Buffer buffer;
    // use quick serialization function,
    // it will use default configuration to setup all the necessary steps
    // and serialize data to container
    auto writtenSize = bitsery::quickSerialization<OutputAdapter>(buffer, iq);

    // interpolators should not be the same before serialization
    REQUIRE(iq != iq2);

    // same as serialization, but returns deserialization state as a pair
    // first = error code, second = is buffer was successfully read from begin to the end.
    auto state = bitsery::quickDeserialization<InputAdapter>({ buffer.begin(), writtenSize }, iq2);
    REQUIRE(state.first == bitsery::ReaderError::NoError);
    REQUIRE(state.second);

    REQUIRE(iq == iq2);
}

// just to test how to serialize vectors of quaternions
struct MyStruct
{
    std::vector<t_quaternion> Q;

    template<typename S>
    void serialize(S& s)
    {
        s.container(Q, SERIALIZER_DEFAULT_MAX_CONTAINER_SIZE);
    }

    bool operator==(const MyStruct& rhs) const
    {
        if (Q.size() != rhs.Q.size())
            return false;
        return std::equal(Q.begin(), Q.end(), rhs.Q.begin());
    }
    bool operator!=(const MyStruct& rhs) const { return !(*this == rhs); }
};

TEST_CASE("Custom bitsery types should serializable", TESTTAG)
{
    auto     q1 = t_quaternion(10, 11, 12, 13);
    auto     q2 = t_quaternion(11, 22, 33, 44);
    MyStruct Q, QQ;
    Q.Q  = { q1, q1, q1 };
    QQ.Q = { q2, q2, q2 };

    REQUIRE(Q != QQ);

    test_serialize(q1);
    test_serialize(Q);
}