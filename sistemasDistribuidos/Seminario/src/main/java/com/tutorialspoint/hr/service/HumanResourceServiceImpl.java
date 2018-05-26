package com.tutorialspoint.hr.service;

import java.util.List;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.FileSystemXmlApplicationContext;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.springws.bo.PersonBo;
import com.springws.dao.PersonDAO;
import com.springws.model.Person;

@Transactional
@Service
public class HumanResourceServiceImpl implements HumanResourceService 
{

    @Override
    public String bookLeave(String nickname1, String nickname2)
    {
        PersonDAO personDAO = new PersonDAO();
        List<String> teste;
        System.out.println("teste1");
        ApplicationContext appContext =  new FileSystemXmlApplicationContext("/../webapps/seminario/WEB-INF/resources/spring/config/BeanLocations.xml");

        PersonBo personBo = (PersonBo)appContext.getBean("personBo");
      //  personBo.getByNickName(nickname1);
        
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
         s.append("Repetidas de " + nickname1);
         
         for(Long l : list1)
         {
             s.append(l + " ");
         }
         s.append("\n");
         s.append("Repetidas de " + nickname2);
         for(Long l : list2)
         {
             s.append(l + " ");
         }
         return s.toString();
//        Person person2 = personDAO.getPersonByNickName(nickname2);
//       StickerToPersonDAO stickerToPersonDAO = new StickerToPersonDAO();
//        System.out.println(person.getNickname());
//        List<StickerToPerson> stickerToPerson = stickerToPersonDAO.getRepetidas(person.getPersonId());
//        for(StickerToPerson s : stickerToPerson)
//        {
//            System.out.println(s.getStickers().getStickerId());
//        }
        
    }
  
}