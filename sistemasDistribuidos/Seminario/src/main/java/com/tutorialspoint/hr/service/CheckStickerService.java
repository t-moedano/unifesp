package com.tutorialspoint.hr.service;

import java.util.List;

import com.springws.dao.PersonDAO;

public class CheckStickerService 
{
    public String verifyTheSticker(String nickname1, String nickname2)
    {
        PersonDAO personDAO = new PersonDAO();
         List<Long> list1 = personDAO.getPersonByNickName(nickname1);
         List<Long> list2 = personDAO.getPersonByNickName(nickname2);
         
         if(list1.size() > list2.size())
         {
             list1.removeAll(list2);
         }
         else
         {
             list2.removeAll(list1);
         }
         StringBuilder s = new StringBuilder();
         s.append("Repetidas de " + nickname1 + " ");
         
         for(Long l : list1)
         {
             s.append(l + " ");
         }
         s.append(" || Repetidas de " + nickname2 + " ");
         for(Long l : list2)
         {
             s.append(l + " ");
         }
         return s.toString();
    }
}