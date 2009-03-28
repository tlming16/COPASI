// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/examples/example5.java,v $ 
//   $Revision: 1.1.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2009/03/28 22:52:07 $ 
// End CVS Header 
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

/**
 * This is an example on how to run an optimization task.
 * And how to access the result of an optimization.
 */


import org.COPASI.*;

public class example5 
{

   public static void main(String[] args) 
   {
     try
     {
       CCopasiDataModel.getGlobal().newModel();
     }
     catch(Exception e)
     {
        System.err.println("Error. Could not create model.");
        System.exit(1);
     }
     CModel model=CCopasiDataModel.getGlobal().getModel();
     assert model != null;
     model.setVolumeUnit(CModel.fl);
     model.setTimeUnit(CModel.s);
     model.setQuantityUnit(CModel.fMol);
     CModelValue fixedModelValue=model.createModelValue("F");
     assert fixedModelValue != null;
     fixedModelValue.setStatus(CModelEntity.FIXED);
     fixedModelValue.setInitialValue(3.0);   
     CModelValue variableModelValue=model.createModelValue("V");
     assert variableModelValue != null;
     variableModelValue.setStatus(CModelEntity.ASSIGNMENT);
     // we create a very simple assignment that is easy on the optimization
     // a parabole with the minimum at x=6 should do just fine
     String s=fixedModelValue.getObject(new CCopasiObjectName("Reference=Value")).getCN().getString();
     s="(<"+s+"> - 6.0)^2";
     variableModelValue.setExpression(s);
     // now we compile the model and tell COPASI which values have changed so
     // that COPASI can update the values that depend on those
     model.compileIfNecessary();
     ObjectStdVector changedObjects=new ObjectStdVector();
     changedObjects.add(fixedModelValue.getObject(new CCopasiObjectName("Reference=InitialValue")));
     changedObjects.add(variableModelValue.getObject(new CCopasiObjectName("Reference=InitialValue")));
     model.updateInitialValues(changedObjects);
     
     // now we set up the optimization

     // we want to do an optimization for the time course
     // so we have to set up the time course task first
     CTrajectoryTask timeCourseTask = (CTrajectoryTask)CCopasiDataModel.getGlobal().getTask("Time-Course");
     assert timeCourseTask != null;
     // since for this example it really doesn't matter how long we run the time course 
     // we run for 1 second and calculate 10 steps
     // run a deterministic time course
     timeCourseTask.setMethodType(CCopasiMethod.deterministic);

     // pass a pointer of the model to the problem
     timeCourseTask.getProblem().setModel(CCopasiDataModel.getGlobal().getModel());

     // get the problem for the task to set some parameters
     CTrajectoryProblem problem = (CTrajectoryProblem)timeCourseTask.getProblem();
     assert problem != null;

     // simulate 10 steps
     problem.setStepNumber(10);
     // start at time 0
     CCopasiDataModel.getGlobal().getModel().setInitialTime(0.0);
     // simulate a duration of 1 time units
     problem.setDuration(1);
     // tell the problem to actually generate time series data
     problem.setTimeSeriesRequested(true);
    
     // get the optimization task
     COptTask optTask=(COptTask)CCopasiDataModel.getGlobal().getTask("Optimization");
     assert optTask != null;
     // we want to use Levenberg-Marquardt as the optimization method
     optTask.setMethodType(CCopasiMethod.LevenbergMarquardt);
     
     // next we need to set subtask type on the problem
     COptProblem optProblem=(COptProblem)optTask.getProblem();
     assert optProblem != null;
     optProblem.setSubtaskType(CCopasiTask.timeCourse);
     
     // we create the objective function
     // we want to minimize the value of the variable model value at the end of
     // the simulation
     // the objective function is normally minimized
     String objectiveFunction=variableModelValue.getObject(new CCopasiObjectName("Reference=Value")).getCN().getString();
     // we need to put the angled brackets around the common name of the object
     objectiveFunction="<"+objectiveFunction+">";
     // now we set the objective function in the problem
     optProblem.setObjectiveFunction(objectiveFunction);

     // now we create the optimization items
     // i.e. the model elements that have to be changed during the optimization
     // in order to get to the optimal solution
     COptItem optItem=optProblem.addOptItem(new CCopasiObjectName(fixedModelValue.getObject(new CCopasiObjectName("Reference=InitialValue")).getCN()));
     // we want to change the fixed model value from -100 to +100 with a start
     // value of 50
     optItem.setStartValue(50.0);
     optItem.setLowerBound(new CCopasiObjectName("-100"));
     optItem.setUpperBound(new CCopasiObjectName("100"));
     
     // now we set some parameters on the method
     // these parameters are specific to the method type we set above
     // (in this case Levenberg-Marquardt)
     COptMethod optMethod=(COptMethod)optTask.getMethod();
     assert optMethod != null;
     
     // now we set some method parameters for the optimization method
     // iteration limit
     CCopasiParameter parameter=optMethod.getParameter("Iteration Limit");
     assert parameter != null;
     parameter.setIntValue(2000);
     // tolerance
     parameter=optMethod.getParameter("Tolerance");
     assert parameter != null;
     parameter.setDblValue(1.0e-5);

     // create a report with the correct filename and all the species against
     // time.
     CReportDefinitionVector reports = CCopasiDataModel.getGlobal().getReportDefinitionList();
     // create a new report definition object
     CReportDefinition report = reports.createReportDefinition("Report", "Output for optimization");
     // set the task type for the report definition to timecourse
     report.setTaskType(CCopasiTask.optimization);
     // we don't want a table
     report.setIsTable(false);
     // the entries in the output should be seperated by a ", "
     report.setSeparator(new CCopasiReportSeparator(", "));

     // we need a handle to the header and the body
     // the header will display the ids of the metabolites and "time" for
     // the first column
     // the body will contain the actual timecourse data
     ReportItemVector header = report.getHeaderAddr();
     ReportItemVector body = report.getBodyAddr();
     
     // in the report header we write two strings and a separator
     header.add(new CRegisteredObjectName(new CCopasiStaticString("value of objective function").getCN().getString()));
     header.add(new CRegisteredObjectName(report.getSeparator().getCN().getString()));
     header.add(new CRegisteredObjectName(new CCopasiStaticString("initial value of F").getCN().getString()));
     // in the report body we write the best value of the objective function and
     // the initial value of the fixed parameter separated by a komma
     body.add(new CRegisteredObjectName(optProblem.getObject(new CCopasiObjectName("Reference=Best Value")).getCN().getString()));
     body.add(new CRegisteredObjectName(report.getSeparator().getCN().getString()));
     body.add(new CRegisteredObjectName(fixedModelValue.getObject(new CCopasiObjectName("Reference=InitialValue")).getCN().getString()));

     
     // set the report for the task
     optTask.getReport().setReportDefinition(report);
     // set the output filename
     optTask.getReport().setTarget("example5.txt");
     // don't append output if the file exists, but overwrite the file
     optTask.getReport().setAppend(false);


     boolean result=false;
     try
     {
       result=optTask.process(true);
     }
     catch(Exception e)
     {
         System.err.println("ERROR: "+e.getMessage());
     }
     if(!result)
     {
         System.err.println("Running the optimization failed.");
     }
     // now we check if the optimization actually got the correct result
     // the best value it should have is 0 and the best parameter value for
     // that result should be 6 for the initial value of the fixed parameter
     double bestValue=optProblem.getSolutionValue();
     assert Math.abs(bestValue) < 1e-3;
     // we should only have one solution variable since we only have one
     // optimization item
     assert optProblem.getSolutionVariables().size() == 1;
     double solution=optProblem.getSolutionVariables().get(0);
     assert Math.abs((solution-6.0)/6.0) < 1e-3;
  }

}
