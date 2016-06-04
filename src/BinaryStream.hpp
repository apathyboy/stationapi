
#pragma once

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

using BinarySourceStream = boost::iostreams::stream<boost::iostreams::array_source>;
using BinarySinkStream = boost::iostreams::stream<boost::iostreams::array_sink>;
