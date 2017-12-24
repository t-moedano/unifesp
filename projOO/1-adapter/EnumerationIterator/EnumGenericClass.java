

import java.util.Enumeration;
import java.util.Vector;

/**
 * @author Thauany Moedano
 * Classe genérica que utiliza enumeration.
 */
public class EnumGenericClass 
{
	Vector vector;
	
	public EnumGenericClass()
	{
		vector = new Vector();
	}
	
	/**
	 * @return retorna um enumerado dado um vetor.
	 */
	public Enumeration getElements()
	{
		Enumeration listaFrutas = vector.elements();
		
		return listaFrutas;
	}
	
	/**
	 * @param element
	 * Adiciona um elemento no vetor
	 */
	public void setElement(String element)
	{
		vector.add(element);
	}
}
