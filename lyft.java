import java.util.*;

public class lyft {

	static class point {
		double longitude;
		double latitude;

		public point(double latitude, double longitude){
			this.longitude = longitude;
			this.latitude = latitude;
		}

		void setLongitude(double longitude){
			this.longitude = longitude;
		}

		void setLatitude(double latitude){
			this.latitude = latitude;
		}

		double getLongitude(){
			return this.longitude;
		}

		double getLatitude(){
			return this.latitude;
		}
	}

	
	static ArrayList<String> possibleDetours = new ArrayList<String>();
	static HashMap<String, point> points = new HashMap<String, point>();
	
	static point A = new point(25, 75);
	static point B = new point(35, 60);
	static point C = new point(25, 100);
	static point D = new point(35, 100);


	static double calcDistance(point source, point destination){

		final double radiusOfEarth = 3960;

		double diffLat = Math.toRadians(destination.latitude - source.latitude);
		double diffLong = Math.toRadians(destination.longitude - source.longitude);

		double lat1 = Math.toRadians(source.latitude);
		double lat2 = Math.toRadians(destination.latitude);
		
		double a = Math.pow(Math.sin(diffLat/2) , 2) + Math.pow(Math.sin(diffLong/2), 2)* Math.cos(lat1)* Math.cos(lat2);
		double c  = 2*Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
		double distance = radiusOfEarth * c;

		return distance;
	}

	static int shorterDetour(){
		ArrayList<Double> dDistances = new ArrayList<Double>();
		double currentDistance = 0;

		for(String eachDetour : possibleDetours){
			char[] vertices = eachDetour.toCharArray();
			for(int index = 0; index < vertices.length-1; index ++){
				String source = "" + vertices[index];
				String destination = "" + vertices[index+1];
				currentDistance += calcDistance(points.get(source), points.get(destination));				
			}
			dDistances.add(currentDistance);
		}

		double minDD = dDistances.get(0);
		int index = 0;
		
		for(double current : dDistances)
			if(minDD > current){
				minDD = current;
				index = dDistances.indexOf(current);
			}
		System.out.println("The shortest detour distance is: " + Math.round(minDD) + " miles");
		return index;
	}

	public static void main(String[] args){

		possibleDetours.add("ACDB");
		possibleDetours.add("CABD");

		points.put("A", A);
		points.put("B", B);
		points.put("C", C);
		points.put("D", D);

		System.out.println("The shortest detour path is: " + possibleDetours.get(shorterDetour()));

	}
}

