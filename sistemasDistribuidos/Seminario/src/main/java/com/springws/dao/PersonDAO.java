package com.springws.dao;


import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import javax.annotation.Resource;

import org.hibernate.SessionFactory;
import org.springframework.transaction.annotation.Transactional;

import com.springws.model.Person;

@Transactional
public class PersonDAO 
{
    static Connection crunchifyConn = null;
    static PreparedStatement crunchifyPrepareStat = null;

    @Resource(name = "sessionFactory")
    private SessionFactory sessionFactory;
    public SessionFactory getSessionFactory() {
        return sessionFactory;}
    public void setSessionFactory(SessionFactory sessionFactory) {
         this.sessionFactory = sessionFactory;
    }

    
    public void create(Person pPerson)
    {
        getSessionFactory().getCurrentSession().save(pPerson);
    }
    
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
                crunchifyPrepareStat = crunchifyConn.prepareStatement(sql);
                crunchifyPrepareStat.setString(1, pName);
                ResultSet rs = crunchifyPrepareStat.executeQuery();
                while(rs.next())
                {
                    int i = rs.getRow();
                    list.add(rs.getLong(i));
                }
            } catch (SQLException e)
            {
                // TODO Auto-generated catch block
               System.out.println("nao executou");
            }
            
            // Execute the Query, and get a java ResultSet
           
            System.out.println("teste");
         //   return (Person) person.get(0);
            return list;
    }
    
    private static void makeJDBCConnection() {
        
        try {
            Class.forName("com.mysql.jdbc.Driver");
            System.out.println("Congrats - Seems your MySQL JDBC Driver Registered!");
        } catch (ClassNotFoundException e) {
            System.out.println("Sorry, couldn't found JDBC driver. Make sure you have added JDBC Maven Dependency Correctly");
            e.printStackTrace();
            return;
        }
 
        try {
            // DriverManager: The basic service for managing a set of JDBC drivers.
            crunchifyConn = DriverManager.getConnection("jdbc:mysql://localhost:3306/springws", "root", "admin");
            if (crunchifyConn != null) {
                System.out.println("Connection Successful! Enjoy. Now it's time to push data");
            } else {
                System.out.println("Failed to make connection!");
            }
        } catch (SQLException e) {
            System.out.println("MySQL Connection Failed!");
            e.printStackTrace();
            return;
        }
 
    }
}
