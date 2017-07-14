import java.util.ArrayList;

//Non-Preemptive batch algorithm.Assumes run times are known in advance.

public class ShortestJobFirst implements Executable
{
	@Override
	public Result execute(ArrayList<Process> processes) 
	{
		Result r = new Result();
		int numProcesses = processes.size();
		
		/*
		for(Process p : processes)
		{
			float f = (float) Math.floor(p.getArrivalNum());
			p.setArrivalNum(f);
		}
		*/
		
		//Sort the list of Processes by arrival time
		processes.sort(Process.compareByArrival());
		
		//A list to hold the Processes as they arrive. A waiting list
		ArrayList<Process> waiting = new ArrayList<Process>();
		
		//At algorithm completion will hold the Processes in the order they were run
		ArrayList<Process> running = new ArrayList<Process>();
		
		float i = 0f;
		i = processes.get(0).getArrivalNum(); //set i to the arrival time of first process
		int next = 0;
		int run = 0;
		running.add(processes.get(next)); //load running queue
		Process p = running.get(run); //the first Process to run
		next++;//point to the next Process that will arrive
		float runTime = 0f;
		boolean runNext = false;
		p.start(i);
		String q = "";//for the time chart variable of the Result object
		
		//No Processes running up until the lowest arrival time
		for(int j = 0; j < i - 1; j++)
		{
			// nice output, but changing to match the others
//			q = "Quanta " + j + ": No processes running yet"+System.getProperty("line.separator");
			q = "";
			r.addChart(q);
		}
		
		
		do
		{
			// nice output, but changing to match the others
//			q = "Quanta " + Math.floor(i) + ": " + running.get(run).getName() + System.getProperty("line.separator");
			q = running.get(run).getName();
			r.addChart(q);
	
			//advance quanta and runTime counter
			i += 1;
			runTime += 1;
			waiting.sort(Process.compareByRunTime());
			
			//Has another Processes time been reached? If so add them to the waiting queue
			if((next < numProcesses) && (i >= processes.get(next).getArrivalNum()))
			{
				waiting.add(processes.get(next));
				//newly added Process has been added so sort the waiting queue
				waiting.sort(Process.compareByRunTime());
				next++; //point to the next Process that will arrive
			}
			
			//Has the current running Process's time been reached? If so end it
			if(runTime >= p.getRunTime())
			{
				p.stop(i);
				runNext = true; //The next Process can be run
			}
				

			//Run next waiting Process if there are no Processes currently running
			if((runNext) && (!waiting.isEmpty()))
			{
				running.add(waiting.get(0)); //Move next Process from waiting to running queue
				run++;
				waiting.remove(0); //remove from waiting queue and shift any elements down
				runTime = 0; //reset counter for the next Process
				p = running.get(run); //Run the next Process
				p.start(i); //set the start
				runNext = false; //A Process is running, don't run the next waiting Process 
			}
			
			
		}while((processes.get(numProcesses - 1).getEndTime() <= 0) || (runNext == false) || i < 99);
		
		
		//System.out.println("Throughput Value = " + i); //The throughput is the final quanta of the last Process
		//Fill the Result processList with the current list of Processes
//		for(Process t : processes)
//		{
//			String list = t.toString();
//			r.addProcess(list);
//		}
		int count = 1;
		float turnAround = 0f;
		float waitTimeTotal = 0f;
		float responseTimeTotal = 0f;
		for(Process s : running)
		{
			turnAround += s.getEndTime() - s.getStartTime();
			waitTimeTotal += s.getStartTime() - s.getArrivalNum();
			responseTimeTotal += s.getEndTime() - s.getArrivalNum();
			//System.out.println(count + " " + s.toString());
			count++;
		}
		r.runResults(turnAround / processes.size(), waitTimeTotal / processes.size(), responseTimeTotal / processes.size(), processes.size() / i);
		
		//System.out.println("End time of last " + running.get(numProcesses - 1).getEndTime());

		
		//System.out.println("******************RESULT toString*****************");
//		System.out.println(r.toString());
		return r;
	}
}
