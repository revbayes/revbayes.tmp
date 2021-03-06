//
//  Func_MixtureCladoProbs.h
//  revbayes-proj
//
//  Created by Michael Landis on 10/22/16.
//  Copyright © 2016 Michael Landis. All rights reserved.
//

#ifndef Func_MixtureCladoProbs_h
#define Func_MixtureCladoProbs_h


#include <string>
#include <iosfwd>
#include <vector>

#include "RlCladogeneticProbabilityMatrix.h"
#include "RlTypedFunction.h"
#include "CladogeneticProbabilityMatrix.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "RevPtr.h"
#include "RlDeterministicNode.h"
#include "TypedDagNode.h"
#include "TypedFunction.h"

namespace RevLanguage {
class ArgumentRules;
class TypeSpec;
    
    class Func_MixtureCladoProbs : public TypedFunction<CladogeneticProbabilityMatrix> {
        
    public:
        Func_MixtureCladoProbs( void );
        
        // Basic utility functions
        Func_MixtureCladoProbs*                                                clone(void) const;                                      //!< Clone the object
        static const std::string&                                       getClassType(void);                                     //!< Get Rev type
        static const TypeSpec&                                          getClassTypeSpec(void);                                 //!< Get class type spec
        std::string                                                     getFunctionName(void) const;                            //!< Get the primary name of the function in Rev
        const TypeSpec&                                                 getTypeSpec(void) const;                                //!< Get the type spec of the instance
        
        // Function functions you have to override
        RevBayesCore::TypedFunction< RevBayesCore::CladogeneticProbabilityMatrix>*         createFunction(void) const;                             //!< Create internal function object
        const ArgumentRules&                                            getArgumentRules(void) const;                           //!< Get argument rules
        
    };
    
}

#endif /* Func_MixtureCladoProbs_h */
