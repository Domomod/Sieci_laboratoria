#include "cmib_object.hpp"

std::string CMIBobject::get_IDENTI()
{
    return (IDENTI);
}

// SYNTAX CMIBobject::get_SYNTAX()
// {
//     return (syntax_scoped);
// }
// ACCESS CMIBobject::get_ACCESS()
// {
//     return (access_scoped);
// }
// STATUS CMIBobject::get_STATUS()
// {
//     return (status_scoped);
// }
// std::string CMIBobject::get_DESCRI()
// {
//     return (DESCRI);
// }

void CMIBobject::set_IDENTI(std::string s)
{
    IDENTI = s;
}

// void CMIBobject::set_SYNTAX(SYNTAX syn_s)
// {
//     syntax_scoped = syn_s;
// }

// void CMIBobject::set_ACCESS(ACCESS ac_s)
// {
//     access_scoped = ac_s;
// }
// void CMIBobject::set_STATUS(STATUS s_s)
// {
//     status_scoped = s_s;
// }

void CMIBobject::set_DESCRI(std::string s)
{
    DESCRI = s;
}