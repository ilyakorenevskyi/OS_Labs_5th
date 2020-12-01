// Run() is called from Scheduling.main() and is where
// the scheduling algorithm written by the user resides.
// User modification should occur within the Run() function.

import java.util.Vector;
import java.io.*;

public class SchedulingAlgorithm {

  public static Results Run(int runtime, Vector processVector, Vector toArriveVector, Results result) {
    int comptime = 0;
    int currentProcess = 0;
    int previousProcess = 0;
    int size = processVector.size();
    int arrivalSize = toArriveVector.size();
    int completed = 0;
    String resultsFile = "Summary-Processes";
    result.schedulingType = "Batch (Nonpreemptive)";
    result.schedulingName = "Shortest remaining time";

    try {
      //BufferedWriter out = new BufferedWriter(new FileWriter(resultsFile));
      //OutputStream out = new FileOutputStream(resultsFile);
      PrintStream out = new PrintStream(new FileOutputStream(resultsFile));
      currentProcess = getShortestRemainingTime(processVector, -1);
      sProcess process = (sProcess) processVector.elementAt(currentProcess);
      out.println("Process: " + currentProcess + " registered... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
      while (comptime < runtime) {
        if (process.cpudone == process.cputime) {
          completed++;
          out.println("Process: " + currentProcess + " completed... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
          if (completed == size && arrivalSize==0) {
            result.compuTime = comptime;
            out.close();
            return result;
          }
          currentProcess = getShortestRemainingTime(processVector,currentProcess);
          process = (sProcess) processVector.elementAt(currentProcess);
          out.println("Process: " + currentProcess + " registered... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
        }

        if (process.ioblocking == process.ionext) {
          out.println("Process: " + currentProcess + " I/O blocked... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
          process.numblocked++;
          process.ionext = 0;
          currentProcess = getShortestRemainingTime(processVector, currentProcess);
          process = (sProcess) processVector.elementAt(currentProcess);
          out.println("Process: " + currentProcess + " registered... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
        }


        previousProcess = currentProcess;
        for(int i = 0; i<arrivalSize; i++){
          sProcess toArriveProcess = (sProcess) toArriveVector.elementAt(i);
          if(toArriveProcess.arrivaltime == comptime){
            processVector.add(toArriveProcess);
            toArriveVector.remove(i);
            i--;
            arrivalSize--;
            out.println("Process: " + size + " arrived... (" + toArriveProcess.cputime + " " + toArriveProcess.ioblocking + " " +toArriveProcess.cpudone + " " + toArriveProcess.cpudone + ")");
            if(toArriveProcess.cputime < (process.cputime-process.cpudone)) {
              out.println("Process: " + previousProcess + " stoped... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
              process = toArriveProcess;
              currentProcess = size;
            }
            size++;
          }
        }
        if(previousProcess != currentProcess ){
          out.println("Process: " + currentProcess + " registered... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
        }


        process.cpudone++;
        if (process.ioblocking > 0) {
          process.ionext++;
        }
        comptime++;
      }
      out.close();
    } catch (IOException e) { /* Handle exceptions */ }
    result.compuTime = comptime;
    return result;
  }

  private static int getShortestRemainingTime(Vector processVector, int previousProcess){    //Returns number of the process with the shortest remaining time
    int remainingTimeMin = 0;
    int minProcess = -1;
    for (int i = 0; i < processVector.size(); i++) {
      sProcess process = (sProcess) processVector.elementAt(i);
      int currRemainingTime = (process.cputime - process.cpudone);
      if((currRemainingTime!=0) && i!= previousProcess && (currRemainingTime < remainingTimeMin || remainingTimeMin == 0)){
          remainingTimeMin = currRemainingTime;
          minProcess = i;
      }
    }
    if(minProcess == -1) return previousProcess;
    else return minProcess;
  }

}
