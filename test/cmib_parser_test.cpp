#include "gtest/gtest.h"
#include "cmib_parser.hpp"
#include "cmib_enum.hpp"

#define GTEST_COUT std::cerr << "[   INFO   ] "



struct syntax_t_tc
{
    syntax_t syntax;
    std::string expression;
};

struct SyntaxTest : testing::Test ,testing::WithParamInterface<syntax_t_tc>
{

};

TEST_P(SyntaxTest, ParseTypeDeclaration)
{
    auto tc = GetParam();
    auto str = tc.expression;
    auto expected = tc.syntax;
    GTEST_COUT << "(syntax_t)" << str << " == " << (syntax_t)str << "\n";

    ASSERT_EQ(expected, (syntax_t)str);
}

INSTANTIATE_TEST_CASE_P(Default, SyntaxTest,
    testing::Values(
    syntax_t_tc{syntax_t{_SYNTAX_e::INTEGER}, "integer"},
    syntax_t_tc{syntax_t{_SYNTAX_e::INTEGER}, "INTEGER"},
    syntax_t_tc{syntax_t{_SYNTAX_e::INTEGER}, "Integer"},
    syntax_t_tc{syntax_t{_SYNTAX_e::OCTET_STRING}, "octet-string"}    
    ));

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
