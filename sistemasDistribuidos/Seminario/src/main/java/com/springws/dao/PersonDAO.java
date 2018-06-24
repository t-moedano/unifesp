package com.springws.dao;


import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;




public class PersonDAO 
{
    static Connection connection = null;
    static PreparedStatement preparedStatement = null;

    
    public List<Long> getPersonByNickName(String pName)
    {
           List<Long> list = new ArrayList<>();
            System.out.println("teste2");
            makeJDBCConnection();
            String sql = "select s.sticker_number from stickers s, "
                    + "sticker_to_person sp, person p where p.nickname = ? "
                    + "and p.person_id = sp.person_id and sp.quantity > 1 and sp.sticker_id = s.sticker_id";
            try
            {
                preparedStatement = connection.prepareStatement(sql);
                preparedStatement.setString(1, pName);
                ResultSet rs = preparedStatement.executeQuery();
                while(rs.next())
                {
                    int i = rs.getRow();
                    list.add(rs.getLong(i));
                }
            } catch (SQLException e)
            {
            }
            return list;
    }
    
    private static void makeJDBCConnection() 
    {
 
        try 
        {
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/springws", "root", "admin");
        } catch (SQLException e) 
        {
            return;
        }
 
    }
}
