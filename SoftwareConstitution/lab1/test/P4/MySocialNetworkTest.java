package twitter;

import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class MySocialNetworkTest {
	public static URL SAMPLE_SERVER = makeURLAssertWellFormatted("https://raw.githubusercontent.com/rainywang/Spring2018_HITCS_SC_Lab1/master/P4/src/tweetPoll.py");
    
    private static URL makeURLAssertWellFormatted(String urlString) {
        try {
            return new URL(urlString);
        } catch (MalformedURLException murle) {
            throw new AssertionError(murle);
        }
    }
    public static void main(String[] args) throws IOException {
        try {
            assert false;
            //throw new Error("Always run main and tests with assertions enabled");
        } catch (AssertionError ae) { }
        
        List<Tweet> tweets;
        try {
            tweets = TweetReader.readTweetsFromWeb(SAMPLE_SERVER);
        } catch (IOException ioe) {
        	SAMPLE_SERVER = makeURLAssertWellFormatted("file:///D:/programme/jaba/P4/src/tweetPoll.py");
        	tweets = TweetReader.readTweetsFromWeb(SAMPLE_SERVER);
        }
        
        // display some characteristics about the tweets
        System.err.println("fetched " + tweets.size() + " tweets");
        
        final Timespan span = Extract.getTimespan(tweets);
        System.err.println("ranging from " + span.getStart() + " to " + span.getEnd());
        
        final Set<String> mentionedUsers = Extract.getMentionedUsers(tweets);
        System.err.println("covers " + mentionedUsers.size() + " Twitter users");
        
        // infer the follows graph
        final Map<String, Set<String>> followsGraph = MySocialNetwork.guessFollowsGraph(tweets);
        System.err.println("follows graph has " + followsGraph.size() + " nodes");
        
        // print the top-N influencers
        final int count = 10;
        final List<String> influencers = MySocialNetwork.influencers(followsGraph);
        for (String username : influencers.subList(0, Math.min(count, influencers.size()))) {
            System.out.println(username);
        }
    }
}
