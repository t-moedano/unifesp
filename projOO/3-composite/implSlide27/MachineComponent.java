import java.util.ArrayList;
import java.util.List;

public abstract class MachineComponent 
{
	String name;
	protected List components = new ArrayList();
	public int  getMachineCount()
	{
		System.out.println("Machine Count: ");
		return 1;
	}
	public String getName()
	{
		return name;
	}
	public void setName(String name) 
	{
		this.name = name;
	}
	
	

	public void add(MachineComponent component)
	{
		components.add(component);
	}
	
}