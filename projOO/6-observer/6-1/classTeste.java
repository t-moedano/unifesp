
public class classTeste 
{
	public static void main(String[] args) 
	{
		InstituicaoObserver INPE = new InstituicaoImpl("INPE");
		InstituicaoObserver ITA = new InstituicaoImpl("ITA");
		InstituicaoObserver Unifesp = new InstituicaoImpl("Unifesp");
		
		PCDData pcd1 = new PCDData(24, 5, 2);
		PCDData pcd2 = new PCDData(24, 5, 3);
		
		pcd1.add(INPE);
		pcd1.add(ITA);
		pcd1.add(Unifesp);
		
		pcd1.setPh(4);
		pcd1.notifyObserver("ph");
		
		pcd2.add(Unifesp);
		pcd2.add(ITA);
		pcd2.setPressaoAtmosferica(12);
		pcd2.notifyObserver("pA");
		
	}
	
	
}
