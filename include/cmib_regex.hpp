

#define CATCH_WORD "([\\w\\-_]+)"
//double __ is intentional
#define CATCH__WORDS "((?:\\s*[\\w\\-_]+)*)"
#define CATCH_DOT_LAZY "(.*?)"
#define CATCH_DOT_GREEDY "(.*)"
#define CATCH_ANYTHING_LAZY "([^]*?)"
#define CATCH_ANYTHING_GREEDY "([^]*)"
#define GROUP(str) "(" str ")"
#define NOCATCH(str) "(?:" str ")"
#define OPTIONAL(str) "(?:" str ")?"
#define SKIP_WHITESPACES "\\s*"
#define LAZY "?"
#define PARANTHESES(str) "\\(" str "\\)"
#define BRACES(str) "\\{" str "\\}"
#define BRACES1(str) "\\{" str " "
#define BRACES2(str) str"\\}"
#define BRACKETS(str) "\\[" str "\\]"
#define CHEVRONS(str) "\\<" str "\\>"
#define COMMENT "(?:--.*\\n\\s*)?"

namespace CmibRegex
{
    constexpr char object_simple_syntax_regexp_str[] =
        SKIP_WHITESPACES CATCH__WORDS SKIP_WHITESPACES;

    constexpr char syntax_type_regexp_str[] =
        SKIP_WHITESPACES CATCH__WORDS
        OPTIONAL(SKIP_WHITESPACES PARANTHESES(CATCH_ANYTHING_GREEDY));

    constexpr char sequence_entry_regexp_str[] =
         SKIP_WHITESPACES CATCH_WORD 
         SKIP_WHITESPACES CATCH__WORDS SKIP_WHITESPACES
OPTIONAL(PARANTHESES( CATCH_DOT_GREEDY ));

        //GROUP(
            // "[\\w\\s]*" 
            // OPTIONAL(BRACES("[^]*")) SKIP_WHITESPACES
            // OPTIONAL(PARANTHESES(".?"))
            // );


    constexpr char sequence_regexp_str[] = 
        SKIP_WHITESPACES "(?:SEQUENCE|CHOICE)" SKIP_WHITESPACES BRACES(CATCH_ANYTHING_GREEDY);

    constexpr char sequence_of_regexp_str[] = 
        SKIP_WHITESPACES "SEQUENCE OF" SKIP_WHITESPACES CATCH__WORDS OPTIONAL(SKIP_WHITESPACES PARANTHESES(CATCH_ANYTHING_GREEDY));

    constexpr char choice_regexp_str[] = 
        SKIP_WHITESPACES CATCH_WORD;

    constexpr char object_type_regexp_str[] =
        CATCH_WORD SKIP_WHITESPACES "OBJECT-TYPE" SKIP_WHITESPACES
                                    "SYNTAX" CATCH_ANYTHING_LAZY
                                    "ACCESS" CATCH_ANYTHING_LAZY
                                    "STATUS" CATCH_ANYTHING_LAZY
                                    "DESCRIPTION" CATCH_ANYTHING_LAZY
                           OPTIONAL("INDEX" CATCH_ANYTHING_LAZY) "::=" SKIP_WHITESPACES
                                             BRACES(CATCH_DOT_LAZY);

    constexpr char type_declaration_regexp_str[] =
        CATCH_WORD SKIP_WHITESPACES "::=" SKIP_WHITESPACES
            OPTIONAL(BRACKETS("APPLICATION (\\d*)") SKIP_WHITESPACES) COMMENT
            OPTIONAL("(IMPLICIT|EXPLLICIT)" SKIP_WHITESPACES)
            CATCH_ANYTHING_GREEDY;

    const char definitions_begin_substr[] =
        "DEFINITIONS ::= BEGIN";

    const char imports_entry_regexp[] =
        "FROM" SKIP_WHITESPACES CATCH_WORD;

    const char split_declarations_regexp[] = 
    // "\\s*\\w"
    // NOCATCH(".*?(MACRO)[^]*?END") "|" 
    // NOCATCH(".*?(EXPORT|IMPORT)[^]?;") "|"
    // //NOCATCH(".*?(OBJECT-IDENTITY)[^]*?:=.*?\n") "|"
    // NOCATCH(".*?(OBJECT-TYPE)[^]*?:=.*?\n")
    // ;
    // // "|"
    // //NOCATCH("[\\s\\w]*?(:=)(.*\n)+?\n") 
    // ;
    R"((?:(EXPORTS|IMPORTS)[^]*?;)|(?:.*?(MACRO)[^]*?END)|(?:.*?(OBJECT-TYPE|OBJECT-IDENTITY|OBJECT IDENTIFIER)[^]*?.*::=.*?\n)|(?:(.*)?:=(.*\n)+?\n))";


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