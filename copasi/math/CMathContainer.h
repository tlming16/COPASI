// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathContainer
#define COPASI_CMathContainer

#include <map>

#include "copasi/report/CCopasiContainer.h"

#include "copasi/math/CMathObject.h"
#include "copasi/math/CMathEvent.h"
#include "copasi/math/CMathDependencyGraph.h"
#include "copasi/math/CMathReaction.h"
#include "copasi/math/CMathDelay.h"
#include "copasi/math/CMathHistory.h"
#include "copasi/math/CMathUpdateSequence.h"

#include "copasi/utilities/CVector.h"
#include "copasi/utilities/CMatrix.h"

#include "copasi/model/CModelParameter.h"

class CModelEntity;
class CReaction;
class CMoiety;
class CRandom;
class CMathEventQueue;

template < class CType > class CCopasiVector;

class CMathContainer: public CCopasiContainer
{
private:

  struct sDiscontinuous
  {
  public:
    CMathEvent * pEvent;
    CMathObject * pDiscontinuous;
  };

  struct sSize
  {
  public:
    size_t nFixed;
    size_t nFixedEventTargets; // auto determined
    size_t nTime; // 0 or 1
    size_t nODE;
    size_t nReactionSpecies; // fixed
    size_t nAssignment;
    size_t nIntensiveValues; // fixed
    size_t nMoieties; // auto determined
    size_t nEvents;
    size_t nEventAssignments;
    size_t nEventRoots; // auto determined
    size_t nReactions; // fixed
    size_t nDiscontinuities; // auto determined
    size_t nDelayValues; // auto determined
    size_t nDelayLags; // auto determined
    C_FLOAT64 * pValue;
    CMathObject * pObject;
  };

  static void createRelocation(const size_t & o, const size_t & n,
                               CMath::sRelocate & relocate,
                               std::vector< CMath::sRelocate > & relocations,
                               const bool & end = true);

  template < class CType > void relocateVector(CVectorCore< CType > & vector, size_t size,
      const std::vector< CMath::sRelocate > & relocations)
  {
    if (size != vector.size())
      {
        CVectorCore< CType > OldVector;
        OldVector.initialize(vector);
        vector.initialize(size, (size > 0) ? new CType[size] : NULL);

        CType * pOld = OldVector.array();
        CType * pNew = vector.array();
        CType * pNewEnd = pNew + std::min(vector.size(), OldVector.size());

        for (; pNew != pNewEnd; ++pNew, ++pOld)
          {
            *pNew = *pOld;
            pNew->relocate(this, relocations);
            pOld->moved();
          }

        if (OldVector.array() != NULL) delete [] OldVector.array();
      }
    else
      {
        CType * pNew = vector.array();
        CType * pNewEnd = pNew + vector.size();

        for (; pNew != pNewEnd; ++pNew)
          {
            pNew->relocate(this, relocations);
          }
      }
  }

public:
  void relocateUpdateSequence(CObjectInterface::UpdateSequence & sequence, const std::vector< CMath::sRelocate > & relocations) const;
  void relocateObjectSet(CObjectInterface::ObjectSet & objectSet, const std::vector< CMath::sRelocate > & relocations) const;
  void relocateValue(C_FLOAT64 *& pValue, const std::vector< CMath::sRelocate > & relocations) const;
  void relocateValue(const C_FLOAT64 *& pValue, const std::vector< CMath::sRelocate > & relocations) const;
  void relocateObject(CObjectInterface *& pObject, const std::vector< CMath::sRelocate > & relocations) const;
  void relocateObject(const CObjectInterface *& pObject, const std::vector< CMath::sRelocate > & relocations) const;
  void relocateObject(CMathObject *& pObject, const std::vector< CMath::sRelocate > & relocations) const;
  void relocateObject(const CMathObject *& pObject, const std::vector< CMath::sRelocate > & relocations) const;

private:
  /**
   * Default Constructor
   */
  CMathContainer();

public:

  /**
   * Specific Constructor
   * @param CModel & model
   */
  CMathContainer(CModel & model);

  /**
   * Copy constructor
   * @param const CMathContainer & src
   */
  CMathContainer(const CMathContainer & src);

  /**
   * Destructor
   */
  virtual ~CMathContainer();

  /**
   * Retrieve the values of all mathematical objects
   * @return const CVectorCore< C_FLOAT64 > & values
   */
  const CVectorCore< C_FLOAT64 > & getValues() const;

  /**
   * Retrieve the values of all mathematical objects
   * @return CVectorCore< C_FLOAT64 > & values
   */
  CVectorCore< C_FLOAT64 > & getValues();

  /**
   * Set the values of all mathematical objects
   * @param const CVectorCore< C_FLOAT64 > & values
   */
  void setValues(const CVectorCore< C_FLOAT64 > & values);

  /**
   * Retrieves the initial state values, i.e., all initial values of objects of
   * simulation type Fixed, Time, ODE, Dependent, and Independent. It includes only
   * extensive values for species.
   * @return const CVectorCore< C_FLOAT64 > & initialState
   */
  const CVectorCore< C_FLOAT64 > & getInitialState() const;

