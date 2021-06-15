#include "Taxon.h"

#include <string>

using namespace RevBayesCore;


/**
 * Default constructor.
 */
Taxon::Taxon( void ) :
    name( "" ),
    species_name( "" )
{
    
}


/**
 * Constructor simply initiating the object and its members.
 *
 * \param[in]    n     The name of the taxon.
 */
Taxon::Taxon(const std::string &n) :
    name( n ),
    species_name( n )
{
    
}


/**
 * Equals operator.
 * We check the species name and the individuals name.
 */
bool Taxon::operator==(const RevBayesCore::Taxon &t) const
{
    
    if ( species_name != t.species_name )
    {
        return false;
    }
    
    if ( name != t.name)
    {
        return false;
    }

    return true;
}


/**
 * Not equals operator. We simply invert the result of the equals operation.
 */
bool Taxon::operator!=(const RevBayesCore::Taxon &t) const
{
    
    return !operator==(t);
}


/**
 * Less-than operator.
 * We check first the species name and then the indidivuals name.
 */
bool Taxon::operator<(const RevBayesCore::Taxon &t) const
{
    
    if ( species_name < t.species_name)
    {
        return true;
    }
    else if ( species_name > t.species_name )
    {
        return false;
    }
    
    if ( name < t.name )
    {
        return true;
    }
    else if ( name > t.name )
    {
        return false;
    }
    
    // by default return false.
    return false;
}



/**
 * Less-than or equals operator.
 */
bool Taxon::operator<=(const RevBayesCore::Taxon &t) const
{
    
    return operator<(t) || operator==(t);
}


/**
 * Greater-than operator.
 * We check first the species name and then the indidivuals name.
 */
bool Taxon::operator>(const RevBayesCore::Taxon &t) const
{
    
    return operator<=(t) == false;
}



/**
 * Greater-than or equals operator.
 */
bool Taxon::operator>=(const RevBayesCore::Taxon &t) const
{
    
    return operator>(t) || operator==(t);
}


/**
 * Get the age for this taxon.
 *
 * \return    The age.
 */
double Taxon::getAge( void ) const
{
    return min_age.getMin();
}


/**
 * Get the age range for this taxon.
 *
 * \return    The age range.
 */
TimeInterval Taxon::getAgeRange( void ) const
{
    return TimeInterval(min_age.getMin(), max_age.getMax());
}


/**
 * Get the max age for this taxon.
 *
 * \return    The age.
 */
double Taxon::getMaxAge( void ) const
{
    return max_age.getMin();
}


/**
 * Get the max age range for this taxon.
 *
 * \return    The age range.
 */
const TimeInterval& Taxon::getMaxAgeRange( void ) const
{
    return max_age;
}


/**
 * Get the min age for this taxon.
 *
 * \return    The age.
 */
double Taxon::getMinAge( void ) const
{
    return min_age.getMin();
}


/**
 * Get the min age range for this taxon.
 *
 * \return    The age range.
 */
const TimeInterval& Taxon::getMinAgeRange( void ) const
{
    return min_age;
}


/**
* Get a JSON-formatted string description of this object.
*
* \return    The JSON-formatted string.
*/
const std::string Taxon::getJsonRespresentation(void) const {

    std::string jsonStr = "";
    jsonStr += "{\"Taxon\": {";
    jsonStr += "\"name\": \"" + name + "\", ";
    jsonStr += "\"speciesName\": \"" + species_name + "\", ";
    jsonStr += "\"TimeInterval\": {\"minAge\": " + std::to_string(min_age.getMin()) + ", ";
    jsonStr += "\"maxAge\": " + std::to_string(max_age.getMax()) + "}}";
    return jsonStr;
}


/**
 * Get the name info for this taxon.
 *
 * \return    The name.
 */
const std::string& Taxon::getName( void ) const
{
    return name;
}


/**
 * Get the species name for this taxon.
 *
 * \return    The species name.
 */
const std::string& Taxon::getSpeciesName( void ) const
{
    return species_name;
}


/**
 * Set the age for this taxon.
 *
 * \param[in]    a     The age.
 */
void Taxon::setAge(double a)
{
    min_age = TimeInterval(a,a);
    max_age = TimeInterval(a,a);
}


/**
 * Set the age range for this taxon.
 *
 * \param[in]    d     The age range.
 */
void Taxon::setAgeRange( const TimeInterval &d )
{
    min_age = TimeInterval(d.getMin(),d.getMin());
    max_age = TimeInterval(d.getMax(),d.getMax());
}


/**
 * Set the min age range for this taxon.
 *
 * \param[in]    d     The age range.
 */
void Taxon::setMinAgeRange( const TimeInterval &d )
{
    min_age = d;
}


/**
 * Set the max age range for this taxon.
 *
 * \param[in]    d     The age range.
 */
void Taxon::setMaxAgeRange( const TimeInterval &d )
{
    max_age = d;
}


/**
 * Set the name info for this taxon.
 *
 * \param[in]    n     The name.
 */
void Taxon::setName( const std::string &n )
{
    name = n;
}


/**
 * Set the species name for this taxon.
 *
 * \param[in]    sn     The species name.
 */
void Taxon::setSpeciesName( const std::string &sn )
{
    species_name = sn;
}


std::ostream& RevBayesCore::operator<<(std::ostream& o, const Taxon& x)
{
    // Sebastian: We will not write out the species name or date anymore
    // These info need to be queried specifically
//    o << x.getName() << ":" << x.getspecies_name() << ":" << x.getDate();
    o << x.getName();
    return o;
}
