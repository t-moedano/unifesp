
/**
 * @author Thauany Moedano
 * Classe de Teste para mostrar o funcionamento do adaptador
 */
public class ClasseTeste 
{
	public static void main(String[] args) 
	{
		IteratorClass iteratorClass = new IteratorClass();
		
		EnumAdapter enumAdapter = new EnumAdapter();
		enumAdapter.setElement("element 1");
		enumAdapter.setElement("element 2");
		
		iteratorClass.showVectorElements(enumAdapter);
	}
}
