#include <ostream>
#include <string>

#include "ArgumentRule.h"
#include "ArgumentRules.h"
#include "MetropolisHastingsMove.h"
#include "ModelVector.h"
#include "Move_CorrelationMatrixExpansion.h"
#include "RealPos.h"
#include "RevObject.h"
#include "RlMatrixReal.h"
#include "TypedDagNode.h"
#include "TypeSpec.h"
#include "RlContinuousCharacterData.h"
#include "CorrelationMatrixExpansionProposal.h"
#include "ModelObject.h"
#include "Move.h"
#include "RevPtr.h"
#include "RevVariable.h"
#include "RlMove.h"
#include "StochasticNode.h"

namespace RevBayesCore { class ContinuousCharacterData; }
namespace RevBayesCore { class MatrixReal; }
namespace RevBayesCore { class Proposal; }
namespace RevBayesCore { template <class valueType> class RbVector; }

using namespace RevLanguage;

Move_CorrelationMatrixExpansion::Move_CorrelationMatrixExpansion() : Move() {
    
}


/**
 * The clone function is a convenience function to create proper copies of inherited objected.
 * E.g. a.clone() will create a clone of the correct type even if 'a' is of derived type 'b'.
 *
 * \return A new copy of the process.
 */
Move_CorrelationMatrixExpansion* Move_CorrelationMatrixExpansion::clone(void) const
{
    
	return new Move_CorrelationMatrixExpansion(*this);
}


void Move_CorrelationMatrixExpansion::constructInternalObject( void )
{
    // we free the memory first
    delete value;

    double w = static_cast<const RealPos &>( weight->getRevObject() ).getValue();

    RevBayesCore::TypedDagNode<RevBayesCore::MatrixReal >* tmp = static_cast<const MatrixReal &>( correlation_matrix->getRevObject() ).getDagNode();
    RevBayesCore::StochasticNode<RevBayesCore::MatrixReal > *n = static_cast<RevBayesCore::StochasticNode<RevBayesCore::MatrixReal> *>( tmp );

    RevBayesCore::TypedDagNode<RevBayesCore::RbVector<double> >* var = static_cast<const ModelVector<RealPos>& >( variance->getRevObject() ).getDagNode();

    RevBayesCore::TypedDagNode<RevBayesCore::ContinuousCharacterData>* mvbm_tdn  = static_cast<const RevLanguage::ContinuousCharacterData&>( mvbm->getRevObject() ).getDagNode();
    RevBayesCore::StochasticNode<RevBayesCore::ContinuousCharacterData>* mvbm_sn = static_cast<RevBayesCore::StochasticNode<RevBayesCore::ContinuousCharacterData>* >(mvbm_tdn);
    
    RevBayesCore::Proposal *p  = new RevBayesCore::CorrelationMatrixExpansionProposal(n, var, mvbm_sn);
    value = new RevBayesCore::MetropolisHastingsMove(p,w,false);
    
}


/** Get Rev type of object */
const std::string& Move_CorrelationMatrixExpansion::getClassType(void)
{
    
    static std::string rev_type = "Move_CorrelationMatrixExpansion";
    
	return rev_type; 
}

/** Get class type spec describing type of object */
const TypeSpec& Move_CorrelationMatrixExpansion::getClassTypeSpec(void)
{
    
    static TypeSpec rev_type_spec = TypeSpec( getClassType(), new TypeSpec( Move::getClassTypeSpec() ) );
    
	return rev_type_spec; 
}


/**
 * Get the Rev name for the constructor function.
 *
 * \return Rev name of constructor function.
 */
std::string Move_CorrelationMatrixExpansion::getMoveName( void ) const
{
    // create a constructor function name variable that is the same for all instance of this class
    std::string c_name = "CorrelationMatrixExpansion";
    
    return c_name;
}


/** Return member rules (no members) */
const MemberRules& Move_CorrelationMatrixExpansion::getParameterRules(void) const
{
    
    static MemberRules move_member_rules;
    static bool rules_set = false;
    
    if ( !rules_set )
    {
        
        move_member_rules.push_back( new ArgumentRule( "correlationMatrix", MatrixReal::getClassTypeSpec(),              "The correlation matrix on which this move operates on.", ArgumentRule::BY_REFERENCE, ArgumentRule::STOCHASTIC ) );
        move_member_rules.push_back( new ArgumentRule( "multivariateBM" ,   ContinuousCharacterData::getClassTypeSpec(), "The multivariate Brownian motion variable associated with the correlation matrix.", ArgumentRule::BY_REFERENCE, ArgumentRule::STOCHASTIC ) );
        move_member_rules.push_back( new ArgumentRule( "variance",          ModelVector<RealPos>::getClassTypeSpec(),    "The vector of variances.", ArgumentRule::BY_REFERENCE, ArgumentRule::ANY)  );
        
        /* Inherit weight from Move, put it after variable */
        const MemberRules& inheritedRules = Move::getParameterRules();
        move_member_rules.insert( move_member_rules.end(), inheritedRules.begin(), inheritedRules.end() );
        
        rules_set = true;
    }
    
    return move_member_rules;
}

/** Get type spec */
const TypeSpec& Move_CorrelationMatrixExpansion::getTypeSpec( void ) const {
    
    static TypeSpec type_spec = getClassTypeSpec();
    
    return type_spec;
}



/** Get type spec */
void Move_CorrelationMatrixExpansion::printValue(std::ostream &o) const {
    
    o << "Move_CorrelationMatrixExpansion(";
//    if (tree != NULL) {
//        o << tree->getName();
//    }
//    else {
//        o << "?";
//    }
    o << ")";
}


/** Set a NearestNeighborInterchange variable */
void Move_CorrelationMatrixExpansion::setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var) {
    
    if ( name == "correlationMatrix" ) {
        correlation_matrix = var;
    }
    else if ( name == "multivariateBM" ) {
        mvbm = var;
    }
    else if ( name == "variance" ) {
        variance = var;
    }
    else {
        Move::setConstParameter(name, var);
    }
}
