
namespace CmibParser
{
#define CATCH_WORD "([\\w\\-_]+)"
//double __ is intentional
#define CATCH__WORDS "((?:\\s*[\\w\\-_]+)*)"
#define CATCH_DOT "(.*?)"
#define CATCH_ANYTHING_LAZY "([^]*?)"
#define CATCH_ANYTHING_GREEDY "([^]*)"
#define GROUP(str) "(" str ")"
#define NOCATCH(str) "(?:" str ")"
#define OPTIONAL(str) "(?:" str ")?"
#define SKIP_WHITESPACES "\\s*"
#define LAZY "?"
#define PARANTHESES(str) "\\(" str "\\)"
#define BRACES(str) "\\{" str "\\}"
#define BRACKETS(str) "\\[" str "\\]"
#define CHEVRONS(str) "\\<" str "\\>"
#define COMMENT "(?:--.*\\n\\s*)?"

    constexpr char syntax_type_regexp_str[] =
        SKIP_WHITESPACES CATCH__WORDS;

    constexpr char type_definition_str[] =
        SKIP_WHITESPACES LAZY CATCH_WORD;

    constexpr char sequence_entry_regexp_str[] =
         SKIP_WHITESPACES CATCH_WORD 
         SKIP_WHITESPACES CATCH__WORDS
OPTIONAL(SKIP_WHITESPACES PARANTHESES( CATCH_DOT ));

        //GROUP(
            // "[\\w\\s]*" 
            // OPTIONAL(BRACES("[^]*")) SKIP_WHITESPACES
            // OPTIONAL(PARANTHESES(".?"))
            // );


    constexpr char sequence_regexp_str[] = 
        SKIP_WHITESPACES "SEQUENCE" SKIP_WHITESPACES BRACES(CATCH_ANYTHING_GREEDY);

    constexpr char sequence_of_regexp_str[] = 
        SKIP_WHITESPACES "SEQUENCE OF" SKIP_WHITESPACES CATCH__WORDS;

    constexpr char choice_regexp_str[] = 
        SKIP_WHITESPACES CATCH_WORD;

    constexpr char object_type_regexp_str[] =
        CATCH_WORD SKIP_WHITESPACES "OBJECT-TYPE" SKIP_WHITESPACES
                                    "SYNTAX" CATCH_ANYTHING_LAZY
                                    "ACCESS" CATCH_ANYTHING_LAZY
                                    "STATUS" CATCH_ANYTHING_LAZY
                                    "DESCRIPTION" CATCH_ANYTHING_LAZY
                           OPTIONAL("INDEX" CATCH_ANYTHING_LAZY) "::=" SKIP_WHITESPACES
                                            BRACES(CATCH_DOT);

    constexpr char type_declaration_regexp_str[] =
        CATCH_WORD SKIP_WHITESPACES "::=" SKIP_WHITESPACES
            OPTIONAL(BRACKETS("APPLICATION (\\d*)") SKIP_WHITESPACES) COMMENT
            OPTIONAL("(IMPLICIT|EXPLLICIT)" SKIP_WHITESPACES)
            CATCH_ANYTHING_GREEDY;

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