#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <cassert>  
#include <map>  

#include "cmib_enum.hpp"

class CMIBType;

class CMIBobject
{

private:
    std::string _name;
    std::string _description;
    access_t _access;
    status_t _status;
    bool is_type_set = false;
    std::string type_name; 
    std::shared_ptr<CMIBType> type;

public:

    const std::string & name() const { return _name; };
    const std::string & description() const { return _description; };
    const access_t & access() const { return _access; };
    const status_t & status() const { return _status; };

    CMIBobject() : type_name(""), is_type_set(false) {}

    ~CMIBobject() 
    {
        if(is_type_set)
        {
            type_name.~basic_string();
        }
        else
        {
            type.~shared_ptr();
        }
    }

    CMIBobject(
            std::string _name,
            std::string _description,
            access_t _access,
            status_t _status,
            std::string type_name
        ) : 
            _name(_name),
            _description(_description),
            _access(_access),
            _status(_status),
            type_name(type_name),
            is_type_set(false)
    {

    }

    CMIBobject(
        const std::string & _name,
        const std::string & _description,
        const access_t & _access,
        const status_t & _status,
        const std::shared_ptr<CMIBType> & type
    ) : 
        _name(_name),
        _description(_description),
        _access(_access),
        _status(_status),
        type(type),
        is_type_set(true)
    {

    }

    void set_derrived_type(std::map<std::string, std::shared_ptr<CMIBType>> types_map){
        if(false == is_type_set)
        {
            std::cout << "Found dependency on " << type_name << ". Initiating map lookup.\n";
            auto type_temp = types_map.at(type_name);
            type = type_temp;
            is_type_set = true;
        }
        else
        {
            std::cout << "This type was already set. \n";
        }
    }

};

class CMIBType
{
private:
    syntax_t base_type;
    std::shared_ptr<CMIBType> derrived_from; //also can represent sequence of
    std::vector<std::shared_ptr<CMIBType>> sequence; // can be empty


public:
    std::string type_name= ""; // can be empty
    std::string derrived_name= ""; // can be empty
    std::string application  = "";
    std::string implicitness = "";
    std::string restrictions = "";

    CMIBType() = delete;
    explicit CMIBType(const syntax_t & base_type)  : base_type(base_type)
    {
    }

    explicit CMIBType(std::vector<std::shared_ptr<CMIBType>> sequence) : sequence(sequence), base_type(SEQUENCE) 
    {

    }

    explicit CMIBType(std::shared_ptr<CMIBType> cmibType_ptr, const syntax_t & e) : derrived_from(cmibType_ptr), base_type(e)
    {
    }

    void set_derrived_type(std::map<std::string, std::shared_ptr<CMIBType>> types_map)
    {
        switch (base_type.get())
        {
        case SEQUENCE:
            std::cout << "Descending into  " << type_name << " sequence\n";
            for(auto type : sequence)
            {
                type->set_derrived_type(types_map);
            }
            break;
        case SEQUENCE_OF:
            std::cout << "Descending into  " << type_name << " sequence of\n";
            derrived_from->set_derrived_type(types_map);
            break;
        case DERRIVED_TYPE:
            std::cout << "Descending into  " << type_name << " derrived type\n";
            std::cout << "Found dependency on " << derrived_name << ". Initiating map lookup.\n";
            derrived_from = types_map.at(derrived_name);
        default:
            break;
        }
    }

    void print()
    {

        switch (base_type.get())
        {
        case SEQUENCE:
            std::cout << "    SEQUENCE     ->\n";
            for(auto type_ptr : sequence)
            {
                std::cout << "\t\t" << type_ptr->derrived_name << " ";
                if(!type_ptr->restrictions.empty()) std::cout << type_ptr->restrictions;
                std::cout  << ",\n";
            }
            break;
        case SEQUENCE_OF:
            std::cout  << "   SEQUENCE OF  ->" << derrived_from->derrived_name << " ";
            if(!restrictions.empty()) std::cout << restrictions;
            std::cout  << "\n";
            break;
        default:
            std::cout << "  REGULAR  TYPE  ->" <<  derrived_name << " ";
            if(!restrictions.empty()) std::cout << restrictions;
            std::cout  << "\n";
            break;
        }
    }
};