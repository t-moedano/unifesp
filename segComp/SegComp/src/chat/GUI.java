package chat;

import java.awt.Color;
import java.io.ObjectOutputStream;
import java.net.Socket;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class GUI
{
    private JLabel _message;
    private JTextField _serverPort;
    private JTextField _ip;
    private JTextField _clientPort;
    private JTextField _clientName;
    private JTextField _cipherMode;
    private JPanel _content;
    private JTextArea _text;
    private JTextField _textMessage;
    private JLabel _history;
    private JLabel _messageLabel;
    private JButton _btnSend;
    private JButton _btnExit;
    private ButtonSendListener _buttonSendListener;
    private ButtonExitListener _buttonExitListener;
    private KeyboardListener _keyboardListener;
    private JScrollPane _scrollPane;
    private JFrame _frame;
    
    
    public void createServerInterface()
    {
         _message = new JLabel("Porta do Servidor:");
         _serverPort = new JTextField("12345");
        Object[] texts = {_message, _serverPort, };  
        JOptionPane.showMessageDialog(null, texts);
    }
    
    public void showServerPortInterface()
    {
        JOptionPane.showMessageDialog(null,"Servidor ativo na porta: "+         
                _serverPort.getText());
    }
    public String getServerPort()
    {
        return _serverPort.getText();
    }
    
    public void createClientInterface()
    {
        _message = new JLabel("Verificar!");
        _ip = new JTextField("127.0.0.1");
        _clientPort = new JTextField("12345");
        _clientName = new JTextField("Cliente");
        _cipherMode = new JTextField("ECB");
        Object[] texts = {_message, _ip, _clientPort, _clientName, _cipherMode };  
        JOptionPane.showMessageDialog(null, texts); 
    }
    
    public String getIp()
    {
        return _ip.getText();
    }
    
    public String getClientPort()
    {
        return _clientPort.getText();
    }
    
    public void createChatScreen(ObjectOutputStream pClient, Socket pClientSocket)
    {
        _content = new JPanel();
        _text  = new JTextArea(10,20);
        _text.setEditable(false);
        _text.setBackground(new Color(240,240,240));
        _textMessage = new JTextField(20);
        _history = new JLabel("Histórico");
        _messageLabel = new JLabel("Mensagem");
        _btnSend = new JButton("Enviar");
        _btnSend.setToolTipText("Enviar Mensagem");
        _btnExit = new JButton("Sair");
        _btnExit.setToolTipText("Sair do Chat");
        _buttonSendListener = new ButtonSendListener(pClient, _textMessage, _clientName, _cipherMode.getText());
        _buttonExitListener = new ButtonExitListener(pClientSocket);
        _btnSend.addActionListener(_buttonSendListener);
        _btnExit.addActionListener(_buttonExitListener);
        _btnSend.addKeyListener(_keyboardListener);
        _textMessage.addKeyListener(_keyboardListener);
        _text.setLineWrap(true);  
        _scrollPane = new JScrollPane(_text);
        _content.add(_history);
        _content.add(_scrollPane);
        _content.add(_messageLabel);
        _content.add(_textMessage);
        _content.add(_btnExit);
        _content.add(_btnSend);
        _content.setBackground(Color.LIGHT_GRAY);
        _text.setBorder(BorderFactory.createEtchedBorder(Color.BLUE,Color.BLUE));
        _textMessage.setBorder(BorderFactory.createEtchedBorder(Color.BLUE, Color.BLUE)); 
        _frame = new JFrame();
        _frame.setTitle(_clientName.getText());
        _frame.setContentPane(_content);
        _frame.setLocationRelativeTo(null);
        _frame.setResizable(false);
        _frame.setSize(250,300);
        _frame.setVisible(true);
        _frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    
    public JTextArea getTextArea()
    {
        return _text;
    }
    
    public String getCipherMode()
    {
        return _cipherMode.getText();
    }
}
