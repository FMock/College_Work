import java.util.ArrayList;

public class FirstComeFirstServed implements Executable{
	Result result = new Result();
	float turnAroundTotal=0;
	float averageTurnAround=0;
	float waitingTotal=0;
	float averageWaiting=0;
	float responseTimeTotal=0;
	float averageResponseTime=0;
	float numberProcessesCompleted=0;
	float throughPut=0;
	float temp=0;
	public Result execute(ArrayList<Process> processes) {
		processes.sort(Process.compareByArrival());
		ArrayList<String> quanta = quantaForTimeChart(processes);
		for(int i=0;i<processes.size();i++){
			// no longer add processes to result
//			result.addProcess(processes.get(i));
			//result.addChart(processes.get(i).getName());
			turnAroundTotal=turnAroundTotal+turnAroundTotal+processes.get(i).getRunTime();
			averageTurnAround=turnAroundTotal/(i+1);
			if(i!=0 && i!=processes.size()-1){
				waitingTotal=waitingTotal+waitingTotal+processes.get(i).getRunTime();
				averageWaiting=waitingTotal/(i+1);
			}
			responseTimeTotal=responseTimeTotal+processes.get(i).getRunTime();
			averageResponseTime=responseTimeTotal/(i+1);
			if(responseTimeTotal<=100){
				numberProcessesCompleted++;
			}
		}
		throughPut=numberProcessesCompleted/100;
		result.runResults(averageTurnAround, averageWaiting, averageResponseTime, throughPut);	
		for(int i=0;i<quanta.size();i++){
			result.addChart(quanta.get(i));
		}
		return result;
	}
	public ArrayList<String> quantaForTimeChart(ArrayList<Process> processes){
		ArrayList<String> quanta = new ArrayList<String>();
		float totalTime=0;
		int unitsToAddEmpty=0;
		int unitsToAddString=0;
		int processesIndex=0;
		int quantaIndex=0;
		while(processesIndex<processes.size()){
			if(processes.get(processesIndex).getArrivalNum()>totalTime){
				unitsToAddEmpty=(int) (processes.get(processesIndex).getArrivalNum()-totalTime);
				for(int i=0;i<unitsToAddEmpty;i++){
					quanta.add(quantaIndex,"");
					quantaIndex++;
				}
				totalTime=processes.get(processesIndex).getArrivalNum();
			}
			else{
				if((int)totalTime+1>totalTime+processes.get(processesIndex).getRunTime()){
					unitsToAddString=1;
				}
				else{
					unitsToAddString=(int) (totalTime+processes.get(processesIndex).getRunTime()-quanta.size())+1;
				}
				// removing line of debug, clean final output
//				System.out.println("unitsToAddString: "+unitsToAddString);
				for(int i=0;i<unitsToAddString;i++){
					if(i==0 && quantaIndex!=0 && totalTime>quantaIndex-1 && quanta.get(quantaIndex-1)!=null){
						quanta.set(quantaIndex-1, quanta.get(quantaIndex-1)+processes.get(processesIndex).getName());
					}
					else{
						quanta.add(quantaIndex, processes.get(processesIndex).getName());
						quantaIndex++;
					}
				}
				totalTime=totalTime+processes.get(processesIndex).getRunTime();
				processesIndex++;
			}
		}
		if(quantaIndex<100){
			while(quantaIndex<100){
				quanta.add(quantaIndex, "");
				quantaIndex++;
			}
		}
		return quanta;
	}
}
