#ifndef PhyloWhiteNoiseProcess_H
#define PhyloWhiteNoiseProcess_H

#include "RbVector.h"
#include "TypedDistribution.h"
#include "TopologyNode.h"

namespace RevBayesCore {
class DagNode;
class Tree;
template <class valueType> class TypedDagNode;
    
    class PhyloWhiteNoiseProcess : public TypedDistribution< RbVector<double> > {
        
    public:
        // constructor(s)
        PhyloWhiteNoiseProcess(const TypedDagNode< Tree > *t, const TypedDagNode< double >* s);
        
        // public member functions
        PhyloWhiteNoiseProcess*                                 clone(void) const;                                                                      //!< Create an independent clone
        double                                                  computeLnProbability(void);
        void                                                    redrawValue(void);
        
    protected:
        // Parameter management functions
        void                                                    swapParameterInternal(const DagNode *oldP, const DagNode *newP);            //!< Swap a parameter
        
    private:
        // helper methods
        void                                                    simulate();
        double                                                  recursiveLnProb(const TopologyNode& n);
        void                                                    recursiveSimulate(const TopologyNode& n);
        
        // private members
        const TypedDagNode< Tree >*                             tau;
        const TypedDagNode< double >*                           sigma;
        
    };
    
}
#endif
