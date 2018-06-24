package chat;

import java.io.Serializable;

import cipherModes.CipherMode;

public class Message implements Serializable
{

    private static final long serialVersionUID = -5399605122490343339L;
    String msg;
    CipherMode cipherMode;

    public Message(String pMsg, CipherMode pCipherMode)
    {
        msg = pMsg;
        cipherMode = pCipherMode;
    }
}
