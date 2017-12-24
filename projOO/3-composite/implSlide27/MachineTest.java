
public class MachineTest 
{
	public static void main(String[] args) 
	{
		MachineComponent machine = new Machine();
		MachineComponent  machineComposite = new MachineComposite();
		MachineComponent machineCompositeList = new MachineComposite();
		MachineComponent machineCompositeList2 = new MachineComposite();
		
		machineComposite.add(machineCompositeList);
		machineComposite.add(machineCompositeList2);
		
		
		int mc = machineComposite.getMachineCount();
		int m = machine.getMachineCount();
		System.out.println("Machine Composite = " + mc);
		System.out.println("Machine  = " + m);
		
	}
}
