package com.springws.bo.impl;

import org.springframework.transaction.annotation.Transactional;

import com.springws.bo.PersonBo;
import com.springws.dao.PersonDAO;
import com.springws.model.Person;

@Transactional
public class PersonBoImpl implements PersonBo
{

    PersonDAO personDao;
    
    public void setPersonDao(PersonDAO pPersonDao) 
    {
        this.personDao = pPersonDao;
    }
    
    @Override
    public void create(Person pPerson)
    {
        personDao.create(pPerson);
    }

    @Override
    public void getByNickName(String pName)
    {
        System.out.println("boimpl");
        personDao.getPersonByNickName(pName);
        
    }
}
