
public class VectorDraw
{
    
    
    public static void main(String[] args)
    {
        Shape s = new ShapeAdapter();
        
        int x = s.getX();
        int height = s.getHeight();
        int y = s.getY();
        int width = s.getWidth();
        
        System.out.println("x: " + x + " y: " + y + " height: " + height + " width: " + width);
    }
}
