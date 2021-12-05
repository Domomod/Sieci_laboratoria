#include<type_traits>
#include<string>
#include<ostream>

#pragma once

enum _SYNTAX_e : uint8_t
{
    OCTET_STRING,
    INTEGER,
    OBJECT_IDENTIFIER,
    //NULL_T,
    IMPORT_S,
    SEQUENCE,
    SEQUENCE_OF,
    _SYNTAX_e_MAX_ENUM
};

enum _ACCESS_e
{
    READ_ONLY,
    READ_WRITE,
    NOT_ACCESSIBLE,
    _ACCESS_e_MAX_ENUM
}; // default type is int

enum _STATUS_e
{
    MANDATORY,
    DEPRECATED,
    _STATUS_e_MAX_ENUM
}; // default type is int


template<class enum_type>
class class_enum
{
    static_assert(std::is_enum<enum_type>::value, "Must be an enum");
public:
    // Move semantics
    class_enum& operator=(class_enum&& value) = default;
    class_enum( class_enum && value )      = default;
    
    // Default constructors and assignment
    class_enum() = default;
    class_enum& operator=(const class_enum& value) = default;
    class_enum( const class_enum & value )      = default;
    class_enum( const enum_type & value ) : value(value) {};

    // Explicit constructors
    explicit class_enum( const std::string & value ) = delete;

    bool operator==(const class_enum & other) const
    {
        return this->value == other.value;
    }

    void print(std::ostream& stream) const { stream << this-> value;};

    enum_type get() {return value;}
private:
    enum_type value;
};

template<class enum_type>
std::ostream& operator<<(std::ostream& stream, const class_enum<enum_type>& value)
{
    value.print(stream);
    return stream;
}

//╔═════════════════════════╗
//║ Forward specializations ║
//╚═════════════════════════╝
template<> class_enum<_SYNTAX_e>::class_enum(const std::string & value);
template<> class_enum<_ACCESS_e>::class_enum(const std::string & value);
template<> class_enum<_STATUS_e>::class_enum(const std::string & value);

template class class_enum<_SYNTAX_e>;
template class class_enum<_ACCESS_e>;
template class class_enum<_STATUS_e>;

//╔═════════╗
//║ Aliases ║
//╚═════════╝
using syntax_t = class_enum<_SYNTAX_e>;
using access_t = class_enum<_ACCESS_e>;
using status_t = class_enum<_STATUS_e>;


//╔════════════════════════════════╗
//║ String constructors definition ║
//╚════════════════════════════════╝

#include<array>
#include<string.h>

template<typename T, size_t N, size_t M>
__attribute__((always_inline))
inline T loop(
    const char* a,
    const std::array<const char*, N> & lut, 
    const std::array<T, M>& ret)
{
    static_assert(N + 1 == M, "Loop template indicies error: N + 1 != M");
    for(int i = 0; i < N; i++)
    {
       if ( 0 == strcasecmp(a, lut[i]) )
           return ret[i];
    }
    return ret[N];
}

template<>
class_enum<_SYNTAX_e>::class_enum(const std::string & value)
{
    static const std::array<const char*, 4> lut =
     {"OCTET_STRING", "INTEGER", "OBJECT_IDENTIFIER", "IMPORT_S"};
    static const std::array<_SYNTAX_e, 5> ret =
     {OCTET_STRING, INTEGER, OBJECT_IDENTIFIER, IMPORT_S, _SYNTAX_e_MAX_ENUM};

    this->value = loop(value.c_str(), lut, ret);
}

template<>
class_enum<_ACCESS_e>::class_enum(const std::string & value)
{
    static const std::array<const char*, 3> lut =
     {"READ-ONLY", "READ-WRITE", "NOT-ACCESSIBLE"};
    static const std::array<_ACCESS_e, 4> ret =
     {READ_ONLY, READ_WRITE, NOT_ACCESSIBLE, _ACCESS_e_MAX_ENUM};

    this->value = loop(value.c_str(), lut, ret);
}

template<>
class_enum<_STATUS_e>::class_enum(const std::string & value)
{
    static const std::array<const char*, 2> lut =
     {"MANDATORY", "DEPRECATED"};
    static const std::array<_STATUS_e, 3> ret =
     {MANDATORY, DEPRECATED, _STATUS_e_MAX_ENUM};

    this->value = loop(value.c_str(), lut, ret);
}