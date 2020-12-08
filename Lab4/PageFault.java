/* It is in this file, specifically the replacePage function that will
   be called by MemoryManagement when there is a page fault.  The 
   users of this program should rewrite PageFault to implement the 
   page replacement algorithm.
*/

  // This PageFault file is an example of the FIFO Page Replacement 
  // Algorithm as described in the Memory Management section.

import java.util.*;
import java.util.Comparator;

public class PageFault {

  /**
   * The page replacement algorithm for the memory management sumulator.
   * This method gets called whenever a page needs to be replaced.
   * <p>
   * The page replacement algorithm included with the simulator is 
   * WGClock
   *
   * @param mem is the vector which contains the contents of the pages 
   *   in memory being simulated.  mem should be searched to find the 
   *   proper page to remove, and modified to reflect any changes.  
   * @param virtPageNum is the number of virtual pages in the 
   *   simulator (set in Kernel.java).
   * @param clockMem is array of pages in physical memory used in WGClocklgorithm
   * @param currClockPointer  current position in WGClock Algorithm
   * @param replacePageNum is the requested page which caused the 
   *   page fault.  
   * @param controlPanel represents the graphical element of the 
   *   simulator, and allows one to modify the current display.
   */
  public static int replacePage ( Vector mem , Vector clockMem ,int currClockPointer, int t, int virtPageNum , int replacePageNum , ControlPanel controlPanel)
  {

    boolean ignoreWorkingSet = false;
    boolean toRemoveFound = false;
    boolean plannedToDisk = false;
   /* Vector clockMem = new Vector();
    for(int i = 0;i < virtPageNum;i++){
      Page page = ( Page ) mem.elementAt(i);
      if(page.physical != -1){
        clockMem.add(page);
      }
    }
    Collections.sort(clockMem,(Page a, Page b) -> b.inMemTime - a.inMemTime);*/
    System.out.println(currClockPointer);
    while(!toRemoveFound){
      int i = currClockPointer;
      do{
        Page page = ( Page ) mem.elementAt(i);
        if(page.R == 0){
          if(page.M == 0 && (page.lastTouchTime > t || ignoreWorkingSet)){
            Page nextpage = ( Page ) mem.elementAt( replacePageNum );
            nextpage.physical = page.physical;
            page.inMemTime = 0;
            page.lastTouchTime = 0;
            page.R = 0;
            page.M = 0;
            page.physical = -1;
            controlPanel.removePhysicalPage(findPageById(mem,virtPageNum,page.id) );
            controlPanel.addPhysicalPage( nextpage.physical , replacePageNum );
            clockMem.set(i, nextpage);
            toRemoveFound = true;
            currClockPointer = (i+1)%clockMem.size();
            break;
          }
          if(page.M == 1) {
            page.M = 0;
            plannedToDisk = true;
          }
        }
        else {
          page.R = 0;
        }
        i = (i+1) % clockMem.size();
      } while(i!= currClockPointer);
      if(plannedToDisk) plannedToDisk = false;
      else{
        ignoreWorkingSet = true;
      }
    }
  return currClockPointer;
    /*int count = 0;
    int oldestPage = -1;
    int oldestTime = 0;
    int firstPage = -1;
    int map_count = 0;
    boolean mapped = false;

    while ( ! (mapped) || count != virtPageNum ) {
      Page page = ( Page ) mem.elementAt( count );
      if ( page.physical != -1 ) {
        if (firstPage == -1) {
          firstPage = count;
        }
        if (page.inMemTime > oldestTime) {
          oldestTime = page.inMemTime;
          oldestPage = count;
          mapped = true;
        }
      }
      count++;
      if ( count == virtPageNum ) {
        mapped = true;
      }
    }
    if (oldestPage == -1) {
      oldestPage = firstPage;
    }*/
    /*Page page = ( Page ) mem.elementAt( oldestPage );
    Page nextpage = ( Page ) mem.elementAt( replacePageNum );
    controlPanel.removePhysicalPage( oldestPage );
    nextpage.physical = page.physical;
    controlPanel.addPhysicalPage( nextpage.physical , replacePageNum );
    page.inMemTime = 0;
    page.lastTouchTime = 0;
    page.R = 0;
    page.M = 0;
    page.physical = -1;*/
  }
  public static int findPageById(Vector mem,int virtPageNum, int id ){
    for(int i=0;i<virtPageNum;i++){
      Page page = (Page) mem.get(i);
      if(page.id == id){
        return i;
      }
    }
    return -1;
  }
}