  /**
   * Retrieves the initial state values, i.e., all initial values of objects of
   * simulation type Fixed, Time, ODE, Dependent, and Independent. It includes only
   * extensive values for species.
   * @return CVectorCore< C_FLOAT64 > & initialState
   */
  CVectorCore< C_FLOAT64 > & getInitialState();

  /**
   * Set the initial state values, i.e., all initial values of objects of
   * simulation type Fixed, Time, ODE, Dependent, and Independent. It includes only
   * extensive values for species.
   * @param const CVectorCore< C_FLOAT64 > & initialState
   */
  void setInitialState(const CVectorCore< C_FLOAT64 > & initialState);

  /**
   * Retrieves the complete initial state values, i.e., all initial values including
   * all internal values.
   * @return const CVectorCore< C_FLOAT64 > & initialState
   */
  const CVectorCore< C_FLOAT64 > & getCompleteInitialState() const;

  /**
   * Set the complete initial state values, i.e., all initial values including
   * all internal values.
   * @param const CVectorCore< C_FLOAT64 > & initialState
   */
  void setCompleteInitialState(const CVectorCore< C_FLOAT64 > & initialState);

  /**
   * Retrieves the state values, i.e., all values of objects of
   * simulation type EventTarget, Time, ODE, Dependent, and Independent. It includes only
   * extensive values for species.
   * @param const bool & reduced
   * @return const CVectorCore< C_FLOAT64 > & state
   */
  const CVectorCore< C_FLOAT64 > & getState(const bool & reduced) const;

  /**
   * Set the state values, i.e., all initial values of objects of
   * simulation type Time, ODE, Dependent, and Independent. It includes only
   * extensive values for species.
   * @param const CVectorCore< C_FLOAT64 > & state
   */
  void setState(const CVectorCore< C_FLOAT64 > & state);

  /**
   * Check whether the current state is valid.
   */
  bool isStateValid() const;

  /**
   * Check whether the model is autonomous
   * @return const bool &isAutonomous
   */
  const bool & isAutonomous() const;

  /**
   * Check whether all objects are constant, i.e., do never change during simulation
   * @param const CObjectInterface::ObjectSet & objects
   * @return bool areObjectsConstant
   */
  bool areObjectsConstant(const CObjectInterface::ObjectSet & objects) const;

  /**
   * Notify the math container that the quantity conversion factor in
   * the corresponding model has changed
   */
  void quantityConversionChanged();

  /**
   * Retrieve the Quantity to Number conversion factor
   * @return C_FLOAT64 & quantity2NumberFactor
   */
  const C_FLOAT64 & getQuantity2NumberFactor() const;

  /**
   * Retrieves the state values, i.e., all values of objects of
   * simulation type EventTarget, Time, ODE, Dependent, and Independent. It includes only
   * extensive values for species.
   * @param const bool & reduced
   * @return const CMathHistoryCore & history
   */
  const CMathHistoryCore & getHistory(const bool & reduced) const;

  /**
   * Set all the history values needed for calculation.
   * @param const CMathHistoryCore & history
   */
  void setHistory(const CMathHistoryCore & history);

  /**
   * Retrieve the vector of delay lags
   * @return const CVectorCore< C_FLOAT64 > & delayLags
   */
  const CVectorCore< C_FLOAT64 > & getDelayLags() const;

  /**
   * Initialize a vector of individual absolute tolerances
   * @param const C_FLOAT64 & baseTolerance
   * @param const bool & reduced
   * @return CVector< C_FLOAT64 > absoluteTolerances
   */
  CVector< C_FLOAT64 > initializeAtolVector(const C_FLOAT64 & baseTolerance, const bool & reduced) const;

  /**
   * Retrieve the rate of state values, i.e., all initial values of objects of
   * simulation type EventTarget, Time, ODE, Dependent, and Independent. It includes only
   * extensive values for species.
   * @param const bool & reduced
   * @return const CVectorCore< C_FLOAT64 > & rate
   */
  const CVectorCore< C_FLOAT64 > & getRate(const bool & reduced) const;

  /**
   * Retrieve the total masses of the moieties.
   * @return const CVectorCore< C_FLOAT64 > & totalMasses
   */
  const CVectorCore< C_FLOAT64 > & getTotalMasses() const;

  /**
   * Retrieve reaction particle fluxes.
   * @return const CVectorCore< C_FLOAT64 > & particleFluxes
   */
  const CVectorCore< C_FLOAT64 > & getParticleFluxes() const;

  /**
   * Retrieve reaction fluxes.
   * @return const CVectorCore< C_FLOAT64 > & fluxes
   */
  const CVectorCore< C_FLOAT64 > & getFluxes() const;

  /**
   * Retrieve reaction propensities.
   * @return const CVectorCore< C_FLOAT64 > & propensities
   */
  const CVectorCore< C_FLOAT64 > & getPropensities() const;

