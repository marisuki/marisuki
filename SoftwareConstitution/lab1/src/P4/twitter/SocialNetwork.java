/* Copyright (c) 2007-2016 MIT 6.005 course staff, all rights reserved.
 * Redistribution of original or derived work requires permission of course staff.
 */
package twitter;

import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * SocialNetwork provides methods that operate on a social network.
 * 
 * A social network is represented by a Map<String, Set<String>> where map[A] is
 * the set of people that person A follows on Twitter, and all people are
 * represented by their Twitter usernames. Users can't follow themselves. If A
 * doesn't follow anybody, then map[A] may be the empty set, or A may not even exist
 * as a key in the map; this is true even if A is followed by other people in the network.
 * Twitter usernames are not case sensitive, so "ernie" is the same as "ERNie".
 * A username should appear at most once as a key in the map or in any given
 * map[A] set.
 * 
 * DO NOT change the method signatures and specifications of these methods, but
 * you should implement their method bodies, and you may add new public or
 * private methods or classes if you like.
 */
public class SocialNetwork {

    /**
     * Guess who might follow whom, from evidence found in tweets.
     * 
     * @param tweets
     *            a list of tweets providing the evidence, not modified by this
     *            method.
     * @return a social network (as defined above) in which Ernie follows Bert
     *         if and only if there is evidence for it in the given list of
     *         tweets.
     *         One kind of evidence that Ernie follows Bert is if Ernie
     *         @-mentions Bert in a tweet. This must be implemented. Other kinds
     *         of evidence may be used at the implementor's discretion.
     *         All the Twitter usernames in the returned social network must be
     *         either authors or @-mentions in the list of tweets.
     */
    public static Map<String, Set<String>> guessFollowsGraph(List<Tweet> tweets) {
        //throw new RuntimeException("not implemented");
    	Extract ext = new Extract();
    	Filter flt = new Filter();
    	Set<String> aut = new HashSet();
    	Map<String, Set<String>> ans = new HashMap();
    	for(Tweet t:tweets)
    	{
    		aut.add(t.getAuthor().toLowerCase());
    	}
    	for(String key:aut)
    	{
    		Set<String> tmpss = ext.getMentionedUsers(flt.writtenBy(tweets, key));
    		ans.put(key, tmpss);
    	}
    	/*
    	for(String key:aut)
    	{
    		Set<String> tmpss = ext.getMentionedUsers(flt.writtenBy(tweets, key));
    		for(String keys: tmpss)
    		{
    			if(ans.containsKey(keys))//.split(":")[0])).split(":")[0].split(":")[0]
    			{
    				ans.get(keys).add(key);
    			}
    			else
    			{
    				Set<String> child = new HashSet<String>();
    				child.add(key.toLowerCase());
    				ans.put(keys.toLowerCase(), child);
    			}
    		}
    	}
    	
    	Integer cnt=0;
    	for(String s:ans.keySet() )
    	{
    		cnt+=ans.get(s).size();
    	}*/
    	//System.out.println(aut.size()); 
    	return ans;
    }

    /**
     * Find the people in a social network who have the greatest influence, in
     * the sense that they have the most followers.
     * 
     * @param followsGraph
     *            a social network (as defined above)
     * @return a list of all distinct Twitter usernames in followsGraph, in
     *         descending order of follower count.
     */
    public static List<String> influencers(Map<String, Set<String>> followsGraph) {
        //throw new RuntimeException("not implemented");
    	List<String> ans = new LinkedList();
    	List<Pair> tmp = new LinkedList();
    	Map<String, Set<String>> influencer = new HashMap();
    	for(String key: followsGraph.keySet())
    	{
    		Set<String> following = followsGraph.get(key);
    		for(String author: following)
    		{
    			if(influencer.containsKey(author))
    			{
    				influencer.get(author).add(key);
    			}
    			else
    			{
    				Set<String> newset = new HashSet();
    				newset.add(key);
    				influencer.put(author, newset);
    			}
    		}
    	}
    	for(Map.Entry<String, Set<String>> en: influencer.entrySet())
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
    		String anss = p.getFirst();
    		ans.add(anss);
    	}
    	return ans;
    }
    
}
class Pair
{
	String au;
	Integer hotpoint;
	public Pair(String aut, Integer hot)
	{
		au = aut;
		hotpoint = hot;
	}
	public String getFirst()
	{
		return au;
	}
	public Integer getSecond()
	{
		return hotpoint;
	}
}