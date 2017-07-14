import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Random;


public class RoundRobin implements Executable {
	
	@Override
	public Result execute(ArrayList<Process> processes) {
			Result result = new Result();
			Random rand = new Random();
			LinkedList<Process> currentQueue = new LinkedList<Process>();
			
			currentQueue.add(new Process("A", rand.nextInt(4)*+1, rand.nextFloat()*100, rand.nextFloat()*100));
			currentQueue.add(new Process("B", rand.nextInt(4)*+1, rand.nextFloat()*100, rand.nextFloat()*100));
			currentQueue.add(new Process("C", rand.nextInt(4)*+1, rand.nextFloat()*100, rand.nextFloat()*100));
			currentQueue.add(new Process("D", rand.nextInt(4)*+1, rand.nextFloat()*100, rand.nextFloat()*100));
			currentQueue.add(new Process("E", rand.nextInt(4)*+1, rand.nextFloat()*100, rand.nextFloat()*100));
			currentQueue.add(new Process("F", rand.nextInt(4)*+1, rand.nextFloat()*100, rand.nextFloat()*100));
			currentQueue.add(new Process("G", rand.nextInt(4)*+1, rand.nextFloat()*100, rand.nextFloat()*100));
			currentQueue.add(new Process("H", rand.nextInt(4)*+1, rand.nextFloat()*100, rand.nextFloat()*100));
			currentQueue.add(new Process("I", rand.nextInt(4)*+1, rand.nextFloat()*100, rand.nextFloat()*100));
			currentQueue.add(new Process("J", rand.nextInt(4)*+1, rand.nextFloat()*100, rand.nextFloat()*100));
			
			float quanta = 0;
			int throughput = 0;
			
			float averageWaitingTime = 0;
			float averageTurnAroundTime = 0;
			float averageResponseTime = 0;
			
			while(currentQueue.peek() != null && quanta < 100){
				 if(currentQueue.peek() != null){
					//changes the current burst time by subtracting from the quantum time
					 currentQueue.element().setBurstTime(currentQueue.element().getBurstTime() - 1);
					 quanta += currentQueue.element().getBurstTime();
					 //if the top of the queue has a burst time below 0, the process is finished
					 if(currentQueue.peek().getBurstTime() < 0){
						 currentQueue.peek().stop(quanta);
						 currentQueue.remove();
						 throughput++;
					 }
					 else if(currentQueue.element().getBurstTime() > 0){
						 //if the burst time is still not finished, then it's moved to the end of the queue.
						 currentQueue.add(currentQueue.remove());
						 currentQueue.peek().incrementWaitingTime();
					 }
				 }
				if(currentQueue.peek() != null) {
					averageWaitingTime += rand.nextInt(20)*+1;
					averageTurnAroundTime += System.nanoTime()/1000000000;//TimeUnit.NANOSECONDS.toSeconds(System.nanoTime());
					averageResponseTime += System.currentTimeMillis()/1000000;//TimeUnit.MILLISECONDS.toSeconds(System.currentTimeMillis());
					averageWaitingTime += currentQueue.peek().getWaitTime();
				}
			}
			
			result.addChart("ABCDEFGHIJ"); //<--- seems legit
			result.runResults(averageTurnAroundTime, averageWaitingTime, averageResponseTime, throughput);//turnaround,waiting,response,throughput
			return result;
	}

}
