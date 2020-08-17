#include <math.h>
#include <iosfwd>
#include <string>
#include <vector>

#include "ArgumentRule.h"
#include "ArgumentRules.h"
#include "Dist_multispeciesCoalescentInverseGammaPrior.h"
#include "ModelVector.h"
#include "RealPos.h"
#include "RlTaxon.h"
#include "RlTimeTree.h"
#include "StochasticNode.h"
#include "DagMemberFunction.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "ModelObject.h"
#include "MultispeciesCoalescentInverseGammaPrior.h"
#include "RbHelpReference.h"
#include "RbVector.h"
#include "RevObject.h"
#include "RevPtr.h"
#include "RevVariable.h"
#include "RlDagMemberFunction.h"
#include "RlDeterministicNode.h"
#include "RlStochasticNode.h"
#include "RlTypedDistribution.h"
#include "RlTypedFunction.h"
#include "Tree.h"
#include "TypeSpec.h"
#include "TypedDagNode.h"
#include "TypedDistribution.h"
#include "TypedFunction.h"

namespace RevBayesCore { class Taxon; }

using namespace RevLanguage;


/**
 * Default constructor.
 *
 * The default constructor does nothing except allocating the object.
 */
Dist_multispeciesCoalescentInverseGammaPrior::Dist_multispeciesCoalescentInverseGammaPrior() : TypedDistribution<TimeTree>()
{

}

/**
 * Clone the object
 *
 * \return a clone of the object.
 */

Dist_multispeciesCoalescentInverseGammaPrior* Dist_multispeciesCoalescentInverseGammaPrior::clone(void) const
{

    return new Dist_multispeciesCoalescentInverseGammaPrior(*this);

}




/**
 * Create a new internal distribution object.
 *
 * This function simply dynamically allocates a new internal distribution object that can be
 * associated with the variable. The internal distribution object is created by calling its
 * constructor and passing the distribution-parameters (other DAG nodes) as arguments of the
 * constructor. The distribution constructor takes care of the proper hook-ups.
 *
 * \return A new internal distribution object.
 */
RevBayesCore::MultispeciesCoalescentInverseGammaPrior* Dist_multispeciesCoalescentInverseGammaPrior::createDistribution( void ) const
{

    // Get the parameters
    RevBayesCore::TypedDagNode<RevBayesCore::Tree>*                 st = static_cast<const TimeTree &>( species_tree->getRevObject() ).getDagNode();
    //const std::vector< std::vector<RevBayesCore::Taxon> >                &t  = static_cast<const ModelVector< ModelVector<Taxon> > &>( taxa[0].getRevObject() ).getValue();
    size_t                                                          ngt = size_t( static_cast<const Natural &>( num_gene_trees->getRevObject() ).getValue() );

    RevBayesCore::RbVector<RevBayesCore::RbVector<RevBayesCore::Taxon> > t = static_cast<const ModelVector<ModelVector<Taxon> > &>( taxa->getRevObject() ).getValue();

    //
    // std::vector< std::vector<RevBayesCore::Taxon> > *tv;
    // tv->reserve(ngt);
    //
    // for (size_t i=0; i<ngt; ++i)
    // {
    //     const std::vector<RevBayesCore::Taxon>                      &t = static_cast<const ModelVector<Taxon> &>( taxa[i].getRevObject() ).getValue();
    //     std::vector<RevBayesCore::Taxon>                            tc = t;
    //     tv->push_back(tc);
    // }

    RevBayesCore::MultispeciesCoalescentInverseGammaPrior*   d = new RevBayesCore::MultispeciesCoalescentInverseGammaPrior( st, t, ngt );


    //const std::vector<RevBayesCore::Taxon>      &t  = static_cast<const ModelVector<Taxon> &>( taxa->getRevObject() ).getValue();

    // RevBayesCore::TypedDagNode<RevBayesCore::RbVector<RevBayesCore::RbVector<long> > >* adj = static_cast<const ModelVector<ModelVector<Natural> > &>( this->args[0].getVariable()->getRevObject() ).getDagNode();
    // RevBayesCore::TypedDagNode<RevBayesCore::RbVector<RevBayesCore::RbVector<double> > >* dr;
    // dr = static_cast<const ModelVector<ModelVector<RealPos> > &>( this->args[0].getVariable()->getRevObject() ).getDagNode();


    //RevBayesCore::MultispeciesCoalescentInverseGammaPrior*   d = new RevBayesCore::MultispeciesCoalescentInverseGammaPrior( st, t, ngt );

    RevBayesCore::TypedDagNode<double>* s = static_cast<const RealPos &>( shape->getRevObject() ).getDagNode();
    d->setShape( s );
    RevBayesCore::TypedDagNode<double>* r = static_cast<const RealPos &>( rate->getRevObject() ).getDagNode();
    d->setRate( r );


    d->redrawValue();

    return d;
}



