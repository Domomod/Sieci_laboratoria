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
struct cber_identifier
{
    union
    {
        struct{
            uint8_t tag :5;
            uint8_t constructed :1;
            uint8_t class_id :2;
        }__attribute__((packed));
        uint8_t identifier;
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
        uint8_t octet;
    };
};

__attribute__((packed))
struct cber_length
{
    union
    {
        struct{
            uint8_t value :7;
            uint8_t long_flag :1;
        };
        uint8_t length;
    };
};

__attribute__((packed))
struct cber_length_octet
{
    uint8_t length;
};

struct cber_code{
    cber_identifier identifier;
    std::vector<cber_identifer_octet> identifier_octets; // Can be empty
    cber_length length;
    std::vector<cber_length_octet> length_octets; // Can be empty
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
    cber_code encodeInteger(uint64_t Integer, visibility_t vis, PC_t pc, uint64_t tag)
    {
        cber_code code;
        code.identifier.class_id = (uint8_t)vis;
        code.identifier.constructed = (uint8_t)pc;
        if(tag < 31)
        {
            code.identifier.tag = tag;
        }
        else
        {
            code.identifier.tag = -1u; //set bitfield to ones
            size_t num_bits = uint64_log2(tag)+1;
            size_t num_octets = num_bits / 7 + (num_bits % 7 != 0);
            code.identifier_octets.resize(num_octets);
            uint64_t tag_temp = tag;
            for(int i = 0; i < num_octets; i++)
            {
                code.identifier_octets[num_octets - 1 - i].last_flag = 1;
                code.identifier_octets[num_octets - 1 - i].value = (uint8_t)tag_temp; //Aware of the conversion loss
                tag_temp >>= 7;
            }
            code.identifier_octets[num_octets - 1].last_flag = 0;
        }

        size_t length_bits = uint64_log2(Integer) + 1;
        size_t length_bytes = length_bits / 8 + (length_bits % 8 != 0);
        if(length_bytes< 128)
        {
            code.length.long_flag = 0;
            code.length.value = length_bytes;
        }
        else
        {
            size_t num_bits = uint64_log2(length_bytes) + 1;
            size_t num_octets = num_bits / 8 + (num_bits % 8 != 0);
            code.length_octets.resize(num_octets);
            int length_bytes_temp = length_bytes;
            for(int i = 0; i < num_octets; i++)
            {
                code.length_octets[num_octets - 1 - i].length = (uint8_t)length_bytes_temp; //Aware of the conversion loss
                length_bytes_temp >>= 8;
            }
        }

        // Print bytes
        printf("Encoding INTEGER %llu, tag %d\n", Integer, tag);
        print_byte_as_bits(code.identifier.identifier);
        for(auto & octet : code.identifier_octets)
        {
            print_byte_as_bits(octet.octet);
        }
        printf("\n");
        print_byte_as_bits(code.length.length);
        for(auto & octet : code.length_octets)
        {
            print_byte_as_bits(octet.length);
        }
        printf("\n");

        // Print hex
        printf("%02X ",code.identifier.identifier);
        for(auto & octet : code.identifier_octets)
        {
            printf("%02X ",octet.octet);
        }
        printf("%02X ",code.length.length);
        for(auto & octet : code.length_octets)
        {
            printf("%02X ",octet.length);
        }
        printf("\n");
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