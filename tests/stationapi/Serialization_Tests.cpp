
#include "catch.hpp"

#include "Serialization.hpp"

SCENARIO("integer serialization", "[serialization]") {
    GIVEN("an initialized 32bit signed integer and a binary stream") {
        int32_t signedInt = -8;
        std::stringstream bs(std::ios_base::out | std::ios_base::in | std::ios_base::binary);

        WHEN("the stream has the integer written to it") {
            write(bs, signedInt);

            THEN("the serialized output size is increased by 4") {
                REQUIRE(bs.str().length() == 4);
            }
            
            AND_THEN("the serialized output is little-endian") {
                auto str = bs.str();
                REQUIRE(str[0] == (char)0xF8);
                REQUIRE(str[1] == (char)0xFF);
                REQUIRE(str[2] == (char)0xFF);
                REQUIRE(str[3] == (char)0xFF);
            }
        }
    }

    GIVEN("a binary stream containing a serialized 32bit signed integer") {
        int32_t signedInt = -8;
        std::stringstream bs(std::ios_base::out | std::ios_base::in | std::ios_base::binary);
        write(bs, signedInt);

        WHEN("the stream has the integer read from it") {
            auto testInt = read<int32_t>(bs);

            THEN("the value read is the value expected") {
                REQUIRE(testInt == signedInt);
            }
        }

        AND_WHEN("the stream is read into an existing integer variable") {
            int32_t testInt = 0;
            read(bs, testInt);

            THEN("the value read is the value expected") {
                REQUIRE(testInt == signedInt);
            }
        }
    }
}

SCENARIO("string serialization", "[serialization]") {
    GIVEN("an initialized ascii string and a binary stream") {
        std::string asciiStr = "Some string value";
        std::stringstream bs(std::ios_base::out | std::ios_base::in | std::ios_base::binary);

        WHEN("the stream has an ascii string written to it") {
            write(bs, asciiStr);

            THEN("the serialized output size is increased by the length of the string, plus a uint16_t string length") {
                REQUIRE(bs.str().length() == asciiStr.length() + sizeof(uint16_t));
            }

            AND_THEN("the output contains a uint16_t string length, followed by the ascii string") {
                auto length = peekAt<uint16_t>(bs, 0);
                REQUIRE(length == asciiStr.length());

                auto str = bs.str();

                REQUIRE(str[2] == asciiStr[0]);
                REQUIRE(str[18] == asciiStr[16]);
            }
        }
    }

    GIVEN("a binary string containing a serialized ascii string") {
        std::string asciiStr = "Some string value";
        std::stringstream bs(std::ios_base::out | std::ios_base::in | std::ios_base::binary);
        write(bs, asciiStr);

        WHEN("the stream has the string read from it") {
            auto testStr = read<std::string>(bs);

            THEN("the value re ad is the value expected") {
                REQUIRE(testStr.compare(asciiStr) == 0);
            }
        }

        AND_WHEN("the stream is read into an existing string variable") {
            std::string testStr;
            read(bs, testStr);

            THEN("the value read is the value expected") {
                REQUIRE(testStr.compare(asciiStr) == 0);
            }
        }
    }
}