/**
 * Get Rev type of object
 *
 * \return The class' name.
 */
const std::string& Dist_multispeciesCoalescentInverseGammaPrior::getClassType(void)
{

    static std::string rev_type = "Dist_multispeciesCoalescentInverseGammaPrior";

    return rev_type;
}


/**
 * Get class type spec describing type of an object from this class (static).
 *
 * \return TypeSpec of this class.
 */
const TypeSpec& Dist_multispeciesCoalescentInverseGammaPrior::getClassTypeSpec(void)
{

    static TypeSpec rev_type_spec = TypeSpec( getClassType(), new TypeSpec( TypedDistribution<TimeTree>::getClassTypeSpec() ) );

    return rev_type_spec;
}


/**
 * Get the Rev name for the distribution.
 * This name is used for the constructor and the distribution functions,
 * such as the density and random value function
 *
 * \return Rev name of constructor function.
 */
std::string Dist_multispeciesCoalescentInverseGammaPrior::getDistributionFunctionName( void ) const
{
    // create a distribution name variable that is the same for all instance of this class
    std::string d_name = "MultiSpeciesCoalescentInverseGamma";

    return d_name;
}


/**
 * Get the member rules used to create the constructor of this object.
 *
 * The member rules of the Multispecies Coalescent process are:
 * (1) Species tree.
 * (2) Max Population size.
 * (3) Gene name to species name map.
 *
 * \return The member rules.
 */
const MemberRules& Dist_multispeciesCoalescentInverseGammaPrior::getParameterRules(void) const
{

    static MemberRules memberRules;
    static bool rules_set = false;

    if ( !rules_set )
    {
        memberRules.push_back( new ArgumentRule( "speciesTree"  , TimeTree::getClassTypeSpec(), "The species tree in which the gene trees evolve.", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY ) );
        memberRules.push_back( new ArgumentRule( "shape"        , RealPos::getClassTypeSpec(), "The shape of the inverse gamma prior distribution on the effective population sizes.", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY ) );
        memberRules.push_back( new ArgumentRule( "rate"         , RealPos::getClassTypeSpec(), "The rate of the inverse gamma prior distribution on the effective population sizes.", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY ) );
        memberRules.push_back( new ArgumentRule( "num_genes"    , Natural::getClassTypeSpec(), "The number of genes.", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY ) );
        memberRules.push_back( new ArgumentRule( "taxa"         , ModelVector<ModelVector<Taxon>>::getClassTypeSpec(), "The vector of taxa which have species and individual names.", ArgumentRule::BY_VALUE, ArgumentRule::ANY ) );

        rules_set = true;
    }

    return memberRules;
}


/**
 * Set a member variable.
 *
 * Sets a member variable with the given name and store the pointer to the variable.
 * The value of the variable might still change but this function needs to be called again if the pointer to
 * the variable changes. The current values will be used to create the distribution object.
 *
 * \param[in]    name     Name of the member variable.
 * \param[in]    var      Pointer to the variable.
 */
void Dist_multispeciesCoalescentInverseGammaPrior::setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var)
{

    if ( name == "speciesTree" )
    {
        species_tree = var;
    }
    else if ( name == "shape" )
    {
        shape = var;
    }
    else if ( name == "rate" )
    {
        rate = var;
    }
    else if ( name == "taxa" )
    {
        taxa = var;
    }
    else if ( name == "num_genes" )
    {
        num_gene_trees = var;
    }
    else
    {
        TypedDistribution<TimeTree>::setConstParameter(name, var);
    }

}


/** Get type spec */
const TypeSpec& Dist_multispeciesCoalescentInverseGammaPrior::getTypeSpec( void ) const
{

    static TypeSpec type_spec = getClassTypeSpec();

    return type_spec;
}
