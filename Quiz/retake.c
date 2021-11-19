#include <stdio.h>
#include <assert.h>


int biggest_digit (int a)
{
    if (a == 0)
    {
        return 0;
    }
    int temp = a%10;
    if (temp > biggest_digit (a/10))
    {
        return (temp);
    }
}
/*
str if_ascending (int a)
{
    if (a = 0)
    {
        return ("Yes");
    }
    int temp = a%10;
    if (temp < if_ascending(a/10))
    {
        return("No");
    }
    else
    {
        return("Yes");
    }
}               //es meky chashxatec bayc qich er mnum)))
*/
void main()
{
    /* str ascending = if_ascending(12345);
    printf (ascending); */
    int result = biggest_digit (32436);
    printf ("biggest num is %d", result);
    
}
