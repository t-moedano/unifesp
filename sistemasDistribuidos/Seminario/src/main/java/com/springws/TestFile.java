package com.springws;

public class TestFile
{
    public static void main(String[] args)
    {
        String test = "0#Panini Knight Logo#true";
        String[] testString = test.split("#");
        System.out.println(testString[0] + " " + testString[1] + " " + testString[2]);
        
        
        Long number = Long.valueOf(testString[0]);
        Boolean bool = Boolean.valueOf(testString[2]);
        
        System.out.println(number + " " + bool);
    }
}
