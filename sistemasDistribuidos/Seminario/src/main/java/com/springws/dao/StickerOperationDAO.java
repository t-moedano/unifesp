package com.springws.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class StickerOperationDAO
{

    public List<Long> getNumberStickers(String pNickname)
    {
        List<Long> listNick = new ArrayList<>();
        try
        {
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/springws", "root", "admin");
            PreparedStatement preparedStatement = connection.prepareStatement("select * from sticker_to_person");
            //preparedStatement.setString(1, pNickname);
            ResultSet resultSet = preparedStatement.executeQuery();
            while(resultSet.next())
            {
                int row = resultSet.getRow();
                listNick.add(resultSet.getLong(row));
            }
           connection.close();
           preparedStatement.close();
           resultSet.close();
        }
        catch(SQLException e)
        {
            System.out.println("a");
        }
        return listNick;
       
    }
}
