
#include "catch.hpp"

#include "StringUtils.hpp"

SCENARIO("string widths can be converted to and from 8 and 16 bits", "[strings]") {
    GIVEN("a narrow string initialized with text") {
        std::string narrowStr = "Some string text here.";

        REQUIRE(narrowStr.length() == 22);

        WHEN("the width is converted to wide") {
            auto wideStr = ToWideString(narrowStr);
            
            THEN("the length of the new string is the same as the narrow string") {
                REQUIRE(wideStr.length() == narrowStr.length());
            }

            AND_THEN("the contents of the new string is equivalent to the narrow string") {
                REQUIRE(wideStr.compare(u"Some string text here.") == 0);
            }
        }

    }

    GIVEN("a wide string initialized with text") {
        std::u16string wideStr = u"Some string text here.";

        REQUIRE(wideStr.length() == 22);

        WHEN("the width is converted to narrow") {
            auto narrowStr = FromWideString(wideStr);

            THEN("the length of the new string is the same as the wide string") {
                REQUIRE(narrowStr.length() == wideStr.length());
            }

            AND_THEN("the contents of the new string is equivalent to the wide string") {
                REQUIRE(narrowStr.compare("Some string text here.") == 0);
            }
        }
    }
}
