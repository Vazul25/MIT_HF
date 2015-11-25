
public class Utility {
	public boolean updateUp(){ return true;}
	public boolean updateDown(){return false;}
	public boolean updateLeft(){return true;}
	public boolean updateRight(){return false;}
	public long getStep(String path, long i){return i%4;}
	
	public long sendMessage(String s1){ return 1;}
	public String waitMessage(){return "Cloud Online";}
	public String getPath(){return "I'm Alive";}
}
