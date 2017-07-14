import java.util.ArrayList;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public class ShortestRemainingTime implements Executable {

	private Predicate<Process> notDone = new Predicate<Process>() {
		@Override
		public boolean test(Process p) {
			return p.getTimeLeft() > 0;
		}
	};

	private Predicate<Process> hasArrivedPredicateMaker(float quanta) {
		return new Predicate<Process>() {
			@Override
			public boolean test(Process t) {
				return t.getArrivalNum() <= quanta;
			}
		};
	}

	@Override
	public Result execute(ArrayList<Process> processes) {
		// Sort the list of Processes by estimated run time
		processes.sort(Process.compareByTimeLeft());

		// statistics
		Result result = new Result();

		// initialization
		float i = 0;
		Process p = null;

		do {
			if (getArrivedProcessesSize(processes, i) != 0) {
				Process nextWaitingProcess = getShortestRemaining(processes, i);
				if (p != null) {
					if (p.getTimeLeft() >= nextWaitingProcess.getTimeLeft()) {
						p = nextWaitingProcess;
						if (p.getStartTime() == 0)
							p.start(i);
					} else if (p.getTimeLeft() <= 0) {
						p = nextWaitingProcess;
					}
					p.decrement(0.1f, i);
				} else {
					p = nextWaitingProcess;
				}
			}
			if (p != null)
				result.addChart(p.getName());

			i += 0.1;
		} while (getRemainingProcessesSize(processes) != 0);

		return generateResults(processes, result);
	}

	private int getArrivedProcessesSize(ArrayList<Process> processes,
			float quanta) {
		return processes.stream().filter(hasArrivedPredicateMaker(quanta))
				.filter(notDone).collect(Collectors.toList()).size();
	}

	private Process getShortestRemaining(ArrayList<Process> processes,
			float quanta) {

		ArrayList<Process> sortedList = (ArrayList<Process>) processes.stream()
				.filter(hasArrivedPredicateMaker(quanta)).filter(notDone)
				.collect(Collectors.toList());

		return sortedList.get(0);
	}

	private int getRemainingProcessesSize(ArrayList<Process> processes) {
		return processes.stream().filter(notDone).collect(Collectors.toList())
				.size();
	}

	private Result generateResults(ArrayList<Process> processes, Result result) {

		float turnaroundAvg = 0, waitingAvg = 0, responseAvg = 0, throughput = 0;

		for (Process p : processes) {
			turnaroundAvg += Math.abs(p.getStartTime() - p.getEndTime());
			waitingAvg += Math.abs(p.getArrivalNum() - p.getStartTime());
			responseAvg += Math.abs(p.getArrivalNum() - p.getEndTime());
			if(p.getEndTime() <= 100){
				throughput++;
			}
		}

		turnaroundAvg /= processes.size();
		waitingAvg /= processes.size();
		responseAvg /= processes.size();
		throughput /= 100;

		result.runResults(turnaroundAvg, waitingAvg, responseAvg, throughput);

		return result;
	}
}
