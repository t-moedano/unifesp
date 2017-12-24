import java.util.*;
	public class MachineComposite extends MachineComponent {
	
		@Override
		public int getMachineCount() 
		{
			return components.size();
		}
}