
public class PCDData extends PCDObservado 
{
	private float temperatura;
	private float pressaoAtmosferica; 
	private int ph;

	public PCDData(float temp, float pa, int ph)
	{
		super();
		this.temperatura = temp;
		this.pressaoAtmosferica = pa;
		this.ph = ph;
	}
	public float getTemperatura() {
		return temperatura;
	}
	public void setTemperatura(float temperatura) {
		this.temperatura = temperatura;
	}
	public float getPressaoAtmosferica() {
		return pressaoAtmosferica;
	}
	public void setPressaoAtmosferica(float pressaoAtmosferica) {
		this.pressaoAtmosferica = pressaoAtmosferica;
	}
	public int getPh() {
		return ph;
	}
	public void setPh(int ph) {
		this.ph = ph;
	}
	
	
	
}
