import java.io.IOException;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.FloatWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;

/**
 * CS157B Hadoop MapReduce Assignment
 * Frank Mock
 */

public class PostalCodeRating {
	/* The Mapper is a generic type with four formal type parameters
	 * that specify the input key, input value, output key, output value*/
	public static class MapperClass
		extends Mapper<Object, Text, Text, FloatWritable> {
		
		Text postalCode = new Text();
		FloatWritable stars = new FloatWritable();
				
		public void map(Object key, Text value, Context context)
				throws IOException, InterruptedException {
			
			String line = value.toString(); // Convert to Java String
			
			line = line.replaceAll("\"", ""); // Remove double quotes
			String[] colValue = line.split(","); // Each token separated by comma

			postalCode.set(colValue[6]); // assign the 6th element to postalcode
			try {
				stars.set(Float.valueOf(colValue[9])); // assign 9th element to stars
			}
			catch (NumberFormatException e) {
				e.printStackTrace();
			}
			// Write output key, value pair to the context object
			context.write(postalCode, stars);
		}
	}
	
	// The Reducer
	public static class ReducerClass
		extends Reducer<Text, FloatWritable, Text, FloatWritable> {
		
		FloatWritable postalCodeRating = new FloatWritable();
		
		public void reduce(Text key, Iterable<FloatWritable> values, Context context)
				throws IOException, InterruptedException {
			// Record sum and count of stars
			float sum = 0;
			float count = 0;
			// Sum all the stars that share the same postal code
			for (FloatWritable val : values) {
				sum += val.get();
				count++;
			}
			// Compute the average
			postalCodeRating.set(sum / count); 
			// Write output pair
			context.write(key, postalCodeRating);
		}
	}
	
	// The Driver Code
	public static void main(String[] args) throws Exception {
		// Check for correct number of arguments
		if (args.length != 2) {
			System.out.println("usage: [input] [output]");
			System.exit(-1);
		}
		// Create and configure MapReduce job
		Configuration conf = new Configuration();
		Job job = Job.getInstance(conf, "PostalCodeRating");
		job.setJarByClass(PostalCodeRating.class);
		// Set Mapper and Reducer Class
		job.setNumReduceTasks(25); // Explicitly set number of reducers
		job.setMapperClass(MapperClass.class);
		job.setReducerClass(ReducerClass.class);
	    // Set output types for keys and values
	    job.setMapOutputKeyClass(Text.class);
	    job.setMapOutputValueClass(FloatWritable.class);
	    job.setOutputKeyClass(Text.class);
	    job.setOutputValueClass(FloatWritable.class);
		// Set input and output format class
		job.setInputFormatClass(TextInputFormat.class); //default
	    job.setOutputFormatClass(TextOutputFormat.class);
	    // Set input and output files from arguments
		FileInputFormat.addInputPath(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));
		// Send job to cluster and wait for job to complete
		job.waitForCompletion(true);
	}

}
