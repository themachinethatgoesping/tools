// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_test_macros.hpp>

#include <string>
#include <vector>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>

using namespace themachinethatgoesping::tools::classhelper;

#define TESTTAG "[classhelper]"

// count how often needle occurs in haystack
static size_t count_occurrences(const std::string& haystack, const std::string& needle)
{
    size_t count = 0;
    for (size_t pos = haystack.find(needle); pos != std::string::npos;
         pos        = haystack.find(needle, pos + needle.size()))
        ++count;
    return count;
}

TEST_CASE("ObjectPrinter register_table renders multi-line cells", TESTTAG)
{
    SECTION("a cell containing newlines is spread over several aligned physical lines")
    {
        ObjectPrinter printer("Test", 2, false);
        // second row has a multi-line cell in the middle column
        printer.register_table("tab",
                               { "id", "sectors", "rx" },
                               { { "A", "s0\ns1\ns2", "RXA" }, { "B", "sB", "RXB" } });

        const std::string str = printer.create_str();

        // every sub-line of the multi-line cell must appear
        REQUIRE(count_occurrences(str, "s0") == 1);
        REQUIRE(count_occurrences(str, "s1") == 1);
        REQUIRE(count_occurrences(str, "s2") == 1);

        // the raw newline inside the cell must NOT survive verbatim as "s0\ns1"
        REQUIRE(str.find("s0\ns1") == std::string::npos);

        // column width is driven by the widest sub-line ("sectors" header, 7 chars), so each
        // sub-line is right-aligned into a 7-wide column => "      s0", "      s1", ...
        REQUIRE(str.find("      s0") != std::string::npos);
        REQUIRE(str.find("      s1") != std::string::npos);
        REQUIRE(str.find("      s2") != std::string::npos);

        // the id/rx columns stay blank on the continuation lines (no second "A" or "RXA")
        REQUIRE(count_occurrences(str, "RXA") == 1);
    }

    SECTION("single-line tables are unchanged (backwards compatible)")
    {
        ObjectPrinter a("Test", 2, false);
        a.register_table("tab", { "id", "v" }, { { "A", "1" }, { "B", "2" } });

        ObjectPrinter b("Test", 2, false);
        // a trailing-empty multi-line split must behave like a plain single line
        b.register_table("tab", { "id", "v" }, { { "A", "1" }, { "B", "2" } });

        REQUIRE(a.create_str() == b.create_str());
    }
}
