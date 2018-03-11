import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Vector;

public class FriendshipGraph {
	@SuppressWarnings("rawtypes")
	/*
	 * @param 
	 */
	private Map<String, LinkedList<String> > adj= new HashMap(); 
	HashMap<String, Integer> map = new HashMap<String, Integer>();
	private Map<String, Integer> dis = new HashMap();
	String Master;
	Integer member;
	boolean update ;
	public FriendshipGraph()
	{
		map.clear();
		member = 0;
		adj.clear();
		dis.clear();
		Master = "";
		update = false;
	}
	@SuppressWarnings("unchecked")
	public void addVertex(Person p)
	{
		if(map.containsKey(p.recallName()))
			throw new RuntimeException("a same key placed before.");
		map.put(p.recallName(), member);
		member += 1;
	}
	public void addEdge(Person p1,Person p2)
	{
		/*
		Integer p1n = map.get(p1.recallName());
		Integer p2n = map.get(p2.recallName());
		Vector<Integer> ve = (Vector)database.elementAt(p1n);
		ve.add(p2n);
		database.setElementAt(ve, p1n);
		*/
		String nam1 = p1.recallName();
		String nam2 = p2.recallName();
		if(adj.containsKey(nam1)) adj.get(nam1).add(nam2);
		else {
			LinkedList<String> li = new LinkedList();
			li.add(nam2);
			adj.put(nam1, li);
		}
		update = true;
	}
	public int getDistance(Person p1,Person p2)
	{
		String nam1 = p1.recallName();
		String nam2 = p2.recallName();
		if(Master == nam1 && update == false)
		{
			Integer ans ;
			if((ans=dis.get(nam2))==null)
			{
				return -1;
			}
			else return ans;
		}
		return BFS(nam1, nam2);
	}
	private int BFS(String f, String t)
	{
		Master = f;
		update = false;
		List<String> vis = new LinkedList<String>();
		@SuppressWarnings({ "rawtypes", "unchecked" })
		Queue<Pair> qpp = new LinkedList();
		qpp.add(new Pair(f, 0));
		dis.put(f, 0);
		vis.add(f);
		while(!qpp.isEmpty())
		{
			Pair noww = qpp.poll();
			String now = (String) noww.getFirst();
			Integer diss = (Integer) noww.getSecond() + 1;
			for(String pos:adj.get(now))
			{
				if(vis.contains(pos)==false)
				{
					vis.add(pos);
					dis.put(pos, diss);
					qpp.add(new Pair(pos, diss));
				}
			}
		}
		if(dis.containsKey(t)==true)
		{
			return dis.get(t);
		}
		else return -1;
	}
}



class Person{
	String name;
	public Person(String name_in)
	{
		name = name_in;
	}
	public String recallName()
	{
		return name;
	}
}

class Pair
{
	private Object first;
	private Object second;
	public Pair(Object fir, Object sec)
	{
		first = fir;
		second = sec;
	}
	public Object getFirst()
	{
		return first;
	}
	public Object getSecond()
	{
		return second;
	}
}
