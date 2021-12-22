#include <stdint.h>
#include <vector>
#include <stdio.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #define __LITTLE_ENDIAN
#else
    #include <endian.h>
#endif

int uint64_log2(uint64_t n)
{
  #define S(k) if (n >= (UINT64_C(1) << k)) { i += k; n >>= k; }

  int i = -(n == 0); S(32); S(16); S(8); S(4); S(2); S(1); return i;

  #undef S
}

enum class visibility_t
{
    UNIVERSAL = 0b00,
    APPLICATION = 0b01,
    CONTEXT_SPECIFIC = 0b10,
    PRIVATE = 0b11
};

enum class PC_t
{
    PRIMITIVE = 0b0,
    CONSTRUCTED = 0b1,
};


__attribute__((packed))
struct cber_identifier_header
{
    union
    {
        struct{
            uint8_t tag :5;
            uint8_t constructed :1;
            uint8_t class_id :2;
        }__attribute__((packed));
        uint8_t u8;
    };
};

__attribute__((packed))
struct cber_identifer_octet
{
    union
    {
        struct{
            uint8_t value :7;
            uint8_t last_flag :1;
        };
        uint8_t u8;
    };
};

__attribute__((packed))
struct cber_length_header
{
    union
    {
        struct{
            uint8_t value :7;
            uint8_t long_flag :1;
        };
        uint8_t u8;
    };
};

__attribute__((packed))
struct cber_length_octet
{
    uint8_t u8;
};

struct cber_identifier
{
    cber_identifier_header header;
    std::vector<cber_identifer_octet> octets; // Can be empty
};

struct cber_length
{
    cber_length_header header;
    std::vector<cber_length_octet> octets; // Can be empty
};

struct cber_code{
    cber_identifier identifier;
    cber_length length;
    std::vector<uint8_t> content; // Can be empty
};

void print_byte_as_bits(char val) {
  for (int i = 7; 0 <= i; i--) {
    printf("%c", (val & (1 << i)) ? '1' : '0');
  }
  printf(" ");
}

class CberCoder
{
public:
/* --------------
 * - Base Types -
 * -------------- */

    void print_identifier_hex(const cber_identifier & identifier)
    {
        printf("%02X ",identifier.header.u8);
        for(auto & octet : identifier.octets)
        {
            printf("%02X ",octet.u8);
        }
    }

    void print_length_hex(const cber_length & length)
    {

        printf("%02X ",length.header);
        for(auto & octet : length.octets)
        {
            printf("%02X ",octet.u8);
        }
    }

    void print_identifier_bin(const cber_identifier & identifier)
    {
        print_byte_as_bits(identifier.header.u8);
        for(auto & octet : identifier.octets)
        {
            print_byte_as_bits(octet.u8);
        }
    }

    void print_length_bin(const cber_length & length)
    {
        print_byte_as_bits(length.header.u8);
        for(auto & octet : length.octets)
        {
            print_byte_as_bits(octet.u8);
        }
    }


    void print_code(const cber_code & code)
    {
        // Print bytes
        print_identifier_hex(code.identifier);
        print_length_hex(code.length);
        printf("\n");

        // Print hex
        print_identifier_bin(code.identifier);
        print_length_bin(code.length);
        printf("\n");
    }

    cber_length encodeLength(uint64_t length_bytes)
    {
        cber_length length;
        if(length_bytes< 128)
        {
            length.header.long_flag = 0;
            length.header.value = length_bytes;
        }
        else
        {
            size_t num_bits = uint64_log2(length_bytes) + 1;
            size_t num_octets = num_bits / 8 + (num_bits % 8 != 0);
            length.octets.resize(num_octets);
            int length_bytes_temp = length_bytes;
            for(int i = 0; i < num_octets; i++)
            {
                length.octets[num_octets - 1 - i].u8 = (uint8_t)length_bytes_temp; //Aware of the conversion loss
                length_bytes_temp >>= 8;
            }
        }
        return length;
    }

    cber_identifier encodeIdentifier(visibility_t vis, PC_t pc, uint64_t tag)
    {
        cber_identifier identifier;
        identifier.header.class_id = (uint8_t)vis;
        identifier.header.constructed = (uint8_t)pc;
        if(tag < 31)
        {
            identifier.header.tag = tag;
        }
        else
        {
            identifier.header.tag = -1u; //set bitfield to ones
            size_t num_bits = uint64_log2(tag)+1;
            size_t num_octets = num_bits / 7 + (num_bits % 7 != 0);
            identifier.octets.resize(num_octets);
            uint64_t tag_temp = tag;
            for(int i = 0; i < num_octets; i++)
            {
                identifier.octets[num_octets - 1 - i].last_flag = 1;
                identifier.octets[num_octets - 1 - i].value = (uint8_t)tag_temp; //Aware of the conversion loss
                tag_temp >>= 7;
            }
            identifier.octets[num_octets - 1].last_flag = 0;
        }
        return identifier;
    }

    cber_code encodeInteger(uint64_t Integer, visibility_t vis, PC_t pc, uint64_t tag)
    {
        cber_code code;

        printf("Encoding INTEGER %llu, tag %d\n", Integer, tag);
        code.identifier = encodeIdentifier(vis,pc,tag);
        size_t length_bits = uint64_log2(Integer) + 1;
        size_t length_bytes = length_bits / 8 + (length_bits % 8 != 0);
        code.length = encodeLength(length_bytes);
        print_code(code);
        return code;
    }
    cber_code encodeOctetString();
    cber_code encodeNull();
    cber_code encodeObjectIdentifier();
    //void encodeByteArray();
/* -----------------
 * - Complex Types -
 * ----------------- */
    void startSequence();
    void endSequence();
    
private:
    void encode();
};