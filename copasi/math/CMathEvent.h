// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathEvent.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/21 14:12:02 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CMathEvent
#define COPASI_CMathEvent

#include "copasi/math/CMathTrigger.h"

#include "copasi/function/CExpression.h"
#include "copasi/utilities/CVector.h"

class CProcessQueue;
class CMathContainer;
class CMathObject;
class CEvent;
class CEventAssignment;

class CMathEventN
{
public:
  class CAssignment
  {
  public:
    /**
     * Default constructor
     */
    CAssignment();

    /**
     * Destructor
     */
    ~CAssignment();

    void initialize(CMath::sPointers & pointers);

    bool compile(CEventAssignment * pDataAssignment,
                 CMathContainer & container);

    bool compileDiscontinuous(const CMathObject * pObject,
                              CMathContainer & container);

  private:
    CMathObject * mpTarget;
    CMathObject * mpAssignment;
  };

  class CTrigger
  {
  public:
    class CRoot
    {
    public:
      /**
       * Default constructor
       */
      CRoot();

      /**
       * Destructor
       */
      ~CRoot();

      void initialize(CMath::sPointers & pointers);

      bool compile(CEvaluationNode * pRootNode,
                   const bool & equality,
                   CMathContainer & container);

      CEvaluationNode * createTriggerExpressionNode() const;

    private:
      CMathObject * mpRoot;
      CMathObject * mpRootState;
      bool mEquality;
      bool mDiscrete;
    };

    /**
     * Default constructor
     */
    CTrigger();

    /**
     * Destructor
     */
    ~CTrigger();

    void allocate(const CEvent * pDataEvent,
                  const CMathContainer & container);

    void allocateDiscontinuous(const size_t & nRoots,
                               const CMathContainer & container);

    void initialize(CMath::sPointers & pointers);

    bool compile(CEvent * pDataEvent,
                 CMathContainer & container);

    bool compileDiscontinuous(const CMathObject * pObject,
                              CMathContainer & container);

    const CVector< CRoot > & getRoots() const;

  private:
    static size_t countRoots(const CEvaluationNode * pNode,
                             const CMath::Variables< size_t > & variables);

    static size_t countRootsDefault(const std::vector< size_t > & children);

    static size_t countRootsEQ(const CEvaluationNode * pNode,
                               const std::vector< size_t > & children);

    static size_t countRootsFUNCTION(const CEvaluationNode * pNode,
                                     const std::vector< size_t > & children);

    static size_t countRootsVARIABLE(const CEvaluationNode * pNode,
                                     const CMath::Variables< size_t > & variables);

    static CEvaluationNode * compile(const CEvaluationNode * pNode,
                                     const CMath::Variables< CEvaluationNode * > & variables,
                                     CMathEventN::CTrigger::CRoot *& pRoot,
                                     CMathContainer & container);

    static CEvaluationNode * compileAND(const CEvaluationNode * pNode,
                                        const std::vector< CEvaluationNode * > & children,
                                        const CMath::Variables< CEvaluationNode * > & variables,
                                        CMathEventN::CTrigger::CRoot *& pRoot,
                                        CMathContainer & container);

    static CEvaluationNode * compileEQ(const CEvaluationNode * pNode,
                                       const std::vector< CEvaluationNode * > & children,
                                       const CMath::Variables< CEvaluationNode * > & variables,
                                       CMathEventN::CTrigger::CRoot *& pRoot,
                                       CMathContainer & container);

    static CEvaluationNode * compileNE(const CEvaluationNode * pNode,
                                       const std::vector< CEvaluationNode * > & children,
                                       const CMath::Variables< CEvaluationNode * > & variables,
                                       CMathEventN::CTrigger::CRoot *& pRoot,
                                       CMathContainer & container);

    static CEvaluationNode * compileLE(const CEvaluationNode * pNode,
                                       const std::vector< CEvaluationNode * > & children,
                                       const CMath::Variables< CEvaluationNode * > & variables,
                                       CMathEventN::CTrigger::CRoot *& pRoot,
                                       CMathContainer & container);

    static CEvaluationNode * compileNOT(const CEvaluationNode * pNode,
                                        const std::vector< CEvaluationNode * > & children,
                                        const CMath::Variables< CEvaluationNode * > & variables,
                                        CMathEventN::CTrigger::CRoot *& pRoot,
                                        CMathContainer & container);

    static CEvaluationNode * compileFUNCTION(const CEvaluationNode * pNode,
        const std::vector< CEvaluationNode * > & children,
        const CMath::Variables< CEvaluationNode * > & variables,
        CMathEventN::CTrigger::CRoot *& pRoot,
        CMathContainer & container);

    static CEvaluationNode * compileVARIABLE(const CEvaluationNode * pNode,
        const std::vector< CEvaluationNode * > & children,
        const CMath::Variables< CEvaluationNode * > & variables,
        CMathEventN::CTrigger::CRoot *& pRoot,
        CMathContainer & container);

    CMathObject * mpTrigger;
    CMathObject * mpInitialTrigger;
    CVector< CRoot > mRoots;
    bool mDualAction;
  };

  /**
   * Default constructor
   */
  CMathEventN();

  /**
   * Destructor
   */
  ~CMathEventN();

