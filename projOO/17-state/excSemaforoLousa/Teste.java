
public class Teste
{
    public static void main(String[] args)
    {
        final Estado OFF = new Off();
        final Estado ON = new On();
        final Estado PANIC = new Panic();
        final Estado TICK = new Tick();
        
        Semaforo s = new Semaforo();
        s.setEstado(TICK);
        s.estado.verde = "on";
        s.estado.vermelho = "off";
        s.estado.amarelo = "off";
        
        s.setEstado(OFF);
        s.estado.execute();
        s.estado.printSemaforo();
        s.setEstado(ON);
        s.estado.execute();
        s.estado.printSemaforo();
        s.setEstado(TICK);
        for(int i = 0; i < 20; ++i)
        {
            s.estado.execute();
        }
        s.setEstado(PANIC);
        s.estado.printSemaforo();
    }
}
