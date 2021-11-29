
namespace CmibParser
{
    #define CATCH_WORD "(\\w*)"
    #define CATCH_DOT "(.*?)" 
    #define CATCH_ANYTHING "([^]*?)"
    #define OPTIONAL(str) "(?:" str ")?"
    #define SKIP_WHITESPACES "\\s*?"
    #define BRACKETS(str) "\\{" str "\\}"

    constexpr char object_type_regexp_str[] = 
         CATCH_WORD SKIP_WHITESPACES "OBJECT-TYPE" SKIP_WHITESPACES
         "SYNTAX" CATCH_ANYTHING
         "ACCESS" CATCH_ANYTHING
         "STATUS" CATCH_ANYTHING
         "DESCRIPTION" CATCH_ANYTHING
OPTIONAL("INDEX" CATCH_ANYTHING)
         "::=" SKIP_WHITESPACES
         BRACKETS(CATCH_DOT);;

    //constexpr char type_declaration_regexp_str[] = 
    //   CATCH_WORD SKIP_WHITESPACES "::=" SKIP_WHITESPACES
    //    R"(?:\[APPLICATION (\d*)\])?\s*(?:--.*\n)?\s*(IMPLICIT|EXPLICIT)?\s*((?:[\w\s]*)(?:\{[^]*\})?)(?:\((.*)\))?)";

    constexpr char type_declaration_regexp_str[] = 
        R"((\w*)\s*::=\s*(?:\[APPLICATION (\d*)\])?\s*(?:--.*\n)?\s*(IMPLICIT|EXPLICIT)?\s*((?:[\w\s]*)(?:\{[^]*\})?)(?:\((.*)\))?)";
        
    #undef CATCH_ANYTHING
    #undef CATCH_WORD
    #undef CATCH_DOT
    #undef CATCH_ANYTHING
    #undef OPTIONAL
    #undef SKIP_WHITESPACES
    #undef BRACKETS
};