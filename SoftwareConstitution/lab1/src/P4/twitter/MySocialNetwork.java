package twitter;

import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.Set;

public class MySocialNetwork {
	public static Map<String, Set<String>> guessFollowsGraph(List<Tweet> tweets)
	{
		//throw new RuntimeException("not implemented");
		SocialNetwork net = new SocialNetwork();
		Map<String, Set<String>> ntt = net.guessFollowsGraph(tweets);
		Set<String> aut = ntt.keySet();
		Map<String, Set<String>> mention = new HashMap();
		Extract ext = new Extract();
    	Filter flt = new Filter();
    	Map<String, Set<String>> ansmen = new HashMap();
    	for(String key:aut)
    	{
    		Set<String> tmpss = ext.getMentionedUsers(flt.writtenBy(tweets, key));
    		ansmen.put(key, tmpss);
    	}
    	Map<String, Set<String>> ans = gradientParametreDescent(ntt, aut, ansmen);
		return ans;
	}
	public static Map<String, Set<String>> gradientParametreDescent(Map<String, Set<String>> foll, Set<String> au, Map<String, Set<String>> mention)
	{
		//throw new RuntimeException("not implemented");
		Random rd = new Random();
		Map<String, Set<String>> ans = new HashMap();
		Map<String, Set<String>> mp = new HashMap();
		for(String a:au)
		{
			Set<String> able = new HashSet();
			if(mention.containsKey(a))
			{
				for(String infl:mention.get(a))
				{
					able.add(infl);
					if(mention.containsKey(infl))
					{
						for(String inll:mention.get(infl))
						{
							Double rt = rd.nextGaussian()+0.5;
							if(rt - 0.5 >= 0.001)
							{
								able.add(inll);
							}
						}
					}
				}
			}
			mp.put(a, able);
		}
		for(String key:mp.keySet())
		{
			Set<String> tmpss = mp.get(key);
			for(String keys: tmpss)
    		{
    			if(ans.containsKey(keys.toLowerCase()))//.split(":")[0])).split(":")[0].split(":")[0]
    			{
    				ans.get(keys.toLowerCase()).add(key.toLowerCase());
    			}
    			else
    			{
    				Set<String> child = new HashSet<String>();
    				child.add(key.toLowerCase());
    				ans.put(keys.toLowerCase(), child);
    			}
    		}
		}
		return ans;
	}
	public static List<String> influencers(Map<String, Set<String>> followsGraph) {
        //throw new RuntimeException("not implemented");
    	List<String> ans = new LinkedList();
    	List<Pair> tmp = new LinkedList();
    	for(Map.Entry<String, Set<String>> en: followsGraph.entrySet())
    	{
    		tmp.add(new Pair(en.getKey(), en.getValue().size()));
    	}
    	Collections.sort(tmp, new Comparator<Pair>(){
    		public int compare(Pair p1, Pair p2)
    		{
    			return p2.getSecond().compareTo(p1.getSecond());
    			/*if(p1.getSecond() > p2.getSecond())
    			{
    				return 1;
    			}
    			else return -1;*/
    		}
    	});
    	for(Pair p: tmp)
    	{
    		String anss = p.getFirst().toLowerCase().split(":")[0];
    		ans.add(anss);
    	}
    	return ans;
    }
}

class Pairs
{
	String au;
	Double hotpoint;
	public Pairs(String aut, Double hot)
	{
		au = aut;
		hotpoint = hot;
	}
	public String getFirst()
	{
		return au;
	}
	public Double getSecond()
	{
		return hotpoint;
	}
}