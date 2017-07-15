import java.applet.Applet;
import java.applet.AudioClip;
import java.io.File;
import java.net.URL;


public class SoundPlay{
	public static void PlaySound(String fileName) {
	   try{					
		   // Get current directory name, and build URL
		   URL testUrl=new URL("file:" + new File(".").getCanonicalPath() + "//" + fileName);
	
		   AudioClip testClip=Applet.newAudioClip(testUrl);
	       testClip.play();  //or use testClip.play();
	
	    } catch(Exception e) {
	        System.out.println(e.toString());
	    }
	}
}