  /**
   * Retrieve root values.
   * @return const CVectorCore< C_FLOAT64 > & roots
   */
  const CVectorCore< C_FLOAT64 > & getRoots() const;

  /**
   * Retrieve a vector of Boolean values indicating whether a root is changing
   * continuously or only during discrete event processing
   */
  const CVectorCore< bool > & getRootIsDiscrete() const;

  /**
   * Retrieve a vector of Boolean values indicating whether a root
   * time dependent
   */
  const CVectorCore< bool > & getRootIsTimeDependent() const;

  /**
   * Retrieve a vector of pointers to root processors
   */
  CVector< CMathEvent::CTrigger::CRootProcessor * > & getRootProcessors();

  /**
   * Calculate all dependent initial values based on initial extensive
   * or intensive values
   * @param const CModelParameter::Framework & framework
   */
  void updateInitialValues(const CModelParameter::Framework & framework);

  /**
   * Set the transient values to the initial values and calculate all
   * dependent values. Please call updateInitialValues before calling this
   * method to assure that all values are up to date.
   */
  void applyInitialValues();

  /**
   * Calculate all values required for simulation based on the current state
   * @param const bool & useMoieties
   */
  void updateSimulatedValues(const bool & useMoieties);

  /**
   * Calculate all transient data values. The simulated values need to be calculated beforehand.
   */
  void updateTransientDataValues();

  /**
   * Calculate all historic values required for delayed differential equations
   * @param const bool & useMoieties
   */
  void updateHistoryValues(const bool & useMoieties);

  /**
   * Calculate all dependent initial values based on initial extensive
   * or intensive values
   */
  void updatePriorityValues();

  /**
   * Apply the given update sequence to the mathematical objects in the container
   * @param const CObjectInterface::UpdateSequence & updateSequence
   */
  void applyUpdateSequence(const CObjectInterface::UpdateSequence & updateSequence);

  /**
   * Calculate the time derivative of all roots
   * @param CVector< C_FLOAT64 > & rootDerivatives
   */
  void calculateRootDerivatives(CVector< C_FLOAT64 > & rootDerivatives);

  /**
   * Calculates the Jacobian of the full model for the current state
   * and stores it in the provided matrix.
   * needs to be called before.
   * @param CMatrix< C_FLOAT64 > & Jacobian
   * @param const C_FLOAT64 & derivationFactor,
   * @param const bool & reduced
   */
  void calculateJacobian(CMatrix< C_FLOAT64 > & jacobian,
                         const C_FLOAT64 & derivationFactor,
                         const bool & reduced);

  /**
   * Calculates whether matrix elements in the Jacobian are identical
   * to zero or not and stored it in the provided matrix.
   * needs to be called before.
   * @param CMatrix< C_FLOAT64 > & jacobianDependencies
   * @param const bool & reduced
   */
  void calculateJacobianDependencies(CMatrix< C_INT32 > & jacobianDependencies,
                                     const bool & reduced);

  /**
   * Calculates whether matrix elements in the elasticity matrix are identical
   * to zero or not and stored it in the provided matrix.
   * needs to be called before.
   * @param CMatrix< C_FLOAT64 > & elasticityDependencies
   * @param const bool & reduced
   */
  void calculateElasticityDependencies(CMatrix< C_INT32 > & elasticityDependencies,
                                       const bool & reduced);

  /**
   * Process events scheduled at the given which a are checked for
   * equality or not
   * @param const bool & equality
   * @return CMath::StateChange stateChange
   */
  CMath::StateChange processQueue(const bool & equality);

  /**
   * Check whether the roots which have value 1 lead to firing of
   * events and schedule them if needed.
   * @param const bool & equality
   * @param const CVector< C_INT > & rootsFound
   */
  void processRoots(const bool & equality,
                    const CVector< C_INT > & rootsFound);

  /**
   * Check whether the roots which have value 1 lead to firing of
   * events and schedule them if needed.
   * @param const CVector< C_INT > & rootsFound
   */
  void processRoots(const CVector< C_INT > & rootsFound);

  /**
   * Retrieve the event processing queue.
   * @return CMathEventQueue & eventQueue
   */
  CMathEventQueue & getProcessQueue();

  /**
   * Retrieve the next execution time scheduled in the process queue
   * @return C_FLOAT64 processQueueExecutionTime
   */
  C_FLOAT64 getProcessQueueExecutionTime() const;

  /**
   * Fetch the initial state from the associated model
   */
  void fetchInitialState();

  /**
   * Push the initial state to the associated model
   */
  void pushInitialState();

  /**
   * Fetch the state from the associated model
   */
  void fetchState();

  /**
   * Push the state to the associated model
   */
  void pushState();

  /**
   * Push all transient values to the associated model.
   */
  void pushAllTransientValues();

  /**
   * Retrieve the CN of the math container
   * The math container provides values for the numerical values of model objects.
   * For the CN mechanism to work properly it has to pretend to be the model.
   * @return CCopasiObjectName
   */
  virtual CCopasiObjectName getCN() const;

