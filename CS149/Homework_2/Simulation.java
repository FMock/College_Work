import java.util.ArrayList;
import java.util.Random;

public class Simulation {

	private static ArrayList<Result> fcfsResults = new ArrayList<Result>();
	private static ArrayList<Result> sjfResults = new ArrayList<Result>();
	private static ArrayList<Result> srtResults = new ArrayList<Result>();
	private static ArrayList<Result> rrResults = new ArrayList<Result>();
	private static ArrayList<Result> hpfpResults = new ArrayList<Result>();
	private static ArrayList<Result> hpfnpResults = new ArrayList<Result>();
	
	private static ArrayList<Process> processes = new ArrayList<Process>();
	
	public static void main(String[] args) {
		for (int i = 0; i < 5; i++) {
			// generate processes (processes should only be generated once per run!)
			processes.clear();
			generateProcesses(20);
			
			// 1. run First-come first served
			Result fcfs = new FirstComeFirstServed().execute(copyProcesses());
			fcfsResults.add(fcfs);
			
			// 2. run Shortest job first
			Result sjf = new ShortestJobFirst().execute(copyProcesses());
			sjfResults.add(sjf);
			
			// 3. run Shortest remaining time
			Result srt = new ShortestRemainingTime().execute(copyProcesses());
			srtResults.add(srt);
			
			// 4. run Round robin
			Result rr = new RoundRobin().execute(copyProcesses());
			rrResults.add(rr);
			
			// 5. run Highest priority first (preemptive)
			Result hpfp = new HighestPriorityFirstPreemptive().execute(copyProcesses());
			hpfpResults.add(hpfp);
			
			// 6. run Highest priority first (non-preemptive)
			Result hpfnp = new HighestPriorityFirstNonPreemptive().execute(copyProcesses());
			hpfnpResults.add(hpfnp);
			
			//print results (if we don't just change the above to execute in println's)
			System.out.println("\nRun " + (i + 1) + " \n");
			System.out.println(processes);
			
			System.out.println("\nFirst Come First Served:");
			System.out.println(fcfs);
			System.out.println("\nShortest Job First:");
			System.out.println(sjf);
			System.out.println("\nShortest Remaining Time:");
			System.out.println(srt);
			System.out.println("\nRound Robin:");
			System.out.println(rr);
			System.out.println("\nHighest Priority First (Preemptive):");
			System.out.println(hpfp);
			System.out.println("\nHighest Priority First (Non Preemptive):");
			System.out.println(hpfnp);
		}
		
		System.out.println("\nRun Averages:\n");
		
		System.out.println("\nFirst Come First Served:");
		System.out.println(getAverage(fcfsResults));
		System.out.println("\nShortest Job First:");
		System.out.println(getAverage(sjfResults));
		System.out.println("\nShortest Remaining Time:");
		System.out.println(getAverage(srtResults));
		System.out.println("\nRound Robin:");
		System.out.println(getAverage(rrResults));
		System.out.println("\nHighest Priority First (Preemptive):");
		System.out.println(getAverage(hpfpResults));
		System.out.println("\nHighest Priority First (Non Preemptive):");
		System.out.println(getAverage(hpfnpResults));
	}

	private static void generateProcesses(int numProcesses) {
		if (numProcesses < 1 || numProcesses > 26) throw new RuntimeException("Process count must be between 1 and 26");
		
		Random random = new Random();
		
		for (int i = 0; i < numProcesses; i++) {
			float runTime = random.nextFloat() * 10;
			if(runTime < 9.9f) runTime += 0.1f;
			processes.add(new Process(Character.toString((char) ('A' + i)), random.nextInt(4) + 1, random.nextFloat() * 100, runTime));
		}
	}
	
	private static ArrayList<Process> copyProcesses() {
		ArrayList<Process> processesCopy = new ArrayList<Process>();
		
		for (Process process : processes) processesCopy.add(new Process(process));
		
		return processesCopy;
	}
	
	private static Result getAverage(ArrayList<Result> results) {
		float totalTurnaround = 0;
		float totalWaiting = 0;
		float totalResponseTime = 0;
		float totalThroughPut = 0;
		
		Result averageResult = new Result();
		
		for (Result result : results) {
			totalTurnaround += result.getTurnaround();
			totalWaiting += result.getWaiting();
			totalResponseTime += result.getResponse();
			totalThroughPut += result.getThroughput();
		}
		
		averageResult.runResults(totalTurnaround / results.size(), totalWaiting / results.size(), totalResponseTime / results.size(), totalThroughPut / results.size());
		return averageResult;
	}
}
