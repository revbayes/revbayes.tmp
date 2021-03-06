/**
 * @file
 * This file contains the declaration of the RevLanguage variance-covariance function, which
 * is used to created deterministic variable associated with the variance-covariance function.
 *
 * @brief Declaration and implementation of Func_varianceCovarianceMatrix
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: $Date: 2012-04-20 04:06:14 +0200 (Fri, 20 Apr 2012) $
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 * @version 1.0
 *
 * $Id: Func_varianceCovarianceMatrix.h 1406 2012-04-20 02:06:14Z hoehna $
 */


#ifndef Func_varianceCovarianceMatrix_H
#define Func_varianceCovarianceMatrix_H

#include <string>
#include <iosfwd>
#include <vector>

#include "RlMatrixRealSymmetric.h"
#include "RlTypedFunction.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "MatrixReal.h"
#include "RevPtr.h"
#include "RlDeterministicNode.h"
#include "TypedDagNode.h"
#include "TypedFunction.h"

namespace RevLanguage {
class ArgumentRules;
class TypeSpec;
    
    class Func_varianceCovarianceMatrix : public TypedFunction<MatrixRealSymmetric> {
        
    public:
        Func_varianceCovarianceMatrix( void );
        
        // Basic utility functions
        Func_varianceCovarianceMatrix*                                  clone(void) const;                      //!< Clone the object
        static const std::string&                                       getClassType(void);                     //!< Get Rev type
        static const TypeSpec&                                          getClassTypeSpec(void);                 //!< Get class type spec
        std::string                                                     getFunctionName(void) const;            //!< Get the primary name of the function in Rev
        const TypeSpec&                                                 getTypeSpec(void) const;                //!< Get the type spec of the instance
        
        // Function functions you have to override
        RevBayesCore::TypedFunction< RevBayesCore::MatrixReal>*         createFunction(void) const;             //!< Create internal function object
        const ArgumentRules&                                            getArgumentRules(void) const;           //!< Get argument rules
        
    };
    
}

#endif
