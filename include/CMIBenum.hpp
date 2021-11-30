enum struct SYNTAX
{
    INTEGER,
    OCTET_STRING,
    OBJECT_IDENTIFIER,
    NULL_T,
    IMPORT_S
}; // default type is int

enum struct ACCESS
{
    read_only,
    read_write,
    not_accessible
}; // default type is int
enum struct STATUS
{
    mandatory,
    deprecated
}; // default type is int
