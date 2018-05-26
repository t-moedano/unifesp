package com.springws.model;

public class Person
{
    private Long personId;
    private String personName;
    private String nickname;
    private static final long serialVersionUID = 1L;

    public Long getPersonId()
    {
        return personId;
    }
    public void setPersonId(Long personId)
    {
        this.personId = personId;
    }
    public String getPersonName()
    {
        return personName;
    }
    public void setPersonName(String personName)
    {
        this.personName = personName;
    }
    public String getNickname()
    {
        return nickname;
    }
    public void setNickname(String nickname)
    {
        this.nickname = nickname;
    }
}
