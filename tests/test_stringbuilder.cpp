#include <clue/stringfmt.hpp>
#include <gtest/gtest.h>

using namespace clue;

constexpr size_t short_len = 32;

TEST(StringBuilder, Basics) {

    string_builder sb;

    ASSERT_TRUE(sb.empty());
    ASSERT_EQ(short_len, sb.capacity());
    ASSERT_EQ(0, sb.size());
    ASSERT_EQ("", sb.str());
    ASSERT_EQ(string_view(sb.data(), 0), sb.str_view());

    sb.reset();

    ASSERT_TRUE(sb.empty());
    ASSERT_EQ(short_len, sb.capacity());
    ASSERT_EQ(0, sb.size());
    ASSERT_EQ("", sb.str());
    ASSERT_EQ(string_view(sb.data(), 0), sb.str_view());

    sb.reserve(short_len / 2);

    ASSERT_TRUE(sb.empty());
    ASSERT_EQ(short_len, sb.capacity());
    ASSERT_EQ(0, sb.size());
    ASSERT_EQ("", sb.str());
    ASSERT_EQ(string_view(sb.data(), 0), sb.str_view());

    sb.reserve(short_len + 1);

    ASSERT_TRUE(sb.empty());
    ASSERT_EQ(short_len * 2, sb.capacity());
    ASSERT_EQ(0, sb.size());
    ASSERT_EQ("", sb.str());
    ASSERT_EQ(string_view(sb.data(), 0), sb.str_view());

    sb.reset();

    ASSERT_TRUE(sb.empty());
    ASSERT_EQ(short_len, sb.capacity());
    ASSERT_EQ(0, sb.size());
    ASSERT_EQ("", sb.str());
    ASSERT_EQ(string_view(sb.data(), 0), sb.str_view());

    sb.reserve(short_len * 4 + 1);

    ASSERT_TRUE(sb.empty());
    ASSERT_EQ(short_len * 8, sb.capacity());
    ASSERT_EQ(0, sb.size());
    ASSERT_EQ("", sb.str());
    ASSERT_EQ(string_view(sb.data(), 0), sb.str_view());
}


TEST(StringBuilder, WriteStrings) {

    string_builder sb;

    sb.write('*', 3);

    ASSERT_FALSE(sb.empty());
    ASSERT_EQ(short_len, sb.capacity());
    ASSERT_EQ(3, sb.size());
    ASSERT_EQ("***", sb.str());
    ASSERT_EQ(string_view(sb.data(), 3), sb.str_view());

    sb.reset();
    sb.write("clue", 4);

    ASSERT_FALSE(sb.empty());
    ASSERT_EQ(short_len, sb.capacity());
    ASSERT_EQ(4, sb.size());
    ASSERT_EQ("clue", sb.str());
    ASSERT_EQ(string_view(sb.data(), 4), sb.str_view());

    sb.write('.');

    ASSERT_FALSE(sb.empty());
    ASSERT_EQ(short_len, sb.capacity());
    ASSERT_EQ(5, sb.size());
    ASSERT_EQ("clue.", sb.str());
    ASSERT_EQ(string_view(sb.data(), 5), sb.str_view());

    // length of long_text is 21 * 3 + 2 = 65;
    const char *long_text =
        "0123456789-0123456789;"
        "0123456789-0123456789;"
        "0123456789-0123456789";

    sb.write(std::string(long_text));

    ASSERT_FALSE(sb.empty());
    ASSERT_EQ(70, sb.size());
    ASSERT_EQ(128, sb.capacity());
    ASSERT_EQ(std::string("clue.") + long_text, sb.str());
    ASSERT_EQ(string_view(sb.data(), sb.size()), sb.str_view());

    // length of long_text2 is 21 * 5 + 4 = 109;
    const char *long_text2 =
        "0123456789-0123456789;"
        "0123456789-0123456789;"
        "0123456789-0123456789;"
        "0123456789-0123456789;"
        "0123456789-0123456789";

    sb.write(long_text2);

    ASSERT_EQ(256, sb.capacity());
    ASSERT_EQ(std::string("clue.") + long_text + long_text2, sb.str());
    ASSERT_EQ(string_view(sb.data(), sb.size()), sb.str_view());
}

