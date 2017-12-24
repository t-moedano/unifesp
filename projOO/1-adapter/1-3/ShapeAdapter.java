
public class ShapeAdapter extends Shape
{
    RasterBox rasterBox = new RasterBox();
    
    @Override
    public int getX()
    {
        return rasterBox.getBottomRight().x;
    }
    
    @Override
    public int getY()
    {
        return rasterBox.getBottomRight().y;
    }
    
    @Override
    public int getHeight()
    {
        return rasterBox.getTopLeft().x;
    }
    
    @Override
    public int getWidth()
    {
        return rasterBox.getTopLeft().y;
    }
}
