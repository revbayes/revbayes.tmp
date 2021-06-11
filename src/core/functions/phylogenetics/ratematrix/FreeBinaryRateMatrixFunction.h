#ifndef FreeBinaryRateMatrixFunction_h
#define FreeBinaryRateMatrixFunction_h

#include "TypedFunction.h"
#include "RateGenerator.h"

namespace RevBayesCore {
class DagNode;
template <class valueType> class RbVector;
template <class valueType> class TypedDagNode;
    
    class FreeBinaryRateMatrixFunction : public TypedFunction<RateGenerator> {
        
    public:
        FreeBinaryRateMatrixFunction(const TypedDagNode< RbVector<double> > *tr, bool rescale_to_one);
        virtual                                            ~FreeBinaryRateMatrixFunction(void);                                                    //!< Virtual destructor
        
        // public member functions
        FreeBinaryRateMatrixFunction*                       clone(void) const;                                                              //!< Create an independent clone
        void                                                update(void);
        
    protected:
        void                                                swapParameterInternal(const DagNode *oldP, const DagNode *newP);                        //!< Implementation of swaping parameters
        
    private:
        
        // members
        const TypedDagNode< RbVector<double> >*             transition_rates;
        
    };
    
}

#endif /* defined(FreeBinaryRateMatrixFunction_h) */