  /**
   * Retrieve a descendant object by its partial CN.
   * @param const CCopasiObjectName & cn
   * @return const CObjectInterface * pObject
   */
  virtual const CObjectInterface * getObject(const CCopasiObjectName & cn) const;

  /**
   * Retrieve a object by its full CN.
   * @param const CCopasiObjectName & cn
   * @return const CObjectInterface * pObject
   */
  virtual const CObjectInterface * getObjectFromCN(const CCopasiObjectName & cn) const;

  /**
   * Retrieve a pointer to the corresponding the mathematical object
   * for the given object if it exists otherwise NULL
   * @param const CObjectInterface * pObject
   * @return CMathObject * pMathObject
   */
  CMathObject * getMathObject(const CObjectInterface * pObject) const;

  /**
   * Retrieve a pointer to the mathematical object for data value pointer
   * @param const C_FLOAT64 * pDataValue
   * @return CMathObject * pMathObject
   */
  CMathObject * getMathObject(const C_FLOAT64 * pDataValue) const;

  /**
   * Retrieve a pointer to the mathematical object for the given CN
   * @param const CCopasiObjectName & cn
   * @return CMathObject * pMathObject
   */
  CMathObject * getMathObject(const CCopasiObjectName & cn) const;

  /**
   * Retrieve a pointer to the data object for a data value pointer
   * @param const C_FLOAT64 * pDataValue
   * @return CCopasiObject * pDataObject
   */
  CCopasiObject * getDataObject(const C_FLOAT64 * pDataValue) const;

  /**
   * Retrieve a pointer to the corresponding the mathematical reaction
   * for the given reaction if it exists otherwise NULL
   * @param const CObjectInterface * pObject
   * @return CMathReaction * pMathReaction
   */
  CMathReaction * getMathReaction(const CReaction * pReaction) const;

  /**
   * Retrieve the pointer to the compartment of a species related object
   * otherwise NULL
   * @param const CMathObject * pObject
   * CMathObject * pCompartment
   */
  CMathObject * getCompartment(const CMathObject * pObject) const;

  /**
   * Retrieve the size of the largest compartment of the species changed in
   * the reaction
   * @param const CMathReaction * pReaction
   * @return CMathObject * pLargestCompartment
   */
  CMathObject * getLargestReactionCompartment(const CMathReaction * pReaction) const;

  /**
   * Retrieve the model for the container
   * @return const CModel & model
   */
  const CModel & getModel() const;

  /**
   * Retrieve the count of fixed values which are changed through events
   * @return const size_t & countFixedEventTargets
   */
  const size_t & getCountFixedEventTargets() const;

  /**
   * Retrieve the count of values determined by ODEs
   * @return const size_t & countODEs
   */
  const size_t & getCountODEs() const;

  /**
   * Retrieve the count of independent species
   * @return size_t countIndependentSpecies
   */
  size_t getCountIndependentSpecies() const;

  /**
   * Retrieve the count of dependent species
   * @return const size_t & countDependentSpecies
   */
  const size_t & getCountDependentSpecies() const;

  /**
   * Retrieve the count of assignments
   * @return const size_t & countDependentSpecies
   */
  const size_t & getCountAssignments() const;

  /**
   * Retrieve the count of fixed values, i.e., parameters
   * @return const size_t & countDependentSpecies
   */
  const size_t & getCountFixed() const;

  /**
   * Retrieve the reactions
   * @return CVectorCore< CMathReaction > & reactions
   */
  CVectorCore< CMathReaction > & getReactions();

  /**
   * Retrieve the reactions
   * @return const CVectorCore< CMathReaction > & reactions
   */
  const CVectorCore< CMathReaction > & getReactions() const;

  /**
   * Retrieve the stoichiometry matrix
   * @param const bool & reduced (default: false)
   * @return const CMatrix< C_FLOAT64 > & stoichiometry
   */
  const CMatrix< C_FLOAT64 > & getStoichiometry(const bool & reduced = false) const;

  /**
   * Retrieve the events
   * @return const CVector< CMathEventN > & events
   */
  const CVectorCore< CMathEvent > & getEvents() const;

  /**
   * Retrieve the initial dependencies
   * @return CMathDependencyGraph & getTransientDependencies
   */
  const CMathDependencyGraph & getInitialDependencies() const;

  /**
   * Retrieve the transient dependencies
   * @return CMathDependencyGraph & getTransientDependencies
   */
  const CMathDependencyGraph & getTransientDependencies() const;

  /**
   * Retrieve the objects which represent the initial state.
   * @return CObjectInterface::ObjectSet & stateObjects
   */
  const CObjectInterface::ObjectSet & getInitialStateObjects() const;

  /**
   * Retrieve the objects which represent the state or reduced state.
   * @param const bool & reduced (default: false)
   * @return CObjectInterface::ObjectSet & stateObjects
   */
  const CObjectInterface::ObjectSet & getStateObjects(const bool & reduced = false) const;

