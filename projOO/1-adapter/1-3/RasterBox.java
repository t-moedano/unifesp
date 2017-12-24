
public class RasterBox
{
   private Coords topLeft, bottomRight;
   
   public RasterBox()
   {
       topLeft = new Coords(2, 3);
       bottomRight = new Coords(4, 5);
   }
   
   public Coords getTopLeft()
   {
       return topLeft;
   }
   
   public Coords getBottomRight()
   {
       return bottomRight;
   }
}
