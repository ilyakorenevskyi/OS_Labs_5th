public class sProcess {
  public int arrivaltime;
  public int cputime;
  public int ioblocking;
  public int cpudone;
  public int ionext;
  public int numblocked;
  public int priority;
  public sProcess (int cputime,int arrivaltime, int ioblocking, int cpudone, int ionext, int numblocked, int priority) {
    this.cputime = cputime;
    this.ioblocking = ioblocking;
    this.cpudone = cpudone;
    this.ionext = ionext;
    this.numblocked = numblocked;
    this.arrivaltime = arrivaltime;
    this.priority = priority;
  }

}
