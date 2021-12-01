
namespace CmibParser
{
#define CATCH_WORD "([\\w\\-_]*)"
#define CATCH_DOT "(.*?)"
#define CATCH_ANYTHING "([^]*?)"
#define GROUP(str) "(" str ")"
#define NOCATCH(str) "(?:" str ")"
#define OPTIONAL(str) "(?:" str ")?"
#define SKIP_WHITESPACES "\\s*?"
#define PARANTHESES(str) "\\(" str "\\)"
#define BRACES(str) "\\{" str "\\}"
#define BRACKETS(str) "\\[" str "\\]"
#define CHEVRONS(str) "\\<" str "\\>"
#define COMMENT "(?:--.*\\n\\s*)?"

    constexpr char syntax_type_regexp_str[] = 
        "\\s*(\\w*)";

    constexpr char object_type_regexp_str[] =
        CATCH_WORD SKIP_WHITESPACES "OBJECT-TYPE" SKIP_WHITESPACES
                                    "SYNTAX" CATCH_ANYTHING
                                    "ACCESS" CATCH_ANYTHING
                                    "STATUS" CATCH_ANYTHING
                                    "DESCRIPTION" CATCH_ANYTHING
                           OPTIONAL("INDEX" CATCH_ANYTHING) "::=" SKIP_WHITESPACES
                                            BRACES(CATCH_DOT);

    constexpr char type_declaration_regexp_str[] =
        CATCH_WORD SKIP_WHITESPACES "::=" SKIP_WHITESPACES
            OPTIONAL(BRACKETS("APPLICATION (\\d*)")) SKIP_WHITESPACES COMMENT
            OPTIONAL("(IMPLICIT|EXPLLICIT)") SKIP_WHITESPACES
            GROUP(NOCATCH("[\\w\\s]*") NOCATCH(BRACES("[^]*")))
            OPTIONAL(PARANTHESES(CATCH_DOT));

#undef CATCH_WORD
#undef CATCH_DOT
#undef CATCH_ANYTHING
#undef GROUP
#undef NOCATCH
#undef OPTIONAL
#undef SKIP_WHITESPACES
#undef PARANTHESES
#undef BRACES
#undef BRACKETS
#undef CHEVRONS
#undef COMMENT
};