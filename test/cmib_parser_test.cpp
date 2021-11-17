#include "gtest/gtest.h"
#include "cmib_parser.hpp"

#define GTEST_COUT std::cerr << "[   INFO   ] "



struct parse_type_tc
{
    union
    {
        type_declaration expected_type_struct;
    };

    std::string expression;
};

struct CmibTest : testing::Test ,testing::WithParamInterface<parse_type_tc>
{

};

TEST_P(CmibTest, ParseTypeDeclaration)
{
    GTEST_COUT << "Hello world\n";
    auto tc = GetParam();
    auto str = tc.expression;
    GTEST_COUT << str <<"\n";
    auto expected = tc.expected_type_struct;
    //CmibParser::parse(CmibParser::parse_type_job, )
}

INSTANTIATE_TEST_CASE_P(Default, CmibTest,
    testing::Values(
    parse_type_tc{type_declaration{0}, "AAAAAAAA"},
    parse_type_tc{type_declaration{0}, "DUPAAAAA"},
    parse_type_tc{type_declaration{0}, "AAAAAAAA"}   
    ));

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}