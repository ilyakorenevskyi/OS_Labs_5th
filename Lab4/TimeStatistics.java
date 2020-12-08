import java.util.concurrent.TimeUnit;
public class TimeStatistics {
    private int totalTime;
    private int num;
    private long start;
    private long end;
    public TimeStatistics(){
        this.totalTime = 0;
        this.num = 0;
        this.start = -1;
        this.end = -1;
    }
    public double getMedium(){
        return (totalTime/num)/1000000.;
    }
    public void startInterval(){
        start = System.nanoTime();
    }
    public void endInterval(){
        end = System.nanoTime();
        if(start!=-1){
            totalTime += end - start;
            num++;
        }
        start = -1;
        end = -1;
    }
}