  /**
   * Retrieve the objects which are up to date after a call to updateSimulatedValues.
   * @return CObjectInterface::ObjectSet & imulationUpToDateObjects
   */
  const CObjectInterface::ObjectSet & getSimulationUpToDateObjects() const;

  /**
   * Retrieve the sequence for synchronizing all transient values for the given framework.
   * @param const CModelParameter::Framework & framework
   * @return CObjectInterface::UpdateSequence & synchronizeInitialValuesSequence
   */
  const CObjectInterface::UpdateSequence & getSynchronizeInitialValuesSequence(const CModelParameter::Framework & framework) const;

  /**
   * Retrieve the sequence for applying the initial values to the transient values.
   * @return CObjectInterface::UpdateSequence & applyInitialValuesSequence
   */
  const CObjectInterface::UpdateSequence & getApplyInitialValuesSequence() const;

  /**
   * Retrieve the sequence for calculating all values needed for the simulation.
   * @param const bool & useMoieties
   * @return CObjectInterface::UpdateSequence & synchronizeInitialValuesSequence
   */
  const CObjectInterface::UpdateSequence & getSimulationValuesSequence(const bool & useMoieties) const;

  /**
   * Retrieve the sequence for updating all transient values.
   * @return CObjectInterface::UpdateSequence & transientDataValueSequence
   */
  const CObjectInterface::UpdateSequence & getTransientDataValueSequence() const;

  /**
   * Copy a node and all its children. Nodes are converted to suite the math container,
   * i.e., objects nodes point to math object or numbers, function calls are expanded
   * and discrete nodes are replaced by object node pointing to newly created math objects,
   * which are and targets of automatically generated events.
   * @param const CEvaluationNode * pSrc
   * @param const bool & replaceDiscontinuousNodes
   * @return CEvaluationNode * pCopy
   */
  CEvaluationNode * copyBranch(const CEvaluationNode * pSrc,
                               const bool & replaceDiscontinuousNodes);

  /**
   * Copy a node and all its children. Nodes are converted to suite the math container,
   * i.e., objects nodes point to math object or numbers, function calls are expanded
   * and discrete nodes are replaced by object node pointing to newly created math objects,
   * which are and targets of automatically generated events.
   * @param const CEvaluationNode * pSrc
   * @param const CMath::Variables & variables
   * @param const bool & replaceDiscontinuousNodes
   * @return CEvaluationNode * pCopy
   */
  CEvaluationNode * copyBranch(const CEvaluationNode * pSrc,
                               const CMath::Variables< CEvaluationNode * > & variables,
                               const bool & replaceDiscontinuousNodes);

  /**
   * Replace a discontinuous node by an object node pointing to newly created math objects,
   * which are targets of automatically generated events.
   * @param const CEvaluationNode * pSrc
   * @param const std::vector< CEvaluationNode * > & children
   * @return CEvaluationNode * pCopy
   */
  CEvaluationNode * replaceDiscontinuousNode(const CEvaluationNode * pSrc,
      const std::vector< CEvaluationNode * > & children);

  /**
   * Retrieve the pointer to the corresponding initial value
   * @param const C_FLOAT64 * pValue
   * @return C_FLOAT64 * pInitialvalue
   */
  C_FLOAT64 * getInitialValuePointer(const C_FLOAT64 * pValue) const;

  /**
   * Add an entity to the container
   * const const CMath::Entity< CCopasiObject > & dataOjects
   * const const CMath::SimulationType & simulationType
   * const const std::string & infix
   * @return CMath::Entity< CMathObject > mathObjects
   */
  CMath::Entity< CMathObject > addAnalysisObject(const CMath::Entity< CCopasiObject > & dataOjects,
      const CMath::SimulationType & simulationType,
      const std::string & infix);

  /**
   * Remove the event from the container
   * @param CMath::Entity< CMathObject > & mathObjects
   * @return bool success
   */
  bool removeAnalysisObject(CMath::Entity< CMathObject > & mathObjects);

  /**
   * Add an event to the container
   * @param const CEvent & dataEvent
   * @return const CMathEvent * pMathEvent
   */
  CMathEvent * addAnalysisEvent(const CEvent & dataEvent);

  /**
   * Remove the event from the container
   * @param CMathEvent *& pMathEvent
   * @return bool success
   */
  bool removeAnalysisEvent(CMathEvent *& pMathEvent);

  /**
   * Retrieve the random number generator.
   */
  CRandom & getRandomGenerator() const;

  /**
   * Compile the mathematical model
   */
  void compile();

  /**
   * Register and update sequence.
   * @param CMathUpdateSequence * pUpdateSequence
   */
  void registerUpdateSequence(CMathUpdateSequence * pUpdateSequence);

  /**
   * Deregister and update sequence.
   * @param CMathUpdateSequence * pUpdateSeqeunce
   */
  void deregisterUpdateSequence(CMathUpdateSequence * pUpdateSequence);

private:
  /**
   * Allocate the memory for objects and values
   */
  void allocate();

