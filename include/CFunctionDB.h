/**
 * CFunctionDB
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */


#ifndef COPASI_CFunctionDB
#define COPASI_CFunctionDB

#include <string>

#include "CKinFunction.h"

class CFunctionDB
{
// Attributes
private:
    /**
     *  Filename which contains the function database
     */
    string mFilename;

    /**
     *  Builtin Functions
     */
    vector < CBaseFunction * > mBuiltinFunctions;

    /**
     *  Vector of the currently loaded functions
     */
    CCopasiVectorP < CBaseFunction * > mLoadedFunctions;
// Operations
public:
    /**
     *
     */
    CFunctionDB();

    /**
     *
     */
    void Init();

    /**
     *
     */
    ~CFunctionDB();

    /**
     *
     */
    void Delete();

    /**
     *
     */
    void SetFilename(const string & filename);
    
    /**
     *
     */
    string GetFilename();
    
    /**
     *  Load the function functionName from the database
     *  @param "const string" &functionName
     *  @return CKinFunction &
     */
    CBaseFunction & DBLoad(const string & functionName);

    /**
     *  Add the function to the database
     *  @param CKinFunction &function
     *  @return C_INT32 Fail
     */
    void Add(CKinFunction & function);

    /**
     *  Delete the function functionName from the database
     *  @param "const string" &functionName
     *  @return C_INT32 Fail
     */
    void DBDelete(const string & functionName);

    /**
     *  Search for a function among the loaded functions. If no
     *  function is found the database is searched and the apropriate 
     *  function is loaded.
     *  @param "const string" &functionName
     *  @return CKinFunction &
     */
    CBaseFunction & FindFunction(const string & functionName);

    /**
     *  Retrieves the vector of loades functions.
     *  @return "CCopasiVector < CKinFunction > &" LoadedFunctions
     */
    CCopasiVectorP < CBaseFunction * > & LoadedFunctions();
};

#endif // COPASI_CFunctionDB
