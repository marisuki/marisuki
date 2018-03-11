import static org.junit.Assert.*;
import org.junit.Test;
public class FriendshipGraphTest {
	/**
     * Tests that assertions are enabled.
     */
    @Test(expected=AssertionError.class)
    public void testAssertionsEnabled() {
        assert false;
    }

    /**
     * Tests calculateRegularPolygonAngle.
     */
    @Test
    public void calculateTest() {
        FriendshipGraph gra = new FriendshipGraph();
        Person rachel = new Person("Rachel");
        Person ross = new Person("Ross");
        Person ben = new Person("Ben");
        Person kramer = new Person("Kramer");
        gra.addVertex(rachel);
        gra.addVertex(kramer);
        gra.addVertex(ben);
        gra.addVertex(ross);
        gra.addEdge(rachel, ross);
        gra.addEdge(ross, rachel);
        gra.addEdge(ross, ben);
        gra.addEdge(ben, ross);
        assertEquals(1, gra.getDistance(rachel, ross), 0.001);
        assertEquals(2, gra.getDistance(rachel, ben), 0.001);
        assertEquals(0, gra.getDistance(rachel, rachel), 0.001);
        assertEquals(-1, gra.getDistance(rachel, kramer), 0.001);
    }
}
