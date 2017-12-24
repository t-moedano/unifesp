
public class ImageIconProxy extends ImageIcon implements Runnable
{
	final static ImageIcon ABSENT = new ImageIcon("absent");
	final static ImageIcon LOADING = new ImageIcon("loading");
	
	protected String filename;
	protected JFrame callbackFrame;
	public ImageIconProxy(String filename)
	{
		super();
		this.filename = filename;
	}
	
	
	@Override
	public void run()
	{}
	
	public int getIconHeight()
	{
		return ABSENT.getIconHeight();
	}
	
	public int getIconWidth()
	{
		return LOADING.getIconWidth
	}
	
	public void paintIcon()
	{
		System.out.println("Imprimindo... ");
	}
}
