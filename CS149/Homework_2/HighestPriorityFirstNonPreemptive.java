import java.util.ArrayDeque;
import java.util.ArrayList;


public class HighestPriorityFirstNonPreemptive implements Executable {
	
	Result result = new Result();
	float quanta = 0;
	float turnaroundTime = 0;
	float waitingTime = 0;
	float responseTime = 0;
	float throughput = 0;
	boolean finishedP =false;
	ArrayList<ArrayDeque<Process>> priority = new ArrayList<ArrayDeque<Process>>();
	
	public Result execute(ArrayList<Process> processes) {
		priority.add(new ArrayDeque<Process>());
		priority.add(new ArrayDeque<Process>());
		priority.add(new ArrayDeque<Process>());
		priority.add(new ArrayDeque<Process>());
	
		processes.sort(Process.compareByArrival());
		boolean running = true;
		int nextProcess = 0;
		
		while(running){
			if(quanta > 100 || processes.size() == nextProcess){
				running = false;
			}
			if(running && processes.get(nextProcess).getArrivalNum() <= quanta){
				addProcess(processes.get(nextProcess));
				if(nextProcess < (processes.size() - 1))
						nextProcess++;
				
				if(quanta > nextStartTime() && !finishedP){
					quanta = nextStartTime();
				}
			}else{
				quanta += 1;
				finishedP = false;
			}
			
			
			Process runningP= nextProcess();
			evaluate(runningP, "");
			
			
		}
		result.runResults(turnaroundTime / throughput, waitingTime/ throughput, responseTime/throughput, throughput / 100);
		return result;
	}
	
	private void addProcess(Process process){
		switch (process.getPriority()){
		case 1: priority.get(0).add(process);
			break;
		case 2: priority.get(1).add(process);
			break;
		case 3: priority.get(2).add(process);
			break;
		case 4: priority.get(3).add(process);
			break;
		default: throw new RuntimeException("Invalid Priority");
		}
	}
	
	private void addBackProcess(Process process){
		switch(process.getPriority()){
		case 1: priority.get(0).addFirst(process);
			break;
		case 2: priority.get(1).addFirst(process);
			break;
		case 3: priority.get(2).addFirst(process);
			break;
		case 4: priority.get(3).addFirst(process);
			break;
		default: throw new RuntimeException("Invalid Priority");
		}
	}
	
	private Process nextProcess(){
		if(!priority.get(0).isEmpty()){
			return priority.get(0).pop();
		}else if(!priority.get(1).isEmpty()){
			return priority.get(1).pop();
		}else if(!priority.get(2).isEmpty()){
			return priority.get(2).pop();
		}else if (!priority.get(3).isEmpty()){
			return priority.get(3).pop();
		}else{
			return null;
		}
	}
	
	private void evaluate(Process process, String processString){
		if(process != null){
			if(((quanta % 1) + process.getTimeLeft()) >= 1.0f){
				if(!process.hasStarted()){
					process.start(quanta);
				}
				quanta =(float)((int) quanta) + 2;
				process.setTimeLeft(process.getTimeLeft() - 1.0f);
				addBackProcess(process);
				result.addChart(processString.concat(process.getName()));
			}else{
				if(!process.hasStarted()){
					process.start(quanta);
				}
				responseTime += (quanta - process.getArrivalNum());
				quanta += process.getTimeLeft();
				finishedP = true;
				process.stop(quanta);
				throughput++;
				waitingTime += Math.abs(process.getStartTime() - process.getArrivalNum());
				turnaroundTime += (process.getEndTime() - process.getArrivalNum());
				Process newProcess = nextProcess();
				if(newProcess != null){
					evaluate(newProcess, processString.concat(process.getName()));
				}else{
					result.addChart(processString.concat(process.getName()));
				}
			}
		}
	}
	
	private float nextStartTime(){
		if(!priority.get(0).isEmpty()){
			return priority.get(0).peek().getArrivalNum();
		}else if(!priority.get(1).isEmpty()){
			return priority.get(1).peek().getArrivalNum();
		}else if(!priority.get(2).isEmpty()){
			return priority.get(2).peek().getArrivalNum();
		}else{
			return priority.get(3).peek().getArrivalNum();
		}
	}
}