  /**
   * Create relocation information
   * @param const sSize & size
   * @param std::vector< CMath::sRelocate > & Relocations
   */
  void createRelocations(const sSize & size, std::vector< CMath::sRelocate > & Relocations);

  /**
   * Resize the container
   * @param CMathContainer::sSize & size
   * @return std::vector< CMath::sRelocate > relocations
   */
  std::vector< CMath::sRelocate > resize(sSize & size);

  /**
   * Complete resize and release temporary objects
   */
  void finishResize();

  /**
   * Relocate the objects.
   * This works only if you relocate objects down in the existing location or out of space.
   * @param const sSize & size
   * @param const std::vector< CMath::sRelocate > & Relocations
   */
  void relocate(const sSize & size,
                const std::vector< CMath::sRelocate > & Relocations);

  /**
   * Initialize the pointers
   * @param sPointers & pointers
   */
  void initializePointers(CMath::sPointers & pointers);

#ifdef COPASI_DEBUG
  /**
   * Print pointer state
   * @param sPointers & pointers
   */
  void printPointers(CMath::sPointers & pointers);
#endif // COAPSI_DEBUG

  /**
   * Initialize the pointers used for the conversion of
   * discontinuous nodes.
   */
  void initializeDiscontinuousCreationPointer();

  /**
   * Initialize the objects
   * @param sPointers & pointers
   */
  void initializeObjects(CMath::sPointers & pointers);

  /**
   * Initialize the events
   * @param sPointers & pointers
   */
  void initializeEvents(CMath::sPointers & pointers);

  /**
   * Compile the objects
   */
  bool compileObjects();

  /**
   * Compile the events
   */
  bool compileEvents();

  /**
   * Convert nodes which generate discrete changes into events
   * and compiles them.
   */
  bool compileDiscreteChanges();

  /**
   * Create a node based on the given pointer to the math object
   * @param const CObjectInterface * pMathObject
   * @return CEvaluationNode * pNode
   */
  CEvaluationNode * createNodeFromObject(const CObjectInterface * pMathObject);

  /**
   * Create a node based on the given pointer to a data value
   * @param const C_FLOAT64 * pDataValue
   * @return CEvaluationNode * pNode
   */
  CEvaluationNode * createNodeFromValue(const C_FLOAT64 * pDataValue);

  /**
   * Create Dependency Graphs
   */
  void createDependencyGraphs();

  /**
   * Create Update Sequences
   */
  void createUpdateSequences();

  /**
   * Analyze the number and type of roots, i.e., which roots are only changed during discrete event processing.
   */
  void analyzeRoots();

  /**
   * Calculate the partial derivative of the root values with respect to the
   * continuous state variables
   * @param CMatrix< C_FLOAT64 > & jacobian
   */
  void calculateRootJacobian(CMatrix< C_FLOAT64 > & jacobian);

  /**
   * Create the update sequences needed to synchronize the initial values
   */
  void createSynchronizeInitialValuesSequence();

  /**
   * Create the update sequence used when applying the initial state
   */
  void createApplyInitialValuesSequence();

  /**
   * Create the update sequences used to calculate all values required for simulation
   */
  void createUpdateSimulationValuesSequence();

  /**
   * Create the update sequences used to calculate all transient data values
   */
  void createUpdateAllTransientDataValuesSequence();

  /**
   * Determine the entity type of an entity
   * @param const CModelEntity * pEntity
   * @return CMath::EntityType entityType
   */
  static CMath::EntityType getEntityType(const CModelEntity * pEntity);

  /**
   * Initialize several mathematical objects of a common simulation type and
   * advance relevant pointers
   * @param const std::vector<const CModelEntity*> & entities
   * @param const CMath::SimulationType & simulationType
   * @param sPointers & pointers
   */
  void initializeMathObjects(const std::vector<const CModelEntity*> & entities,
                             const CMath::SimulationType & simulationType,
                             CMath::sPointers & pointers);

  /**
   * Initialize several mathematical objects for local reaction parameters and
   * advance relevant pointers
   * @param const std::vector<const CCopasiObject *> & parameters
   * @param CMathContainer::sPointers & p
   */
  void initializeMathObjects(const std::vector<const CCopasiObject *> & parameters,
                             CMath::sPointers & p);

  /**
   * Initialize several mathematical objects for local reaction parameters and
   * advance relevant pointers
   * @param const CCopasiVector< CReaction > & reactions
   * @param CMathContainer::sPointers & p
   */
  void initializeMathObjects(const CCopasiVector< CReaction > & reactions,
                             CMath::sPointers & p);

  /**
   * Initialize several mathematical objects for local reaction parameters and
   * advance relevant pointers
   * @param const CCopasiVector< CMoiety > & moieties
   * @param CMathContainer::sPointers & p
   */
  void initializeMathObjects(const CCopasiVector< CMoiety > & moieties,
                             CMath::sPointers & p);

  /**
   * Determine whether on object has calculation dependencies.
   */
  static bool hasDependencies(const CCopasiObject * pObject);

