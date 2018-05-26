package com.springws.bo;

import com.springws.model.Person;

public interface PersonBo
{

    void create (Person pPerson);
    
    void getByNickName(String pName);
}
