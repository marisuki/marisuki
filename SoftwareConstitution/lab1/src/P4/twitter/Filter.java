/* Copyright (c) 2007-2016 MIT 6.005 course staff, all rights reserved.
 * Redistribution of original or derived work requires permission of course staff.
 */
package twitter;

import java.time.Instant;
import java.util.LinkedList;
import java.util.List;

/**
 * Filter consists of methods that filter a list of tweets for those matching a
 * condition.
 * 
 * DO NOT change the method signatures and specifications of these methods, but
 * you should implement their method bodies, and you may add new public or
 * private methods or classes if you like.
 */
public class Filter {

    private static Object A;

	/**
     * Find tweets written by a particular user.
     * 
     * @param tweets
     *            a list of tweets with distinct ids, not modified by this method.
     * @param username
     *            Twitter username, required to be a valid Twitter username as
     *            defined by Tweet.getAuthor()'s spec.
     * @return all and only the tweets in the list whose author is username,
     *         in the same order as in the input list.
     */
    public static List<Tweet> writtenBy(List<Tweet> tweets, String username) {
        //throw new RuntimeException("not implemented");
    	List<Tweet> ans = new LinkedList<Tweet>();
    	for(Tweet t: tweets)
    	{
    		if(t.getAuthor().toLowerCase().equals(username.toLowerCase()))
    		{
    			ans.add(t);
    		}
    	}
    	return ans;
    }

    /**
     * Find tweets that were sent during a particular timespan.
     * 
     * @param tweets
     *            a list of tweets with distinct ids, not modified by this method.
     * @param timespan
     *            timespan
     * @return all and only the tweets in the list that were sent during the timespan,
     *         in the same order as in the input list.
     */
    public static List<Tweet> inTimespan(List<Tweet> tweets, Timespan timespan) {
        //throw new RuntimeException("not implemented");
    	Instant st = timespan.getStart();
    	Instant ed = timespan.getEnd();
    	List<Tweet> ans = new LinkedList<Tweet>();
    	for(Tweet t: tweets)
    	{
    		if(t.getTimestamp().isAfter(st) && t.getTimestamp().isBefore(ed))
    		{
    			ans.add(t);
    		}
    	}
    	return ans;
    }

    /**
     * Find tweets that contain certain words.
     * 
     * @param tweets
     *            a list of tweets with distinct ids, not modified by this method.
     * @param words
     *            a list of words to search for in the tweets. 
     *            A word is a nonempty sequence of nonspace characters.
     * @return all and only the tweets in the list such that the tweet text (when 
     *         represented as a sequence of nonempty words bounded by space characters 
     *         and the ends of the string) includes *at least one* of the words 
     *         found in the words list. Word comparison is not case-sensitive,
     *         so "Obama" is the same as "obama".  The returned tweets are in the
     *         same order as in the input list.
     */
    public static List<Tweet> containing(List<Tweet> tweets, List<String> words) {
        //throw new RuntimeException("not implemented");
    	List<Tweet> ans = new LinkedList<Tweet>();
    	for(Tweet t: tweets)
    	{
    		String gro[] = t.getText().split(" ");
    		boolean has = false;
    		for(String str: words)
    		{
    			for(String s:gro)
    			{
    				if(str.equals(s))
    				{
    					has = true;
    					break;
    				}
    			}
    			if(has)
    			{
    				break;
    			}
    		}
    		if(has) ans.add(t);
    	}
    	return ans;
    }

}