  /**
   * Map the data object to the math object
   * @param CCopasiObject * pDataObject
   * @param CMathObject * pMathObject
   */
  void map(const CCopasiObject * pDataObject, CMathObject * pMathObject);

  /**
   * Create an event of type CEvent::Discontinuity for each discontinuity in the model
   */
  void createDiscontinuityEvents();

  /**
   * Create an event of type CEvent::Discontinuity for each discontinuity the tree with root pNode
   * @param const CEvaluationTree * pTree
   */
  void createDiscontinuityEvents(const CEvaluationTree * pTree);

  /**
   * Create an event of type CEvent::Discontinuity for the given node
   * @param const CEvaluationNode * pNode
   */
  void createDiscontinuityDataEvent(const CEvaluationNode * pNode);

  /**
   * Create the infix for trigger of the event which tracks changes in a discontinuity
   * represented by the node.
   * @param const CEvaluationNode * pNode
   */
  std::string createDiscontinuityTriggerInfix(const CEvaluationNode * pNode);

  /**
   * Create all delays
   */
  void createDelays();

  /**
   * Calculate the Jacobian for the roots.
   * @param CMatrix< C_FLOAT64 > & jacobian
   * @param const CVector< C_FLOAT64 > & rates
   */
  void calculateRootJacobian(CMatrix< C_FLOAT64 > & jacobian,
                             const CVector< C_FLOAT64 > & rates);

  // Attributes

  /**
   * A pointer to the data model which mathematics are contained
   */
  CModel * mpModel;
  C_FLOAT64 mAvogadroValue;
  CMathObject mAvogadroObject;
  C_FLOAT64 mQuantity2NumberFactorValue;
  CMathObject mQuantity2NumberFactorObject;

  CMathEventQueue * mpProcessQueue;
  CRandom * mpRandomGenerator;

  CVectorCore< C_FLOAT64 > mValues;
  CVectorCore< C_FLOAT64 > mOldValues;
  C_FLOAT64 * mpValuesBuffer;

  CVectorCore< C_FLOAT64 > mInitialExtensiveValues;
  CVectorCore< C_FLOAT64 > mInitialIntensiveValues;
  CVectorCore< C_FLOAT64 > mInitialExtensiveRates;
  CVectorCore< C_FLOAT64 > mInitialIntensiveRates;
  CVectorCore< C_FLOAT64 > mInitialParticleFluxes;
  CVectorCore< C_FLOAT64 > mInitialFluxes;
  CVectorCore< C_FLOAT64 > mInitialTotalMasses;
  CVectorCore< C_FLOAT64 > mInitialEventTriggers;

  CVectorCore< C_FLOAT64 > mExtensiveValues;
  CVectorCore< C_FLOAT64 > mIntensiveValues;
  CVectorCore< C_FLOAT64 > mExtensiveRates;
  CVectorCore< C_FLOAT64 > mIntensiveRates;
  CVectorCore< C_FLOAT64 > mParticleFluxes;
  CVectorCore< C_FLOAT64 > mFluxes;
  CVectorCore< C_FLOAT64 > mTotalMasses;
  CVectorCore< C_FLOAT64 > mEventTriggers;

  CVectorCore< C_FLOAT64 > mEventDelays;
  CVectorCore< C_FLOAT64 > mEventPriorities;
  CVectorCore< C_FLOAT64 > mEventAssignments;
  CVectorCore< C_FLOAT64 > mEventRoots;
  CVectorCore< C_FLOAT64 > mEventRootStates;
  CVectorCore< C_FLOAT64 > mPropensities;
  CVectorCore< C_FLOAT64 > mDependentMasses;
  CVectorCore< C_FLOAT64 > mDiscontinuous;
  CVectorCore< C_FLOAT64 > mDelayValues;
  CVectorCore< C_FLOAT64 > mDelayLags;
  CVectorCore< C_FLOAT64 > mTransitionTimes;

  /**
   * The initial state contains also all fixed values
   */
  CVectorCore< C_FLOAT64 > mInitialState;

  /**
   * The initial state contains additionally all computed internal values
   */
  CVectorCore< C_FLOAT64 > mCompleteInitialState;

  /**
   * The state contains values of type EventTarget, Time, ODE, Independent, and Dependent
   */
  CVectorCore< C_FLOAT64 > mState;

  /**
   * The reduced state contains values of type EventTarget, Time, ODE, Independent
   */
  CVectorCore< C_FLOAT64 > mStateReduced;

  /**
   * The full history needed for the calculation of delayed differential equations
   */
  CMathHistory mHistory;

  /**
   * The reduced history needed for the calculation of delayed differential equations
   */
  CMathHistoryCore mHistoryReduced;

  /**
   * The rate contains derivatives for values of type EventTarget, Time, ODE, Independent, and Dependent
   */
  CVectorCore< C_FLOAT64 > mRate;

  /**
   * The reduced rate derivatives for contains values of type EventTarget, Time, ODE, Independent
   */
  CVectorCore< C_FLOAT64 > mRateReduced;

