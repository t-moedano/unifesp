
public abstract class TemplateMensagem 
{
	public String msg;
	
	public String templateMethod(String msg)
	{
		msg = "Msg: " + msg + " de: " + getClassName();
		return msg;
	}

	private String getClassName() 
	{
		return "TemplateMensagem";
	}

}