  static void allocate(CMathEventN * pEvent,
                       const CEvent * pDataEvent,
                       const CMathContainer & container);

  static void allocateDiscontinuous(CMathEventN * pEvent,
                                    const size_t & nRoots,
                                    const CMathContainer & container);

  void initialize(CMath::sPointers & pointers);

  bool compile(CEvent * pDataEvent,
               CMathContainer & container);

  bool compileDiscontinuous(const CMathObject * pObject,
                            CMathContainer & container);

  const CTrigger & getTrigger() const;

  const CVector< CAssignment > & getAssignments() const;

private:
  CTrigger mTrigger;
  CVector< CAssignment > mAssignments;
  CMathObject * mpDelay;
  CMathObject * mpPriority;
  bool mFireAtInitialTime;
  bool mPersistentTrigger;
  bool mDelayAssignment;
};

class CMathEvent : public CCopasiContainer
{
private:
  class CAssignment : public CCopasiContainer
  {
    friend class CMathEvent;

    // Operations
  public:
    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CAssignment(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CAssignment &" src
     * @param "const CCopasiContainer * pParent (default: NULL)
     */
    CAssignment(const CAssignment & src,
                const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    ~CAssignment();

    /**
     * Compile the root finder
     * @param const CEventAssignment * pEvent
     * @param std::vector< CCopasiContainer * > listOfContainer
     */
    bool compile(const CEventAssignment * pAssignment,
                 std::vector< CCopasiContainer * > listOfContainer);

    // Attributes
  private:
    /**
     * Pointer to the value to be modified by the assignment
     */
    C_FLOAT64 * mpTarget;

    /**
     * Expression to calculate the new value.
     */
    CExpression mExpression;
  };

  // Operations
public:
  /**
   * Default constructor
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CMathEvent(const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param "const CMathEvent &" src
   * @param "const CCopasiContainer * pParent (default: NULL)
   */
  CMathEvent(const CMathEvent & src,
             const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  ~CMathEvent();

  /**
   * Compile the root finder
   * @param const CEvent * pEvent
   * @param std::vector< CCopasiContainer * > listOfContainer
   */
  bool compile(const CEvent * pEvent,
               std::vector< CCopasiContainer * > listOfContainer);

  /**
   * The event fires and the approriate actions are scheduled
   * in the process queue.
   * @param const C_FLOAT64 & time
   * @param const bool & equality
   * @param CProcessQueue & processQueue
   */
  void fire(const C_FLOAT64 & time,
            const bool & equality,
            CProcessQueue & processQueue);

  /**
   * Apply all needed refreshes so that the delay expression are
   * correctly calculated.
   */
  void applyDelayRefreshes();

  /**
   * Apply all needed refreshes so that the assignment expressions are
   * correctly calculated.
   */
  void applyValueRefreshes();

  /**
   * Apply all needed refreshes to update all values depending on the
   * assignment targets.
   */
  void applyDependentRefreshes();

  /**
   * Retrieve the trigger for this event.
   * @return CMathTrigger & mathTrigger
   */
  CMathTrigger & getMathTrigger();

  /**
   * Retrieve the order in which this event shall be processed
   * @return const size_t & order
   */
  const size_t & getOrder() const;

  /**
   * Retrieve the time for calculating the assignment expression
   * @param const C_FLOAT64 & currentTime
   * @return C_FLOAT64 calculationTime
   */
  C_FLOAT64 getCalculationTime(const C_FLOAT64 & currentTime);

  /**
   * Retrieve the time for executing the assignmentS
   * @param const C_FLOAT64 & currentTime
   * @return C_FLOAT64 executionTime
   */
  C_FLOAT64 getAssignmentTime(const C_FLOAT64 & currentTime);
  
  bool isCutPlane() const;

private:
  /**
   * Calculate the time for delays. This accounts for small errors relative
   * to the current time.
   * @param const C_FLOAT64 & currentTime
   * @return C_FLOAT64 delayedTime
   */
  C_FLOAT64 calculateDelayedTime(const C_FLOAT64 & currentTime);

  // Attributes
private:
  /**
   * Trigger expression.
   */
  CMathTrigger mTrigger;

  /**
   * The order in which the event is processed in case of simultaneous
   * assignments
   */
  size_t mOrder;

  /**
   * Boolean value indicating whether the event involves a delay.
   */
  bool mHaveDelay;

  /**
   * Delay expression.
   */
  CExpression mDelay;

  /**
   * Boolean value indicating whether the calculation or the assignment is delayed.
   */
  bool mDelayAssignment;

  /**
   * List of assignments
   */
  CCopasiVector< CAssignment > mAssignments;

  /**
   * A sequence of refresh calls needed to prepare
   * to calculate the delay value.
   */
  std::vector< Refresh * > mDelayValueRefreshes;

  /**
   * A sequence of refresh calls needed to prepare
   * to calculate the current values of the assignments.
   */
  std::vector< Refresh * > mAssignmentValueRefreshes;

  /**
   * A sequence of refresh calls needed to calculate all
   * values which depend on the target values of the assignments.
   */
  std::vector< Refresh * > mDependentValueRefreshes;
  
  /**
   * indicates whether this is a special event used in nonlinear dynamics
   * analysis
   */
  bool mIsCutPlane;
};

#endif // COPASI_CMathEvent
