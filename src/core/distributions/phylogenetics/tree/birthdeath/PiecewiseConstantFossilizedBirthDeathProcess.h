#ifndef PiecewiseConstantFossilizedBirthDeathProcess_H
#define PiecewiseConstantFossilizedBirthDeathProcess_H

#include "RbVector.h"
#include "AbstractBirthDeathProcess.h"
#include "AbstractPiecewiseConstantFossilizedRangeProcess.h"

namespace RevBayesCore {
    
    class Clade;
    class Taxon;
    
    /**
     * @brief Piecewise-constant fossilized birth-death range distribution of sampled/extended trees.
     *
     * The piecewise-constant fossilized birth-death range process has constant rates for each time interval.
     * At the end of each time interval there may be an abrupt rate-shift (jump) for each
     * of the rates. Additionally, there may be sampling at the end of each interval.
     * Finally, fossils are sampled with rate psi, the others (fossils and extant taxa) are
     * sampled at sampling times (including the present).
     *
     * We assume that the rate vectors have one more element than the rate-change vectors.
     * Thus, one rate-change means always two interval, two rate-changes three interval, and so on.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (Walker Pett)
     * @since 2014-03-18, version 1.0
     *
     */
    class PiecewiseConstantFossilizedBirthDeathProcess : public AbstractBirthDeathProcess, public AbstractPiecewiseConstantFossilizedRangeProcess {
        
        using AbstractBirthDeathProcess::taxa;

    public:
        PiecewiseConstantFossilizedBirthDeathProcess (const TypedDagNode<double>* ra,
                                                      const DagNode *speciation,
                                                      const DagNode *extinction,
                                                      const DagNode *psi,
                                                      const DagNode *counts,
                                                      const TypedDagNode<double>* rho,
                                                      const DagNode *lambda_a,
                                                      const DagNode *beta,
                                                      const TypedDagNode<RbVector<double> > *times,
                                                      const std::string &condition,
                                                      const std::vector<Taxon> &taxa,
                                                      bool uo,
                                                      bool pa,
                                                      bool ex );  //!< Constructor
        
        // public member functions
        PiecewiseConstantFossilizedBirthDeathProcess*   clone(void) const;                                         //!< Create an independent clone

        double                                          getAnageneticSpeciationRate( size_t index ) const;
        double                                          getSymmetricSpeciationProbability( size_t index ) const;

        void                                            simulateClade(std::vector<TopologyNode *> &n, double age, double present);

    protected:
        void                                            updateStartEndTimes();
        int                                             updateStartEndTimes(const TopologyNode & );

        double                                          pSurvival(double start, double end) const;             //!< Compute the probability of survival of the process (without incomplete taxon sampling).

        // Parameter management functions
        double                                          computeLnProbabilityTimes(void);                            //!< Compute the log-transformed probability of the current value.
        double                                          computeLnProbabilityDivergenceTimes(void);                            //!< Compute the log-transformed probability of the current value.

        double                                          lnProbNumTaxa(size_t n, double start, double end, bool MRCA) const { throw RbException("Cannot compute P(nTaxa)."); }
        double                                          lnProbTreeShape(void) const;

        double                                          q(size_t i, double t, bool tilde = false) const;
        double                                          H(size_t i, double x, double t) const;
        virtual double                                  Z(size_t k, size_t i, double x, double t) const;

        double                                          simulateDivergenceTime(double origin, double present) const;    //!< Simulate a speciation event.
        std::vector<double>                             simulateDivergenceTimes(size_t n, double origin, double present, double min) const;                 //!< Simulate n speciation events.

        void                                            keepSpecialization(DagNode *toucher);
        void                                            restoreSpecialization(DagNode *toucher);
        void                                            touchSpecialization(DagNode *toucher, bool touchAll);

        // Parameter management functions
        void                                            swapParameterInternal(const DagNode *oldP, const DagNode *newP);                //!< Swap a parameter

        virtual void                                    updateIntervals();

    private:
        
        // helper functions
        double                                          getMaxTaxonAge( const TopologyNode& ) const;

        mutable std::vector<bool>                       I;
        bool                                            extended;

        //mutable std::vector<bool>                       bifurcation;

        mutable std::vector<double>                     anagenetic;
        mutable std::vector<double>                     symmetric;

        const TypedDagNode<double >*                    homogeneous_lambda_a;                                    //!< The homogeneous anagenetic speciation rates.
        const TypedDagNode<RbVector<double> >*          heterogeneous_lambda_a;                                  //!< The heterogeneous anagenetic speciation rates.
        const TypedDagNode<double >*                    homogeneous_beta;                                        //!< The homogeneous symmetric speciation prob.
        const TypedDagNode<RbVector<double> >*          heterogeneous_beta;                                      //!< The heterogeneous symmetric speciation probs.
    };
}

#endif