  /**
   * Dependency graph for initial value calculations
   */
  CMathDependencyGraph mInitialDependencies;

  /**
   * Dependency graph for transient value calculations
   */
  CMathDependencyGraph mTransientDependencies;

  /**
   * The sequence of updates needed to synchronize the initial values based
   * on extensive values, i.e., species amounts
   */
  CObjectInterface::UpdateSequence mSynchronizeInitialValuesSequenceExtensive;

  /**
   * The sequence of updates needed to synchronize the initial values based
   * on intensive values, i.e., species concentrations.
   */
  CObjectInterface::UpdateSequence mSynchronizeInitialValuesSequenceIntensive;

  /**
   * The sequence of updates needed to apply the initial values
   */
  CObjectInterface::UpdateSequence mApplyInitialValuesSequence;

  /**
   * The sequence of updates needed to calculate all simulation required values based
   * on the assumption that all state values may have changed
   */
  CObjectInterface::UpdateSequence mSimulationValuesSequence;

  /**
   * The sequence of updates needed to calculate all simulation required values based
   * on the assumption that all state values may have changed
   */
  CObjectInterface::UpdateSequence mSimulationValuesSequenceReduced;

  /**
   * The sequence of updates needed to calculate all priorities
   * on the assumption that all state values may have changed
   */
  CObjectInterface::UpdateSequence mPrioritySequence;

  /**
   * The sequence of updates needed to calculate all objects which have data object associated
   * on the assumption that all state values may have changed
   */
  CObjectInterface::UpdateSequence mTransientDataObjectSequence;

  /**
   * The set of objects which determine the initial state of the model based on extensive
   * values
   */
  CObjectInterface::ObjectSet mInitialStateValueExtensive;

  /**
   * The set of objects which determine the initial state of the model based on intensive
   * values
   */
  CObjectInterface::ObjectSet mInitialStateValueIntensive;

  /**
   * All initial state values (intensive and extensive)
   */
  CObjectInterface::ObjectSet mInitialStateValueAll;

  /**
   * The set of objects which determine the transient state of the model
   */
  CObjectInterface::ObjectSet mStateValues;

  /**
   * The set of objects which determine the transient state of the reduced model
   */
  CObjectInterface::ObjectSet mReducedStateValues;

  /**
   * The objects which are required to be up to date for simulation of the full model,
   * i.e., the right hand side of ODEs, rates of species determined by reaction,
   * and event roots.
   */
  CObjectInterface::ObjectSet mSimulationRequiredValues;

  /**
   * A vector containing all math objects.
   */
  CVectorCore< CMathObject > mObjects;
  CVectorCore< CMathObject > mOldObjects;
  CMathObject * mpObjectsBuffer;

  /**
   * A vector containing all math events.
   */
  CVectorCore< CMathEvent > mEvents;

  /**
   * A vector containing all math reactions.
   */
  CVectorCore< CMathReaction > mReactions;

  /**
   * A vector of Boolean values indicating whether a root is changing
   * continuously or only during discrete event processing.
   */
  CVector< bool > mRootIsDiscrete;

  /**
   * A vector of Boolean values indicating whether a root is non time
   * dependent.
   */
  CVector< bool > mRootIsTimeDependent;

  /**
   * A vector of pointers to all objects values CMathEventN::CTrigger::CRootProcessor
   */
  CVector< CMathEvent::CTrigger::CRootProcessor * > mRootProcessors;

  /**
   * Structure of pointers used for creating discontinuities.
   */
  sDiscontinuous mCreateDiscontinuousPointer;

  /**
   * A map from data objects to math objects
   */
  std::map< const CCopasiObject *, CMathObject * > mDataObject2MathObject;

  /**
   * A map from data objects values to math objects
   */
  std::map< C_FLOAT64 *, CMathObject * > mDataValue2MathObject;

  /**
   * A map from data objects values to math objects
   */
  std::map< C_FLOAT64 *, CCopasiObject * > mDataValue2DataObject;

  /**
   * A vector of data events for discontinuities
   */
  CCopasiVector< CEvent > mDiscontinuityEvents;

  /**
   * A map from the infix of the expression of a discontinuity to the object
   * representing it.
   */
  std::map< std::string, CMathObject * > mDiscontinuityInfix2Object;

  /**
   * A map from the discontinuity trigger infix of to event
   * representing it.
   */
  std::map< std::string,  CMathEvent * > mTriggerInfix2Event;

  /**
   * A map of root counts to math events.
   */
  std::multimap< size_t, size_t > mRootCount2Events;

  /**
   * A vector of delays
   */
  CVectorCore< CMathDelay > mDelays;

  /**
   * A flag indicating whether the model is autonomous.
   */
  bool mIsAutonomous;

  /**
   * Structure containing all the important size information
   */
  sSize mSize;

  /**
   * Pointers to all update sequences associated with this container;
   */
  std::set< CMathUpdateSequence * > mUpdateSequences;
};

#endif // COPASI_CMathContainer
