public class Utility {
	
	long n = 5;
	boolean[] mtx = {	false,false,false,false,false,
						false,true, true, true,false,
						false,false,false,true,false,
						false,false,false,false,false,
						false,false,false,false,false	};
	
	long rand = 0;
	
	public boolean updateUp(long x, long y){ 
		if(y == 0) return true;
		return mtx[(int) (y*(n-1)+x)];
	}
	public boolean updateDown(long x, long y){
		if(y == (n-1)) return true;
		return mtx[(int)(y*(n+1)+x)];
	}
	public boolean updateLeft(long x, long y){
		if(x == 0) return true;
		return mtx[(int)(y*n+x-1)];
	}
	public boolean updateRight(long x, long y){
		if(x == n-1) return true;
		return mtx[(int)(y*n+x+1)];
	}
	public long getStep(String path, long i){return i%4;}
	
	public long sendMessage(long s1, long x, long y){ return 1;}
	public long waitMessage(){
		try {
			Thread.sleep(3000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return (rand++)%5;
	}
	public String getPath(){return "I'm Alive";}
}
